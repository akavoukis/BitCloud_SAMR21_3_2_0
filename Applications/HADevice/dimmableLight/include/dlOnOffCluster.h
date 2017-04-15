/**************************************************************************//**
  \file dlOnOffCluster.h

  \brief
    Dimmable Light On/Off cluster interface.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    10.12.12 N. Fomin - Created.
******************************************************************************/
#ifndef _DLONOFFCLUSTER_H
#define _DLONOFFCLUSTER_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zclOnOffCluster.h>

/******************************************************************************
                    Definition(s) section
******************************************************************************/
#define ONOFF_VAL_MIN_REPORT_PERIOD 30
#define ONOFF_VAL_MAX_REPORT_PERIOD 60

/******************************************************************************
                    Externals
******************************************************************************/
extern ZCL_OnOffClusterServerAttributes_t dlOnOffClusterServerAttributes;
extern ZCL_OnOffClusterCommands_t         dlOnOffCommands;

/******************************************************************************
                    Prototypes section
******************************************************************************/
/**************************************************************************//**
\brief Initializes On/Off cluster
******************************************************************************/
void onOffClusterInit(void);

/**************************************************************************//**
\brief Sets on/off state
******************************************************************************/
void onOffSetOnOffState(bool state);

/**************************************************************************//**
\brief gets on/off state

\return on/off state
******************************************************************************/
bool onOffState(void);

#endif // _DLONOFFCLUSTER_H

// eof dlOnOffCluster.h

