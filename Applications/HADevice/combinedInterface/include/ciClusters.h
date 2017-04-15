/**************************************************************************//**
  \file ciClusters.h

  \brief
    Combined Interface clusters interface.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2013, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    03.09.13 N. Fomin - Created.
******************************************************************************/
#ifndef _CICLUSTER_H
#define _CICLUSTER_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zcl.h>

/******************************************************************************
                    Definitions section
******************************************************************************/
#ifdef OTAU_SERVER
  #define CI_SERVER_CLUSTERS_COUNT     5
  #define CI_SERVER_CLUSTER_INIT_COUNT (CI_SERVER_CLUSTERS_COUNT - 1)
#else
  #define CI_SERVER_CLUSTERS_COUNT     4
  #define CI_SERVER_CLUSTER_INIT_COUNT CI_SERVER_CLUSTERS_COUNT
#endif

#define CI_CLIENT_CLUSTER_INIT_COUNT 0
#define CI_CLIENT_CLUSTERS_COUNT     17

/******************************************************************************
                    Externals
******************************************************************************/
extern ZCL_Cluster_t ciServerClusters[CI_SERVER_CLUSTERS_COUNT];
extern ZCL_Cluster_t ciClientClusters[CI_CLIENT_CLUSTERS_COUNT];
extern void (*ciServerClusterInitFunctions[CI_SERVER_CLUSTER_INIT_COUNT])();

extern ClusterId_t   ciServerClusterIds[CI_SERVER_CLUSTERS_COUNT];
extern ClusterId_t   ciClientClusterIds[CI_CLIENT_CLUSTERS_COUNT];

#endif // _CICLUSTER_H

// eof ciClusters.h
