/**************************************************************************//**
  \file iasACEBasicCluster.c

  \brief
    IAS ACE Basic cluster implementation.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    18/11/2014 Yogesh - Created.
******************************************************************************/
#ifdef APP_DEVICE_TYPE_IAS_ACE

/******************************************************************************
                    Includes section
******************************************************************************/
#include <iasACEBasicCluster.h>
#include <iasACECluster.h>
#include <basicCluster.h>

/******************************************************************************
                    Prototypes section
******************************************************************************/
static ZCL_Status_t resetToFactoryDefaultsInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload);

/******************************************************************************
                    Global variables
******************************************************************************/
ZCL_BasicClusterServerAttributes_t  iasACEBasicClusterServerAttributes =
{
  ZCL_DEFINE_BASIC_CLUSTER_SERVER_ATTRIBUTES()
};

ZCL_BasicClusterServerCommands_t iasACEBasicClusterServerCommands =
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
  iasACEBasicClusterServerAttributes.zclVersion.value          = ZCL_VERSION;
  iasACEBasicClusterServerAttributes.powerSource.value         = ZCL_MAINS_THREE_PHASE;
  iasACEBasicClusterServerAttributes.physicalEnvironment.value = ZCL_UNSPECIFIED_ENVIRONMENT;
  iasACEBasicClusterServerAttributes.applicationVersion.value  = 0x02;
  iasACEBasicClusterServerAttributes.stackVersion.value        = 0x03;
  iasACEBasicClusterServerAttributes.hwVersion.value           = 0x04;

  memcpy(iasACEBasicClusterServerAttributes.manufacturerName.value, "\x1f Atmel ", 8);
  memcpy(iasACEBasicClusterServerAttributes.modelIdentifier.value, "\x1f IAS ACE", 15);
}

/**************************************************************************//**
\brief Callback on receive of resetToFactoryDefaults command
******************************************************************************/
static ZCL_Status_t resetToFactoryDefaultsInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload)
{
  for (uint8_t i=0; i<IAS_ACE_SERVER_CLUSTER_INIT_COUNT; i++)
  {
     if (iasACEServerClusterInitFunctions[i])
      (iasACEServerClusterInitFunctions[i])();
  }

#ifdef OTAU_CLIENT 
  for (uint8_t i=0; i<IAS_ACE_CLIENT_CLUSTER_INIT_COUNT; i++)
  {
    if (iasACEClientClusterInitFunctions[i])
      (iasACEClientClusterInitFunctions[i])();
  }
#endif 
  (void)addressing;
  (void)payloadLength;
  (void)payload;
  return ZCL_SUCCESS_STATUS;
}

#endif // APP_DEVICE_TYPE_IAS_ACE

// eof iasACEBasicCluster.c
