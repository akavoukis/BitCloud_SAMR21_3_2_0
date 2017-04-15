/**************************************************************************//**
  \file  halWdt.c

  \brief Implementation of WDT interrupt handler.

  \author
      Atmel Corporation: http://www.atmel.com \n
      Support email: avr@atmel.com

    Copyright (c) 2008-2012, Atmel Corporation. All rights reserved.
    Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    07/04/14 karthik.p_u - Created
 ******************************************************************************/
/******************************************************************************
 *   WARNING: CHANGING THIS FILE MAY AFFECT CORE FUNCTIONALITY OF THE STACK.  *
 *   EXPERT USERS SHOULD PROCEED WITH CAUTION.                                *
 ******************************************************************************/
#if defined(HAL_USE_WDT)
/******************************************************************************
                   Includes section
******************************************************************************/
#include <wdtCtrl.h>
#include <atomic.h>
#include <halDbg.h>
#include <halDiagnostic.h>
#include <core_cm0plus.h>

/******************************************************************************
                   Static variables section
******************************************************************************/
#define WDT_TC_COUNT (F_CPU/1024ul)

/******************************************************************************
                   Static variables section
******************************************************************************/
static uint8_t wdt_count = 0;
static uint8_t wdt_tc_interval = 0;
 
/******************************************************************************
                   Global variables section
******************************************************************************/
void (*halWdtCallback)(void) = NULL;
void wdtTimerHandler(void);
void wdtTCHandler(void);

/*******************************************************************************
Registers WDT fired callback.
Parameters:
  wdtCallback - callback.
Returns:
  none.
*******************************************************************************/
void HAL_RegisterWdtCallback(void (*wdtCallback)(void))
{
  halWdtCallback = wdtCallback;
}

/*******************************************************************************
Starts Calculating WDT TC Compare Match Interval
Also sets the wdt_tc_interval
Parameters:
  interval - interval.
Returns:
  rt_value - Compare Match value.
*******************************************************************************/
uint16_t halCalcWdtTimerVal(HAL_WdtInterval_t interval)
{
  uint16_t rt_value;
  // The Formula is ((2^((interval-1)+3))/(2^10))
  uint32_t comp = ((1<<((interval-1)+3))>>10);
  if (comp)
  {
    wdt_tc_interval = comp;
    rt_value =  WDT_TC_COUNT;
  }
  else
  {
    wdt_tc_interval = 1;
    // The Formula is (WDT_TC_COUNT/((2*(10 - ((interval - 1)+3)))))
    rt_value = (WDT_TC_COUNT>>(10-((interval-1)+3)));
  }
  return rt_value;
}

/*******************************************************************//**
\brief Resets the WDT TC Counter
***********************************************************************/
void wdtTCReset(void)
{
  if (halWdtCallback)
  {
    wdtTCSync();
    TC5_16_COUNT = (uint16_t)0;
  }
}

/*******************************************************************//**
\brief Stops the WDT TC Counter
***********************************************************************/
void wdtTCStop(void)
{
  if (halWdtCallback)
  {
    wdtTCSync();
    TC5_16_CTRLA_s.enable = 0; // stop wdt timer
  }
}

/*******************************************************************//**
\brief Enables the WDT TC Counter
***********************************************************************/
void wdtTCEnable(void)
{
  if (halWdtCallback)
  {
    wdtTCSync();
    TC5_16_CTRLA_s.enable = 1; // enable wdt timer
  }
}

/*******************************************************************************
Starts WDT TC timer interval.
Parameters:
  interval - interval.
Returns:
  none.
*******************************************************************************/
void wdtTCStart(HAL_WdtInterval_t interval)
{
  PM_APBCMASK_s.tc5 = 1;

  GCLK_CLKCTRL_s.id = 0x1C;  // enabling clock for TC5
  GCLK_CLKCTRL_s.gen = 0;    // generic clock generator 0
  GCLK_CLKCTRL_s.clken = 1;
  
  wdtTCSync();
  TC5_16_CTRLA = TC5_16_CTRLA_MODE(0) | TC5_16_CTRLA_WAVEGEN(1) \
                 | TC5_16_CTRLA_PRESCALER(7) ;

  wdtTCSync();
  TC5_16_COUNT = 0;
  wdtTCSync();
  TC5_16_CC0 = halCalcWdtTimerVal(interval);

  wdtTCSync();
  TC5_16_CTRLBCLR = TC5_16_CTRLBCLR_ONESHOT | TC5_16_CTRLBCLR_DIR;

  wdtTCSync();
  TC5_16_INTENSET = TC5_16_INTENSET_MC0; // enabling interrupt MC0

  NVIC_EnableIRQ(TC5_IRQn);
}

/*******************************************************************************
Starts WDT with interval.
Parameters:
  interval - interval.
Returns:
  none.
*******************************************************************************/
void HAL_StartWdt(HAL_WdtInterval_t interval)
{
  GCLK_CLKCTRL_s.id = 0x03; // wdt clock
  GCLK_CLKCTRL_s.gen = 4; // Generic clock generator 4
  GCLK_CLKCTRL_s.clken = 1;

  ATOMIC_SECTION_ENTER
  BEGIN_MEASURE
  while(WDT_STATUS & WDT_STATUS_SYNCBUSY);
  WDT_CTRL_s.enable = 0; // Disabling watchdog
  WDT_CTRL_s.wen = 0; // disabling window mode
  WDT_CTRL_s.alwayson = 0; // disabling alwayson mode

  WDT_INTENCLR_s.ew = 1;
  if (halWdtCallback)
  {
    WDT_INTENSET_s.ew = 1;
    WDT_EWCTRL_s.ewoffset = interval;
    NVIC_EnableIRQ(WDT_IRQn);
    wdtTCStart(interval);
  }
  else
  {
    WDT_CONFIG_s.per = interval;
  }
  while(WDT_STATUS & WDT_STATUS_SYNCBUSY);
  WDT_CTRL_s.enable = 1; // Enabling watchdog
  wdtTCEnable(); // enabling wdt TC timer
  END_MEASURE(HALATOM_WDT_START_MEASURE_CODE)
  ATOMIC_SECTION_LEAVE

}

/*******************************************************************//**
\brief Restart the Watch Dog timer

Note Restart the watchdog timer.
***********************************************************************/
void halRestartWdt(void)
{
  while(WDT_STATUS & WDT_STATUS_SYNCBUSY);
  WDT_CLEAR_s.clear = 0xA5;
  wdtTCReset();
}

/*******************************************************************//**
\brief Resets the WDT Counter
************************************************************************/
void wdt_reset(void)
{
  if(!(WDT_STATUS & WDT_STATUS_SYNCBUSY))
  {
    WDT_CLEAR_s.clear = 0xA5;
    wdtTCReset();
    wdt_count = 0;
  }
  else if(wdt_count >= wdt_tc_interval)
  {
    while(WDT_STATUS & WDT_STATUS_SYNCBUSY);
    WDT_CLEAR_s.clear = 0xA5;
    wdt_count = 0;
    wdtTCReset();
  }
}

/*******************************************************************//**
\brief Stops the Watch Dog timer

Note that function is empty for AT91SAM7X256. WDT for AT91SAM7X256 is
impossible to stop.
***********************************************************************/
void HAL_StopWdt(void)
{
  while(WDT_STATUS & WDT_STATUS_SYNCBUSY);
  WDT_CTRL_s.enable = 0;
  wdtTCStop();
}

/*******************************************************************************
Interrupt handler for WDT TC Handler
*******************************************************************************/
void wdtTCHandler(void)
{
  if (TC5_16_INTFLAG_s.mc0 & TC5_16_INTENSET_s.mc0)
  {
    TC5_16_INTFLAG_s.mc0 = 1;
    wdt_count++;
  }
}

/*******************************************************************************
Interrupt handler for WDT Handler
*******************************************************************************/
void wdtTimerHandler(void)
{
  while(WDT_STATUS & WDT_STATUS_SYNCBUSY);
  WDT_CTRL_s.enable = 0;

  if (halWdtCallback)
    halWdtCallback();

  WDT_INTENCLR_s.ew = 0;
  WDT_CONFIG_s.per = 0;
  WDT_CTRL_s.enable = 1;
  for (;;);
}

#endif // defined(HAL_USE_WDT)

//eof halWdt.c
