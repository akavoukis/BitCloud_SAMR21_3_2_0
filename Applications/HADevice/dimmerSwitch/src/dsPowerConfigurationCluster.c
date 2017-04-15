/**************************************************************************//**
  \file dsPowerConfigurationCluster.c

  \brief
    Dimmer Switch Power Configuration cluster implementation.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    17.11.14 Prashanth - Created.
******************************************************************************/
#ifdef APP_DEVICE_TYPE_DIMMER_SWITCH

/******************************************************************************
                    Includes section
******************************************************************************/

#include <zclDevice.h>
#include <haClusters.h>
#include <commandManager.h>
#include <uartManager.h>
#include <zclDevice.h>
#include <bspVoltageSensor.h>
#include <ezModeManager.h>
#include <dsAlarmsCluster.h>
#include <dsPowerConfigurationCluster.h>
#include <zclAttributes.h>

/******************************************************************************
                    Definition(s) section
******************************************************************************/
#if (APP_ENABLE_CERTIFICATION_EXTENSION == 0)
// The Time is Configurable according to customer needs
#define BATTERY_ONE_VOLTAGE_MEAS_TIME                10000
#define BATTERY_TWO_VOLTAGE_MEAS_TIME                20000
#define BATTERY_THREE_VOLTAGE_MEAS_TIME              30000
#define BATTERY_ONE_PERCENTAGE_REMAINING_MEAS_TIME   10000
#define BATTERY_TWO_PERCENTAGE_REMAINING_MEAS_TIME   20000
#define BATTERY_THREE_PERCENTAGE_REMAINING_MEAS_TIME 30000
#endif

/******************************************************************************
                    Prototypes section
******************************************************************************/
static void powerConfigurationInformationAttrInit(void);
static void powerConfigurationSettingsAttrInit(void);
#if (APP_ENABLE_CERTIFICATION_EXTENSION == 0)
static void readBatteryOneVoltage(void);
static void readBatteryTwoVoltage(void);
static void readBatteryThreeVoltage(void);
static void readBatteryOnePercentageRemaining(void);
static void readBatteryTwoPercentageRemaining(void);
static void readBatteryThreePercentageRemaining(void);
static uint16_t smallestOfTwo(uint16_t one, uint16_t two);
#endif
static void dsPwrConfigEventListener(SYS_EventId_t eventId, SYS_EventData_t data);
static void dsPwrResetAllAlarms(void);
static void dsPwrResetAlarm(uint8_t alarmCode);

/******************************************************************************
                    Global variables section
******************************************************************************/
ZCL_PowerConfigurationClusterServerAttributes_t dsPowerConfigurationClusterServerAttributes =
{
  ZCL_DEFINE_POWER_CONFIGURATION_CLUSTER_SERVER_ATTRIBUTES(POWER_CONFIGURATION_MIN_REPORT_PERIOD, POWER_CONFIGURATION_MAX_REPORT_PERIOD)
};

/******************************************************************************
                    Static variables section
******************************************************************************/
#if (APP_ENABLE_CERTIFICATION_EXTENSION == 0)
static HAL_AppTimer_t batteryOneVoltageMeasTimer;
static HAL_AppTimer_t batteryTwoVoltageMeasTimer;
static HAL_AppTimer_t batteryThreeVoltageMeasTimer;
static HAL_AppTimer_t batteryOnePercentageRemainingMeasTimer;
static HAL_AppTimer_t batteryTwoPercentageRemainingMeasTimer;
static HAL_AppTimer_t batteryThreePercentageRemainingMeasTimer;
#endif
static void dsPowerConfigurationAttrEventInd(ZCL_Addressing_t *addressing, ZCL_AttributeId_t attributeId, ZCL_AttributeEvent_t event);
static SYS_EventReceiver_t dsPwrConfigEventReceiver = { .func = dsPwrConfigEventListener};

/******************************************************************************
                    Implementation section
******************************************************************************/
/**************************************************************************//**
\brief Initializes Identify cluster
******************************************************************************/
void powerConfigurationClusterInit(void)
{
  ZCL_Cluster_t *cluster = ZCL_GetCluster(APP_SRC_ENDPOINT_ID, POWER_CONFIGURATION_CLUSTER_ID, ZCL_CLUSTER_SIDE_SERVER);

  if (cluster)
  {
    cluster->ZCL_AttributeEventInd = dsPowerConfigurationAttrEventInd;
  }
  powerConfigurationClusterInitAttributes();

#if (APP_ENABLE_CERTIFICATION_EXTENSION == 0)
  /*Start periodic voltage measurement for Battery One*/
  batteryOneVoltageMeasTimer.interval = BATTERY_ONE_VOLTAGE_MEAS_TIME;
  batteryOneVoltageMeasTimer.mode = TIMER_REPEAT_MODE;
  batteryOneVoltageMeasTimer.callback = readBatteryOneVoltage;
  HAL_StopAppTimer(&batteryOneVoltageMeasTimer);
  HAL_StartAppTimer(&batteryOneVoltageMeasTimer);
  
  /*Start periodic voltage measurement for Battery One*/
  batteryTwoVoltageMeasTimer.interval = BATTERY_TWO_VOLTAGE_MEAS_TIME;
  batteryTwoVoltageMeasTimer.mode = TIMER_REPEAT_MODE;
  batteryTwoVoltageMeasTimer.callback = readBatteryTwoVoltage;
  HAL_StopAppTimer(&batteryTwoVoltageMeasTimer);
  HAL_StartAppTimer(&batteryTwoVoltageMeasTimer);
  
  /*Start periodic voltage measurement for Battery One*/
  batteryThreeVoltageMeasTimer.interval = BATTERY_THREE_VOLTAGE_MEAS_TIME;
  batteryThreeVoltageMeasTimer.mode = TIMER_REPEAT_MODE;
  batteryThreeVoltageMeasTimer.callback = readBatteryThreeVoltage;
  HAL_StopAppTimer(&batteryThreeVoltageMeasTimer);
  HAL_StartAppTimer(&batteryThreeVoltageMeasTimer);
  
    /*Start periodic voltage measurement for Battery One*/
  batteryOnePercentageRemainingMeasTimer.interval = BATTERY_ONE_PERCENTAGE_REMAINING_MEAS_TIME;
  batteryOnePercentageRemainingMeasTimer.mode = TIMER_REPEAT_MODE;
  batteryOnePercentageRemainingMeasTimer.callback = readBatteryOnePercentageRemaining;
  HAL_StopAppTimer(&batteryOnePercentageRemainingMeasTimer);
  HAL_StartAppTimer(&batteryOnePercentageRemainingMeasTimer);
  
  /*Start periodic voltage measurement for Battery One*/
  batteryTwoPercentageRemainingMeasTimer.interval = BATTERY_TWO_PERCENTAGE_REMAINING_MEAS_TIME;
  batteryTwoPercentageRemainingMeasTimer.mode = TIMER_REPEAT_MODE;
  batteryTwoPercentageRemainingMeasTimer.callback = readBatteryTwoPercentageRemaining;
  HAL_StopAppTimer(&batteryTwoPercentageRemainingMeasTimer);
  HAL_StartAppTimer(&batteryTwoPercentageRemainingMeasTimer);
  
  /*Start periodic voltage measurement for Battery One*/
  batteryThreePercentageRemainingMeasTimer.interval = BATTERY_THREE_PERCENTAGE_REMAINING_MEAS_TIME;
  batteryThreePercentageRemainingMeasTimer.mode = TIMER_REPEAT_MODE;
  batteryThreePercentageRemainingMeasTimer.callback = readBatteryThreePercentageRemaining;
  HAL_StopAppTimer(&batteryThreePercentageRemainingMeasTimer);
  HAL_StartAppTimer(&batteryThreePercentageRemainingMeasTimer);
#endif
  
  SYS_SubscribeToEvent(BC_ZCL_EVENT_ACTION_REQUEST, &dsPwrConfigEventReceiver);
}

/**************************************************************************//**
\brief Attribute Event indication handler(to indicate when attr values have
        read or written)

\param[in] addressing - pointer to addressing information;
\param[in] reportLength - data payload length;
\param[in] reportPayload - data pointer
******************************************************************************/
static void dsPowerConfigurationAttrEventInd(ZCL_Addressing_t *addressing, ZCL_AttributeId_t attributeId, ZCL_AttributeEvent_t event)
{
  (void)addressing;
  (void)attributeId;
  (void)event;
}

/**************************************************************************//**
  \brief  ZCL action request event handler, 
          handles the ZCL_ACTION_WRITE_ATTR_REQUEST for attribute specific validation

  \param[in] ev - must be BC_ZCL_EVENT_ACTION_REQUEST.
  \param[in] data - this field must contain pointer to the BcZCLActionReq_t structure,

  \return None.
 ******************************************************************************/
static void dsPwrConfigEventListener(SYS_EventId_t eventId, SYS_EventData_t data)
{
  BcZCLActionReq_t *const actionReq = (BcZCLActionReq_t*)data;
  actionReq->denied = 0U;
  int16_t requestedValue = 0;
  if (BC_ZCL_EVENT_ACTION_REQUEST == eventId)
  {    
    if (ZCL_ACTION_WRITE_ATTR_REQUEST == actionReq->action)
    {
      ZCLActionWriteAttrReq_t *const zclWriteAttrReq = (ZCLActionWriteAttrReq_t*)actionReq->context;
      if( (POWER_CONFIGURATION_CLUSTER_ID == zclWriteAttrReq->clusterId) && 
              (ZCL_CLUSTER_SIDE_SERVER == zclWriteAttrReq->clusterSide))
      {
        memcpy((uint8_t *)&requestedValue,zclWriteAttrReq->attrValue, sizeof(int16_t));
        switch(zclWriteAttrReq->attrId)
        {
          case ZCL_POWER_CONFIGURATION_CLUSTER_SERVER_BATTERY_SOURCE_1_SIZE_ID:
            if((requestedValue <= ZCL_BATTERY_RES2) && (requestedValue >= ZCL_BATTERY_RES1))
              actionReq->denied = 1U;
            break;
          case ZCL_POWER_CONFIGURATION_CLUSTER_SERVER_BATTERY_SOURCE_2_SIZE_ID:
            if((requestedValue <= ZCL_BATTERY_RES2) && (requestedValue >= ZCL_BATTERY_RES1))
              actionReq->denied = 1U;
            break;
          case ZCL_POWER_CONFIGURATION_CLUSTER_SERVER_BATTERY_SOURCE_3_SIZE_ID:
            if((requestedValue <= ZCL_BATTERY_RES2) && (requestedValue >= ZCL_BATTERY_RES1))
              actionReq->denied = 1U;
            break;
          case ZCL_POWER_CONFIGURATION_CLUSTER_SERVER_BATTERY_SOURCE_1_ALARM_STATE_ID:
            if((requestedValue & ZCL_DS_BATTERY_ALARM_STATE_RESERVED_MASK_1) && (requestedValue & ZCL_DS_BATTERY_ALARM_STATE_RESERVED_MASK_2))
              actionReq->denied = 1U;
            break;
          case ZCL_POWER_CONFIGURATION_CLUSTER_SERVER_BATTERY_SOURCE_2_ALARM_STATE_ID:
            if((requestedValue & ZCL_DS_BATTERY_ALARM_STATE_RESERVED_MASK_1) && (requestedValue & ZCL_DS_BATTERY_ALARM_STATE_RESERVED_MASK_2))
              actionReq->denied = 1U;
            break;
          case ZCL_POWER_CONFIGURATION_CLUSTER_SERVER_BATTERY_SOURCE_3_ALARM_STATE_ID:
            if((requestedValue & ZCL_DS_BATTERY_ALARM_STATE_RESERVED_MASK_1) && (requestedValue & ZCL_DS_BATTERY_ALARM_STATE_RESERVED_MASK_2))
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
          (POWER_CONFIGURATION_CLUSTER_ID == resetAlarmNotification->clusterIdentifier))
      {
        //reset the alarmCode
        LOG_STRING(resetAlarmEventStr, "->powerConfigurationResetAlarm:%d \r\n");
        appSnprintf(resetAlarmEventStr, resetAlarmNotification->alarmCode);
        dsPwrResetAlarm(resetAlarmNotification->alarmCode);
      }
      else if (ZCL_ALARMS_CLUSTER_SERVER_RESET_ALL_ALARMS_COMMAND_ID == resetAlarmNotification->commandId)
      {
        LOG_STRING(resetAllAlarmEventStr, "->PowerConfigurationResetAllAlarm\r\n");
        appSnprintf(resetAllAlarmEventStr);
        dsPwrResetAllAlarms();
      }
    }
  }
}

#if (APP_ENABLE_CERTIFICATION_EXTENSION == 0)
/**************************************************************************//**
\brief Battery One Percentage Remaining measurement timer expiry
       The Percentage remaining returns the remaining battery charge in 
       percentage value.

\param NA
******************************************************************************/
static void readBatteryOnePercentageRemaining(void)
{
  uint8_t percentageRemaining;
  uint8_t minThreshold = dsPowerConfigurationClusterServerAttributes.batterySourceOnePercentageMinThreshold.value;
  uint8_t thresholdOne = dsPowerConfigurationClusterServerAttributes.batterySourceOnePercentageThreshold_1.value;
  uint8_t thresholdTwo = dsPowerConfigurationClusterServerAttributes.batterySourceOnePercentageThreshold_2.value;
  uint8_t thresholdThree = dsPowerConfigurationClusterServerAttributes.batterySourceOnePercentageThreshold_3.value;
  // Clearing Alarm States for setting new states from Readings 
  dsPowerConfigurationClusterServerAttributes.batterySourceOneAlarmState.value = 0;
#if APP_BSP_READ_BATTERY_VALUE
  BSP_ReadBatPercentageRemaining(&percentageRemaining);
  // multiply by 2
  percentageRemaining = (percentageRemaining << 1);
  dsPowerConfigurationClusterServerAttributes.batterySourceOnePercentageRemaining.value = percentageRemaining;
#else
  percentageRemaining = dsPowerConfigurationClusterServerAttributes.batterySourceOnePercentageRemaining.value;
#endif

  if(dsPowerConfigurationClusterServerAttributes.batterySourceOneAlarmMask.value.batteryTooLow == 1)
  {
    if(smallestOfTwo(percentageRemaining,minThreshold) == percentageRemaining)
    {
      dsPowerConfigurationClusterServerAttributes.batterySourceOneAlarmState.value |= BATTERY_ONE_MIN_THRESHOLD_MASK;
      alarmNotification(ZCL_BATTERY_MIN_THRESHOLD_SOURCE_1_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
      dsPowerConfigurationClusterServerAttributes.batterySourceOneAlarmState.value |= BATTERY_TWO_MIN_THRESHOLD_MASK;
      alarmNotification(ZCL_BATTERY_MIN_THRESHOLD_SOURCE_2_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
      dsPowerConfigurationClusterServerAttributes.batterySourceOneAlarmState.value |= BATTERY_THREE_MIN_THRESHOLD_MASK;
      alarmNotification(ZCL_BATTERY_MIN_THRESHOLD_SOURCE_3_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
    }
  }
  else if(dsPowerConfigurationClusterServerAttributes.batterySourceOneAlarmMask.value.batteryAlarm1 == 1)
  {
    if((smallestOfTwo(percentageRemaining,thresholdOne) == percentageRemaining) && (percentageRemaining > minThreshold))
    {
      dsPowerConfigurationClusterServerAttributes.batterySourceOneAlarmState.value |= BATTERY_ONE_THRESHOLD_1_MASK;
      alarmNotification(ZCL_BATTERY_THRESHOLD_1_SOURCE_1_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
      dsPowerConfigurationClusterServerAttributes.batterySourceOneAlarmState.value |= BATTERY_TWO_THRESHOLD_1_MASK;
      alarmNotification(ZCL_BATTERY_THRESHOLD_1_SOURCE_2_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
      dsPowerConfigurationClusterServerAttributes.batterySourceOneAlarmState.value |= BATTERY_THREE_THRESHOLD_1_MASK;
      alarmNotification(ZCL_BATTERY_THRESHOLD_1_SOURCE_3_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
    }
  }
  else if(dsPowerConfigurationClusterServerAttributes.batterySourceOneAlarmMask.value.batteryAlarm2 == 1)
  {
    if((smallestOfTwo(percentageRemaining,thresholdTwo) == percentageRemaining) && (percentageRemaining > thresholdOne))
    {
      dsPowerConfigurationClusterServerAttributes.batterySourceOneAlarmState.value |= BATTERY_ONE_THRESHOLD_2_MASK;
      alarmNotification(ZCL_BATTERY_THRESHOLD_2_SOURCE_1_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
      dsPowerConfigurationClusterServerAttributes.batterySourceOneAlarmState.value |= BATTERY_TWO_THRESHOLD_2_MASK;
      alarmNotification(ZCL_BATTERY_THRESHOLD_2_SOURCE_2_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
      dsPowerConfigurationClusterServerAttributes.batterySourceOneAlarmState.value |= BATTERY_THREE_THRESHOLD_2_MASK;
      alarmNotification(ZCL_BATTERY_THRESHOLD_2_SOURCE_3_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
    }
  }
  else if(dsPowerConfigurationClusterServerAttributes.batterySourceOneAlarmMask.value.batteryAlarm3 == 1)
  {
    if((smallestOfTwo(percentageRemaining,thresholdThree) == percentageRemaining) && (percentageRemaining > thresholdTwo))
    {
      dsPowerConfigurationClusterServerAttributes.batterySourceOneAlarmState.value |= BATTERY_ONE_THRESHOLD_3_MASK;
      alarmNotification(ZCL_BATTERY_THRESHOLD_3_SOURCE_1_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
      dsPowerConfigurationClusterServerAttributes.batterySourceOneAlarmState.value |= BATTERY_TWO_THRESHOLD_3_MASK;
      alarmNotification(ZCL_BATTERY_THRESHOLD_3_SOURCE_2_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
      dsPowerConfigurationClusterServerAttributes.batterySourceOneAlarmState.value |= BATTERY_THREE_THRESHOLD_3_MASK;
      alarmNotification(ZCL_BATTERY_THRESHOLD_3_SOURCE_3_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
    }
  }
}

/**************************************************************************//**
\brief Battery Two Percentage Remaining measurement timer expiry
       The Percentage remaining returns the remaining battery charge in 
       percentage value.

\param NA
******************************************************************************/
static void readBatteryTwoPercentageRemaining(void)
{
  uint8_t percentageRemaining;
  uint8_t minThreshold = dsPowerConfigurationClusterServerAttributes.batterySourceTwoPercentageMinThreshold.value;
  uint8_t thresholdOne = dsPowerConfigurationClusterServerAttributes.batterySourceTwoPercentageThreshold_1.value;
  uint8_t thresholdTwo = dsPowerConfigurationClusterServerAttributes.batterySourceTwoPercentageThreshold_2.value;
  uint8_t thresholdThree = dsPowerConfigurationClusterServerAttributes.batterySourceTwoPercentageThreshold_3.value;
  // Clearing Alarm States for setting new states from Readings 
  dsPowerConfigurationClusterServerAttributes.batterySourceTwoAlarmState.value = 0;
#if APP_BSP_READ_BATTERY_VALUE
  BSP_ReadBatPercentageRemaining(&percentageRemaining);
  // multiply by 2
  percentageRemaining = (percentageRemaining << 1);
  dsPowerConfigurationClusterServerAttributes.batterySourceTwoPercentageRemaining.value = percentageRemaining;
#else
  percentageRemaining = dsPowerConfigurationClusterServerAttributes.batterySourceTwoPercentageRemaining.value;
#endif

  if(dsPowerConfigurationClusterServerAttributes.batterySourceTwoAlarmMask.value.batteryTooLow == 1)
  {
    if(smallestOfTwo(percentageRemaining,minThreshold) == percentageRemaining)
    {
      dsPowerConfigurationClusterServerAttributes.batterySourceTwoAlarmState.value |= BATTERY_ONE_MIN_THRESHOLD_MASK;
      alarmNotification(ZCL_BATTERY_MIN_THRESHOLD_SOURCE_1_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
      dsPowerConfigurationClusterServerAttributes.batterySourceTwoAlarmState.value |= BATTERY_TWO_MIN_THRESHOLD_MASK;
      alarmNotification(ZCL_BATTERY_MIN_THRESHOLD_SOURCE_2_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
      dsPowerConfigurationClusterServerAttributes.batterySourceTwoAlarmState.value |= BATTERY_THREE_MIN_THRESHOLD_MASK;
      alarmNotification(ZCL_BATTERY_MIN_THRESHOLD_SOURCE_3_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
    }
  }
  else if(dsPowerConfigurationClusterServerAttributes.batterySourceTwoAlarmMask.value.batteryAlarm1 == 1)
  {
   if((smallestOfTwo(percentageRemaining,thresholdOne) == percentageRemaining) && (percentageRemaining > minThreshold))
    {
      dsPowerConfigurationClusterServerAttributes.batterySourceTwoAlarmState.value |= BATTERY_ONE_THRESHOLD_1_MASK;
      alarmNotification(ZCL_BATTERY_THRESHOLD_1_SOURCE_1_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
      dsPowerConfigurationClusterServerAttributes.batterySourceTwoAlarmState.value |= BATTERY_TWO_THRESHOLD_1_MASK;
      alarmNotification(ZCL_BATTERY_THRESHOLD_1_SOURCE_2_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
      dsPowerConfigurationClusterServerAttributes.batterySourceTwoAlarmState.value |= BATTERY_THREE_THRESHOLD_1_MASK;
      alarmNotification(ZCL_BATTERY_THRESHOLD_1_SOURCE_3_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
    }
  }
  else if(dsPowerConfigurationClusterServerAttributes.batterySourceTwoAlarmMask.value.batteryAlarm2 == 1)
  {
    if((smallestOfTwo(percentageRemaining,thresholdTwo) == percentageRemaining) && (percentageRemaining > thresholdOne))
    {
      dsPowerConfigurationClusterServerAttributes.batterySourceTwoAlarmState.value |= BATTERY_ONE_THRESHOLD_2_MASK;
      alarmNotification(ZCL_BATTERY_THRESHOLD_2_SOURCE_1_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
      dsPowerConfigurationClusterServerAttributes.batterySourceTwoAlarmState.value |= BATTERY_TWO_THRESHOLD_2_MASK;
      alarmNotification(ZCL_BATTERY_THRESHOLD_2_SOURCE_2_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
      dsPowerConfigurationClusterServerAttributes.batterySourceTwoAlarmState.value |= BATTERY_THREE_THRESHOLD_2_MASK;
      alarmNotification(ZCL_BATTERY_THRESHOLD_2_SOURCE_3_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
    }
  }
  else if(dsPowerConfigurationClusterServerAttributes.batterySourceTwoAlarmMask.value.batteryAlarm3 == 1)
  {
    if((smallestOfTwo(percentageRemaining,thresholdThree) == percentageRemaining) && (percentageRemaining > thresholdTwo))
    {
      dsPowerConfigurationClusterServerAttributes.batterySourceTwoAlarmState.value |= BATTERY_ONE_THRESHOLD_3_MASK;
      alarmNotification(ZCL_BATTERY_THRESHOLD_3_SOURCE_1_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
      dsPowerConfigurationClusterServerAttributes.batterySourceTwoAlarmState.value |= BATTERY_TWO_THRESHOLD_3_MASK;
      alarmNotification(ZCL_BATTERY_THRESHOLD_3_SOURCE_2_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
      dsPowerConfigurationClusterServerAttributes.batterySourceTwoAlarmState.value |= BATTERY_THREE_THRESHOLD_3_MASK;
      alarmNotification(ZCL_BATTERY_THRESHOLD_3_SOURCE_3_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
    }
  }
}

/**************************************************************************//**
\brief Battery Three Percentage Remaining measurement timer expiry
       The Percentage remaining returns the remaining battery charge in 
       percentage value.

\param NA
******************************************************************************/
static void readBatteryThreePercentageRemaining(void)
{
  uint8_t percentageRemaining;
  uint8_t minThreshold = dsPowerConfigurationClusterServerAttributes.batterySourceThreePercentageMinThreshold.value;
  uint8_t thresholdOne = dsPowerConfigurationClusterServerAttributes.batterySourceThreePercentageThreshold_1.value;
  uint8_t thresholdTwo = dsPowerConfigurationClusterServerAttributes.batterySourceThreePercentageThreshold_2.value;
  uint8_t thresholdThree = dsPowerConfigurationClusterServerAttributes.batterySourceThreePercentageThreshold_3.value;
  // Clearing Alarm States for setting new states from Readings 
  dsPowerConfigurationClusterServerAttributes.batterySourceThreeAlarmState.value = 0;
#if APP_BSP_READ_BATTERY_VALUE
  BSP_ReadBatPercentageRemaining(&percentageRemaining);
  // multiply by 2
  percentageRemaining = (percentageRemaining << 1);
  dsPowerConfigurationClusterServerAttributes.batterySourceThreePercentageRemaining.value = percentageRemaining;
#else
  percentageRemaining = dsPowerConfigurationClusterServerAttributes.batterySourceThreePercentageRemaining.value;
#endif
  
  if(dsPowerConfigurationClusterServerAttributes.batterySourceThreeAlarmMask.value.batteryTooLow == 1)
  {
    if(smallestOfTwo(percentageRemaining,minThreshold) == percentageRemaining)
    {
      dsPowerConfigurationClusterServerAttributes.batterySourceThreeAlarmState.value |= BATTERY_ONE_MIN_THRESHOLD_MASK;
      alarmNotification(ZCL_BATTERY_MIN_THRESHOLD_SOURCE_1_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
      dsPowerConfigurationClusterServerAttributes.batterySourceThreeAlarmState.value |= BATTERY_TWO_MIN_THRESHOLD_MASK;
      alarmNotification(ZCL_BATTERY_MIN_THRESHOLD_SOURCE_2_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
      dsPowerConfigurationClusterServerAttributes.batterySourceThreeAlarmState.value |= BATTERY_THREE_MIN_THRESHOLD_MASK;
      alarmNotification(ZCL_BATTERY_MIN_THRESHOLD_SOURCE_3_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
    }
  }
  else if(dsPowerConfigurationClusterServerAttributes.batterySourceThreeAlarmMask.value.batteryAlarm1 == 1)
  {
    if((smallestOfTwo(percentageRemaining,thresholdOne) == percentageRemaining) && (percentageRemaining > minThreshold))
    {
      dsPowerConfigurationClusterServerAttributes.batterySourceThreeAlarmState.value |= BATTERY_ONE_THRESHOLD_1_MASK;
      alarmNotification(ZCL_BATTERY_THRESHOLD_1_SOURCE_1_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
      dsPowerConfigurationClusterServerAttributes.batterySourceThreeAlarmState.value |= BATTERY_TWO_THRESHOLD_1_MASK;
      alarmNotification(ZCL_BATTERY_THRESHOLD_1_SOURCE_2_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
      dsPowerConfigurationClusterServerAttributes.batterySourceThreeAlarmState.value |= BATTERY_THREE_THRESHOLD_1_MASK;
      alarmNotification(ZCL_BATTERY_THRESHOLD_1_SOURCE_3_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
    }
  }
  else if(dsPowerConfigurationClusterServerAttributes.batterySourceThreeAlarmMask.value.batteryAlarm2 == 1)
  {
    if((smallestOfTwo(percentageRemaining,thresholdTwo) == percentageRemaining) && (percentageRemaining > thresholdOne))
    {
      dsPowerConfigurationClusterServerAttributes.batterySourceThreeAlarmState.value |= BATTERY_ONE_THRESHOLD_2_MASK;
      alarmNotification(ZCL_BATTERY_THRESHOLD_2_SOURCE_1_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
      dsPowerConfigurationClusterServerAttributes.batterySourceThreeAlarmState.value |= BATTERY_TWO_THRESHOLD_2_MASK;
      alarmNotification(ZCL_BATTERY_THRESHOLD_2_SOURCE_2_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
      dsPowerConfigurationClusterServerAttributes.batterySourceThreeAlarmState.value |= BATTERY_THREE_THRESHOLD_2_MASK;
      alarmNotification(ZCL_BATTERY_THRESHOLD_2_SOURCE_3_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
    }
  }
  else if(dsPowerConfigurationClusterServerAttributes.batterySourceThreeAlarmMask.value.batteryAlarm3 == 1)
  {
    if((smallestOfTwo(percentageRemaining,thresholdThree) == percentageRemaining) && (percentageRemaining > thresholdTwo))
    {
      dsPowerConfigurationClusterServerAttributes.batterySourceThreeAlarmState.value |= BATTERY_ONE_THRESHOLD_3_MASK;
      alarmNotification(ZCL_BATTERY_THRESHOLD_3_SOURCE_1_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
      dsPowerConfigurationClusterServerAttributes.batterySourceThreeAlarmState.value |= BATTERY_TWO_THRESHOLD_3_MASK;
      alarmNotification(ZCL_BATTERY_THRESHOLD_3_SOURCE_2_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
      dsPowerConfigurationClusterServerAttributes.batterySourceThreeAlarmState.value |= BATTERY_THREE_THRESHOLD_3_MASK;
      alarmNotification(ZCL_BATTERY_THRESHOLD_3_SOURCE_3_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
    }
  }
}

/**************************************************************************//**
\brief Battery One voltage measurement on timer expiry
       The Voltage sensor returns a Voltage value already scaled in milliVolts
       range which will be divided by ZCL_DS_BATTERY_VOLTAGE_CONVERSION_UNIT
       to convert to hundreds of voltage in range.

\param NA
******************************************************************************/
static void readBatteryOneVoltage(void)
{
  // In millivolts
  uint16_t measuredVoltage;
  uint8_t minThreshold = dsPowerConfigurationClusterServerAttributes.batterySourceOneVoltageMinThreshold.value;
  uint8_t thresholdOne = dsPowerConfigurationClusterServerAttributes.batterySourceOneVoltageThreshold_1.value;
  uint8_t thresholdTwo = dsPowerConfigurationClusterServerAttributes.batterySourceOneVoltageThreshold_2.value;
  uint8_t thresholdThree = dsPowerConfigurationClusterServerAttributes.batterySourceOneVoltageThreshold_3.value;
  // Clearing Alarm States for setting new states from Readings 
  dsPowerConfigurationClusterServerAttributes.batterySourceOneAlarmState.value = 0;
#if APP_BSP_READ_BATTERY_VALUE
  BSP_ReadVoltageSensor(&measuredVoltage);
  dsPowerConfigurationClusterServerAttributes.batterySourceOneVoltage.value = (measuredVoltage/ZCL_DS_BATTERY_VOLTAGE_CONVERSION_UNIT);
#else
  measuredVoltage = dsPowerConfigurationClusterServerAttributes.batterySourceOneVoltage.value;
#endif

  if(dsPowerConfigurationClusterServerAttributes.batterySourceOneAlarmMask.value.batteryTooLow == 1)
  {
    if(smallestOfTwo(measuredVoltage,minThreshold) == measuredVoltage)
    {
      dsPowerConfigurationClusterServerAttributes.batterySourceOneAlarmState.value |= BATTERY_ONE_MIN_THRESHOLD_MASK;
      alarmNotification(ZCL_BATTERY_MIN_THRESHOLD_SOURCE_1_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
      dsPowerConfigurationClusterServerAttributes.batterySourceOneAlarmState.value |= BATTERY_TWO_MIN_THRESHOLD_MASK;
      alarmNotification(ZCL_BATTERY_MIN_THRESHOLD_SOURCE_2_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
      dsPowerConfigurationClusterServerAttributes.batterySourceOneAlarmState.value |= BATTERY_THREE_MIN_THRESHOLD_MASK;
      alarmNotification(ZCL_BATTERY_MIN_THRESHOLD_SOURCE_3_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
    }
  }
  else if(dsPowerConfigurationClusterServerAttributes.batterySourceOneAlarmMask.value.batteryAlarm1 == 1)
  {
    if((smallestOfTwo(measuredVoltage,thresholdOne) == measuredVoltage) && (measuredVoltage > minThreshold))
    {
      dsPowerConfigurationClusterServerAttributes.batterySourceOneAlarmState.value |= BATTERY_ONE_THRESHOLD_1_MASK;
      alarmNotification(ZCL_BATTERY_THRESHOLD_1_SOURCE_1_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
      dsPowerConfigurationClusterServerAttributes.batterySourceOneAlarmState.value |= BATTERY_TWO_THRESHOLD_1_MASK;
      alarmNotification(ZCL_BATTERY_THRESHOLD_1_SOURCE_2_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
      dsPowerConfigurationClusterServerAttributes.batterySourceOneAlarmState.value |= BATTERY_THREE_THRESHOLD_1_MASK;
      alarmNotification(ZCL_BATTERY_THRESHOLD_1_SOURCE_3_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
    }
  }
  else if(dsPowerConfigurationClusterServerAttributes.batterySourceOneAlarmMask.value.batteryAlarm2 == 1)
  {
    if((smallestOfTwo(measuredVoltage,thresholdTwo) == measuredVoltage) && (measuredVoltage > thresholdOne))
    {
      dsPowerConfigurationClusterServerAttributes.batterySourceOneAlarmState.value |= BATTERY_ONE_THRESHOLD_2_MASK;
      alarmNotification(ZCL_BATTERY_THRESHOLD_2_SOURCE_1_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
      dsPowerConfigurationClusterServerAttributes.batterySourceOneAlarmState.value |= BATTERY_TWO_THRESHOLD_2_MASK;
      alarmNotification(ZCL_BATTERY_THRESHOLD_2_SOURCE_2_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
      dsPowerConfigurationClusterServerAttributes.batterySourceOneAlarmState.value |= BATTERY_THREE_THRESHOLD_2_MASK;
      alarmNotification(ZCL_BATTERY_THRESHOLD_2_SOURCE_3_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
    }
  }
  else if(dsPowerConfigurationClusterServerAttributes.batterySourceOneAlarmMask.value.batteryAlarm3 == 1)
  {
    if((smallestOfTwo(measuredVoltage,thresholdThree) == measuredVoltage) && (measuredVoltage > thresholdTwo))
    {
      dsPowerConfigurationClusterServerAttributes.batterySourceOneAlarmState.value |= BATTERY_ONE_THRESHOLD_3_MASK;
      alarmNotification(ZCL_BATTERY_THRESHOLD_3_SOURCE_1_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
      dsPowerConfigurationClusterServerAttributes.batterySourceOneAlarmState.value |= BATTERY_TWO_THRESHOLD_3_MASK;
      alarmNotification(ZCL_BATTERY_THRESHOLD_3_SOURCE_2_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
      dsPowerConfigurationClusterServerAttributes.batterySourceOneAlarmState.value |= BATTERY_THREE_THRESHOLD_3_MASK;
      alarmNotification(ZCL_BATTERY_THRESHOLD_3_SOURCE_3_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
    }
  }
}

/**************************************************************************//**
\brief Battery Two voltage measurement on timer expiry
       The Voltage sensor returns a Voltage value already scaled in milliVolts
       range which will be divided by ZCL_DS_BATTERY_VOLTAGE_CONVERSION_UNIT
       to convert to hundreds of voltage in range.

\param NA
******************************************************************************/
static void readBatteryTwoVoltage(void)
{
  // In millivolts
  uint16_t measuredVoltage;
  uint8_t minThreshold = dsPowerConfigurationClusterServerAttributes.batterySourceTwoVoltageMinThreshold.value;
  uint8_t thresholdOne = dsPowerConfigurationClusterServerAttributes.batterySourceTwoVoltageThreshold_1.value;
  uint8_t thresholdTwo = dsPowerConfigurationClusterServerAttributes.batterySourceTwoVoltageThreshold_2.value;
  uint8_t thresholdThree = dsPowerConfigurationClusterServerAttributes.batterySourceTwoVoltageThreshold_3.value;
  // Clearing Alarm States for setting new states from Readings 
  dsPowerConfigurationClusterServerAttributes.batterySourceTwoAlarmState.value = 0;
#if APP_BSP_READ_BATTERY_VALUE
  BSP_ReadVoltageSensor(&measuredVoltage);
  dsPowerConfigurationClusterServerAttributes.batterySourceTwoVoltage.value = (measuredVoltage/ZCL_DS_BATTERY_VOLTAGE_CONVERSION_UNIT);
#else
  measuredVoltage = dsPowerConfigurationClusterServerAttributes.batterySourceTwoVoltage.value;
#endif
        
  if(dsPowerConfigurationClusterServerAttributes.batterySourceTwoAlarmMask.value.batteryTooLow == 1)
  {
    if(smallestOfTwo(measuredVoltage,minThreshold) == measuredVoltage)
    {
      dsPowerConfigurationClusterServerAttributes.batterySourceTwoAlarmState.value |= BATTERY_ONE_MIN_THRESHOLD_MASK;
      alarmNotification(ZCL_BATTERY_MIN_THRESHOLD_SOURCE_1_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
      dsPowerConfigurationClusterServerAttributes.batterySourceTwoAlarmState.value |= BATTERY_TWO_MIN_THRESHOLD_MASK;
      alarmNotification(ZCL_BATTERY_MIN_THRESHOLD_SOURCE_2_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
      dsPowerConfigurationClusterServerAttributes.batterySourceTwoAlarmState.value |= BATTERY_THREE_MIN_THRESHOLD_MASK;
      alarmNotification(ZCL_BATTERY_MIN_THRESHOLD_SOURCE_3_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
    }
  }
  else if(dsPowerConfigurationClusterServerAttributes.batterySourceTwoAlarmMask.value.batteryAlarm1 == 1)
  {
    if((smallestOfTwo(measuredVoltage,thresholdOne) == measuredVoltage) && (measuredVoltage > minThreshold))
    {
      dsPowerConfigurationClusterServerAttributes.batterySourceTwoAlarmState.value |= BATTERY_ONE_THRESHOLD_1_MASK;
      alarmNotification(ZCL_BATTERY_THRESHOLD_1_SOURCE_1_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
      dsPowerConfigurationClusterServerAttributes.batterySourceTwoAlarmState.value |= BATTERY_TWO_THRESHOLD_1_MASK;
      alarmNotification(ZCL_BATTERY_THRESHOLD_1_SOURCE_2_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
      dsPowerConfigurationClusterServerAttributes.batterySourceTwoAlarmState.value |= BATTERY_THREE_THRESHOLD_1_MASK;
      alarmNotification(ZCL_BATTERY_THRESHOLD_1_SOURCE_3_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
    }
  }
  else if(dsPowerConfigurationClusterServerAttributes.batterySourceTwoAlarmMask.value.batteryAlarm2 == 1)
  {
    if((smallestOfTwo(measuredVoltage,thresholdTwo) == measuredVoltage) && (measuredVoltage > thresholdOne))
    {
      dsPowerConfigurationClusterServerAttributes.batterySourceTwoAlarmState.value |= BATTERY_ONE_THRESHOLD_2_MASK;
      alarmNotification(ZCL_BATTERY_THRESHOLD_2_SOURCE_1_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
      dsPowerConfigurationClusterServerAttributes.batterySourceTwoAlarmState.value |= BATTERY_TWO_THRESHOLD_2_MASK;
      alarmNotification(ZCL_BATTERY_THRESHOLD_2_SOURCE_2_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
      dsPowerConfigurationClusterServerAttributes.batterySourceTwoAlarmState.value |= BATTERY_THREE_THRESHOLD_2_MASK;
      alarmNotification(ZCL_BATTERY_THRESHOLD_2_SOURCE_3_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
    }
  }
  else if(dsPowerConfigurationClusterServerAttributes.batterySourceTwoAlarmMask.value.batteryAlarm3 == 1)
  {
    if((smallestOfTwo(measuredVoltage,thresholdThree) == measuredVoltage) && (measuredVoltage > thresholdTwo))
    {
      dsPowerConfigurationClusterServerAttributes.batterySourceTwoAlarmState.value |= BATTERY_ONE_THRESHOLD_3_MASK;
      alarmNotification(ZCL_BATTERY_THRESHOLD_3_SOURCE_1_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
      dsPowerConfigurationClusterServerAttributes.batterySourceTwoAlarmState.value |= BATTERY_TWO_THRESHOLD_3_MASK;
      alarmNotification(ZCL_BATTERY_THRESHOLD_3_SOURCE_2_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
      dsPowerConfigurationClusterServerAttributes.batterySourceTwoAlarmState.value |= BATTERY_THREE_THRESHOLD_3_MASK;
      alarmNotification(ZCL_BATTERY_THRESHOLD_3_SOURCE_3_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
    }
  }
}

/**************************************************************************//**
\brief Battery Three voltage measurement on timer expiry
       The Voltage sensor returns a Voltage value already scaled in milliVolts
       range which will be divided by ZCL_DS_BATTERY_VOLTAGE_CONVERSION_UNIT
       to convert to hundreds of voltage in range.

\param NA
******************************************************************************/
static void readBatteryThreeVoltage(void)
{
  // In millivolts
  uint16_t measuredVoltage;
  uint8_t minThreshold = dsPowerConfigurationClusterServerAttributes.batterySourceThreeVoltageMinThreshold.value;
  uint8_t thresholdOne = dsPowerConfigurationClusterServerAttributes.batterySourceThreeVoltageThreshold_1.value;
  uint8_t thresholdTwo = dsPowerConfigurationClusterServerAttributes.batterySourceThreeVoltageThreshold_2.value;
  uint8_t thresholdThree = dsPowerConfigurationClusterServerAttributes.batterySourceThreeVoltageThreshold_3.value;
  // Clearing Alarm States for setting new states from Readings 
  dsPowerConfigurationClusterServerAttributes.batterySourceThreeAlarmState.value = 0;
#if APP_BSP_READ_BATTERY_VALUE
  BSP_ReadVoltageSensor(&measuredVoltage);
  dsPowerConfigurationClusterServerAttributes.batterySourceThreeVoltage.value = (measuredVoltage/ZCL_DS_BATTERY_VOLTAGE_CONVERSION_UNIT);
#else
  measuredVoltage = dsPowerConfigurationClusterServerAttributes.batterySourceThreeVoltage.value;
#endif
        
  if(dsPowerConfigurationClusterServerAttributes.batterySourceThreeAlarmMask.value.batteryTooLow == 1)
  {
    if(smallestOfTwo(measuredVoltage,minThreshold) == measuredVoltage)
    {
      dsPowerConfigurationClusterServerAttributes.batterySourceThreeAlarmState.value |= BATTERY_ONE_MIN_THRESHOLD_MASK;
      alarmNotification(ZCL_BATTERY_MIN_THRESHOLD_SOURCE_1_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
      dsPowerConfigurationClusterServerAttributes.batterySourceThreeAlarmState.value |= BATTERY_TWO_MIN_THRESHOLD_MASK;
      alarmNotification(ZCL_BATTERY_MIN_THRESHOLD_SOURCE_2_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
      dsPowerConfigurationClusterServerAttributes.batterySourceThreeAlarmState.value |= BATTERY_THREE_MIN_THRESHOLD_MASK;
      alarmNotification(ZCL_BATTERY_MIN_THRESHOLD_SOURCE_3_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
    }
  }
  else if(dsPowerConfigurationClusterServerAttributes.batterySourceThreeAlarmMask.value.batteryAlarm1 == 1)
  {
    if((smallestOfTwo(measuredVoltage,thresholdOne) == measuredVoltage) && (measuredVoltage > minThreshold))
    {
      dsPowerConfigurationClusterServerAttributes.batterySourceThreeAlarmState.value |= BATTERY_ONE_THRESHOLD_1_MASK;
      alarmNotification(ZCL_BATTERY_THRESHOLD_1_SOURCE_1_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
      dsPowerConfigurationClusterServerAttributes.batterySourceThreeAlarmState.value |= BATTERY_TWO_THRESHOLD_1_MASK;
      alarmNotification(ZCL_BATTERY_THRESHOLD_1_SOURCE_2_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
      dsPowerConfigurationClusterServerAttributes.batterySourceThreeAlarmState.value |= BATTERY_THREE_THRESHOLD_1_MASK;
      alarmNotification(ZCL_BATTERY_THRESHOLD_1_SOURCE_3_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
    }
  }
  else if(dsPowerConfigurationClusterServerAttributes.batterySourceThreeAlarmMask.value.batteryAlarm2 == 1)
  {
    if((smallestOfTwo(measuredVoltage,thresholdTwo) == measuredVoltage) && (measuredVoltage > thresholdOne))
    {
      dsPowerConfigurationClusterServerAttributes.batterySourceThreeAlarmState.value |= BATTERY_ONE_THRESHOLD_2_MASK;
      alarmNotification(ZCL_BATTERY_THRESHOLD_2_SOURCE_1_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
      dsPowerConfigurationClusterServerAttributes.batterySourceThreeAlarmState.value |= BATTERY_TWO_THRESHOLD_2_MASK;
      alarmNotification(ZCL_BATTERY_THRESHOLD_2_SOURCE_2_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
      dsPowerConfigurationClusterServerAttributes.batterySourceThreeAlarmState.value |= BATTERY_THREE_THRESHOLD_2_MASK;
      alarmNotification(ZCL_BATTERY_THRESHOLD_2_SOURCE_3_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
    }
  }
  else if(dsPowerConfigurationClusterServerAttributes.batterySourceThreeAlarmMask.value.batteryAlarm3 == 1)
  {
    if((smallestOfTwo(measuredVoltage,thresholdThree) == measuredVoltage) && (measuredVoltage > thresholdTwo))
    {
      dsPowerConfigurationClusterServerAttributes.batterySourceThreeAlarmState.value |= BATTERY_ONE_THRESHOLD_3_MASK;
      alarmNotification(ZCL_BATTERY_THRESHOLD_3_SOURCE_1_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
      dsPowerConfigurationClusterServerAttributes.batterySourceThreeAlarmState.value |= BATTERY_TWO_THRESHOLD_3_MASK;
      alarmNotification(ZCL_BATTERY_THRESHOLD_3_SOURCE_2_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
      dsPowerConfigurationClusterServerAttributes.batterySourceThreeAlarmState.value |= BATTERY_THREE_THRESHOLD_3_MASK;
      alarmNotification(ZCL_BATTERY_THRESHOLD_3_SOURCE_3_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
    }
  } 
}
#endif

/**************************************************************************//**
\brief Initializes power configuration cluster attributes to their defaults
\param NA
******************************************************************************/
void powerConfigurationClusterInitAttributes()
{
  powerConfigurationInformationAttrInit();
  powerConfigurationSettingsAttrInit();
}

/**************************************************************************//**
\brief Initializes the power configuration information attributes to their defaults
\param NA
******************************************************************************/
static void powerConfigurationInformationAttrInit()
{
  dsPowerConfigurationClusterServerAttributes.batterySourceOneVoltage.value = ZCL_DS_DEFAULT_BATTERY_VOLTAGE;
  dsPowerConfigurationClusterServerAttributes.batterySourceTwoVoltage.value = ZCL_DS_DEFAULT_BATTERY_VOLTAGE;
  dsPowerConfigurationClusterServerAttributes.batterySourceThreeVoltage.value = ZCL_DS_DEFAULT_BATTERY_VOLTAGE;

  dsPowerConfigurationClusterServerAttributes.batterySourceOnePercentageRemaining.value = ZCL_DS_DEFAULT_BATTERY_PERCENTAGE;
  dsPowerConfigurationClusterServerAttributes.batterySourceTwoPercentageRemaining.value = ZCL_DS_DEFAULT_BATTERY_PERCENTAGE;
  dsPowerConfigurationClusterServerAttributes.batterySourceThreePercentageRemaining.value = ZCL_DS_DEFAULT_BATTERY_PERCENTAGE;
}

/**************************************************************************//**
\brief Initializes the power configuration settings attributes to their defaults
\param NA
******************************************************************************/
static void powerConfigurationSettingsAttrInit()
{
  dsPowerConfigurationClusterServerAttributes.batterySourceOneSize.value = ZCL_DS_DEFAULT_BATTERY_SIZE;
  dsPowerConfigurationClusterServerAttributes.batterySourceTwoSize.value = ZCL_DS_DEFAULT_BATTERY_SIZE;
  dsPowerConfigurationClusterServerAttributes.batterySourceThreeSize.value = ZCL_DS_DEFAULT_BATTERY_SIZE;

  dsPowerConfigurationClusterServerAttributes.batterySourceOneQuantity.value = ZCL_DS_DEFAULT_BATTERY_QUANDITY;
  dsPowerConfigurationClusterServerAttributes.batterySourceTwoQuantity.value = ZCL_DS_DEFAULT_BATTERY_QUANDITY;
  dsPowerConfigurationClusterServerAttributes.batterySourceThreeQuantity.value = ZCL_DS_DEFAULT_BATTERY_QUANDITY;

  memset(&dsPowerConfigurationClusterServerAttributes.batterySourceOneAlarmMask.value,ZCL_DS_DEFAULT_BATTERY_ALARM_MASK,sizeof(uint8_t));
  memset(&dsPowerConfigurationClusterServerAttributes.batterySourceTwoAlarmMask.value,ZCL_DS_DEFAULT_BATTERY_ALARM_MASK,sizeof(uint8_t));
  memset(&dsPowerConfigurationClusterServerAttributes.batterySourceThreeAlarmMask.value,ZCL_DS_DEFAULT_BATTERY_ALARM_MASK,sizeof(uint8_t));

  dsPowerConfigurationClusterServerAttributes.batterySourceOneAlarmState.value = 0;
  dsPowerConfigurationClusterServerAttributes.batterySourceTwoAlarmState.value = 0;
  dsPowerConfigurationClusterServerAttributes.batterySourceThreeAlarmState.value = 0;

  dsPowerConfigurationClusterServerAttributes.batterySourceOneVoltageMinThreshold.value = ZCL_DS_DEFAULT_BATTERY_MIN_THREASHOLD;
  dsPowerConfigurationClusterServerAttributes.batterySourceTwoVoltageMinThreshold.value = ZCL_DS_DEFAULT_BATTERY_MIN_THREASHOLD;
  dsPowerConfigurationClusterServerAttributes.batterySourceThreeVoltageMinThreshold.value = ZCL_DS_DEFAULT_BATTERY_MIN_THREASHOLD;

  dsPowerConfigurationClusterServerAttributes.batterySourceOneVoltageThreshold_1.value = ZCL_DS_DEFAULT_BATTERY_THREASHOLD_1;
  dsPowerConfigurationClusterServerAttributes.batterySourceTwoVoltageThreshold_1.value = ZCL_DS_DEFAULT_BATTERY_THREASHOLD_1;
  dsPowerConfigurationClusterServerAttributes.batterySourceThreeVoltageThreshold_1.value = ZCL_DS_DEFAULT_BATTERY_THREASHOLD_1;

  dsPowerConfigurationClusterServerAttributes.batterySourceOneVoltageThreshold_2.value = ZCL_DS_DEFAULT_BATTERY_THREASHOLD_2;
  dsPowerConfigurationClusterServerAttributes.batterySourceTwoVoltageThreshold_2.value = ZCL_DS_DEFAULT_BATTERY_THREASHOLD_2;
  dsPowerConfigurationClusterServerAttributes.batterySourceThreeVoltageThreshold_2.value = ZCL_DS_DEFAULT_BATTERY_THREASHOLD_2;

  dsPowerConfigurationClusterServerAttributes.batterySourceOneVoltageThreshold_3.value = ZCL_DS_DEFAULT_BATTERY_THREASHOLD_3;
  dsPowerConfigurationClusterServerAttributes.batterySourceTwoVoltageThreshold_3.value = ZCL_DS_DEFAULT_BATTERY_THREASHOLD_3;
  dsPowerConfigurationClusterServerAttributes.batterySourceThreeVoltageThreshold_3.value = ZCL_DS_DEFAULT_BATTERY_THREASHOLD_3;

  dsPowerConfigurationClusterServerAttributes.batterySourceOnePercentageMinThreshold.value = ZCL_DS_DEFAULT_BATTERY_MIN_THREASHOLD;
  dsPowerConfigurationClusterServerAttributes.batterySourceTwoPercentageMinThreshold.value = ZCL_DS_DEFAULT_BATTERY_MIN_THREASHOLD;
  dsPowerConfigurationClusterServerAttributes.batterySourceThreePercentageMinThreshold.value = ZCL_DS_DEFAULT_BATTERY_MIN_THREASHOLD;

  dsPowerConfigurationClusterServerAttributes.batterySourceOnePercentageThreshold_1.value = ZCL_DS_DEFAULT_BATTERY_THREASHOLD_1;
  dsPowerConfigurationClusterServerAttributes.batterySourceTwoPercentageThreshold_1.value = ZCL_DS_DEFAULT_BATTERY_THREASHOLD_1;
  dsPowerConfigurationClusterServerAttributes.batterySourceThreePercentageThreshold_1.value = ZCL_DS_DEFAULT_BATTERY_THREASHOLD_1;

  dsPowerConfigurationClusterServerAttributes.batterySourceOnePercentageThreshold_2.value = ZCL_DS_DEFAULT_BATTERY_THREASHOLD_2;
  dsPowerConfigurationClusterServerAttributes.batterySourceTwoPercentageThreshold_2.value = ZCL_DS_DEFAULT_BATTERY_THREASHOLD_2;
  dsPowerConfigurationClusterServerAttributes.batterySourceThreePercentageThreshold_2.value = ZCL_DS_DEFAULT_BATTERY_THREASHOLD_2;

  dsPowerConfigurationClusterServerAttributes.batterySourceOnePercentageThreshold_3.value = ZCL_DS_DEFAULT_BATTERY_THREASHOLD_3;
  dsPowerConfigurationClusterServerAttributes.batterySourceTwoPercentageThreshold_3.value = ZCL_DS_DEFAULT_BATTERY_THREASHOLD_3;
  dsPowerConfigurationClusterServerAttributes.batterySourceThreePercentageThreshold_3.value = ZCL_DS_DEFAULT_BATTERY_THREASHOLD_3;
}

/****************************************************************//**
 \brief Resets a particular AlarmMask
 \param alarmCode - The AlarmMask to be Reset
 \return none
********************************************************************/
static void dsPwrResetAlarm(uint8_t alarmCode)
{
  if (alarmCode == BATTERY_ONE_MIN_THRESHOLD_MASK)
  {
    if (dsPowerConfigurationClusterServerAttributes.batterySourceOneAlarmState.value & BATTERY_ONE_MIN_THRESHOLD_MASK)
    {
      dsPowerConfigurationClusterServerAttributes.batterySourceOneAlarmState.value &= ~BATTERY_ONE_MIN_THRESHOLD_MASK;
      alarmNotification(ZCL_BATTERY_MIN_THRESHOLD_SOURCE_1_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
    }
    if (dsPowerConfigurationClusterServerAttributes.batterySourceTwoAlarmState.value & BATTERY_ONE_MIN_THRESHOLD_MASK)
    {
      dsPowerConfigurationClusterServerAttributes.batterySourceTwoAlarmState.value &= ~BATTERY_ONE_MIN_THRESHOLD_MASK;
      alarmNotification(ZCL_BATTERY_MIN_THRESHOLD_SOURCE_1_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
    }
    if (dsPowerConfigurationClusterServerAttributes.batterySourceThreeAlarmState.value & BATTERY_ONE_MIN_THRESHOLD_MASK)
    {
      dsPowerConfigurationClusterServerAttributes.batterySourceThreeAlarmState.value &= ~BATTERY_ONE_MIN_THRESHOLD_MASK;
      alarmNotification(ZCL_BATTERY_MIN_THRESHOLD_SOURCE_1_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
    }
  }
  else if (alarmCode == ZCL_BATTERY_THRESHOLD_1_SOURCE_1_ALARM)
  {
    if (dsPowerConfigurationClusterServerAttributes.batterySourceOneAlarmState.value & BATTERY_ONE_THRESHOLD_1_MASK)
    {
      dsPowerConfigurationClusterServerAttributes.batterySourceOneAlarmState.value &= ~BATTERY_ONE_THRESHOLD_1_MASK;
      alarmNotification(ZCL_BATTERY_THRESHOLD_1_SOURCE_1_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
    }
    if (dsPowerConfigurationClusterServerAttributes.batterySourceTwoAlarmState.value & BATTERY_ONE_THRESHOLD_1_MASK)
    {
      dsPowerConfigurationClusterServerAttributes.batterySourceTwoAlarmState.value &= ~BATTERY_ONE_THRESHOLD_1_MASK;
      alarmNotification(ZCL_BATTERY_THRESHOLD_1_SOURCE_1_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
    }
    if (dsPowerConfigurationClusterServerAttributes.batterySourceThreeAlarmState.value & BATTERY_ONE_THRESHOLD_1_MASK)
    {
      dsPowerConfigurationClusterServerAttributes.batterySourceThreeAlarmState.value &= ~BATTERY_ONE_THRESHOLD_1_MASK;
      alarmNotification(ZCL_BATTERY_THRESHOLD_1_SOURCE_1_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
    }
  }
  else if (alarmCode == ZCL_BATTERY_THRESHOLD_2_SOURCE_1_ALARM)
  {
    if (dsPowerConfigurationClusterServerAttributes.batterySourceOneAlarmState.value & BATTERY_ONE_THRESHOLD_2_MASK)
    {
      dsPowerConfigurationClusterServerAttributes.batterySourceOneAlarmState.value &= ~BATTERY_ONE_THRESHOLD_2_MASK;
      alarmNotification(ZCL_BATTERY_THRESHOLD_2_SOURCE_1_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
    }
    if (dsPowerConfigurationClusterServerAttributes.batterySourceTwoAlarmState.value & BATTERY_ONE_THRESHOLD_2_MASK)
    {
      dsPowerConfigurationClusterServerAttributes.batterySourceTwoAlarmState.value &= ~BATTERY_ONE_THRESHOLD_2_MASK;
      alarmNotification(ZCL_BATTERY_THRESHOLD_2_SOURCE_1_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
    }
    if (dsPowerConfigurationClusterServerAttributes.batterySourceThreeAlarmState.value & BATTERY_ONE_THRESHOLD_2_MASK)
    {
      dsPowerConfigurationClusterServerAttributes.batterySourceThreeAlarmState.value &= ~BATTERY_ONE_THRESHOLD_2_MASK;
      alarmNotification(ZCL_BATTERY_THRESHOLD_2_SOURCE_1_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
    }
  }
  else if (alarmCode == ZCL_BATTERY_THRESHOLD_3_SOURCE_1_ALARM)
  {
    if (dsPowerConfigurationClusterServerAttributes.batterySourceOneAlarmState.value & BATTERY_ONE_THRESHOLD_3_MASK)
    {
      dsPowerConfigurationClusterServerAttributes.batterySourceOneAlarmState.value &= ~BATTERY_ONE_THRESHOLD_3_MASK;
      alarmNotification(ZCL_BATTERY_THRESHOLD_3_SOURCE_1_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
    }
    if (dsPowerConfigurationClusterServerAttributes.batterySourceTwoAlarmState.value & BATTERY_ONE_THRESHOLD_3_MASK)
    {
      dsPowerConfigurationClusterServerAttributes.batterySourceTwoAlarmState.value &= ~BATTERY_ONE_THRESHOLD_3_MASK;
      alarmNotification(ZCL_BATTERY_THRESHOLD_3_SOURCE_1_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
    }
    if (dsPowerConfigurationClusterServerAttributes.batterySourceThreeAlarmState.value & BATTERY_ONE_THRESHOLD_3_MASK)
    {
      dsPowerConfigurationClusterServerAttributes.batterySourceThreeAlarmState.value &= ~BATTERY_ONE_THRESHOLD_3_MASK;
      alarmNotification(ZCL_BATTERY_THRESHOLD_3_SOURCE_1_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
    }
  }
  else if (alarmCode == ZCL_BATTERY_MIN_THRESHOLD_SOURCE_2_ALARM)
  {
    if (dsPowerConfigurationClusterServerAttributes.batterySourceOneAlarmState.value & BATTERY_TWO_MIN_THRESHOLD_MASK)
    {
      dsPowerConfigurationClusterServerAttributes.batterySourceOneAlarmState.value &= ~BATTERY_TWO_MIN_THRESHOLD_MASK;
      alarmNotification(ZCL_BATTERY_MIN_THRESHOLD_SOURCE_2_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
    }
    if (dsPowerConfigurationClusterServerAttributes.batterySourceTwoAlarmState.value & BATTERY_TWO_MIN_THRESHOLD_MASK)
    {
      dsPowerConfigurationClusterServerAttributes.batterySourceTwoAlarmState.value &= ~BATTERY_TWO_MIN_THRESHOLD_MASK;
      alarmNotification(ZCL_BATTERY_MIN_THRESHOLD_SOURCE_2_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
    }
    if (dsPowerConfigurationClusterServerAttributes.batterySourceThreeAlarmState.value & BATTERY_TWO_MIN_THRESHOLD_MASK)
    {
      dsPowerConfigurationClusterServerAttributes.batterySourceThreeAlarmState.value &= ~BATTERY_TWO_MIN_THRESHOLD_MASK;
      alarmNotification(ZCL_BATTERY_MIN_THRESHOLD_SOURCE_2_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
    }
  }
  else if (alarmCode == ZCL_BATTERY_THRESHOLD_1_SOURCE_2_ALARM)
  {
    if (dsPowerConfigurationClusterServerAttributes.batterySourceOneAlarmState.value & BATTERY_TWO_THRESHOLD_1_MASK)
    {
      dsPowerConfigurationClusterServerAttributes.batterySourceOneAlarmState.value &= ~BATTERY_TWO_THRESHOLD_1_MASK;
      alarmNotification(ZCL_BATTERY_THRESHOLD_1_SOURCE_2_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
    }
    if (dsPowerConfigurationClusterServerAttributes.batterySourceTwoAlarmState.value & BATTERY_TWO_THRESHOLD_1_MASK)
    {
      dsPowerConfigurationClusterServerAttributes.batterySourceTwoAlarmState.value &= ~BATTERY_TWO_THRESHOLD_1_MASK;
      alarmNotification(ZCL_BATTERY_THRESHOLD_1_SOURCE_2_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
    }
    if (dsPowerConfigurationClusterServerAttributes.batterySourceThreeAlarmState.value & BATTERY_TWO_THRESHOLD_1_MASK)
    {
      dsPowerConfigurationClusterServerAttributes.batterySourceThreeAlarmState.value &= ~BATTERY_TWO_THRESHOLD_1_MASK;
      alarmNotification(ZCL_BATTERY_THRESHOLD_1_SOURCE_2_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
    }
  }
  else if (alarmCode == ZCL_BATTERY_THRESHOLD_2_SOURCE_2_ALARM)
  {
    if (dsPowerConfigurationClusterServerAttributes.batterySourceOneAlarmState.value & BATTERY_TWO_THRESHOLD_2_MASK)
    {
      dsPowerConfigurationClusterServerAttributes.batterySourceOneAlarmState.value &= ~BATTERY_TWO_THRESHOLD_2_MASK;
      alarmNotification(ZCL_BATTERY_THRESHOLD_2_SOURCE_2_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
    }
    if (dsPowerConfigurationClusterServerAttributes.batterySourceTwoAlarmState.value & BATTERY_TWO_THRESHOLD_2_MASK)
    {
      dsPowerConfigurationClusterServerAttributes.batterySourceTwoAlarmState.value &= ~BATTERY_TWO_THRESHOLD_2_MASK;
      alarmNotification(ZCL_BATTERY_THRESHOLD_2_SOURCE_2_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
    }
    if (dsPowerConfigurationClusterServerAttributes.batterySourceThreeAlarmState.value & BATTERY_TWO_THRESHOLD_2_MASK)
    {
      dsPowerConfigurationClusterServerAttributes.batterySourceThreeAlarmState.value &= ~BATTERY_TWO_THRESHOLD_2_MASK;
      alarmNotification(ZCL_BATTERY_THRESHOLD_2_SOURCE_2_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
    }
  }
  else if (alarmCode == ZCL_BATTERY_THRESHOLD_3_SOURCE_2_ALARM)
  {
    if (dsPowerConfigurationClusterServerAttributes.batterySourceOneAlarmState.value & BATTERY_TWO_THRESHOLD_3_MASK)
    {
      dsPowerConfigurationClusterServerAttributes.batterySourceOneAlarmState.value &= ~BATTERY_TWO_THRESHOLD_3_MASK;
      alarmNotification(ZCL_BATTERY_THRESHOLD_3_SOURCE_2_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
    }
    if (dsPowerConfigurationClusterServerAttributes.batterySourceTwoAlarmState.value & BATTERY_TWO_THRESHOLD_3_MASK)
    {
      dsPowerConfigurationClusterServerAttributes.batterySourceTwoAlarmState.value &= ~BATTERY_TWO_THRESHOLD_3_MASK;
      alarmNotification(ZCL_BATTERY_THRESHOLD_3_SOURCE_2_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
    }
    if (dsPowerConfigurationClusterServerAttributes.batterySourceThreeAlarmState.value & BATTERY_TWO_THRESHOLD_3_MASK)
    {
      dsPowerConfigurationClusterServerAttributes.batterySourceThreeAlarmState.value &= ~BATTERY_TWO_THRESHOLD_3_MASK;
      alarmNotification(ZCL_BATTERY_THRESHOLD_3_SOURCE_2_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
    }
  }
  else if (alarmCode == ZCL_BATTERY_MIN_THRESHOLD_SOURCE_3_ALARM)
  {
    if (dsPowerConfigurationClusterServerAttributes.batterySourceOneAlarmState.value & BATTERY_THREE_MIN_THRESHOLD_MASK)
    {
      dsPowerConfigurationClusterServerAttributes.batterySourceOneAlarmState.value &= ~BATTERY_THREE_MIN_THRESHOLD_MASK;
      alarmNotification(ZCL_BATTERY_MIN_THRESHOLD_SOURCE_3_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
    }
    if (dsPowerConfigurationClusterServerAttributes.batterySourceTwoAlarmState.value & BATTERY_THREE_MIN_THRESHOLD_MASK)
    {
      dsPowerConfigurationClusterServerAttributes.batterySourceTwoAlarmState.value &= ~BATTERY_THREE_MIN_THRESHOLD_MASK;
      alarmNotification(ZCL_BATTERY_MIN_THRESHOLD_SOURCE_3_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
    }
    if (dsPowerConfigurationClusterServerAttributes.batterySourceThreeAlarmState.value & BATTERY_THREE_MIN_THRESHOLD_MASK)
    {
      dsPowerConfigurationClusterServerAttributes.batterySourceThreeAlarmState.value &= ~BATTERY_THREE_MIN_THRESHOLD_MASK;
      alarmNotification(ZCL_BATTERY_MIN_THRESHOLD_SOURCE_3_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
    }
  }
  else if (alarmCode == ZCL_BATTERY_THRESHOLD_1_SOURCE_3_ALARM)
  {
    if (dsPowerConfigurationClusterServerAttributes.batterySourceOneAlarmState.value & BATTERY_THREE_THRESHOLD_1_MASK)
    {
      dsPowerConfigurationClusterServerAttributes.batterySourceOneAlarmState.value &= ~BATTERY_THREE_THRESHOLD_1_MASK;
      alarmNotification(ZCL_BATTERY_THRESHOLD_1_SOURCE_3_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
    }
    if (dsPowerConfigurationClusterServerAttributes.batterySourceTwoAlarmState.value & BATTERY_THREE_THRESHOLD_1_MASK)
    {
      dsPowerConfigurationClusterServerAttributes.batterySourceTwoAlarmState.value &= ~BATTERY_THREE_THRESHOLD_1_MASK;
      alarmNotification(ZCL_BATTERY_THRESHOLD_1_SOURCE_3_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
    }
    if (dsPowerConfigurationClusterServerAttributes.batterySourceThreeAlarmState.value & BATTERY_THREE_THRESHOLD_1_MASK)
    {
      dsPowerConfigurationClusterServerAttributes.batterySourceThreeAlarmState.value &= ~BATTERY_THREE_THRESHOLD_1_MASK;
      alarmNotification(ZCL_BATTERY_THRESHOLD_1_SOURCE_3_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
    }
  }
  else if (alarmCode == ZCL_BATTERY_THRESHOLD_2_SOURCE_3_ALARM)
  {
    if (dsPowerConfigurationClusterServerAttributes.batterySourceOneAlarmState.value & BATTERY_THREE_THRESHOLD_2_MASK)
    {
      dsPowerConfigurationClusterServerAttributes.batterySourceOneAlarmState.value &= ~BATTERY_THREE_THRESHOLD_2_MASK;
      alarmNotification(ZCL_BATTERY_THRESHOLD_2_SOURCE_3_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
    }
    if (dsPowerConfigurationClusterServerAttributes.batterySourceTwoAlarmState.value & BATTERY_THREE_THRESHOLD_2_MASK)
    {
      dsPowerConfigurationClusterServerAttributes.batterySourceTwoAlarmState.value &= ~BATTERY_THREE_THRESHOLD_2_MASK;
      alarmNotification(ZCL_BATTERY_THRESHOLD_2_SOURCE_3_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
    }
    if (dsPowerConfigurationClusterServerAttributes.batterySourceThreeAlarmState.value & BATTERY_THREE_THRESHOLD_2_MASK)
    {
      dsPowerConfigurationClusterServerAttributes.batterySourceThreeAlarmState.value &= ~BATTERY_THREE_THRESHOLD_2_MASK;
      alarmNotification(ZCL_BATTERY_THRESHOLD_2_SOURCE_3_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
    }
  }
  else if (alarmCode == ZCL_BATTERY_THRESHOLD_3_SOURCE_3_ALARM)
  {
    if (dsPowerConfigurationClusterServerAttributes.batterySourceOneAlarmState.value & BATTERY_THREE_THRESHOLD_3_MASK)
    {
      dsPowerConfigurationClusterServerAttributes.batterySourceOneAlarmState.value &= ~BATTERY_THREE_THRESHOLD_3_MASK;
      alarmNotification(ZCL_BATTERY_THRESHOLD_3_SOURCE_3_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
    }
    if (dsPowerConfigurationClusterServerAttributes.batterySourceTwoAlarmState.value & BATTERY_THREE_THRESHOLD_3_MASK)
    {
      dsPowerConfigurationClusterServerAttributes.batterySourceTwoAlarmState.value &= ~BATTERY_THREE_THRESHOLD_3_MASK;
      alarmNotification(ZCL_BATTERY_THRESHOLD_3_SOURCE_3_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
    }
    if (dsPowerConfigurationClusterServerAttributes.batterySourceThreeAlarmState.value & BATTERY_THREE_THRESHOLD_3_MASK)
    {
      dsPowerConfigurationClusterServerAttributes.batterySourceThreeAlarmState.value &= ~BATTERY_THREE_THRESHOLD_3_MASK;
      alarmNotification(ZCL_BATTERY_THRESHOLD_3_SOURCE_3_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
    }
  }
}

/****************************************************************//**
 \brief Resets all active AlarmMasks
 \param none
 \return none
********************************************************************/
static void dsPwrResetAllAlarms(void)
{
  if (dsPowerConfigurationClusterServerAttributes.batterySourceOneAlarmState.value & BATTERY_ONE_MIN_THRESHOLD_MASK)
  {
    dsPowerConfigurationClusterServerAttributes.batterySourceOneAlarmState.value &= ~BATTERY_ONE_MIN_THRESHOLD_MASK;
    alarmNotification(ZCL_BATTERY_MIN_THRESHOLD_SOURCE_1_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
  }
  if (dsPowerConfigurationClusterServerAttributes.batterySourceTwoAlarmState.value & BATTERY_ONE_MIN_THRESHOLD_MASK)
  {
    dsPowerConfigurationClusterServerAttributes.batterySourceTwoAlarmState.value &= ~BATTERY_ONE_MIN_THRESHOLD_MASK;
    alarmNotification(ZCL_BATTERY_MIN_THRESHOLD_SOURCE_1_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
  }
  if (dsPowerConfigurationClusterServerAttributes.batterySourceThreeAlarmState.value & BATTERY_ONE_MIN_THRESHOLD_MASK)
  {
    dsPowerConfigurationClusterServerAttributes.batterySourceThreeAlarmState.value &= ~BATTERY_ONE_MIN_THRESHOLD_MASK;
    alarmNotification(ZCL_BATTERY_MIN_THRESHOLD_SOURCE_1_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
  }
  if (dsPowerConfigurationClusterServerAttributes.batterySourceOneAlarmState.value & BATTERY_ONE_THRESHOLD_1_MASK)
  {
    dsPowerConfigurationClusterServerAttributes.batterySourceOneAlarmState.value &= ~BATTERY_ONE_THRESHOLD_1_MASK;
    alarmNotification(ZCL_BATTERY_THRESHOLD_1_SOURCE_1_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
  }
  if (dsPowerConfigurationClusterServerAttributes.batterySourceTwoAlarmState.value & BATTERY_ONE_THRESHOLD_1_MASK)
  {
    dsPowerConfigurationClusterServerAttributes.batterySourceTwoAlarmState.value &= ~BATTERY_ONE_THRESHOLD_1_MASK;
    alarmNotification(ZCL_BATTERY_THRESHOLD_1_SOURCE_1_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
  }
  if (dsPowerConfigurationClusterServerAttributes.batterySourceThreeAlarmState.value & BATTERY_ONE_THRESHOLD_1_MASK)
  {
    dsPowerConfigurationClusterServerAttributes.batterySourceThreeAlarmState.value &= ~BATTERY_ONE_THRESHOLD_1_MASK;
    alarmNotification(ZCL_BATTERY_THRESHOLD_1_SOURCE_1_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
  }
  
  if (dsPowerConfigurationClusterServerAttributes.batterySourceOneAlarmState.value & BATTERY_ONE_THRESHOLD_2_MASK)
  {
    dsPowerConfigurationClusterServerAttributes.batterySourceOneAlarmState.value &= ~BATTERY_ONE_THRESHOLD_2_MASK;
    alarmNotification(ZCL_BATTERY_THRESHOLD_2_SOURCE_1_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
  }
  if (dsPowerConfigurationClusterServerAttributes.batterySourceTwoAlarmState.value & BATTERY_ONE_THRESHOLD_2_MASK)
  {
    dsPowerConfigurationClusterServerAttributes.batterySourceTwoAlarmState.value &= ~BATTERY_ONE_THRESHOLD_2_MASK;
    alarmNotification(ZCL_BATTERY_THRESHOLD_2_SOURCE_1_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
  }
  if (dsPowerConfigurationClusterServerAttributes.batterySourceThreeAlarmState.value & BATTERY_ONE_THRESHOLD_2_MASK)
  {
    dsPowerConfigurationClusterServerAttributes.batterySourceThreeAlarmState.value &= ~BATTERY_ONE_THRESHOLD_2_MASK;
    alarmNotification(ZCL_BATTERY_THRESHOLD_2_SOURCE_1_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
  }
  if (dsPowerConfigurationClusterServerAttributes.batterySourceOneAlarmState.value & BATTERY_ONE_THRESHOLD_3_MASK)
  {
    dsPowerConfigurationClusterServerAttributes.batterySourceOneAlarmState.value &= ~BATTERY_ONE_THRESHOLD_3_MASK;
    alarmNotification(ZCL_BATTERY_THRESHOLD_3_SOURCE_1_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
  }
  if (dsPowerConfigurationClusterServerAttributes.batterySourceTwoAlarmState.value & BATTERY_ONE_THRESHOLD_3_MASK)
  {
    dsPowerConfigurationClusterServerAttributes.batterySourceTwoAlarmState.value &= ~BATTERY_ONE_THRESHOLD_3_MASK;
    alarmNotification(ZCL_BATTERY_THRESHOLD_3_SOURCE_1_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
  }
  if (dsPowerConfigurationClusterServerAttributes.batterySourceThreeAlarmState.value & BATTERY_ONE_THRESHOLD_3_MASK)
  {
    dsPowerConfigurationClusterServerAttributes.batterySourceThreeAlarmState.value &= ~BATTERY_ONE_THRESHOLD_3_MASK;
    alarmNotification(ZCL_BATTERY_THRESHOLD_3_SOURCE_1_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
  }

  if (dsPowerConfigurationClusterServerAttributes.batterySourceOneAlarmState.value & BATTERY_TWO_MIN_THRESHOLD_MASK)
  {
    dsPowerConfigurationClusterServerAttributes.batterySourceOneAlarmState.value &= ~BATTERY_TWO_MIN_THRESHOLD_MASK;
    alarmNotification(ZCL_BATTERY_MIN_THRESHOLD_SOURCE_2_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
  }
  if (dsPowerConfigurationClusterServerAttributes.batterySourceTwoAlarmState.value & BATTERY_TWO_MIN_THRESHOLD_MASK)
  {
    dsPowerConfigurationClusterServerAttributes.batterySourceTwoAlarmState.value &= ~BATTERY_TWO_MIN_THRESHOLD_MASK;
    alarmNotification(ZCL_BATTERY_MIN_THRESHOLD_SOURCE_2_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
  }
  if (dsPowerConfigurationClusterServerAttributes.batterySourceThreeAlarmState.value & BATTERY_TWO_MIN_THRESHOLD_MASK)
  {
    dsPowerConfigurationClusterServerAttributes.batterySourceThreeAlarmState.value &= ~BATTERY_TWO_MIN_THRESHOLD_MASK;
    alarmNotification(ZCL_BATTERY_MIN_THRESHOLD_SOURCE_2_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
  }
  if (dsPowerConfigurationClusterServerAttributes.batterySourceOneAlarmState.value & BATTERY_TWO_THRESHOLD_1_MASK)
  {
    dsPowerConfigurationClusterServerAttributes.batterySourceOneAlarmState.value &= ~BATTERY_TWO_THRESHOLD_1_MASK;
    alarmNotification(ZCL_BATTERY_THRESHOLD_1_SOURCE_2_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
  }
  if (dsPowerConfigurationClusterServerAttributes.batterySourceTwoAlarmState.value & BATTERY_TWO_THRESHOLD_1_MASK)
  {
    dsPowerConfigurationClusterServerAttributes.batterySourceTwoAlarmState.value &= ~BATTERY_TWO_THRESHOLD_1_MASK;
    alarmNotification(ZCL_BATTERY_THRESHOLD_1_SOURCE_2_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
  }
  if (dsPowerConfigurationClusterServerAttributes.batterySourceThreeAlarmState.value & BATTERY_TWO_THRESHOLD_1_MASK)
  {
    dsPowerConfigurationClusterServerAttributes.batterySourceThreeAlarmState.value &= ~BATTERY_TWO_THRESHOLD_1_MASK;
    alarmNotification(ZCL_BATTERY_THRESHOLD_1_SOURCE_2_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
  }
  if (dsPowerConfigurationClusterServerAttributes.batterySourceOneAlarmState.value & BATTERY_TWO_THRESHOLD_2_MASK)
  {
    dsPowerConfigurationClusterServerAttributes.batterySourceOneAlarmState.value &= ~BATTERY_TWO_THRESHOLD_2_MASK;
    alarmNotification(ZCL_BATTERY_THRESHOLD_2_SOURCE_2_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
  }
  if (dsPowerConfigurationClusterServerAttributes.batterySourceTwoAlarmState.value & BATTERY_TWO_THRESHOLD_2_MASK)
  {
    dsPowerConfigurationClusterServerAttributes.batterySourceTwoAlarmState.value &= ~BATTERY_TWO_THRESHOLD_2_MASK;
    alarmNotification(ZCL_BATTERY_THRESHOLD_2_SOURCE_2_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
  }
  if (dsPowerConfigurationClusterServerAttributes.batterySourceThreeAlarmState.value & BATTERY_TWO_THRESHOLD_2_MASK)
  {
    dsPowerConfigurationClusterServerAttributes.batterySourceThreeAlarmState.value &= ~BATTERY_TWO_THRESHOLD_2_MASK;
    alarmNotification(ZCL_BATTERY_THRESHOLD_2_SOURCE_2_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
  }
  if (dsPowerConfigurationClusterServerAttributes.batterySourceOneAlarmState.value & BATTERY_TWO_THRESHOLD_3_MASK)
  {
    dsPowerConfigurationClusterServerAttributes.batterySourceOneAlarmState.value &= ~BATTERY_TWO_THRESHOLD_3_MASK;
    alarmNotification(ZCL_BATTERY_THRESHOLD_3_SOURCE_2_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
  }
  if (dsPowerConfigurationClusterServerAttributes.batterySourceTwoAlarmState.value & BATTERY_TWO_THRESHOLD_3_MASK)
  {
    dsPowerConfigurationClusterServerAttributes.batterySourceTwoAlarmState.value &= ~BATTERY_TWO_THRESHOLD_3_MASK;
    alarmNotification(ZCL_BATTERY_THRESHOLD_3_SOURCE_2_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
  }
  if (dsPowerConfigurationClusterServerAttributes.batterySourceThreeAlarmState.value & BATTERY_TWO_THRESHOLD_3_MASK)
  {
    dsPowerConfigurationClusterServerAttributes.batterySourceThreeAlarmState.value &= ~BATTERY_TWO_THRESHOLD_3_MASK;
    alarmNotification(ZCL_BATTERY_THRESHOLD_3_SOURCE_2_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
  }
  if (dsPowerConfigurationClusterServerAttributes.batterySourceOneAlarmState.value & BATTERY_THREE_MIN_THRESHOLD_MASK)
  {
    dsPowerConfigurationClusterServerAttributes.batterySourceOneAlarmState.value &= ~BATTERY_THREE_MIN_THRESHOLD_MASK;
    alarmNotification(ZCL_BATTERY_MIN_THRESHOLD_SOURCE_3_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
  }
  if (dsPowerConfigurationClusterServerAttributes.batterySourceTwoAlarmState.value & BATTERY_THREE_MIN_THRESHOLD_MASK)
  {
    dsPowerConfigurationClusterServerAttributes.batterySourceTwoAlarmState.value &= ~BATTERY_THREE_MIN_THRESHOLD_MASK;
    alarmNotification(ZCL_BATTERY_MIN_THRESHOLD_SOURCE_3_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
  }
  if (dsPowerConfigurationClusterServerAttributes.batterySourceThreeAlarmState.value & BATTERY_THREE_MIN_THRESHOLD_MASK)
  {
    dsPowerConfigurationClusterServerAttributes.batterySourceThreeAlarmState.value &= ~BATTERY_THREE_MIN_THRESHOLD_MASK;
    alarmNotification(ZCL_BATTERY_MIN_THRESHOLD_SOURCE_3_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
  }
  if (dsPowerConfigurationClusterServerAttributes.batterySourceOneAlarmState.value & BATTERY_THREE_THRESHOLD_1_MASK)
  {
    dsPowerConfigurationClusterServerAttributes.batterySourceOneAlarmState.value &= ~BATTERY_THREE_THRESHOLD_1_MASK;
    alarmNotification(ZCL_BATTERY_THRESHOLD_1_SOURCE_3_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
  }
  if (dsPowerConfigurationClusterServerAttributes.batterySourceTwoAlarmState.value & BATTERY_THREE_THRESHOLD_1_MASK)
  {
    dsPowerConfigurationClusterServerAttributes.batterySourceTwoAlarmState.value &= ~BATTERY_THREE_THRESHOLD_1_MASK;
    alarmNotification(ZCL_BATTERY_THRESHOLD_1_SOURCE_3_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
  }
  if (dsPowerConfigurationClusterServerAttributes.batterySourceThreeAlarmState.value & BATTERY_THREE_THRESHOLD_1_MASK)
  {
    dsPowerConfigurationClusterServerAttributes.batterySourceThreeAlarmState.value &= ~BATTERY_THREE_THRESHOLD_1_MASK;
    alarmNotification(ZCL_BATTERY_THRESHOLD_1_SOURCE_3_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
  }
  if (dsPowerConfigurationClusterServerAttributes.batterySourceOneAlarmState.value & BATTERY_THREE_THRESHOLD_2_MASK)
  {
    dsPowerConfigurationClusterServerAttributes.batterySourceOneAlarmState.value &= ~BATTERY_THREE_THRESHOLD_2_MASK;
    alarmNotification(ZCL_BATTERY_THRESHOLD_2_SOURCE_3_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
  }
  if (dsPowerConfigurationClusterServerAttributes.batterySourceTwoAlarmState.value & BATTERY_THREE_THRESHOLD_2_MASK)
  {
    dsPowerConfigurationClusterServerAttributes.batterySourceTwoAlarmState.value &= ~BATTERY_THREE_THRESHOLD_2_MASK;
    alarmNotification(ZCL_BATTERY_THRESHOLD_2_SOURCE_3_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
  }
  if (dsPowerConfigurationClusterServerAttributes.batterySourceThreeAlarmState.value & BATTERY_THREE_THRESHOLD_2_MASK)
  {
    dsPowerConfigurationClusterServerAttributes.batterySourceThreeAlarmState.value &= ~BATTERY_THREE_THRESHOLD_2_MASK;
    alarmNotification(ZCL_BATTERY_THRESHOLD_2_SOURCE_3_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
  }
  if (dsPowerConfigurationClusterServerAttributes.batterySourceOneAlarmState.value & BATTERY_THREE_THRESHOLD_3_MASK)
  {
    dsPowerConfigurationClusterServerAttributes.batterySourceOneAlarmState.value &= ~BATTERY_THREE_THRESHOLD_3_MASK;
    alarmNotification(ZCL_BATTERY_THRESHOLD_3_SOURCE_3_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
  }
  if (dsPowerConfigurationClusterServerAttributes.batterySourceTwoAlarmState.value & BATTERY_THREE_THRESHOLD_3_MASK)
  {
    dsPowerConfigurationClusterServerAttributes.batterySourceTwoAlarmState.value &= ~BATTERY_THREE_THRESHOLD_3_MASK;
    alarmNotification(ZCL_BATTERY_THRESHOLD_3_SOURCE_3_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
  }
  if (dsPowerConfigurationClusterServerAttributes.batterySourceThreeAlarmState.value & BATTERY_THREE_THRESHOLD_3_MASK)
  {
    dsPowerConfigurationClusterServerAttributes.batterySourceThreeAlarmState.value &= ~BATTERY_THREE_THRESHOLD_3_MASK;
    alarmNotification(ZCL_BATTERY_THRESHOLD_3_SOURCE_3_ALARM, POWER_CONFIGURATION_CLUSTER_ID);
  }
}

#if (APP_ENABLE_CERTIFICATION_EXTENSION == 0)
/****************************************************************//**
 \brief Finding the samllest of Two numbers
 \param one - The first Number
 \param two  - The second number
 \return uint16_t
********************************************************************/
static uint16_t smallestOfTwo(uint16_t one, uint16_t two)
{
  return (one < two ? one : two);
}
#endif

#endif // APP_DEVICE_TYPE_DIMMER_SWITCH

// eof dsPowerConfigurationCluster.c
