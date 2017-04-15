/******************************************************************************
  \file thPdt.c

  \brief
    Thermostat Persistent Data Table implementation.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2010 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    09/09/2014 Unithra.C - Created.
******************************************************************************/
#ifdef APP_DEVICE_TYPE_THERMOSTAT

/******************************************************************************
                    Includes section
******************************************************************************/
#include <pdsDataServer.h>
#include <thThermostatCluster.h>
#include <thOccupancySensingCluster.h>
#include <thHumidityMeasurementCluster.h>
#include <thTemperatureMeasurementCluster.h>
#include <thScenes.h>

/******************************************************************************
                    PDT definitions
******************************************************************************/
#ifdef _ENABLE_PERSISTENT_SERVER_
/* Thermostat application data file descriptors.
   Shall be placed in the PDS_FF code segment. */
PDS_DECLARE_FILE(APP_TH_LOCAL_TEMPERATURE_MEM_ID,                 sizeof(thThermostatClusterServerAttributes.localTemperature),               &thThermostatClusterServerAttributes.localTemperature,              NO_FILE_MARKS);
PDS_DECLARE_FILE(APP_TH_OCCUPIED_COOLING_SETPOINT_MEM_ID,         sizeof(thThermostatClusterServerAttributes.occupiedCoolingSetpoint),        &thThermostatClusterServerAttributes.occupiedCoolingSetpoint,       NO_FILE_MARKS);
PDS_DECLARE_FILE(APP_TH_OCCUPIED_HEATING_SETPOINT_MEM_ID,         sizeof(thThermostatClusterServerAttributes.occupiedHeatingSetpoint),        &thThermostatClusterServerAttributes.occupiedHeatingSetpoint,       NO_FILE_MARKS);
PDS_DECLARE_FILE(APP_TH_OCCUPANCY_MEM_ID,                         sizeof(thOccupancySensingClusterServerAttributes.occupancy),                &thOccupancySensingClusterServerAttributes.occupancy,               NO_FILE_MARKS);
PDS_DECLARE_FILE(APP_TH_HUMIDITY_MEASURED_VALUE_MEM_ID,           sizeof(thHumidityMeasurementClusterServerAttributes.measuredValue),         &thHumidityMeasurementClusterServerAttributes.measuredValue,        NO_FILE_MARKS);
PDS_DECLARE_FILE(APP_TH_HUMIDITY_TOLERANCE_MEM_ID,                sizeof(thHumidityMeasurementClusterServerAttributes.tolerance),             &thHumidityMeasurementClusterServerAttributes.tolerance,            NO_FILE_MARKS);
PDS_DECLARE_FILE(APP_TH_SCENES_MEM_ID,                            MAX_SCENES_AMOUNT * sizeof(Scene_t),                                        scenePool,                                                          NO_FILE_MARKS);
PDS_DECLARE_FILE(APP_TH_TEMPERATURE_MEASURED_VALUE_MEM_ID,        sizeof(thTemperatureMeasurementClusterServerAttributes.measuredValue),      &thTemperatureMeasurementClusterServerAttributes.measuredValue,     NO_FILE_MARKS);
PDS_DECLARE_FILE(APP_TH_TEMPERATURE_TOLERANCE_MEM_ID,             sizeof(thTemperatureMeasurementClusterServerAttributes.tolerance),          &thTemperatureMeasurementClusterServerAttributes.tolerance,         NO_FILE_MARKS);
/* Thermostat application data file identifiers list.
   Will be placed in flash. */
PROGMEM_DECLARE(PDS_MemId_t appThMemoryIdsTable[]) =
{
  APP_TH_LOCAL_TEMPERATURE_MEM_ID,
  APP_TH_OCCUPIED_COOLING_SETPOINT_MEM_ID,
  APP_TH_OCCUPIED_HEATING_SETPOINT_MEM_ID,
  APP_TH_OCCUPANCY_MEM_ID,
  APP_TH_HUMIDITY_MEASURED_VALUE_MEM_ID,
  APP_TH_HUMIDITY_TOLERANCE_MEM_ID,
  APP_TH_SCENES_MEM_ID,
  APP_TH_TEMPERATURE_MEASURED_VALUE_MEM_ID,
  APP_TH_TEMPERATURE_TOLERANCE_MEM_ID
};

/* Thermostat application directory descriptor.
   Shall be placed in the PDS_FD code segment. */
PDS_DECLARE_DIR(PDS_DirDescr_t appEsiMemoryDirDescr) =
{
  .list       = appThMemoryIdsTable,
  .filesCount = ARRAY_SIZE(appThMemoryIdsTable),
  .memoryId   = HA_APP_MEMORY_MEM_ID
};

#endif // _ENABLE_PERSISTENT_SERVER_
#endif // APP_DEVICE_TYPE_THERMOSTAT

// eof thPdt.c
