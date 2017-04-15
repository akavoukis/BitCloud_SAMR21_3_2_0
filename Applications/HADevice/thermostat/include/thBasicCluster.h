/**************************************************************************//**
  \file thBasicCluster.h

  \brief
    Thermostat Basic cluster interface.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    09/09/2014 Unithra.C - Created.
******************************************************************************/
#ifndef _THBASICCLUSTER_H
#define _THBASICCLUSTER_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zclBasicCluster.h>

/******************************************************************************
                    Defines section
******************************************************************************/
#define ZCL_VERSION                    0x01
#define ZCL_MAINS_THREE_PHASE          0x02
#define ZCL_UNSPECIFIED_ENVIRONMENT    0x00
/******************************************************************************
                    External variables section
******************************************************************************/
extern ZCL_BasicClusterServerAttributes_t thBasicClusterServerAttributes;
extern ZCL_BasicClusterServerCommands_t thBasicClusterServerCommands;

#endif // _THBASICCLUSTER_H

// eof thBasicCluster.h
