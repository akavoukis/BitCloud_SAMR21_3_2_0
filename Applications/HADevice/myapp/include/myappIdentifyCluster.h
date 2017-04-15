/**************************************************************************//**
  \file dlIdentifyCluster.h

  \brief
    Dimmable Light Identify cluster interface.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    10.12.12 N. Fomin - Created.
******************************************************************************/
#ifndef _MYAPPIDENTIFYCLUSTER_H
#define _MYAPPIDENTIFYCLUSTER_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zclIdentifyCluster.h>

/******************************************************************************
                    Externals
******************************************************************************/
extern ZCL_IdentifyClusterAttributes_t dlIdentifyClusterServerAttributes;
extern ZCL_IdentifyClusterCommands_t   dlIdentifyCommands;

/******************************************************************************
                    Prototypes section
******************************************************************************/
/**************************************************************************//**
\brief Checks if identification process is in progress

\returns true if it is, false otherwise
******************************************************************************/
bool identifyIsIdentifying(void);

#endif // _DLIDENTIFYCLUSTER_H

// eof dlIdentifyCluster.h

