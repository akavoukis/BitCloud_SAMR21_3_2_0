/**************************************************************************//**
  \file colorSceneRemoteLevelControlCluster.c

  \brief
    Color Scene Remote device Level Control cluster implementation.

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
#include <colorSceneRemoteLevelControlCluster.h>
#include <colorSceneRemoteClusters.h>

/******************************************************************************
                    Global variables section
******************************************************************************/
ZCL_LevelControlClusterCommands_t levelControlClusterCommands =
{
  ZCL_DEFINE_LEVEL_CONTROL_CLUSTER_COMMANDS(NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL)
};

/******************************************************************************
                    Prototypes section
******************************************************************************/
static void colorSceneRemoteFillMoveToLevelPayload(ZCL_MoveToLevel_t *payload, uint8_t level, uint16_t time);
#if APP_ENABLE_CERTIFICATION_EXTENSION == 1
static void readAttributeResp(ZCL_Notify_t *ntfy);
#endif // APP_ENABLE_CERTIFICATION_EXTENSION == 1
/******************************************************************************
                    Implementations section
******************************************************************************/
#if APP_ENABLE_CERTIFICATION_EXTENSION == 0
/**************************************************************************//**
\brief Sends Move To Level command

\param[in] mode  - address mode;
\param[in] addr  - short address of destination node or number of group;
\param[in] level - color level;
\param[in] time  - transition time;
\param[in] ep    - endpoint number of destination device
******************************************************************************/
void colorSceneRemoteSendMoveToLevelCommand(APS_AddrMode_t mode, ShortAddr_t addr, uint8_t level, uint16_t time, Endpoint_t ep)
{
  CommandDescriptor_t *cmd;
  ZCL_Addressing_t addressing;

  if (!(cmd = colorSceneRemoteGetFreeCommand()))
    return;

  colorSceneRemoteFillCommandRequest(cmd, ZCL_LEVEL_CONTROL_CLUSTER_MOVE_TO_LEVEL_COMMAND_ID,
                                     LEVEL_CONTROL_CLUSTER_ID, sizeof(cmd->payload.moveToLevel));
  colorSceneRemoteFillMoveToLevelPayload(&cmd->payload.moveToLevel, level, time);
  colorSceneRemoteFillDstAddressing(&addressing, mode, addr, ep);
  addressing.clusterId = LEVEL_CONTROL_CLUSTER_ID;

  clustersSendCommandWithAddressing(cmd, &addressing);
}

#else // APP_ENABLE_CERTIFICATION_EXTENSION == 1
/**************************************************************************//**
\brief Sends commands without payload

\param[in] command - command identifier
******************************************************************************/
void colorSceneRemoteSendLevelControlCommand(uint8_t command)
{
  CommandDescriptor_t *cmd;

  if (!(cmd = colorSceneRemoteGetFreeCommand()))
    return;

  colorSceneRemoteFillCommandRequest(cmd, command,
                                     LEVEL_CONTROL_CLUSTER_ID, 0);
  clustersSendCommand(cmd);
}


/**************************************************************************//**
\brief Sends move to level command (ZCL_LEVEL_CONTROL_CLUSTER_MOVE_TO_LEVEL_COMMAND_ID or
                                    ZCL_LEVEL_CONTROL_CLUSTER_MOVE_TO_LEVEL_W_ONOFF_COMMAND_ID)

\param[in] command - command identifier
\param[in] level - color level;
\param[in] time  - transition time;
******************************************************************************/
void colorSceneRemoteSendMoveToLevelCommand(uint8_t command, uint8_t level, uint16_t time)
{
  CommandDescriptor_t *cmd;

  if (!(cmd = colorSceneRemoteGetFreeCommand()))
    return;

  colorSceneRemoteFillCommandRequest(cmd, command,
                                     LEVEL_CONTROL_CLUSTER_ID, sizeof(cmd->payload.moveToLevel));
  colorSceneRemoteFillMoveToLevelPayload(&cmd->payload.moveToLevel, level, time);

  clustersSendCommand(cmd);
}

/**************************************************************************//**
\brief Sends move command

\param[in] command - command identifier (ZCL_LEVEL_CONTROL_CLUSTER_MOVE_W_ONOFF_COMMAND_ID
                     or ZCL_LEVEL_CONTROL_CLUSTER_MOVE_COMMAND_ID);
\param[in] moveMode - move type;
\param[in] rate - rate in units per second;
******************************************************************************/
void colorSceneRemoteSendMoveCommand(uint8_t command, uint8_t moveMode, uint8_t rate)
{
  CommandDescriptor_t *cmd;

  if (!(cmd = colorSceneRemoteGetFreeCommand()))
    return;

  colorSceneRemoteFillCommandRequest(cmd, command,
                                     LEVEL_CONTROL_CLUSTER_ID, 0);

  cmd->payload.moveLevel.moveMode = moveMode;
  cmd->payload.moveLevel.rate = rate;
  cmd->size = sizeof(cmd->payload.moveLevel);

  clustersSendCommand(cmd);
}

/**************************************************************************//**
\brief Sends move command

\param[in] command - command identifier (ZCL_LEVEL_CONTROL_CLUSTER_STEP_W_ONOFF_COMMAND_ID
                     or ZCL_LEVEL_CONTROL_CLUSTER_STEP_COMMAND_ID);
\param[in] stepMode - step type;
\param[in] size - step size;
\param[in] time - transition time;
******************************************************************************/
void colorSceneRemoteSendStepCommand(uint8_t command, uint8_t stepMode, uint8_t size, uint16_t time)
{
  CommandDescriptor_t *cmd;

  if (!(cmd = colorSceneRemoteGetFreeCommand()))
    return;

  colorSceneRemoteFillCommandRequest(cmd, command,
                                     LEVEL_CONTROL_CLUSTER_ID, 0);

  cmd->payload.stepLevel.stepMode = stepMode;
  cmd->payload.stepLevel.stepSize = size;
  cmd->payload.stepLevel.transitionTime = time;
  cmd->size = sizeof(cmd->payload.stepLevel);

  clustersSendCommand(cmd);
}

/**************************************************************************//**
\brief Sends Level control Cluster read attribute command

\param[in] attributeId - attribute of interest identifier
******************************************************************************/
void levelControlSendReadAttribute(uint16_t attributeId)
{
  CommandDescriptor_t *cmd;

  if (!(cmd = clustersAllocCommand()))
    return;

  cmd->clusterId = LEVEL_CONTROL_CLUSTER_ID;
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
/**************************************************************************//**
\brief Fills Move To Color command structure

\param[out] payload - pointer to command structure;
\param[in]  level   - color level;
\param[in]  time    - transition time
******************************************************************************/
static void colorSceneRemoteFillMoveToLevelPayload(ZCL_MoveToLevel_t *payload, uint8_t level, uint16_t time)
{
  payload->level          = level;
  payload->transitionTime = time;
}

#endif // APP_ZLL_DEVICE_TYPE == APP_DEVICE_TYPE_COLOR_SCENE_REMOTE

// eof colorSceneRemoteLevelControlCluster.c
