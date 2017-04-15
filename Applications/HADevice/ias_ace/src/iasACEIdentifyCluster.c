/**************************************************************************//**
  \file iasACEIdentifyCluster.c

  \brief
    iasACE Identify cluster implementation.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    18/11/2014 Yogesh - Created.
******************************************************************************/
#ifdef APP_DEVICE_TYPE_IAS_ACE

/******************************************************************************
                    Includes section
******************************************************************************/
#include <iasACEIdentifyCluster.h>
#include <identifyCluster.h>
#include <haClusters.h>
#include <uartManager.h>
#include <commandManager.h>
#include <pdsDataServer.h>
#include <zclDevice.h>
#include <ezModeManager.h>

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
static void iasACEFillIdentifyQueryResponsePayload(ZCL_IdentifyQueryResponse_t *payload, uint16_t time);
static void identifyTimerFired(void);
static void ZCL_IdentifyAttributeEventInd(ZCL_Addressing_t *addressing, ZCL_AttributeId_t attributeId, ZCL_AttributeEvent_t event);

/******************************************************************************
                    Global variables section
******************************************************************************/
ZCL_IdentifyClusterAttributes_t iasACEIdentifyClusterServerAttributes =
{
  ZCL_DEFINE_IDENTIFY_CLUSTER_SERVER_ATTRIBUTES()
};
ZCL_IdentifyClusterCommands_t   iasACEIdentifyCommands =
{
  IDENTIFY_CLUSTER_COMMANDS(identifyInd, identifyQueryInd, identifyQueryResponseInd, ezModeInvokeInd, updateCommissioningStateInd)
};

/******************************************************************************
                    Static variables section
******************************************************************************/
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
  iasACEIdentifyClusterServerAttributes.identifyTime.value = 0;

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
    if(!putQueueElem(&subscribers, subscriber))
    {
	  /* failed to queue */
    }
}

/**************************************************************************//**
\brief Sends Identify Query request

\param[in] mode - address mode;
\param[in] addr - short address of destination node;
\param[in] ep   - destination endpoint
******************************************************************************/
void identifySendIdentifyQuery(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep)
{
  (void)mode, (void)addr, (void)ep;
}

/**************************************************************************//**
\brief Sends Update Commissioning State command

\param[in] mode - address mode;
\param[in] addr   - short address of destination node;
\param[in] ep     - destination endpoint;
\param[in] action - action to be done upon reception;
\param[in] mask   - commissiong state mask
******************************************************************************/
void identifySendUpdateCommissioningState(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep,
  ZCL_UpdateCommissioningStateAction_t action, uint8_t mask)
{
  (void)mode, (void)addr, (void)ep, (void)action, (void)mask;
}

/**************************************************************************//**
\brief Checks if identification process is in progress

\returns true if it is, false otherwise
******************************************************************************/
bool identifyIsIdentifying(void)
{
  return iasACEIdentifyClusterServerAttributes.identifyTime.value > 0;
}

/**************************************************************************//**
\brief Makes device to start identify itself

\param[in] time - identifying time in seconds
******************************************************************************/
void idetifyStartIdentifying(uint16_t time)
{
  iasACEIdentifyClusterServerAttributes.identifyTime.value = time;
  HAL_StopAppTimer(&identifyTimer);
  HAL_StartAppTimer(&identifyTimer);
}

/**************************************************************************//**
\brief Send Identify Query command unicastly

\param[in] nwkState        - new netwrok state;
\param[in] operationalState - new operational state
******************************************************************************/
void identifyUpdateCommissioningState(bool nwkState, bool operationalState)
{
  iasACEIdentifyClusterServerAttributes.commissioningState.value.networkState     = nwkState;
  iasACEIdentifyClusterServerAttributes.commissioningState.value.operationalState = operationalState;
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

  iasACEIdentifyClusterServerAttributes.identifyTime.value = payload->identifyTime;

  HAL_StopAppTimer(&identifyTimer);

  if (payload->identifyTime)
  {
    
    HAL_StartAppTimer(&identifyTimer);
  }

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
  
  if (iasACEIdentifyClusterServerAttributes.identifyTime.value)
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
  LOG_STRING(identifyStr, "->Identify Query Response, addr = %d\r\n");
  appSnprintf(identifyStr, addressing->addr.shortAddress);

  RAISE_CALLBACKS_TO_IDENTIFY_SUBSCIBERS(subscribers, identifyQueryResponse);

  (void)payloadLength;
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

  if (payload->factoryFresh)
    PDS_DeleteAll(false);
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
\brief Callback on receiving Upodate Commissioning State command

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
    iasACEIdentifyClusterServerAttributes.commissioningState.value.networkState     |= payload->commissioningStateMask.networkState;
    iasACEIdentifyClusterServerAttributes.commissioningState.value.operationalState |= payload->commissioningStateMask.operationalState;
  }
  if (ZCL_UPDATE_COMMISSIONING_STATE_ACTION_CLEAR == payload->action)
  {
    iasACEIdentifyClusterServerAttributes.commissioningState.value.networkState     &= ~payload->commissioningStateMask.networkState;
    iasACEIdentifyClusterServerAttributes.commissioningState.value.operationalState &= ~payload->commissioningStateMask.operationalState;
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
  iasACEFillIdentifyQueryResponsePayload((ZCL_IdentifyQueryResponse_t *)req->requestPayload, iasACEIdentifyClusterServerAttributes.identifyTime.value);
  fillDstAddressingViaSourceAddressing(&req->dstAddressing, addressing, ZCL_CLUSTER_SIDE_CLIENT);
  commandManagerSendCommand(req);

  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Fills Identify Query Response command structure

\param[out] payload - pointer to command structure;
\param[in]  time    - identify time
******************************************************************************/
static void iasACEFillIdentifyQueryResponsePayload(ZCL_IdentifyQueryResponse_t *payload, uint16_t time)
{
  payload->timeout = time;
}

/**************************************************************************//**
\brief Identify timer has fired
******************************************************************************/
static void identifyTimerFired(void)
{
  --iasACEIdentifyClusterServerAttributes.identifyTime.value;
  // TO DO: toggle LED
  if (!iasACEIdentifyClusterServerAttributes.identifyTime.value)
  {    
    HAL_StopAppTimer(&identifyTimer);
    // TO DO: turn LED off
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
    if (iasACEIdentifyClusterServerAttributes.identifyTime.value)
      HAL_StartAppTimer(&identifyTimer);

    (void)addressing;
  }
}
#endif // APP_DEVICE_TYPE_IAS_ACE

// eof iasACEIdentifyCluster.c

