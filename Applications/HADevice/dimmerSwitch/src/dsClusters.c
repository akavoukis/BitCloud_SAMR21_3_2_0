/**************************************************************************//**
  \file dsClusters.c

  \brief
    Dimmer Switch clusters implementation.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    12.12.12 N. Fomin - Created.
******************************************************************************/

#ifdef APP_DEVICE_TYPE_DIMMER_SWITCH
/******************************************************************************
                    Includes section
******************************************************************************/
#include <dsClusters.h>
#include <basicCluster.h>
#include <identifyCluster.h>
#include <dsBasicCluster.h>
#include <dsIdentifyCluster.h>
#include <dsOnOffCluster.h>
#include <dsPowerConfigurationCluster.h>
#include <dsAlarmsCluster.h>
#include <dsLevelControlCluster.h>

/******************************************************************************
                    Global variables
******************************************************************************/
ZCL_Cluster_t dsServerClusters[DS_SERVER_CLUSTERS_COUNT] =
{
  ZCL_DEFINE_BASIC_CLUSTER_SERVER(&dsBasicClusterServerAttributes, &dsBasicClusterServerCommands),
  DEFINE_IDENTIFY_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &dsIdentifyClusterServerAttributes, &dsIdentifyCommands),
  DEFINE_POWER_CONFIGURATION_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &dsPowerConfigurationClusterServerAttributes, NULL),
  DEFINE_ALARMS_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &dsAlarmsClusterServerAttributes, &dsAlarmsClusterServerCommands),
};

void (*dsServerClusterInitFunctions[DS_SERVER_CLUSTER_INIT_COUNT])() =
{
  basicClusterInit,
  identifyClusterInit,
  alarmsClusterInit,
  powerConfigurationClusterInit
};	

ZCL_Cluster_t dsClientClusters[DS_CLIENT_CLUSTERS_COUNT] =
{
  DEFINE_IDENTIFY_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, NULL, &dsIdentifyCommands),
  DEFINE_ONOFF_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, NULL, &dsOnOffCommands),
  DEFINE_LEVEL_CONTROL_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, NULL, &dsLevelControlCommands)
};

#ifdef OTAU_CLIENT
void (*dsClientClusterInitFunctions[DS_CLIENT_CLUSTER_INIT_COUNT])() =
{
  NULL // need to add oatu client init
};
#endif

ClusterId_t   dsServerClusterIds[DS_SERVER_CLUSTERS_COUNT] =
{
  BASIC_CLUSTER_ID,
  IDENTIFY_CLUSTER_ID,
  ALARMS_CLUSTER_ID,
  POWER_CONFIGURATION_CLUSTER_ID
};
ClusterId_t   dsClientClusterIds[DS_CLIENT_CLUSTERS_COUNT] =
{
  IDENTIFY_CLUSTER_ID,
  ONOFF_CLUSTER_ID,
  LEVEL_CONTROL_CLUSTER_ID,
#ifdef OTAU_CLIENT
  OTAU_CLUSTER_ID, // Always should be on last position in list of clusters ID.
#endif
};

#endif // APP_DEVICE_TYPE_DIMMER_SWITCH

// eof dsClusters.c
