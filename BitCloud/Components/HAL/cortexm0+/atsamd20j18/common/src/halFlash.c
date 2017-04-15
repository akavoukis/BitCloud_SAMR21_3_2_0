/**************************************************************************//**
  \file  halFlash.c

  \brief Implementation of flash access hardware-dependent module.

  \author
      Atmel Corporation: http://www.atmel.com \n
      Support email: avr@atmel.com

    Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
    Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:
   17/10/13 Agasthian - Created
  Last change:
    $Id: halFlash.c 25824 2013-12-10 08:44:12Z mahendran.p $
 ******************************************************************************/
/******************************************************************************
 *   WARNING: CHANGING THIS FILE MAY AFFECT CORE FUNCTIONALITY OF THE STACK.  *
 *   EXPERT USERS SHOULD PROCEED WITH CAUTION.                                *
 ******************************************************************************/
#if defined(HAL_USE_FLASH_ACCESS)

/******************************************************************************
                   Includes section
******************************************************************************/
#include <sysTypes.h>
#include <halFlash.h>

/******************************************************************************
                   Define(s) section
******************************************************************************/
#define FLASH_READY() (NVMCTRL_INTFLAG_s.ready)

/******************************************************************************
                   Implementations section
******************************************************************************/

/**************************************************************************//**
  \brief Initializes the flash.
  \param[in] None
******************************************************************************/
void halInitFlash(void)
{
  /* Can configure user row(NVMCTRL_USER) for boot loader size & EEPROM size
  enable nvmcontrol in AHB */
  PM_AHBMASK_s.nvmctrl = 1;
  /* enable nvmcontrol in APBB */
  PM_APBBMASK_s.nvmctrl = 1;
  /* enable manual write */
  NVMCTRL_CTRLB_s.manw = 1;
  /* configure power reduction mode - WAKEUPINSTANT */
  NVMCTRL_CTRLB_s.sleepprm = 0x01;
  /* Unlock all the regions */
  NVMCTRL_LOCK = 0xFFFF;
}

/**************************************************************************//**
  \brief Executes the specified command.
  \param[in] cmd - flash command
******************************************************************************/
void halExecuteCommand(flash_cmd_t cmd)
{
  while (!FLASH_READY()); 
  NVMCTRL_CTRLA = NVMCTRL_CTRLA_CMDEX(CMD_KEY)| NVMCTRL_CTRLA_CMD(cmd);
}

#endif  // defined(HAL_USE_FLASH_ACCESS)
