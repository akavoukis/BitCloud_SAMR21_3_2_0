/**************************************************************************//**
  \file iasZoneCluster.c

  \brief
    IAS-Zone Cluster implementation.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    18/11/14 Yogesh Bellan - Created.
******************************************************************************/
#if defined APP_DEVICE_TYPE_IAS_ACE

/******************************************************************************
                    Includes section
******************************************************************************/
#include <iasACEZoneCluster.h>
#if APP_ENABLE_CONSOLE == 1
#include <uartManager.h>
#endif
#include <iasACEBasicCluster.h>
#include <iasACEIdentifyCluster.h>
#include <iasACECluster.h>
#include <zclIasZoneCluster.h>
#include <zclIasACECluster.h>
#include <zclBasicCluster.h>
#include <zclIdentifyCluster.h>
#include <haClusters.h>
#include <commandManager.h>

/*******************************************************************************
                             Types section
*******************************************************************************/
typedef struct PACK
{
  uint16_t zoneStatus;
  uint8_t  extendedStatus;
} zoneStatusChangeNot_t;

typedef struct PACK
{
  uint16_t zoneType;
  uint16_t manufacturerCode;
} zoneEnrollReq_t;


/******************************************************************************
                    Prototypes section
******************************************************************************/
static ZCL_Status_t zoneEnrollResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength,ZCL_ZoneEnrollResCommand_t * payload);
static void iasZoneFillZoneZoneEnrollRequest(ZCL_ZoneEnrollRequest_t *payload, uint16_t zoneType, uint16_t manufCode);
static void zoneStatusChangeNotificationCommandCallback();
static void iasACEAttrEventInd(ZCL_Addressing_t *addressing, ZCL_AttributeId_t attributeId, ZCL_AttributeEvent_t event);
static ZCL_Status_t zoneInitiateNormalOperatingModeInd(ZCL_Addressing_t *addressing);
static ZCL_Status_t zoneInitiateTestModeInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ZoneInitiateTestMode_t * payload);
static void zoneChangeNotiCmdTimerFired(void);
static void zoneTestModeOperationTimerFired(void);
static uint8_t currentZoneSensitivityLevelValue = DEFAULT_VAL;
/******************************************************************************
                    Global variables
******************************************************************************/
static HAL_AppTimer_t zoneChangeNotiCmdTimer;
static HAL_AppTimer_t zoneTestModeOperationTimer;

//IAS Zone Server Attributes
ZCL_IasZoneClusterAttributes_t iasACEZoneClusterServerAttributes =
{
  ZCL_DEFINE_IAS_ZONE_CLUSTER_SERVER_ATTRIBUTES()
};

//IAS Zone Server Commands
ZCL_IasZoneClusterCommands_t iasACEZoneClusterServerCommands =
{
  ZCL_DEFINE_IAS_ZONE_CLUSTER_COMMANDS(NULL, NULL, zoneEnrollResponseInd, zoneInitiateNormalOperatingModeInd, zoneInitiateTestModeInd)
};


/******************************************************************************
                    Implementation section
******************************************************************************/
/**************************************************************************//**
 \brief iasZoneClusterInit
 \param none
 \return none
******************************************************************************/
void iasZoneClusterInit(void)
{
  ZCL_Cluster_t *cluster = ZCL_GetCluster(APP_SRC_ENDPOINT_ID, IAS_ZONE_CLUSTER_ID, ZCL_CLUSTER_SIDE_SERVER);

  if (cluster)
  {
    cluster->ZCL_AttributeEventInd = iasACEAttrEventInd;
  }
  
  //Initialization of the list of attributes to their default values of IAS Zones
  iasACEZoneClusterServerAttributes.iaszoneState.value = ZCL_IAS_ZONE_CLUSTER_SERVER_ZONE_STATE_ATTRIBUTE_ID_DEFAULT;
  iasACEZoneClusterServerAttributes.iaszoneType.value = APP_IAS_ZONE_TYPE_ATTRIBUTE_VALUE;
  iasACEZoneClusterServerAttributes.iaszoneStatus.value = ZCL_IAS_ZONE_CLUSTER_SERVER_ZONE_STATUS_ATTRIBUTE_ID_DEFAULT;
  iasACEZoneClusterServerAttributes.iasCieAddress.value = APP_IAS_ZONE_CIE_ADDRESS_ATTRIBUTE_VALUE;
  iasACEZoneClusterServerAttributes.iasZoneId.value = ZCL_IAS_ZONE_CLUSTER_SERVER_ZONE_ID_ATTRIBUTE_ID_DEFAULT;
  iasACEZoneClusterServerAttributes.iasZoneNumberOfZoneSensitivityLevelsSupported.value =ZCL_IAS_ZONE_CLUSTER_SERVER_NUMBEROFZONESENSITIVITY_LEVEL_SUPP_DEFAULT;
  iasACEZoneClusterServerAttributes.iasZoneCurrentZoneSensitivityLevel.value =ZCL_IAS_ZONE_CLUSTER_SERVER_CURRENTZONESENSITIVITY_LEVEL_SUPP_DEFAULT;
  currentZoneSensitivityLevelValue = iasACEZoneClusterServerAttributes.iasZoneCurrentZoneSensitivityLevel.value;
}

/**************************************************************************//**
 \brief iasZoneFillZoneStatusChangeNotification
 \param payload - ZOne status change notification payload
 \param zoneStatus  - device /zone statu attribute value
 \param extendedStatus - extended status as part of payload
 \return none
******************************************************************************/
static void iasZoneFillZoneStatusChangeNotification(ZCL_ZoneStatusChangeNot_t *payload, uint16_t zoneStatus, uint8_t extendedStatus)
{
  payload->zoneStatus          = zoneStatus;
  payload->extendedStatus      = extendedStatus;
  payload->zoneId              = iasACEZoneClusterServerAttributes.iasZoneId.value;
  payload->delayTime           = ZONE_NOTI_PERIOD; 
}

/**************************************************************************//**
 \brief iasZoneFillZoneStatusChangeNotification Callback
 \param payload - ZOne status change notification payload
 \return none
******************************************************************************/
static void iasZoneFillZoneStatusChangeNotificationCallback(ZCL_ZoneStatusChangeNot_t *payload)
{
  payload->zoneStatus          = iasACEZoneClusterServerAttributes.iaszoneStatus.value;
  payload->extendedStatus      = EXTENDED_STATE_DEFAULT;
  payload->zoneId              = iasACEZoneClusterServerAttributes.iasZoneId.value;
  payload->delayTime           = ZONE_NOTI_PERIOD; 
}

/**************************************************************************//**
 \brief iasZoneFillZoneZoneEnrollRequest
 \param payload - Enroll request payload to be filled
 \param zoneType  - type of the zone
 \param manufCode - manufacturer code
 \return none
******************************************************************************/
static void iasZoneFillZoneZoneEnrollRequest(ZCL_ZoneEnrollRequest_t *payload, uint16_t zoneType, uint16_t manufCode)
{
  payload->zoneType          = zoneType;
  payload->manufacturerCode  = manufCode;
}

/**************************************************************************//**
 \brief zoneStatusChangeNotification Command
 \param mode - Adress Mode
 \param addr - short addr
 \param ep  -  Endpoint of the device
 \param zoneStatus - status of the zone
 \param extendedStatus - extended status of the zone
 \return none
******************************************************************************/
void zoneStatusChangeNotificationCommand(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep,uint16_t zoneStatus, uint8_t extendedStatus)
{
  ZCL_Request_t *req;

  if (!(req = getFreeCommand()))
    return;

  fillCommandRequest(req, ZCL_IAS_ZONE_CLUSTER_ZONE_STATUS_CHANGE_NOTIFY_COMMAND_ID, sizeof(ZCL_ZoneStatusChangeNot_t));
  iasZoneFillZoneStatusChangeNotification((ZCL_ZoneStatusChangeNot_t *)req->requestPayload,zoneStatus,extendedStatus);
  fillDstAddressingServer(&req->dstAddressing, mode, addr, ep, IAS_ZONE_CLUSTER_ID);
  commandManagerSendCommand(req);
}

/**************************************************************************//**
 \brief zoneStatusChangeNotification Command
 \return none
******************************************************************************/
void zoneStatusChangeNotificationCommandCallback()
{
  ZCL_Request_t *req;

  if (!(req = getFreeCommand()))
    return;

  fillCommandRequest(req, ZCL_IAS_ZONE_CLUSTER_ZONE_STATUS_CHANGE_NOTIFY_COMMAND_ID, sizeof(ZCL_ZoneStatusChangeNot_t));
  iasZoneFillZoneStatusChangeNotificationCallback((ZCL_ZoneStatusChangeNot_t *)req->requestPayload);
  fillDstAddressingServer(&req->dstAddressing, ADRESS_MODE, CIE_ADDR, CIE_ENDPT, IAS_ZONE_CLUSTER_ID);
  commandManagerSendCommand(req);
}

/**************************************************************************//**
 \brief zoneEnrollRequest Command
 \param mode - Adress Mode
 \param addr - short addr
 \param ep  -  Endpoint of the device
 \param zoneType -  type of the zone
 \param manufCode  -  manufacturer code
 \return none
******************************************************************************/
void zoneEnrollRequestCommand(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep, uint16_t zoneType, uint16_t manufCode)
{
  ZCL_Request_t *req;

  if (!(req = getFreeCommand()))
    return;

  fillCommandRequest(req, ZCL_IAS_ZONE_CLUSTER_ZONE_ENROLL_REQUEST_COMMAND_ID, sizeof(ZCL_ZoneEnrollRequest_t));
  iasZoneFillZoneZoneEnrollRequest((ZCL_ZoneEnrollRequest_t *)req->requestPayload,zoneType, manufCode);
  fillDstAddressingServer(&req->dstAddressing, mode, addr, ep, IAS_ZONE_CLUSTER_ID);
  commandManagerSendCommand(req);
}

/**************************************************************************//**
 \brief Initiating ZoneEnrollRequest Command
 \param shortAddress - short address
 \return none
******************************************************************************/
void sendZoneEnrollRequestCommand(uint16_t shortAddress)
{
  zoneEnrollRequestCommand(ADRESS_MODE, shortAddress, CIE_ENDPT, iasACEZoneClusterServerAttributes.iaszoneType.value, 0x0000 );
}

/**************************************************************************//**
 \brief ZoneEnrollResponseInd Command
 \param addressing - source info
 \param reportLength  - length of data in reportPayload
 \param payload - payload data
 \return none
******************************************************************************/
static ZCL_Status_t zoneEnrollResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength,ZCL_ZoneEnrollResCommand_t * payload)
{
  switch(payload->enrollResponseCode)
  {
    case ENROLL_RESP_SUCCESS:
#if APP_ENABLE_CONSOLE != 1
      iasACEZoneClusterServerAttributes.iaszoneStatus.value = SUPERVISION_REPORT_STATE;
      iasACEZoneClusterServerAttributes.iaszoneType.value = ZCL_IAS_ZONE_CLUSTER_ZONE_TYPE_ATTRIBUTE_MOTION_SENSOR;
#endif
      iasACEZoneClusterServerAttributes.iaszoneState.value = ZCL_IAS_ZONE_CLUSTER_ZONE_STATE_ATTRIBUTE_ENROLLED;
      iasACEZoneClusterServerAttributes.iasZoneId.value = payload->zoneId;
      iasACEZoneClusterServerAttributes.iasCieAddress.value = addressing->addr.extAddress;
      if((iasACEZoneClusterServerAttributes.iaszoneStatus.value) && ( 1<< ZCL_IAS_ZONE_CLUSTER_ZONE_STATUS_ATTRIBUTE_SUPERVISION_REPORTS))
      {
        zoneChangeNotiCmdTimer.interval = ZONE_NOTI_PERIOD;
        zoneChangeNotiCmdTimer.mode     = TIMER_REPEAT_MODE;
        zoneChangeNotiCmdTimer.callback = zoneChangeNotiCmdTimerFired;
        HAL_StartAppTimer(&zoneChangeNotiCmdTimer);
      }
      break;
    case ENROLL_RESP_NOT_SUPPORTED:
    case ENROLL_RESP_NOT_ENROLL_PERMIT:
    case ENROLL_RESP_TOO_MANY_ZONES:
      break;
    default:
      break;
   }
#if APP_ENABLE_CONSOLE == 1
  LOG_STRING(writeAttrSuccessStr, " <-ZoneEnrollResponseInd Command : Status = %u\r\n");
  appSnprintf(writeAttrSuccessStr, (unsigned)payload->enrollResponseCode);
#endif
  (void) payloadLength;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
 \brief ZoneInitiateNormalOperatingModeInd Command
 \param addressing - source info
 \return none
******************************************************************************/
static ZCL_Status_t zoneInitiateNormalOperatingModeInd(ZCL_Addressing_t *addressing)
{
  //To retain the default value of CurrentZoneSensitivitylevel
  iasACEZoneClusterServerAttributes.iasZoneCurrentZoneSensitivityLevel.value =ZCL_IAS_ZONE_CLUSTER_SERVER_CURRENTZONESENSITIVITY_LEVEL_SUPP_DEFAULT;

  //To bring it back to the normal mode of the zone status value
  iasACEZoneClusterServerAttributes.iaszoneStatus.value &= ZCL_IAS_ZONE_CLUSTER_ZONE_STATUS_ATTRIBUTE_TEST_MODE_TO_OPERATION_MODE;

  //To bring it back to the normal mode of the zone status value
  iasACEZoneClusterServerAttributes.iasZoneCurrentZoneSensitivityLevel.value = currentZoneSensitivityLevelValue;

  //Stop the timer, if already initiated by the normal mode operation
  HAL_StopAppTimer(&zoneTestModeOperationTimer);

  //Send notification to the IAS Zone Client
  zoneStatusChangeNotificationCommandCallback();
  (void) addressing;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
 \brief ZoneInitiateTestModeInd Command
 \param addressing - source info
 \param payloadLength  - length of data in reportPayload
 \param payload - payload data
 \return none
******************************************************************************/
static ZCL_Status_t zoneInitiateTestModeInd(ZCL_Addressing_t *addressing, uint8_t payloadLength,ZCL_ZoneInitiateTestMode_t * payload)
{
  //To retain the default value of CurrentZoneSensitivitylevel
  iasACEZoneClusterServerAttributes.iasZoneCurrentZoneSensitivityLevel.value = payload->currentZoneSensitivityLevel;

  //To bring it back to the normal mode of the zone status value
  iasACEZoneClusterServerAttributes.iaszoneStatus.value |= (1<< ZCL_IAS_ZONE_CLUSTER_ZONE_STATUS_ATTRIBUTE_TEST_MODE);

  //To bring it back to the normal mode of the zone status value
  currentZoneSensitivityLevelValue = iasACEZoneClusterServerAttributes.iasZoneCurrentZoneSensitivityLevel.value;
  iasACEZoneClusterServerAttributes.iasZoneCurrentZoneSensitivityLevel.value = payload->currentZoneSensitivityLevel;

  //Timer to be in the test mode emulation for the Server  
  zoneTestModeOperationTimer.interval = (payload->testmodeDuration) * TIME_IN_SECONDS;
  zoneTestModeOperationTimer.mode     = TIMER_ONE_SHOT_MODE;
  zoneTestModeOperationTimer.callback = zoneTestModeOperationTimerFired;
  HAL_StartAppTimer(&zoneTestModeOperationTimer);

  //Send notification to the IAS Zone Client
  zoneStatusChangeNotificationCommandCallback();
  (void) payloadLength;
  (void) addressing;
  return ZCL_SUCCESS_STATUS;
}

/***************************************************************************//**
 \brief zoneTestModeOperationTimerFired
*******************************************************************************/
static void zoneTestModeOperationTimerFired(void)
{
  //Stop the timer
  HAL_StopAppTimer(&zoneTestModeOperationTimer);

  //Update the Test Bit to Zero
  iasACEZoneClusterServerAttributes.iaszoneStatus.value &= ZCL_IAS_ZONE_CLUSTER_ZONE_STATUS_ATTRIBUTE_TEST_MODE_TO_OPERATION_MODE;

  //Update the CurrentZone Sensitivity level to the default value
  iasACEZoneClusterServerAttributes.iasZoneCurrentZoneSensitivityLevel.value = currentZoneSensitivityLevelValue;

  //Send notification to the client and resume normal mode operation
  zoneStatusChangeNotificationCommandCallback();
}

/***************************************************************************//**
 \brief zoneChangeNotiCmdTimerFired
*******************************************************************************/
static void zoneChangeNotiCmdTimerFired(void)
{
  HAL_StopAppTimer(&zoneChangeNotiCmdTimer);
  
  //To check whether we need periodic reports or not
  if((iasACEZoneClusterServerAttributes.iaszoneStatus.value) & ( 1<< ZCL_IAS_ZONE_CLUSTER_ZONE_STATUS_ATTRIBUTE_SUPERVISION_REPORTS))
  {
    HAL_StartAppTimer(&zoneChangeNotiCmdTimer);
  }
  //Callback for the Zone notification
  zoneStatusChangeNotificationCommandCallback();
}

/**************************************************************************//**
 \brief Attribute Event indication handler(to indicate when attr values have
        read or written)
 \param[in] addressing - pointer to addressing information;
 \param[in] attributeId - Id of the attribute;
 \param[in] event - event details
 \return none
******************************************************************************/
static void iasACEAttrEventInd(ZCL_Addressing_t *addressing, ZCL_AttributeId_t attributeId, ZCL_AttributeEvent_t event)
{
  //To take action for Current Zone Sensitivity level attribute
  if ( (attributeId == ZCL_IAS_ZONE_CLUSTER_SERVER_CURRENTZONESENSITIVITY_LEVEL_SUPP_ID)
           && (event == ZCL_WRITE_ATTRIBUTE_EVENT) )
  {
    if(!(iasACEZoneClusterServerAttributes.iaszoneStatus.value & ~(1<< ZCL_IAS_ZONE_CLUSTER_ZONE_STATUS_ATTRIBUTE_TEST_MODE)))
    {
      currentZoneSensitivityLevelValue = iasACEZoneClusterServerAttributes.iasZoneCurrentZoneSensitivityLevel.value;
    }
  }

  //To take action for number of Zone Sensitivity level supported attribute
  if ( (attributeId == ZCL_IAS_ZONE_CLUSTER_SERVER_NUMBEROFZONESENSITIVITY_LEVEL_SUPP_ID)
           && (event == ZCL_WRITE_ATTRIBUTE_EVENT) )
  {
    if(iasACEZoneClusterServerAttributes.iasZoneCurrentZoneSensitivityLevel.value <2)
    {
      iasACEZoneClusterServerAttributes.iasZoneCurrentZoneSensitivityLevel.value = ZCL_IAS_ZONE_CLUSTER_SERVER_CURRENTZONESENSITIVITY_LEVEL_SUPP_DEFAULT;
    }
  }
  (void) addressing;
}

/***************************************************************************//**
 \brief zoneChange change to send out the notification to CIE
 \param[in] addressing - pointer to addressing information;
 \return none
*******************************************************************************/
void zoneStatusChangeCommand(uint16_t zoneStatusChangeValue)
{
  if(zoneStatusChangeValue <= ZONE_MAXIMUM_LIMIT_VALUE)
  {
    iasACEZoneClusterServerAttributes.iaszoneStatus.value = zoneStatusChangeValue;
    zoneStatusChangeNotificationCommandCallback();
    if((iasACEZoneClusterServerAttributes.iaszoneStatus.value) & ( 1<< ZCL_IAS_ZONE_CLUSTER_ZONE_STATUS_ATTRIBUTE_SUPERVISION_REPORTS))
    {
      zoneChangeNotiCmdTimer.interval = ZONE_NOTI_PERIOD;
      zoneChangeNotiCmdTimer.mode     = TIMER_ONE_SHOT_MODE;
      zoneChangeNotiCmdTimer.callback = zoneChangeNotiCmdTimerFired;
      HAL_StartAppTimer(&zoneChangeNotiCmdTimer);
    }
  }
}
#endif // APP_DEVICE_TYPE_IAS_ACE
// eof iasZoneCluster.c
