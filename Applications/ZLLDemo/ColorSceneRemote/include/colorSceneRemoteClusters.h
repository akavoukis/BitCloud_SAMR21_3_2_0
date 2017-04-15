/**************************************************************************//**
  \file colorSceneRemoteClusters.h

  \brief
    Color Scene Remote device clusters interface.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    28.06.11 A. Taradov - Created.
******************************************************************************/
#ifndef _COLORSCENEREMOTECLUSTERS_H
#define _COLORSCENEREMOTECLUSTERS_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zcl.h>
#include <commandManager.h>

/******************************************************************************
                    Definitions section
******************************************************************************/
#define COLOR_SCENE_REMOTE_SERVER_CLUSTERS_COUNT     2
#ifdef OTAU_CLIENT
  #define COLOR_SCENE_REMOTE_CLIENT_CLUSTERS_COUNT     10
#else
  #define COLOR_SCENE_REMOTE_CLIENT_CLUSTERS_COUNT     9
#endif // OTAU_CLIENT


/******************************************************************************
                    Externals
******************************************************************************/
extern ZCL_Cluster_t colorSceneRemoteClientClusters[COLOR_SCENE_REMOTE_CLIENT_CLUSTERS_COUNT];
extern ClusterId_t colorSceneRemoteClientClusterIds[COLOR_SCENE_REMOTE_CLIENT_CLUSTERS_COUNT];

extern ZCL_Cluster_t colorSceneRemoteServerClusters[COLOR_SCENE_REMOTE_SERVER_CLUSTERS_COUNT];
extern ClusterId_t colorSceneRemoteServerClusterIds[COLOR_SCENE_REMOTE_SERVER_CLUSTERS_COUNT];

/******************************************************************************
                    Prototypes section
******************************************************************************/
/**************************************************************************//**
\brief Adds OTAU client cluster to list of clients clusters of color 
       scene remote device.
******************************************************************************/
void colorSceneRemoteAddOTAUClientCluster(void);

/**************************************************************************//**
\brief Fills zcl addressing structure

\param[out] addressing - pointer to the structure to be filled;
\param[in]  mode       - address mode;
\param[in]  addr       - short address or group id of destination node;
\param[in]  ep         - endpoint number of destination node
******************************************************************************/
void colorSceneRemoteFillDstAddressing(ZCL_Addressing_t *addressing, APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep);

/**************************************************************************//**
\brief Fills zcl addressing structure

\param[out] cmd     - pointer to the command to be filled;
\param[in]  command - id of a command;
\param[in]  cluster - id of a cluster;
\param[in]  size    - payload size for zcl request
******************************************************************************/
void colorSceneRemoteFillCommandRequest(CommandDescriptor_t *cmd, ZCL_CommandId_t command, ClusterId_t cluster, uint8_t size);

/**************************************************************************//**
\brief Gets free command buffer

\returns pointer to a command buffer
******************************************************************************/
CommandDescriptor_t *colorSceneRemoteGetFreeCommand(void);

#endif // _COLORSCENEREMOTECLUSTERS_H

// eof colorSceneRemoteClusters.h
