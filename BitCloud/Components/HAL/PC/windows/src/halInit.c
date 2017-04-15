/**********************************************************************//**
\file  halInit.c

\brief HAL start up module.

\author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

\internal
  History:
    01/03/12 N. Fomin - Created
**************************************************************************/
/******************************************************************************
                   Includes section
******************************************************************************/
#include <halAppClock.h>
#include <halAtomic.h>

/******************************************************************************
                   Implementations section
******************************************************************************/\
/******************************************************************************
Performs start up HAL initialization.
******************************************************************************/
void HAL_Init(void)
{
  // start timer 0
  halInitCriticalSection();
  halStartAppClock();
}
// eof halInit.c
