/**************************************************************************//**
  \file dsIdentifyCluster.h

  \brief
    Dimmer Switch Identify cluster interface.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    12.12.12 N. Fomin - Created.
******************************************************************************/
#ifndef _DSIDENTIFYCLUSTER_H
#define _DSIDENTIFYCLUSTER_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zclIdentifyCluster.h>

/******************************************************************************
                    Externals
******************************************************************************/
extern ZCL_IdentifyClusterAttributes_t dsIdentifyClusterServerAttributes;
extern ZCL_IdentifyClusterCommands_t   dsIdentifyCommands;

#endif // _DSIDENTIFYCLUSTER_H

// eof dsIdentifyCluster.h

