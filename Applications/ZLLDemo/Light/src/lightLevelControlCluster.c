/**************************************************************************//**
  \file lightLevelControlCluster.c

  \brief
    Light device Level Control cluster implementation.

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
#include <zcl.h>
#include <zclZllLevelControlCluster.h>
#if defined(BOARD_MEGARF) || defined(BOARD_SAMR21)
#include <ledsExt.h>
#include <lcdExt.h>
#endif
#include <debug.h>
#include <lightOnOffCluster.h>
#include <lightScenesCluster.h>
#include <zllDemo.h>
#include <lightLevelControlCluster.h>
#include <pdsDataServer.h>

#include <N_DeviceInfo_Bindings.h>
#include <N_DeviceInfo.h>

/******************************************************************************
                    Prototypes section
******************************************************************************/
static ZCL_Status_t moveToLevelInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload);
static ZCL_Status_t moveInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload);
static ZCL_Status_t stepInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload);
static ZCL_Status_t stopInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload);
static ZCL_Status_t moveToLevelWOnOffInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload);
static ZCL_Status_t moveWOnOffInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload);
static ZCL_Status_t stepWOnOffInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload);
static ZCL_Status_t stopWOnOffInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload);

static void setLevel(bool wOnOff, uint8_t level);
static void moveToLevel(bool wOnOff, uint8_t newLevel, uint16_t transitionTime);
static void stopMoving(void);
static void updateTransitionState(void);
static void adjustOnOffState(uint8_t level);

/******************************************************************************
                    Global variables
******************************************************************************/
ZCL_LevelControlClusterServerAttributes_t levelControlClusterServerAttributes =
{
  ZCL_DEFINE_LEVEL_CONTROL_CLUSTER_SERVER_MANDATORY_ATTRIBUTES(0, 0)
};

ZCL_LevelControlClusterCommands_t levelControlClusterServerCommands =
{
  ZCL_DEFINE_LEVEL_CONTROL_CLUSTER_COMMANDS(moveToLevelInd, moveInd, stepInd, stopInd,
      moveToLevelWOnOffInd, moveWOnOffInd, stepWOnOffInd, stopWOnOffInd)
};

/******************************************************************************
                    Local variables
******************************************************************************/
static HAL_AppTimer_t updateTimer;
static uint8_t gTargetLevel;
static uint16_t gTransitionTime;
static int16_t gDelta;
static bool gWithOnOff;

/******************************************************************************
                    Implementations
******************************************************************************/

/**************************************************************************//**
\brief Initialize Level Control cluster.
******************************************************************************/
void levelControlClusterInit(void)
{
  if (!PDS_IsAbleToRestore(APP_LIGHT_LEVEL_CONTROL_CLUSTER_SERVER_ATTR_MEM_ID))
  {
    levelControlClusterServerAttributes.currentLevel.value = MAX_LIGHT_LEVEL / 2;
    levelControlClusterServerAttributes.remainingTime.value = 0;
  }

  levelControlDisplayLevel();
}

/**************************************************************************//**
\brief Set Extension Field Set
******************************************************************************/
void levelControlClusterSetExtensionField(uint16_t currentLevel)
{
  stopMoving();
  setLevel(false, currentLevel);
}

/**************************************************************************//**
\brief Display current level value.
******************************************************************************/
void levelControlDisplayLevel(void)
{
  uint8_t level = levelControlClusterServerAttributes.currentLevel.value;

  LCD_PRINT(2, 0, "%3d", level);
#if (APP_ENABLE_CERTIFICATION_EXTENSION == 0 && APP_ZLL_DEVICE_TYPE >= APP_DEVICE_TYPE_DIMMABLE_LIGHT)
  {
    LOG_STRING(currentLevelValueStr, "Current level value: %3d\r\n");

    appSnprintf(currentLevelValueStr, level);
  }
#endif //APP_ENABLE_CERTIFICATION_EXTENSION == 0

  if (!zllDeviceIsOn())
    level = 0;

  LEDS_SET_BRIGHTNESS(level);
  (void)level;
}

/**************************************************************************//**
\brief Set Current Level attribute to a specified value
******************************************************************************/
static void setLevel(bool wOnOff, uint8_t level)
{
  if (wOnOff)
    adjustOnOffState(level);

  levelControlClusterServerAttributes.currentLevel.value = level;
  scenesClusterInvalidate();
#if APP_ZLL_DEVICE_TYPE >= APP_DEVICE_TYPE_DIMMABLE_LIGHT
  levelControlDisplayLevel();
#endif
}

/**************************************************************************//**
\brief On/off value adjustment regarding to current level

\param[in] level - current level value
******************************************************************************/
static void adjustOnOffState(uint8_t level)
{
  bool turnOn = (level == MIN_LIGHT_LEVEL) ? false : true;

  onOffClusterSetExtensionField(turnOn);
#if APP_ZLL_DEVICE_TYPE == APP_DEVICE_TYPE_ON_OFF_LIGHT
  if(level > MIN_LIGHT_LEVEL)
  {
    LOG_STRING(onRcvdStr, "On\r\n");
    appSnprintf(onRcvdStr);
  }
  else
  {
    LOG_STRING(offRcvdStr, "Off\r\n");
    appSnprintf(offRcvdStr);
  }
#endif
}

/**************************************************************************//**
\brief Stat moving to the specified level
******************************************************************************/
static void moveToLevel(bool wOnOff, uint8_t newLevel, uint16_t transitionTime)
{
  int16_t level = newLevel;
  stopMoving();

  gTransitionTime = transitionTime;
  gTargetLevel = newLevel;
  gDelta = level - levelControlClusterServerAttributes.currentLevel.value;
  gWithOnOff = wOnOff;

  updateTimer.mode = TIMER_REPEAT_MODE;
  updateTimer.interval = UPDATE_TIMER_INTERVAL;
  updateTimer.callback = updateTransitionState;
  HAL_StopAppTimer(&updateTimer);
  HAL_StartAppTimer(&updateTimer);

  levelControlClusterServerAttributes.remainingTime.value = transitionTime;
}

/**************************************************************************//**
\brief Update transition state
******************************************************************************/
static void updateTransitionState(void)
{
  if (!zllDeviceIsOn() && !gWithOnOff)
  {
    levelControlClusterServerAttributes.remainingTime.value = 0;
    HAL_StopAppTimer(&updateTimer);
    return;
  }

  levelControlClusterServerAttributes.remainingTime.value--;

  if (levelControlClusterServerAttributes.remainingTime.value > 0)
  {
    int32_t remainingTime = levelControlClusterServerAttributes.remainingTime.value;
    int16_t newLevel = (int16_t)gTargetLevel - ((remainingTime * gDelta) / (int32_t)gTransitionTime);
    setLevel(gWithOnOff, (uint8_t)newLevel);
  }
  else
  {
    HAL_StopAppTimer(&updateTimer);
    setLevel(gWithOnOff, gTargetLevel);
    gWithOnOff = false;

    PDS_Store(ZLL_APP_MEMORY_MEM_ID);
  }
}

/**************************************************************************//**
\brief Stop moving
******************************************************************************/
static void stopMoving(void)
{
  HAL_StopAppTimer(&updateTimer);
  gWithOnOff = false;
  levelControlClusterServerAttributes.remainingTime.value = 0;
  levelControlDisplayLevel();
}

/**************************************************************************//**
\brief Process Move To Level command
******************************************************************************/
static ZCL_Status_t processMoveToLevel(bool wOnOff, ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload)
{
  ZCL_MoveToLevel_t *req = (ZCL_MoveToLevel_t *)payload;
  ZCL_Status_t status;
  uint8_t type;
  uint8_t onOffState;

  status = ZCL_ReadAttributeValue(APP_ENDPOINT_LIGHT, ONOFF_CLUSTER_ID, ZCL_CLUSTER_SIDE_SERVER,
                                  ZCL_ONOFF_CLUSTER_ONOFF_SERVER_ATTRIBUTE_ID, &type, &onOffState);

  if (!wOnOff && !onOffState && !status)
    return ZCL_SUCCESS_STATUS;

  if (!wOnOff && !zllDeviceIsOn())
    return ZCL_SUCCESS_STATUS;

  if (req->level > MAX_LIGHT_LEVEL)
    req->level = MAX_LIGHT_LEVEL;

  if (req->level < MIN_LIGHT_LEVEL)
    req->level = MIN_LIGHT_LEVEL;

  if (0xffff != req->transitionTime && 0 != req->transitionTime)
  {
    moveToLevel(wOnOff, req->level, req->transitionTime);
  }
  else
  {
    setLevel(wOnOff, req->level);
    PDS_Store(ZLL_APP_MEMORY_MEM_ID);
  }

  (void)addressing;
  (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Process Move command
******************************************************************************/
static ZCL_Status_t processMove(bool wOnOff, ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload)
{
  ZCL_Move_t *req = (ZCL_Move_t *)payload;
  uint16_t transitionTime = MIN_TRANSITION_TIME;
  uint8_t level = MIN_LIGHT_LEVEL;
  uint8_t currentLevel = 0;

  ZCL_Status_t status;
  uint8_t type;
  uint8_t onOffState;

  status = ZCL_ReadAttributeValue(APP_ENDPOINT_LIGHT, ONOFF_CLUSTER_ID, ZCL_CLUSTER_SIDE_SERVER,
                                  ZCL_ONOFF_CLUSTER_ONOFF_SERVER_ATTRIBUTE_ID, &type, &onOffState);

  if (!wOnOff && !onOffState && !status)
    return ZCL_SUCCESS_STATUS;

  if (!wOnOff && !zllDeviceIsOn())
    return ZCL_SUCCESS_STATUS;

  currentLevel = levelControlClusterServerAttributes.currentLevel.value;

  if (ZLL_LEVEL_CONTROL_UP_DIRECTION == req->moveMode)
  {
    level = MAX_LIGHT_LEVEL;
    transitionTime = ((MAX_LIGHT_LEVEL - currentLevel) * 10 /* 1/10 sec */) / req->rate;
  }

  else if (ZLL_LEVEL_CONTROL_DOWN_DIRECTION == req->moveMode)
  {
    level = MIN_LIGHT_LEVEL;
    transitionTime = ((currentLevel - MIN_LIGHT_LEVEL) * 10 /* 1/10 sec */) / req->rate;
  }

  moveToLevel(wOnOff, level, transitionTime);

  (void)addressing;
  (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Process Step command
******************************************************************************/
static ZCL_Status_t processStep(bool wOnOff, ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload)
{
  ZCL_Step_t *req = (ZCL_Step_t *)payload;
  int16_t level;
  ZCL_Status_t status;
  uint8_t type;
  uint8_t onOffState;

  status = ZCL_ReadAttributeValue(APP_ENDPOINT_LIGHT, ONOFF_CLUSTER_ID, ZCL_CLUSTER_SIDE_SERVER,
                                  ZCL_ONOFF_CLUSTER_ONOFF_SERVER_ATTRIBUTE_ID, &type, &onOffState);

  if (!wOnOff && !onOffState && !status)
    return ZCL_SUCCESS_STATUS;

  if (!wOnOff && !zllDeviceIsOn())
    return ZCL_SUCCESS_STATUS;

  level = levelControlClusterServerAttributes.currentLevel.value;

  if (ZLL_LEVEL_CONTROL_UP_DIRECTION == req->stepMode)
  {
    level += req->stepSize;

    if (level > MAX_LIGHT_LEVEL)
      level = MAX_LIGHT_LEVEL;
  }

  else if (ZLL_LEVEL_CONTROL_DOWN_DIRECTION == req->stepMode)
  {
    level -= req->stepSize;

    if (level < MIN_LIGHT_LEVEL)
      level = MIN_LIGHT_LEVEL;
  }

  if (0xffff != req->transitionTime && 0 != req->transitionTime)
  {
    moveToLevel(wOnOff, level, req->transitionTime);
  }

  if (!wOnOff && !zllDeviceIsOn())
    return ZCL_SUCCESS_STATUS;

  stopMoving();
  setLevel(wOnOff, level);
  PDS_Store(ZLL_APP_MEMORY_MEM_ID);

  (void)addressing;
  (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Process Stop command
******************************************************************************/
static ZCL_Status_t processStop(bool wOnOff, ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload)
{
  ZCL_Status_t status;
  uint8_t type;
  uint8_t onOffState;

  status = ZCL_ReadAttributeValue(APP_ENDPOINT_LIGHT, ONOFF_CLUSTER_ID, ZCL_CLUSTER_SIDE_SERVER,
                                  ZCL_ONOFF_CLUSTER_ONOFF_SERVER_ATTRIBUTE_ID, &type, &onOffState);

  if (!wOnOff && !onOffState && !status)
    return ZCL_SUCCESS_STATUS;

  stopMoving();
  PDS_Store(ZLL_APP_MEMORY_MEM_ID);

  (void)wOnOff;
  (void)addressing;
  (void)payloadLength;
  (void)payload;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receive of Move To Level command
******************************************************************************/
static ZCL_Status_t moveToLevelInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload)
{
  return processMoveToLevel(false, addressing, payloadLength, payload);
}

/**************************************************************************//**
\brief Callback on receive of Move command
******************************************************************************/
static ZCL_Status_t moveInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload)
{
  return processMove(false, addressing, payloadLength, payload);
}

/**************************************************************************//**
\brief Callback on receive of Step command
******************************************************************************/
static ZCL_Status_t stepInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload)
{
  return processStep(false, addressing, payloadLength, payload);
}

/**************************************************************************//**
\brief Callback on receive of Stop command
******************************************************************************/
static ZCL_Status_t stopInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload)
{
  return processStop(false, addressing, payloadLength, payload);
}

/**************************************************************************//**
\brief Callback on receive of Move To Level With On/Off command
******************************************************************************/
static ZCL_Status_t moveToLevelWOnOffInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload)
{
  onOffClusterSetGlobalSceneControl();
  return processMoveToLevel(true, addressing, payloadLength, payload);
}

/**************************************************************************//**
\brief Callback on receive of Move With On/Off command
******************************************************************************/
static ZCL_Status_t moveWOnOffInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload)
{
  return processMove(true, addressing, payloadLength, payload);
}

/**************************************************************************//**
\brief Callback on receive of Step With On/Off command
******************************************************************************/
static ZCL_Status_t stepWOnOffInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload)
{
  return processStep(true, addressing, payloadLength, payload);
}

/**************************************************************************//**
\brief Callback on receive of Stop With On/Off command
******************************************************************************/
static ZCL_Status_t stopWOnOffInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload)
{
  return processStop(true, addressing, payloadLength, payload);
}

#else // // APP_ZLL_DEVICE_TYPE >= APP_DEVICE_TYPE_ON_OFF_LIGHT
void levelControlClusterInit(void) {;}
void levelControlDisplayLevel(void) {;}
#endif // APP_ZLL_DEVICE_TYPE >= APP_DEVICE_TYPE_ON_OFF_LIGHT

// eof lightLevelControlCluster.c
