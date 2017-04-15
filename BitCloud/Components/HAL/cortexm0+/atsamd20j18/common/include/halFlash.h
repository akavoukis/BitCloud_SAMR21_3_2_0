/*****************************************************************************//**
\file  halFlash.h

\brief  Declarations of flash access module.

\author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2012, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

\internal
  History:
    17/10/13 Agasthian - Created
  Last change:
    $Id: halFlash.h 25824 2013-12-10 08:44:12Z mahendran.p $
**********************************************************************************/
/******************************************************************************
 *   WARNING: CHANGING THIS FILE MAY AFFECT CORE FUNCTIONALITY OF THE STACK.  *
 *   EXPERT USERS SHOULD PROCEED WITH CAUTION.                                *
 ******************************************************************************/
#ifndef _HALFLASH_H
#define _HALFLASH_H

/******************************************************************************
                   Includes section
******************************************************************************/
#include <flash.h>

/******************************************************************************
                   Define(s) section
******************************************************************************/
#define CMD_KEY                       0xA5
#define PAGE_SIZE                     64
#define NO_OF_PAGES_PER_ROW           4
#define NO_OF_HALF_WORDS_PER_PAGE     32
#define ROW_SIZE                      (4 * PAGE_SIZE)
#define ROW_SIZE_IN_HALF_WORDS        (ROW_SIZE / 2)
#define FLASH_MAIN_ADDRESS_SPACE      (0x00)

/******************************************************************************
                   Types definition section
******************************************************************************/

typedef enum flash_cmd_tag {
  ERASE_ROW = 0x02,
  WRITE_PAGE = 0x04,
  ERASE_AUXILARYROW = 0x05,
  WRITE_AUXILARYPAGE = 0x06,
  LOCK_REGION = 0x40,
  UNLOCK_REGION = 0x41,
  SET_POWERREDUCTIONMODE = 0x42,
  CLEAR_POWERREDUCTIONMODE = 0x43,
  PAGE_BUFFERCLEAR = 0x44,
  SET_SECURITYBIT = 0x45,
  INVALID_ALLCACHE = 0x46
 } flash_cmd_t;

/******************************************************************************
                   Prototypes section
******************************************************************************/

/**************************************************************************//**
  \brief Initializes the flash.
  \param[in] None
******************************************************************************/
void halInitFlash(void);

/**************************************************************************//**
  \brief Executes the specified command.
  \param[in] cmd - flash command
******************************************************************************/
void halExecuteCommand(flash_cmd_t cmd);

#endif // _HALFLASH_H

//eof halFlash.h
