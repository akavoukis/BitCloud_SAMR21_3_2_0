/**************************************************************************//**
  \file bridgeClusters.h

  \brief
    Control Bridge device clusters interface.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2013, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    22.01.13 N. Fomin - Created.
******************************************************************************/
#ifndef _BRIDGECLUSTERS_H
#define _BRIDGECLUSTERS_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zcl.h>
#include <commandManager.h>

/******************************************************************************
                    Definitions section
******************************************************************************/
#ifdef OTAU_SERVER
  #define BRIDGE_SERVER_CLUSTERS_COUNT     4
#else
  #define BRIDGE_SERVER_CLUSTERS_COUNT     3
#endif // OTAU_SERVER
#define BRIDGE_CLIENT_CLUSTERS_COUNT     7

/******************************************************************************
                    Externals
******************************************************************************/
extern ZCL_Cluster_t bridgeClientClusters[BRIDGE_CLIENT_CLUSTERS_COUNT];
extern ClusterId_t bridgeClientClusterIds[BRIDGE_CLIENT_CLUSTERS_COUNT];

extern ZCL_Cluster_t bridgeServerClusters[BRIDGE_SERVER_CLUSTERS_COUNT];
extern ClusterId_t bridgeServerClusterIds[BRIDGE_SERVER_CLUSTERS_COUNT];

/******************************************************************************
                    Prototypes section
******************************************************************************/
/**************************************************************************//**
\brief Adds OTAU server cluster to list of server clusters of bridge device.
******************************************************************************/
void bridgeAddOTAUServerCluster(void);

/**************************************************************************//**
\brief Fills zcl addressing structure

\param[out] addressing - pointer to the structure to be filled;
\param[in]  mode       - address mode;
\param[in]  addr       - short address or group id of destination node;
\param[in]  ep         - endpoint number of destination node
******************************************************************************/
void bridgeFillDstAddressing(ZCL_Addressing_t *addressing, APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep);

/**************************************************************************//**
\brief Fills zcl addressing structure

\param[out] cmd     - pointer to the command to be filled;
\param[in]  command - id of a command;
\param[in]  cluster - id of a cluster;
\param[in]  size    - payload size for zcl request
******************************************************************************/
void bridgeFillCommandRequest(CommandDescriptor_t *cmd, ZCL_CommandId_t command, ClusterId_t cluster, uint8_t size);

/**************************************************************************//**
\brief Gets free command buffer

\returns pointer to a command buffer
******************************************************************************/
CommandDescriptor_t *bridgeGetFreeCommand(void);

#endif // _BRIDGECLUSTERS_H

// eof bridgeClusters.h
