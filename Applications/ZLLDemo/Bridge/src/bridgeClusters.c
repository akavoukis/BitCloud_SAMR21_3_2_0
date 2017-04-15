/**************************************************************************//**
  \file bridgeClusters.c

  \brief
    Control Bridge device clusters implementation.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
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
#include <bridgeClusters.h>
#include <bridgeBasicCluster.h>
#include <bridgeIdentifyCluster.h>
#include <bridgeOnOffCluster.h>
#include <bridgeLevelControlCluster.h>
#include <bridgeGroupsCluster.h>
#include <bridgeCommissioningCluster.h>
#include <bridgeScenesCluster.h>
#include <bridgeColorControlCluster.h>
#include <bridgeLinkInfocluster.h>
#include <uartManager.h>
#include <zllDemo.h>

/******************************************************************************
                    Global variables
******************************************************************************/
ZCL_Cluster_t bridgeClientClusters[BRIDGE_CLIENT_CLUSTERS_COUNT] =
{
  DEFINE_COMMISSIONING_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE,
      NULL, &commissioningClusterCommands),
  DEFINE_IDENTIFY_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, NULL, &identifyClusterCommands),
  DEFINE_ONOFF_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, NULL, &onOffClusterCommands),
  DEFINE_LEVEL_CONTROL_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, NULL, &levelControlClusterCommands),
  DEFINE_GROUPS_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, NULL, &groupsClusterCommands),
  DEFINE_SCENES_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE,
      NULL, &scenesClusterCommands),
  DEFINE_COLOR_CONTROL_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, NULL, &colorControlClusterCommands),
};

ClusterId_t bridgeClientClusterIds[BRIDGE_CLIENT_CLUSTERS_COUNT] =
{
  ZLL_COMMISSIONING_CLUSTER_ID,
  IDENTIFY_CLUSTER_ID,
  ONOFF_CLUSTER_ID,
  LEVEL_CONTROL_CLUSTER_ID,
  GROUPS_CLUSTER_ID,
  SCENES_CLUSTER_ID,
  COLOR_CONTROL_CLUSTER_ID,
};

ZCL_Cluster_t bridgeServerClusters[BRIDGE_SERVER_CLUSTERS_COUNT] =
{
  ZCL_DEFINE_BASIC_CLUSTER_SERVER(&basicClusterServerAttributes),
  DEFINE_COMMISSIONING_CLUSTER(ZCL_SERVER_CLUSTER_TYPE,
      NULL, &commissioningClusterCommands),
  DEFINE_LINK_INFO_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, NULL, &linkInfoCommands)
};

ClusterId_t bridgeServerClusterIds[BRIDGE_SERVER_CLUSTERS_COUNT] =
{
  BASIC_CLUSTER_ID,
  ZLL_COMMISSIONING_CLUSTER_ID,
  LINK_INFO_CLUSTER_ID,
#ifdef OTAU_SERVER
  OTAU_CLUSTER_ID, // Always should be on last position in list of clusters ID.
#endif // OTAU_SERVER
};

/******************************************************************************
                    Implementations section
******************************************************************************/
/**************************************************************************//**
\brief Adds OTAU server cluster to list of server clusters of bridge device.
******************************************************************************/
void bridgeAddOTAUServerCluster(void)
{
#ifdef OTAU_SERVER
  bridgeServerClusters[BRIDGE_SERVER_CLUSTERS_COUNT - 1U] = ZCL_GetOtauServerCluster();
#endif // OTAU_SERVER
}
/**************************************************************************//**
\brief Fills zcl addressing structure

\param[out] addressing - pointer to the structure to be filled;
\param[in]  mode       - address mode;
\param[in]  addr       - short address or group id of destination node;
\param[in]  ep         - endpoint number of destination node
******************************************************************************/
void bridgeFillDstAddressing(ZCL_Addressing_t *addressing, APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep)
{
  addressing->addrMode             = mode;
  addressing->addr.shortAddress    = addr;
  addressing->profileId            = APP_PROFILE_ID;
  addressing->clusterSide          = ZCL_CLUSTER_SIDE_SERVER;
  addressing->endpointId           = ep;
  addressing->manufacturerSpecCode = 0;
  addressing->sequenceNumber       = ZCL_GetNextSeqNumber();
}

/**************************************************************************//**
\brief Fills zcl addressing structure

\param[out] cmd     - pointer to the command to be filled;
\param[in]  command - id of a command;
\param[in]  cluster - id of a cluster;
\param[in]  size    - payload size for zcl request
******************************************************************************/
void bridgeFillCommandRequest(CommandDescriptor_t *cmd, ZCL_CommandId_t command, ClusterId_t cluster, uint8_t size)
{
  cmd->clusterId          = cluster;
  cmd->commandId          = command;
  cmd->disableDefaultResp = true;
  cmd->srcEndpoint        = APP_ENDPOINT_BRIDGE;
  cmd->size               = size;
}

/**************************************************************************//**
\brief Gets free command buffer

\returns pointer to a command buffer
******************************************************************************/
CommandDescriptor_t *bridgeGetFreeCommand(void)
{
  CommandDescriptor_t *cmd;

  if (!(cmd = clustersAllocCommand()))
  {
    LOG_STRING(insufficientBuffersAmountStr, "\r\nNot enough command buffers\r\n");
    appSnprintf(insufficientBuffersAmountStr);
    return NULL;
  }
  return cmd;
}

#endif // APP_ZLL_DEVICE_TYPE == APP_DEVICE_TYPE_BRIDGE

// eof bridgeClusters.c
