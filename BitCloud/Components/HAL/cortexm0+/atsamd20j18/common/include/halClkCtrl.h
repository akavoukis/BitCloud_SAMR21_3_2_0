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
    19/08/13 Agasthian.s - Created
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
#include <atsamd20.h>
#include <inttypes.h>

/******************************************************************************
                   Define(s) section
******************************************************************************/
// the main cpu clock
#if defined(HAL_4MHz)
  #define F_CPU 4000000
#elif defined(HAL_8MHz)
  #define F_CPU 8000000
#elif defined(HAL_12MHz)
  #define F_CPU 12000000
#elif defined(HAL_64MHz)
  #define F_CPU 64000000
#endif
#define ALL_PERIPHERIAL_INTERRUPT_DISABLE  0xFFFFFFFF

/******************************************************************************
                   Prototypes section
******************************************************************************/
/******************************************************************************
System clock.
Returns:
  system clock in Hz.
******************************************************************************/
uint32_t HAL_ReadFreq(void);

#endif /* _HALCLKCTRL_H */

// eof halClkCtrl.h
