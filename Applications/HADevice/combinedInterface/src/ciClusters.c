/**************************************************************************//**
  \file ciClusters.c

  \brief
    Combined Interface clusters implementation.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2013, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    03.09.13 N. Fomin - Created.
******************************************************************************/

#ifdef APP_DEVICE_TYPE_COMBINED_INTERFACE
/******************************************************************************
                    Includes section
******************************************************************************/
#include <haClusters.h>
#include <ciClusters.h>
#include <basicCluster.h>
#include <identifyCluster.h>
#include <ciBasicCluster.h>
#include <ciIdentifyCluster.h>
#include <ciOnOffCluster.h>
#include <ciLevelControlCluster.h>
#include <ciGroupsCluster.h>
#include <ciScenesCluster.h>
#include <ciOccupancySensingCluster.h>
#include <ciTemperatureMeasurementCluster.h>
#include <ciHumidityMeasurementCluster.h>
#include <ciIlluminanceMeasurementCluster.h>
#include <ciThermostatCluster.h>
#include <ciThermostatUiConfCluster.h>
#include <ciDiagnosticsCluster.h>
#include <ciFanControlCluster.h>
#include <ciPowerConfigurationCluster.h>
#include <ciTimeCluster.h>
#include <ciAlarmsCluster.h>
#include <ciIasZoneCluster.h>
#include <ciIasACECluster.h>


/******************************************************************************
                    Global variables
******************************************************************************/
ZCL_Cluster_t ciServerClusters[CI_SERVER_CLUSTERS_COUNT] =
{
  ZCL_DEFINE_BASIC_CLUSTER_SERVER(&ciBasicClusterServerAttributes, &ciBasicClusterServerCommands),
  DEFINE_IDENTIFY_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &ciIdentifyClusterServerAttributes, &ciIdentifyCommands),
  DEFINE_TIME_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &ciTimeClusterServerAttributes, NULL),
  DEFINE_IAS_ACE_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, NULL, &ciIASACEClusterCommands),
};

void (*ciServerClusterInitFunctions[CI_SERVER_CLUSTER_INIT_COUNT])() =
{
  basicClusterInit,
  identifyClusterInit,
  timeClusterInit,
  iasACEClusterInit
};

ZCL_Cluster_t ciClientClusters[CI_CLIENT_CLUSTERS_COUNT] =
{
  ZCL_DEFINE_BASIC_CLUSTER_CLIENT(),
  DEFINE_IDENTIFY_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, NULL, &ciIdentifyCommands),
  DEFINE_ONOFF_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, NULL, &ciOnOffCommands),
  DEFINE_LEVEL_CONTROL_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, NULL, &ciLevelControlCommands),
  DEFINE_GROUPS_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, NULL, &ciGroupsCommands),
  DEFINE_SCENES_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, NULL, &ciScenesCommands),
  DEFINE_OCCUPANCY_SENSING_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, NULL, NULL),
  DEFINE_TEMPERATURE_MEASUREMENT_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, NULL),
  DEFINE_HUMIDITY_MEASUREMENT_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, NULL),
  DEFINE_ILLUMINANCE_MEASUREMENT_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, NULL),
  DEFINE_THERMOSTAT_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, NULL, NULL),
  DEFINE_THERMOSTAT_UI_CONF_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, NULL, NULL),
  DEFINE_DIAGNOSTICS_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, NULL, NULL),
  DEFINE_ALARMS_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, NULL, &ciAlarmsCommands),
  DEFINE_POWER_CONFIGURATION_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, NULL, NULL),
  DEFINE_FAN_CONTROL_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, NULL, NULL),
  DEFINE_IAS_ZONE_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, NULL, &ciIASZoneClusterServerCommands),
};

ClusterId_t   ciServerClusterIds[CI_SERVER_CLUSTERS_COUNT] =
{
  BASIC_CLUSTER_ID,
  IDENTIFY_CLUSTER_ID,
  TIME_CLUSTER_ID,
  IAS_ACE_CLUSTER_ID,
#ifdef OTAU_SERVER
  OTAU_CLUSTER_ID, // Always should be on last position in list of clusters ID.
#endif // OTAU_SERVER
};
ClusterId_t   ciClientClusterIds[CI_CLIENT_CLUSTERS_COUNT] =
{
  BASIC_CLUSTER_ID,
  IDENTIFY_CLUSTER_ID,
  ONOFF_CLUSTER_ID,
  LEVEL_CONTROL_CLUSTER_ID,
  GROUPS_CLUSTER_ID,
  SCENES_CLUSTER_ID,
  OCCUPANCY_SENSING_CLUSTER_ID,
  TEMPERATURE_MEASUREMENT_CLUSTER_ID,
  HUMIDITY_MEASUREMENT_CLUSTER_ID,
  ILLUMINANCE_MEASUREMENT_CLUSTER_ID,
  THERMOSTAT_CLUSTER_ID,
  THERMOSTAT_UI_CONF_CLUSTER_ID,
  DIAGNOSTICS_CLUSTER_ID,
  ALARMS_CLUSTER_ID,
  POWER_CONFIGURATION_CLUSTER_ID,
  FAN_CONTROL_CLUSTER_ID,
  IAS_ZONE_CLUSTER_ID,
};

#endif // APP_DEVICE_TYPE_COMBINED_INTERFACE

// eof ciClusters.c
