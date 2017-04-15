/**************************************************************************//**
  \file thermostat.c

  \brief
    Thermostat implementation.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    09/09/2014 Unithra.C  - Created
******************************************************************************/
#ifdef APP_DEVICE_TYPE_THERMOSTAT

/******************************************************************************
                             Includes section
******************************************************************************/
#include <thClusters.h>
#include <basicCluster.h>
#include <identifyCluster.h>
#include <thThermostatCluster.h>
#include <thThermostatUiConfCluster.h>
#include <zclDevice.h>
#include <zclSecurityManager.h>
#include <commandManager.h>
#include <uartManager.h>
#include <console.h>
#include <pdsDataServer.h>
#include <ezModeManager.h>
#include <haClusters.h>
#include <otauService.h>
#include <thOccupancySensingCluster.h>
#include <thFanControlCluster.h>
#include <thDiagnosticsCluster.h>
#include <thHumidityMeasurementCluster.h>
#include <thGroupsCluster.h>
#include <thScenesCluster.h>
#include <thTemperatureMeasurementCluster.h>
#ifdef BOARD_QTOUCH_XPRO
#include <qtTaskManager.h>
#endif
#include <sleep.h>
#include <halSleep.h>
#include <sysIdleHandler.h>
/******************************************************************************
                   Define(s) section
******************************************************************************/
#define UPDATING_PERIOD                    20000UL

/******************************************************************************
                   type(s) section
******************************************************************************/
typedef enum _ReportingState_t
{
  THERMOSTAT_REPORTING_CONFIGURED = 0,
  OCCUPANCY_REPORTING_CONFIGURED,
  HUMIDITY_MEASURED_VALUE_REPORTING_CONFIGURED,
  HUMIDITY_TOLERANCE_VALUE_REPORTING_CONFIGURED,
  TEMPERATURE_MEASURED_VALUE_REPORTING_CONFIGURED,
  TEMPERATURE_TOLERANCE_VALUE_REPORTING_CONFIGURED,
  CONFIGURATION_COMPLETED
}ReportingState_t;

/*******************************************************************************
                    Static functions section
*******************************************************************************/
static void updateCommissioningStateCb(ZCL_Addressing_t *addressing, ZCL_UpdateCommissioningState_t *payload);
static void updateSensorsAttributeValues(void);

static void isBusyOrPollCheck(SYS_EventId_t eventId, SYS_EventData_t data);
#if defined (_SLEEP_WHEN_IDLE_)
#if (APP_ENABLE_CONSOLE == 1)
static void sleepModeHandler(SYS_EventId_t eventId, SYS_EventData_t data);
#endif
static void sleepEventHandler(SYS_EventId_t eventId, SYS_EventData_t data);
static void ZDO_WakeUpConf(ZDO_WakeUpConf_t *conf);
#endif

#ifdef BOARD_QTOUCH_XPRO
#define TOUCH_TIMEOUT 5000
static void appButtonsInd( BSP_TouchEvent_t event, BSP_ButtonId_t button, uint8_t data);
static uint8_t appConvertTemperatureToSliderPosition(int16_t temperature, int16_t min,int16_t max);
static bool setPointChangeStatusR = false,setPointChangeStatusL = false;
static BSP_ButtonId_t button_prev= NONE;
static bool setPointRecFlag = false;
static uint8_t slider_thershold;
static void touchTimeOut(void);
static HAL_AppTimer_t TouchTimer={
  .interval = TOUCH_TIMEOUT,
  .mode = TIMER_ONE_SHOT_MODE,
  .callback = touchTimeOut,
};
#endif

static SYS_EventReceiver_t zdoBusyPollCheck = { .func = isBusyOrPollCheck};
#if defined (_SLEEP_WHEN_IDLE_)
static ZDO_WakeUpReq_t zdoWakeUpReq;
static SYS_EventReceiver_t sleepEventListener = {.func = sleepEventHandler};
#if (APP_ENABLE_CONSOLE == 1)
static SYS_EventReceiver_t sleepModeListener = {.func = sleepModeHandler};
#endif
#endif

/******************************************************************************
                    Local variables section
******************************************************************************/
static ZCL_DeviceEndpoint_t thEndpoint =
{
  .simpleDescriptor =
  {
    .endpoint            = APP_SRC_ENDPOINT_ID,
    .AppProfileId        = PROFILE_ID_HOME_AUTOMATION,
    .AppDeviceId         = HA_THERMOSTAT_DEVICE_ID,
    .AppInClustersCount  = ARRAY_SIZE(thServerClusterIds),
    .AppInClustersList   = thServerClusterIds,
    .AppOutClustersCount = ARRAY_SIZE(thClientClusterIds),
    .AppOutClustersList  = thClientClusterIds,
  },
  .serverCluster = thServerClusters,
  .clientCluster = thClientClusters,
};

static ZCL_LinkKeyDesc_t thermostatKeyDesc = {APS_UNIVERSAL_EXTENDED_ADDRESS  /*addr*/,
                                         HA_LINK_KEY /*key*/};

static IdentifySubscriber_t subcriber =
{
  .updateCommissioningState = updateCommissioningStateCb
};

static HAL_AppTimer_t sensorAttributeUpdateTimer =
{
  .interval = UPDATING_PERIOD,
  .mode     = TIMER_REPEAT_MODE,
  .callback = updateSensorsAttributeValues,
};
/******************************************************************************
                    Prototypes section
******************************************************************************/
static void thConfigureReportingResp(ZCL_Notify_t *ntfy);
/******************************************************************************
                    Implementation section
******************************************************************************/

/**************************************************************************//**
\brief Device initialization routine
******************************************************************************/
void appDeviceInit(void)
{
  ZCL_RegisterEndpoint(&thEndpoint);

#if (APP_ENABLE_CONSOLE == 1) || (APP_DEVICE_EVENTS_LOGGING == 1)
  uartInit();
#endif
#if APP_ENABLE_CONSOLE == 1
  initConsole();
#endif
  /* Subscribe the Commissioning update command for Target devices */
  identifySubscribe(&subcriber);

  basicClusterInit();
  identifyClusterInit();
  thermostatClusterInit();
  thermostatUiConfClusterInit();
  occupancySensingClusterInit();
  fanControlClusterInit();
  diagnosticsClusterInit();
  humidityMeasurementClusterInit();
  groupsClusterInit();
  scenesClusterInit();
  thTemperatureMeasurementClusterInit();
  
#ifdef BOARD_QTOUCH_XPRO  
  BSP_InitQTouch(appButtonsInd);
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
  
  if (PDS_IsAbleToRestore(HA_APP_MEMORY_MEM_ID))
    PDS_Restore(HA_APP_MEMORY_MEM_ID);

  ZCL_StartReporting();

  /* Timer update the attribute values of various sensor types */
  HAL_StartAppTimer(&sensorAttributeUpdateTimer);
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

#ifdef BOARD_QTOUCH_XPRO

/**************************************************************************//**
\brief callback for touch Timer
******************************************************************************/
static void touchTimeOut(void)
{
  HAL_StopAppTimer(&TouchTimer);
  setPointChangeStatusR = false;
  button_prev = NONE;
  setPointRecFlag = false;
  setPointChangeStatusL = false;
  //ButtonR_LED_Ind(1);
  //ButtonL_LED_Ind(1);
  //Slider_LED_Off();
}

/**************************************************************************//**
\brief Buttons handler

\param[in] event - event
\param[in] button - index
\param[in] data - data (AKA hold time)
******************************************************************************/
void appButtonsInd(BSP_TouchEvent_t event, BSP_ButtonId_t button, uint8_t data)
{
  uint8_t Pos;
  if (BUTTON_R == button) // Heat set Point  Right
  {
    if( event == TOUCHKEY_PRESSED_EVENT) 
    {
      if(setPointChangeStatusR != true && setPointRecFlag == false)
      {
        if(setPointRecFlag == false && setPointChangeStatusL == true)
        {
          //ButtonL_LED_Ind(1);  // OFF
          setPointChangeStatusL = false;
        }        
        //ButtonR_LED_Ind(0);
        Pos = appConvertTemperatureToSliderPosition(thThermostatClusterServerAttributes.occupiedHeatingSetpoint.value,MIN_HEAT_SETPOINT_LIMIT,MAX_HEAT_SETPOINT_LIMIT);
        //Slider_LED_On(Pos);
        setPointChangeStatusR = true;
        button_prev = BUTTON_R;
        setPointRecFlag = false;
        HAL_StopAppTimer(&TouchTimer);
        HAL_StartAppTimer(&TouchTimer);
  
        LOG_STRING(modeStr, "#heat setpoint:%d.%d\r\n");
        appSnprintf(modeStr, (thThermostatClusterServerAttributes.occupiedHeatingSetpoint.value/100),(int)(thThermostatClusterServerAttributes.occupiedHeatingSetpoint.value%100));
      }
      else
      {
        setPointChangeStatusR = false;
      }
    }
    else
    {
      if(setPointRecFlag == true && button_prev == BUTTON_R)
      {
        //ButtonR_LED_Ind(1);
        //Slider_LED_Off();
        setPointRecFlag = false;
        setPointChangeStatusR = false;
        thermostatSetPointsChangeButton(0,slider_thershold);
        
        LOG_STRING(reportAttrIndStr, "<-Setpoints changed on Thermostat:\r\n");
        appSnprintf(reportAttrIndStr);
        LOG_STRING(modeStr1, "#heat setpoint:%d.%d\r\n");
        appSnprintf(modeStr1, (thThermostatClusterServerAttributes.occupiedHeatingSetpoint.value/100),(int)(thThermostatClusterServerAttributes.occupiedHeatingSetpoint.value%100));
        
        button_prev = NONE;
        HAL_StopAppTimer(&TouchTimer);
      }
      else if(setPointRecFlag == false && setPointChangeStatusR == false)
      {
        //ButtonR_LED_Ind(1);
        //Slider_LED_Off();
        HAL_StopAppTimer(&TouchTimer);
      }
    }
  }
  
  if (BUTTON_L == button)  // Left Cool
  {
    if( event == TOUCHKEY_PRESSED_EVENT)
    {
      if(setPointChangeStatusL != true && setPointRecFlag == false)
      {
        if(setPointRecFlag == false && setPointChangeStatusR == true)
        {
          //ButtonR_LED_Ind(1);  // OFF
          setPointChangeStatusR = false;
        }
        //ButtonL_LED_Ind(0);
        Pos = appConvertTemperatureToSliderPosition(thThermostatClusterServerAttributes.occupiedCoolingSetpoint.value,MIN_COOL_SETPOINT_LIMIT,MAX_COOL_SETPOINT_LIMIT);        
        //Slider_LED_On(Pos);
        setPointChangeStatusL = true;
        button_prev = BUTTON_L;
        setPointRecFlag = false;
        HAL_StopAppTimer(&TouchTimer);
        HAL_StartAppTimer(&TouchTimer);
        LOG_STRING(amtStr, "#cool setpoint: %d.%d\r\n");
        appSnprintf(amtStr, (thThermostatClusterServerAttributes.occupiedCoolingSetpoint.value/100),(int)(thThermostatClusterServerAttributes.occupiedCoolingSetpoint.value%100));        
      }
      else
      {
        setPointChangeStatusL = false;
      }
    }
    else
    {
      if(setPointRecFlag == true && button_prev == BUTTON_L)
      {
        //ButtonL_LED_Ind(1);
        //Slider_LED_Off();
        setPointRecFlag = false;
        setPointChangeStatusL = false;
        thermostatSetPointsChangeButton(1,slider_thershold);
        
        LOG_STRING(reportAttrIndStr1, "<-Setpoints changed on Thermostat:\r\n");
        appSnprintf(reportAttrIndStr1);
        LOG_STRING(amtStr1, "#cool setpoint: %d.%d\r\n");
        appSnprintf(amtStr1, (thThermostatClusterServerAttributes.occupiedCoolingSetpoint.value/100),(int)(thThermostatClusterServerAttributes.occupiedCoolingSetpoint.value%100));     
        
        button_prev = NONE;
        HAL_StopAppTimer(&TouchTimer);
      }
      else if(setPointRecFlag == false && setPointChangeStatusL == false)
      {
        //ButtonL_LED_Ind(1);
        //Slider_LED_Off();
        HAL_StopAppTimer(&TouchTimer);
      }
    }
  }
  
  if(BUTTON_SLIDER == button)
  { 
    if(button_prev != NONE)
    {
      if( event == TOUCHKEY_PRESSED_EVENT)
      {
        slider_thershold = data;
        setPointRecFlag = true;
        HAL_StopAppTimer(&TouchTimer);
        HAL_StartAppTimer(&TouchTimer);
      }
        //Slider_LED_On(slider_thershold);
    }
  }
}

static uint8_t appConvertTemperatureToSliderPosition(int16_t temperature, int16_t min,int16_t max)
{
  uint8_t slider_position;
  uint32_t temp;
  temperature = temperature;// / 100;
  temp = ((temperature - min) * 255 * 100)/ (max-min);
  temp = temp/100;
  slider_position = (uint8_t)temp;
  return slider_position;
}
#endif
/**************************************************************************//**
\breif Performs security initialization actions
******************************************************************************/
void appSecurityInit(void)
{
  ZCL_Set_t zclSet;

  ZCL_ResetSecurity();
  zclSet.attr.id = ZCL_LINK_KEY_DESC_ID;
  zclSet.attr.value.linkKeyDesc = &thermostatKeyDesc;
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
      }
#ifdef OTAU_CLIENT
      startOtauClient(&thClientClusters[TH_CLIENT_CLUSTERS_COUNT - 1]);
#endif
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
  return NULL;
}

/**************************************************************************//**
\brief Stops application
******************************************************************************/
void appStop(void)
{
  identifyClusterStop();
}

/**************************************************************************//**
\brief Asks device if it is an initiator

\returns true if it is, false otherwise
******************************************************************************/
bool appIsInitiator(void)
{
  return false;
}

/**************************************************************************//**
\brief EZ-Mode done callback

\returns function which is called by EZ-Mode manager when it is done
******************************************************************************/
void appEzModeDone(void)
{}

/**************************************************************************//**
\brief Update Commissioning State received callback

\param[in] addressing - pointer to addressing information;
\param[in] payload - data pointer
******************************************************************************/
static void updateCommissioningStateCb(ZCL_Addressing_t *addressing, ZCL_UpdateCommissioningState_t *payload)
{
  sendConfigureReportingToNotify(APP_SRC_ENDPOINT_ID, APP_ENDPOINT_COMBINED_INTERFACE, THERMOSTAT_CLUSTER_ID,
    ZCL_THERMOSTAT_CLUSTER_LOCAL_TEMPERATURE_SERVER_ATTRIBUTE_ID, THERMOSTAT_LOCAL_TEMPERATURE_MAX_REPORT_PERIOD, thConfigureReportingResp);

  ZCL_StartReporting();
  (void)addressing, (void)payload;
}
/**************************************************************************//**
\brief Indication of configure reporting response

\param[in] resp - pointer to response
******************************************************************************/
static void thConfigureReportingResp(ZCL_Notify_t *ntfy)
{
  static ReportingState_t configureReportingState = THERMOSTAT_REPORTING_CONFIGURED;

  switch (configureReportingState)
  {
    case THERMOSTAT_REPORTING_CONFIGURED:
      sendConfigureReportingToNotify(APP_SRC_ENDPOINT_ID, APP_ENDPOINT_COMBINED_INTERFACE, OCCUPANCY_SENSING_CLUSTER_ID,
        ZCL_OCCUPANCY_SENSING_CLUSTER_OCCUPANCY_SERVER_ATTRIBUTE_ID, OCCUPANCY_SENSING_VAL_MAX_REPORT_PERIOD, thConfigureReportingResp);
      configureReportingState = OCCUPANCY_REPORTING_CONFIGURED;
      break;

    case OCCUPANCY_REPORTING_CONFIGURED:
      sendConfigureReportingToNotify(APP_SRC_ENDPOINT_ID, APP_ENDPOINT_COMBINED_INTERFACE, HUMIDITY_MEASUREMENT_CLUSTER_ID,
        ZCL_HUMIDITY_MEASUREMENT_CLUSTER_SERVER_MEASURED_VALUE_ATTRIBUTE_ID, HUMIDITY_MEASUREMENT_VAL_MAX_REPORT_PERIOD, thConfigureReportingResp);
      configureReportingState = HUMIDITY_MEASURED_VALUE_REPORTING_CONFIGURED;
      break;

    case HUMIDITY_MEASURED_VALUE_REPORTING_CONFIGURED:    
      sendConfigureReportingToNotify(APP_SRC_ENDPOINT_ID, APP_ENDPOINT_COMBINED_INTERFACE, HUMIDITY_MEASUREMENT_CLUSTER_ID,
        ZCL_HUMIDITY_MEASUREMENT_CLUSTER_SERVER_TOLERANCE_ATTRIBUTE_ID, HUMIDITY_MEASUREMENT_VAL_MAX_REPORT_PERIOD, thConfigureReportingResp);
      configureReportingState = HUMIDITY_TOLERANCE_VALUE_REPORTING_CONFIGURED;    
      break;

    case HUMIDITY_TOLERANCE_VALUE_REPORTING_CONFIGURED:
      sendConfigureReportingToNotify(APP_SRC_ENDPOINT_ID, APP_ENDPOINT_COMBINED_INTERFACE, TEMPERATURE_MEASUREMENT_CLUSTER_ID,
        ZCL_TEMPERATURE_MEASUREMENT_CLUSTER_SERVER_MEASURED_VALUE_ATTRIBUTE_ID, TEMPERATURE_MEASUREMENT_VAL_MAX_REPORT_PERIOD, thConfigureReportingResp);
      configureReportingState =  TEMPERATURE_MEASURED_VALUE_REPORTING_CONFIGURED;
      break;

    case TEMPERATURE_MEASURED_VALUE_REPORTING_CONFIGURED:
      sendConfigureReportingToNotify(APP_SRC_ENDPOINT_ID, APP_ENDPOINT_COMBINED_INTERFACE, TEMPERATURE_MEASUREMENT_CLUSTER_ID,
        ZCL_TEMPERATURE_MEASUREMENT_CLUSTER_SERVER_TOLERANCE_ATTRIBUTE_ID, TEMPERATURE_MEASUREMENT_VAL_MAX_REPORT_PERIOD, thConfigureReportingResp);
      configureReportingState = CONFIGURATION_COMPLETED;
      break;

  case CONFIGURATION_COMPLETED:
  default:
    break;
  }
  (void)ntfy;
}
/**************************************************************************//**
\brief ZDO Binding indication function

\param[out] bindInd - ZDO bind indication parameters structure pointer. For details go to
            ZDO_BindInd_t declaration
******************************************************************************/
void ZDO_BindIndication(ZDO_BindInd_t *bindInd)
{
  (void)bindInd;
}

/**************************************************************************//**
\brief ZDO Unbinding indication function

\param[out] unbindInd - ZDO unbind indication parameters structure pointer. For details go to
            ZDO_UnbindInd_t declaration
******************************************************************************/
void ZDO_UnbindIndication(ZDO_UnbindInd_t *unbindInd)
{
  (void)unbindInd;
}

/**************************************************************************//**
\brief Periodic update of various attributes of different sensors
*****************************************************************************/
static void updateSensorsAttributeValues(void)
{
  humidityMeasurementUpdateMeasuredValue();
  humidityMeasurementUpdateTolerance();
}

#endif // APP_DEVICE_TYPE_THERMOSTAT
// eof thermostat.c
