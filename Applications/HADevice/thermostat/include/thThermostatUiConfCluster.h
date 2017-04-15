/**************************************************************************//**
  \file thThermostatUiConfCluster.h

  \brief
    Thermostat Ui conf cluster interface.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    9.10.2014 Unithra - Created.
******************************************************************************/
#ifndef _THTHERMOSTATUICONFCLUSTER_H
#define _THTHERMOSTATUICONFCLUSTER_H
/******************************************************************************
                    Includes section
******************************************************************************/
#include <zclThermostatUiConfCluster.h>
/******************************************************************************
                    External variables section
******************************************************************************/
extern ZCL_ThermostatUiConfClusterServerAttributes_t thThermostatUiConfClusterServerAttributes;

/******************************************************************************
                    Prototypes section
******************************************************************************/
/**************************************************************************//**
\brief Initializes Thermostat Ui Conf cluster
******************************************************************************/
void thermostatUiConfClusterInit(void);
#endif // _THTHERMOSTATUICONFCLUSTER_H
