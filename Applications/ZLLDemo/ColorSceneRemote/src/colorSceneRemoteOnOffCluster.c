/**************************************************************************//**
  \file colorSceneRemoteOnOffCluster.c

  \brief
    Color Scene Remote device On/Off cluster implementation.

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
                    Includes section
******************************************************************************/
#include <debug.h>
#include <zcl.h>
#include <zclParser.h>
#include <clusters.h>
#include <commandManager.h>
#include <colorSceneRemoteOnOffCluster.h>
#include <colorSceneRemoteClusters.h>

/******************************************************************************
                    Global variables
******************************************************************************/
ZCL_OnOffClusterCommands_t onOffClusterCommands =
{
  ZCL_DEFINE_ONOFF_CLUSTER_COMMANDS(NULL, NULL, NULL, NULL, NULL, NULL)
};

/******************************************************************************
                    Local variables
******************************************************************************/

/******************************************************************************
                    Prototypes
******************************************************************************/
#if APP_ENABLE_CERTIFICATION_EXTENSION == 1
static void readAttributeResp(ZCL_Notify_t *ntfy);
#endif // APP_ENABLE_CERTIFICATION_EXTENSION == 1
/******************************************************************************
                    Implementations
******************************************************************************/
#if APP_ENABLE_CERTIFICATION_EXTENSION == 0
/**************************************************************************//**
\brief Sends On/Off command

\param[in] mode    - address mode;
\param[in] addr    - short address of destination node or number of group;
\param[in] command - 0 - off command, 1 - on command;
\param[in] ep      - endpoint number of destination device
******************************************************************************/
void colorSceneRemoteSendOnOffCommand(APS_AddrMode_t mode, ShortAddr_t addr, uint8_t command, Endpoint_t ep)
{
  CommandDescriptor_t *cmd;
  ZCL_Addressing_t addressing;

  if (!(cmd = colorSceneRemoteGetFreeCommand()))
    return;

  colorSceneRemoteFillCommandRequest(cmd, command, ONOFF_CLUSTER_ID, 0);
  colorSceneRemoteFillDstAddressing(&addressing, mode, addr, ep);
  addressing.clusterId = ONOFF_CLUSTER_ID;

  clustersSendCommandWithAddressing(cmd, &addressing);
}

#else // APP_ENABLE_CERTIFICATION_EXTENSION == 1
/**************************************************************************//**
\brief Sends On/Off/Toggle commands

\param[in] command - 0 - off command, 1 - on command;
******************************************************************************/
void colorSceneRemoteSendOnOffCommand(uint8_t command)
{
  CommandDescriptor_t *cmd;

  if (!(cmd = colorSceneRemoteGetFreeCommand()))
    return;

  colorSceneRemoteFillCommandRequest(cmd, command, ONOFF_CLUSTER_ID, 0);

  clustersSendCommand(cmd);
}

/**************************************************************************//**
\brief Sends Off with Effect command

\param[in] effectIdentifier - identifier of the effect to be used
\param[in] effectVariant - effect variant
******************************************************************************/
void colorSceneRemoteSendOffWithEffectCommand(uint8_t effectIdentifier, uint8_t effectVariant)
{
  CommandDescriptor_t *cmd;

  if (!(cmd = colorSceneRemoteGetFreeCommand()))
    return;

  colorSceneRemoteFillCommandRequest(cmd, ZCL_ONOFF_CLUSTER_OFF_WITH_EFFECT_COMMAND_ID, ONOFF_CLUSTER_ID, 0);
  cmd->payload.offWithEffect.effectIdentifier = effectIdentifier;
  cmd->payload.offWithEffect.effectVariant = effectVariant;
  cmd->size = sizeof(cmd->payload.offWithEffect);

  clustersSendCommand(cmd);
}

/**************************************************************************//**
\brief Sends On with timed off command

\param[in] onOffControl - on/off control field value
\param[in] onTime - on time field value
\param[in] offWaitTime - off wait time value
******************************************************************************/
void colorSceneRemoteSendOnWithTimedOffCommand(uint8_t onOffControl, uint16_t onTime, uint16_t offWaitTime)
{
  CommandDescriptor_t *cmd;

  if (!(cmd = colorSceneRemoteGetFreeCommand()))
    return;

  colorSceneRemoteFillCommandRequest(cmd, ZCL_ONOFF_CLUSTER_ON_WITH_TIMED_OFF_COMMAND_ID, ONOFF_CLUSTER_ID, 0);
  cmd->payload.onWithTimedOff.onOffControl = onOffControl;
  cmd->payload.onWithTimedOff.onTime = onTime;
  cmd->payload.onWithTimedOff.offWaitTime = offWaitTime;
  cmd->size = sizeof(cmd->payload.onWithTimedOff);

  clustersSendCommand(cmd);
}

/**************************************************************************//**
\brief Sends On/off Cluster read attribute command

\param[in] attributeId - attribute of interest identifier
******************************************************************************/
void onOffSendReadAttribute(uint16_t attributeId)
{
  CommandDescriptor_t *cmd;

  if (!(cmd = clustersAllocCommand()))
    return;

  cmd->clusterId = ONOFF_CLUSTER_ID;
  cmd->commandId = ZCL_READ_ATTRIBUTES_COMMAND_ID;
  cmd->payload.readAttribute.id = attributeId;
  cmd->size = sizeof(ZCL_ReadAttributeReq_t);
  cmd->isAttributeOperation = true;
  cmd->ZCL_Notify = readAttributeResp;
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
#endif // APP_ENABLE_CERTIFICATION_EXTENSION
#endif // APP_ZLL_DEVICE_TYPE == APP_DEVICE_TYPE_COLOR_SCENE_REMOTE

// eof colorSceneRemoteOnOffCluster.c
