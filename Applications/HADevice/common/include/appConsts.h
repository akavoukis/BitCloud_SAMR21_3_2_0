/************************************************************************//**
  \file appConst.h

  \brief
    Devices related definition.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    03.12.09 A. Kostyukov - Created.
******************************************************************************/

#ifndef _APPCONSTS_H
#define _APPCONSTS_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <appFramework.h>

/******************************************************************************
                    Defines section
******************************************************************************/
#define APP_PROFILE_ID PROFILE_ID_HOME_AUTOMATION

#define APP_ENDPOINT_DIMMABLE_LIGHT          0x11
#define APP_ENDPOINT_DIMMER_SWITCH           0x12
#define APP_ENDPOINT_COMBINED_INTERFACE      0x14

#define APP_ENDPOINT_MULTI_SENSOR            0x15
#define APP_ENDPOINT_OCCUPANCY_SENSOR        0x13
#define APP_ENDPOINT_TEMPERATURE_SENSOR      0x16
#define APP_ENDPOINT_HUMIDITY_SENSOR         0x17
#define APP_ENDPOINT_LIGHT_SENSOR            0x18
#define APP_ENDPOINT_THERMOSTAT              0x19
#define APP_ENDPOINT_IAS_ACE                 0x1A

// Organize device-related definitions and check device type setting.
// Usually this section shall not be changed by user.
#if defined(APP_DEVICE_TYPE_DIMMABLE_LIGHT)
  #define APP_DEVICE_TYPE DEV_TYPE_ROUTER
  #define APP_SRC_ENDPOINT_ID APP_ENDPOINT_DIMMABLE_LIGHT
  #define APP_ENDPOINTS_AMOUNT            1

#elif defined(APP_DEVICE_TYPE_MYAPP)
	#define APP_DEVICE_TYPE DEV_TYPE_ROUTER
	#define APP_SRC_ENDPOINT_ID APP_ENDPOINT_DIMMABLE_LIGHT
	#define APP_ENDPOINTS_AMOUNT            1

#elif defined(APP_DEVICE_TYPE_THERMOSTAT)
  #define APP_DEVICE_TYPE DEV_TYPE_ENDDEVICE//DEV_TYPE_ROUTER
  #define APP_SRC_ENDPOINT_ID APP_ENDPOINT_THERMOSTAT
  #define APP_ENDPOINTS_AMOUNT            1

#elif defined(APP_DEVICE_TYPE_DIMMER_SWITCH)
  #define APP_DEVICE_TYPE DEV_TYPE_ENDDEVICE
  #define APP_SRC_ENDPOINT_ID APP_ENDPOINT_DIMMER_SWITCH
  #define APP_ENDPOINTS_AMOUNT            1

#elif defined(APP_DEVICE_TYPE_MULTI_SENSOR)
  #define APP_DEVICE_TYPE DEV_TYPE_ENDDEVICE
  #define APP_SRC_ENDPOINT_ID  APP_ENDPOINT_MULTI_SENSOR
  #ifdef APP_SENSOR_TYPE_OCCUPANCY_SENSOR
    #define APP_SRC_ENDPOINT1_ID APP_ENDPOINT_OCCUPANCY_SENSOR
    #define OCCUPANCY_SENSOR_ENDPOINT     1
  #else
    #define OCCUPANCY_SENSOR_ENDPOINT     0
  #endif
  #ifdef APP_SENSOR_TYPE_TEMPERATURE_SENSOR
    #define APP_SRC_ENDPOINT2_ID APP_ENDPOINT_TEMPERATURE_SENSOR
    #define TEMPERATURE_SENSOR_ENDPOINT   1
  #else
    #define TEMPERATURE_SENSOR_ENDPOINT   0
  #endif
  #ifdef APP_SENSOR_TYPE_HUMIDITY_SENSOR  //manufacturer specific
    #define APP_SRC_ENDPOINT3_ID APP_ENDPOINT_HUMIDITY_SENSOR
    #define HUMIDITY_SENSOR_ENDPOINT      1
  #else
    #define HUMIDITY_SENSOR_ENDPOINT      0
  #endif
  #ifdef APP_SENSOR_TYPE_LIGHT_SENSOR
    #define APP_SRC_ENDPOINT4_ID APP_ENDPOINT_LIGHT_SENSOR
    #define LIGHT_SENSOR_ENDPOINT         1
  #else
    #define LIGHT_SENSOR_ENDPOINT         0
  #endif

  #define APP_ENDPOINTS_AMOUNT            (OCCUPANCY_SENSOR_ENDPOINT + TEMPERATURE_SENSOR_ENDPOINT + HUMIDITY_SENSOR_ENDPOINT + LIGHT_SENSOR_ENDPOINT)

#elif defined (APP_DEVICE_TYPE_COMBINED_INTERFACE)
  #define APP_DEVICE_TYPE DEV_TYPE_COORDINATOR
  #define APP_SRC_ENDPOINT_ID APP_ENDPOINT_COMBINED_INTERFACE
  #define APP_ENDPOINTS_AMOUNT              1
#elif defined (APP_DEVICE_TYPE_IAS_ACE)
  #define APP_DEVICE_TYPE DEV_TYPE_ENDDEVICE
  #define APP_SRC_ENDPOINT_ID APP_ENDPOINT_IAS_ACE
  #define APP_ENDPOINTS_AMOUNT              1
#else
  #error Device type is not detected
#endif

#ifndef APP_NETWORK_KEY
  #define APP_NETWORK_KEY {0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc}
#endif //#ifndef APP_NETWORK_KEY


//#define HA_LINK_KEY {0x5a,0x69,0x67,0x42,0x65,0x65,0x41,0x6c,0x6c,0x69,0x61,0x6e,0x63,0x65,0x30,0x39}
// For ZLL networks compatibility
//uncommented
#define HA_LINK_KEY {0xd0, 0xd1, 0xd2, 0xd3, 0xd4, 0xd5, 0xd6, 0xd7, 0xd8, 0xd9, 0xdA, 0xdb, 0xdc, 0xdd, 0xde, 0xdf}

#define HA_APP_MEMORY_MEM_ID                   APP_DIR1_MEM_ID
#define APP_DL_SCENES_MEM_ID                   APP_PARAM1_MEM_ID
#define APP_DL_ONOFF_MEM_ID                    APP_PARAM2_MEM_ID
#define APP_DL_LEVEL_CONTROL_MEM_ID            APP_PARAM3_MEM_ID
#ifdef APP_SENSOR_TYPE_OCCUPANCY_SENSOR
#define APP_MS_OCCUPANCY_MEM_ID                APP_PARAM1_MEM_ID
#endif
#ifdef APP_SENSOR_TYPE_TEMPERATURE_SENSOR
#define APP_MS_TEMP_MEASURED_VALUE_MEM_ID      APP_PARAM2_MEM_ID
#define APP_MS_TEMP_TOLERANCE_MEM_ID           APP_PARAM3_MEM_ID
#endif
#ifdef APP_SENSOR_TYPE_HUMIDITY_SENSOR
#define APP_MS_HUMIDITY_MEASURED_VALUE_MEM_ID  APP_PARAM4_MEM_ID
#define APP_MS_HUMIDITY_TOLERANCE_MEM_ID       APP_PARAM5_MEM_ID
#endif
#ifdef APP_SENSOR_TYPE_LIGHT_SENSOR
#define APP_MS_ILLU_MEASURED_VALUE_MEM_ID      APP_PARAM6_MEM_ID
#define APP_MS_ILLU_TOLERANCE_MEM_ID           APP_PARAM7_MEM_ID
#endif

#define APP_TH_LOCAL_TEMPERATURE_MEM_ID                APP_PARAM8_MEM_ID
#define APP_TH_OCCUPIED_COOLING_SETPOINT_MEM_ID        APP_PARAM9_MEM_ID
#define APP_TH_OCCUPIED_HEATING_SETPOINT_MEM_ID        APP_PARAM10_MEM_ID
#define APP_TH_OCCUPANCY_MEM_ID                        APP_PARAM11_MEM_ID
#define APP_TH_HUMIDITY_MEASURED_VALUE_MEM_ID          APP_PARAM12_MEM_ID
#define APP_TH_HUMIDITY_TOLERANCE_MEM_ID               APP_PARAM13_MEM_ID
#define APP_TH_SCENES_MEM_ID                           APP_PARAM14_MEM_ID
#define APP_TH_TEMPERATURE_MEASURED_VALUE_MEM_ID       APP_PARAM15_MEM_ID
#define APP_TH_TEMPERATURE_TOLERANCE_MEM_ID            APP_PARAM16_MEM_ID

#ifdef APP_DEVICE_TYPE_IAS_ACE
#define APP_IAS_ACE_ZONE_STATE_MEM_ID                    APP_PARAM1A_MEM_ID
#define APP_IAS_ACE_ZONE_TYPE_MEM_ID                     APP_PARAM1B_MEM_ID
#define APP_IAS_ACE_ZONE_STATUS_MEM_ID                   APP_PARAM1C_MEM_ID
#define APP_IAS_ACE_ZONE_CIE_ADDR_MEM_ID                 APP_PARAM1D_MEM_ID
#define APP_IAS_ACE_ZONE_ID_MEM_ID                       APP_PARAM1E_MEM_ID
#define APP_IAS_ACE_ZONE_NO_SENSITIVITY_LEVELS_MEM_ID    APP_PARAM1F_MEM_ID
#define APP_IAS_ACE_ZONE_NO_CURR_SENSITIVITY_LEV_MEM_ID  APP_PARAM20_MEM_ID
#endif

#endif // _APPCONSTS_H

// eof appConsts.h

