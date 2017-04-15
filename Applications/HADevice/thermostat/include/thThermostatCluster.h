/**************************************************************************//**
  \file thThermostatCluster.h

  \brief
    Thermostat cluster interface.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    12.12.12 N. Fomin - Created.
    28.05.14 Viswanadham Kotla - Modified.
******************************************************************************/
#ifndef _THTHERMOSTATCLUSTER_H
#define _THTHERMOSTATCLUSTER_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zclThermostatCluster.h>

/******************************************************************************
                    Definition(s) section
******************************************************************************/
#ifdef ZCL_THERMOSTAT_CLUSTER_INCLUDE_OPTIONAL_ATTRIBUTES
/*Uncomment the following attribute if external node is used as temperature sensor*/
  #define THERMOSTAT_EXTERNAL_TEMPERATURE_SENSOR_NODE_AVAILABLE
#endif

#define THERMOSTAT_LOCAL_TEMPERATURE_MIN_REPORT_PERIOD 10
#define THERMOSTAT_LOCAL_TEMPERATURE_MAX_REPORT_PERIOD 20

#define ZCL_TH_LOCAL_TEMPERATURE_DEF    20
#define ZCL_TH_PI_COOLING_DEMAND_DEF    0
#define ZCL_TH_PI_HEATING_DEMAND_DEF    0
#define ZCL_TH_RUNNING_STATE_DEF ( ((uint8_t)ZCL_RUNNING_STATE_OFF << ZCL_HEAT_STATE_BIT_POS) | \
                               ((uint8_t)ZCL_RUNNING_STATE_OFF << ZCL_COOL_STATE_BIT_POS) | \
                               ((uint8_t)ZCL_RUNNING_STATE_OFF << ZCL_FAN_STATE_BIT_POS) | \
                               ((uint8_t)ZCL_RUNNING_STATE_OFF << ZCL_HEAT_STAGE2_STATE_BIT_POS) | \
                               ((uint8_t)ZCL_RUNNING_STATE_OFF << ZCL_COOL_STAGE2_STATE_BIT_POS) | \
                               ((uint8_t)ZCL_RUNNING_STATE_OFF << ZCL_FAN_STAGE2_STATE_BIT_POS) | \
                               ((uint8_t)ZCL_RUNNING_STATE_OFF << ZCL_FAN_STAGE3_STATE_BIT_POS) )

#ifdef BOARD_QTOUCH_XPRO 
#define MIN_HEAT_SETPOINT_LIMIT 1500
#define MAX_HEAT_SETPOINT_LIMIT 3900
#define MIN_COOL_SETPOINT_LIMIT 1500
#define MAX_COOL_SETPOINT_LIMIT 3900
#endif
/******************************************************************************
                    External variables section
******************************************************************************/
extern ZCL_ThermostatClusterServerAttributes_t thThermostatClusterServerAttributes;

extern ZCL_ThermostatClusterCommands_t thThermostatClusterServerCommands;

/******************************************************************************
                    Prototypes section
******************************************************************************/
/**************************************************************************//**
\brief Initializes Thermostat cluster
******************************************************************************/
void thermostatClusterInit(void);
void thermostatClusterInitAttributes(void);
#ifdef ZCL_THERMOSTAT_CLUSTER_INCLUDE_OPTIONAL_ATTRIBUTES
ZCL_Status_t thermostatSetOccupancy(ZCL_ThOccupancy_t value);
#endif

/**************************************************************************//**
\brief Trigger alarm condition
******************************************************************************/
void thermostatSetAlarmCondition(ZclThermostatAlarmCode_t alarmCode, bool alarmSet);

/**************************************************************************//**
\brief Set alarm mask
******************************************************************************/
void thermostatSetAlarmMask(uint8_t alarMask);

#ifdef BOARD_QTOUCH_XPRO 
void thermostatSetPointsChangeButton(int8_t mode,uint8_t amount);
#endif


#endif // _THTHERMOSTATCLUSTER_H

// eof thThermostatCluster.h
