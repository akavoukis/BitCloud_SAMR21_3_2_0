/**************************************************************************//**
  \file lightClusters.h

  \brief
    Light device clusters interface.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    28.06.11 A. Taradov - Created.
******************************************************************************/
#ifndef _LIGHTCLUSTERS_H
#define _LIGHTCLUSTERS_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zcl.h>

/******************************************************************************
                    Definitions section
******************************************************************************/
#if APP_ZLL_DEVICE_TYPE < APP_DEVICE_TYPE_ON_OFF_LIGHT
  #define LIGHT_SERVER_CLUSTERS_COUNT     6
#elif APP_ZLL_DEVICE_TYPE < APP_DEVICE_TYPE_COLOR_LIGHT
  #define LIGHT_SERVER_CLUSTERS_COUNT     7
#else
  #define LIGHT_SERVER_CLUSTERS_COUNT     8
#endif // APP_ZLL_DEVICE_TYPE >= APP_DEVICE_TYPE_COLOR_LIGHT

#ifdef OTAU_CLIENT
  #define LIGHT_CLIENT_CLUSTERS_COUNT     2
#else
  #define LIGHT_CLIENT_CLUSTERS_COUNT     1
#endif //APP_ZLL_DEVICE_TYPE < APP_DEVICE_TYPE_ON_OFF_LIGH
/******************************************************************************
                    Externals
******************************************************************************/
extern ZCL_Cluster_t lightServerClusters[LIGHT_SERVER_CLUSTERS_COUNT];
extern ClusterId_t lightServerClusterIds[LIGHT_SERVER_CLUSTERS_COUNT];

extern ZCL_Cluster_t lightClientClusters[LIGHT_CLIENT_CLUSTERS_COUNT];
extern ClusterId_t lightClientClusterIds[LIGHT_CLIENT_CLUSTERS_COUNT];
/******************************************************************************
                    Prototypes
******************************************************************************/
/**************************************************************************//**
\brief Adds OTAU client cluster to list of clients clusters of light device.
******************************************************************************/
void lightAddOTAUClientCluster(void);

#endif // _LIGHTCLUSTERS_H

// eof lightClusters.h
