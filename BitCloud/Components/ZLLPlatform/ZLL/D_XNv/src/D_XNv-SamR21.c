/*********************************************************************************************//**
\file

\brief D_XNv Drivers Implementation

This file implements a few basic 'static inline' functions that are intended to be used in a
certain way. This is as follows:

For any Flash command, the flash chip must first be selected using SelectFlash().
Each command ends with de-selection of the flash chip by calling DeselectFlash().
Within a command, a byte can be transferred over SPI to the flash chip using this sequence:
 - SpiTxByte(uint8_t b);  // initiates the transfer of a byte over SPI
 - SpiTxWaitReady();    // waits until the transfer is ready
 - SpiRxByte();         // Need to do a dummy read after sending a byte over SPI
When the flash chip sends back a byte (i.e. a response), a dummy byte is sent and the response is read:
 - SpiTxByte(0x00u);    // initiates the transfer of a dummy byte over SPI
 - SpiTxWaitReady();    // waits until the transfer is ready
 - byte = SpiRxByte();  // reads the byte
To optimize speed, any calculations should be done between SpiTxByte() and SpiTxWaitReady(), because
the SpiTxWaitReady() will be ready about 2 microseconds after the SpiTxByte().

\author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

\internal

$Id: D_XNv-SamR21.c 24615 2013-02-27 05:14:24Z mahendranp $

***************************************************************************************************/

/***************************************************************************************************
* LOCAL INCLUDE FILES
***************************************************************************************************/

#include "D_XNv_Bindings.h"
#include "D_XNv_Init.h"
#include "D_XNv.h"

#include "N_Types.h"
#include <atsamr21.h>
#include <atomic.h>
#include <spi.h>


/***************************************************************************************************
* EXTERNAL INCLUDE FILES
***************************************************************************************************/

#if defined(ENABLE_NV_USAGE_SIMULATION)
#include "N_Log.h"
#endif

/***************************************************************************************************
* LOCAL MACROS AND CONSTANTS
***************************************************************************************************/

#define COMPID "D_XNv"

#define D_XNV_PAGE_PROGRAM_CMD  0x02u
#define D_XNV_READ_CMD          0x03u
#define D_XNV_READ_STATUS_CMD   0x05u
#define D_XNV_WRITE_ENABLE_CMD  0x06u
#define D_XNV_SECTOR_ERASE_CMD  0xD8u

#define D_XNV_STATUS_WIP        0x01u

#define EXTFLASH_SPI_CS         (1 << 14)
#define EXTFLASH_SPI_SCK        (1 << 9)
#define EXTFLASH_SPI_MOSI       (1 << 8)
#define EXTFLASH_SPI_MISO       (1 << 15)

/***************************************************************************************************
* LOCAL FUNCTIONS
***************************************************************************************************/

static inline void SelectFlash(void)
{
    // Make CSn low
    PORTA_OUTCLR = EXTFLASH_SPI_CS;
}

static void DeselectFlash(void)
{
    // Make CSn high
    PORTA_OUTSET = EXTFLASH_SPI_CS;
}

static inline void SpiTxByte(uint8_t value)
{
    SC2_SPI_DATA = value;
}

static inline void SpiTxWaitReady(void)
{
    // Wait for transmission complete
    while ( !(SC2_SPI_INTFLAG & SC2_SPI_INTFLAG_RXC) )
    {
        // no action
    }
}

/** Receive a byte that was transferred during a transmit */
static inline uint8_t SpiRxByte(void)
{
    return SC2_SPI_DATA;
}

static inline void SpiTxByteAndWait(uint8_t value)
{
    ATOMIC_SECTION_ENTER
    SpiTxByte(value);
    SpiTxWaitReady();
    ATOMIC_SECTION_LEAVE
}

static inline void SpiTxByteWaitAndDummyReadByte(uint8_t value)
{
    SpiTxByteAndWait(value);
    SpiRxByte();
}

/** Wait unit a previous write or sector erase has finished. This can take really long! */
static void WaitUntilWriteFinished(void)
{
    SelectFlash();
    SpiTxByteWaitAndDummyReadByte(D_XNV_READ_STATUS_CMD);
    do
    {
        SpiTxByteAndWait(0u);
    }
    while ( SpiRxByte() & D_XNV_STATUS_WIP );
    DeselectFlash();
}

static inline uint8_t ReadSingleByte(void)
{
    SpiTxByteAndWait(0u);
    return SpiRxByte();
}

/***************************************************************************************************
* EXPORTED FUNCTIONS
***************************************************************************************************/

void D_XNv_Init(void)
{
    /* Configure PIOs for SPI */
    PORTA_DIRSET = EXTFLASH_SPI_CS;
    PORTA_DIRCLR = EXTFLASH_SPI_SCK | EXTFLASH_SPI_MISO | EXTFLASH_SPI_MOSI;

    /* Pin configurations */
    PORTA_PINCFG15 |= PORTA_PINCFG15_PMUXEN; //MISO  A15
    PORTA_PINCFG8 |= PORTA_PINCFG8_PMUXEN; //MOSI  A8
    PORTA_PINCFG9 |= PORTA_PINCFG9_PMUXEN; //SCK   A9

    /* Configure SPI in peripheral multiplexing */
    PORTA_PMUX7 |= PORTA_PMUX7_PMUXO(2);
    PORTA_PMUX4 = PORTA_PMUX4_PMUXE(3) | PORTA_PMUX4_PMUXO(3);

    /* Enable the clock of SPI */
    PM_APBCMASK |= PM_APBCMASK_SERCOM2;

    /* Configure the generic clk settings */
    GCLK_CLKCTRL_s.id = 0x16;  // enabling clock for SERCOM2
    GCLK_CLKCTRL_s.gen = 0;
    GCLK_CLKCTRL_s.clken = 1;

    /* Reset */
    SC2_SPI_CTRLA = SC2_SPI_CTRLA_SWRST;
    while((SC2_SPI_SYNCBUSY & SC2_SPI_SYNCBUSY_SWRST));

    /* Receiver Enable*/
    SC2_SPI_CTRLB  = SC2_SPI_CTRLB_RXEN;
    while(SC2_SPI_SYNCBUSY & SC2_SPI_SYNCBUSY_CTRLB);

    /* Baud Rate Configuration */
    SC2_SPI_BAUD = SPI_CLOCK_RATE_2000;

    /* setup spi mode master, pad & enable it */
    SC2_SPI_CTRLA |=  SC2_SPI_CTRLA_MODE(3) | SC2_SPI_CTRLA_DIPO(3)| SC2_SPI_CTRLA_DOPO(0) | SC2_SPI_CTRLA_ENABLE;
    while(SC2_SPI_SYNCBUSY & SC2_SPI_SYNCBUSY_ENABLE);
}

void D_XNv_Read_Impl(uint8_t sector, uint16_t offset, uint8_t *pBuffer, D_XNv_Size_t numberOfBytes)
{
    WaitUntilWriteFinished();

    SelectFlash();
    SpiTxByteWaitAndDummyReadByte(D_XNV_READ_CMD);
    SpiTxByteWaitAndDummyReadByte(sector);
    SpiTxByteWaitAndDummyReadByte((uint8_t)(offset >> 8));
    SpiTxByteWaitAndDummyReadByte((uint8_t)offset);

    while ( numberOfBytes != 0u )
    {
        *pBuffer = ReadSingleByte();
        pBuffer++;
        numberOfBytes--;
    }

    DeselectFlash();
}

void D_XNv_Write_Impl(uint8_t sector, uint16_t offset, const uint8_t *pBuffer, D_XNv_Size_t numberOfBytes)
{
    while (numberOfBytes != 0u)
    {
        WaitUntilWriteFinished();
        SelectFlash();
        SpiTxByteWaitAndDummyReadByte(D_XNV_WRITE_ENABLE_CMD);
        DeselectFlash();

        SelectFlash();
        SpiTxByteWaitAndDummyReadByte(D_XNV_PAGE_PROGRAM_CMD);
        SpiTxByteWaitAndDummyReadByte(sector);
        SpiTxByteWaitAndDummyReadByte((uint8_t)(offset >> 8));
        SpiTxByteWaitAndDummyReadByte((uint8_t)offset);
        do
        {
            SpiTxByteWaitAndDummyReadByte(*pBuffer);
            pBuffer++;
            numberOfBytes--;
            offset++;
        }
        while ( ( numberOfBytes != 0u ) && ( (offset & 0x00FFu) != 0x0000u ) );
        DeselectFlash();
    }
}

void D_XNv_EraseSector_Impl(uint8_t sector)
{
#if defined(ENABLE_NV_USAGE_SIMULATION)
    N_LOG_ALWAYS(("EraseSector,%hu", sector));
#endif
    WaitUntilWriteFinished();
    SelectFlash();
    SpiTxByteWaitAndDummyReadByte(D_XNV_WRITE_ENABLE_CMD);
    DeselectFlash();

    SelectFlash();
    SpiTxByteWaitAndDummyReadByte(D_XNV_SECTOR_ERASE_CMD);
    SpiTxByteWaitAndDummyReadByte(sector);
    SpiTxByteWaitAndDummyReadByte(0x00u);
    SpiTxByteWaitAndDummyReadByte(0x00u);
    DeselectFlash();
}

bool D_XNv_IsEmpty_Impl(uint8_t sector, uint16_t offset, D_XNv_Size_t numberOfBytes)
{
    WaitUntilWriteFinished();

    SelectFlash();
    SpiTxByteWaitAndDummyReadByte(D_XNV_READ_CMD);
    SpiTxByteWaitAndDummyReadByte(sector);
    SpiTxByteWaitAndDummyReadByte((uint8_t)(offset >> 8));
    SpiTxByteWaitAndDummyReadByte((uint8_t)offset);

    uint8_t andedContent = 0xFFu;
    do
    {
        andedContent &= ReadSingleByte();
        numberOfBytes--; // will wrap from 0 to 0xFFFF when numberOfBytes equals 0 on entry
    }
    while ((andedContent == 0xFFu) && (numberOfBytes != 0u));

    DeselectFlash();
   return (andedContent == 0xFFu);
}

bool D_XNv_IsEqual_Impl(uint8_t sector, uint16_t offset, uint8_t *pBuffer, D_XNv_Size_t numberOfBytes)
{
    bool isEqual = TRUE;

    WaitUntilWriteFinished();

    SelectFlash();
    SpiTxByteWaitAndDummyReadByte(D_XNV_READ_CMD);
    SpiTxByteWaitAndDummyReadByte(sector);
    SpiTxByteWaitAndDummyReadByte((uint8_t)(offset >> 8));
    SpiTxByteWaitAndDummyReadByte((uint8_t)offset);

    while ((isEqual) && (numberOfBytes != 0u))
    {
        isEqual = (*pBuffer == ReadSingleByte());
        pBuffer++;

        numberOfBytes--;
    }

    DeselectFlash();

    return isEqual;
}
