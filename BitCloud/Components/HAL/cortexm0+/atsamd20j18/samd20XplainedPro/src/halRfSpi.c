/**************************************************************************//**
\file  halSpi.c

\brief SPI interface routine.

\author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

\internal
  History:
    23/09/13 Viswanadham.Kotla - Created
*******************************************************************************/
/******************************************************************************
 *   WARNING: CHANGING THIS FILE MAY AFFECT CORE FUNCTIONALITY OF THE STACK.  *
 *   EXPERT USERS SHOULD PROCEED WITH CAUTION.                                *
 ******************************************************************************/

/******************************************************************************
                   Includes section
******************************************************************************/
#include <halRfSpi.h>
#include <halRfPio.h>
#include <halAppClock.h>
#include <halTaskManager.h>

/******************************************************************************
                   Define(s) section
******************************************************************************/


/******************************************************************************
                   Implementations section
******************************************************************************/
/******************************************************************************
  Performs hardware initialization of SPI0 interface.
******************************************************************************/
void HAL_InitRfSpi(void)
{
  /* Configure PIOs for SPI */
  GPIO_RF_SLP_TR_make_out();
  GPIO_RF_SLP_TR_clr();
  GPIO_RF_RST_make_out();
  GPIO_RF_IRQ_make_in();
  GPIO_RF_CS_make_out();
  GPIO_RF_MISO_make_in();
  GPIO_RF_MOSI_make_out();
  GPIO_RF_SCK_make_out();

  /* pin configurations */
  PORTA_PINCFG18 |= PORTA_PINCFG18_PMUXEN; //MOSI
  PORTA_PINCFG16 |= PORTA_PINCFG16_PMUXEN; //MISO
  PORTA_PINCFG19 |= PORTA_PINCFG19_PMUXEN; //SCK
  PORTB_PINCFG14 |= PORTB_PINCFG14_PMUXEN; //IRQ

  /* Configure SPI in peripheral multiplexing */
  PORTA_PMUX8 = PORTA_PMUX8_PMUXE(2);//peripheral function C
  PORTA_PMUX9 = PORTA_PMUX9_PMUXE(2) | PORTA_PMUX9_PMUXO(2);

  /* Initialization spi. Reset and disable. */
  SC1_SPI_CTRLA &= ~SC1_SPI_CTRLA_ENABLE;

  /* Enable the clock of SPI */
  PM_APBCMASK |= PM_APBCMASK_SERCOM1;

  /* Configure the generic clk settings */
  GCLK_CLKCTRL |=  GCLK_CLKCTRL_CLKEN | GCLK_CLKCTRL_ID(14) | GCLK_CLKCTRL_GEN(GCLK_GENERATOR_0);

  SC1_SPI_CTRLB  =/*|= SPI_CHARACTER_SIZE_8BIT |*/ SC1_SPI_CTRLB_RXEN;
  while(halSpiSyncing());

  /* setup spi mode master, first peripheral active */
  SC1_SPI_CTRLA |=  SC1_SPI_CTRLA_MODE(3) | SC1_SPI_CTRLA_DOPO | SC1_SPI_CTRLA_ENABLE;
  while(halSpiSyncing());
}

/******************************************************************************
  Writes/reads byte to/from SPI.
  parameters: value - byte to write.
  Returns:    the data which was read.
******************************************************************************/
uint32_t HAL_WriteByteRfSpi(uint8_t value)
{
  return HAL_WriteByteInlineRfSpi(value);
}

/******************************************************************************
  Deselects a slave device.
******************************************************************************/
void HAL_DeselectRfSpi(void)
{
  GPIO_RF_CS_set();
}

/******************************************************************************
  Selects a slave device.
******************************************************************************/
void HAL_SelectRfSpi(void)
{
  GPIO_RF_CS_clr();
}
// eof halRfSpi.c
