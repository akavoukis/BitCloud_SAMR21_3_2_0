/**************************************************************************//**
  \file bridgeLevelControlCluster.c

  \brief
    Control Bridge device Level Control cluster implementation.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2013, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    22.01.13 N. Fomin - Created.
******************************************************************************/

#if APP_ZLL_DEVICE_TYPE == APP_DEVICE_TYPE_BRIDGE

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zcl.h>
#include <clusters.h>
#include <commandManager.h>
#include <bridgeLevelControlCluster.h>
#include <bridgeClusters.h>

/******************************************************************************
                    Global variables section
******************************************************************************/
ZCL_LevelControlClusterCommands_t levelControlClusterCommands =
{
  ZCL_DEFINE_LEVEL_CONTROL_CLUSTER_COMMANDS(NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL)
};

static void bridgeFillMoveToLevelPayload(ZCL_MoveToLevel_t *payload, uint8_t level, uint16_t time);
static void bridgeFillStepLevelPayload(ZCL_Step_t *payload, uint8_t mode, uint8_t size, uint16_t time);

/******************************************************************************
                    Implementations section
******************************************************************************/
/**************************************************************************//**
\brief Sends Move To Level command

\param[in] mode  - address mode;
\param[in] addr  - short address of destination node or number of group;
\param[in] level - color level;
\param[in] time  - transition time;
\param[in] ep    - endpoint number of destination device
******************************************************************************/
void bridgeSendMoveToLevelCommand(APS_AddrMode_t mode, ShortAddr_t addr, uint8_t level, uint16_t time, Endpoint_t ep)
{
  CommandDescriptor_t *cmd;
  ZCL_Addressing_t addressing;

  if (!(cmd = bridgeGetFreeCommand()))
    return;

  bridgeFillCommandRequest(cmd, ZCL_LEVEL_CONTROL_CLUSTER_MOVE_TO_LEVEL_COMMAND_ID,
                                     LEVEL_CONTROL_CLUSTER_ID, sizeof(cmd->payload.moveToLevel));
  bridgeFillMoveToLevelPayload(&cmd->payload.moveToLevel, level, time);
  bridgeFillDstAddressing(&addressing, mode, addr, ep);

  clustersSendCommandWithAddressing(cmd, &addressing);
}

/**************************************************************************//**
\brief Sends Step Level command

\param[in] addrMode - address mode;
\param[in] addr     - short address of destination node or number of group;
\param[in] ep       - endpoint number of destination device;
\param[in] mode     - step mode;
\param[in] size     - step size;
\param[in] time     - transition time
******************************************************************************/
void bridgeSendStepLevelCommand(APS_AddrMode_t addrMode, ShortAddr_t addr, Endpoint_t ep, uint8_t mode, uint8_t size, uint16_t time)
{
  CommandDescriptor_t *cmd;
  ZCL_Addressing_t addressing;

  if (!(cmd = bridgeGetFreeCommand()))
    return;

  bridgeFillCommandRequest(cmd, ZCL_LEVEL_CONTROL_CLUSTER_STEP_COMMAND_ID,
                                     LEVEL_CONTROL_CLUSTER_ID, sizeof(cmd->payload.stepLevel));
  bridgeFillStepLevelPayload(&cmd->payload.stepLevel, mode, size, time);
  bridgeFillDstAddressing(&addressing, addrMode, addr, ep);

  clustersSendCommandWithAddressing(cmd, &addressing);
}

/**************************************************************************//**
\brief Fills Move To Color command structure

\param[out] payload - pointer to command structure;
\param[in]  level   - color level;
\param[in]  time    - transition time
******************************************************************************/
static void bridgeFillMoveToLevelPayload(ZCL_MoveToLevel_t *payload, uint8_t level, uint16_t time)
{
  payload->level          = level;
  payload->transitionTime = time;
}

/**************************************************************************//**
\brief Fills Step Color command structure

\param[out] payload - pointer to command structure;
\param[in] mode     - step mode;
\param[in] size     - step size;
\param[in] time     - transition time
******************************************************************************/
static void bridgeFillStepLevelPayload(ZCL_Step_t *payload, uint8_t mode, uint8_t size, uint16_t time)
{
  payload->stepMode       = mode;
  payload->stepSize       = size;
  payload->transitionTime = time;
}

#endif // APP_ZLL_DEVICE_TYPE == APP_DEVICE_TYPE_BRIDGE

// eof bridgeLevelControlCluster.c
