/**************************************************************************//**
  \file msBasicCluster.h

  \brief
    Multi-Sensor Basic cluster interface.

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
#ifndef _MSBASICCLUSTER_H
#define _MSBASICCLUSTER_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zclBasicCluster.h>

/******************************************************************************
                    Externals
******************************************************************************/
extern ZCL_BasicClusterServerAttributes_t msBasicClusterServerAttributes;
extern ZCL_BasicClusterServerCommands_t msBasicClusterServerCommands;

#endif // _MSBASICCLUSTER_H

// eof msBasicCluster.h
