/**************************************************************************//**
  \file bridgeLinkInfoCluster.c

  \brief
    Control Bridge device Link Info cluster implementation.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    25.01.13 N. Fomin - Created.
******************************************************************************/

#if APP_ZLL_DEVICE_TYPE == APP_DEVICE_TYPE_BRIDGE

/******************************************************************************
                    Includes section
******************************************************************************/
#include <colorSceneRemoteLinkInfoCluster.h>
#include <zllDemo.h>
#include <uartManager.h>
#include <commandManager.h>
#include <bridgeClusters.h>

/******************************************************************************
                    Prototypes section
******************************************************************************/
static ZCL_Status_t readyToTransmitInd(ZCL_Addressing_t *addressing, uint8_t payloadLength,
                                       ZCL_ReadyToTransmit_t *payload);

static void readLinkInfoAttrResp(ZCL_Notify_t *ntfy);
static ZCL_Status_t sendReadAttrRequest(ZCL_Addressing_t *addressing, ZCL_AttributeId_t id);

/******************************************************************************
                    Global variables section
******************************************************************************/
ZCL_LinkInfoClusterCommands_t linkInfoCommands =
{
  ZCL_DEFINE_LINK_INFO_SERVER_SIDE_CLUSTER_COMMANDS(readyToTransmitInd)
};

/******************************************************************************
                    Local variables section
******************************************************************************/
static uint16_t boundDevicesAmount;
static uint16_t currentAttrId;
static bool     transmissionInProgress;

/******************************************************************************
                    Implementations section
******************************************************************************/
/**************************************************************************//**
\brief Initialize Link Info cluster
******************************************************************************/
void linkInfoClusterInit(void)
{}

/**************************************************************************//**
\brief Callback on receiving Ready To Transmit command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\returns status of indication routine
******************************************************************************/
static ZCL_Status_t readyToTransmitInd(ZCL_Addressing_t *addressing, uint8_t payloadLength,
                                       ZCL_ReadyToTransmit_t *payload)
{
  boundDevicesAmount = payload->boundDevicesAmount;
  if (boundDevicesAmount && !transmissionInProgress)
  {
    transmissionInProgress = true;
    currentAttrId          = 0;

    return sendReadAttrRequest(addressing, 0);
  }

  (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Indication of read attribute response

\param[in] ntfy - pointer to response
******************************************************************************/
static void readLinkInfoAttrResp(ZCL_Notify_t *ntfy)
{
  if (ZCL_SUCCESS_STATUS == ntfy->status)
  {
    ZCL_ReadAttributeResp_t *resp = (ZCL_ReadAttributeResp_t *)ntfy->responsePayload;
    ZclLinkInfoAttrValue_t *attrValue = (ZclLinkInfoAttrValue_t *)resp->value;
    BoundDevice_t *device = (BoundDevice_t *)attrValue->payload;

    LOG_STRING(lightInfoStr, "\r\nLight: %d %d 0x%x %d");
    LOG_STRING(groupInfoStr, " %d");
    LOG_STRING(endStr, "\r\n");

    appSnprintf(lightInfoStr, 
                (int)((device->ieeeAddr >> 32) & ~(0UL)), 
                (int)(device->ieeeAddr & ~(0UL)), 
                device->nwkAddr,
                device->endpoint);

    if (device->isInGroup)
      appSnprintf(groupInfoStr, device->groupIds);

    appSnprintf(endStr);
  }

  if (!(--boundDevicesAmount))
    transmissionInProgress = false;
  else
    sendReadAttrRequest(ntfy->addressing, ++currentAttrId);
}

/**************************************************************************//**
\brief Sends read attribute request

\param[in] addressing - addressing information about destination node;
\param[in] id         - attribute identifier
******************************************************************************/
static ZCL_Status_t sendReadAttrRequest(ZCL_Addressing_t *addressing, ZCL_AttributeId_t id)
{
  CommandDescriptor_t *cmd;
  ZCL_Addressing_t dstAddressing;

  if (!(cmd = bridgeGetFreeCommand()))
    return ZCL_INSUFFICIENT_SPACE_STATUS;

  cmd->isAttributeOperation = true;
  bridgeFillCommandRequest(cmd, ZCL_READ_ATTRIBUTES_COMMAND_ID,
                           LINK_INFO_CLUSTER_ID, sizeof(ZCL_ReadAttributeReq_t));
  bridgeFillDstAddressing(&dstAddressing, APS_SHORT_ADDRESS,
                          addressing->addr.shortAddress, addressing->endpointId);
  dstAddressing.manufacturerSpecCode = 0xabcd;
  dstAddressing.clusterSide = ZCL_CLUSTER_SIDE_CLIENT;
  cmd->payload.readAttribute.id = id;
  cmd->ZCL_Notify = readLinkInfoAttrResp;

  clustersSendCommandWithAddressing(cmd, &dstAddressing);

  return ZCL_SUCCESS_STATUS;
}

#endif // APP_ZLL_DEVICE_TYPE == APP_DEVICE_TYPE_COLOR_SCENE_REMOTE

// eof bridgeLinkInfoCluster.c
