/**************************************************************************//**
  \file  halWdt.c

  \brief Implementation of WDT interrupt handler.

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
                   Global variables section
******************************************************************************/
void (*halWdtCallback)(void) = NULL;
void wdtTimerHandler(void);

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
Starts WDT with interval.
Parameters:
  interval - interval.
Returns:
  none.
*******************************************************************************/
void HAL_StartWdt(HAL_WdtInterval_t interval)
{
 
  GCLK_CLKCTRL_s.id = 0x01; // wdt clock
  GCLK_CLKCTRL_s.gen = 0x01; // Generic clock generator 1
  GCLK_CLKCTRL_s.clken = 1;

  ATOMIC_SECTION_ENTER
  BEGIN_MEASURE
  WDT_CTRL_s.enable = 0; // Disabling watchdog
  WDT_CTRL_s.wen = 0; // disabling window mode
  WDT_CTRL_s.alwayson = 0; // disabling alwayson mode
 
  WDT_INTENCLR_s.ew = 1;
  if (halWdtCallback)
  {
    WDT_INTENSET_s.ew = 1;
    WDT_EWCTRL_s.ewoffset = interval;
    NVIC_EnableIRQ(WDT_IRQn);
  }
  else
  {
    WDT_CONFIG_s.per = interval;  
  }
  WDT_CTRL_s.enable = 1; // Enabling watchdog
  END_MEASURE(HALATOM_WDT_START_MEASURE_CODE)
  ATOMIC_SECTION_LEAVE

}

/*******************************************************************//**
\brief Restart the Watch Dog timer

Note Restart the watchdog timer.
***********************************************************************/
void halRestartWdt(void)
{
  WDT_CLEAR_s.clear = 0xA5;
}

/*******************************************************************//**
\brief Stops the Watch Dog timer

Note that function is empty for AT91SAM7X256. WDT for AT91SAM7X256 is
impossible to stop.
***********************************************************************/
void HAL_StopWdt(void)
{
  WDT_CTRL_s.enable = 0;
}

/*******************************************************************************
Interrupt handler.
*******************************************************************************/
void wdtTimerHandler(void)
{
  if (NULL != halWdtCallback)
    halWdtCallback();

  WDT_CTRL_s.enable = 0;
  WDT_INTENCLR_s.ew = 0;
  WDT_CONFIG_s.per = 0;
  WDT_CTRL_s.enable = 1;
  for (;;);
}
#endif // defined(HAL_USE_WDT)

//eof halWdt.c
