/**************************************************************************//**
  \file dlBasicCluster.c

  \brief
    Dimmable Light Basic cluster implementation.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    10.12.12 N. Fomin - Created.
******************************************************************************/
#ifdef APP_DEVICE_TYPE_MYAPP

/******************************************************************************
                    Includes section
******************************************************************************/
#include <myappBasicCluster.h>
#include <basicCluster.h>
#include <myappClusters.h>
#include <pdsDataServer.h>

/******************************************************************************
                    Prototypes section
******************************************************************************/
static ZCL_Status_t resetToFactoryDefaultsInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload);

/******************************************************************************
                    Global variables section
******************************************************************************/
ZCL_BasicClusterServerAttributes_t dlBasicClusterServerAttributes =
{
  ZCL_DEFINE_BASIC_CLUSTER_SERVER_ATTRIBUTES()
};


ZCL_BasicClusterServerCommands_t dlBasicClusterServerCommands =
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
  dlBasicClusterServerAttributes.zclVersion.value          = 0x01;
  dlBasicClusterServerAttributes.powerSource.value         = 0x04;
  dlBasicClusterServerAttributes.physicalEnvironment.value = 0x00;
  dlBasicClusterServerAttributes.applicationVersion.value  = 2;
  dlBasicClusterServerAttributes.stackVersion.value        = 3;
  dlBasicClusterServerAttributes.hwVersion.value           = 4;

  memcpy(dlBasicClusterServerAttributes.manufacturerName.value, "\x1f Atmel ", 8);
  memcpy(dlBasicClusterServerAttributes.modelIdentifier.value, "\x1f DimmableLight", 14);
}

/**************************************************************************//**
\brief Callback on receive of resetToFactoryDefaults command
******************************************************************************/
static ZCL_Status_t resetToFactoryDefaultsInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload)
{
  for (uint8_t i=0; i<DL_SERVER_CLUSTER_INIT_COUNT; i++)
  {
    if (dlServerClusterInitFunctions[i])
      (dlServerClusterInitFunctions[i])();
  }

#ifdef OTAU_CLIENT	
  for (uint8_t i=0; i<DL_CLIENT_CLUSTER_INIT_COUNT; i++)
  {
    if (dlClientClusterInitFunctions[i])
      (dlClientClusterInitFunctions[i])();
  }
#endif
   PDS_Store(HA_APP_MEMORY_MEM_ID);

  (void)addressing;
  (void)payloadLength;
  (void)payload;
  return ZCL_SUCCESS_STATUS;
}


#endif // APP_DEVICE_TYPE_MYAPP

// eof dlBasicCluster.c
