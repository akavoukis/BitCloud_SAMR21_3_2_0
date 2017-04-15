/**************************************************************************//**
  \file dlBasicCluster.h

  \brief
    Dimmable Light Basic cluster interface.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    10.12.12 N. Fomin - Created.
******************************************************************************/
#ifndef _DLBASICCLUSTER_H
#define _DLBASICCLUSTER_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zclBasicCluster.h>

/******************************************************************************
                    Externals
******************************************************************************/
extern ZCL_BasicClusterServerAttributes_t dlBasicClusterServerAttributes;
extern ZCL_BasicClusterServerCommands_t dlBasicClusterServerCommands;

#endif // _DLBASICCLUSTER_H

// eof dlBasicCluster.h
