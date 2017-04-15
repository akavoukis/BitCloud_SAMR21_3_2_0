/**************************************************************************//**
  \file thAlarmCluster.c

  \brief
    Thermostat Alarm cluster implementation.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    20/10/2014 Agasthian - Created.
******************************************************************************/
#ifdef APP_DEVICE_TYPE_THERMOSTAT

/******************************************************************************
                    Includes section
******************************************************************************/
#include <thAlarmsCluster.h>
#include <haClusters.h>
#include <uartManager.h>
#include <commandManager.h>
#include <pdsDataServer.h>
#include <zclDevice.h>

/******************************************************************************
                    Definition(s) section
******************************************************************************/
#define ALARM_TABLE_SIZE 4u

/******************************************************************************
                    Prototypes section
******************************************************************************/
static ZCL_Status_t resetAlarmInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ResetAlarm_t *payload);
static ZCL_Status_t resetAllAlarmsInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload);
static ZCL_Status_t getAlarmInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload);
static ZCL_Status_t resetAlarmLogInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload);
static void addAlarmEntry(uint8_t alarmCode, ClusterId_t clusterId);
static void removeAlarmEntry();
static void alarmNotificationResp(ZCL_Notify_t *ntfy);

/******************************************************************************
                    Global variables section
******************************************************************************/
ZCL_AlarmsClusterServerAttributes_t thAlarmsClusterServerAttributes =
{
  ZCL_DEFINE_ALARMS_CLUSTER_SERVER_ATTRIBUTES()
};
ZCL_AlarmsClusterServerCommands_t   thAlarmsClusterServerCommands =
{
  ZCL_DEFINE_ALARMS_CLUSTER_SERVER_COMMANDS(resetAlarmInd, resetAllAlarmsInd, getAlarmInd, resetAlarmLogInd)
};

/******************************************************************************
                    Static variables section
******************************************************************************/
ZCL_AlarmEntry_t thAlarmTable[ALARM_TABLE_SIZE];

/******************************************************************************
                    Implementation section
******************************************************************************/
/**************************************************************************//**
\brief Initializes Identify cluster
******************************************************************************/
void alarmsClusterInit(void)
{
  thAlarmsClusterServerAttributes.alarmCount.value = 0;
}

/**************************************************************************//**
\brief Callback on receiving resetAllAlarm command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
static ZCL_Status_t resetAllAlarmsInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload)
{
  BcZCLActionReq_t resetAllAlarmActionReq;
  ZCL_ResetAlarmNotification_t resetAllAlarmsNotification;

  LOG_STRING(resetAllAlarmStr, "<-resetAllAlarm\r\n");
  appSnprintf(resetAllAlarmStr);

  resetAllAlarmsNotification.commandId = ZCL_ALARMS_CLUSTER_SERVER_RESET_ALL_ALARMS_COMMAND_ID;
  resetAllAlarmsNotification.clusterIdentifier = 0x00;
  resetAllAlarmsNotification.alarmCode = 0x00;

  // Raise event to the subscribers. They will reset all their alarms
  // If alarm is still active, they may initiate notification
  resetAllAlarmActionReq.action = ZCL_ACTION_RESET_ALARM_REQUEST;
  resetAllAlarmActionReq.context = (const void *)&resetAllAlarmsNotification;
  SYS_PostEvent(BC_ZCL_EVENT_ACTION_REQUEST, (SYS_EventData_t)&resetAllAlarmActionReq);


  (void)addressing, (void)payloadLength, (void)payload;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receiving resetAlarm command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
static ZCL_Status_t resetAlarmInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ResetAlarm_t *payload)
{
  BcZCLActionReq_t resetAlarmActionReq;
  ZCL_ResetAlarmNotification_t resetAlarmNotification;

  LOG_STRING(resetAlarmStr, "<-resetAlarm clusterId = 0x%x alarmCode = %d\r\n");
  appSnprintf(resetAlarmStr, payload->clusterIdentifier, payload->alarmCode);

  resetAlarmNotification.commandId = ZCL_ALARMS_CLUSTER_SERVER_RESET_ALARM_COMMAND_ID;
  resetAlarmNotification.clusterIdentifier = payload->clusterIdentifier;
  resetAlarmNotification.alarmCode = payload->alarmCode;

  // Raise event to the subscribers. They will reset the alarm
  // If alarm is still active, they may initiate notification
  resetAlarmActionReq.action = ZCL_ACTION_RESET_ALARM_REQUEST;
  resetAlarmActionReq.context = (const void *)&resetAlarmNotification;
  SYS_PostEvent(BC_ZCL_EVENT_ACTION_REQUEST, (SYS_EventData_t)&resetAlarmActionReq);

  (void)addressing, (void)payloadLength, (void)payload;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receiving getAlarm command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
static ZCL_Status_t getAlarmInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload)
{
  ZCL_Request_t *req;
  ZCL_getAlarmResponse_t *getAlarmResponse;
  uint8_t reqLength;

  LOG_STRING(resetGetAlarmStr, "<-getAlarm\r\n");
  appSnprintf(resetGetAlarmStr);

  if (addressing->nonUnicast)
    return ZCL_SUCCESS_STATUS;

  if (!(req = getFreeCommand()))
    return ZCL_INSUFFICIENT_SPACE_STATUS;

  getAlarmResponse = (ZCL_getAlarmResponse_t *)req->requestPayload;

  if (thAlarmsClusterServerAttributes.alarmCount.value)
  {
    reqLength = sizeof(ZCL_getAlarmResponse_t);
    getAlarmResponse->status = ZCL_SUCCESS_STATUS;
    getAlarmResponse->alarmCode = thAlarmTable[0].alarmCode;
    getAlarmResponse->clusterIdentifier = thAlarmTable[0].clusterIdentifier;
    getAlarmResponse->timeStamp = thAlarmTable[0].timeStamp;
    removeAlarmEntry();
  }
  else
  {
    reqLength = 1;
    getAlarmResponse->status = ZCL_NOT_FOUND_STATUS;
  }

  fillCommandRequest(req, ZCL_ALARMS_CLUSTER_CLIENT_GET_ALARM_RESPONSE_COMMAND_ID, reqLength);
  fillDstAddressingViaSourceAddressing(&req->dstAddressing, addressing, ZCL_CLUSTER_SIDE_CLIENT);
  commandManagerSendCommand(req);

  (void)addressing, (void)payloadLength, (void)payload;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receiving resetAlarmLog command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
static ZCL_Status_t resetAlarmLogInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload)
{
  LOG_STRING(resetAlarmLogStr, "<-resetAlarmLog\r\n");
  appSnprintf(resetAlarmLogStr);

  thAlarmsClusterServerAttributes.alarmCount.value = 0;

  (void)addressing, (void)payloadLength, (void)payload;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief alarm notification raised by other clusters

\param[in] alarmCode - alarm code;
\param[in] clusterId - cluster identifier;
******************************************************************************/
void alarmNotification(uint8_t alarmCode, ClusterId_t clusterId)
{
  // send alarm notification
  ZCL_Request_t *req;
  ZCL_Alarm_t *alarm;

  if (!(req = getFreeCommand()))
    return;

  alarm = (ZCL_Alarm_t *)req->requestPayload;
  alarm->alarmCode = alarmCode;
  alarm->clusterIdentifier = clusterId;
  fillCommandRequest(req, ZCL_ALARMS_CLUSTER_CLIENT_ALARM_COMMAND_ID, sizeof(ZCL_Alarm_t));
  fillDstAddressing(&req->dstAddressing, APS_NO_ADDRESS, 0x00, APP_SRC_ENDPOINT_ID, ALARMS_CLUSTER_ID);
  req->dstAddressing.clusterSide = ZCL_CLUSTER_SIDE_CLIENT;
  req->ZCL_Notify = alarmNotificationResp;
  commandManagerSendCommand(req);

  // add to table
  addAlarmEntry(alarmCode, clusterId);
}
/**************************************************************************//**
\brief Indication of alarm notification response

\param[in] ntfy - pointer to response
******************************************************************************/
static void alarmNotificationResp(ZCL_Notify_t *ntfy)
{
  (void)ntfy;
}

/**************************************************************************//**
\brief adding entry to alarm table

\param[in] alarmCode - alarm code;
\param[in] clusterId - cluster identifier;
******************************************************************************/
static void addAlarmEntry(uint8_t alarmCode, ClusterId_t clusterId)
{
  if (thAlarmsClusterServerAttributes.alarmCount.value >= ALARM_TABLE_SIZE)
    removeAlarmEntry();

  thAlarmTable[thAlarmsClusterServerAttributes.alarmCount.value].alarmCode = alarmCode;
  thAlarmTable[thAlarmsClusterServerAttributes.alarmCount.value].clusterIdentifier = clusterId;
  thAlarmTable[thAlarmsClusterServerAttributes.alarmCount.value].timeStamp = HAL_GetSystemTime() / 1000; // this needs to be linked with time cluster UTC
  thAlarmsClusterServerAttributes.alarmCount.value++;

}

/**************************************************************************//**
\brief remove the first entry(earliest timestamp)from alarm table

\param[in] alarmCode - alarm code;
\param[in] clusterId - cluster identifier;
******************************************************************************/
static void removeAlarmEntry()
{
  for (uint8_t i = 0; i < (thAlarmsClusterServerAttributes.alarmCount.value-1); i++)
    memcpy(&thAlarmTable[i], &thAlarmTable[i+1], sizeof(ZCL_AlarmEntry_t));
  thAlarmsClusterServerAttributes.alarmCount.value--;
}

#endif // APP_DEVICE_TYPE_THERMOSTAT

// eof thAlarmsCluster.c

