/**************************************************************************//**
\file  halAppClock.h

\brief Declarations of appTimer hardware-dependent module.

\author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

\internal
  History:
    19/08/13 Agasthian.s - Created
******************************************************************************/
/******************************************************************************
 *   WARNING: CHANGING THIS FILE MAY AFFECT CORE FUNCTIONALITY OF THE STACK.  *
 *   EXPERT USERS SHOULD PROCEED WITH CAUTION.                                *
 ******************************************************************************/

#ifndef _HALAPPCLOCK_H
#define _HALAPPCLOCK_H

/******************************************************************************
                   Includes section
******************************************************************************/
#include <halClkCtrl.h>
#include <halTaskManager.h>

/******************************************************************************
                   Define(s) section
******************************************************************************/
/** \brief system timer interval in ms */
#define HAL_APPTIMERINTERVAL 10ul
/** \brief frequency prescaler for system timer */
#if defined(HAL_8MHz)
  #define TIMER_CLOCK_SOURCE   6 /* OSC8M - Internal */
  #define TIMER_FREQUENCY_PRESCALER  8
#endif
/** \brief timer counter top value */
#define TOP_TIMER_COUNTER_VALUE  ((F_CPU/1000ul) / TIMER_FREQUENCY_PRESCALER) * HAL_APPTIMERINTERVAL
/** \brief Usable timer channel */
#define HAL_TIMER_CHANNEL  0

/******************************************************************************
                   Prototypes section
******************************************************************************/
/**************************************************************************//**
\brief configure, enable and start timer counter channel 0
******************************************************************************/
void halStartAppClock(void);

/**************************************************************************//**
\brief Stop and disable timer
******************************************************************************/
void halStopAppClock(void);

/**************************************************************************//**
\brief Synchronization system time which based on application timer.
******************************************************************************/
void halAppSystemTimeSynchronize(void);

/**************************************************************************//**
\brief Return time of sleep timer.

\return
  time in ms.
******************************************************************************/
uint32_t halGetTimeOfAppTimer(void);

/**************************************************************************//**
\brief Delay in microseconds.

\param[in] us - delay time in microseconds
******************************************************************************/
void halDelayUs(uint16_t us);

/**************************************************************************//**
\brief Takes account of the sleep interval.

\param[in]
  interval - time of sleep
******************************************************************************/
void halAdjustSleepInterval(uint32_t interval);
#endif
// eof halAppClock.h
