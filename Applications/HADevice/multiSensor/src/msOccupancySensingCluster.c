/**************************************************************************//**
  \file msOccupancySensingCluster.c

  \brief
    Multi-Sensor Occupancy Sensing cluster implementation.

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
#if defined APP_DEVICE_TYPE_MULTI_SENSOR && defined APP_SENSOR_TYPE_OCCUPANCY_SENSOR

/******************************************************************************
                    Includes section
******************************************************************************/
#include <msOccupancySensingCluster.h>

/******************************************************************************
                    Global variables
******************************************************************************/
ZCL_OccupancySensingClusterServerAttributes_t osOccupancySensingClusterServerAttributes =
{
  ZCL_DEFINE_OCCUPANCY_SENSING_CLUSTER_SERVER_ATTRIBUTES(OCCUPANCY_SENSING_VAL_MIN_REPORT_PERIOD, OCCUPANCY_SENSING_VAL_MAX_REPORT_PERIOD)
};

/******************************************************************************
                    Implementation section
******************************************************************************/
/**************************************************************************//**
\brief Initializes Occupancy Sensing cluster
******************************************************************************/
void occupancySensingClusterInit(void)
{
  osOccupancySensingClusterServerAttributes.occupancySensorType.value = OCCUPANYC_SENSOR_TYPE_ATTRIBUTE_VALUE_PIR;
  osOccupancySensingClusterServerAttributes.occupancy.value = OCCUPANCY_ATTRIBUTE_VALUE_UNOCCUPIED;
}

/**************************************************************************//**
\brief Toggles occupancy
******************************************************************************/
void occupancySensingToggleOccupancy(void)
{
  if (OCCUPANCY_ATTRIBUTE_VALUE_UNOCCUPIED == osOccupancySensingClusterServerAttributes.occupancy.value)
    osOccupancySensingClusterServerAttributes.occupancy.value = OCCUPANCY_ATTRIBUTE_VALUE_OCCUPIED;
  else
    osOccupancySensingClusterServerAttributes.occupancy.value = OCCUPANCY_ATTRIBUTE_VALUE_UNOCCUPIED;

  ZCL_ReportOnChangeIfNeeded(&osOccupancySensingClusterServerAttributes.occupancy);
}

#endif // APP_DEVICE_TYPE_MULTI_SENSOR && defined APP_SENSOR_TYPE_OCCUPANCY_SENSOR

// eof msOccupancySensingCluster.c
