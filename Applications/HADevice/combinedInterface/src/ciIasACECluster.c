/**************************************************************************//**
  \file ciIasACECluster.c

  \brief
    Combined Interface IAS ACE cluster implementation.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2013, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    18/11/2014 Yogesh- Created.
******************************************************************************/
#ifdef APP_DEVICE_TYPE_COMBINED_INTERFACE

/******************************************************************************
                    Includes section
******************************************************************************/
#include <ciIasACECluster.h>
#include <ciIasZoneCluster.h>
#include <uartManager.h>
#include <commandManager.h>
#include <haClusters.h>

/******************************************************************************
                    Local variables section
******************************************************************************/
//ByPass Table
bypassTable_t byPassList;

//Arm Table with a maximum entry of 3
ZCL_ACEArm_t armTable[ZONE_TABLE_ENTRIES];

//Panel Status Timer
static uint8_t panelStatusTimer = 0;

/******************************************************************************
                    Prototypes section
******************************************************************************/
static void ZCL_ReadAttributeResp(ZCL_Notify_t *ntfy);
static void ZCL_WriteAttributeResp(ZCL_Notify_t *ntfy);
static ZCL_Status_t aceGetZoneInformationCommandInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_GetZoneInformationCommand_t *payload);
static ZCL_Status_t aceGetZoneStatusCommandInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ACEGetZoneStatusCommand_t *payload);
static ZCL_Status_t aceByPassCommandInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload);
static ZCL_Status_t aceArmCommandInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ACEArm_t *payload);
static void iasACEFillGetZoneInformationCommand(ZCL_GetZoneInformationResp_t *zonepayload, uint8_t zoneId );
static ZCL_Status_t aceEmergencyCommandInd(ZCL_Addressing_t *addressing);
static ZCL_Status_t aceFireCommandInd(ZCL_Addressing_t *addressing);
static ZCL_Status_t acePanicCommandInd(ZCL_Addressing_t *addressing);
static ZCL_Status_t aceGetZoneIdMapCommandInd(ZCL_Addressing_t *addressing);
static ZCL_Status_t aceGetPanelStatusCommandInd(ZCL_Addressing_t *addressing);
static void getPanelStatusChangeCmdTimerCallback();
static ZCL_Status_t  aceGetByPassesZoneListCommandInd(ZCL_Addressing_t *addressing);
static AttibuteReadCallback_t   readAttributeCallback;
static AttributeWriteCallback_t writeAttributeCallback;
static HAL_AppTimer_t getZoneStatusChangeCmdTimer;
static void getPanelStatusChangeCmdTimerFired(void);

/*****************************************************************************/
/******************************************************************************
                    Prototypes section
******************************************************************************/
ZCL_IasACEClusterCommands_t ciIASACEClusterCommands =
{
  ZCL_DEFINE_IAS_ACE_CLUSTER_COMMANDS(aceArmCommandInd,\
                    NULL,\
                    aceByPassCommandInd,\
                    aceEmergencyCommandInd,\
                    aceFireCommandInd,\
                    acePanicCommandInd,\
                    aceGetZoneIdMapCommandInd,\
                    NULL,\
                    aceGetZoneInformationCommandInd,\
                    NULL,\
                    aceGetPanelStatusCommandInd,\
                    NULL,\
                    aceGetZoneStatusCommandInd,\
                    NULL,\
                    NULL,\
                    NULL,\
                    aceGetByPassesZoneListCommandInd,\
                    NULL,\
                    NULL
                    )\
};

/******************************************************************************
                    Implementation section
******************************************************************************/
/**************************************************************************//**
\brief Initializes IAS ACE cluster
******************************************************************************/
void iasACEClusterInit(void)
{
  //Initializes the byPass Table entries
  byPassList.totalZones = DEFAULT_VAL;
  
  for(uint8_t bypassArmEntry= DEFAULT_VAL; bypassArmEntry < ZONE_TABLE_ENTRIES; bypassArmEntry++)
  {
    //Initializes the byPass Table entries
    byPassList.bypassTable[bypassArmEntry].zoneId = 0xFF;
    byPassList.bypassTable[bypassArmEntry].armDisarmCode[0] = DEFAULT_VAL;

    //Initializes the Arm Table entries  
    armTable[bypassArmEntry].zoneId= 0xFF;
    armTable[bypassArmEntry].armMode= 0xFF;
    armTable[bypassArmEntry].lengthArmMode = 0xFF;
    armTable[bypassArmEntry].armDisarmCode[0] = DEFAULT_VAL;
  }
}

/**************************************************************************//**
\brief Sends Read Attribute command unicastly

\param[in] mode - address mode;
\param[in] addr - short address of destination node;
\param[in] ep   - destination endpoint;
\param[in] attr - attribute id;
\param[in] cb   - callback function
******************************************************************************/
void iasACEReadAttribute(APS_AddrMode_t mode,ShortAddr_t addr, Endpoint_t ep,
  uint16_t attr, AttibuteReadCallback_t cb)
{
  ZCL_Request_t *req;
  ZCL_NextElement_t element;
  ZCL_ReadAttributeReq_t readAttrReqElement;

  if (!(req = getFreeCommand()))
    return;

  readAttributeCallback = cb;

  readAttrReqElement.id = attr;

  element.payloadLength = DEFAULT_VAL;
  element.payload = req->requestPayload;
  element.id = ZCL_READ_ATTRIBUTES_COMMAND_ID;
  element.content = &readAttrReqElement;
  ZCL_PutNextElement(&element);

  fillCommandRequest(req, ZCL_READ_ATTRIBUTES_COMMAND_ID, element.payloadLength);
  fillDstAddressing(&req->dstAddressing, mode, addr, ep, IAS_ACE_CLUSTER_ID);
  req->ZCL_Notify = ZCL_ReadAttributeResp;

  commandManagerSendAttribute(req);
}

/**************************************************************************//**
\brief Sends Write Attribute command unicastly

\param[in] mode - address mode;
\param[in] addr - short address of destination node;
\param[in] attr - attribute id;
\param[in] ep   - destination endpoint;
\param[in] type - attribute type;
\param[in] cb   - callback function;
\param[in] data - the pointer to memory with value to be written;
\param[in] size - size of data parameter in octets
******************************************************************************/
void iasACEWriteAttribute(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep,
  uint16_t attr, uint8_t type, AttributeWriteCallback_t cb, void *data, uint8_t size)
{
  ZCL_Request_t *req;
  ZCL_WriteAttributeReq_t writeAttrReq;

  if (!(req = getFreeCommand()))
    return;

  writeAttributeCallback = cb;

  writeAttrReq.id = attr;
  writeAttrReq.type = type;
  memcpy(req->requestPayload, (uint8_t *)&writeAttrReq, sizeof(ZCL_WriteAttributeReq_t) - sizeof(uint8_t));
  memcpy(req->requestPayload + sizeof(ZCL_WriteAttributeReq_t) - sizeof(uint8_t), (uint8_t *)data, size);

  fillCommandRequest(req, ZCL_WRITE_ATTRIBUTES_COMMAND_ID, size + sizeof(ZCL_WriteAttributeReq_t) - sizeof(uint8_t));
  fillDstAddressing(&req->dstAddressing, mode, addr, ep, IAS_ACE_CLUSTER_ID);
  req->ZCL_Notify = ZCL_WriteAttributeResp;

  commandManagerSendAttribute(req);
}

/**************************************************************************//**
\brief Indication of read attribute response

\param[in] resp - pointer to response
******************************************************************************/
static void ZCL_ReadAttributeResp(ZCL_Notify_t *ntfy)
{
  ZCL_NextElement_t element;
  ZCL_ReadAttributeResp_t *readAttributeResp;
  int16_t attributeValue;

  if (ZCL_SUCCESS_STATUS == ntfy->status)
  {
    element.id            = ZCL_READ_ATTRIBUTES_RESPONSE_COMMAND_ID;
    element.payloadLength = ntfy->responseLength;
    element.payload       = ntfy->responsePayload;
    element.content       = NULL;

    ZCL_GetNextElement(&element);
    readAttributeResp = (ZCL_ReadAttributeResp_t *) element.content;

    if (readAttributeCallback)
      readAttributeCallback((void *)&readAttributeResp->value[0]);
    
    memcpy(&attributeValue, &readAttributeResp->value[0], sizeof(uint16_t));
#if APP_ENABLE_CONSOLE == 1
    LOG_STRING(readAttrSuccessStr, "<-Read IasACE attribute (0x%x) response: success  t = 0x%x\r\n");
    appSnprintf(readAttrSuccessStr, (unsigned)readAttributeResp->id, attributeValue);
#endif
  }
  else
  {
#if APP_ENABLE_CONSOLE == 1
    LOG_STRING(readAttrFailStr, " +Read IasACE attribute failed: status = 0x%2x\r\n");
    appSnprintf(readAttrFailStr, (unsigned)ntfy->status);
#endif
  }
}

/**************************************************************************//**
\brief Indication of write attribute response

\param[in] resp - pointer to response
******************************************************************************/
static void ZCL_WriteAttributeResp(ZCL_Notify_t *ntfy)
{
  ZCL_NextElement_t element;

  if (ZCL_SUCCESS_STATUS == ntfy->status)
  {
    element.id            = ZCL_WRITE_ATTRIBUTES_RESPONSE_COMMAND_ID;
    element.payloadLength = ntfy->responseLength;
    element.payload       = ntfy->responsePayload;
    element.content       = NULL;

    ZCL_GetNextElement(&element);

    if (writeAttributeCallback)
      writeAttributeCallback();
#if APP_ENABLE_CONSOLE == 1
    LOG_STRING(writeAttrSuccessStr, " <-Write IasACE attribute response: success\r\n");
    appSnprintf(writeAttrSuccessStr);
#endif
  }
  else
  {
#if APP_ENABLE_CONSOLE == 1
    LOG_STRING(writeAttrFailStrTwo, " +Write IasACE attribute failed: status = 0x%x\r\n");
    appSnprintf(writeAttrFailStrTwo, (unsigned)ntfy->status);
#endif
  }
}

/**************************************************************************//**
\brief Sends ACEGetPanelStatusChanged Command

\param[in] mode - address mode;
\param[in] addr - short address of destination node;
\param[in] panel_status - Panel status value;
\param[in] seconds_remaining  - seconds remaining for the panel status;
\param[in] audible_noti - audible notificaiton;
\param[in] alarmstatus   - alarm status;
******************************************************************************/
void acePanelStatusChangedCommand(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep,ZCL_PanelStatus_t panelStatus,
                              uint8_t secondsRemaining, ZCL_AudibleNotification_t audibleNoti,ZCL_AlarmStatus_t alarmStatus)
{
  ZCL_Request_t *req;
  ZCL_ACEPanelStatusChangedCommand_t *resp;
  
  if (!(req = getFreeCommand()))
    return;

  //Forming the command payload to be sent
  fillCommandRequest(req, ZCL_IAS_ACE_CLUSTER_PANEL_STATUS_CHANGED_COMMAND_ID, sizeof(ZCL_ACEPanelStatusChangedCommand_t));
  resp = (ZCL_ACEPanelStatusChangedCommand_t *) req->requestPayload;
  
  //Filling the response structure with the input parameters
  resp-> panel_status= panelStatus;
  resp->seconds_remaining = secondsRemaining;
  resp->audible_noti = audibleNoti;
  resp->alarmstatus = alarmStatus;
  
  //To start the timer only when the state of the panel is of Exit and Entry Delay
  if((panelStatus == EXIT_DELAY || panelStatus == ENTRY_DELAY) && (secondsRemaining > DEFAULT_VAL))
  {
      panelStatusTimer = secondsRemaining;
      getZoneStatusChangeCmdTimer.interval = PANEL_STAUS_TIMER;
      getZoneStatusChangeCmdTimer.mode     = TIMER_ONE_SHOT_MODE;
      getZoneStatusChangeCmdTimer.callback = getPanelStatusChangeCmdTimerFired;
      HAL_StartAppTimer(&getZoneStatusChangeCmdTimer);
  }
  fillDstAddressingServer(&req->dstAddressing, mode, addr, ep, IAS_ACE_CLUSTER_ID);
  commandManagerSendCommand(req);
  return;
}

/**************************************************************************//**
\brief ACEGetPanelStatus Command Indication

\param[in] addressing - pointer to addressing information;

\return status of indication routine
******************************************************************************/
static ZCL_Status_t aceGetPanelStatusCommandInd(ZCL_Addressing_t *addressing)
{
  ZCL_Request_t *req;
  ZCL_ACEGetPanelStatusCommandResp_t *resp;
  
  if (!(req = getFreeCommand()))
    return ZCL_INSUFFICIENT_SPACE_STATUS;

  fillCommandRequest(req, ZCL_IAS_ACE_CLUSTER_GET_PANEL_STATUS_RESPONSE_COMMAND_ID, sizeof(ZCL_ACEGetPanelStatusCommandResp_t));
  resp = (ZCL_ACEGetPanelStatusCommandResp_t *)req->requestPayload;
  
  resp->panel_status= PANEL_DEFAULT_STATE;
  //To check whether the timer is already started or not
  if(panelStatusTimer > DEFAULT_VAL)
  {
    resp->seconds_remain = getZoneStatusChangeCmdTimer.interval;
  }
  else
  {
    resp->seconds_remain = TIME_REMAINING_DEFAULT;
  }
  resp->audible_noti = DEFAULT_SOUND;
  resp->alarmstatus = NO_ALARM;
  fillDstAddressingViaSourceAddressing(&req->dstAddressing, addressing, ZCL_CLUSTER_SIDE_CLIENT);
  commandManagerSendCommand(req);
#if APP_ENABLE_CONSOLE == 1    
    LOG_STRING(aceCmdStr, " ->ACEGetPanelStatusCommandInd Received\r\n");
    appSnprintf(aceCmdStr);
#endif    
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief ACEGetZoneStatus Command Indication

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
static ZCL_Status_t aceGetZoneStatusCommandInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ACEGetZoneStatusCommand_t *payload)
{
  ZCL_Request_t *req;
  uint8_t payloadResponse[PAYLOAD_SIZE];
  uint8_t payloadZoneResponseIndex = DEFAULT_VAL;
  uint8_t resp_count = DEFAULT_VAL;
  uint8_t zoneIdOffset = DEFAULT_VAL;  
  
  if (!(req = getFreeCommand()))
    return ZCL_INSUFFICIENT_SPACE_STATUS;

  payloadResponse[payloadZoneResponseIndex] = 1;
  payloadZoneResponseIndex++;
  payloadResponse[payloadZoneResponseIndex] = payload->max_number_zoneids;
  payloadZoneResponseIndex++;
  uint8_t maxZoneNumber = payload->max_number_zoneids;  
  for(uint8_t zone_check = payload->starting_zone_id; zone_check < ZONE_TABLE_ENTRIES; zone_check++)
  {
    if(maxZoneNumber >0)
    {
      payloadResponse[payloadZoneResponseIndex] = zoneTables[zone_check].zoneId;
      payloadZoneResponseIndex++;
      uint16_t zoneStatus = zoneTables[zone_check].zoneStatus;
      memcpy(&payloadResponse[payloadZoneResponseIndex],&zoneStatus, 2);
      payloadZoneResponseIndex +=2;
      maxZoneNumber--;
      resp_count++;
    }
  }

  if(resp_count != payload->max_number_zoneids)
  {
    payloadResponse[zoneIdOffset] = DEFAULT_VAL;
    zoneIdOffset++;
    payloadResponse[zoneIdOffset] =resp_count;
  }
  
  fillCommandRequest(req, ZCL_IAS_ACE_CLUSTER_GET_ZONE_STATUS_RESPONSE_COMMAND_ID, payloadZoneResponseIndex);
  memcpy(req->requestPayload , &payloadResponse[0],payloadZoneResponseIndex);
  fillDstAddressingViaSourceAddressing(&req->dstAddressing, addressing, ZCL_CLUSTER_SIDE_CLIENT);
  commandManagerSendCommand(req);
#if APP_ENABLE_CONSOLE == 1
    LOG_STRING(aceCmdStr, " ->ACEGetZoneStatusCommandRespInd Received\r\n");
    appSnprintf(aceCmdStr);
#endif
  (void) payloadLength;  
  return ZCL_SUCCESS_STATUS; 
}

/**************************************************************************//**
\brief Sends ACEGetZoneStatusChanged Command

\param[in] mode - address mode;
\param[in] addr - short address of destination node;
\param[in] zoneId - zoneId which changed the status;
\param[in] zoneStatus  - status of the zoneId which changed;
\param[in] audible_sound - audible sound;
\param[in] zone_label   - zone label;
******************************************************************************/
void aceZoneStatusChangedCommand(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep,
                                        uint8_t zoneId, uint8_t zoneStatus, uint8_t audibleSound, uint16_t zoneLabel)
{
  ZCL_Request_t *req;
  ZCL_ACEZoneStatusChangedCommand_t *resp;
  
  if (!(req = getFreeCommand()))
    return;
  
  //Memory Allocation 
  fillCommandRequest(req, ZCL_IAS_ACE_CLUSTER_ZONE_STATUS_CHANGED_COMMAND_ID, sizeof(ZCL_ACEZoneStatusChangedCommand_t));
  resp = (ZCL_ACEZoneStatusChangedCommand_t *) req->requestPayload;
  
  //Response filling  
  resp->zoneid = zoneId;
  resp->zoneStatus = zoneStatus;
  resp->audible_noti = audibleSound;
  resp->zoneLength = ZCL_IAS_ACE_ZONE_LABEL_SIZE;
  memcpy(&resp->zoneLabel[0], &zoneLabel, ZCL_IAS_ACE_ZONE_LABEL_SIZE);

  //Address Allocation
  fillDstAddressingServer(&req->dstAddressing, mode, addr, ep, IAS_ACE_CLUSTER_ID);
  commandManagerSendCommand(req);

  return;
}

/**************************************************************************//**
\brief ACEArm Command Indication

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
static ZCL_Status_t aceArmCommandInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ACEArm_t *payload)
{
  ZCL_Request_t *req;
  ZCL_ACEResponseArm_t arm_response;
  uint8_t armAction = DEFAULT_VAL;
  uint8_t armSeqCheck = DEFAULT_VAL;
  
  //Assigning default value
  arm_response.armMode = DEFAULT_VAL;

  //Arm Payload extraction and action  
  if(payload->zoneId < ZONE_TABLE_ENTRIES)
  {
    if(armTable[payload->zoneId].zoneId == payload->zoneId)
    {
      //Compare the disarm_code Code
      for (uint8_t byteCheck = DEFAULT_VAL ; byteCheck < 8; byteCheck++)
      {
        if(armTable[payload->zoneId].armDisarmCode[byteCheck] == payload->armDisarmCode[byteCheck])
          armSeqCheck++;
       }
      if(armSeqCheck == ZCL_IAS_ACE_ARM_DISARM_CODE_SIZE)
        armAction = 1;
      else
        arm_response.armMode = INVALID_ARMCODE;
    }
    else if(payload->zoneId == zoneTables[payload->zoneId].zoneId)
    {
      armTable[payload->zoneId].armMode = payload->armMode;
      armTable[payload->zoneId].zoneId = payload->zoneId;
      armTable[payload->zoneId].lengthArmMode = payload->lengthArmMode;
      memcpy(&armTable[payload->zoneId].armDisarmCode,payload->armDisarmCode,ZCL_IAS_ACE_ARM_DISARM_CODE_SIZE);
      armAction = 1;
    }
    if((armAction))
    {
      if(payload->armMode == ALL_ZONE_ARMED)
      {
        armTable[payload->zoneId].armMode = ONLY_NIGHT_SLEEP_ZONES_ARMED;
        arm_response.armMode = armTable[payload->zoneId].armMode;
      }
      else if((payload->armMode == ALL_ZONE_DISARMED )  && (ALL_ZONE_DISARMED == armTable[payload->zoneId].armMode))
      {
        arm_response.armMode = ALREADY_DISARMED;
      }
      else
      {
        arm_response.armMode = armTable[payload->zoneId].armMode;
      }
    }
  }
  //Allocating Memory for the response
  if (!(req = getFreeCommand()))
    return ZCL_INSUFFICIENT_SPACE_STATUS;
  
  fillCommandRequest(req, ZCL_IAS_ACE_CLUSTER_ARM_RESPONSE_COMMAND_ID, sizeof(ZCL_ACEResponseArm_t));
  memcpy(req->requestPayload, &arm_response, sizeof(ZCL_ACEResponseArm_t));
  fillDstAddressingViaSourceAddressing(&req->dstAddressing, addressing, ZCL_CLUSTER_SIDE_CLIENT);
  commandManagerSendCommand(req);
  (void) payloadLength;
  return ZCL_SUCCESS_STATUS; 
}

/**************************************************************************//**
\brief Fills iasACEFillGetZoneInformation Command

\param[in] zonepayload - pointer to payload for filling;
\param[in] zoneId - zoneId base to get relevant informationh;

\return none
******************************************************************************/
static void iasACEFillGetZoneInformationCommand(ZCL_GetZoneInformationResp_t *zonepayload, uint8_t zoneId)
{
  if(zoneId < ZONE_TABLE_ENTRIES)
  {
    zonepayload->zoneId      = zoneTables[zoneId].zoneId;
    zonepayload->zoneType    = zoneTables[zoneId].zoneType;
    zonepayload->zoneAddress = zoneTables[zoneId].zoneAddress;
  }
  else
  {
    zonepayload->zoneId = 0xFF;
    zonepayload->zoneType = 0xFFFF;
    zonepayload->zoneAddress = DEFAULT_EXT_ADDR;
  }
  zonepayload->length    = ZCL_IAS_ACE_ZONE_LABEL_SIZE;
  for ( uint8_t zoneLabelSize = 0; zoneLabelSize < ZCL_IAS_ACE_ZONE_LABEL_SIZE ; zoneLabelSize++)
  {
    zonepayload->zoneLabel[zoneLabelSize] = DEFAULT_VAL;
    zonepayload->zoneLabel[zoneLabelSize] = DEFAULT_VAL;
  }
}

/**************************************************************************//**
\brief ACEGetZoneInformation Command Indication

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
static ZCL_Status_t aceGetZoneInformationCommandInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_GetZoneInformationCommand_t *payload)
{
  ZCL_Request_t *req;

  if (!(req = getFreeCommand()))
    return ZCL_INSUFFICIENT_SPACE_STATUS;
  
  fillCommandRequest(req, ZCL_IAS_ACE_CLUSTER_GET_ZONE_INFORMATION_RESPONSE_COMMAND_ID, sizeof(ZCL_GetZoneInformationResp_t));
  iasACEFillGetZoneInformationCommand((ZCL_GetZoneInformationResp_t *)req->requestPayload ,payload->zoneId);
  fillDstAddressingViaSourceAddressing(&req->dstAddressing, addressing, ZCL_CLUSTER_SIDE_CLIENT);
  commandManagerSendCommand(req);
  (void) payloadLength;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief ACEGetZoneIdMap Command Indication

\param[in] addressing - pointer to addressing information;

\return status of indication routine
******************************************************************************/
static ZCL_Status_t aceGetZoneIdMapCommandInd(ZCL_Addressing_t *addressing)
{
  ZCL_Request_t *req;
  ZCL_GetZoneIdMapResponse_t *payload;
  uint8_t responsePayload = DEFAULT_VAL;
  uint8_t zoneidTrack = DEFAULT_VAL;
  
  if (!(req = getFreeCommand()))
    return ZCL_INSUFFICIENT_SPACE_STATUS;

  fillCommandRequest(req, ZCL_IAS_ACE_CLUSTER_GET_ZONE_ID_MAP_RESPONSE_COMMAND_ID, sizeof(ZCL_GetZoneIdMapResponse_t));
  payload = (ZCL_GetZoneIdMapResponse_t *) req->requestPayload;
  
  //Initializing the response payload
  for(uint8_t zoneEntry = 0 ; zoneEntry < ZCL_IAS_ACE_MAP_ID_RESPONSE_SIZE ; zoneEntry++)
  {
    payload->getZoneIdMapResponse[zoneEntry] = DEFAULT_VAL;
  }
  
  //Framing response packets and typically 256 zoneIds are allowed
  for(uint8_t zoneIdEntry = DEFAULT_VAL; zoneIdEntry < ZONE_TABLE_ENTRIES; zoneIdEntry++)
  {
    if(zoneTables[zoneIdEntry].zoneId != 0xFF)
    {
      if(responsePayload < ZCL_IAS_ACE_MAP_ID_RESPONSE_SIZE)
      {
        payload->getZoneIdMapResponse[responsePayload] |= 1 << zoneIdEntry;
        zoneidTrack++;
        if(zoneidTrack == ZCL_IAS_ACE_MAP_ID_RESPONSE_SIZE)
        {
          responsePayload++;
        }
      }
    }
  }

  fillDstAddressingViaSourceAddressing(&req->dstAddressing, addressing, ZCL_CLUSTER_SIDE_CLIENT);
  commandManagerSendCommand(req);
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief ACEByPass Command Indication

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/         
static ZCL_Status_t aceByPassCommandInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload)
{
  ZCL_Request_t *req;
  uint8_t payloadExtractLength = DEFAULT_VAL;
  uint8_t payloadZoneResponseIndex = DEFAULT_VAL;
  uint8_t zoneIdOffset = 1;
  
  //Extract Payload
  uint8_t payload_extract[PAYLOAD_SIZE];
  uint8_t payloadResponse[PAYLOAD_SIZE];
  memcpy(&payload_extract[payloadExtractLength], payload,payloadLength);
  uint8_t totalZones = payload_extract[payloadExtractLength];
  payloadExtractLength++;
  zoneIdOffset = payload_extract[payloadExtractLength];
  payloadExtractLength++;
  
  //Total Number of Zones in the response
  payloadResponse[payloadZoneResponseIndex] = totalZones;
  payloadZoneResponseIndex++;
  
  for( uint8_t zonesearch = DEFAULT_VAL ;zonesearch < totalZones ;zonesearch++)
  {
    if(zoneIdOffset >= ZONE_TABLE_ENTRIES)
    {
      payloadResponse[payloadZoneResponseIndex]  = INVALID_ZONE_ID; /*Suitale would be Invalid*/
    }    
    else
    {
      if(zoneTables[zoneIdOffset].zoneId == zoneIdOffset)
      {
        if(byPassList.bypassTable[zoneIdOffset].zoneId != zoneIdOffset)
        {
          byPassList.bypassTable[zoneIdOffset].zoneId = zoneIdOffset;
            
          //Compare the disarm_code Code
          if((byPassList.bypassTable[zoneIdOffset].armDisarmCode == DEFAULT_VAL) ||
               (memcmp(byPassList.bypassTable[zoneIdOffset].armDisarmCode,&payload_extract[totalZones+2],ZCL_IAS_ACE_ARM_DISARM_CODE_SIZE)))
          {
            memcpy(&byPassList.bypassTable[zoneIdOffset].armDisarmCode[0], &payload_extract[totalZones+2],ZCL_IAS_ACE_ARM_DISARM_CODE_SIZE);
            byPassList.totalZones++;
            payloadResponse[payloadZoneResponseIndex] = ZONE_BYPASSED; 
          }
          else
          {
            payloadResponse[payloadZoneResponseIndex] = INVALID_ARM_DISARM_CODE;
          }
        }
        else if(byPassList.bypassTable[zoneIdOffset].zoneId == zoneIdOffset)
        {
          uint8_t compareSeqCheck = DEFAULT_VAL;
          //Compare the disarm_code Code
          for (uint8_t byteCheck = DEFAULT_VAL ; byteCheck < 8; byteCheck++)
          {
            if(byPassList.bypassTable[zoneIdOffset].armDisarmCode[byteCheck] == payload_extract[totalZones+2+byteCheck])
              compareSeqCheck++;
          }
          if(compareSeqCheck == 0x08)
            payloadResponse[payloadZoneResponseIndex] = ZONE_BYPASSED;
          else
            payloadResponse[payloadZoneResponseIndex] = INVALID_ARM_DISARM_CODE;
        }
        else
        {
          payloadResponse[payloadZoneResponseIndex] = NOT_ALLOWED;
        } 
      }
      else
      {
        payloadResponse[payloadZoneResponseIndex] = UNKNOWN_ZONE_ID;
      }
    }
    zoneIdOffset = payload_extract[payloadExtractLength++];
    payloadZoneResponseIndex++;
  }
  
  //Allocating Memory for the response
  if (!(req = getFreeCommand()))
    return ZCL_INSUFFICIENT_SPACE_STATUS;

   //Allocating Buffer Space for the Command
   fillCommandRequest(req, ZCL_IAS_ACE_CLUSTER_BYPASS_RESPONSE_COMMAND_ID, payloadZoneResponseIndex);
  
   //Payload Copy into the request Payload.
   memcpy(req->requestPayload, &payloadResponse[0],payloadZoneResponseIndex);
   
  //fillCommandRequest(req, BYPASS_RESP, sizeof(ZCL_AceByPassResponseCommand_t));
  fillDstAddressingViaSourceAddressing(&req->dstAddressing, addressing, ZCL_CLUSTER_SIDE_CLIENT);
  commandManagerSendCommand(req);
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief ACEGetByPassesZoneList Command Indication

\param[in] addressing - pointer to addressing information;

\return status of indication routine
******************************************************************************/
static  ZCL_Status_t  aceGetByPassesZoneListCommandInd(ZCL_Addressing_t *addressing)
{
  ZCL_Request_t *req;
  uint8_t payloadSetResponseListIndex = DEFAULT_VAL;
  uint8_t payloadResponse[PAYLOAD_SIZE];
  
  if (!(req = getFreeCommand()))
    return ZCL_INSUFFICIENT_SPACE_STATUS;
  
  payloadResponse[payloadSetResponseListIndex] = byPassList.totalZones;
  payloadSetResponseListIndex++;

  for (uint8_t zonelist = DEFAULT_VAL; zonelist < byPassList.totalZones ; zonelist++)
  {
    payloadResponse[payloadSetResponseListIndex] = byPassList.bypassTable[zonelist].zoneId;
    payloadSetResponseListIndex++;
  }
  
   //Allocating Buffer Space for the Command
   fillCommandRequest(req, ZCL_IAS_ACE_CLUSTER_SET_BYPASSED_ZONE_LIST_COMMAND_ID, payloadSetResponseListIndex--);
  
   //Payload Copy into the request Payload.
   memcpy(req->requestPayload, &payloadResponse[0],payloadSetResponseListIndex--);

  fillDstAddressingViaSourceAddressing(&req->dstAddressing, addressing, ZCL_CLUSTER_SIDE_CLIENT);
  commandManagerSendCommand(req);
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief ACEEmergency Command Indication

\param[in] addressing - pointer to addressing information;

\return status of indication routine
******************************************************************************/
static ZCL_Status_t aceEmergencyCommandInd(ZCL_Addressing_t *addressing)
{
  (void)addressing;
#if APP_ENABLE_CONSOLE == 1
  appSnprintf(" ->ACE Emergency Command Received\r\n");
#endif
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief ACEFire Command Indication

\param[in] addressing - pointer to addressing information;

\return status of indication routine
******************************************************************************/
static  ZCL_Status_t aceFireCommandInd(ZCL_Addressing_t *addressing)
{
  (void)addressing;
#if APP_ENABLE_CONSOLE == 1
  appSnprintf(" ->ACE Fire Command Received\r\n");
#endif
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief  ACEPanic Command Indication

\param[in] addressing - pointer to addressing information;

\return status of indication routine
******************************************************************************/
static ZCL_Status_t acePanicCommandInd(ZCL_Addressing_t *addressing)
{
  (void)addressing;
#if APP_ENABLE_CONSOLE == 1
  appSnprintf(" ->ACE Panic Command Received\r\n");
#endif
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
 \brief getPanelStatusChangeCmdTimerCallback
 \param none
 \return none
******************************************************************************/
void getPanelStatusChangeCmdTimerCallback()
{
  ZCL_Request_t *req;
  ZCL_ACEGetPanelStatusCommandResp_t *resp;
  ShortAddr_t nwk_addr;
  
  if (!(req = getFreeCommand()))
    return;
  
  fillCommandRequest(req, ZCL_IAS_ACE_CLUSTER_PANEL_STATUS_CHANGED_COMMAND_ID, sizeof(ZCL_ACEGetPanelStatusCommandResp_t));
  resp = (ZCL_ACEGetPanelStatusCommandResp_t *) req->requestPayload;
  nwk_addr = NWK_GetShortAddr();
  
  resp->panel_status= PANEL_DEFAULT_STATE;
  resp->seconds_remain = panelStatusTimer;
  resp->audible_noti = DEFAULT_SOUND;
  resp->alarmstatus = NO_ALARM;
  
  fillDstAddressingServer(&req->dstAddressing, ADRESS_MODE, nwk_addr, ACE_ENDPT, IAS_ACE_CLUSTER_ID);
  commandManagerSendCommand(req);
  
  //To Send periodic panel status change update of One second
  if(panelStatusTimer > DEFAULT_VAL)
  {
    HAL_StartAppTimer(&getZoneStatusChangeCmdTimer);
  }
  else
  {
    //To reset the timer count
    panelStatusTimer = 0;
  }
#if APP_ENABLE_CONSOLE == 1
    LOG_STRING(aceCmdStr, " ->ACEGetPanelStatusCommandInd Received\r\n");
    appSnprintf(aceCmdStr);
#endif
    
}

/*********************************************************************************************************************//**
 \brief getPanelStatusChangeCmdTimerFired
***********************************************************************************************************************/
static void getPanelStatusChangeCmdTimerFired(void)
{
  HAL_StopAppTimer(&getZoneStatusChangeCmdTimer);
  panelStatusTimer--;
  getPanelStatusChangeCmdTimerCallback();
}
#endif // APP_DEVICE_TYPE_COMBINED_INTERFACE
// eof ciIasACECluster.c
