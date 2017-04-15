/**************************************************************************//**
  \file dsClusters.h

  \brief
    Dimmer Switch clusters interface.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    12.12.12 N. Fomin - Created.
******************************************************************************/
#ifndef _DSCLUSTER_H
#define _DSCLUSTER_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zcl.h>

/******************************************************************************
                    Definitions section
******************************************************************************/
#define DS_SERVER_CLUSTERS_COUNT     4
#ifdef OTAU_CLIENT
  #define DS_CLIENT_CLUSTERS_COUNT   4
  #define DS_CLIENT_CLUSTER_INIT_COUNT 1
#else
  #define DS_CLIENT_CLUSTERS_COUNT   3
  #define DS_CLIENT_CLUSTER_INIT_COUNT 0
#endif
#define DS_SERVER_CLUSTER_INIT_COUNT DS_SERVER_CLUSTERS_COUNT

/******************************************************************************
                    Types section
******************************************************************************/
typedef void (*AttibuteReadCallback_t)(void *data);
typedef void (*AttributeWriteCallback_t)(void);

/******************************************************************************
                    Externals
******************************************************************************/
extern ZCL_Cluster_t dsServerClusters[DS_SERVER_CLUSTERS_COUNT];
extern ZCL_Cluster_t dsClientClusters[DS_CLIENT_CLUSTERS_COUNT];

extern void (*dsServerClusterInitFunctions[DS_SERVER_CLUSTER_INIT_COUNT])();
#ifdef OTAU_CLIENT
extern void (*dsClientClusterInitFunctions[DS_CLIENT_CLUSTER_INIT_COUNT])();
#endif

extern ClusterId_t   dsServerClusterIds[DS_SERVER_CLUSTERS_COUNT];
extern ClusterId_t   dsClientClusterIds[DS_CLIENT_CLUSTERS_COUNT];

#endif // _DSCLUSTER_H

// eof dsClusters.h
