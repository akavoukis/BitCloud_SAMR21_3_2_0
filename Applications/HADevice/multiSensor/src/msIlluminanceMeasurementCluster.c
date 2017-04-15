/**************************************************************************//**
  \file msIlluminanceMeasurement.c

  \brief
    Multi-Sensor Illuminance Measurement Cluster implementation.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    12.06.14 Yogesh - Created.
******************************************************************************/
#if defined APP_DEVICE_TYPE_MULTI_SENSOR && defined APP_SENSOR_TYPE_LIGHT_SENSOR

/******************************************************************************
                    Includes section
******************************************************************************/
#include <msIlluminanceMeasurementCluster.h>

/******************************************************************************
                    Global variables
******************************************************************************/
ZCL_IlluminanceMeasurementClusterServerAttributes_t msIlluminanceMeasurementClusterServerAttributes =
{
  ZCL_DEFINE_ILLUMINANCE_MEASUREMENT_CLUSTER_SERVER_ATTRIBUTES(ILLUMINANCE_MEASUREMENT_VAL_MIN_REPORT_PERIOD, ILLUMINANCE_MEASUREMENT_VAL_MAX_REPORT_PERIOD)
};

/******************************************************************************
                    Implementation section
******************************************************************************/
/**************************************************************************//**
\brief Initializes Illuminance measurement Sensing cluster
******************************************************************************/
void illuminanceMeasurementClusterInit(void)
{
  msIlluminanceMeasurementClusterServerAttributes.lightSensorType.value = APP_ILLUMINANCE_MEASUREMENT_LIGHT_SENSOR_TYPE_VALUE;
  msIlluminanceMeasurementClusterServerAttributes.measuredValue.value = APP_ILLUMINANCE_MEASUREMENT_MEASURED_VALUE_ATTRIBUTE_VALUE;
  msIlluminanceMeasurementClusterServerAttributes.minMeasuredValue.value = APP_ILLUMINANCE_MEASUREMENT_MIN_MEASURED_VALUE_ATTRIBUTE_VALUE;
  msIlluminanceMeasurementClusterServerAttributes.maxMeasuredValue.value = APP_ILLUMINANCE_MEASUREMENT_MAX_MEASURED_VALUE_ATTRIBUTE_VALUE;
  msIlluminanceMeasurementClusterServerAttributes.tolerance.value = APP_ILLUMINANCE_MEASUREMENT_TOLERANCE_ATTRIBUTE_VALUE;
}

/**************************************************************************//**
\brief Update the measured Value
******************************************************************************/
void illuminanceMeasurementUpdateMeasuredValue(void)
{
  uint16_t measuredValue;

  measuredValue = rand()% APP_ILLUMINANCE_MEASUREMENT_MAX_MEASURED_VALUE_ATTRIBUTE_VALUE;
  if (measuredValue < msIlluminanceMeasurementClusterServerAttributes.minMeasuredValue.value)
    msIlluminanceMeasurementClusterServerAttributes.measuredValue.value = msIlluminanceMeasurementClusterServerAttributes.minMeasuredValue.value;
  else
    msIlluminanceMeasurementClusterServerAttributes.measuredValue.value = measuredValue;

  ZCL_ReportOnChangeIfNeeded(&msIlluminanceMeasurementClusterServerAttributes.measuredValue);
}

/**************************************************************************//**
\brief Update the tolerance value
******************************************************************************/
void illuminanceMeasurementUpdateTolerance(void)
{
  msIlluminanceMeasurementClusterServerAttributes.tolerance.value = 0;

  ZCL_ReportOnChangeIfNeeded(&msIlluminanceMeasurementClusterServerAttributes.tolerance);
}

#endif // APP_DEVICE_TYPE_MULTI_SENSOR

// eof msilluminanceMeasurementCluster.c
