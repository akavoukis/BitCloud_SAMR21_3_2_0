/**************************************************************************//**
\file   atomic.c

\brief  Implementation of atomic sections.

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

/******************************************************************************
                   Includes section
******************************************************************************/
#include <atsamd20.h>
#include <core_cm0plus.h>
#include <atomic.h>
#include <sysTypes.h>

/******************************************************************************
                   Implementations section
******************************************************************************/
/******************************************************************************
 Disables global interrupt. Enter atomic section.
******************************************************************************/
void halStartAtomic(atomic_t volatile *pAtomic)
{
  *pAtomic = __get_PRIMASK();
  __disable_irq();
}

/******************************************************************************
 Exit atomic section
******************************************************************************/
void halEndAtomic(atomic_t volatile *pAtomic)
{
  __set_PRIMASK(*pAtomic);
}

// eof atomic.c
