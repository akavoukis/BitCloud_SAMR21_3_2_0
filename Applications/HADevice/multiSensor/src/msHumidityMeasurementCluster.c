/**************************************************************************//**
  \file msHumidityMeasurementCluster.c

  \brief
    Multi-Sensor Humidity Measurement cluster implementation.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    06.06.14 Viswanadham Kotla - Created.
******************************************************************************/
#if defined APP_DEVICE_TYPE_MULTI_SENSOR && defined APP_SENSOR_TYPE_HUMIDITY_SENSOR

/******************************************************************************
                    Includes section
******************************************************************************/
#include <msHumidityMeasurementCluster.h>

/******************************************************************************
                    Global variables
******************************************************************************/
ZCL_HumidityMeasurementClusterAttributes_t hsHumidityMeasurementClusterServerAttributes =
{
  ZCL_DEFINE_HUMIDITY_MEASUREMENT_CLUSTER_SERVER_ATTRIBUTES(HUMIDITY_MEASUREMENT_VAL_MIN_REPORT_PERIOD, HUMIDITY_MEASUREMENT_VAL_MAX_REPORT_PERIOD)
};

/******************************************************************************
                    Implementation section
******************************************************************************/
/**************************************************************************//**
\brief Initializes Humidity Measurement cluster
******************************************************************************/
void humidityMeasurementClusterInit(void)
{
  hsHumidityMeasurementClusterServerAttributes.measuredValue.value = APP_HUMIDITY_MEASUREMENT_MEASURED_VLAUE_ATTRIBUTE_VALUE;
  hsHumidityMeasurementClusterServerAttributes.minMeasuredValue.value = APP_HUMIDITY_MEASUREMENT_MIN_MEASURED_VALUE_ATTRIBUTE_VALUE;
  hsHumidityMeasurementClusterServerAttributes.maxMeasuredValue.value = APP_HUMIDITY_MEASUREMENT_MAX_MEASURED_VALUE_ATTRIBUTE_VALUE;
  hsHumidityMeasurementClusterServerAttributes.tolerance.value = APP_HUMIDITY_MEASUREMENT_TOLERANCE_ATTRIBUTE_VALUE;//to be updated
}

/**************************************************************************//**
\brief Update the measured Value
******************************************************************************/
void humidityMeasurementUpdateMeasuredValue(void)
{
  uint16_t measuredValue ;

  measuredValue = hsHumidityMeasurementClusterServerAttributes.measuredValue.value + APP_HUMIDITY_MEASUREMENT_MEASURED_VALUE_PERIODIC_CHANGE;

  if (measuredValue > hsHumidityMeasurementClusterServerAttributes.maxMeasuredValue.value)
    hsHumidityMeasurementClusterServerAttributes.measuredValue.value =  hsHumidityMeasurementClusterServerAttributes.minMeasuredValue.value;
  else
    hsHumidityMeasurementClusterServerAttributes.measuredValue.value = measuredValue;

  ZCL_ReportOnChangeIfNeeded(&hsHumidityMeasurementClusterServerAttributes.measuredValue);
}

/**************************************************************************//**
\brief Update the tolerance value
******************************************************************************/
void humidityMeasurementUpdateTolerance(void)
{
  hsHumidityMeasurementClusterServerAttributes.tolerance.value = 0;

  ZCL_ReportOnChangeIfNeeded(&hsHumidityMeasurementClusterServerAttributes.tolerance);
}

#endif // APP_DEVICE_TYPE_MULTI_SENSOR && defined APP_SENSOR_TYPE_HUMIDITY_SENSOR

// eof msHumidityMeasuementCluster.c
