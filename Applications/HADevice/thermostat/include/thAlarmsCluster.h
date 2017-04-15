/**************************************************************************//**
  \file thAlarmsCluster.h

  \brief
    Thermostat Alarm cluster interface.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    28/10/2014 Agasthian.C - Created.
******************************************************************************/
#ifndef _THALARMSCLUSTER_H
#define _THALARMSCLUSTER_H

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
extern ZCL_AlarmsClusterServerAttributes_t thAlarmsClusterServerAttributes;
extern ZCL_AlarmsClusterServerCommands_t   thAlarmsClusterServerCommands;

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

#endif // _THALARMSCLUSTER_H

// eof thAlarmsCluster.h
