/**************************************************************************//**
  \file multiSensor.c

  \brief
    Mutli-Sensor implementation.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    12.12.12 N.Fomin - Created
    28.05.14 Viswanadham Kotla - Modified
******************************************************************************/

#ifdef APP_DEVICE_TYPE_MULTI_SENSOR

/******************************************************************************
                             Includes section
******************************************************************************/
#include <msClusters.h>
#include <zclDevice.h>
#include <uartManager.h>
#include <zclSecurityManager.h>
#include <console.h>
#include <identifyCluster.h>
#include <sysIdleHandler.h>
#include <ezModeManager.h>
#include <pdsDataServer.h>
#include <haClusters.h>
#include <otauService.h>
#include <sleep.h>
#include <halSleep.h>
#include <msOccupancySensingCluster.h>
#include <msTemperatureMeasurementCluster.h>
#include <msHumidityMeasurementCluster.h>
#include <msIlluminanceMeasurementCluster.h>
#include <basicCluster.h>
#include <msIdentifyCluster.h>
#include <msDiagnosticsCluster.h>

/******************************************************************************
                             Defines section
******************************************************************************/
#define SWITCHING_PERIOD                    20000UL

/* Multi sensor device type logical device Id form reserved space */
#define  APP_HA_MULTI_SENSOR_DEVICE_ID      0x01ff
/* Humidity Sensor logical device Id form reserved space */
#define APP_HA_HUMIDITY_SENSOR_DEVICE_ID    0x03ff

/******************************************************************************
                        Prototypes section
******************************************************************************/
static void isBusyOrPollCheck(SYS_EventId_t eventId, SYS_EventData_t data);
static void updateSensorsAttributeValues(void);
static void msConfigureReportingResp(ZCL_Notify_t *ntfy);
#if defined (_SLEEP_WHEN_IDLE_)
#if (APP_ENABLE_CONSOLE == 1)
static void sleepModeHandler(SYS_EventId_t eventId, SYS_EventData_t data);
#endif
static void sleepEventHandler(SYS_EventId_t eventId, SYS_EventData_t data);
static void ZDO_WakeUpConf(ZDO_WakeUpConf_t *conf);
#endif

/******************************************************************************
                    Local variables section
******************************************************************************/
static ZCL_DeviceEndpoint_t msEndpoint =
{
  .simpleDescriptor =
  {
    .endpoint            = APP_SRC_ENDPOINT_ID,
    .AppProfileId        = PROFILE_ID_HOME_AUTOMATION,
    .AppDeviceId         = APP_HA_MULTI_SENSOR_DEVICE_ID,
    .AppInClustersCount  = ARRAY_SIZE(msServerClusterIds),
    .AppInClustersList   = msServerClusterIds,
    .AppOutClustersCount = ARRAY_SIZE(msClientClusterIds),
    .AppOutClustersList  = msClientClusterIds,
  },
  .serverCluster = msServerClusters,
  .clientCluster = msClientClusters,
};

#ifdef APP_SENSOR_TYPE_OCCUPANCY_SENSOR
static ZCL_DeviceEndpoint_t osEndpoint =
{
  .simpleDescriptor =
  {
    .endpoint            = APP_SRC_ENDPOINT1_ID,
    .AppProfileId        = PROFILE_ID_HOME_AUTOMATION,
    .AppDeviceId         = HA_OCCUPANCY_SENSOR_DEVICE_ID,
    .AppInClustersCount  = ARRAY_SIZE(osServerClusterIds),
    .AppInClustersList   = osServerClusterIds,
    .AppOutClustersCount = 0,
    .AppOutClustersList  = NULL,
  },
  .serverCluster = osServerClusters,
  .clientCluster = NULL,//&osClientClusters,
};

static ClusterId_t osServerClusterToBindIds[] =
{
  OCCUPANCY_SENSING_CLUSTER_ID,
};

static AppBindReq_t osBindReq =
{
  .nwkAddrOfInterest = RX_ON_WHEN_IDLE_ADDR,
  .remoteServers     = NULL,
  .remoteServersCnt  = 0,
  .remoteClients     = osServerClusterToBindIds,
  .remoteClientsCnt  = ARRAY_SIZE(osServerClusterToBindIds),
  .profile           = PROFILE_ID_HOME_AUTOMATION,
  .srcEndpoint       = APP_SRC_ENDPOINT1_ID,
  .callback          = NULL,
};

#endif //APP_SENSOR_TYPE_OCCUPANCY_SENSOR

#ifdef APP_SENSOR_TYPE_TEMPERATURE_SENSOR
static ZCL_DeviceEndpoint_t tsEndpoint =
{
  .simpleDescriptor =
  {
    .endpoint            = APP_SRC_ENDPOINT2_ID,
    .AppProfileId        = PROFILE_ID_HOME_AUTOMATION,
    .AppDeviceId         = HA_TEMPERATURE_SENSOR_DEVICE_ID,
    .AppInClustersCount  = ARRAY_SIZE(tsServerClusterIds),
    .AppInClustersList   = tsServerClusterIds,
    .AppOutClustersCount = 0,
    .AppOutClustersList  = NULL,
  },
  .serverCluster = tsServerClusters,
  .clientCluster = NULL,
};

static ClusterId_t tsServerClusterToBindIds[] =
{
  TEMPERATURE_MEASUREMENT_CLUSTER_ID
};

static AppBindReq_t tsBindReq =
{
  .nwkAddrOfInterest = RX_ON_WHEN_IDLE_ADDR,
  .remoteServers     = NULL,
  .remoteServersCnt  = 0,
  .remoteClients     = tsServerClusterToBindIds,
  .remoteClientsCnt  = ARRAY_SIZE(tsServerClusterToBindIds),
  .profile           = PROFILE_ID_HOME_AUTOMATION,
  .srcEndpoint       = APP_SRC_ENDPOINT2_ID,
  .callback          = NULL,
};
#endif  //APP_SENSOR_TYPE_TEMPERATURE_SENSOR

#ifdef APP_SENSOR_TYPE_HUMIDITY_SENSOR
static ZCL_DeviceEndpoint_t hsEndpoint =
{
  .simpleDescriptor =
  {
    .endpoint            = APP_SRC_ENDPOINT3_ID,
    .AppProfileId        = PROFILE_ID_HOME_AUTOMATION,
    .AppDeviceId         = APP_HA_HUMIDITY_SENSOR_DEVICE_ID,
    .AppInClustersCount  = ARRAY_SIZE(hsServerClusterIds),
    .AppInClustersList   = hsServerClusterIds,
    .AppOutClustersCount = 0,
    .AppOutClustersList  = NULL,
  },
  .serverCluster = hsServerClusters,
  .clientCluster = NULL,
};

static ClusterId_t hsServerClusterToBindIds[] =
{
  HUMIDITY_MEASUREMENT_CLUSTER_ID
};

static AppBindReq_t hsBindReq =
{
  .nwkAddrOfInterest = RX_ON_WHEN_IDLE_ADDR,
  .remoteServers     = NULL,
  .remoteServersCnt  = 0,
  .remoteClients     = hsServerClusterToBindIds,
  .remoteClientsCnt  = ARRAY_SIZE(hsServerClusterToBindIds),
  .profile           = PROFILE_ID_HOME_AUTOMATION,
  .srcEndpoint       = APP_SRC_ENDPOINT3_ID,
  .callback          = NULL,
};
#endif  //APP_SENSOR_TYPE_HUMIDITY_SENSOR

#ifdef APP_SENSOR_TYPE_LIGHT_SENSOR
static ZCL_DeviceEndpoint_t lsEndpoint =
{
  .simpleDescriptor =
  {
    .endpoint            = APP_SRC_ENDPOINT4_ID,
    .AppProfileId        = PROFILE_ID_HOME_AUTOMATION,
    .AppDeviceId         = HA_LIGHT_SENSOR_DEVICE_ID,
    .AppInClustersCount  = ARRAY_SIZE(lsServerClusterIds),
    .AppInClustersList   = lsServerClusterIds,
    .AppOutClustersCount = 0,
    .AppOutClustersList  = NULL,
  },
  .serverCluster = lsServerClusters,
  .clientCluster = NULL,
};

static ClusterId_t lsServerClusterToBindIds[] =
{
  ILLUMINANCE_MEASUREMENT_CLUSTER_ID,
};

static AppBindReq_t lsBindReq =
{
  .nwkAddrOfInterest = RX_ON_WHEN_IDLE_ADDR,
  .remoteServers     = NULL,
  .remoteServersCnt  = 0,
  .remoteClients     = lsServerClusterToBindIds,
  .remoteClientsCnt  = ARRAY_SIZE(lsServerClusterToBindIds),
  .profile           = PROFILE_ID_HOME_AUTOMATION,
  .srcEndpoint       = APP_SRC_ENDPOINT4_ID,
  .callback          = NULL,
};
#endif //APP_SENSOR_TYPE_LIGHT_SENSOR

static ZCL_LinkKeyDesc_t keyDesc = {CCPU_TO_LE64(APS_UNIVERSAL_EXTENDED_ADDRESS), HA_LINK_KEY};

static HAL_AppTimer_t sensorAttributeUpdateTimer =
{
  .interval = SWITCHING_PERIOD,
  .mode     = TIMER_REPEAT_MODE,
  .callback = updateSensorsAttributeValues,
};

static SYS_EventReceiver_t zdoBusyPollCheck = { .func = isBusyOrPollCheck};

AppBindReq_t* deviceBindReqs[APP_ENDPOINTS_AMOUNT];
#if defined (_SLEEP_WHEN_IDLE_)
static ZDO_WakeUpReq_t zdoWakeUpReq;
static SYS_EventReceiver_t sleepEventListener = {.func = sleepEventHandler};
#if (APP_ENABLE_CONSOLE == 1)
static SYS_EventReceiver_t sleepModeListener = {.func = sleepModeHandler};
#endif
#endif

/******************************************************************************
                   type(s) section
******************************************************************************/
typedef enum _ReportingState_t
{
  OCCUPANCY_SENSOR_REPORTING_CONFIGURED = 1,
  TEMPERATURE_SENSOR_MEASURED_VALUE_REPORTING_CONFIGURED,
  TEMPERATURE_SENSOR_TOLERANCE_VALUE_REPORTING_CONFIGURED,
  HUMIDITY_SENSOR_MEASURED_VALUE_REPORTING_CONFIGURED,
  HUMIDITY_SENSOR_TOLERANCE_VALUE_REPORTING_CONFIGURED,
  LIGHT_SENSOR_MEASURED_VALUE_REPORTING_CONFIGURED,
  LIGHT_SENSOR_TOLERANCE_VALUE_REPORTING_CONFIGURED,
  CONFIGURE_REPORTING_COMPLETED
}ReportingState_t;

/******************************************************************************
                    Static variables section
******************************************************************************/
static ReportingState_t configureReportingState = 0;

/******************************************************************************
                    Implementation section
******************************************************************************/
/**************************************************************************//**
\brief Device initialization routine
******************************************************************************/
void appDeviceInit(void)
{
  uint8_t epIndex = 0;

/* Bind requests with clusters to bind for initiator device */
#ifdef APP_SENSOR_TYPE_OCCUPANCY_SENSOR
  deviceBindReqs[epIndex++] = &osBindReq;
#endif
#ifdef APP_SENSOR_TYPE_TEMPERATURE_SENSOR
  deviceBindReqs[epIndex++] = &tsBindReq;
#endif
#ifdef APP_SENSOR_TYPE_HUMIDITY_SENSOR
  deviceBindReqs[epIndex++] = &hsBindReq;
#endif
#ifdef APP_SENSOR_TYPE_LIGHT_SENSOR
  deviceBindReqs[epIndex++] = &lsBindReq;
#endif

  ZCL_RegisterEndpoint(&msEndpoint);

  basicClusterInit();
  identifyClusterInit();
  diagnosticsClusterInit();
  /* Register defined endpoints */
#ifdef APP_SENSOR_TYPE_OCCUPANCY_SENSOR
  ZCL_RegisterEndpoint(&osEndpoint);
  occupancySensingClusterInit();
  
  if (PDS_IsAbleToRestore(APP_MS_OCCUPANCY_MEM_ID))
    PDS_Restore(APP_MS_OCCUPANCY_MEM_ID);
#endif

#ifdef APP_SENSOR_TYPE_TEMPERATURE_SENSOR
  ZCL_RegisterEndpoint(&tsEndpoint);
  temperatureMeasurementClusterInit();

  if (PDS_IsAbleToRestore(APP_MS_TEMP_MEASURED_VALUE_MEM_ID))
    PDS_Restore(APP_MS_TEMP_MEASURED_VALUE_MEM_ID);

  if (PDS_IsAbleToRestore(APP_MS_TEMP_TOLERANCE_MEM_ID))
    PDS_Restore(APP_MS_TEMP_TOLERANCE_MEM_ID);
#endif

#ifdef APP_SENSOR_TYPE_HUMIDITY_SENSOR
  ZCL_RegisterEndpoint(&hsEndpoint);
  humidityMeasurementClusterInit();

  if (PDS_IsAbleToRestore(APP_MS_HUMIDITY_MEASURED_VALUE_MEM_ID))
    PDS_Restore(APP_MS_HUMIDITY_MEASURED_VALUE_MEM_ID);

  if (PDS_IsAbleToRestore(APP_MS_HUMIDITY_TOLERANCE_MEM_ID))
    PDS_Restore(APP_MS_HUMIDITY_TOLERANCE_MEM_ID);
#endif

#ifdef APP_SENSOR_TYPE_LIGHT_SENSOR
  ZCL_RegisterEndpoint(&lsEndpoint);
  illuminanceMeasurementClusterInit();

  if (PDS_IsAbleToRestore(APP_MS_ILLU_MEASURED_VALUE_MEM_ID))
    PDS_Restore(APP_MS_ILLU_MEASURED_VALUE_MEM_ID);

  if (PDS_IsAbleToRestore(APP_MS_ILLU_TOLERANCE_MEM_ID))
    PDS_Restore(APP_MS_ILLU_TOLERANCE_MEM_ID);
#endif

  /* Timer update the attribute values of various sensor types */
  HAL_StartAppTimer(&sensorAttributeUpdateTimer);

#if (APP_ENABLE_CONSOLE == 1) || (APP_DEVICE_EVENTS_LOGGING == 1)
  uartInit();
#endif
#if APP_ENABLE_CONSOLE == 1
  initConsole();
#endif

#if defined (_SLEEP_WHEN_IDLE_)
  SYS_EnableSleepWhenIdle();
#if (APP_ENABLE_CONSOLE == 1)
  SYS_SubscribeToEvent(HAL_EVENT_FALLING_ASLEEP, &sleepModeListener);
  SYS_SubscribeToEvent(HAL_EVENT_CONTINUING_SLEEP, &sleepModeListener);
#endif
  SYS_SubscribeToEvent(HAL_EVENT_WAKING_UP, &sleepEventListener);
#endif
  SYS_SubscribeToEvent(BC_EVENT_POLL_REQUEST, &zdoBusyPollCheck);

  ZCL_StartReporting();
}

/**************************************************************************//**
\breif Performs security initialization actions
******************************************************************************/
void appSecurityInit(void)
{
  ZCL_Set_t zclSet;

  ZCL_ResetSecurity();

  zclSet.attr.id = ZCL_LINK_KEY_DESC_ID;
  zclSet.attr.value.linkKeyDesc = &keyDesc;
  ZCL_Set(&zclSet);
}

/**************************************************************************//**
\brief Device common task handler
******************************************************************************/
void appDeviceTaskHandler(void)
{
  switch (appDeviceState) // Actual device state when one joined network
  {
    case DEVICE_INITIAL_STATE:
      {
        appDeviceState = DEVICE_ACTIVE_IDLE_STATE;
        startOtauClient(&msClientClusters[MS_CLIENT_CLUSTERS_COUNT - 1]);
      }
      break;
    case DEVICE_ACTIVE_IDLE_STATE:
    default:
      break;
  }
}

/**************************************************************************//**
\brief Gets bind request

\return pointer to a bind request used by HA device
******************************************************************************/
AppBindReq_t **getDeviceBindRequest(void)
{
  return deviceBindReqs;
}

/**************************************************************************//**
\brief Stops application
******************************************************************************/
void appStop(void)
{
  HAL_StopAppTimer(&sensorAttributeUpdateTimer);
  identifyClusterStop();
}

/**************************************************************************//**
\brief Asks device if it is an initiator

\returns true if it is, false otherwise
******************************************************************************/
bool appIsInitiator(void)
{
  return true;
}

/**************************************************************************//**
\brief EZ-Mode done callback

\returns function which is called by EZ-Mode manager when it is done
******************************************************************************/
void appEzModeDone(void)
{
#ifdef APP_SENSOR_TYPE_OCCUPANCY_SENSOR
    sendConfigureReportingToNotify(APP_SRC_ENDPOINT1_ID, APP_ENDPOINT_COMBINED_INTERFACE, OCCUPANCY_SENSING_CLUSTER_ID,
      ZCL_OCCUPANCY_SENSING_CLUSTER_OCCUPANCY_SERVER_ATTRIBUTE_ID, OCCUPANCY_SENSING_VAL_MAX_REPORT_PERIOD, msConfigureReportingResp);
    configureReportingState = OCCUPANCY_SENSOR_REPORTING_CONFIGURED;
    
#elif defined APP_SENSOR_TYPE_TEMPERATURE_SENSOR
    sendConfigureReportingToNotify(APP_SRC_ENDPOINT2_ID, APP_ENDPOINT_COMBINED_INTERFACE, TEMPERATURE_MEASUREMENT_CLUSTER_ID,
      ZCL_TEMPERATURE_MEASUREMENT_CLUSTER_SERVER_MEASURED_VALUE_ATTRIBUTE_ID, TEMPERATURE_MEASUREMENT_VAL_MAX_REPORT_PERIOD, msConfigureReportingResp);
    configureReportingState = TEMPERATURE_SENSOR_MEASURED_VALUE_REPORTING_CONFIGURED;
    
#elif defined APP_SENSOR_TYPE_HUMIDITY_SENSOR
    sendConfigureReportingToNotify(APP_SRC_ENDPOINT3_ID, APP_ENDPOINT_COMBINED_INTERFACE, HUMIDITY_MEASUREMENT_CLUSTER_ID,
      ZCL_HUMIDITY_MEASUREMENT_CLUSTER_SERVER_MEASURED_VALUE_ATTRIBUTE_ID, HUMIDITY_MEASUREMENT_VAL_MAX_REPORT_PERIOD, msConfigureReportingResp);
    configureReportingState = HUMIDITY_SENSOR_MEASURED_VALUE_REPORTING_CONFIGURED;
    
#elif defined APP_SENSOR_TYPE_LIGHT_SENSOR
    sendConfigureReportingToNotify(APP_SRC_ENDPOINT4_ID, APP_ENDPOINT_COMBINED_INTERFACE, ILLUMINANCE_MEASUREMENT_CLUSTER_ID,
      ZCL_ILLUMINANCE_MEASUREMENT_CLUSTER_MEASURED_VALUE_SERVER_ATTRIBUTE_ID, ILLUMINANCE_MEASUREMENT_VAL_MAX_REPORT_PERIOD, msConfigureReportingResp);
    configureReportingState = LIGHT_SENSOR_MEASURED_VALUE_REPORTING_CONFIGURED;

#endif

  ZCL_StartReporting();
}

/**************************************************************************//**
\brief Indication of configure reporting response

\param[in] resp - pointer to response
******************************************************************************/
static void msConfigureReportingResp(ZCL_Notify_t *ntfy)
{
  // The following state machine checks the reported state of a sensor and will try to send another reporting if that sensor is enabled.
  // If that sensor is not enabled it will try to send the reporting of next available/enabled sensor.
  // If all the sensors have finished reporting the status of the state machine will be changed to CONFIGURE_REPORTING_COMPLETED.
  switch (configureReportingState)
  {
  case OCCUPANCY_SENSOR_REPORTING_CONFIGURED:
#ifdef APP_SENSOR_TYPE_TEMPERATURE_SENSOR
    sendConfigureReportingToNotify(APP_SRC_ENDPOINT2_ID, APP_ENDPOINT_COMBINED_INTERFACE, TEMPERATURE_MEASUREMENT_CLUSTER_ID,
      ZCL_TEMPERATURE_MEASUREMENT_CLUSTER_SERVER_MEASURED_VALUE_ATTRIBUTE_ID, TEMPERATURE_MEASUREMENT_VAL_MAX_REPORT_PERIOD, msConfigureReportingResp);
    configureReportingState = TEMPERATURE_SENSOR_MEASURED_VALUE_REPORTING_CONFIGURED;
    break;
#endif
  case TEMPERATURE_SENSOR_MEASURED_VALUE_REPORTING_CONFIGURED:
#ifdef APP_SENSOR_TYPE_TEMPERATURE_SENSOR
    sendConfigureReportingToNotify(APP_SRC_ENDPOINT2_ID, APP_ENDPOINT_COMBINED_INTERFACE, TEMPERATURE_MEASUREMENT_CLUSTER_ID,
      ZCL_TEMPERATURE_MEASUREMENT_CLUSTER_SERVER_TOLERANCE_ATTRIBUTE_ID, TEMPERATURE_MEASUREMENT_VAL_MAX_REPORT_PERIOD, msConfigureReportingResp);
    configureReportingState = TEMPERATURE_SENSOR_TOLERANCE_VALUE_REPORTING_CONFIGURED;
    break;
#endif
  case TEMPERATURE_SENSOR_TOLERANCE_VALUE_REPORTING_CONFIGURED:
#ifdef APP_SENSOR_TYPE_HUMIDITY_SENSOR
    sendConfigureReportingToNotify(APP_SRC_ENDPOINT3_ID, APP_ENDPOINT_COMBINED_INTERFACE, HUMIDITY_MEASUREMENT_CLUSTER_ID,
      ZCL_HUMIDITY_MEASUREMENT_CLUSTER_SERVER_MEASURED_VALUE_ATTRIBUTE_ID, HUMIDITY_MEASUREMENT_VAL_MAX_REPORT_PERIOD, msConfigureReportingResp);
    configureReportingState = HUMIDITY_SENSOR_MEASURED_VALUE_REPORTING_CONFIGURED;
    break;
#endif
  case HUMIDITY_SENSOR_MEASURED_VALUE_REPORTING_CONFIGURED:
#ifdef APP_SENSOR_TYPE_HUMIDITY_SENSOR
    sendConfigureReportingToNotify(APP_SRC_ENDPOINT3_ID, APP_ENDPOINT_COMBINED_INTERFACE, HUMIDITY_MEASUREMENT_CLUSTER_ID,
      ZCL_HUMIDITY_MEASUREMENT_CLUSTER_SERVER_TOLERANCE_ATTRIBUTE_ID, HUMIDITY_MEASUREMENT_VAL_MAX_REPORT_PERIOD, msConfigureReportingResp);
    configureReportingState = HUMIDITY_SENSOR_TOLERANCE_VALUE_REPORTING_CONFIGURED;
    break;
#endif
  case HUMIDITY_SENSOR_TOLERANCE_VALUE_REPORTING_CONFIGURED:
#ifdef APP_SENSOR_TYPE_LIGHT_SENSOR
    sendConfigureReportingToNotify(APP_SRC_ENDPOINT4_ID, APP_ENDPOINT_COMBINED_INTERFACE, ILLUMINANCE_MEASUREMENT_CLUSTER_ID,
      ZCL_ILLUMINANCE_MEASUREMENT_CLUSTER_MEASURED_VALUE_SERVER_ATTRIBUTE_ID, ILLUMINANCE_MEASUREMENT_VAL_MAX_REPORT_PERIOD, msConfigureReportingResp);
    configureReportingState = LIGHT_SENSOR_MEASURED_VALUE_REPORTING_CONFIGURED;
    break;
#endif
  case LIGHT_SENSOR_MEASURED_VALUE_REPORTING_CONFIGURED:
#ifdef APP_SENSOR_TYPE_LIGHT_SENSOR
    sendConfigureReportingToNotify(APP_SRC_ENDPOINT4_ID, APP_ENDPOINT_COMBINED_INTERFACE, ILLUMINANCE_MEASUREMENT_CLUSTER_ID,
      ZCL_ILLUMINANCE_MEASUREMENT_CLUSTER_TOLERANCE_SERVER_ATTRIBUTE_ID, ILLUMINANCE_MEASUREMENT_VAL_MAX_REPORT_PERIOD, msConfigureReportingResp);
    configureReportingState = LIGHT_SENSOR_TOLERANCE_VALUE_REPORTING_CONFIGURED;
    break;
#endif
  default:
    configureReportingState = CONFIGURE_REPORTING_COMPLETED;
    break;
  }
  (void)ntfy;
}

/**************************************************************************//**
\brief Periodic update of various attributes of different sensors
*****************************************************************************/
static void updateSensorsAttributeValues(void)
{
#ifdef APP_SENSOR_TYPE_OCCUPANCY_SENSOR
  occupancySensingToggleOccupancy();
#endif
#ifdef APP_SENSOR_TYPE_TEMPERATURE_SENSOR
  tempeartureMeasurementUpdateMeasuredValue();
#endif
#ifdef APP_SENSOR_TYPE_HUMIDITY_SENSOR
  humidityMeasurementUpdateMeasuredValue();
#endif
#ifdef APP_SENSOR_TYPE_LIGHT_SENSOR
  illuminanceMeasurementUpdateMeasuredValue();
#endif

}
/**************************************************************************//**
\brief ZDO Binding indication function

\param[out] bindInd - ZDO bind indication parameters structure pointer.
                      For details go to ZDO_BindInd_t declaration
******************************************************************************/
void ZDO_BindIndication(ZDO_BindInd_t *bindInd)
{
  (void)bindInd;
}

/**************************************************************************//**
\brief ZDO Unbinding indication function

\param[out] unbindInd - ZDO unbind indication parameters structure pointer.
                        For details go to ZDO_UnbindInd_t declaration
******************************************************************************/
void ZDO_UnbindIndication(ZDO_UnbindInd_t *unbindInd)
{
  (void)unbindInd;
}

/**************************************************************************//**
  \brief Processes BC_EVENT_POLL_REQUEST event

  \param[in] eventId - id of raised event;
  \param[in] data    - event's data.
******************************************************************************/
static void isBusyOrPollCheck(SYS_EventId_t eventId, SYS_EventData_t data)
{
#if defined (_SLEEP_WHEN_IDLE_)
  bool *check = (bool *)data;

  *check |= isEzModeInProgress();
  (void)eventId;
#else
  (void)eventId, (void)data;
#endif
}

#if defined (_SLEEP_WHEN_IDLE_)
/**************************************************************************//**
  \brief Processes HAL_EVENT_WAKING_UP event

  \param[in] eventId - id of raised event;
  \param[in] data    - event's data.
******************************************************************************/
static void sleepEventHandler(SYS_EventId_t eventId, SYS_EventData_t data)
{
  HAL_SleepControl_t *sleepControl = (HAL_SleepControl_t *)data;

  if (HAL_WAKEUP_SOURCE_EXT_IRQ == sleepControl->wakeupSource)
  {
    zdoWakeUpReq.ZDO_WakeUpConf = ZDO_WakeUpConf;
    ZDO_WakeUpReq(&zdoWakeUpReq);
  }
  (void)eventId;
}

/**************************************************************************//**
  \brief Wake up confirmation handler.

  \param[in] conf - confirmation parameters.
*****************************************************************************/
static void ZDO_WakeUpConf(ZDO_WakeUpConf_t *conf)
{
  (void)conf;
}

#if (APP_ENABLE_CONSOLE == 1)
/**************************************************************************//**
  \brief Processes HAL_EVENT_FALL_ASLEEP & HAL_EVENT_CONITUING_SLEEP events

  \param[in] eventId - id of raised event;
  \param[in] data    - event's data.
******************************************************************************/
static void sleepModeHandler(SYS_EventId_t eventId, SYS_EventData_t data)
{
  // when console is enabled, we go to idle mode to handle UART Rx interrupt
  // because UART Rx interrupt will not wake up the MCU from power save or power down modes
  *(HAL_SleepMode_t *)data = HAL_SLEEP_MODE_IDLE;
  (void)eventId;
}
#endif // #if (APP_ENABLE_CONSOLE == 1)
#endif // #if defined (_SLEEP_WHEN_IDLE_)
#endif // APP_DEVICE_TYPE_MULTI_SENSOR
// eof multiSensor.c