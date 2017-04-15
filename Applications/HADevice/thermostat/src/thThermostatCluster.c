/**************************************************************************//**
  \file thThermostatCluster.c

  \brief
    Thermostat cluster implementation.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
       09/09/2014 Unithra.C - Created
******************************************************************************/
#ifdef APP_DEVICE_TYPE_THERMOSTAT

/******************************************************************************
                    Includes section
******************************************************************************/
#include <thThermostatCluster.h>
#if APP_ENABLE_CONSOLE == 1
#include <uartManager.h>
#endif
#include <tempSensor.h>
#include <thAlarmsCluster.h>
#include <haClusters.h>
#include <commandManager.h>
#include <bspTempSensor.h>
#include <zclAttributes.h>

/*******************************************************************************
                             Defines section
*******************************************************************************/
#define THERMOSTAT_SETPOINT_SCALE 10

#if THERMOSTAT_LOCAL_TEMPERATURE_MAX_REPORT_PERIOD > 2
#define TEMP_MEAS_TIME  ((THERMOSTAT_LOCAL_TEMPERATURE_MAX_REPORT_PERIOD/2) - 1)*1000
#else
#define TEMP_MEAS_TIME 1000
#endif

/*******************************************************************************
                             Types section
*******************************************************************************/
typedef struct PACK
{
  ZCL_AttributeId_t id;
  uint8_t type;
  uint8_t properties;
  int16_t value;
} setPoint_t;

#if  BOARD_QTOUCH_XPRO
enum setPointMode
  {
    ADJUST_HEAT_SETPOINT,
    ADJUST_COOL_SETPOINT,
    ADJUST_HEAT_AND_COOL_SETPOINT,
  };
#define LOCAL_TEMPERATURE_CONST 100  
#endif
/*******************************************************************************
                    Static functions prototypes section
*******************************************************************************/
static ZCL_Status_t setpointCommandInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_SetpointRaiseLower_t * payload);
static void readTemperature(void);
static void thThermostatAttrEventInd(ZCL_Addressing_t *addressing, ZCL_AttributeId_t attributeId, ZCL_AttributeEvent_t event);
static void thermostatSettingsAttrInit(void);
static void thermostatInformationAttrInit(void);
static void thThermostatEventListener(SYS_EventId_t eventId, SYS_EventData_t data);
#ifdef ZCL_THERMOSTAT_CLUSTER_INCLUDE_OPTIONAL_ATTRIBUTES
  static void thermostatUpdateThRunningMode(int16_t temperature);
#endif
#if defined(THERMOSTAT_EXTERNAL_TEMPERATURE_SENSOR_NODE_AVAILABLE) && defined (ZCL_THERMOSTAT_CLUSTER_INCLUDE_OPTIONAL_ATTRIBUTES)
  static void thermostatReadExternalTempSensor(int16_t *pTemperature);
#endif
static ZCL_Status_t thermostatValidateSystemModeValue(ZCL_ThControlSeqOfOperation_t ctrlSeqOperation,ZCL_ThSystemMode_t sysModeValue);
static void setAlarmState(ZclThermostatAlarmCode_t alarmCode, bool setAlarm);
static bool isAlarmActive(ZclThermostatAlarmCode_t alarmCode);

/******************************************************************************
                    Global variables
******************************************************************************/
ZCL_ThermostatClusterServerAttributes_t thThermostatClusterServerAttributes =
{
  ZCL_DEFINE_THERMOSTAT_CLUSTER_SERVER_MANDATORY_ATTRIBUTES(THERMOSTAT_LOCAL_TEMPERATURE_MIN_REPORT_PERIOD, THERMOSTAT_LOCAL_TEMPERATURE_MAX_REPORT_PERIOD)
#ifdef ZCL_THERMOSTAT_CLUSTER_INCLUDE_OPTIONAL_ATTRIBUTES    
  ZCL_DEFINE_THERMOSTAT_CLUSTER_SERVER_OPTIONAL_ATTRIBUTES(THERMOSTAT_LOCAL_TEMPERATURE_MIN_REPORT_PERIOD, THERMOSTAT_LOCAL_TEMPERATURE_MAX_REPORT_PERIOD)
#endif    
};

ZCL_ThermostatClusterCommands_t thThermostatClusterServerCommands =
{
  ZCL_DEFINE_THERMOSTAT_CLUSTER_COMMANDS(setpointCommandInd)
};

/******************************************************************************
                    Local variables
******************************************************************************/
static HAL_AppTimer_t tempMeasTimer;
static uint8_t activeAlarms;
/* BitCloud events receiver */
static SYS_EventReceiver_t thEventReceiver = { .func = thThermostatEventListener};

/******************************************************************************
                    Implementation section
******************************************************************************/

/**************************************************************************//**
\brief Initializes thermostat cluster atttributes to their defaults,
        register events and required timers
\param NA
******************************************************************************/
void thermostatClusterInit(void)
{
  ZCL_Cluster_t *cluster = ZCL_GetCluster(APP_SRC_ENDPOINT_ID, THERMOSTAT_CLUSTER_ID, ZCL_CLUSTER_SIDE_SERVER);

  if (cluster)
  {
    cluster->ZCL_AttributeEventInd = thThermostatAttrEventInd;
  }
  thermostatClusterInitAttributes();
  BSP_OpenTempSensor();

  /*Start periodic temperature measurement - this period shall always be less
  than reporting period*/
  tempMeasTimer.interval = TEMP_MEAS_TIME;
  tempMeasTimer.mode = TIMER_REPEAT_MODE;
  tempMeasTimer.callback = readTemperature;
  HAL_StopAppTimer(&tempMeasTimer);
  HAL_StartAppTimer(&tempMeasTimer);

  SYS_SubscribeToEvent(BC_ZCL_EVENT_ACTION_REQUEST, &thEventReceiver);
}
/**************************************************************************//**
\brief Initializes thermostat cluster atttributes to their defaults
\param NA
******************************************************************************/
 void thermostatClusterInitAttributes(void)
 {
  thermostatInformationAttrInit();
  thermostatSettingsAttrInit();
#ifdef ZCL_THERMOSTAT_CLUSTER_INCLUDE_OPTIONAL_ATTRIBUTES  
  thThermostatClusterServerAttributes.thermostatRunningState.value = CCPU_TO_LE16(ZCL_TH_RUNNING_STATE_DEF);
#endif
 }
/**************************************************************************//**
\brief Initializes the thermostat information attributes to their defaults
\param NA
******************************************************************************/
static void thermostatInformationAttrInit(void)
{
  thThermostatClusterServerAttributes.localTemperature.value =
      CCPU_TO_LE16(ZCL_THERMOSTAT_TEMPERATURE_SCALE * ZCL_TH_LOCAL_TEMPERATURE_DEF);
#ifdef ZCL_THERMOSTAT_CLUSTER_INCLUDE_OPTIONAL_ATTRIBUTES  
  thThermostatClusterServerAttributes.outdoorTemperature.value =
      CCPU_TO_LE16(ZCL_THERMOSTAT_TEMPERATURE_SCALE * ZCL_TH_LOCAL_TEMPERATURE_DEF);
  
  thThermostatClusterServerAttributes.occupancy.value.occupied = CCPU_TO_LE16(ZCL_NOT_OCCUPIED);
  thThermostatClusterServerAttributes.absMinHeatSetpointLimit.value = 
      CCPU_TO_LE16(ZCL_THERMOSTAT_TEMPERATURE_SCALE * ZCL_TH_ABS_MIN_HEAT_SP_LIMIT_DEF);
  thThermostatClusterServerAttributes.absMaxHeatSetpointLimit.value = 
      CCPU_TO_LE16(ZCL_THERMOSTAT_TEMPERATURE_SCALE * ZCL_TH_ABS_MAX_HEAT_SP_LIMIT_DEF);
  thThermostatClusterServerAttributes.absMinCoolSetpointLimit.value = 
      CCPU_TO_LE16(ZCL_THERMOSTAT_TEMPERATURE_SCALE * ZCL_TH_ABS_MIN_COOL_SP_LIMIT_DEF);
  thThermostatClusterServerAttributes.absMaxCoolSetpointLimit.value = 
      CCPU_TO_LE16(ZCL_THERMOSTAT_TEMPERATURE_SCALE * ZCL_TH_ABS_MAX_COOL_SP_LIMIT_DEF);
  
  /*hvacSystemTypeConfiguration*/
  thThermostatClusterServerAttributes.hvacSystemTypeConfiguration.value.coolingStage = 
      (uint8_t)CCPU_TO_LE16(ZCL_HVAC_COOL_STAGE_1);
  thThermostatClusterServerAttributes.hvacSystemTypeConfiguration.value.heatingStage = 
      (uint8_t)CCPU_TO_LE16(ZCL_HVAC_HEAT_STAGE_1);
  thThermostatClusterServerAttributes.hvacSystemTypeConfiguration.value.heatingType = 
      (uint8_t)CCPU_TO_LE16(ZCL_HVAC_TYPE_CONVENTIONAL);
  thThermostatClusterServerAttributes.hvacSystemTypeConfiguration.value.heatingFuelSource = 
      (uint8_t)CCPU_TO_LE16(ZCL_HVAC_SOURCE_ELECTRIC);
#endif
}

/**************************************************************************//**
\brief Initializes the thermostat settings attributes to their defaults

\param NA
******************************************************************************/
static void thermostatSettingsAttrInit(void)
{
#ifdef ZCL_THERMOSTAT_CLUSTER_INCLUDE_OPTIONAL_ATTRIBUTES  
  thThermostatClusterServerAttributes.localTemperatureCalibration.value = 
      CCPU_TO_LE16(ZCL_TH_LOCAL_TEMP_CALIB_DEF);
#endif
  thThermostatClusterServerAttributes.occupiedCoolingSetpoint.value =
      CCPU_TO_LE16(ZCL_THERMOSTAT_TEMPERATURE_SCALE * ZCL_TH_OCCUPIED_COOLING_SP_DEF);
  thThermostatClusterServerAttributes.occupiedHeatingSetpoint.value = 
      CCPU_TO_LE16(ZCL_THERMOSTAT_TEMPERATURE_SCALE * ZCL_TH_OCCUPIED_HEATING_SP_DEF);
#ifdef ZCL_THERMOSTAT_CLUSTER_INCLUDE_OPTIONAL_ATTRIBUTES
  thThermostatClusterServerAttributes.unOccupiedCoolingSetpoint.value =
      CCPU_TO_LE16(ZCL_THERMOSTAT_TEMPERATURE_SCALE * ZCL_TH_UNOCCUPIED_COOLING_SP_DEF);
  thThermostatClusterServerAttributes.unOccupiedHeatingSetpoint.value = 
      CCPU_TO_LE16(ZCL_THERMOSTAT_TEMPERATURE_SCALE * ZCL_TH_UNOCCUPIED_HEATING_SP_DEF);
  thThermostatClusterServerAttributes.minHeatSetpointLimit.value = 
      CCPU_TO_LE16(ZCL_THERMOSTAT_TEMPERATURE_SCALE * ZCL_TH_MIN_HEAT_SP_LIMIT_DEF);
  thThermostatClusterServerAttributes.maxHeatSetpointLimit.value = 
      CCPU_TO_LE16(ZCL_THERMOSTAT_TEMPERATURE_SCALE * ZCL_TH_MAX_HEAT_SP_LIMIT_DEF);
  thThermostatClusterServerAttributes.minCoolSetpointLimit.value = 
      CCPU_TO_LE16(ZCL_THERMOSTAT_TEMPERATURE_SCALE * ZCL_TH_MIN_COOL_SP_LIMIT_DEF);
  thThermostatClusterServerAttributes.maxCoolSetpointLimit.value = 
      CCPU_TO_LE16(ZCL_THERMOSTAT_TEMPERATURE_SCALE * ZCL_TH_MAX_COOL_SP_LIMIT_DEF);
  thThermostatClusterServerAttributes.minSetpointDeadBand.value = 
      (int8_t)CCPU_TO_LE16(ZCL_TH_MIN_SP_DEADBABD_DEF);
  
  /*remoteSensing*/
  thThermostatClusterServerAttributes.remoteSensing.value.localTemperature = 
      CCPU_TO_LE16(ZCL_SENSE_INTERNALLY);
  thThermostatClusterServerAttributes.remoteSensing.value.outdoorTemperature = 
      CCPU_TO_LE16(ZCL_SENSE_INTERNALLY);
  thThermostatClusterServerAttributes.remoteSensing.value.occupancySense = 
      CCPU_TO_LE16(ZCL_SENSE_INTERNALLY);
#endif  
  thThermostatClusterServerAttributes.controlSequenceofOperation.value = 
      CCPU_TO_LE16(ZCL_COOL_HEAT_4PIPES);
  thThermostatClusterServerAttributes.systemMode.value = CCPU_TO_LE16(ZCL_SYS_MODE_AUTO);
#ifdef ZCL_THERMOSTAT_CLUSTER_INCLUDE_OPTIONAL_ATTRIBUTES  
  thThermostatClusterServerAttributes.alarmMask.value.initFailure = 
      CCPU_TO_LE16(ZCL_TH_ALARM_DISABLED);
  thThermostatClusterServerAttributes.alarmMask.value.hardwareFailure = 
      CCPU_TO_LE16(ZCL_TH_ALARM_DISABLED);
  thThermostatClusterServerAttributes.alarmMask.value.selfCalibrationFailure = 
      CCPU_TO_LE16(ZCL_TH_ALARM_DISABLED);

  thThermostatClusterServerAttributes.thermostatRunningMode.value = 
      CCPU_TO_LE16(ZCL_RUNNING_MODE_OFF);
#endif
}

/**************************************************************************//**
\brief Temperature measurement on timer expiry
       The temp sensor returns a temperature value already scaled by 
       THERMOSTAT_LOCAL_TEMPERATURE_SCALE.So further scaling is not needed here.

\param NA
******************************************************************************/
static void readTemperature(void)
{
  int16_t measuredTemp = 0;
#ifdef ZCL_THERMOSTAT_CLUSTER_INCLUDE_OPTIONAL_ATTRIBUTES  
  if (ZCL_SENSE_INTERNALLY == thThermostatClusterServerAttributes.remoteSensing.value.localTemperature)
#endif    
    BSP_ReadTempSensor(&measuredTemp);
#if defined(THERMOSTAT_EXTERNAL_TEMPERATURE_SENSOR_NODE_AVAILABLE) && defined(ZCL_THERMOSTAT_CLUSTER_INCLUDE_OPTIONAL_ATTRIBUTES)
  else  thermostatReadExternalTempSensor(&measuredTemp);
#endif  
  thThermostatClusterServerAttributes.localTemperature.value = measuredTemp;
#ifdef ZCL_THERMOSTAT_CLUSTER_INCLUDE_OPTIONAL_ATTRIBUTES  
  thermostatUpdateThRunningMode(thThermostatClusterServerAttributes.localTemperature.value);
#endif
}

#ifdef ZCL_THERMOSTAT_CLUSTER_INCLUDE_OPTIONAL_ATTRIBUTES
/**************************************************************************//**
\brief Updates the thermostat running mode based on the given temperature

\param[in] - measured temperature
\param[out] - None
******************************************************************************/
static void thermostatUpdateThRunningMode(int16_t temperature)
{
  if (ZCL_OCCUPIED == thThermostatClusterServerAttributes.occupancy.value.occupied)
  {
    if(temperature <= thThermostatClusterServerAttributes.occupiedHeatingSetpoint.value)
      thThermostatClusterServerAttributes.thermostatRunningMode.value = ZCL_RUNNING_MODE_HEAT;
  
    else if(temperature >= thThermostatClusterServerAttributes.occupiedCoolingSetpoint.value)
      thThermostatClusterServerAttributes.thermostatRunningMode.value = ZCL_RUNNING_MODE_COOL;
  
    else
      thThermostatClusterServerAttributes.thermostatRunningMode.value = ZCL_RUNNING_MODE_OFF;
  }
  else if (ZCL_NOT_OCCUPIED == thThermostatClusterServerAttributes.occupancy.value.occupied)
  {
    if(temperature <= thThermostatClusterServerAttributes.unOccupiedHeatingSetpoint.value)
      thThermostatClusterServerAttributes.thermostatRunningMode.value = ZCL_RUNNING_MODE_HEAT;
  
    else if(temperature >= thThermostatClusterServerAttributes.unOccupiedCoolingSetpoint.value)
      thThermostatClusterServerAttributes.thermostatRunningMode.value = ZCL_RUNNING_MODE_COOL;
  
    else
      thThermostatClusterServerAttributes.thermostatRunningMode.value = ZCL_RUNNING_MODE_OFF;
  }  
}
#endif

#if defined(THERMOSTAT_EXTERNAL_TEMPERATURE_SENSOR_NODE_AVAILABLE) && defined (ZCL_THERMOSTAT_CLUSTER_INCLUDE_OPTIONAL_ATTRIBUTES)
/**************************************************************************//**
\brief Read temperature from the remote sensor node on the network

\param[in] - pointer to return the measured temperature
\param[out] - None
******************************************************************************/
static void thermostatReadExternalTempSensor(int16_t *pTemperature)
{
  *pTemperature = ((int16_t)rand()) % (ZCL_TH_ABS_MAX_COOL_SP_LIMIT_DEF - ZCL_TH_ABS_MIN_HEAT_SP_LIMIT_DEF) 
                    + ZCL_TH_ABS_MIN_HEAT_SP_LIMIT_DEF;
  *pTemperature *= ZCL_THERMOSTAT_TEMPERATURE_SCALE;
}
#endif

/****************************************************************//**
 \brief thermostat cluster setpointRaiseLowerCommand indication
 \param addressing - source info
 \param reportLength  - length of data in reportPayload
 \param payload - payload data
 \return none
********************************************************************/
static ZCL_Status_t setpointCommandInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, 
                                       ZCL_SetpointRaiseLower_t * payload)
{
  int16_t requestedValue = 0;
  switch(payload->mode)
  {
      case ZCL_ADJUST_HEAT_SETPOINT:
#ifdef ZCL_THERMOSTAT_CLUSTER_INCLUDE_OPTIONAL_ATTRIBUTES
        if(ZCL_OCCUPIED == thThermostatClusterServerAttributes.occupancy.value.occupied)
#endif          
        {
          requestedValue = thThermostatClusterServerAttributes.occupiedHeatingSetpoint.value +
                                               (payload->amount)*THERMOSTAT_SETPOINT_SCALE;
          ZCL_WriteAttributeValue(APP_ENDPOINT_THERMOSTAT,THERMOSTAT_CLUSTER_ID,
                                     ZCL_SERVER_CLUSTER_TYPE,ZCL_THERMOSTAT_CLUSTER_OCCUPIED_HEATING_SETPOINT_SERVER_ATTRIBUTE_ID,
                                     ZCL_S16BIT_DATA_TYPE_ID,(uint8_t *)&requestedValue);
        }
#ifdef ZCL_THERMOSTAT_CLUSTER_INCLUDE_OPTIONAL_ATTRIBUTES
        else
        {
          requestedValue = thThermostatClusterServerAttributes.unOccupiedHeatingSetpoint.value +
                                               (payload->amount)*THERMOSTAT_SETPOINT_SCALE;
          ZCL_WriteAttributeValue(APP_ENDPOINT_THERMOSTAT,THERMOSTAT_CLUSTER_ID,
                                     ZCL_SERVER_CLUSTER_TYPE,ZCL_THERMOSTAT_CLUSTER_UNOCCUPIED_HEATING_SETPOINT_SERVER_ATTRIBUTE_ID,
                                     ZCL_S16BIT_DATA_TYPE_ID,(uint8_t *)&requestedValue);
        }
#endif
        break;
      case ZCL_ADJUST_COOL_SETPOINT:
#ifdef ZCL_THERMOSTAT_CLUSTER_INCLUDE_OPTIONAL_ATTRIBUTES        
        if(ZCL_OCCUPIED == thThermostatClusterServerAttributes.occupancy.value.occupied)
#endif
        {
          requestedValue = thThermostatClusterServerAttributes.occupiedCoolingSetpoint.value +
                                               (payload->amount)*THERMOSTAT_SETPOINT_SCALE;
          ZCL_WriteAttributeValue(APP_ENDPOINT_THERMOSTAT,THERMOSTAT_CLUSTER_ID,
                                     ZCL_SERVER_CLUSTER_TYPE,ZCL_THERMOSTAT_CLUSTER_OCCUPIED_COOLING_SETPOINT_SERVER_ATTRIBUTE_ID,
                                     ZCL_S16BIT_DATA_TYPE_ID,(uint8_t *)&requestedValue);
        }
#ifdef ZCL_THERMOSTAT_CLUSTER_INCLUDE_OPTIONAL_ATTRIBUTES
        else
        {
          requestedValue = thThermostatClusterServerAttributes.unOccupiedCoolingSetpoint.value +
                                               (payload->amount)*THERMOSTAT_SETPOINT_SCALE;
          ZCL_WriteAttributeValue(APP_ENDPOINT_THERMOSTAT,THERMOSTAT_CLUSTER_ID,
                                     ZCL_SERVER_CLUSTER_TYPE,ZCL_THERMOSTAT_CLUSTER_UNOCCUPIED_COOLING_SETPOINT_SERVER_ATTRIBUTE_ID,
                                     ZCL_S16BIT_DATA_TYPE_ID,(uint8_t *)&requestedValue);
        }
#endif
        break;
      case ZCL_ADJUST_HEAT_AND_COOL_SETPOINT:
#ifdef ZCL_THERMOSTAT_CLUSTER_INCLUDE_OPTIONAL_ATTRIBUTES
        if(ZCL_OCCUPIED == thThermostatClusterServerAttributes.occupancy.value.occupied)
#endif
        {
          requestedValue = thThermostatClusterServerAttributes.occupiedHeatingSetpoint.value +
                                               (payload->amount)*THERMOSTAT_SETPOINT_SCALE;
          ZCL_WriteAttributeValue(APP_ENDPOINT_THERMOSTAT,THERMOSTAT_CLUSTER_ID,
                                     ZCL_SERVER_CLUSTER_TYPE,ZCL_THERMOSTAT_CLUSTER_OCCUPIED_HEATING_SETPOINT_SERVER_ATTRIBUTE_ID,
                                     ZCL_S16BIT_DATA_TYPE_ID,(uint8_t *)&requestedValue);
          requestedValue = thThermostatClusterServerAttributes.occupiedCoolingSetpoint.value +
                                               (payload->amount)*THERMOSTAT_SETPOINT_SCALE;
          ZCL_WriteAttributeValue(APP_ENDPOINT_THERMOSTAT,THERMOSTAT_CLUSTER_ID,
                                     ZCL_SERVER_CLUSTER_TYPE,ZCL_THERMOSTAT_CLUSTER_OCCUPIED_COOLING_SETPOINT_SERVER_ATTRIBUTE_ID,
                                     ZCL_S16BIT_DATA_TYPE_ID,(uint8_t *)&requestedValue);
        }
#ifdef ZCL_THERMOSTAT_CLUSTER_INCLUDE_OPTIONAL_ATTRIBUTES
        else
        {
          requestedValue = thThermostatClusterServerAttributes.unOccupiedHeatingSetpoint.value +
                                               (payload->amount)*THERMOSTAT_SETPOINT_SCALE;
          ZCL_WriteAttributeValue(APP_ENDPOINT_THERMOSTAT,THERMOSTAT_CLUSTER_ID,
                                     ZCL_SERVER_CLUSTER_TYPE,ZCL_THERMOSTAT_CLUSTER_UNOCCUPIED_HEATING_SETPOINT_SERVER_ATTRIBUTE_ID,
                                     ZCL_S16BIT_DATA_TYPE_ID,(uint8_t *)&requestedValue);
          requestedValue = thThermostatClusterServerAttributes.unOccupiedCoolingSetpoint.value +
                                               (payload->amount)*THERMOSTAT_SETPOINT_SCALE;
          ZCL_WriteAttributeValue(APP_ENDPOINT_THERMOSTAT,THERMOSTAT_CLUSTER_ID,
                                     ZCL_SERVER_CLUSTER_TYPE,ZCL_THERMOSTAT_CLUSTER_UNOCCUPIED_COOLING_SETPOINT_SERVER_ATTRIBUTE_ID,
                                     ZCL_S16BIT_DATA_TYPE_ID,(uint8_t *)&requestedValue);
        }
#endif
        break;
      default:
        return ZCL_INVALID_ATTRIBUTE_VALUE_STATUS;
        break;
  }

#if APP_ENABLE_CONSOLE == 1
  LOG_STRING(setPointStr, "->SetPoints updated by CI: \r\n");
  appSnprintf(setPointStr);
  LOG_STRING(modeStr, "#setpoint mode: %d\r\n");
  appSnprintf(modeStr,payload->mode);
  LOG_STRING(amtStr, "->setpoint amount updated by: %d.%d C\r\n");
  appSnprintf(amtStr, (int)((payload->amount)/THERMOSTAT_SETPOINT_SCALE),(int)((payload->amount)%THERMOSTAT_SETPOINT_SCALE));
#endif
  // warnings prevention
  (void)addressing;
  (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Attribute Event indication handler(to indicate when attr values have
        read or written)

\param[in] addressing - pointer to addressing information;
\param[in] reportLength - data payload length;
\param[in] reportPayload - data pointer
******************************************************************************/
static void thThermostatAttrEventInd(ZCL_Addressing_t *addressing, ZCL_AttributeId_t attributeId, ZCL_AttributeEvent_t event)
{
  if(attributeId == ZCL_THERMOSTAT_CLUSTER_LOCAL_TEMPERATURE_SERVER_ATTRIBUTE_ID && event == ZCL_CONFIGURE_ATTRIBUTE_REPORTING_EVENT)
  {
#if APP_ENABLE_CONSOLE == 1
    LOG_STRING(AttrEventIndStr, "->temperature report configuration updated by CI:\r\n");
    appSnprintf(AttrEventIndStr);
    LOG_STRING(minStr, "->min Report Interval: %d secs\r\n");
    appSnprintf(minStr, thThermostatClusterServerAttributes.localTemperature.minReportInterval);
    LOG_STRING(maxStr, "->max Report Interval: %d secs\r\n");
    appSnprintf(maxStr, thThermostatClusterServerAttributes.localTemperature.maxReportInterval);
#endif
  }
  else if ( (attributeId == ZCL_THERMOSTAT_CLUSTER_CONTROL_SEQUENCE_OF_OPERATION_SERVER_ATTRIBUTE_ID) 
           && (event == ZCL_WRITE_ATTRIBUTE_EVENT) )
  {
    if(!thermostatValidateSystemModeValue(thThermostatClusterServerAttributes.controlSequenceofOperation.value,
                                         thThermostatClusterServerAttributes.systemMode.value))
      thThermostatClusterServerAttributes.systemMode.value = ZCL_SYS_MODE_AUTO;
  }
  else
  {
#if APP_ENABLE_CONSOLE == 1
    LOG_STRING(AttrEventIndStr, "<-Attr ID 0x%x event 0x%x\r\n");
    appSnprintf(AttrEventIndStr, attributeId, event);
#endif
  }
  (void)addressing;
}
/**************************************************************************//**
\brief Validates the possible system mode value for the given control sequence 
       of operation

\param[in] - Control sequence of operation value
\param[in] - System mode value to be verified
\param[out] - None
******************************************************************************/
static ZCL_Status_t thermostatValidateSystemModeValue(ZCL_ThControlSeqOfOperation_t ctrlSeqOperation,ZCL_ThSystemMode_t sysModeValue)
{
  if(ZCL_SYS_MODE_RESERVED == sysModeValue)
  {
    return ZCL_FAILURE_STATUS;
  }
  switch(ctrlSeqOperation)
  {
    case ZCL_COOL_ONLY:
    case ZCL_COOL_WITH_REHEAT:
      if((ZCL_SYS_MODE_HEAT == sysModeValue) || (ZCL_SYS_MODE_EMERGENCY_HEATING == sysModeValue))
        return ZCL_FAILURE_STATUS;
      break;
    case ZCL_HEAT_ONLY:
    case ZCL_HEAT_WITH_REHEAT:
      if((ZCL_SYS_MODE_COOL == sysModeValue) || (ZCL_SYS_MODE_PRECOOLING == sysModeValue))
        return ZCL_FAILURE_STATUS;
      break;
    case ZCL_COOL_HEAT_4PIPES:      
    case ZCL_COOL_HEAT_4PIPES_REHEAT:
      return ZCL_SUCCESS_STATUS;
      break;
    default:
      return ZCL_SUCCESS_STATUS;
      break;
  }
  return ZCL_SUCCESS_STATUS;
}
/**************************************************************************//**
  \brief  ZCL action request event handler, 
          handles the ZCL_ACTION_WRITE_ATTR_REQUEST for attribute specific validation

  \param[in] ev - must be BC_ZCL_EVENT_ACTION_REQUEST.
  \param[in] data - this field must contain pointer to the BcZCLActionReq_t structure,

  \return None.
 ******************************************************************************/
static void thThermostatEventListener(SYS_EventId_t eventId, SYS_EventData_t data)
{
  BcZCLActionReq_t *const actionReq = (BcZCLActionReq_t*)data;
  int16_t requestedValue = 0;
  if (BC_ZCL_EVENT_ACTION_REQUEST == eventId)
  {
    if (ZCL_ACTION_WRITE_ATTR_REQUEST == actionReq->action)
    {
      ZCLActionWriteAttrReq_t *const zclWriteAttrReq = (ZCLActionWriteAttrReq_t*)actionReq->context;
      if( (THERMOSTAT_CLUSTER_ID == zclWriteAttrReq->clusterId) && 
              (ZCL_CLUSTER_SIDE_SERVER == zclWriteAttrReq->clusterSide))
      {
        memcpy((uint8_t *)&requestedValue,zclWriteAttrReq->attrValue, sizeof(int16_t));
        actionReq->denied = 0U;
        switch(zclWriteAttrReq->attrId)
        {
          case ZCL_THERMOSTAT_CLUSTER_OCCUPIED_COOLING_SETPOINT_SERVER_ATTRIBUTE_ID:
            if(requestedValue <= (thThermostatClusterServerAttributes.occupiedHeatingSetpoint.value 
#ifdef ZCL_THERMOSTAT_CLUSTER_INCLUDE_OPTIONAL_ATTRIBUTES
                                  + thThermostatClusterServerAttributes.minSetpointDeadBand.value
#endif
                                    ))
              actionReq->denied = 1U;
            break;
          case ZCL_THERMOSTAT_CLUSTER_OCCUPIED_HEATING_SETPOINT_SERVER_ATTRIBUTE_ID:
            if(requestedValue >= (thThermostatClusterServerAttributes.occupiedCoolingSetpoint.value 
#ifdef ZCL_THERMOSTAT_CLUSTER_INCLUDE_OPTIONAL_ATTRIBUTES
                                  - thThermostatClusterServerAttributes.minSetpointDeadBand.value
#endif
                                    ))
              actionReq->denied = 1U;
            break;
#ifdef ZCL_THERMOSTAT_CLUSTER_INCLUDE_OPTIONAL_ATTRIBUTES
          case ZCL_THERMOSTAT_CLUSTER_UNOCCUPIED_COOLING_SETPOINT_SERVER_ATTRIBUTE_ID:
            if(requestedValue <= (thThermostatClusterServerAttributes.unOccupiedHeatingSetpoint.value + 
                                    thThermostatClusterServerAttributes.minSetpointDeadBand.value))
              actionReq->denied = 1U;
            break;
          case ZCL_THERMOSTAT_CLUSTER_UNOCCUPIED_HEATING_SETPOINT_SERVER_ATTRIBUTE_ID: 
            if(requestedValue >= (thThermostatClusterServerAttributes.unOccupiedCoolingSetpoint.value -
                                    thThermostatClusterServerAttributes.minSetpointDeadBand.value))
              actionReq->denied = 1U;
            break;
          case ZCL_THERMOSTAT_CLUSTER_MIN_HEAT_SETPOINT_LIMIT_SERVER_ATTRIBUTE_ID:
            if(requestedValue < thThermostatClusterServerAttributes.absMinHeatSetpointLimit.value)
              actionReq->denied = 1U;
            break;
          case ZCL_THERMOSTAT_CLUSTER_MAX_HEAT_SETPOINT_LIMIT_SERVER_ATTRIBUTE_ID:
            if(requestedValue > thThermostatClusterServerAttributes.absMaxHeatSetpointLimit.value)
              actionReq->denied = 1U;
            break;
          case ZCL_THERMOSTAT_CLUSTER_MIN_COOL_SETPOINT_LIMIT_SERVER_ATTRIBUTE_ID:
            if(requestedValue < thThermostatClusterServerAttributes.absMinCoolSetpointLimit.value)
              actionReq->denied = 1U;
            break;
          case ZCL_THERMOSTAT_CLUSTER_MAX_COOL_SETPOINT_LIMIT_SERVER_ATTRIBUTE_ID:
            if(requestedValue > thThermostatClusterServerAttributes.absMaxCoolSetpointLimit.value)
              actionReq->denied = 1U;
            break;
#endif            
          case ZCL_THERMOSTAT_CLUSTER_SYSTEM_MODE_SERVER_ATTRIBUTE_ID:
            if(ZCL_SUCCESS_STATUS != thermostatValidateSystemModeValue(thThermostatClusterServerAttributes.controlSequenceofOperation.value, 
                                                                       (ZCL_ThSystemMode_t)*(zclWriteAttrReq->attrValue)))
              actionReq->denied = 1U;
            break;
          default:
            break;
        }
      }
    }
    else if (ZCL_ACTION_RESET_ALARM_REQUEST == actionReq->action)
    {
      ZCL_ResetAlarmNotification_t  *resetAlarmNotification = (ZCL_ResetAlarmNotification_t *)(actionReq->context);

      if ((ZCL_ALARMS_CLUSTER_SERVER_RESET_ALARM_COMMAND_ID == resetAlarmNotification->commandId) && \
  	      (THERMOSTAT_CLUSTER_ID == resetAlarmNotification->clusterIdentifier))
      {
        //reset the alarmCode
#if APP_ENABLE_CONSOLE == 1
        LOG_STRING(resetAlarmEventStr, "->thermostatResetAlarm:%d \r\n");
        appSnprintf(resetAlarmEventStr, resetAlarmNotification->alarmCode);
#endif
        if (isAlarmActive(resetAlarmNotification->alarmCode))
        {
          setAlarmState(resetAlarmNotification->alarmCode, false);
          alarmNotification(resetAlarmNotification->alarmCode, THERMOSTAT_CLUSTER_ID);
        }
      }
      else if (ZCL_ALARMS_CLUSTER_SERVER_RESET_ALL_ALARMS_COMMAND_ID == resetAlarmNotification->commandId)
      {
#if APP_ENABLE_CONSOLE == 1
        LOG_STRING(resetAllAlarmEventStr, "->thermostatResetAllAlarm\r\n");
        appSnprintf(resetAllAlarmEventStr);
#endif
        for (uint8_t i = 0; i < NO_OF_ALARM_CODES; i++)
        {
          if (isAlarmActive(i))
          {
            setAlarmState(i, false);
            alarmNotification(i, THERMOSTAT_CLUSTER_ID);
          }
        }
      }
    }
  }
}

#ifdef BOARD_QTOUCH_XPRO
/**************************************************************************//**
\brief Report Attr confirmation

\param[in] ntfy - pointer to status
******************************************************************************/
static void ZCL_ReportAttributeResp(ZCL_Notify_t *ntfy)
{
  if (ZCL_SUCCESS_STATUS == ntfy->status)
  {
    LOG_STRING(reportAttrSuccessStr, "->Report setpoint update to CI success\r\n");
    appSnprintf(reportAttrSuccessStr);
  }
  else
  {
    LOG_STRING(reportAttrSuccessStr, "->Report setpoint update to CI failed: status = 0x%2x\r\n");
    appSnprintf(reportAttrSuccessStr, (unsigned)ntfy->status);
  }
}
/**************************************************************************//**
\brief Local change of setpoints through Touch button
******************************************************************************/
void thermostatSetPointsChangeButton(int8_t mode,uint8_t amount)
{
  /* notify combined interface that setpoints have been locally changed */
  ZCL_Request_t *req;
  setPoint_t reportAttrReq[2];
  int16_t data[2];
  int16_t setPointValue;

  if (!(req = getFreeCommand()))
    return;
  
  switch(mode)
  {
      case ADJUST_HEAT_SETPOINT:
        setPointValue = MIN_HEAT_SETPOINT_LIMIT + (((MAX_HEAT_SETPOINT_LIMIT - MIN_HEAT_SETPOINT_LIMIT) * amount)/255);
        thThermostatClusterServerAttributes.occupiedHeatingSetpoint.value = setPointValue;
        break;
        
      case ADJUST_COOL_SETPOINT:
        setPointValue = MIN_COOL_SETPOINT_LIMIT + (((MAX_COOL_SETPOINT_LIMIT - MIN_COOL_SETPOINT_LIMIT) * amount)/255);
        thThermostatClusterServerAttributes.occupiedCoolingSetpoint.value = setPointValue;
        break;
            
      default:
        break;
  }
  LOG_STRING(setPointsStr, "Local update of setpoints done\r\n");
  appSnprintf(setPointsStr);
  LOG_STRING(minStr, "#current cool setpoint: %d.%d C\r\n");
  appSnprintf(minStr, (int)(thThermostatClusterServerAttributes.occupiedCoolingSetpoint.value/LOCAL_TEMPERATURE_CONST), \
    (int)(thThermostatClusterServerAttributes.occupiedCoolingSetpoint.value%LOCAL_TEMPERATURE_CONST));
  LOG_STRING(maxStr, "#current heat setpoint: %d.%d C\r\n");
  appSnprintf(maxStr, (int)(thThermostatClusterServerAttributes.occupiedHeatingSetpoint.value/LOCAL_TEMPERATURE_CONST), \
    (int)(thThermostatClusterServerAttributes.occupiedHeatingSetpoint.value%LOCAL_TEMPERATURE_CONST));   
  
  data[0] = thThermostatClusterServerAttributes.occupiedCoolingSetpoint.value;
  data[1] = thThermostatClusterServerAttributes.occupiedHeatingSetpoint.value;
  
  reportAttrReq[0].id = ZCL_THERMOSTAT_CLUSTER_OCCUPIED_COOLING_SETPOINT_SERVER_ATTRIBUTE_ID;
  reportAttrReq[0].type = ZCL_S16BIT_DATA_TYPE_ID;
  reportAttrReq[0].properties= ZCL_READWRITE_ATTRIBUTE;
  memcpy(&reportAttrReq[0].value, &data[0],sizeof(int16_t));
  
  reportAttrReq[1].id = ZCL_THERMOSTAT_CLUSTER_OCCUPIED_HEATING_SETPOINT_SERVER_ATTRIBUTE_ID;
  reportAttrReq[1].type = ZCL_S16BIT_DATA_TYPE_ID;
  reportAttrReq[1].properties= ZCL_READWRITE_ATTRIBUTE;
  memcpy(&reportAttrReq[1].value, &data[1],sizeof(int16_t));
  
  memcpy(req->requestPayload, (uint8_t *)&reportAttrReq, sizeof(reportAttrReq));

  fillCommandRequest(req, ZCL_REPORT_ATTRIBUTES_COMMAND_ID, sizeof(reportAttrReq));

  req->dstAddressing.addrMode             = APS_NO_ADDRESS;
  req->dstAddressing.addr.shortAddress    = 0;
  req->dstAddressing.profileId            = PROFILE_ID_HOME_AUTOMATION;
  req->dstAddressing.endpointId           = APP_ENDPOINT_COMBINED_INTERFACE;
  req->dstAddressing.clusterId            = THERMOSTAT_CLUSTER_ID;
  req->dstAddressing.clusterSide          = ZCL_CLUSTER_SIDE_CLIENT;
  req->dstAddressing.manufacturerSpecCode = 0;
  req->dstAddressing.sequenceNumber       = ZCL_GetNextSeqNumber();
  req->ZCL_Notify = ZCL_ReportAttributeResp;

  commandManagerSendAttribute(req);
}
#endif

#ifdef ZCL_THERMOSTAT_CLUSTER_INCLUDE_OPTIONAL_ATTRIBUTES
/**************************************************************************//**
  \brief  Sets the occupancy attribute value         

  \param[in] value - Occupied or Not occupied
  \return Success(if valid value) / Failure (if not valid value)
 ******************************************************************************/
ZCL_Status_t thermostatSetOccupancy(ZCL_ThOccupancy_t value)
{
  if ((ZCL_OCCUPIED == value) || (ZCL_NOT_OCCUPIED == value))
  {
    thThermostatClusterServerAttributes.occupancy.value.occupied = value;
    return ZCL_SUCCESS_STATUS;
  }
  else 
    return ZCL_FAILURE_STATUS;
}
#endif
/**************************************************************************//**
\brief Trigger alarm condition
******************************************************************************/
void thermostatSetAlarmCondition(ZclThermostatAlarmCode_t alarmCode, bool alarmSet)
{
  uint8_t attrVal   = *(uint8_t *)&thThermostatClusterServerAttributes.alarmMask.value;
  if (attrVal & (1 << alarmCode))
  {
    setAlarmState(alarmCode,alarmSet);

    if (true == alarmSet)
      alarmNotification(alarmCode, THERMOSTAT_CLUSTER_ID);
  }
}
/**************************************************************************//**
\brief Set alarm mask
******************************************************************************/
void thermostatSetAlarmMask(uint8_t alarmMask)
{
  uint8_t *ptr = (uint8_t *)&thThermostatClusterServerAttributes.alarmMask.value;
  *ptr = alarmMask;
  for (uint8_t i = 0; i < NO_OF_ALARM_CODES; i++)
  {
    if (!(alarmMask & ((uint8_t)1 << i)))
      activeAlarms &= ~((uint8_t)1 << i);
  }
}
/**************************************************************************//**
  \brief set/reset alarm

  \param[in] alarmCode - alarmCode to be set/reset
  \param[in] setAlarm  - true - set the alarm
                         false - reset the alarm.
******************************************************************************/
static void setAlarmState(ZclThermostatAlarmCode_t alarmCode, bool setAlarm)
{
  if (setAlarm)
    activeAlarms |= (1 << alarmCode);
  else
    activeAlarms &= ~((uint8_t)1 << alarmCode);
}

/**************************************************************************//**
  \brief To check whether alarm is active or not

  \param[in] alarmCode - alarmCode to be set/reset
  \return    retStatus  - true if it is active
                          false if it is not active.
******************************************************************************/
static bool isAlarmActive(ZclThermostatAlarmCode_t alarmCode)
{
  bool retStatus = false;
  if (activeAlarms & ((uint8_t)1 << alarmCode))
    retStatus = true;
  return retStatus;
}

#endif // APP_DEVICE_TYPE_THERMOSTAT

// eof thThermostatCluster.c
