/**************************************************************************//**
  \file ciIasZoneCluster.c

  \brief
    Combined Interface IASZone cluster implementation.

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
#include <ciIasZoneCluster.h>
#include <ciIasACECluster.h>
#include <uartManager.h>
#include <commandManager.h>
#include <haClusters.h>

/******************************************************************************
                    Local variables section
******************************************************************************/
static AttibuteReadCallback_t   readAttributeCallback;
static AttributeWriteCallback_t writeAttributeCallback;
zoneTable_t zoneTables[ZONE_TABLE_ENTRIES];
//Initialize Zone Table entries
static  uint8_t Zone_table_entries = DEFAULT_VAL;

/******************************************************************************
                    Prototypes section
******************************************************************************/
static void ZCL_ReadAttributeResp(ZCL_Notify_t *ntfy);
static void ZCL_WriteAttributeResp(ZCL_Notify_t *ntfy);
static ZCL_Status_t ZoneStatusChangeNotificationCommandInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ZoneStatusChangeNot_t *payload);
static ZCL_Status_t ZoneEnrollRequestCommandInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ZoneEnrollRequest_t *payload);
static void ZoneTableEntry(ZCL_ZoneEnrollResCommand_t *response, ZCL_ZoneEnrollRequest_t *payload, ZCL_Addressing_t *addressing);

/*****************************************************************************/
/******************************************************************************
                    Prototypes section
******************************************************************************/
ZCL_IasZoneClusterCommands_t ciIASZoneClusterServerCommands =
{
  ZCL_DEFINE_IAS_ZONE_CLUSTER_COMMANDS(ZoneStatusChangeNotificationCommandInd, ZoneEnrollRequestCommandInd, NULL, NULL, NULL)
};

/******************************************************************************
                    Implementation section
******************************************************************************/
/**************************************************************************//**
\brief Initializes Thermostat cluster
******************************************************************************/
void iaszoneClusterInit(void)
{
  for(uint8_t zoneEntry= DEFAULT_VAL; zoneEntry < ZONE_TABLE_ENTRIES; zoneEntry++)
  {
    zoneTables[zoneEntry].zoneId = 0xFF;
    zoneTables[zoneEntry].zoneType = 0xFFFF;
    zoneTables[zoneEntry].zoneStatus = 0x0000;
    zoneTables[zoneEntry].zoneAddress = DEFAULT_EXT_ADDR;
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
void iaszoneReadAttribute(APS_AddrMode_t mode,ShortAddr_t addr, Endpoint_t ep,
  uint16_t attr, AttibuteReadCallback_t cb)
{
  ZCL_Request_t *req;
  ZCL_NextElement_t element;
  ZCL_ReadAttributeReq_t readAttrReqElement;

  if (!(req = getFreeCommand()))
    return;

  readAttributeCallback = cb;

  readAttrReqElement.id = attr;

  element.payloadLength = 0;
  element.payload = req->requestPayload;
  element.id = ZCL_READ_ATTRIBUTES_COMMAND_ID;
  element.content = &readAttrReqElement;
  ZCL_PutNextElement(&element);

  fillCommandRequest(req, ZCL_READ_ATTRIBUTES_COMMAND_ID, element.payloadLength);
  fillDstAddressing(&req->dstAddressing, mode, addr, ep, IAS_ZONE_CLUSTER_ID);
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
void iaszoneWriteAttribute(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep,
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
  fillDstAddressing(&req->dstAddressing, mode, addr, ep, IAS_ZONE_CLUSTER_ID);
  req->ZCL_Notify = ZCL_WriteAttributeResp;

  commandManagerSendAttribute(req);
}

/**************************************************************************//**
  \brief ZoneStatusChangeNotificationCommandInd
  \param[in] addressing - pointer to addressing information
  \param[in] payloadLength - payloadlength
  \param[in] payload - ChangeNotification payload
  \return status of indication routine
******************************************************************************/
static ZCL_Status_t ZoneStatusChangeNotificationCommandInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ZoneStatusChangeNot_t *payload)
{
  //Expected to Send the Changed Command to the Device , but what happens for the Periodic report and CIE do not maintain attributes to check for the change.
  //For now the locally maintained zonestatus within the zonetable is used for the same
  if(zoneTables[payload->zoneId].zoneStatus != payload->zoneStatus)
  {
    zoneTables[payload->zoneId].zoneStatus = payload->zoneStatus;
    aceZoneStatusChangedCommand(ADRESS_MODE, addressing->addr.shortAddress, addressing->endpointId, payload->zoneId, payload->zoneStatus, DEFAULT_SOUND, DEFAULT_VAL);
  }
#if APP_ENABLE_CONSOLE == 1  
  LOG_STRING(writeAttrSuccessStr, " <-Zone Status Change Notification Received\r\n");
  appSnprintf(writeAttrSuccessStr); 
#endif
  (void) payloadLength;  
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
  \brief ZoneTableEntry
  \param[in] response - Zone enroll resp;
  \param[in] payload - Zone enroll req;
  \param[in] addressing   - address details;
  \return none
******************************************************************************/
static void ZoneTableEntry(ZCL_ZoneEnrollResCommand_t *response, ZCL_ZoneEnrollRequest_t *payload, ZCL_Addressing_t *addressing)
{
  static uint8_t zoneSet = DEFAULT_VAL;
  response->enrollResponseCode = ENROLL_RESP_TOO_MANY_ZONES;

  for(uint8_t zoneEntry= DEFAULT_VAL;zoneEntry < ZONE_TABLE_ENTRIES;zoneEntry++)
  {
    if(!zoneSet && (zoneTables[zoneEntry].zoneAddress == addressing->addr.extAddress))
    {
      response->enrollResponseCode = ENROLL_RESP_SUCCESS;
      response->zoneId = zoneTables[zoneEntry].zoneId;
      zoneSet = 1;
    }
    if(!zoneSet && (zoneTables[zoneEntry].zoneId == 0xFF))
    {
      zoneTables[zoneEntry].zoneId = Zone_table_entries;
      zoneTables[zoneEntry].zoneType=payload->zoneType;
      zoneTables[zoneEntry].zoneAddress=addressing->addr.extAddress;
      response->enrollResponseCode = ENROLL_RESP_SUCCESS;
      response->zoneId = Zone_table_entries++;
      zoneSet = 1;
    }
  }
  zoneSet = 0;
}

/**************************************************************************//**
  \brief ZoneEnrollRequestCommandInd
  \param[in] addressing - pointer to addressing information;
  \param[in] payload - Zone enroll req payload;
  \param[in] request - Zone enroll request;
  \return status of indication routine
******************************************************************************/
ZCL_Status_t ZoneEnrollRequestCommandInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ZoneEnrollRequest_t *payload)
{
  ZCL_Request_t *req;

  if (!(req = getFreeCommand()))
    return ZCL_INSUFFICIENT_SPACE_STATUS;
  
  fillCommandRequest(req, ZCL_IAS_ZONE_CLUSTER_ZONE_ENROLL_RESPONSE_COMMAND_ID, sizeof(ZCL_ZoneEnrollResCommand_t));
  ZoneTableEntry((ZCL_ZoneEnrollResCommand_t *)req->requestPayload, payload ,addressing);
  fillDstAddressingViaSourceAddressing(&req->dstAddressing, addressing, ZCL_CLUSTER_SIDE_SERVER);
  commandManagerSendCommand(req);
  (void) payloadLength; 
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
  \brief ZoneInitiateNormalOperatingModeCommand
  \param[in] mode   - address mode;
  \param[in] addr   - short address of destination node;
  \param[in] ep     - destination endpoint;
  \return none
******************************************************************************/  
void ZoneInitiateNormalOperatingModeCommand(APS_AddrMode_t mode,ShortAddr_t addr, Endpoint_t ep)
{
  ZCL_Request_t *req;

  if (!(req = getFreeCommand()))
    return;
  
  fillCommandRequest(req, ZCL_IAS_ZONE_CLUSTER_ZONE_NORMAL_OPERATIONG_MODE, 0);
  fillDstAddressing(&req->dstAddressing, mode, addr, ep, IAS_ZONE_CLUSTER_ID);
  commandManagerSendCommand(req);
}

/**************************************************************************//**
  \brief ZoneInitiateTestModeCommand
  \param[in] mode   - address mode;
  \param[in] addr   - short address of destination node;
  \param[in] ep     - destination endpoint;
  \param[in] testmode_duration     - test mode duration;
  \param[in] testmode_duration     - test mode duration;
  \return none
******************************************************************************/
void ZoneInitiateTestModeCommand(APS_AddrMode_t mode,ShortAddr_t addr, Endpoint_t ep, uint8_t testmodeDuration, uint8_t currentZoneSensitivityLevel)
{
  ZCL_Request_t *req;
  ZCL_ZoneInitiateTestMode_t reqpayload;
  //ZCL_ZoneEnrollResCommand_t response;

  if (!(req = getFreeCommand()))
    return;
  
  //Test Mode dutaion - typically it should be greater than zero
  if(testmodeDuration > 0)
  {
    reqpayload.testmodeDuration = testmodeDuration;
  }
  else
  {
    reqpayload.testmodeDuration = TEST_MODE_DURATION;
  }
  //CurrentZoneSensitivit level to be modified in Zone Server
  reqpayload.currentZoneSensitivityLevel = currentZoneSensitivityLevel;
  
  fillCommandRequest(req, ZCL_IAS_ZONE_CLUSTER_ZONE_TEST_MODE, sizeof(ZCL_ZoneInitiateTestMode_t));
  memcpy((ZCL_ZoneInitiateTestMode_t *)req->requestPayload, &reqpayload , sizeof(ZCL_ZoneInitiateTestMode_t));
  fillDstAddressing(&req->dstAddressing, mode, addr, ep, IAS_ZONE_CLUSTER_ID);
  commandManagerSendCommand(req);
}
/**************************************************************************//**
\brief Indication of read attribute response

\param[in] resp - pointer to response
******************************************************************************/
static void ZCL_ReadAttributeResp(ZCL_Notify_t *ntfy)
{
  ZCL_NextElement_t element;
  ZCL_ReadAttributeResp_t *readAttributeResp;

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
#if APP_ENABLE_CONSOLE == 1
    LOG_STRING(readAttrSuccessStr, " <-Read IasZone attribute (0x%x) response: success value = %u\r\n");
    appSnprintf(readAttrSuccessStr, (unsigned)readAttributeResp->id, *((uint8_t*)&readAttributeResp->value[0]));
#endif
  }
  else
  {
#if APP_ENABLE_CONSOLE == 1
    LOG_STRING(readAttrFailStr, " +Read IasZone attribute failed: status = 0x%2x\r\n");
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
    LOG_STRING(writeAttrSuccessStr, " <-Write IasZone attribute response: success\r\n");
    appSnprintf(writeAttrSuccessStr);
#endif
  }
  else
  {
#if APP_ENABLE_CONSOLE == 1
    LOG_STRING(writeAttrFailStrTwo, " +Write IasZone attribute response failed: status value = 0x%x\r\n");
    appSnprintf(writeAttrFailStrTwo, (unsigned)ntfy->status);
#endif
  }
}
#endif // APP_DEVICE_TYPE_COMBINED_INTERFACE
// eof ciIasZoneCluster.c
