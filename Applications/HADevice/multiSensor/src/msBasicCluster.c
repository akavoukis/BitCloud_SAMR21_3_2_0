/**************************************************************************//**
  \file msBasicCluster.c

  \brief
    Multi-Sensor Basic cluster implementation.

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
#include <msBasicCluster.h>
#include <basicCluster.h>
#include <msClusters.h>

/******************************************************************************
                    Prototypes section
******************************************************************************/
static ZCL_Status_t resetToFactoryDefaultsInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload);

/******************************************************************************
                    Global variables section
******************************************************************************/
ZCL_BasicClusterServerAttributes_t msBasicClusterServerAttributes =
{
  ZCL_DEFINE_BASIC_CLUSTER_SERVER_ATTRIBUTES()
};


ZCL_BasicClusterServerCommands_t msBasicClusterServerCommands =
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
  msBasicClusterServerAttributes.zclVersion.value          = 0x01;
  msBasicClusterServerAttributes.powerSource.value         = 0x04;
  msBasicClusterServerAttributes.physicalEnvironment.value = 0x00;
  msBasicClusterServerAttributes.applicationVersion.value  = 2;
  msBasicClusterServerAttributes.stackVersion.value        = 3;
  msBasicClusterServerAttributes.hwVersion.value           = 4;

  memcpy(msBasicClusterServerAttributes.manufacturerName.value, "\x1f Atmel ", 8);
  memcpy(msBasicClusterServerAttributes.modelIdentifier.value, "\x1f MultiSensor", 13);
}

/**************************************************************************//**
\brief Callback on receive of resetToFactoryDefaults command
******************************************************************************/
static ZCL_Status_t resetToFactoryDefaultsInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload)
{

  for (uint8_t i=0; i<MS_SERVER_CLUSTER_INIT_COUNT; i++)
  {
    if (msServerClusterInitFunctions[i])
      (msServerClusterInitFunctions[i])();
  }

#ifdef OTAU_CLIENT
  for (uint8_t i=0; i<MS_CLIENT_CLUSTER_INIT_COUNT; i++)
  {
    if (msClientClusterInitFunctions[i])
      (msClientClusterInitFunctions[i])();
  }
#endif

  // needs to enable after app directory is created
  //PDS_Store(HA_APP_MEMORY_MEM_ID);

  (void)addressing;
  (void)payloadLength;
  (void)payload;
  return ZCL_SUCCESS_STATUS;
}

#endif // APP_DEVICE_TYPE_MULTI_SENSOR

// eof msBasicCluster.c
