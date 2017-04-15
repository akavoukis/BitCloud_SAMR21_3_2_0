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
    07/04/14 karthik.p_u - Created
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
#if defined(HAL_USE_EE_READY)
#if defined(HAL_USE_EEPROM_EMULATION)
#include <halEeprom.h>
#endif
#endif
#include <atomic.h>
#include <halDbg.h>

/******************************************************************************
                   Define(s) section
******************************************************************************/
#define FLASH_READY() (NVMCTRL_INTFLAG_s.ready)

/******************************************************************************
                   Local variables section
******************************************************************************/
static uint16_t pageBufferToFill[ROW_SIZE_IN_HALF_WORDS];

/******************************************************************************
                   Prototypes section
******************************************************************************/
static void halExecuteCommand(flash_cmd_t cmd);

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

#if defined(HAL_USE_EE_READY)
#if defined(HAL_USE_EEPROM_EMULATION)
  halInitEepromEmulator();
#endif
#endif
}

/**************************************************************************//**
  \brief Executes the specified command.
  \param[in] cmd - flash command
******************************************************************************/
static void halExecuteCommand(flash_cmd_t cmd)
{
  while (!FLASH_READY());
  NVMCTRL_CTRLA = NVMCTRL_CTRLA_CMDEX(CMD_KEY)| NVMCTRL_CTRLA_CMD(cmd);
}

/**************************************************************************//**
  \brief Writes data to the page buffer.
  \param[in] startOffset - start position for writing within the page
  \param[in] length - data to write length in bytes
  \param[in] data - pointer to data to write
******************************************************************************/
void halFillFlashPageBuffer(uint32_t startOffset, uint16_t length, uint8_t *data)
{
  // Page size is 64 Bytes so that Row size becomes 4*64 = 256 Bytes
  // max. value of length may be 256 Bytes
  uint16_t unalignedWord;
  uint16_t alignedWord;
  uint8_t wordPos;

  if (startOffset % ROW_SIZE + length > ROW_SIZE)
  {
    // leaking into next row & abort the file operation
    sysAssert(false, FLASH_PAGEFILLBUFFERINCORRECTOFFSET_0);
    return;
  }

  // Initialize the page buffer
  for (uint16_t index = 0; index < ROW_SIZE_IN_HALF_WORDS; index++)
    pageBufferToFill[index] = 0xFFFF;
  // Check, if first byte of current data is unaligned
  if (startOffset % 2)
  {
    /* Fill it as a MSB of a word */
    unalignedWord = 0x00FF | ((uint16_t)*data++ << 8);
    wordPos = (startOffset % ROW_SIZE - 1) / 2;
    pageBufferToFill[wordPos] = unalignedWord;
    startOffset++;
    length--;
  }

  // Handle if the last byte is not aligned
  if (length % 2)
  {
    unalignedWord = 0xFF00 | data[length - 1];
    wordPos = (startOffset % ROW_SIZE + length - 1) / 2 ;
    pageBufferToFill[wordPos] = unalignedWord;
    length--;
  }

  // Copy the remaining aligneed bytes to page buffer
  for (uint8_t index =0; index < length/2; index++)
  {
    wordPos = startOffset % ROW_SIZE / 2;
    alignedWord = *data++;
    alignedWord = alignedWord | (*data++ << 8);
    pageBufferToFill[wordPos] = alignedWord;
    startOffset += 2;
  }
}

/**************************************************************************//**
  \brief Erases specified flash page.
  \param[in] pageStartAddress - address within the target page
******************************************************************************/
void halEraseFlashPage(uint32_t pageStartAddress)
{
  if (pageStartAddress % 2)
    pageStartAddress--;
  /* Loading ADDR register */
  *(uint16_t *)(FLASH_MAIN_ADDRESS_SPACE + pageStartAddress) = 0xFFFF;
  halExecuteCommand(ERASE_ROW);
}

/**************************************************************************//**
  \brief Writes flash page buffer without erasing.
  \param[in] pageStartAddress - address within the target page
******************************************************************************/
void halWriteFlashPage(uint32_t pageStartAddress)
{
  /* PDS page is mapped to row. so finding out the starting of row */
  if (pageStartAddress % ROW_SIZE)
    pageStartAddress = pageStartAddress - (pageStartAddress % ROW_SIZE);

  for (uint8_t pageCnt = 0; pageCnt < NO_OF_PAGES_PER_ROW; pageCnt++)
  {
    for (uint8_t wordCnt = 0; wordCnt < NO_OF_HALF_WORDS_PER_PAGE; wordCnt++)
      *(uint16_t *)(FLASH_MAIN_ADDRESS_SPACE + pageStartAddress + wordCnt * 2) = pageBufferToFill[pageCnt * NO_OF_HALF_WORDS_PER_PAGE + wordCnt];

    halExecuteCommand(WRITE_PAGE);
    pageStartAddress += PAGE_SIZE;
  }
}

#if !defined(HAL_USE_EEPROM_EMULATION)
/**************************************************************************//**
  \brief Prepares single page for write, updates eeprom write request structure
  \param[in] eeprom - EEPROM write request structure
  \return prepared page number
******************************************************************************/
void halFlashWriteEepromPage(HAL_EepromParams_t *eeprom)
{
  uint32_t eepromAddr;
  uint16_t bytesToWrite;
  uint16_t pageNo;
  uint8_t pageBufferEeprom[ROW_SIZE];

  eepromAddr = FLASH_EEPROM_BASE_ADDRESS + eeprom->address;
  pageNo = eepromAddr / ROW_SIZE;

  bytesToWrite = ROW_SIZE - (eepromAddr % ROW_SIZE);
  memcpy_P(&pageBufferEeprom[0], (void *)(pageNo * ROW_SIZE), ROW_SIZE);

  if (eeprom->length < bytesToWrite)
    bytesToWrite = eeprom->length;

  memcpy(&pageBufferEeprom[eepromAddr % ROW_SIZE], eeprom->data, bytesToWrite);

  halEraseFlashPage(pageNo*ROW_SIZE);
  halFillFlashPageBuffer(pageNo*ROW_SIZE, ROW_SIZE, &pageBufferEeprom[0]);
  halWriteFlashPage(pageNo*ROW_SIZE);

  eeprom->address += bytesToWrite;
  eeprom->length -= bytesToWrite;
  eeprom->data += bytesToWrite;

}

#endif // defined(HAL_USE_EEPROM_EMULATION)
#endif  // defined(HAL_USE_FLASH_ACCESS)
