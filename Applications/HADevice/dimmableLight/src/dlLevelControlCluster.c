/**************************************************************************//**
  \file dlLevelControlCluster.c

  \brief
    Dimmable Light Level Control cluster implementation.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    11.12.12 N. Fomin - Created.
******************************************************************************/
#ifdef APP_DEVICE_TYPE_DIMMABLE_LIGHT

/******************************************************************************
                    Includes section
******************************************************************************/
#include <dlLevelControlCluster.h>
#include <dlOnOffCluster.h>
#include <dlScenesCluster.h>
#include <appTimer.h>
#include <uartManager.h>
#include <pdsDataServer.h>

/******************************************************************************
                    Definition(s) section
******************************************************************************/
#define MAX_LIGHT_LEVEL 254
#define MIN_LIGHT_LEVEL 1

#define LEVEL_TRANSITION_TIMER_INTERVAL 100

/******************************************************************************
                    Types section
******************************************************************************/
typedef struct
{
  uint16_t transitionTime;
  uint8_t  level;
  int16_t  levelDelta;
  uint16_t remainingTime;
} DlLevelControlMem_t;

/******************************************************************************
                    Prototypes section
******************************************************************************/
static ZCL_Status_t moveToLevelInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_MoveToLevel_t *payload);
static ZCL_Status_t moveInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_Move_t *payload);
static ZCL_Status_t stepInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_Step_t *payload);
static ZCL_Status_t stopInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload);
static ZCL_Status_t moveToLevelWOnOffInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_MoveToLevelWithOnOff_t *payload);
static ZCL_Status_t moveWOnOffInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_MoveWithOnOff_t *payload);
static ZCL_Status_t stepWOnOffInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_StepWithOnOff_t *payload);
static ZCL_Status_t stopWOnOffInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload);

static void moveToLevel(uint8_t level, uint16_t time, bool onOff);
static void moveLevel(uint8_t mode, uint8_t rate, bool onOff);
static void stepLevel(uint8_t mode, uint8_t size, uint16_t time, bool onOff);

static void levelTransitionTimerFired(void);

static void setLevel(uint8_t level);

/******************************************************************************
                    Global variables section
******************************************************************************/
ZCL_LevelControlClusterServerAttributes_t dlLevelControlClusterServerAttributes =
{
  ZCL_DEFINE_LEVEL_CONTROL_CLUSTER_SERVER_MANDATORY_ATTRIBUTES(LEVEL_CONTROL_VAL_MIN_REPORT_PERIOD, LEVEL_CONTROL_VAL_MAX_REPORT_PERIOD)
};
ZCL_LevelControlClusterCommands_t         dlLevelControlCommands =
{
  ZCL_DEFINE_LEVEL_CONTROL_CLUSTER_COMMANDS(moveToLevelInd, moveInd, stepInd, stopInd,
                                            moveToLevelWOnOffInd, moveWOnOffInd, stepWOnOffInd, stopWOnOffInd)
};

/******************************************************************************
                    Static variables section
******************************************************************************/
static HAL_AppTimer_t      levelTransitionTimer;
static DlLevelControlMem_t levelControlMem;

/******************************************************************************
                    Implementation section
******************************************************************************/
/**************************************************************************//**
\brief Initializes Level Control cluster
******************************************************************************/
void levelControlClusterInit(void)
{
  dlLevelControlClusterServerAttributes.currentLevel.value = 0;

  levelTransitionTimer.mode     = TIMER_REPEAT_MODE;
  levelTransitionTimer.interval = LEVEL_TRANSITION_TIMER_INTERVAL;
  levelTransitionTimer.callback = levelTransitionTimerFired;
}

/**************************************************************************//**
\brief Stops Level Control cluster
******************************************************************************/
void levelControlClusterStop(void)
{
  HAL_StopAppTimer(&levelTransitionTimer);
}

/**************************************************************************//**
\brief Gets current color level

\returns current coloe level
******************************************************************************/
uint8_t levelControlCurrentLevel(void)
{
  return dlLevelControlClusterServerAttributes.currentLevel.value;
}

/**************************************************************************//**
\brief Sets color level

\param[in] level - color level
******************************************************************************/
void levelControlSetLevel(uint8_t level)
{
  HAL_StopAppTimer(&levelTransitionTimer);

  dlLevelControlClusterServerAttributes.currentLevel.value = level;
  ZCL_ReportOnChangeIfNeeded(&dlLevelControlClusterServerAttributes.currentLevel);
  PDS_Store(APP_DL_LEVEL_CONTROL_MEM_ID);
}

/**************************************************************************//**
\brief Callback on receiving Move To Level command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
static ZCL_Status_t moveToLevelInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_MoveToLevel_t *payload)
{
  LOG_STRING(moveToLevelStr, "->MoveToLevel: lvl=0x%x trTime=%u\r\n");
  appSnprintf(moveToLevelStr, payload->level, payload->transitionTime);
  moveToLevel(payload->level, payload->transitionTime, false);

  (void)addressing, (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receiving Move command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
static ZCL_Status_t moveInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_Move_t *payload)
{
  LOG_STRING(moveStr, "->Move: mode=0x%x rate=0x%x\r\n");
  appSnprintf(moveStr, payload->moveMode, payload->rate);
  moveLevel(payload->moveMode, payload->rate, false);

  (void)addressing, (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receiving Step command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
static ZCL_Status_t stepInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_Step_t *payload)
{
  LOG_STRING(stepStr, "->Step: mode=0x%x stepSize=0x%x trTime=%u\r\n");
  appSnprintf(stepStr, payload->stepMode, payload->stepSize, payload->transitionTime);
  stepLevel(payload->stepMode, payload->stepSize, payload->transitionTime, false);

  (void)addressing, (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receiving Stop command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
static ZCL_Status_t stopInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload)
{
  LOG_STRING(stopStr, "->Stop\r\n");
  appSnprintf(stopStr);

  HAL_StopAppTimer(&levelTransitionTimer);

  (void)addressing, (void)payloadLength, (void)payload;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receiving Move To Level With On/Off command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
static ZCL_Status_t moveToLevelWOnOffInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_MoveToLevelWithOnOff_t *payload)
{
  LOG_STRING(moveToLevelStr, "->MoveToLevelWithOnOff: lvl=0x%x trTime=%u\r\n");
  appSnprintf(moveToLevelStr, payload->level, payload->transitionTime);
  moveToLevel(payload->level, payload->transitionTime, true);

  (void)addressing, (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receiving Move With On/Off command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
static ZCL_Status_t moveWOnOffInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_MoveWithOnOff_t *payload)
{
  LOG_STRING(moveStr, "->Move with on/off: mode=0x%x rate=0x%x\r\n");
  appSnprintf(moveStr, payload->moveMode, payload->rate);
  moveLevel(payload->moveMode, payload->rate, true);

  (void)addressing, (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receiving Step With On/Off command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
static ZCL_Status_t stepWOnOffInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_StepWithOnOff_t *payload)
{
  LOG_STRING(stepStr, "->Step with on/off: mode=0x%x stepSize=0x%x trTime=%u\r\n");
  appSnprintf(stepStr, payload->stepMode, payload->stepSize, payload->transitionTime);
  stepLevel(payload->stepMode, payload->stepSize, payload->transitionTime, true);

  (void)addressing, (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receiving Stop With On/Off command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
static ZCL_Status_t stopWOnOffInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload)
{
  LOG_STRING(stopStr, "->Stop with on/off\r\n");
  appSnprintf(stopStr);

  HAL_StopAppTimer(&levelTransitionTimer);

  (void)addressing, (void)payloadLength, (void)payload;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Moves to color level

\param[in] level - new color level;
\param[in] time  - transition time;
\param[in] onOff - true if level should be moved with on/off effect
******************************************************************************/
static void moveToLevel(uint8_t level, uint16_t time, bool onOff)
{
  // stop any other level changing
  HAL_StopAppTimer(&levelTransitionTimer);

  // update on/off cluster (on the same ep) attribute value if command is with on/off effect
  if (onOff)
    onOffSetOnOffState(true);

  if (level > MAX_LIGHT_LEVEL)
    level = MAX_LIGHT_LEVEL;
  if (level < MIN_LIGHT_LEVEL)
    level = MIN_LIGHT_LEVEL;

  if (ZCL_LEVEL_CONTROL_CLUSTER_ASAP_TRANSITION_TIME == time)
  {
    setLevel(level);
    return;
  }

  // store current level transition parameters
  levelControlMem.transitionTime = time;
  levelControlMem.level          = level;
  levelControlMem.levelDelta     = level - dlLevelControlClusterServerAttributes.currentLevel.value;
  levelControlMem.remainingTime  = time;

  HAL_StartAppTimer(&levelTransitionTimer);
}

/**************************************************************************//**
\brief Moves color level

\param[in] mode  - move mode (up or down);
\param[in] rate  - move rate;
\param[in] onOff - true if level should be moved with on/off effect
******************************************************************************/
static void moveLevel(uint8_t mode, uint8_t rate, bool onOff)
{
  // stop any other level changing
  HAL_StopAppTimer(&levelTransitionTimer);

  // update on/off cluster (on the same ep) attribute value if command is with on/off effect
  if (onOff)
    onOffSetOnOffState(true);

  if (ZCL_MOVE_MODE_UP == mode)
  {
    levelControlMem.level          = MAX_LIGHT_LEVEL;
    levelControlMem.transitionTime = ((MAX_LIGHT_LEVEL - dlLevelControlClusterServerAttributes.currentLevel.value) *
      10) / rate;
  }
  else
  {
    levelControlMem.level          = MIN_LIGHT_LEVEL;
    levelControlMem.transitionTime = ((dlLevelControlClusterServerAttributes.currentLevel.value - MIN_LIGHT_LEVEL) *
      10) / rate;
  }
  levelControlMem.levelDelta    = levelControlMem.level - dlLevelControlClusterServerAttributes.currentLevel.value;
  levelControlMem.remainingTime = levelControlMem.transitionTime;

  HAL_StartAppTimer(&levelTransitionTimer);
}

/**************************************************************************//**
\brief Steps color level

\param[in] mode  - step mode (up or down);
\param[in] size  - step size;
\param[in] time  - transition time;
\param[in] onOff - true if level should be moved with on/off effect
******************************************************************************/
static void stepLevel(uint8_t mode, uint8_t size, uint16_t time, bool onOff)
{
  // stop any other level changing
  HAL_StopAppTimer(&levelTransitionTimer);

  // update on/off cluster (on the same ep) attribute value if command is with on/off effect
  if (onOff)
    onOffSetOnOffState(true);

  if (ZCL_STEP_MODE_UP == mode)
  {
    levelControlMem.level += size;
    levelControlMem.level = MIN(levelControlMem.level, MAX_LIGHT_LEVEL);
  }
  else
  {
    levelControlMem.level -= size;
    levelControlMem.level = MAX(levelControlMem.level, MIN_LIGHT_LEVEL);
  }

  if (ZCL_LEVEL_CONTROL_CLUSTER_ASAP_TRANSITION_TIME == time)
  {
    setLevel(levelControlMem.level);
    return;
  }

  levelControlMem.levelDelta    = levelControlMem.level - dlLevelControlClusterServerAttributes.currentLevel.value;
  levelControlMem.remainingTime = time;
  HAL_StartAppTimer(&levelTransitionTimer);
}

/**************************************************************************//**
\brief Level transition timer has fired
******************************************************************************/
static void levelTransitionTimerFired(void)
{
  if (--levelControlMem.remainingTime)
  {
    uint32_t remainingTime = levelControlMem.remainingTime;
    int16_t  level         = (int16_t)levelControlMem.level -
      (remainingTime * levelControlMem.levelDelta) / (int32_t)levelControlMem.transitionTime;

    setLevel((uint8_t)level);
  }
  else
  {
    HAL_StopAppTimer(&levelTransitionTimer);
    setLevel(levelControlMem.level);
    LOG_STRING(levelTransactionFinishedStr, " + Color level transition is finished. Current level is %u\r\n");
    appSnprintf(levelTransactionFinishedStr, levelControlMem.level);
    PDS_Store(APP_DL_LEVEL_CONTROL_MEM_ID);
  }
}

/**************************************************************************//**
\brief Sets color level

\param[in] level - new color level
******************************************************************************/
static void setLevel(uint8_t level)
{
  dlLevelControlClusterServerAttributes.currentLevel.value = level;
  ZCL_ReportOnChangeIfNeeded(&dlLevelControlClusterServerAttributes.currentLevel);

  scenesInvalidate();
}

#endif // APP_DEVICE_TYPE_DIMMABLE_LIGHT
// eof dlLevelControlCluster.c

