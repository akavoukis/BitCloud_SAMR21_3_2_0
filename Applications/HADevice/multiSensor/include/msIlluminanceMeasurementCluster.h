/**************************************************************************//**
  \file msIlluminanceMeasurementCluster.h

  \brief
    Multi-Sensor Illuminance Measurement Cluster.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
     12.06.14 Yogesh - Created.
******************************************************************************/
#ifndef _MSILLUMINANCEMEASUREMENTCLUSTER_H
#define _MSILLUMINANCEMEASUREMENTCLUSTER_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zclIlluminanceMeasurementCluster.h>

/******************************************************************************
                    Definition(s) section
******************************************************************************/
#define ILLUMINANCE_MEASUREMENT_VAL_MIN_REPORT_PERIOD 15
#define ILLUMINANCE_MEASUREMENT_VAL_MAX_REPORT_PERIOD 30

/* Some default values for attributes */
#define APP_ILLUMINANCE_MEASUREMENT_MEASURED_VALUE_ATTRIBUTE_VALUE       0x00ff
#define APP_ILLUMINANCE_MEASUREMENT_MIN_MEASURED_VALUE_ATTRIBUTE_VALUE   0x0002 //range 0x0002 – 0xfffd
#define APP_ILLUMINANCE_MEASUREMENT_MAX_MEASURED_VALUE_ATTRIBUTE_VALUE   0xfffe //range 0x0001 – 0xfffe
#define APP_ILLUMINANCE_MEASUREMENT_TOLERANCE_ATTRIBUTE_VALUE            0x0700 //0x0000 – 0x0800   //Optional
#define APP_ILLUMINANCE_MEASUREMENT_LIGHT_SENSOR_TYPE_VALUE              0x7f   //0x00 – 0xff       //Optional

/******************************************************************************
                    Externals
******************************************************************************/
extern ZCL_IlluminanceMeasurementClusterServerAttributes_t msIlluminanceMeasurementClusterServerAttributes;

/******************************************************************************
                    Prototypes section
******************************************************************************/
/**************************************************************************//**
\brief Initializes illuminance Measurement cluster
******************************************************************************/
extern void illuminanceMeasurementClusterInit(void);

/**************************************************************************//**
\brief Update the measured Value
******************************************************************************/
extern void illuminanceMeasurementUpdateMeasuredValue(void);

/**************************************************************************//**
\brief Update the tolerance value
******************************************************************************/
extern void illuminanceMeasurementUpdateTolerance(void);

#endif // _MSILLUMINANCEMEASUREMENTCLUSTER_H

// eof msilluminanceMeasureCluster.h
