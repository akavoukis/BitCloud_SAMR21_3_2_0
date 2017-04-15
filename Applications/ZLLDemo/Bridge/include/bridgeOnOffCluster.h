/**************************************************************************//**
  \file bridgeOnOffCluster.h

  \brief
    Control Bridge device On/Off cluster interface.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2013, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    22.01.13 N. Fomin - Created.
******************************************************************************/
#ifndef _BRIDGEONOFFCLUSTER_H
#define _BRIDGEONOFFCLUSTER_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zcl.h>
#include <zclZllOnOffCluster.h>

/******************************************************************************
                    Externals
******************************************************************************/
extern ZCL_OnOffClusterCommands_t onOffClusterCommands;

/******************************************************************************
                    Prototypes section
******************************************************************************/
/**************************************************************************//**
\brief Sends On/Off command

\param[in] mode    - address mode;
\param[in] addr    - short address of destination node or number of group;
\param[in] command - 0 - off command, 1 - on command;
\param[in] ep      - endpoint number of destination device
******************************************************************************/
void bridgeSendOnOffCommand(APS_AddrMode_t mode, ShortAddr_t addr, uint8_t command, Endpoint_t ep);

#endif // _BRIDGEONOFFCLUSTER_H

// eof bridgeOnOffCluster.h
