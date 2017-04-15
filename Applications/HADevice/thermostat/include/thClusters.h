/**************************************************************************//**
  \file thClusters.h

  \brief
    Thermostat clusters interface.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    09/09/2014 Unithra.C  - Created.
******************************************************************************/
#ifndef _THCLUSTERS_H
#define _THCLUSTERS_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zcl.h>

/******************************************************************************
                    Definitions section
******************************************************************************/
#define TH_SERVER_CLUSTERS_COUNT     12
#ifdef OTAU_CLIENT
  #define TH_CLIENT_CLUSTERS_COUNT   5
  #define TH_CLIENT_CLUSTER_INIT_COUNT 1
#else
  #define TH_CLIENT_CLUSTERS_COUNT   4
  #define TH_CLIENT_CLUSTER_INIT_COUNT 0
#endif
#define TH_SERVER_CLUSTER_INIT_COUNT TH_SERVER_CLUSTERS_COUNT

/******************************************************************************
                    Externals
******************************************************************************/
extern ZCL_Cluster_t thServerClusters[TH_SERVER_CLUSTERS_COUNT];
extern ClusterId_t thServerClusterIds[TH_SERVER_CLUSTERS_COUNT];
extern void (*thServerClusterInitFunctions[TH_SERVER_CLUSTER_INIT_COUNT])();

extern ZCL_Cluster_t thClientClusters[TH_CLIENT_CLUSTERS_COUNT];
extern ClusterId_t thClientClusterIds[TH_CLIENT_CLUSTERS_COUNT];
#ifdef OTAU_CLIENT
extern void (*thClientClusterInitFunctions[TH_CLIENT_CLUSTER_INIT_COUNT])();
#endif
#endif // _THCLUSTERS_H

// eof thClusters.h
