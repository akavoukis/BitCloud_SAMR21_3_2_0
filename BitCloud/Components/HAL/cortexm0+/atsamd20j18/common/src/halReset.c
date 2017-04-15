/*****************************************************************************
  \file  halReset.c

  \brief Implementation of the software reset

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:
    19/08/13 Agasthian.s - Created
******************************************************************************/

/*****************************************************************************
                              Includes section
******************************************************************************/
#include <sysTypes.h>
#include <atsamd20.h>
#include <atomic.h>
#include <halReset.h>
#include <halInterrupt.h>

/*****************************************************************************
                              Definitions section
******************************************************************************/

/******************************************************************************
                              Implementations section
******************************************************************************/
/**************************************************************************//**
 \brief Read the reset status register.
 \return Current value of the reset status register.
******************************************************************************/
HAL_ResetReason_t halReadResetReason(void)
{
  return (HAL_ResetReason_t)(PM_RCAUSE & (PM_RCAUSE_POR | PM_RCAUSE_BOD12 | PM_RCAUSE_BOD33 | \
                             PM_RCAUSE_EXT | PM_RCAUSE_WDT | PM_RCAUSE_SYST ));
}

/**************************************************************************//**
 \brief Reset core and peripherals.
******************************************************************************/
void halSoftwareReset(void)
{
  // software reset processor core and peripherals
  NVIC_SystemReset();
}

// eof halReset.c
