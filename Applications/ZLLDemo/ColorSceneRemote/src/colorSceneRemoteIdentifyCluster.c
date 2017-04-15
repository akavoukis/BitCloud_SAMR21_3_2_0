/**************************************************************************//**
  \file colorSceneRemoteIdentifyCluster.c

  \brief
    Color Scene Remote device Identify cluster implementation.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    28.06.11 A. Taradov - Created.
******************************************************************************/

#if APP_ZLL_DEVICE_TYPE == APP_DEVICE_TYPE_COLOR_SCENE_REMOTE

/******************************************************************************
                    Includes
******************************************************************************/
#include <debug.h>
#include <zclParser.h>
#include <zcl.h>
#include <clusters.h>
#include <commandManager.h>
#include <zclZllIdentifyCluster.h>
#include <zllDemo.h>
#include <colorSceneRemoteIdentifyCluster.h>
#include <colorSceneRemoteClusters.h>

/******************************************************************************
                    Definitions section
******************************************************************************/
#define IDENTIFY_TIME 5

/******************************************************************************
                    Prototypes section
******************************************************************************/
static void colorSceneRemoteFillIdentifyPayload(ZCL_Identify_t *payload, uint16_t time);
#if APP_ENABLE_CERTIFICATION_EXTENSION == 1
static void readAttributeResp(ZCL_Notify_t *ntfy);
static void commandZclRequestResp(ZCL_Notify_t *ntfy);
static ZCL_Status_t identifyQueryResponseCommand(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_IdentifyQueryResponse_t *payload);
#endif // APP_ENABLE_CERTIFICATION_EXTENSION == 1

/******************************************************************************
                    Global variables section
******************************************************************************/
ZCL_IdentifyClusterCommands_t identifyClusterCommands =
{
#if APP_ENABLE_CERTIFICATION_EXTENSION == 1
  ZCL_IDENTIFY_CLUSTER_COMMANDS(NULL, NULL, NULL, identifyQueryResponseCommand)
#else
  ZCL_IDENTIFY_CLUSTER_COMMANDS(NULL, NULL, NULL, NULL)
#endif
};

/******************************************************************************
                    Implementation section
******************************************************************************/
/**************************************************************************//**
\brief Initialize Identify cluster.
******************************************************************************/
void identifyClusterInit(void)
{
#if APP_ENABLE_CERTIFICATION_EXTENSION == 1
  ZCL_Cluster_t *identifyCluster = ZCL_GetCluster(APP_ENDPOINT_COLOR_SCENE_REMOTE,
                                                  IDENTIFY_CLUSTER_ID,
                                                  ZCL_CLUSTER_SIDE_CLIENT);

  identifyCluster->ZCL_DefaultRespInd = commandManagerDefaultResponseHandler;
#endif // APP_ENABLE_CERTIFICATION_EXTENSION == 1
}

#if APP_ENABLE_CERTIFICATION_EXTENSION == 0
/**************************************************************************//**
\brief Sends Identify command

\param[in] mode  - address mode;
\param[in] addr  - short address of destination node or number of group;
\param[in] ep    - endpoint number of destination device
******************************************************************************/
void colorSceneRemoteSendIdentifyCommand(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep)
{
  CommandDescriptor_t *cmd;
  ZCL_Addressing_t addressing;

  if (!(cmd = colorSceneRemoteGetFreeCommand()))
    return;

  colorSceneRemoteFillCommandRequest(cmd, ZCL_IDENTIFY_CLUSTER_IDENTIFY_COMMAND_ID,
                                     IDENTIFY_CLUSTER_ID, sizeof(cmd->payload.identify));
  colorSceneRemoteFillIdentifyPayload(&cmd->payload.identify, IDENTIFY_TIME);
  colorSceneRemoteFillDstAddressing(&addressing, mode, addr, ep);
  addressing.clusterId = IDENTIFY_CLUSTER_ID;

  clustersSendCommandWithAddressing(cmd, &addressing);
}

#else // APP_ENABLE_CERTIFICATION_EXTENSION == 1
/**************************************************************************//**
\brief Sends Identify command
******************************************************************************/
void colorSceneRemoteSendIdentifyCommand(uint16_t identifyTime)
{
  CommandDescriptor_t *cmd;

  if (!(cmd = colorSceneRemoteGetFreeCommand()))
    return;

  colorSceneRemoteFillCommandRequest(cmd, ZCL_IDENTIFY_CLUSTER_IDENTIFY_COMMAND_ID,
                                     IDENTIFY_CLUSTER_ID, sizeof(cmd->payload.identify));
  colorSceneRemoteFillIdentifyPayload(&cmd->payload.identify, identifyTime);
  clustersSendCommand(cmd);
}

/**************************************************************************//**
\brief Sends Identify Query command
******************************************************************************/
void colorSceneRemoteSendIdentifyQueryCommand(void)
{
  CommandDescriptor_t *cmd;

  if (!(cmd = colorSceneRemoteGetFreeCommand()))
    return;

  colorSceneRemoteFillCommandRequest(cmd, ZCL_IDENTIFY_CLUSTER_IDENTIFY_QUERY_COMMAND_ID,
                                     IDENTIFY_CLUSTER_ID, 0);
  cmd->ZCL_Notify = commandZclRequestResp;
  clustersSendCommand(cmd);
}

/**************************************************************************//**
\brief ZCL command response
******************************************************************************/
static void commandZclRequestResp(ZCL_Notify_t *ntfy)
{
  if (ZCL_ZCL_RESPONSE_ID == ntfy->id &&
      ZCL_SUCCESS_STATUS == ntfy->status)
  {
    ZCL_IdentifyQueryResponse_t *resp = (ZCL_IdentifyQueryResponse_t *)ntfy->responsePayload;
    LOG_STRING(zclIdentifyQueryStr, "IdentifyQueryResp: timeout = 0x%04x\r\n");

    appSnprintf(zclIdentifyQueryStr, resp->timeout);
  }
}


/**************************************************************************//**
\brief Sends Trigger Effect command
******************************************************************************/
void colorSceneRemoteSendTriggerEffectCommand(uint8_t effectIdentifier, uint8_t effectVariant)
{
  CommandDescriptor_t *cmd;

  if (!(cmd = colorSceneRemoteGetFreeCommand()))
    return;

  colorSceneRemoteFillCommandRequest(cmd, ZCL_IDENTIFY_CLUSTER_TRIGGER_EFFECT_COMMAND_ID,
                                     IDENTIFY_CLUSTER_ID, sizeof(cmd->payload.triggerEffect));
  cmd->payload.triggerEffect.effectIdentifier = effectIdentifier;
  cmd->payload.triggerEffect.effectVariant = effectVariant;
  clustersSendCommand(cmd);
}

/**************************************************************************//**
\brief Sends Identify Cluster read attribute command

\param[in] attributeId - attribute of interest identifier
******************************************************************************/
void identifySendReadAttribute(uint16_t attributeId)
{
  CommandDescriptor_t *cmd;

  if (!(cmd = clustersAllocCommand()))
    return;

  cmd->clusterId = IDENTIFY_CLUSTER_ID;
  cmd->commandId = ZCL_READ_ATTRIBUTES_COMMAND_ID;
  cmd->payload.readAttribute.id = attributeId;
  cmd->size = sizeof(ZCL_ReadAttributeReq_t);
  cmd->isAttributeOperation = true;
  cmd->ZCL_Notify = readAttributeResp;
  clustersSendCommand(cmd);
}

/**************************************************************************//**
\brief Sends Identify Cluster write attribute command

\param[in] attributeId - attribute of interest identifier
******************************************************************************/
void identifySendWriteAttribute(uint16_t attributeId, void *value, uint8_t type)
{
  CommandDescriptor_t *cmd;
  ZCL_DataTypeDescriptor_t attrDesc;

  if (!(cmd = clustersAllocCommand()))
    return;

  ZCL_GetDataTypeDescriptor(type, value, &attrDesc);

  cmd->clusterId = IDENTIFY_CLUSTER_ID;
  cmd->commandId = ZCL_WRITE_ATTRIBUTES_COMMAND_ID;
  cmd->payload.writeAttribute.id = attributeId;
  cmd->payload.writeAttribute.type = type;
  memcpy(cmd->payload.writeAttribute.value, value, attrDesc.length);
  cmd->size = sizeof(uint16_t) + sizeof(uint8_t) + attrDesc.length;
  cmd->isAttributeOperation = true;
  clustersSendCommand(cmd);
}

/**************************************************************************//**
\brief ZCL command response
******************************************************************************/
static void readAttributeResp(ZCL_Notify_t *ntfy)
{
  if (ZCL_ZCL_RESPONSE_ID == ntfy->id && ZCL_SUCCESS_STATUS == ntfy->status)
  {
    ZCL_ReadAttributeResp_t *readAttrResp = (ZCL_ReadAttributeResp_t *)ntfy->responsePayload;
    ZCL_DataTypeDescriptor_t attrDesc;

    ZCL_GetDataTypeDescriptor(readAttrResp->type, readAttrResp->value, &attrDesc);

    if ((ZCL_DATA_TYPE_ANALOG_KIND == attrDesc.kind ||
         ZCL_DATA_TYPE_DISCRETE_KIND == attrDesc.kind) &&
        sizeof(uint32_t) >= attrDesc.length)
    {
      uint32_t value = 0;
      LOG_STRING(attrValueStr, "Attr 0x%04x = %u\r\n");

      memcpy(&value, readAttrResp->value, attrDesc.length);
      appSnprintf(attrValueStr, (unsigned)readAttrResp->id, (unsigned int)value);
    }
  }
}

/**************************************************************************//**
\brief Callback on receive of Identify Query Response command
******************************************************************************/
static ZCL_Status_t identifyQueryResponseCommand(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_IdentifyQueryResponse_t *payload)
{
  LOG_STRING(zclIdentifyQueryRespStr, "IdentifyQueryResp: timeout = 0x%04x\r\n");

  appSnprintf(zclIdentifyQueryRespStr, payload->timeout);

  (void)addressing;
  (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}

#endif // APP_ENABLE_CERTIFICATION_EXTENSION

/**************************************************************************//**
\brief Fills Identify command structure

\param[out] payload - pointer to command structure;
\param[in]  time    - identify time
******************************************************************************/
static void colorSceneRemoteFillIdentifyPayload(ZCL_Identify_t *payload, uint16_t time)
{
  payload->identifyTime = time;
}

#endif // APP_ZLL_DEVICE_TYPE == APP_DEVICE_TYPE_COLOR_SCENE_REMOTE

// eof colorSceneRemoteIdentifyCluster.c
