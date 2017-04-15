/**************************************************************************//**
  \file thThermostatCluster.c

  \brief
    Thermostat cluster implementation.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
       09/09/2014 Unithra.C - Created
******************************************************************************/
#ifdef APP_DEVICE_TYPE_THERMOSTAT
/******************************************************************************
                    Includes section
******************************************************************************/
#include <thThermostatUiConfCluster.h>
/*******************************************************************************
                             Defines section
*******************************************************************************/
/*******************************************************************************
                    Static functions prototypes section
*******************************************************************************/
/******************************************************************************
                    Global variables
******************************************************************************/
ZCL_ThermostatUiConfClusterServerAttributes_t thThermostatUiConfClusterServerAttributes =
{
  ZCL_DEFINE_THERMOSTAT_UI_CONF_CLUSTER_SERVER_ATTRIBUTES()
};
/******************************************************************************
                    Implementation section
******************************************************************************/
/**************************************************************************//**
\brief Initializes thermostat ui conf cluster
******************************************************************************/
void thermostatUiConfClusterInit(void)
{
  thThermostatUiConfClusterServerAttributes.temperatureDisplayMode.value = ZCL_TEMPERATURE_IN_CELSIUS;
  thThermostatUiConfClusterServerAttributes.keypadLockOut.value = ZCL_NO_LOCKOUT;
  thThermostatUiConfClusterServerAttributes.scheduleProgVisibility.value = ZCL_ENABLE_LOCAL_SCHEDULE_PROGRAMMING;
}
#endif // APP_DEVICE_TYPE_THERMOSTAT
// eof thThermostatUiConfCluster.c
