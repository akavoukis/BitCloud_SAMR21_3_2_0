/**************************************************************************//**
  \file msHumidityMeasurementCluster.h

  \brief
    Multi-Sensor Humidity Measurement cluster interface.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:    
    06.06.14 Viswanadham Kotla - Created.
******************************************************************************/
#ifndef _MSHUMIDITYMEASUREMENTCLUSTER_H
#define _MSHUMIDITYMEASUREMENTCLUSTER_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zclHumidityMeasurementCluster.h>

/******************************************************************************
                    Definition(s) section
******************************************************************************/
#define HUMIDITY_MEASUREMENT_VAL_MIN_REPORT_PERIOD 15
#define HUMIDITY_MEASUREMENT_VAL_MAX_REPORT_PERIOD 25

/* Some default values for attributes */
#define APP_HUMIDITY_MEASUREMENT_MEASURED_VLAUE_ATTRIBUTE_VALUE       0x1000
#define APP_HUMIDITY_MEASUREMENT_MIN_MEASURED_VALUE_ATTRIBUTE_VALUE   0x0000 //range 0x0 – 0x270f
#define APP_HUMIDITY_MEASUREMENT_MAX_MEASURED_VALUE_ATTRIBUTE_VALUE   0x2710 //range 0x954e – 0x2710
#define APP_HUMIDITY_MEASUREMENT_TOLERANCE_ATTRIBUTE_VALUE            0x0100 //0x0000 – 0x0800

#define APP_HUMIDITY_MEASUREMENT_MEASURED_VALUE_PERIODIC_CHANGE       1000 //coresponding to 10%  
/******************************************************************************
                    Externals
******************************************************************************/
extern ZCL_HumidityMeasurementClusterAttributes_t hsHumidityMeasurementClusterServerAttributes;

/******************************************************************************
                    Prototypes section
******************************************************************************/
/**************************************************************************//**
\brief Initializes Humidity Measurement cluster
******************************************************************************/
void humidityMeasurementClusterInit(void);

/**************************************************************************//**
\brief Update the measured Value
******************************************************************************/
void humidityMeasurementUpdateMeasuredValue(void);

#endif // _MSHUMIDITYMEASUREMENTCLUSTER_H

// eof msHumidityMeasurementCluster.h
