/**************************************************************************//**
  \file msIdentifyCluster.h

  \brief
    Multi-Sensor Identify cluster interface.

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
#ifndef _MSIDENTIFYCLUSTER_H
#define _MSIDENTIFYCLUSTER_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zclIdentifyCluster.h>

/******************************************************************************
                    Externals
******************************************************************************/
extern ZCL_IdentifyClusterAttributes_t msIdentifyClusterServerAttributes;
extern ZCL_IdentifyClusterCommands_t   msIdentifyCommands;

#endif // _MSIDENTIFYCLUSTER_H

// eof msIdentifyCluster.h

