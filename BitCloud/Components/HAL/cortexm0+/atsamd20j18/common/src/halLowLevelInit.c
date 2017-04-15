/**************************************************************************//**
\file  halLowLevelInit.c

\brief
   Implementation of the basic initialization module.

\author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

\internal
  History:
    19/08/13 Agasthian.s - Created
*******************************************************************************/
/******************************************************************************
                   Includes section
******************************************************************************/
#include <atsamd20.h>
#include <core_cm0plus.h>
#include <sysTypes.h>

/******************************************************************************
                   Define(s) section
******************************************************************************/

/******************************************************************************
                              Implementations section
******************************************************************************/
/**************************************************************************//**
\brief Run device from 8MHz RC clock
******************************************************************************/
void halSwitchToRcClock(void)
{
  SYSCTRL_OSC8M_s.presc = 0x0; // Prescaler - 1
  SYSCTRL_OSC8M_s.enable = 0x1; // Enablign the oscillator
  

  // Use generic clock generator 0(GCLKMAIN) - internal clock as input source
  // configure the division for clock generator 0

  GCLK_GENDIV_s.id = 0;
  GCLK_GENDIV_s.div = 0;
  
  // then configure internal clock as input source & division enabled
  GCLK_GENCTRL_s.id = 0;
  GCLK_GENCTRL_s.src = 0x06;  // OSC8M
  GCLK_GENCTRL_s.divsel = 0;  // no division so 8MHz clock
  
  GCLK_GENDIV_s.id = 1;
  GCLK_GENDIV_s.div = 12;  // divide by 8192
  
  // then configure internal clock as input source & division enabled
  GCLK_GENCTRL_s.id = 1;
  GCLK_GENCTRL_s.src = 0x06;  // OSC8M
  GCLK_GENCTRL_s.divsel = 1;  // division of 8MHz clock
  
}
/**************************************************************************//**
\brief Run device from active clock (intended at configuration)
******************************************************************************/
void halSwitchToActiveClock(void)
{
#if defined(RC_INTERNAL)
  
  GCLK_GENDIV_s.id = 0;
  GCLK_GENDIV_s.div = 0;
  
  // then configure internal clock as input source & division enabled
  GCLK_GENCTRL_s.id = 0;
  GCLK_GENCTRL_s.src = 0x06;  // OSC8M
  GCLK_GENCTRL_s.divsel = 0;
#else
  /* external clock */

#endif

}
/**************************************************************************//**
\brief Restore default setup value: enable Main On-Chip RC oscillator running on
8 MHz for Main Clock source.
******************************************************************************/
void halRestoreStartupClock(void)
{

  /* Clock system may be already setup by flash loaders or IAR startup script.
     Restore default settings: CPU is clocked from RC oscillator running on
     8 MHz as Main Clock source. */
  halSwitchToRcClock();
  /* Switch to active clock (RC or XTAL) and perform clock system initialization */
  halSwitchToActiveClock();
}

/**************************************************************************//**
\brief Initialization of the flash controller, the clock source systems and
the watchdog timer.
******************************************************************************/
void halLowLevelInit(void)
{
  halRestoreStartupClock();

#if !defined(HAL_USE_WDT)
  /* Disable watchdog timer */
  WDT_CTRL_s.enable = 0;  
#endif

  /* Enable interrupt */
  __enable_irq();
}
// eof halLowLevelInit.c
