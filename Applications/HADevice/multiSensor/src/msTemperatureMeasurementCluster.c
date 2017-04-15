/**************************************************************************//**
  \file msTemperatureMeasurementCluster.c

  \brief
    Multi-Sensor Temperature Measurement cluster implementation.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    28.05.14 Viswanadham Kotla - Created.
******************************************************************************/
#if defined APP_DEVICE_TYPE_MULTI_SENSOR && defined APP_SENSOR_TYPE_TEMPERATURE_SENSOR

/******************************************************************************
                    Includes section
******************************************************************************/
#include <msTemperatureMeasurementCluster.h>

/******************************************************************************
                    Global variables
******************************************************************************/
ZCL_TemperatureMeasurementClusterAttributes_t tsTemperatureMeasurementClusterServerAttributes =
{
  ZCL_DEFINE_TEMPERATURE_MEASUREMENT_CLUSTER_SERVER_ATTRIBUTES(TEMPERATURE_MEASUREMENT_VAL_MIN_REPORT_PERIOD, TEMPERATURE_MEASUREMENT_VAL_MAX_REPORT_PERIOD)
};

/******************************************************************************
                    Implementation section
******************************************************************************/
/**************************************************************************//**
\brief Initializes Temperature Measurement cluster
******************************************************************************/
void temperatureMeasurementClusterInit(void)
{
  tsTemperatureMeasurementClusterServerAttributes.measuredValue.value = APP_TEMPERATURE_MEASUREMENT_MEASURED_VALUE_ATTRIBUTE_VALUE;
  tsTemperatureMeasurementClusterServerAttributes.minMeasuredValue.value = APP_TEMPERATURE_MEASUREMENT_MIN_MEASURED_VALUE_ATTRIBUTE_VALUE;
  tsTemperatureMeasurementClusterServerAttributes.maxMeasuredValue.value = APP_TEMPERATURE_MEASUREMENT_MAX_MEASURED_VALUE_ATTRIBUTE_VALUE;
  tsTemperatureMeasurementClusterServerAttributes.tolerance.value = APP_TEMPERATURE_MEASUREMENT_TOLERANCE_ATTRIBUTE_VALUE;//to be updated
}

/**************************************************************************//**
\brief Update the measured Value
******************************************************************************/
void tempeartureMeasurementUpdateMeasuredValue(void)
{
  int16_t measuredValue;

  measuredValue = tsTemperatureMeasurementClusterServerAttributes.measuredValue.value - APP_TEMPERATURE_MEASUREMENT_MEASURED_VALUE_PERIODIC_CHANGE;

  if (measuredValue < tsTemperatureMeasurementClusterServerAttributes.minMeasuredValue.value)
    tsTemperatureMeasurementClusterServerAttributes.measuredValue.value =  tsTemperatureMeasurementClusterServerAttributes.maxMeasuredValue.value;
  else
    tsTemperatureMeasurementClusterServerAttributes.measuredValue.value = measuredValue;

  ZCL_ReportOnChangeIfNeeded(&tsTemperatureMeasurementClusterServerAttributes.measuredValue);
}

/**************************************************************************//**
\brief Update the tolerance value
******************************************************************************/
void tempeartureMeasurementUpdateTolerance(void)
{
  tsTemperatureMeasurementClusterServerAttributes.tolerance.value = 0;

  ZCL_ReportOnChangeIfNeeded(&tsTemperatureMeasurementClusterServerAttributes.tolerance);
}

#endif // APP_DEVICE_TYPE_MULTI_SENSOR

// eof msTemperatureMeasurementCluster.c
