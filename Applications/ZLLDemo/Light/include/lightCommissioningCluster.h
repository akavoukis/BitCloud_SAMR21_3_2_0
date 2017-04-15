/**************************************************************************//**
  \file lightCommissioningCluster.h

  \brief
    Light device Commissioning cluster interface.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    07.07.11  A. Taradov - Created.
******************************************************************************/
#ifndef _LIGHTCOMMISSIONINGCLUSTER_H
#define _LIGHTCOMMISSIONINGCLUSTER_H

/******************************************************************************
                    Includes
******************************************************************************/
#include <zcl.h>
#include <zclZllCommissioningCluster.h>

/******************************************************************************
                    Externals
******************************************************************************/
extern ZCL_CommissioningClusterCommands_t commissioningClusterCommands;

/******************************************************************************
                    Prototypes
******************************************************************************/
void commissioningClusterInit(void);

void sendEndpointInformation(ZCL_Addressing_t *addressing);

#endif // _LIGHTCOMMISSIONINGCLUSTER_H

// eof lightCommissioningCluster.h
