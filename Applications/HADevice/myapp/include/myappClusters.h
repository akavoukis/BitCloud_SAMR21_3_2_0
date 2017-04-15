/**************************************************************************//**
  \file dlClusters.h

  \brief
    Dimmable Light clusters interface.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    12.12.12 N. Fomin - Created.
******************************************************************************/
#ifndef _MYAPPCLUSTER_H
#define _MYAPPCLUSTER_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zcl.h>

/******************************************************************************
                    Definitions section
******************************************************************************/
#define DL_SERVER_CLUSTERS_COUNT     6
#ifdef OTAU_CLIENT
  #define DL_CLIENT_CLUSTERS_COUNT   1
#else
  #define DL_CLIENT_CLUSTERS_COUNT   0
#endif
#define DL_SERVER_CLUSTER_INIT_COUNT DL_SERVER_CLUSTERS_COUNT
#define DL_CLIENT_CLUSTER_INIT_COUNT DL_CLIENT_CLUSTERS_COUNT

/******************************************************************************
                    Externals
******************************************************************************/
extern ZCL_Cluster_t dlServerClusters[DL_SERVER_CLUSTERS_COUNT];
extern ClusterId_t dlServerClusterIds[DL_SERVER_CLUSTERS_COUNT];
extern void (*dlServerClusterInitFunctions[DL_SERVER_CLUSTER_INIT_COUNT])();

#ifdef OTAU_CLIENT
extern ZCL_Cluster_t dlClientClusters[DL_CLIENT_CLUSTERS_COUNT];
extern ClusterId_t dlClientClusterIds[DL_CLIENT_CLUSTERS_COUNT];
extern void (*dlClientClusterInitFunctions[DL_CLIENT_CLUSTER_INIT_COUNT])();
#endif

#endif // _DLCLUSTER_H

// eof dlClusters.h
