/**************************************************************************//**
  \file dsBasicCluster.c

  \brief
    Dimmer Switch Basic cluster implementation.

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
#include <dsBasicCluster.h>
#include <basicCluster.h>
#include <dsClusters.h>
#include <commandManager.h>
#include <uartManager.h>
#include <dsClusters.h>

/******************************************************************************
                    Prototypes section
******************************************************************************/
static ZCL_Status_t resetToFactoryDefaultsInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload);

/******************************************************************************
                    Global variables section
******************************************************************************/
ZCL_BasicClusterServerAttributes_t dsBasicClusterServerAttributes =
{
  ZCL_DEFINE_BASIC_CLUSTER_SERVER_ATTRIBUTES()
};

ZCL_BasicClusterServerCommands_t dsBasicClusterServerCommands =
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
  dsBasicClusterServerAttributes.zclVersion.value          = 0x01;
  dsBasicClusterServerAttributes.powerSource.value         = 0x04;
  dsBasicClusterServerAttributes.physicalEnvironment.value = 0x00;
  dsBasicClusterServerAttributes.applicationVersion.value  = 2;
  dsBasicClusterServerAttributes.stackVersion.value        = 3;
  dsBasicClusterServerAttributes.hwVersion.value           = 4;

  memcpy(dsBasicClusterServerAttributes.manufacturerName.value, "\x1f Atmel ", 8);
  memcpy(dsBasicClusterServerAttributes.modelIdentifier.value, "\x1f DimmableSwitch", 15);
}

/**************************************************************************//**
\brief Callback on receive of resetToFactoryDefaults command
******************************************************************************/
static ZCL_Status_t resetToFactoryDefaultsInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload)
{
  for (uint8_t i=0; i<DS_SERVER_CLUSTER_INIT_COUNT; i++)
  {
    if (dsServerClusterInitFunctions[i])
      (dsServerClusterInitFunctions[i])();
  }

#ifdef OTAU_CLIENT 
  for (uint8_t i=0; i<DS_CLIENT_CLUSTER_INIT_COUNT; i++)
  {
    if (dsClientClusterInitFunctions[i])
      (dsClientClusterInitFunctions[i])();
  }
#endif 

  // needs to enable after app directory is created
  //PDS_Store(HA_APP_MEMORY_MEM_ID);

  (void)addressing;
  (void)payloadLength;
  (void)payload;
  return ZCL_SUCCESS_STATUS;
}

#endif // APP_DEVICE_TYPE_DIMMER_SWITCH
// eof dsBasicCluster.c
