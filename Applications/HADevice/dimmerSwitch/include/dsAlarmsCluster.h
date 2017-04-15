/**************************************************************************//**
  \file dsAlarmsCluster.h

  \brief
    DimmerSwitch Alarm cluster interface.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    08/12/2014 Prashanth.Udumula - Created.
******************************************************************************/
#ifndef _DSALARMSCLUSTER_H
#define _DSALARMSCLUSTER_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zclAlarmsCluster.h>

/******************************************************************************
                    Defines section
******************************************************************************/

/******************************************************************************
                    External variables section
******************************************************************************/
extern ZCL_AlarmsClusterServerAttributes_t dsAlarmsClusterServerAttributes;
extern ZCL_AlarmsClusterServerCommands_t   dsAlarmsClusterServerCommands;

/******************************************************************************
                    Prototypes section
******************************************************************************/
/**************************************************************************//**
\brief Initializes Identify cluster
******************************************************************************/
void alarmsClusterInit(void);

/**************************************************************************//**
\brief alarm notification raised by other clusters

\param[in] alarmCode - alarm code;
\param[in] clusterId - cluster identifier;
******************************************************************************/
void alarmNotification(uint8_t alarmCode, ClusterId_t clusterId);

#endif // _DSALARMSCLUSTER_H

// eof dsAlarmsCluster.h
