/**************************************************************************//**
  \file dsBasicCluster.h

  \brief
    Dimmer Switch Basic cluster interface.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    12.12.12 N. Fomin - Created.
******************************************************************************/
#ifndef _DSBASICCLUSTER_H
#define _DSBASICCLUSTER_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zclBasicCluster.h>

/******************************************************************************
                    Externals
******************************************************************************/
extern ZCL_BasicClusterServerAttributes_t dsBasicClusterServerAttributes;
extern ZCL_BasicClusterServerCommands_t dsBasicClusterServerCommands;

#endif // _DSBASICCLUSTER_H

// eof dsBasicCluster.h
