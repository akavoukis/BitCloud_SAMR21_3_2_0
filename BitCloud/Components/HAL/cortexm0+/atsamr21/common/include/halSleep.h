/**************************************************************************//**
  \file  halSleep.h

  \brief Interface to control sleep mode.

  \author
      Atmel Corporation: http://www.atmel.com \n
      Support email: avr@atmel.com

    Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
    Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
      15/05/14 Viswanadham Kotla - Created
 ******************************************************************************/
/******************************************************************************
 *   WARNING: CHANGING THIS FILE MAY AFFECT CORE FUNCTIONALITY OF THE STACK.  *
 *   EXPERT USERS SHOULD PROCEED WITH CAUTION.                                *
 ******************************************************************************/

#ifndef _HALSLEEP_H
#define _HALSLEEP_H

/******************************************************************************
                   Includes section
******************************************************************************/
#include <sleep.h>
#include <sleepTimer.h>

/******************************************************************************
                   Defines section
******************************************************************************/
#define HAL_ACTIVE_MODE                    0
#define HAL_SLEEP_MODE                     1
#define HAL_SLEEP_TIMER_IS_STOPPED         0
#define HAL_SLEEP_TIMER_IS_STARTED         1
#define HAL_SLEEP_TIMER_IS_WAKEUP_SOURCE   0
#define HAL_EXT_IRQ_IS_WAKEUP_SOURCE       1
#define HAL_SLEEP_STATE_BEGIN              0
#define HAL_SLEEP_STATE_CONTINUE_SLEEP     1

/******************************************************************************
                   Types section
******************************************************************************/
typedef struct _HalSleepControl_t
{
  HAL_WakeUpCallback_t callback;
  HAL_SleepTimer_t sleepTimer;
  HAL_SleepMode_t sleepMode;
  uint8_t wakeupStation    : 1;
  uint8_t wakeupSource     : 1;
  uint8_t sleepTimerState  : 1;
  uint8_t sleepState       : 1;
  uint8_t startPoll        : 1;
} HAL_SleepControl_t;

typedef enum 
{
  SLEEPMODE_IDLE_0,
  SLEEPMODE_IDLE_1,
  SLEEPMODE_IDLE_2,
  SLEEPMODE_STANDBY
} HALSleepModes_t;
    
/******************************************************************************
                   Prototypes section
******************************************************************************/
/**************************************************************************//**
\brief Switch on system power.

\param[in]
  wakeupSource - wake up source
******************************************************************************/
void halPowerOn(const uint8_t wakeupSource);

/***************************************************************************//**
\brief Shutdown system.
  NOTES:
  the application should be sure the poweroff will not be
  interrupted after the execution of the sleep().
*******************************************************************************/
void halPowerOff(void);

#endif /* _HALSLEEP_H */
// eof halSleep.h
