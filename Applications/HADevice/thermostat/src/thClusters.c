/**************************************************************************//**
  \file thClusters.c

  \brief
    Thermostat clusters implementation.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    09/09/2014 Unithra.C - Created.
******************************************************************************/

#ifdef APP_DEVICE_TYPE_THERMOSTAT
/******************************************************************************
                    Includes section
******************************************************************************/
#include <thClusters.h>
#include <basicCluster.h>
#include <identifyCluster.h>
#include <thBasicCluster.h>
#include <thIdentifyCluster.h>
#include <thThermostatCluster.h>
#include <thThermostatUiConfCluster.h>
#include <thOccupancySensingCluster.h>
#include <thFanControlCluster.h>
#include <thDiagnosticsCluster.h>
#include <thTimeCluster.h>
#include <thAlarmsCluster.h>
#include <thHumidityMeasurementCluster.h>
#include <thGroupsCluster.h>
#include <thScenesCluster.h>
#include <thTemperatureMeasurementCluster.h>

/******************************************************************************
                    Global variables
******************************************************************************/
ZCL_Cluster_t thServerClusters[TH_SERVER_CLUSTERS_COUNT] =
{
  ZCL_DEFINE_BASIC_CLUSTER_SERVER(&thBasicClusterServerAttributes, &thBasicClusterServerCommands),
  DEFINE_IDENTIFY_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &thIdentifyClusterServerAttributes, &thIdentifyCommands),
  DEFINE_THERMOSTAT_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &thThermostatClusterServerAttributes, &thThermostatClusterServerCommands),
  DEFINE_THERMOSTAT_UI_CONF_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &thThermostatUiConfClusterServerAttributes, NULL),
  DEFINE_OCCUPANCY_SENSING_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &thOccupancySensingClusterServerAttributes, NULL),
  DEFINE_DIAGNOSTICS_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &thDiagnosticsClusterServerAttributes, NULL),
  DEFINE_ALARMS_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &thAlarmsClusterServerAttributes, &thAlarmsClusterServerCommands),
  DEFINE_HUMIDITY_MEASUREMENT_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &thHumidityMeasurementClusterServerAttributes),
  DEFINE_FAN_CONTROL_CLUSTER(ZCL_SERVER_CLUSTER_TYPE,&thFanControlClusterServerAttributes,NULL),
  DEFINE_GROUPS_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &thGroupsClusterServerAttributes, &thGroupsCommands),
  DEFINE_SCENES_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &thScenesClusterServerAttributes, &thScenesCommands),
  DEFINE_TEMPERATURE_MEASUREMENT_CLUSTER(ZCL_SERVER_CLUSTER_TYPE,&thTemperatureMeasurementClusterServerAttributes),
};

void (*thServerClusterInitFunctions[TH_SERVER_CLUSTER_INIT_COUNT])() =
{
  basicClusterInit,
  identifyClusterInit,
  thermostatClusterInit,
  thermostatUiConfClusterInit,
  occupancySensingClusterInit,
  diagnosticsClusterInit,
  alarmsClusterInit,
  humidityMeasurementClusterInit,
  fanControlClusterInit,
  groupsClusterInit,
  scenesClusterInit,
  thTemperatureMeasurementClusterInit,
};

ClusterId_t thServerClusterIds[TH_SERVER_CLUSTERS_COUNT] =
{
  BASIC_CLUSTER_ID,
  IDENTIFY_CLUSTER_ID,
  THERMOSTAT_CLUSTER_ID,
  THERMOSTAT_UI_CONF_CLUSTER_ID,
  OCCUPANCY_SENSING_CLUSTER_ID,
  DIAGNOSTICS_CLUSTER_ID,
  ALARMS_CLUSTER_ID,
  HUMIDITY_MEASUREMENT_CLUSTER_ID,
  FAN_CONTROL_CLUSTER_ID,
  GROUPS_CLUSTER_ID,
  SCENES_CLUSTER_ID,
  TEMPERATURE_MEASUREMENT_CLUSTER_ID,
};


ZCL_Cluster_t thClientClusters[TH_CLIENT_CLUSTERS_COUNT] = 
{
  DEFINE_OCCUPANCY_SENSING_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, NULL, NULL),
  DEFINE_TIME_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, NULL, NULL),
  DEFINE_HUMIDITY_MEASUREMENT_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, NULL),
  DEFINE_TEMPERATURE_MEASUREMENT_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, NULL),
};

ClusterId_t thClientClusterIds[TH_CLIENT_CLUSTERS_COUNT] =
{
  OCCUPANCY_SENSING_CLUSTER_ID,
  TIME_CLUSTER_ID,
  HUMIDITY_MEASUREMENT_CLUSTER_ID,
  TEMPERATURE_MEASUREMENT_CLUSTER_ID,
#ifdef OTAU_CLIENT
  OTAU_CLUSTER_ID, // Always should be on last position in list of clusters ID.
#endif
};

#ifdef OTAU_CLIENT
void (*thClientClusterInitFunctions[TH_CLIENT_CLUSTER_INIT_COUNT])() =
{
  NULL // need to call otau client init function
};
#endif

#endif // APP_DEVICE_TYPE_THERMOSTAT

// eof thClusters.c
