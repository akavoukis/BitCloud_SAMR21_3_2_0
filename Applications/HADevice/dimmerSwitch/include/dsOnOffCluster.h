/**************************************************************************//**
  \file dsOnOffCluster.h

  \brief
    Dimmer Switch On/Off cluster interface.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    13.12.12 N. Fomin - Created.
******************************************************************************/
#ifndef _DSONOFFCLUSTER_H
#define _DSONOFFCLUSTER_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zclOnOffCluster.h>

/******************************************************************************
                    Types section
******************************************************************************/
typedef enum
{
  OFF_COMMAND    = 0,
  ON_COMMAND     = 1,
  TOGGLE_COMMAND = 2
} OnOffToggle_t;

/******************************************************************************
                    Externals
******************************************************************************/
extern ZCL_OnOffClusterCommands_t dsOnOffCommands;

/******************************************************************************
                    Prototypes section
******************************************************************************/
/**************************************************************************//**
\brief Initializes On/Off cluster
******************************************************************************/
void onOffClusterInit(void);

/**************************************************************************//**
\brief Sends On, Off or Toggle command to bound devices

\param[in] mode    - address mode;
\param[in] addr    - short address of destination node or number of group;
\param[in] ep      - endpoint number of destination device;
\param[in] command - command id
******************************************************************************/
void onOffSendOnOffToggle(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep, OnOffToggle_t command);

#endif // _DSONOFFCLUSTER_H

// eof dsOnOffCluster.h

