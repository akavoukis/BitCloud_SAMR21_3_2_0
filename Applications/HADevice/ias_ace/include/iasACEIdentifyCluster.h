/**************************************************************************//**
  \file iasACEIdentifyCluster.h

  \brief
     IAS ACE Identify Cluster interface.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    18/11/2014 Yogesh - Created.
******************************************************************************/
#ifndef _IASACEIDENTIFYCLUSTER_H
#define _IASACEIDENTIFYCLUSTER_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zclIdentifyCluster.h>

/******************************************************************************
                    External variable section
******************************************************************************/
extern ZCL_IdentifyClusterAttributes_t iasACEIdentifyClusterServerAttributes;
extern ZCL_IdentifyClusterCommands_t   iasACEIdentifyCommands;

/******************************************************************************
                    Prototypes section
******************************************************************************/
/**************************************************************************//**
\brief Checks if identification process is in progress

\returns true if it is, false otherwise
******************************************************************************/
bool identifyIsIdentifying(void);

#endif // _IASACEIDENTIFYCLUSTER_H

// eof iasACEIdentifyCluster.h

