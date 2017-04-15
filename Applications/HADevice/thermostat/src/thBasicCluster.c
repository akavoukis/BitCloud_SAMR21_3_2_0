/**************************************************************************//**
  \file thBasicCluster.c

  \brief
    Thermostat Basic cluster implementation.

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
#include <thBasicCluster.h>
#include <basicCluster.h>
#include <thClusters.h>

/******************************************************************************
                    Prototypes section
******************************************************************************/
static ZCL_Status_t resetToFactoryDefaultsInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload);

/******************************************************************************
                    Global variables
******************************************************************************/
ZCL_BasicClusterServerAttributes_t thBasicClusterServerAttributes =
{
  ZCL_DEFINE_BASIC_CLUSTER_SERVER_ATTRIBUTES()
};

ZCL_BasicClusterServerCommands_t thBasicClusterServerCommands =
{
  ZCL_DEFINE_BASIC_CLUSTER_COMMANDS(resetToFactoryDefaultsInd)
};

/******************************************************************************
                    Implementation section
******************************************************************************/
/**************************************************************************//**
\brief Initializes Basic cluster
******************************************************************************/
void basicClusterInit(void)
{
  thBasicClusterServerAttributes.zclVersion.value          = ZCL_VERSION;
  thBasicClusterServerAttributes.powerSource.value         = ZCL_MAINS_THREE_PHASE;
  thBasicClusterServerAttributes.physicalEnvironment.value = ZCL_UNSPECIFIED_ENVIRONMENT;
  thBasicClusterServerAttributes.applicationVersion.value  = 2;
  thBasicClusterServerAttributes.stackVersion.value        = 3;
  thBasicClusterServerAttributes.hwVersion.value           = 4;

  memcpy(thBasicClusterServerAttributes.manufacturerName.value, "\x1f Atmel ", 8);
  memcpy(thBasicClusterServerAttributes.modelIdentifier.value, "\x1f Thermostat", 12);
}

/**************************************************************************//**
\brief Callback on receive of resetToFactoryDefaults command
******************************************************************************/
static ZCL_Status_t resetToFactoryDefaultsInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload)
{
  for (uint8_t i=0; i<TH_SERVER_CLUSTER_INIT_COUNT; i++)
  {
    if (thServerClusterInitFunctions[i])
      (thServerClusterInitFunctions[i])();
  }

#ifdef OTAU_CLIENT
  for (uint8_t i=0; i<TH_CLIENT_CLUSTER_INIT_COUNT; i++)
  {
    if (thClientClusterInitFunctions[i])
      (thClientClusterInitFunctions[i])();
  }
#endif

  // needs to enable after app directory is created
  //PDS_Store(HA_APP_MEMORY_MEM_ID);

  (void)addressing;
  (void)payloadLength;
  (void)payload;
  return ZCL_SUCCESS_STATUS;
}

#endif // APP_DEVICE_TYPE_THERMOSTAT

// eof thBasicCluster.c
