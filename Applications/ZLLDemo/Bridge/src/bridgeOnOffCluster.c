/**************************************************************************//**
  \file bridgeOnOffCluster.c

  \brief
    Control Bridge device On/Off cluster implementation.

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
#include <bridgeOnOffCluster.h>
#include <bridgeClusters.h>

/******************************************************************************
                    Global variables
******************************************************************************/
ZCL_OnOffClusterCommands_t onOffClusterCommands =
{
  ZCL_DEFINE_ONOFF_CLUSTER_COMMANDS(NULL, NULL, NULL, NULL, NULL, NULL)
};

/******************************************************************************
                    Implementations
******************************************************************************/
/**************************************************************************//**
\brief Sends On/Off command

\param[in] mode    - address mode;
\param[in] addr    - short address of destination node or number of group;
\param[in] command - 0 - off command, 1 - on command;
\param[in] ep      - endpoint number of destination device
******************************************************************************/
void bridgeSendOnOffCommand(APS_AddrMode_t mode, ShortAddr_t addr, uint8_t command, Endpoint_t ep)
{
  CommandDescriptor_t *cmd;
  ZCL_Addressing_t addressing;

  if (!(cmd = bridgeGetFreeCommand()))
    return;

  bridgeFillCommandRequest(cmd, command, ONOFF_CLUSTER_ID, 0);
  bridgeFillDstAddressing(&addressing, mode, addr, ep);

  clustersSendCommandWithAddressing(cmd, &addressing);
}

#endif // APP_ZLL_DEVICE_TYPE == APP_DEVICE_TYPE_BRIDGE

// eof bridgeOnOffCluster.c
