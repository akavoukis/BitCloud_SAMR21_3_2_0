/**************************************************************************//**
  \file bridgeCommissioningCluster.h

  \brief
    Control Bridge device Commissioning cluster interface.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2013, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    22.01.13  N. Fomin - Created.
******************************************************************************/
#ifndef _BRIDGECOMMISSIONINGCLUSTER_H
#define _BRIDGECOMMISSIONINGCLUSTER_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zcl.h>
#include <zclZllCommissioningCluster.h>

/******************************************************************************
                    Externals
******************************************************************************/
extern ZCL_CommissioningClusterCommands_t commissioningClusterCommands;

#endif // _BRIDGECOMMISSIONINGCLUSTER_H

// eof bridgeCommissioningCluster.h
