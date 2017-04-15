/**************************************************************************//**
  \file dsPowerConfigurationCluster.h

  \brief
    Dimmer Switch Power Configuration cluster interface.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    17.11.14 Prashanth - Created.
******************************************************************************/
#ifndef _DSPOWERCONFIGRATIONCLUSTER_H
#define _DSPOWERCONFIGRATIONCLUSTER_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zclPowerConfigurationCluster.h>

/******************************************************************************
                    Definition(s) section
******************************************************************************/
#define ZCL_DS_BATTERY_VOLTAGE_INVALID_DEF               0xFF
#define ZCL_DS_BATTERY_PERCENTAGE_REMAINING_INVALID_DEF  0xFF
#define ZCL_DS_BATTERY_VOLTAGE_CONVERSION_UNIT           100
// Masks
#define ZCL_DS_BATTERY_ALARM_STATE_RESERVED_MASK_1       ((1<<4) | (1<<5) | (1<<6) | (1<<7) | (1<<8) | (1UL<<9))
#define ZCL_DS_BATTERY_ALARM_STATE_RESERVED_MASK_2       ((1UL<<14) | (1UL<<15) | (1UL<<16) | (1UL<<17) | (1UL<<18) | (1UL<<19))
// Reportable Time Values
#define POWER_CONFIGURATION_MIN_REPORT_PERIOD 10
#define POWER_CONFIGURATION_MAX_REPORT_PERIOD 20

/******************************************************************************
                    External variables section
******************************************************************************/
extern ZCL_PowerConfigurationClusterServerAttributes_t dsPowerConfigurationClusterServerAttributes;

/******************************************************************************
                    Prototypes section
******************************************************************************/

/**************************************************************************//**
\brief Initializes Power Configuration cluster
******************************************************************************/
void powerConfigurationClusterInit(void);
void powerConfigurationClusterInitAttributes(void);

#endif // _DSPOWERCONFIGRATIONCLUSTER_H

// eof dsPowerConfigurationCluster.h

