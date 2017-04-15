/**************************************************************************//**
\file  halAssert.h

\brief Implementation of pc assert algorithm.

\author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

\internal
  History:
    0608/12 N. Fomin - Created
******************************************************************************/
#ifndef _HALASSERT_H
#define _HALASSERT_H

/******************************************************************************
                   Includes section
******************************************************************************/
#include <stdio.h>

/******************************************************************************
                   Inline static functions section
******************************************************************************/
INLINE void halAssert(uint8_t condition, uint16_t dbgCode)
{
  if (0 == condition)
  {
    fprintf(stderr, "Assert - 0x%4x\n", dbgCode);
//    while(1);
  }
}


#endif /* _HALASSERT_H */

// eof halAssert.h
