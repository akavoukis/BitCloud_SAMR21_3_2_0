/**************************************************************************//**
  \file  resetReason.c

  \brief Implementation of the reset reason interface.

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
#include <sysTypes.h>
#include <resetReason.h>
#include <halReset.h>

/******************************************************************************
                            Implementations section
 ******************************************************************************/
/**************************************************************************//**
\brief Returns the reset reason.

\return The reason of reset.
******************************************************************************/
HAL_ResetReason_t HAL_ReadResetReason(void)
{
  return (HAL_ResetReason_t)halReadResetReason();
}

/**************************************************************************//**
\brief  Software reset.
******************************************************************************/
void HAL_WarmReset(void)
{
  halSoftwareReset();
}

// eof resetReason.c
