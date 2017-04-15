/**************************************************************************//**
  \file msClusters.c

  \brief
    Multi-Sensor clusters implementation.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    12.12.12 N. Fomin - Created.
    28.05.14 Viswanadham Kotla - Modified.
******************************************************************************/

#ifdef APP_DEVICE_TYPE_MULTI_SENSOR
/******************************************************************************
                    Includes section
******************************************************************************/
#include <msClusters.h>
#include <basicCluster.h>
#include <identifyCluster.h>
#include <msOccupancySensingCluster.h>
#include <msTemperatureMeasurementCluster.h>
#include <msHumidityMeasurementCluster.h>
#include <msilluminanceMeasurementCluster.h>
#include <msBasicCluster.h>
#include <msIdentifyCluster.h>
#include <msDiagnosticsCluster.h>

/******************************************************************************
                    Global variables
******************************************************************************/
ZCL_Cluster_t msServerClusters[MS_SERVER_CLUSTERS_COUNT] =
{
  ZCL_DEFINE_BASIC_CLUSTER_SERVER(&msBasicClusterServerAttributes, &msBasicClusterServerCommands),
  DEFINE_IDENTIFY_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &msIdentifyClusterServerAttributes, &msIdentifyCommands),
  DEFINE_DIAGNOSTICS_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &msDiagnosticsClusterServerAttributes, NULL),
};

void (*msServerClusterInitFunctions[MS_SERVER_CLUSTER_INIT_COUNT])() =
{
  basicClusterInit,
  identifyClusterInit,
  diagnosticsClusterInit
#ifdef APP_SENSOR_TYPE_OCCUPANCY_SENSOR
  ,occupancySensingClusterInit
#endif
#ifdef APP_SENSOR_TYPE_TEMPERATURE_SENSOR
  ,temperatureMeasurementClusterInit
#endif
#ifdef APP_SENSOR_TYPE_HUMIDITY_SENSOR
  ,humidityMeasurementClusterInit
#endif
#ifdef APP_SENSOR_TYPE_LIGHT_SENSOR
  ,illuminanceMeasurementClusterInit
#endif  
};

ZCL_Cluster_t msClientClusters[MS_CLIENT_CLUSTERS_COUNT] =
{
  DEFINE_IDENTIFY_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, NULL, &msIdentifyCommands)
};

ClusterId_t msClientClusterIds[MS_CLIENT_CLUSTERS_COUNT] =
{
  IDENTIFY_CLUSTER_ID,
#ifdef OTAU_CLIENT
  OTAU_CLUSTER_ID, // Always should be on last position in list of clusters ID.
#endif
};

#ifdef OTAU_CLIENT
void (*msClientClusterInitFunctions[MS_CLIENT_CLUSTER_INIT_COUNT])() =
{
  NULL // needs to add otau client init
};
#endif

ClusterId_t msServerClusterIds[MS_SERVER_CLUSTERS_COUNT] =
{
  BASIC_CLUSTER_ID,
  IDENTIFY_CLUSTER_ID,
  DIAGNOSTICS_CLUSTER_ID
};


#ifdef APP_SENSOR_TYPE_OCCUPANCY_SENSOR
ZCL_Cluster_t osServerClusters[OS_SERVER_CLUSTERS_COUNT] =
{
  DEFINE_OCCUPANCY_SENSING_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &osOccupancySensingClusterServerAttributes, NULL),
};

ClusterId_t osServerClusterIds[OS_SERVER_CLUSTERS_COUNT] =
{
  OCCUPANCY_SENSING_CLUSTER_ID,
};

#endif //APP_SENSOR_TYPE_OCCUPANCY_SENSOR

#ifdef APP_SENSOR_TYPE_TEMPERATURE_SENSOR
ZCL_Cluster_t tsServerClusters[TS_SERVER_CLUSTERS_COUNT] =
{
  DEFINE_TEMPERATURE_MEASUREMENT_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &tsTemperatureMeasurementClusterServerAttributes)
};

ClusterId_t tsServerClusterIds[TS_SERVER_CLUSTERS_COUNT] =
{
  TEMPERATURE_MEASUREMENT_CLUSTER_ID,
};

#endif //APP_SENSOR_TYPE_TEMPERATURE_SENSOR

#ifdef APP_SENSOR_TYPE_HUMIDITY_SENSOR
ZCL_Cluster_t hsServerClusters[HS_SERVER_CLUSTERS_COUNT] =
{
  DEFINE_HUMIDITY_MEASUREMENT_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &hsHumidityMeasurementClusterServerAttributes)
};

ClusterId_t hsServerClusterIds[HS_SERVER_CLUSTERS_COUNT] =
{
  HUMIDITY_MEASUREMENT_CLUSTER_ID,
};

#endif //APP_SENSOR_TYPE_HUMIDITY_SENSOR

#ifdef APP_SENSOR_TYPE_LIGHT_SENSOR
ZCL_Cluster_t lsServerClusters[LS_SERVER_CLUSTERS_COUNT] =
{
  DEFINE_ILLUMINANCE_MEASUREMENT_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &msIlluminanceMeasurementClusterServerAttributes),
};

ClusterId_t lsServerClusterIds[LS_SERVER_CLUSTERS_COUNT] =
{
  ILLUMINANCE_MEASUREMENT_CLUSTER_ID,
};

#endif //APP_SENSOR_TYPE_LIGHT_SENSOR

#endif // APP_DEVICE_TYPE_MULTI_SENSOR

// eof msClusters.c
