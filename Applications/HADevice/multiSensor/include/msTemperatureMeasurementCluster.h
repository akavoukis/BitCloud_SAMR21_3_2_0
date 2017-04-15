/**************************************************************************//**
  \file msTemperatureMeasurementCluster.h

  \brief
    Multi-Sensor Temperature Measurement cluster interface.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:    
    28.05.14 Viswanadham Kotla - Modified.
******************************************************************************/
#ifndef _MSTEMPERATUREMEASUREMENTCLUSTER_H
#define _MSTEMPERATUREMEASUREMENTCLUSTER_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zclTemperatureMeasurementCluster.h>

/******************************************************************************
                    Definition(s) section
******************************************************************************/
#define TEMPERATURE_MEASUREMENT_VAL_MIN_REPORT_PERIOD 5
#define TEMPERATURE_MEASUREMENT_VAL_MAX_REPORT_PERIOD 15

/* Some default values for attributes */
#define APP_TEMPERATURE_MEASUREMENT_MEASURED_VALUE_ATTRIBUTE_VALUE       0x5000
#define APP_TEMPERATURE_MEASUREMENT_MIN_MEASURED_VALUE_ATTRIBUTE_VALUE   0x954d //range 0x954d – 0x7ffe
#define APP_TEMPERATURE_MEASUREMENT_MAX_MEASURED_VALUE_ATTRIBUTE_VALUE   0x7fff //range 0x954e – 0x7fff
#define APP_TEMPERATURE_MEASUREMENT_TOLERANCE_ATTRIBUTE_VALUE            0x0100 //0x0000 – 0x0800

#define APP_TEMPERATURE_MEASUREMENT_MEASURED_VALUE_PERIODIC_CHANGE       1000 //corresponding to 10 degree celsius
/******************************************************************************
                    Externals
******************************************************************************/
extern ZCL_TemperatureMeasurementClusterAttributes_t tsTemperatureMeasurementClusterServerAttributes;

/******************************************************************************
                    Prototypes section
******************************************************************************/
/**************************************************************************//**
\brief Initializes Temperature Measurement cluster
******************************************************************************/
void temperatureMeasurementClusterInit(void);

/**************************************************************************//**
\brief Update the measured Value
******************************************************************************/
void tempeartureMeasurementUpdateMeasuredValue(void);

#endif // _MSTEMPERATUREMEASUREMENTCLUSTER_H

// eof msTemperatureMeasurementCluster.h
