/**************************************************************************//**
  \file msClusters.h

  \brief
    Multi-Sensor clusters interface.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    12.12.12 N. Fomin - Created.
    28.05.14 Viswanadham Kotla- Modified.
******************************************************************************/
#ifndef _MSCLUSTER_H
#define _MSCLUSTER_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zcl.h>

/******************************************************************************
                    Definitions section
******************************************************************************/

#ifdef APP_SENSOR_TYPE_OCCUPANCY_SENSOR
#define OS_SERVER_CLUSTERS_COUNT     1
#else
#define OS_SERVER_CLUSTERS_COUNT     0
#endif

#ifdef APP_SENSOR_TYPE_TEMPERATURE_SENSOR
#define TS_SERVER_CLUSTERS_COUNT     1
#else
#define TS_SERVER_CLUSTERS_COUNT     0
#endif

#ifdef APP_SENSOR_TYPE_HUMIDITY_SENSOR
#define HS_SERVER_CLUSTERS_COUNT     1
#else
#define HS_SERVER_CLUSTERS_COUNT     0
#endif

#ifdef APP_SENSOR_TYPE_LIGHT_SENSOR
#define LS_SERVER_CLUSTERS_COUNT     1
#else
#define LS_SERVER_CLUSTERS_COUNT     0
#endif


#define MS_SERVER_CLUSTERS_COUNT     (3 + OS_SERVER_CLUSTERS_COUNT + TS_SERVER_CLUSTERS_COUNT + HS_SERVER_CLUSTERS_COUNT + LS_SERVER_CLUSTERS_COUNT)
#define MS_SERVER_CLUSTER_INIT_COUNT MS_SERVER_CLUSTERS_COUNT

#define OS_CLIENT_CLUSTERS_COUNT   0
#define TS_CLIENT_CLUSTERS_COUNT   0
#define HS_CLIENT_CLUSTERS_COUNT   0
#define LS_CLIENT_CLUSTERS_COUNT   0

#ifdef OTAU_CLIENT
  #define MS_CLIENT_CLUSTERS_COUNT   (2 + OS_CLIENT_CLUSTERS_COUNT + TS_CLIENT_CLUSTERS_COUNT + HS_CLIENT_CLUSTERS_COUNT + LS_CLIENT_CLUSTERS_COUNT)//identify, OTAU
  #define MS_CLIENT_CLUSTER_INIT_COUNT 1
#else
  #define MS_CLIENT_CLUSTERS_COUNT   1
  #define MS_CLIENT_CLUSTER_INIT_COUNT 0
#endif

/******************************************************************************
                    Externals
******************************************************************************/

extern ZCL_Cluster_t msServerClusters[MS_SERVER_CLUSTERS_COUNT];
extern ClusterId_t   msServerClusterIds[MS_SERVER_CLUSTERS_COUNT];
extern void (*msServerClusterInitFunctions[MS_SERVER_CLUSTER_INIT_COUNT])();
#ifdef OTAU_CLIENT
extern void (*msClientClusterInitFunctions[MS_CLIENT_CLUSTER_INIT_COUNT])();
#endif
extern ZCL_Cluster_t msClientClusters[MS_CLIENT_CLUSTERS_COUNT];
extern ClusterId_t   msClientClusterIds[MS_CLIENT_CLUSTERS_COUNT];



#ifdef APP_SENSOR_TYPE_OCCUPANCY_SENSOR

extern ZCL_Cluster_t osServerClusters[OS_SERVER_CLUSTERS_COUNT];
extern ClusterId_t   osServerClusterIds[OS_SERVER_CLUSTERS_COUNT];

extern ZCL_Cluster_t osClientClusters;
extern ClusterId_t   osClientClusterIds;

#endif

#ifdef APP_SENSOR_TYPE_TEMPERATURE_SENSOR

extern ZCL_Cluster_t tsServerClusters[TS_SERVER_CLUSTERS_COUNT];
extern ClusterId_t   tsServerClusterIds[TS_SERVER_CLUSTERS_COUNT];

extern ZCL_Cluster_t tsClientClusters;
extern ClusterId_t   tsClientClusterIds;

#endif

#ifdef APP_SENSOR_TYPE_HUMIDITY_SENSOR

extern ZCL_Cluster_t hsServerClusters[HS_SERVER_CLUSTERS_COUNT];
extern ClusterId_t   hsServerClusterIds[HS_SERVER_CLUSTERS_COUNT];

extern ZCL_Cluster_t hsClientClusters;
extern ClusterId_t   hsClientClusterIds;

#endif

#ifdef APP_SENSOR_TYPE_LIGHT_SENSOR

extern ZCL_Cluster_t lsServerClusters[LS_SERVER_CLUSTERS_COUNT];
extern ClusterId_t   lsServerClusterIds[LS_SERVER_CLUSTERS_COUNT];

extern ZCL_Cluster_t lsClientClusters;
extern ClusterId_t   lsClientClusterIds;

#endif

#endif // _MSCLUSTER_H

// eof msClusters.h
