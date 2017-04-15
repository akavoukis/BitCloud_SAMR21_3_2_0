/**************************************************************************//**
  \file ciAlarmsCluster.c

  \brief
    Combined Interface Alarms cluster implementation.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2013, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    20.10.14 Agasthian - Created.
******************************************************************************/
#ifdef APP_DEVICE_TYPE_COMBINED_INTERFACE

/******************************************************************************
                    Includes section
******************************************************************************/
#include <ciAlarmsCluster.h>
#include <haClusters.h>
#include <commandManager.h>
#include <uartManager.h>
#include <pdsDataServer.h>
#include <zclDevice.h>
#include <sysQueue.h>

/******************************************************************************
                    Local variables section
******************************************************************************/
static AttibuteReadCallback_t   readAttributeCallback;
static AttributeWriteCallback_t writeAttributeCallback;

/******************************************************************************
                    Prototypes section
******************************************************************************/
static ZCL_Status_t alarmInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_Alarm_t *payload);
static ZCL_Status_t getAlarmResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_getAlarmResponse_t *payload);
static void ZCL_ReadAttributeResp(ZCL_Notify_t *ntfy);
static void ZCL_WriteAttributeResp(ZCL_Notify_t *ntfy);

/******************************************************************************
                    Global variables section
******************************************************************************/
ZCL_AlarmsClusterClientCommands_t   ciAlarmsCommands =
{
  ZCL_DEFINE_ALARMS_CLUSTER_CLIENT_COMMANDS(alarmInd, getAlarmResponseInd)
};

/******************************************************************************
                    Implementation section
******************************************************************************/
/**************************************************************************//**
\brief Callback on receiving alarm command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
static ZCL_Status_t alarmInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_Alarm_t *payload)
{
#if (APP_ENABLE_CONSOLE == 1)
  LOG_STRING(alarmIndStr, "<-Alarms clusterId = 0x%x alarmCode = %d\r\n");
  appSnprintf(alarmIndStr, payload->clusterIdentifier, payload->alarmCode);
#else
  (void)payload;
#endif
  (void)addressing, (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receiving getAlarmResponse command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
static ZCL_Status_t getAlarmResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_getAlarmResponse_t *payload)
{
  if ( BC_SUCCESS == payload->status)
  {
    LOG_STRING(getAlarmResponseStr1, "<-GetAlarmResponse status = 0x%x clusterId = 0x%x alarmCode = %d\r\n");
    appSnprintf(getAlarmResponseStr1, payload->status, payload->clusterIdentifier, payload->alarmCode);
  }
  else
  {
    LOG_STRING(getAlarmResponseStr2, "<-GetAlarmResponse failed status = 0x%x\r\n");
    appSnprintf(getAlarmResponseStr2, payload->status);    
  }

  (void)addressing, (void)payload, (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Sends Reset alarm command unicastly

\param[in] mode - address mode;
\param[in] addr - short address of destination node;
\param[in] ep   - destination endpoint;
\param[in] alarmCode - alarm code to be reset;
\param[in] clsuetrId   - cluster identifier;
******************************************************************************/
void alarmsSendResetAlarm(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep, ClusterId_t clusterId, uint8_t alarmCode)
{
  ZCL_Request_t *req;
  ZCL_ResetAlarm_t *resetAlarm;

  if (!(req = getFreeCommand()))
    return;

  fillCommandRequest(req, ZCL_ALARMS_CLUSTER_SERVER_RESET_ALARM_COMMAND_ID, sizeof(ZCL_ResetAlarm_t));
  resetAlarm = (ZCL_ResetAlarm_t *)req->requestPayload;
  resetAlarm->alarmCode = alarmCode;
  resetAlarm->clusterIdentifier = clusterId;
  fillDstAddressing(&req->dstAddressing, mode, addr, ep, ALARMS_CLUSTER_ID);
  commandManagerSendCommand(req);
}

/**************************************************************************//**
\brief Sends Reset all alarms command unicastly

\param[in] mode - address mode;
\param[in] addr - short address of destination node;
\param[in] ep   - destination endpoint;
******************************************************************************/
void alarmsSendResetAllAlarms(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep)
{
  ZCL_Request_t *req;

  if (!(req = getFreeCommand()))
    return;

  fillCommandRequest(req, ZCL_ALARMS_CLUSTER_SERVER_RESET_ALL_ALARMS_COMMAND_ID, 0);
  fillDstAddressing(&req->dstAddressing, mode, addr, ep, ALARMS_CLUSTER_ID);
  commandManagerSendCommand(req);
}

/**************************************************************************//**
\brief Sends Get Alarm command unicastly

\param[in] mode - address mode;
\param[in] addr - short address of destination node;
\param[in] ep   - destination endpoint;
******************************************************************************/
void alarmsSendGetAlarm(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep)
{
  ZCL_Request_t *req;

  if (!(req = getFreeCommand()))
    return;

  fillCommandRequest(req, ZCL_ALARMS_CLUSTER_SERVER_GET_ALARM_COMMAND_ID, 0);
  fillDstAddressing(&req->dstAddressing, mode, addr, ep, ALARMS_CLUSTER_ID);
  commandManagerSendCommand(req);
}

/**************************************************************************//**
\brief Sends ResetAlarmLog unicastly

\param[in] mode - address mode;
\param[in] addr - short address of destination node;
\param[in] ep   - destination endpoint;
******************************************************************************/
void alarmsSendResetAlarmLog(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep)
{
  ZCL_Request_t *req;

  if (!(req = getFreeCommand()))
    return;

  fillCommandRequest(req, ZCL_ALARMS_CLUSTER_SERVER_RESET_ALARM_LOG_COMMAND_ID, 0);
  fillDstAddressing(&req->dstAddressing, mode, addr, ep, ALARMS_CLUSTER_ID);
  commandManagerSendCommand(req);
}

/**************************************************************************//**
\brief Sends Read Attribute command unicastly

\param[in] mode - address mode;
\param[in] addr - short address of destination node;
\param[in] ep   - destination endpoint;
\param[in] attr - attribute id;
\param[in] cb   - callback function
******************************************************************************/
void alarmsReadAttribute(APS_AddrMode_t mode,ShortAddr_t addr, Endpoint_t ep,
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
  fillDstAddressing(&req->dstAddressing, mode, addr, ep, ALARMS_CLUSTER_ID);
  req->ZCL_Notify = ZCL_ReadAttributeResp;

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

    LOG_STRING(readAttrSuccessStr, "<-Read Alarm attribute (0x%x) response: success value = %d\r\n");
    appSnprintf(readAttrSuccessStr, (unsigned)readAttributeResp->id, ((uint16_t)readAttributeResp->value[0] | (readAttributeResp->value[1] << 8)));
  }
  else
  {
    LOG_STRING(readAttrFailStr, "+Read Alarm attribute failed: status = 0x%x\r\n");
    appSnprintf(readAttrFailStr, (unsigned)ntfy->status);
  }
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
void alarmsWriteAttribute(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep,
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
  fillDstAddressing(&req->dstAddressing, mode, addr, ep, ALARMS_CLUSTER_ID);
  req->ZCL_Notify = ZCL_WriteAttributeResp;

  commandManagerSendAttribute(req);
}
/**************************************************************************//**
\brief Indication of write attribute response

\param[in] resp - pointer to response
******************************************************************************/
static void ZCL_WriteAttributeResp(ZCL_Notify_t *ntfy)
{
  if (ZCL_SUCCESS_STATUS == ntfy->status)
  {
    if (writeAttributeCallback)
      writeAttributeCallback();

    LOG_STRING(writeAttrSuccessStr, " <-Write Alarms attribute response: success\r\n");
    appSnprintf(writeAttrSuccessStr);
  }
  else
  {
    LOG_STRING(writeAttrFailStrTwo, " +Write Alarms attribute failed: status = 0x%x\r\n");
    appSnprintf(writeAttrFailStrTwo, (unsigned)ntfy->status);
  }
}
#endif // APP_DEVICE_TYPE_COMBINED_INTERFACE

// eof ciAlarmCluster.c

