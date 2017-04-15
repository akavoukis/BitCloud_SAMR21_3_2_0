/**************************************************************************//**
  \file bridgeIdentifyCluster.h

  \brief
    Control Bridge device Identify cluster interface.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2013, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    22.01.13 N. Fomin - Created.
******************************************************************************/
#ifndef _BRIDGEIDENTIFYCLUSTER_H
#define _BRIDGEIDENTIFYCLUSTER_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zcl.h>
#include <zclZllIdentifyCluster.h>

/******************************************************************************
                    Externals
******************************************************************************/
extern ZCL_IdentifyClusterCommands_t identifyClusterCommands;

/**************************************************************************//**
\brief Sends Identify command

\param[in] mode  - address mode;
\param[in] addr  - short address of destination node or number of group;
\param[in] ep    - endpoint number of destination device
******************************************************************************/
void bridgeSendIdentifyCommand(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep);

#endif // _BRIDGEIDENTIFYCLUSTER_H

// eof bridgeIdentifyCluster.h
