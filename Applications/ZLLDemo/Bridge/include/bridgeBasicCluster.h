/**************************************************************************//**
  \file bridgeBasicCluster.h

  \brief
    Control Bridge device Basic cluster interface.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2013, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    22.01.13 N. Fomin - Created.
******************************************************************************/
#ifndef _BRIDGEBASICCLUSTER_H
#define _BRIDGEBASICCLUSTER_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zcl.h>
#include <zclZllBasicCluster.h>

/******************************************************************************
                    Externals
******************************************************************************/
extern ZCL_BasicClusterServerAttributes_t basicClusterServerAttributes;

/******************************************************************************
                    Prototypes section
******************************************************************************/
/**************************************************************************//**
\brief Initializes Basic cluster
******************************************************************************/
void basicClusterInit(void);

#endif // _BRIDGEBASICCLUSTER_H

// eof bridgeBasicCluster.h
