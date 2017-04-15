/**************************************************************************//**
  \file bridgeBasicCluster.c

  \brief
    Control Bridge device Basic cluster implementation.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2013, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    22.01.13 N. Fomin - Created.
******************************************************************************/

#if APP_ZLL_DEVICE_TYPE == APP_DEVICE_TYPE_BRIDGE

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zcl.h>
#include <zclZllBasicCluster.h>

/******************************************************************************
                    Global variables
******************************************************************************/
ZCL_BasicClusterServerAttributes_t basicClusterServerAttributes =
{
  ZCL_DEFINE_BASIC_CLUSTER_SERVER_ATTRIBUTES()
};

/******************************************************************************
                    Implementations section
******************************************************************************/
/**************************************************************************//**
\brief Initializes Basic cluster
******************************************************************************/
void basicClusterInit(void)
{
  basicClusterServerAttributes.zclVersion.value = 1;
  basicClusterServerAttributes.applicationVersion.value = 2;
  basicClusterServerAttributes.stackVersion.value = 3;
  basicClusterServerAttributes.hwVersion.value = 4;
  basicClusterServerAttributes.powerSource.value = 0x03;

  memcpy(basicClusterServerAttributes.manufacturerName.value, "\x07 Atmel ", 8);
  memcpy(basicClusterServerAttributes.modelIdentifier.value, "\x07 Bridge", 8);
  memcpy(basicClusterServerAttributes.dateCode.value, "\x09 20111223", 10);
  memcpy(basicClusterServerAttributes.swBuildId.value, "\x08 Phoenix", 9);
}

#endif // APP_ZLL_DEVICE_TYPE == APP_DEVICE_TYPE_BRIDGE

// eof bridgeBasicCluster.c
