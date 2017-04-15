/**************************************************************************//**
  \file  halWdt.h

  \brief  Declarations of wdt hardware-dependent module.

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

#ifndef _HALWDT_H
#define _HALWDT_H

/******************************************************************************
                   Includes section
******************************************************************************/
#include <sysTypes.h>
#include <atsamd20.h>


/******************************************************************************
                   Define(s) section
******************************************************************************/
INLINE void wdt_reset(void)
{
  WDT_CLEAR_s.clear = 0xA5;
}

#endif /* _HALWDT_H */

//eof halWdt.h
