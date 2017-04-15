/**************************************************************************//**
  \file lightClusters.c

  \brief
    Light device clusters configuration

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    28.06.11 A. Taradov - Created.
******************************************************************************/

#if APP_ZLL_DEVICE_TYPE >= APP_DEVICE_TYPE_ON_OFF_LIGHT

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zcl.h>
#include <lightClusters.h>
#include <lightBasicCluster.h>
#include <lightScenesCluster.h>
#include <lightOnOffCluster.h>
#include <lightGroupsCluster.h>
#include <lightIdentifyCluster.h>
#include <lightLevelControlCluster.h>
#include <lightColorControlCluster.h>
#include <lightCommissioningCluster.h>
#include <lightOtaCluster.h>

/******************************************************************************
                    Global variables
******************************************************************************/
ZCL_Cluster_t lightServerClusters[LIGHT_SERVER_CLUSTERS_COUNT] =
{
  ZCL_DEFINE_BASIC_CLUSTER_SERVER(&basicClusterServerAttributes),
  DEFINE_COMMISSIONING_CLUSTER(ZCL_SERVER_CLUSTER_TYPE,
      NULL, &commissioningClusterCommands),
  DEFINE_GROUPS_CLUSTER(ZCL_SERVER_CLUSTER_TYPE,
      &groupsClusterServerAttributes, &groupsClusterServerCommands),
  DEFINE_IDENTIFY_CLUSTER(ZCL_SERVER_CLUSTER_TYPE,
      &identifyClusterServerAttributes, &identifyClusterServerCommands),
  DEFINE_SCENES_CLUSTER(ZCL_SERVER_CLUSTER_TYPE,
      &scenesClusterServerAttributes, &scenesClusterCommands),
  DEFINE_ONOFF_CLUSTER(ZCL_SERVER_CLUSTER_TYPE,
      &onOffClusterServerAttributes, &onOffClusterCommands),
#if APP_ZLL_DEVICE_TYPE >= APP_DEVICE_TYPE_ON_OFF_LIGHT
  DEFINE_LEVEL_CONTROL_CLUSTER(ZCL_SERVER_CLUSTER_TYPE,
      &levelControlClusterServerAttributes, &levelControlClusterServerCommands),
#endif // APP_ZLL_DEVICE_TYPE >= APP_DEVICE_TYPE_ON_OFF_LIGHT
#if APP_ZLL_DEVICE_TYPE >= APP_DEVICE_TYPE_COLOR_LIGHT
  DEFINE_COLOR_CONTROL_CLUSTER(ZCL_SERVER_CLUSTER_TYPE,
      &colorControlClusterServerAttributes, &colorControlClusterServerCommands),
#endif // APP_ZLL_DEVICE_TYPE >= APP_DEVICE_TYPE_COLOR_LIGHT
};

ClusterId_t lightServerClusterIds[LIGHT_SERVER_CLUSTERS_COUNT] =
{
  BASIC_CLUSTER_ID,
  ZLL_COMMISSIONING_CLUSTER_ID,
  GROUPS_CLUSTER_ID,
  IDENTIFY_CLUSTER_ID,
  SCENES_CLUSTER_ID,
  ONOFF_CLUSTER_ID,
#if APP_ZLL_DEVICE_TYPE >= APP_DEVICE_TYPE_ON_OFF_LIGHT
  LEVEL_CONTROL_CLUSTER_ID,
#endif // APP_ZLL_DEVICE_TYPE >= APP_DEVICE_TYPE_ON_OFF_LIGHT
#if APP_ZLL_DEVICE_TYPE >= APP_DEVICE_TYPE_COLOR_LIGHT
  COLOR_CONTROL_CLUSTER_ID,
#endif // APP_ZLL_DEVICE_TYPE >= APP_DEVICE_TYPE_COLOR_LIGHT
};

ZCL_Cluster_t lightClientClusters[LIGHT_CLIENT_CLUSTERS_COUNT] =
{
  ZCL_DEFINE_BASIC_CLUSTER_CLIENT(),
};

ClusterId_t lightClientClusterIds[LIGHT_CLIENT_CLUSTERS_COUNT] =
{
  BASIC_CLUSTER_ID,
#ifdef OTAU_CLIENT
  OTAU_CLUSTER_ID, // Always should be on last position in list of clusters ID.
#endif /* OTAU_CLIENT */
};

/******************************************************************************
                             Implementation section
******************************************************************************/
/**************************************************************************//**
\brief Adds OTAU client cluster to list of clients clusters of light device.
******************************************************************************/
void lightAddOTAUClientCluster(void)
{
#ifdef OTAU_CLIENT
  lightClientClusters[LIGHT_CLIENT_CLUSTERS_COUNT - 1U] = ZCL_GetOtauClientCluster();
#endif // OTAU_CLIENT
}

#endif // APP_ZLL_DEVICE_TYPE >= APP_DEVICE_TYPE_ON_OFF_LIGHT

// eof lightClusters.c
