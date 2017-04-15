/**************************************************************************//**
  \file ciIdentifyCluster.c

  \brief
    Combined Interface Identify cluster implementation.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2013, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    04.09.13 N. Fomin - Created.
******************************************************************************/
#ifdef APP_DEVICE_TYPE_COMBINED_INTERFACE

/******************************************************************************
                    Includes section
******************************************************************************/
#include <ciIdentifyCluster.h>
#include <identifyCluster.h>
#include <haClusters.h>
#include <commandManager.h>
#include <uartManager.h>
#include <pdsDataServer.h>
#include <zclDevice.h>
#include <ezModeManager.h>
#include <sysQueue.h>

/******************************************************************************
                    Definition(s) section
******************************************************************************/
#define IDENTIFY_TIMER_PERIOD 1000u

/******************************************************************************
                    Prototypes section
******************************************************************************/
static ZCL_Status_t identifyInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_Identify_t *payload);
static ZCL_Status_t identifyQueryInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload);
static ZCL_Status_t identifyQueryResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_IdentifyQueryResponse_t *payload);
static ZCL_Status_t ezModeInvokeInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_EzModeInvoke_t *payload);
static ZCL_Status_t updateCommissioningStateInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_UpdateCommissioningState_t *payload);
static ZCL_Status_t sendIdentifyQueryResponse(ZCL_Addressing_t *addressing);
static void ZCL_ReadAttributeResp(ZCL_Notify_t *ntfy);
static void ZCL_WriteAttributeResp(ZCL_Notify_t *ntfy);
static void ciFillIdentifyQueryResponsePayload(ZCL_IdentifyQueryResponse_t *payload, uint16_t time);
static void ciFillIdentifyPayload(ZCL_Identify_t *payload, uint16_t time);
static void ciFillEzModeInvokePayload(ZCL_EzModeInvoke_t *payload, uint8_t action);
static void ciFillUpdateCommissioningStatePayload(ZCL_UpdateCommissioningState_t *payload, uint8_t action, uint8_t mask);
static void identifyTimerFired(void);
static void ZCL_IdentifyAttributeEventInd(ZCL_Addressing_t *addressing, ZCL_AttributeId_t attributeId, ZCL_AttributeEvent_t event);

/******************************************************************************
                    Global variables section
******************************************************************************/
ZCL_IdentifyClusterAttributes_t ciIdentifyClusterServerAttributes =
{
  ZCL_DEFINE_IDENTIFY_CLUSTER_SERVER_ATTRIBUTES()
};
ZCL_IdentifyClusterCommands_t ciIdentifyCommands =
{
  IDENTIFY_CLUSTER_COMMANDS(identifyInd, identifyQueryInd, identifyQueryResponseInd, ezModeInvokeInd, updateCommissioningStateInd)
};

/******************************************************************************
                    Static variables section
******************************************************************************/
static AttibuteReadCallback_t   readAttributeCallback;
static AttributeWriteCallback_t writeAttributeCallback;
static HAL_AppTimer_t identifyTimer;
static DECLARE_QUEUE(subscribers);

/******************************************************************************
                    Implementation section
******************************************************************************/
/**************************************************************************//**
\brief Initializes Identify cluster
******************************************************************************/
void identifyClusterInit(void)
{
  ciIdentifyClusterServerAttributes.identifyTime.value = 0;

  ZCL_Cluster_t *cluster = ZCL_GetCluster(APP_SRC_ENDPOINT_ID, IDENTIFY_CLUSTER_ID, ZCL_CLUSTER_SIDE_SERVER);

  if (cluster)
    cluster->ZCL_AttributeEventInd = ZCL_IdentifyAttributeEventInd;

  identifyTimer.interval = IDENTIFY_TIMER_PERIOD;
  identifyTimer.mode     = TIMER_REPEAT_MODE;
  identifyTimer.callback = identifyTimerFired;
}

/**************************************************************************//**
\brief Stops Identify cluster
******************************************************************************/
void identifyClusterStop(void)
{
  HAL_StopAppTimer(&identifyTimer);
}

/**************************************************************************//**
\brief Adds record to a list of subscribers

\param[in] subscriber - pointer to subscriber;
******************************************************************************/
void identifySubscribe(IdentifySubscriber_t *subscriber)
{
  if (!isQueueElem(&subscribers, subscriber))
    putQueueElem(&subscribers, subscriber);
}

/**************************************************************************//**
\brief Makes device to start identify itself

\param[in] time - identifying time in seconds
******************************************************************************/
void idetifyStartIdentifying(uint16_t time)
{
  ciIdentifyClusterServerAttributes.identifyTime.value = time;
  HAL_StopAppTimer(&identifyTimer);
  HAL_StartAppTimer(&identifyTimer);
}

/**************************************************************************//**
\brief Sends Identify request

\param[in] mode - address mode;
\param[in] addr - short address of destination node;
\param[in] ep   - destination endpoint;
\param[in] time - identify time
******************************************************************************/
void identifySendIdentify(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep,
  uint16_t time)
{
  ZCL_Request_t *req;

  if (!(req = getFreeCommand()))
    return;

  fillCommandRequest(req, ZCL_IDENTIFY_CLUSTER_IDENTIFY_COMMAND_ID, sizeof(ZCL_Identify_t));
  ciFillIdentifyPayload((ZCL_Identify_t *)req->requestPayload, time);
  fillDstAddressing(&req->dstAddressing, mode, addr, ep, IDENTIFY_CLUSTER_ID);
  commandManagerSendCommand(req);
}

/**************************************************************************//**
\brief Sends Identify Query request

\param[in] mode - address mode;
\param[in] addr - short address of destination node;
\param[in] ep   - destination endpoint
******************************************************************************/
void identifySendIdentifyQuery(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep)
{
  ZCL_Request_t *req;

  if (!(req = getFreeCommand()))
    return;

  fillCommandRequest(req, ZCL_IDENTIFY_CLUSTER_IDENTIFY_QUERY_COMMAND_ID, 0);
  fillDstAddressing(&req->dstAddressing, mode, addr, ep, IDENTIFY_CLUSTER_ID);
  commandManagerSendCommand(req);
}

/**************************************************************************//**
\brief Sends EZ-Mode Invoke command

\param[in] mode   - address mode;
\param[in] addr   - short address of destination node;
\param[in] ep     - destination endpoint;
\param[in] action - action to be done upon reception
******************************************************************************/
void identifySendEzModeInvoke(APS_AddrMode_t mode,ShortAddr_t addr, Endpoint_t ep,
  uint8_t action)
{
  ZCL_Request_t *req;

  if (!(req = getFreeCommand()))
    return;

  fillCommandRequest(req, ZCL_IDENTIFY_CLUSTER_EZ_MODE_INVOKE_COMMAND_ID, sizeof(ZCL_EzModeInvoke_t));
  ciFillEzModeInvokePayload((ZCL_EzModeInvoke_t *)req->requestPayload, action);
  fillDstAddressing(&req->dstAddressing, mode, addr, ep, IDENTIFY_CLUSTER_ID);
  commandManagerSendCommand(req);
}

/**************************************************************************//**
\brief Sends Update Commissioning State command

\param[in] mode   - address mode;
\param[in] addr   - short address of destination node;
\param[in] ep     - destination endpoint;
\param[in] action - action to be done upon reception;
\param[in] mask   - commissiong state mask
******************************************************************************/
void identifySendUpdateCommissioningState(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep,
  ZCL_UpdateCommissioningStateAction_t action, uint8_t mask)
{
  ZCL_Request_t *req;

  if (!(req = getFreeCommand()))
    return;

  fillCommandRequest(req, ZCL_IDENTIFY_CLUSTER_UPDATE_COMMISSIONING_STATE_COMMAND_ID, sizeof(ZCL_UpdateCommissioningState_t));
  ciFillUpdateCommissioningStatePayload((ZCL_UpdateCommissioningState_t *)req->requestPayload, action, mask);
  fillDstAddressing(&req->dstAddressing, mode, addr, ep, IDENTIFY_CLUSTER_ID);
  commandManagerSendCommand(req);
}

/**************************************************************************//**
\brief Updates value of commissioniong state attribute

\param[in] nwkState        - new netwrok state;
\param[in] operationalState - new operational state
******************************************************************************/
void identifyUpdateCommissioningState(bool nwkState, bool operationalState)
{
  ciIdentifyClusterServerAttributes.commissioningState.value.networkState     = nwkState;
  ciIdentifyClusterServerAttributes.commissioningState.value.operationalState = operationalState;
}

/**************************************************************************//**
\brief Callback on receiving Identify command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
static ZCL_Status_t identifyInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_Identify_t *payload)
{
  LOG_STRING(identifyStr, "->Identify\r\n");
  appSnprintf(identifyStr);

  ciIdentifyClusterServerAttributes.identifyTime.value = payload->identifyTime;

  HAL_StopAppTimer(&identifyTimer);

  if (payload->identifyTime)
    HAL_StartAppTimer(&identifyTimer);

  RAISE_CALLBACKS_TO_IDENTIFY_SUBSCIBERS(subscribers, identify);

  (void)addressing, (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receiving Identify Query command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
static ZCL_Status_t identifyQueryInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload)
{
  LOG_STRING(identifyQueryStr, "->Identify Query\r\n");
  appSnprintf(identifyQueryStr);

  if (ciIdentifyClusterServerAttributes.identifyTime.value)
    return sendIdentifyQueryResponse(addressing);

  RAISE_CALLBACKS_TO_IDENTIFY_SUBSCIBERS(subscribers, identifyQuery);

  (void)payload, (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receiving Identify Query Response command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
static ZCL_Status_t identifyQueryResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_IdentifyQueryResponse_t *payload)
{
  LOG_STRING(identifyStr, "->Identify Query Response, addr = %d, timeout = 0x%04x\r\n");
  appSnprintf(identifyStr, addressing->addr.shortAddress, payload->timeout);

  RAISE_CALLBACKS_TO_IDENTIFY_SUBSCIBERS(subscribers, identifyQueryResponse);

  (void)addressing, (void)payloadLength, (void)payload;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receiving EZ-Mode invoke command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
static ZCL_Status_t ezModeInvokeInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_EzModeInvoke_t *payload)
{
  LOG_STRING(identifyStr, "->EZ-Mode Invoke\r\n");
  appSnprintf(identifyStr);
#ifndef ZAPPSI_HOST
  if (payload->factoryFresh)
    PDS_DeleteAll(false);
#endif
  if (payload->networkSteering)
  {
    appRestart(payload->findingAndBinding);
    return ZCL_SUCCESS_STATUS;
  }
  if (payload->findingAndBinding)
    invokeEzMode(NULL);

  RAISE_CALLBACKS_TO_IDENTIFY_SUBSCIBERS(subscribers, ezModeInvoke);

  (void)addressing, (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receiving Update Commissioning State command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
static ZCL_Status_t updateCommissioningStateInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_UpdateCommissioningState_t *payload)
{
  LOG_STRING(identifyStr, "->Update Commissining State\r\n");
  appSnprintf(identifyStr);

  if (ZCL_UPDATE_COMMISSIONING_STATE_ACTION_SET == payload->action)
  {
    ciIdentifyClusterServerAttributes.commissioningState.value.networkState     |= payload->commissioningStateMask.networkState;
    ciIdentifyClusterServerAttributes.commissioningState.value.operationalState |= payload->commissioningStateMask.operationalState;
  }
  if (ZCL_UPDATE_COMMISSIONING_STATE_ACTION_CLEAR == payload->action)
  {
    ciIdentifyClusterServerAttributes.commissioningState.value.networkState     &= ~payload->commissioningStateMask.networkState;
    ciIdentifyClusterServerAttributes.commissioningState.value.operationalState &= ~payload->commissioningStateMask.operationalState;
  }

  RAISE_CALLBACKS_TO_IDENTIFY_SUBSCIBERS(subscribers, updateCommissioningState);

  (void)addressing, (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Sends Identidy Query Response command

\param[in] addressing - addressing information about sender device

\returns status of sending
******************************************************************************/
static ZCL_Status_t sendIdentifyQueryResponse(ZCL_Addressing_t *addressing)
{
  ZCL_Request_t *req;

  if (!(req = getFreeCommand()))
    return ZCL_INSUFFICIENT_SPACE_STATUS;

  fillCommandRequest(req, ZCL_IDENTIFY_CLUSTER_IDENTIFY_QUERY_RESPONSE_COMMAND_ID,
                       sizeof(ZCL_IdentifyQueryResponse_t));
  ciFillIdentifyQueryResponsePayload((ZCL_IdentifyQueryResponse_t *)req->requestPayload, ciIdentifyClusterServerAttributes.identifyTime.value);
  fillDstAddressingViaSourceAddressing(&req->dstAddressing, addressing, ZCL_CLUSTER_SIDE_CLIENT);
  commandManagerSendCommand(req);

  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Fills Identify Query Response command structure

\param[out] payload - pointer to command structure;
\param[in]  time    - identify time
******************************************************************************/
static void ciFillIdentifyQueryResponsePayload(ZCL_IdentifyQueryResponse_t *payload, uint16_t time)
{
  payload->timeout = time;
}

/**************************************************************************//**
\brief Fills Identify command structure

\param[out] payload - pointer to command structure;
\param[in]  time    - identify time
******************************************************************************/
static void ciFillIdentifyPayload(ZCL_Identify_t *payload, uint16_t time)
{
  payload->identifyTime = time;
}

/**************************************************************************//**
\brief Fills EZ-Mode Invoke command structure

\param[out] payload - pointer to command structure;
\param[in]  action  - action
******************************************************************************/
static void ciFillEzModeInvokePayload(ZCL_EzModeInvoke_t *payload, uint8_t action)
{
  payload->data = action;
  (void)payload;
}

/**************************************************************************//**
\brief Fills Update Commissiong State command structure

\param[out] payload - pointer to command structure;
\param[in]  time    - identify time
******************************************************************************/
static void ciFillUpdateCommissioningStatePayload(ZCL_UpdateCommissioningState_t *payload, uint8_t action, uint8_t mask)
{
  payload->action                      = action;
  payload->commissioningStateMask.data = mask;
}

/**************************************************************************//**
\brief Identify timer has fired
******************************************************************************/
static void identifyTimerFired(void)
{
  --ciIdentifyClusterServerAttributes.identifyTime.value;
  // TO DO: toggle LED
  if (!ciIdentifyClusterServerAttributes.identifyTime.value)
  {
    HAL_StopAppTimer(&identifyTimer);
    // TO DO: turn LED off
  }
}
/**************************************************************************//**
\brief Identify reset subscribers queue
******************************************************************************/
void idenityResetSubscribers()
{
  resetQueue(&subscribers);
}

/**************************************************************************//**
\brief Sends Read Attribute command unicastly

\param[in] mode - address mode;
\param[in] addr - short address of destination node;
\param[in] ep   - destination endpoint;
\param[in] attr - attribute id;
\param[in] cb   - callback function
******************************************************************************/
void identifyReadAttribute(APS_AddrMode_t mode,ShortAddr_t addr, Endpoint_t ep,
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
  fillDstAddressing(&req->dstAddressing, mode, addr, ep, IDENTIFY_CLUSTER_ID);
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
void identifyWriteAttribute(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep,
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
  fillDstAddressing(&req->dstAddressing, mode, addr, ep, IDENTIFY_CLUSTER_ID);
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
    LOG_STRING(readAttrSuccessStr, " <-Read Identify attribute (0x%x) response: success t = 0x%x\r\n");
    appSnprintf(readAttrSuccessStr, (unsigned)readAttributeResp->id, attributeValue);
  }
  else
  {
    LOG_STRING(readAttrFailStr, " Read Identify attribute failed: status = 0x%2x\r\n");
    appSnprintf(readAttrFailStr, (unsigned)ntfy->status);
  }
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

    LOG_STRING(writeAttrSuccessStr, " <-Write Identify attribute response: success\r\n");
    appSnprintf(writeAttrSuccessStr);
  }
  else
  {
    LOG_STRING(writeAttrFailStrTwo, " +Write Identify attribute failed: status = 0x%x\r\n");
    appSnprintf(writeAttrFailStrTwo, (unsigned)ntfy->status);
  }
}

/**************************************************************************//**
\brief Attribute event (writing/reading) callback.

\param[in] addressing - incoming request addressing information.
\param[in] attributeId - attribute identifier.
\param[in] event - attribute event (read/write).
******************************************************************************/
static void ZCL_IdentifyAttributeEventInd(ZCL_Addressing_t *addressing,
  ZCL_AttributeId_t attributeId, ZCL_AttributeEvent_t event)
{
  if ((ZCL_WRITE_ATTRIBUTE_EVENT == event) &&
      (ZCL_IDENTIFY_CLUSTER_IDENTIFY_TIME_ATTRIBUTE_ID == attributeId))
  {
    HAL_StopAppTimer(&identifyTimer);
    if (ciIdentifyClusterServerAttributes.identifyTime.value)
      HAL_StartAppTimer(&identifyTimer);

    (void)addressing;
  }
}
#endif // APP_DEVICE_TYPE_COMBINED_INTERFACE

// eof ciIdentifyCluster.c

