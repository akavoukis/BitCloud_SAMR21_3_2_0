/**************************************************************************//**
  \file thIdentifyCluster.h

  \brief
    Thermostat Identify cluster interface.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    09/09/2014 Unithra.C - Created.
******************************************************************************/
#ifndef _THIDENTIFYCLUSTER_H
#define _THIDENTIFYCLUSTER_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zclIdentifyCluster.h>

/******************************************************************************
                    External variable section
******************************************************************************/
extern ZCL_IdentifyClusterAttributes_t thIdentifyClusterServerAttributes;
extern ZCL_IdentifyClusterCommands_t   thIdentifyCommands;

/******************************************************************************
                    Prototypes section
******************************************************************************/
/**************************************************************************//**
\brief Checks if identification process is in progress

\returns true if it is, false otherwise
******************************************************************************/
bool identifyIsIdentifying(void);

#endif // _THIDENTIFYCLUSTER_H

// eof thIdentifyCluster.h

