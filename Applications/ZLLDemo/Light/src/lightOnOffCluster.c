/**************************************************************************//**
  \file lightOnOffCluster.c

  \brief
    Light device On/Off cluster implementation.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    28.06.11 A. Taradov - Created.
******************************************************************************/

#if APP_ZLL_DEVICE_TYPE >= APP_DEVICE_TYPE_ON_OFF_LIGHT

/******************************************************************************
                    Includes section
******************************************************************************/
#include <debug.h>
#if defined(BOARD_MEGARF) || defined(BOARD_SAMR21)
#include <ledsExt.h>
#include <lcdExt.h>
#endif
#include <zcl.h>
#include <zclZllOnOffCluster.h>
#include <lightLevelControlCluster.h>
#include <lightScenesCluster.h>
#include <zllDemo.h>
#include <pdsDataServer.h>

#include <N_DeviceInfo_Bindings.h>
#include <N_DeviceInfo.h>
#include <uartManager.h>

/******************************************************************************
                    Definitions section
******************************************************************************/
#define UPDATE_TIMER_INTERVAL    100 // 1/10th of a second as per specification
#define FADE_TIMER_INTERVAL UPDATE_TIMER_INTERVAL

/******************************************************************************
                    Types section
******************************************************************************/
typedef struct
{
  HAL_AppTimer_t timer;
  uint8_t        firstInterval;
  uint8_t        secondInterval;
  uint8_t        currentLevel;
  int16_t        delta;
  uint8_t        transitionTime;
} FadeMem_t;

/******************************************************************************
                    Prototypes section
******************************************************************************/
static ZCL_Status_t onInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload);
static ZCL_Status_t offInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload);
static ZCL_Status_t toggleInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload);
static ZCL_Status_t offWithEffectInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_OffWithEffect_t *payload);
static ZCL_Status_t onWithRecallGlobalSceneInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload);
static ZCL_Status_t onWithTimedOffInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_OnWithTimedOff_t *payload);

static void startDeviceUpdate(void);
static void stopDeviceUpdate(void);
static void displayStatus(void);
static void updateOnOffState(void);
#if APP_ZLL_DEVICE_TYPE > APP_DEVICE_TYPE_ON_OFF_LIGHT
static void fadeTimerFired(void);
static void processOffEffect(uint8_t effectId, uint8_t effectVariant);
#endif

/******************************************************************************
                    Global variables
******************************************************************************/
ZCL_OnOffClusterCommands_t onOffClusterCommands =
{
  ZCL_DEFINE_ONOFF_CLUSTER_COMMANDS(onInd, offInd, toggleInd, offWithEffectInd, onWithRecallGlobalSceneInd, onWithTimedOffInd)
};

ZCL_OnOffClusterServerAttributes_t onOffClusterServerAttributes =
{
  ZCL_DEFINE_ONOFF_CLUSTER_SERVER_ATTRIBUTES(0, 0)
};

/******************************************************************************
                    Local variables
******************************************************************************/
static HAL_AppTimer_t updateTimer;
#if APP_ZLL_DEVICE_TYPE > APP_DEVICE_TYPE_ON_OFF_LIGHT
static FadeMem_t fadeMem;
#endif

/******************************************************************************
                    Implementations section
******************************************************************************/

/**************************************************************************//**
\brief Initialize On/Off cluster.
******************************************************************************/
void onOffClusterInit(void)
{
  if (!PDS_IsAbleToRestore(APP_LIGHT_ONOFF_CLUSTER_SERVER_ATTR_MEM_ID))
  {
    onOffClusterServerAttributes.onOff.value = false;
    onOffClusterServerAttributes.globalSceneControl.value = true;
    onOffClusterServerAttributes.onTime.value = 0;
    onOffClusterServerAttributes.offWaitTime.value = 0;
  }

  updateTimer.mode = TIMER_REPEAT_MODE;
  updateTimer.interval = UPDATE_TIMER_INTERVAL;
  updateTimer.callback = updateOnOffState;

#if APP_ZLL_DEVICE_TYPE > APP_DEVICE_TYPE_ON_OFF_LIGHT
  fadeMem.timer.mode     = TIMER_REPEAT_MODE;
  fadeMem.timer.interval = FADE_TIMER_INTERVAL;
  fadeMem.timer.callback = fadeTimerFired;
#endif

  displayStatus();
}

/**************************************************************************//**
\brief Set Extension Field Set
******************************************************************************/
void onOffClusterSetExtensionField(bool onOff)
{
  if (onOffClusterServerAttributes.onOff.value != onOff)
  {
    if (!onOff)
    {
      onOffClusterServerAttributes.onTime.value = 0;
    }
    else
    {
      onOffClusterServerAttributes.offWaitTime.value = 0;
      stopDeviceUpdate();
    }

    onOffClusterServerAttributes.onOff.value = onOff;
    displayStatus();

    PDS_Store(ZLL_APP_MEMORY_MEM_ID);
  }
}

/**************************************************************************//**
\brief Set Global Scene Control attribute to 'true'
******************************************************************************/
void onOffClusterSetGlobalSceneControl(void)
{
  onOffClusterServerAttributes.globalSceneControl.value = true;
}

/**************************************************************************//**
\brief Checks, if device is in On state

\return True, if device is in On state; false - otherwise.
******************************************************************************/
bool zllDeviceIsOn(void)
{
  return onOffClusterServerAttributes.onOff.value;
}

/**************************************************************************//**
\brief Start device update procedure
******************************************************************************/
static void startDeviceUpdate(void)
{
  HAL_StopAppTimer(&updateTimer);
  HAL_StartAppTimer(&updateTimer);
}

/**************************************************************************//**
\brief Stop device update procedure
******************************************************************************/
static void stopDeviceUpdate(void)
{
  HAL_StopAppTimer(&updateTimer);
}

/**************************************************************************//**
\brief Set Extension Field Set
******************************************************************************/
static void setOnOff(bool onOff)
{
  onOffClusterServerAttributes.onOff.value = onOff;
  scenesClusterInvalidate();
  displayStatus();

  if (onOff)
  {
#if APP_ZLL_DEVICE_TYPE > APP_DEVICE_TYPE_ON_OFF_LIGHT
    LEDS_SET_BRIGHTNESS(levelControlClusterServerAttributes.currentLevel.value);
#else
    LEDS_SET_BRIGHTNESS(255);
#endif
  }
  else
  {
    LEDS_SET_BRIGHTNESS(0);
  }

  PDS_Store(ZLL_APP_MEMORY_MEM_ID);
}

/**************************************************************************//**
\brief Display current On/Off status.
******************************************************************************/
static void displayStatus(void)
{
  LCD_PRINT(0, 0, onOffClusterServerAttributes.onOff.value ? "I" : "O");
}

/**************************************************************************//**
\brief On/Off cluster update timer callback
******************************************************************************/
static void updateOnOffState(void)
{
  if (onOffClusterServerAttributes.onOff.value)
  {
    if (onOffClusterServerAttributes.onTime.value)
    {
      onOffClusterServerAttributes.onTime.value--;
    }
    else
    {
      onOffClusterServerAttributes.offWaitTime.value = 0;
      setOnOff(false);
    }
  }
  else
  {
    if (onOffClusterServerAttributes.offWaitTime.value)
    {
      onOffClusterServerAttributes.offWaitTime.value--;
    }
    else
    {
      stopDeviceUpdate();
    }
  }
}

#if APP_ZLL_DEVICE_TYPE > APP_DEVICE_TYPE_ON_OFF_LIGHT
/**************************************************************************//**
\brief Fade timer has fired
******************************************************************************/
static void fadeTimerFired(void)
{
  if (fadeMem.firstInterval)
  {
    fadeMem.firstInterval--;

    int32_t remainingTime = fadeMem.firstInterval;
    int16_t targetLevel = MIN((uint16_t)fadeMem.currentLevel + fadeMem.delta, UINT8_MAX);
    int16_t newLevel    = targetLevel - (fadeMem.delta * remainingTime) / (int32_t)fadeMem.transitionTime;

    LEDS_SET_BRIGHTNESS(newLevel);
    (void)newLevel;
  }
  else if(fadeMem.secondInterval)
  {
    fadeMem.firstInterval  = fadeMem.secondInterval;
    fadeMem.transitionTime = fadeMem.secondInterval;
    fadeMem.secondInterval = 0;
    fadeMem.currentLevel   = MIN((uint16_t)fadeMem.currentLevel + fadeMem.delta, UINT8_MAX);
    fadeMem.delta          = -fadeMem.currentLevel;
    fadeTimerFired();
  }
  else
    HAL_StopAppTimer(&fadeMem.timer);
}

/**************************************************************************//**
\brief Processes efefect of OffWithEffect command

\param[in] effectId      - effect identifier;
\param[in] effectVariant - effect variant
******************************************************************************/
static void processOffEffect(uint8_t effectId, uint8_t effectVariant)
{
  fadeMem.currentLevel = levelControlClusterServerAttributes.currentLevel.value;

  if (0 == effectId)
  {
    if (0 == effectVariant)
    {
      fadeMem.firstInterval  = 8;
      fadeMem.secondInterval = 0;
      fadeMem.delta          = -fadeMem.currentLevel;
    }
    if (1 == effectVariant)
    {
      LEDS_SET_BRIGHTNESS(0);
      return;
    }
    if (2 == effectVariant)
    {
      fadeMem.firstInterval  = 8;
      fadeMem.secondInterval = 120;
      fadeMem.delta          = -fadeMem.currentLevel / 2;
    }
  }
  if (1 == effectId)
    if (0 == effectVariant)
    {
      fadeMem.firstInterval  = 5;
      fadeMem.secondInterval = 10;
      fadeMem.delta          = ((uint16_t)fadeMem.currentLevel * 2) / 10;
    }

  if ((signed)UINT8_MAX < fadeMem.delta + fadeMem.currentLevel)
    fadeMem.delta = UINT8_MAX - fadeMem.currentLevel;
  fadeMem.transitionTime = fadeMem.firstInterval;
  HAL_StopAppTimer(&fadeMem.timer);
  HAL_StartAppTimer(&fadeMem.timer);
}
#endif

/**************************************************************************//**
\brief Callback on receive of On command
******************************************************************************/
static ZCL_Status_t onInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload)
{
  if (0 == onOffClusterServerAttributes.onTime.value)
  {
    onOffClusterServerAttributes.offWaitTime.value = 0;
    stopDeviceUpdate();
  }

  onOffClusterSetGlobalSceneControl();
  setOnOff(true);

  LOG_STRING(onRcvdStr, "On\r\n");
  appSnprintf(onRcvdStr);

  (void)addressing;
  (void)payloadLength;
  (void)payload;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receive of Off command
******************************************************************************/
static ZCL_Status_t offInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload)
{
  onOffClusterServerAttributes.onTime.value = 0;
  setOnOff(false);

  LOG_STRING(offRcvdStr, "Off\r\n");
  appSnprintf(offRcvdStr);

  onOffClusterServerAttributes.onTime.value = 0;

  (void)addressing;
  (void)payloadLength;
  (void)payload;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receive of Toggle command
******************************************************************************/
static ZCL_Status_t toggleInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload)
{
  if (false == onOffClusterServerAttributes.onOff.value)
  {
    if (0 == onOffClusterServerAttributes.onTime.value)
      onOffClusterServerAttributes.offWaitTime.value = 0;

    setOnOff(true);
    onOffClusterSetGlobalSceneControl();
  }
  else
  {
    onOffClusterServerAttributes.onTime.value = 0;
    setOnOff(false);
  }

  LOG_STRING(toggleRcvdStr, "Toggle\r\n");
  appSnprintf(toggleRcvdStr);

  (void)addressing;
  (void)payloadLength;
  (void)payload;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receive of Off With Effect command
******************************************************************************/
static ZCL_Status_t offWithEffectInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_OffWithEffect_t *payload)
{
  if (onOffClusterServerAttributes.globalSceneControl.value)
  {
    onOffClusterServerAttributes.globalSceneControl.value = false;
    scenesClusterStoreGlobalScene();
  }

#if APP_ZLL_DEVICE_TYPE > APP_DEVICE_TYPE_ON_OFF_LIGHT
  onOffClusterServerAttributes.onTime.value = 0;
  onOffClusterServerAttributes.onOff.value = false;
  scenesClusterInvalidate();
  displayStatus();
  PDS_Store(ZLL_APP_MEMORY_MEM_ID);
  processOffEffect(payload->effectIdentifier, payload->effectVariant);
#else
  setOnOff(false);
  (void)payload;
#endif

  (void)addressing;
  (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receive of On With Recall Global Scene command
******************************************************************************/
static ZCL_Status_t onWithRecallGlobalSceneInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload)
{
  setOnOff(true);
  onOffClusterServerAttributes.onTime.value = 0;
  onOffClusterServerAttributes.offWaitTime.value = 0;
  stopDeviceUpdate();

  if (false == onOffClusterServerAttributes.globalSceneControl.value)
  {
    scenesClusterRecallGlobalScene();
    onOffClusterServerAttributes.globalSceneControl.value = true;
    if (0 == onOffClusterServerAttributes.onTime.value)
      onOffClusterServerAttributes.offWaitTime.value = 0;
  }

  (void)addressing;
  (void)payloadLength;
  (void)payload;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receive of Toggle command
******************************************************************************/
static ZCL_Status_t onWithTimedOffInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_OnWithTimedOff_t *payload)
{
  if (payload->onOffControl & ZCL_ON_OFF_CLUSTER_ACCEPT_ONLY_WHEN_ON)
  {
    if (false == onOffClusterServerAttributes.onOff.value)
      return ZCL_SUCCESS_STATUS;
  }

  if (onOffClusterServerAttributes.offWaitTime.value > 0 &&
      false == onOffClusterServerAttributes.onOff.value)
  {
    onOffClusterServerAttributes.offWaitTime.value = MIN(payload->offWaitTime,
        onOffClusterServerAttributes.offWaitTime.value);
  }
  else
  {
    onOffClusterServerAttributes.onTime.value = MAX(payload->onTime,
        onOffClusterServerAttributes.onTime.value);

    onOffClusterServerAttributes.offWaitTime.value = payload->offWaitTime;

    setOnOff(true);
  }

  if (onOffClusterServerAttributes.onTime.value < 0xffff &&
      onOffClusterServerAttributes.offWaitTime.value < 0xffff)
  {
    startDeviceUpdate();
  }

  (void)addressing;
  (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}

#endif // APP_ZLL_DEVICE_TYPE >= APP_DEVICE_TYPE_ON_OFF_LIGHT

// eof lightOnOffCluster.c
