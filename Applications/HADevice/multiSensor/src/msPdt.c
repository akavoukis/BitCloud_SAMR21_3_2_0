/******************************************************************************
  \file msPdt.c

  \brief
    Multi-Sensor Persistent Data Table implementation.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2010-2013, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    12.12.12 N. Fomin - Created.
    28.05.14 Viswanadham Kotla - Modoified.
******************************************************************************/
#ifdef APP_DEVICE_TYPE_MULTI_SENSOR

/******************************************************************************
                    Includes section
******************************************************************************/
#include <pdsDataServer.h>
#include <msOccupancySensingCluster.h>
#include <msTemperatureMeasurementCluster.h>
#include <msHumidityMeasurementCluster.h>
#include <msIlluminanceMeasurementCluster.h>

/******************************************************************************
                    PDT definitions
******************************************************************************/
#ifdef _ENABLE_PERSISTENT_SERVER_
/* Occupancy Sensor application data file descriptors.
   Shall be placed in the PDS_FF code segment. */
#ifdef APP_SENSOR_TYPE_OCCUPANCY_SENSOR
PDS_DECLARE_FILE(APP_MS_OCCUPANCY_MEM_ID, sizeof(osOccupancySensingClusterServerAttributes.occupancy), &osOccupancySensingClusterServerAttributes.occupancy,  NO_FILE_MARKS);
#endif

#ifdef APP_SENSOR_TYPE_TEMPERATURE_SENSOR
PDS_DECLARE_FILE(APP_MS_TEMP_MEASURED_VALUE_MEM_ID, sizeof(tsTemperatureMeasurementClusterServerAttributes.measuredValue), &tsTemperatureMeasurementClusterServerAttributes.measuredValue,  NO_FILE_MARKS);
PDS_DECLARE_FILE(APP_MS_TEMP_TOLERANCE_MEM_ID, sizeof(tsTemperatureMeasurementClusterServerAttributes.tolerance), &tsTemperatureMeasurementClusterServerAttributes.tolerance,  NO_FILE_MARKS);
#endif

#ifdef APP_SENSOR_TYPE_HUMIDITY_SENSOR
PDS_DECLARE_FILE(APP_MS_HUMIDITY_MEASURED_VALUE_MEM_ID, sizeof(hsHumidityMeasurementClusterServerAttributes.measuredValue), &hsHumidityMeasurementClusterServerAttributes.measuredValue,  NO_FILE_MARKS);
PDS_DECLARE_FILE(APP_MS_HUMIDITY_TOLERANCE_MEM_ID, sizeof(hsHumidityMeasurementClusterServerAttributes.tolerance), &hsHumidityMeasurementClusterServerAttributes.tolerance,  NO_FILE_MARKS);
#endif

#ifdef APP_SENSOR_TYPE_LIGHT_SENSOR
PDS_DECLARE_FILE(APP_MS_ILLU_MEASURED_VALUE_MEM_ID, sizeof(msIlluminanceMeasurementClusterServerAttributes.measuredValue), &msIlluminanceMeasurementClusterServerAttributes.measuredValue,  NO_FILE_MARKS);
PDS_DECLARE_FILE(APP_MS_ILLU_TOLERANCE_MEM_ID, sizeof(msIlluminanceMeasurementClusterServerAttributes.tolerance), &msIlluminanceMeasurementClusterServerAttributes.tolerance,  NO_FILE_MARKS);
#endif

/* Multi sensor application data file identifiers list.
   Will be placed in flash. */
PROGMEM_DECLARE(PDS_MemId_t appDlMemoryIdsTable[]) =
{
#ifdef APP_SENSOR_TYPE_OCCUPANCY_SENSOR
  APP_MS_OCCUPANCY_MEM_ID,
#endif

#ifdef APP_SENSOR_TYPE_TEMPERATURE_SENSOR
  APP_MS_TEMP_MEASURED_VALUE_MEM_ID,
  APP_MS_TEMP_TOLERANCE_MEM_ID,
#endif

#ifdef APP_SENSOR_TYPE_HUMIDITY_SENSOR
  APP_MS_HUMIDITY_MEASURED_VALUE_MEM_ID,
  APP_MS_HUMIDITY_TOLERANCE_MEM_ID,
#endif

#ifdef APP_SENSOR_TYPE_LIGHT_SENSOR
  APP_MS_ILLU_MEASURED_VALUE_MEM_ID,
  APP_MS_ILLU_TOLERANCE_MEM_ID,
#endif

};

#endif // _ENABLE_PERSISTENT_SERVER_
#endif // APP_DEVICE_TYPE_MULTI_SENSOR

// eof msPdt.c
