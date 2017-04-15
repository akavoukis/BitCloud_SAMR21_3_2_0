/**************************************************************************//**
  \file dlClusters.c

  \brief
    Dimmable Light clusters implementation.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    12.12.12 N. Fomin - Created.
******************************************************************************/

#ifdef APP_DEVICE_TYPE_MYAPP
/******************************************************************************
                    Includes section
******************************************************************************/
#include <basicCluster.h>
#include <identifyCluster.h>
#include <myappClusters.h>
#include <myappBasicCluster.h>
#include <myappIdentifyCluster.h>
#include <myappOnOffCluster.h>
#include <myappLevelControlCluster.h>
#include <myappGroupsCluster.h>
#include <myappScenesCluster.h>

/******************************************************************************
                    Global variables
******************************************************************************/
ZCL_Cluster_t dlServerClusters[DL_SERVER_CLUSTERS_COUNT] =
{
  ZCL_DEFINE_BASIC_CLUSTER_SERVER(&dlBasicClusterServerAttributes, &dlBasicClusterServerCommands),
  DEFINE_IDENTIFY_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &dlIdentifyClusterServerAttributes, &dlIdentifyCommands),
  DEFINE_ONOFF_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &dlOnOffClusterServerAttributes, &dlOnOffCommands)  ,
  DEFINE_LEVEL_CONTROL_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &dlLevelControlClusterServerAttributes, &dlLevelControlCommands),
  DEFINE_GROUPS_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &dlGroupsClusterServerAttributes, &dlGroupsCommands),
  DEFINE_SCENES_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &dlScenesClusterServerAttributes, &dlScenesCommands)
};

void (*dlServerClusterInitFunctions[DL_SERVER_CLUSTER_INIT_COUNT])() =
{
  basicClusterInit,
  identifyClusterInit,
  onOffClusterInit,
  levelControlClusterInit,
  groupsClusterInit,
  scenesClusterInit
};

#ifdef OTAU_CLIENT
void (*dlClientClusterInitFunctions[DL_CLIENT_CLUSTER_INIT_COUNT])() =
{
  NULL // oatu client init fucntion
};
#endif

ClusterId_t dlServerClusterIds[DL_SERVER_CLUSTERS_COUNT] =
{
  BASIC_CLUSTER_ID,
  IDENTIFY_CLUSTER_ID,
  ONOFF_CLUSTER_ID,
  LEVEL_CONTROL_CLUSTER_ID,
  GROUPS_CLUSTER_ID,
  SCENES_CLUSTER_ID
};

#ifdef OTAU_CLIENT
ZCL_Cluster_t dlClientClusters[DL_CLIENT_CLUSTERS_COUNT];

ClusterId_t dlClientClusterIds[DL_CLIENT_CLUSTERS_COUNT] =
{
  OTAU_CLUSTER_ID, // Always should be on last position in list of clusters ID.
};
#endif

#endif // APP_DEVICE_TYPE_MYAPP

// eof dlClusters.c
