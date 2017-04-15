/**************************************************************************//**
\file  qtTimer.c

\brief Implementation of Timer module.

\author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2012, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

\internal
  History:
   14.08.14 Kanchana - Created.
*******************************************************************************/

#ifdef BOARD_QTOUCH_XPRO
/******************************************************************************
                   Includes section
******************************************************************************/
#include <halAppClock.h>
#include <halInterrupt.h>
#include <atsamr21.h>
#include <qtTaskManager.h>


/******************************************************************************
                   Implementations section
******************************************************************************/
/******************************************************************************
 Polling the Sync. flag for register access
 Parameters:
   none
 Returns:
   none
 *****************************************************************************/
INLINE void TimerSync(void)
{
  while (TC5_16_STATUS_s.syncbusy);
}


/******************************************************************
time counter interrupt handler
 Parameters:
   none
 Returns:
   none
******************************************************************/
void timer5Handler(void)
{
  if (TC5_16_INTFLAG_s.mc0 & TC5_16_INTENSET_s.mc0)
  {
    TC5_16_INTFLAG_s.mc0 = 1;
    TimerSync();
    Timer_overflow_callback();
  }
}

/******************************************************************
configure and enable timer counter channel
 Parameters:
   none
 Returns:
   none
******************************************************************/
void StartAppClock(void)
{
  PM_APBCMASK_s.tc5 = 1;

  GCLK_CLKCTRL_s.id = 0x1C;  // enabling clock for TC3
  GCLK_CLKCTRL_s.gen = 3;
  GCLK_CLKCTRL_s.clken = 1;

  TC5_16_CTRLA_s.mode = 0x00;  //16 bit mode
  TimerSync();
  TC5_16_CTRLA_s.wavegen = 1;  // match frequency
  TimerSync();
  TC5_16_CTRLA_s.prescaler = 3;  // Prescaler DIV2
  TimerSync();
  TC5_16_CTRLA_s.prescsync = 0x01; // PRESC
  TimerSync();
  TC5_16_CTRLBCLR_s.oneshot = 1; // clearing one shot mode
  TimerSync();
  TC5_16_CTRLBCLR_s.dir = 1;
  TimerSync();

  TC5_16_COUNT = (uint16_t)0;
  TimerSync();
  TC5_16_CC0 = 0x2710;//(uint16_t)TOP_TIMER_COUNTER_VALUE_5;  // 30000
  TimerSync();

  TC5_16_CTRLA_s.enable = 1; //after configuration enable the timer
  TimerSync();

  TC5_16_INTENSET_s.mc0 = 1; // enabling interrupt MC0
  TimerSync();

  NVIC_EnableIRQ(TC5_IRQn);
}

/******************************************************************
disable timer
 Parameters:
   none
 Returns:
   none
******************************************************************/
void StopAppClock(void)
{
  /* Disable the clock */
  TC5_16_CTRLA_s.enable = 0;
  TimerSync();
}
#endif

// eof halAppClock.c
