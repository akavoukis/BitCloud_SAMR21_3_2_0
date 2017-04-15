/**************************************************************************//**
\file  halInit.c

\brief HAL start up module.

\author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

\internal
  History:
    07/04/14 karthik.p_u - Created
*******************************************************************************/
/******************************************************************************
 *   WARNING: CHANGING THIS FILE MAY AFFECT CORE FUNCTIONALITY OF THE STACK.  *
 *   EXPERT USERS SHOULD PROCEED WITH CAUTION.                                *
 ******************************************************************************/

/******************************************************************************
                   Includes section
******************************************************************************/
#include <halRfSpi.h>
#include <halAppClock.h>
#include <halSleepTimerClock.h>
#include <halFlash.h>


/******************************************************************************
                   Implementations section
******************************************************************************/
/******************************************************************************
Performs start up HAL initialization.
******************************************************************************/
void HAL_Init(void)
{
  // init spi
  HAL_InitRfSpi();
  // start timer 0
  halStartAppClock();

  halStartSleepTimerClock();
#if defined(HAL_USE_FLASH_ACCESS)
  // Init flash module
  halInitFlash();
#endif
}

// eof halInit.c
