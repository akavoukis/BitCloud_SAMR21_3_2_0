/**************************************************************************//**
\file  halClkCtrl.h

\brief Declarations of clock control hardware-dependent module.

\author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

\internal
  History:
    07/04/14 karthik.p_u - Created
******************************************************************************/
/******************************************************************************
 *   WARNING: CHANGING THIS FILE MAY AFFECT CORE FUNCTIONALITY OF THE STACK.  *
 *   EXPERT USERS SHOULD PROCEED WITH CAUTION.                                *
 ******************************************************************************/

#ifndef _HALCLKCTRL_H
#define _HALCLKCTRL_H

/******************************************************************************
                   Includes section
******************************************************************************/
#include <atsamr21.h>
#include <inttypes.h>
#include <sysTypes.h>

/******************************************************************************
                   Define(s) section
******************************************************************************/
// CPU runs at a different freq compared to the peripheral freq
// We are fixing the peripheral freq to 8MHz and are changing the CPU freq alone
// CPU freq is defined by HAL_xMHz and Peripheral freq is defined by F_CPU
// Exception : For HAL_4MHz the Peripherals are also run at 4Mhz
#if defined(HAL_4MHz)
  #define F_CPU  4000000ul
  #define F_PERI 4000000ul
#elif defined(HAL_8MHz)
  #define F_CPU  8000000ul
  #define F_PERI 8000000ul
#elif defined(HAL_16MHz)
  #define F_CPU  16000000ul
  #define F_PERI  8000000ul
#elif defined(HAL_24MHz)
  #define F_CPU  24000000ul
  #define F_PERI  8000000ul
#elif defined(HAL_48MHz)
  #define F_CPU  48000000ul
  #define F_PERI  8000000ul
#endif

#define ALL_PERIPHERIAL_INTERRUPT_DISABLE  0xFFFFFFFF

/**
 * \brief Available start-up times for the XOSC32K
 *
 * Available external 32KHz oscillator start-up times, as a number of external
 * clock cycles.
 */
enum system_xosc32k_startup {
  /** Wait 0 clock cycles until the clock source is considered stable */
  SYSTEM_XOSC32K_STARTUP_0,
  /** Wait 32 clock cycles until the clock source is considered stable */
  SYSTEM_XOSC32K_STARTUP_32,
  /** Wait 2048 clock cycles until the clock source is considered stable */
  SYSTEM_XOSC32K_STARTUP_2048,
  /** Wait 4096 clock cycles until the clock source is considered stable */
  SYSTEM_XOSC32K_STARTUP_4096,
  /** Wait 16384 clock cycles until the clock source is considered stable */
  SYSTEM_XOSC32K_STARTUP_16384,
  /** Wait 32768 clock cycles until the clock source is considered stable */
  SYSTEM_XOSC32K_STARTUP_32768,
  /** Wait 65536 clock cycles until the clock source is considered stable */
  SYSTEM_XOSC32K_STARTUP_65536,
  /** Wait 131072 clock cycles until the clock source is considered stable */
  SYSTEM_XOSC32K_STARTUP_131072,
};

/******************************************************************************
                   Prototypes section
******************************************************************************/
/******************************************************************************
System clock.
Returns:
  system clock in Hz.
******************************************************************************/
uint32_t HAL_ReadFreq(void);

/**************************************************************************//**
\brief Initialize the 32KHz external RC oscillator.
******************************************************************************/
void halXOSC32KInit(void);

/******************************************************************************
 Polling the Sync. flag for register access
 Parameters:
   none
 Returns:
   none
 *****************************************************************************/
INLINE void halGclkSync(void)
{
  while (GCLK_STATUS & GCLK_STATUS_SYNCBUSY);
}

/******************************************************************************
 Polling the DFLL_RDY to check synchronization.
 Parameters:
   none
 Returns:
   none
 *****************************************************************************/
INLINE void halDfllReady(void)
{
  while (!(SYSCTRL_PCLKSR & SYSCTRL_PCLKSR_DFLLRDY));
}

/******************************************************************************
 Polling the DFLLLCKF to see if the DFLL fineLock has locked.
 Parameters:
   none
 Returns:
   none
 *****************************************************************************/
INLINE void halFineLock(void)
{
  while (!(SYSCTRL_PCLKSR & SYSCTRL_PCLKSR_DFLLLCKF));
}

/******************************************************************************
 Polling the DFLLLCKC to see if the DFLL coarseLock has locked.
 Parameters:
   none
 Returns:
   none
 *****************************************************************************/
INLINE void halCoarseLock(void)
{
  while (!(SYSCTRL_PCLKSR & SYSCTRL_PCLKSR_DFLLLCKC));
}

/******************************************************************************
 Polling the OSC8M to check if internal RC has set.
 Parameters:
   none
 Returns:
   none
 *****************************************************************************/
INLINE void halCheckIntRcReady(void)
{
  while( !(SYSCTRL_PCLKSR & SYSCTRL_PCLKSR_OSC8MRDY) );
}

/******************************************************************************
 Polling the XOSC32KRDY to check if XOSC32K has set.
 Parameters:
   none
 Returns:
   none
 *****************************************************************************/
INLINE void halCheckXOSC32KReady(void)
{
  /* Check the XOSC32K Clock source is ready to use */
  while(!((SYSCTRL_XOSC32K & SYSCTRL_PCLKSR_XOSC32KRDY) == \
                SYSCTRL_PCLKSR_XOSC32KRDY));
}

#endif /* _HALCLKCTRL_H */

// eof halClkCtrl.h
