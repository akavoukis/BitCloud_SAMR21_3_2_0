/**************************************************************************//**
  \file bridgeIdentifyCluster.c

  \brief
    Control Bridge device Identify cluster implementation.

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
                    Includes
******************************************************************************/
#include <commandManager.h>
#include <bridgeIdentifyCluster.h>
#include <bridgeClusters.h>

/******************************************************************************
                    Definitions section
******************************************************************************/
#define IDENTIFY_TIME 5

/******************************************************************************
                    Global variables section
******************************************************************************/
ZCL_IdentifyClusterCommands_t identifyClusterCommands =
{
  ZCL_IDENTIFY_CLUSTER_COMMANDS(NULL, NULL, NULL, NULL)
};

/******************************************************************************
                    Prototypes section
******************************************************************************/
static void bridgeFillIdentifyPayload(ZCL_Identify_t *payload, uint16_t time);

/******************************************************************************
                    Implementation section
******************************************************************************/
/**************************************************************************//**
\brief Sends Identify command

\param[in] mode  - address mode;
\param[in] addr  - short address of destination node or number of group;
\param[in] ep    - endpoint number of destination device
******************************************************************************/
void bridgeSendIdentifyCommand(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep)
{
  CommandDescriptor_t *cmd;
  ZCL_Addressing_t addressing;

  if (!(cmd = bridgeGetFreeCommand()))
    return;

  bridgeFillCommandRequest(cmd, ZCL_IDENTIFY_CLUSTER_IDENTIFY_COMMAND_ID,
                                     IDENTIFY_CLUSTER_ID, sizeof(cmd->payload.identify));
  bridgeFillIdentifyPayload(&cmd->payload.identify, IDENTIFY_TIME);
  bridgeFillDstAddressing(&addressing, mode, addr, ep);

  clustersSendCommandWithAddressing(cmd, &addressing);
}

/**************************************************************************//**
\brief Fills Identify command structure

\param[out] payload - pointer to command structure;
\param[in]  time    - identify time
******************************************************************************/
static void bridgeFillIdentifyPayload(ZCL_Identify_t *payload, uint16_t time)
{
  payload->identifyTime = time;
}

#endif // APP_ZLL_DEVICE_TYPE == APP_DEVICE_TYPE_BRIDGE

// eof bridgeIdentifyCluster.c
