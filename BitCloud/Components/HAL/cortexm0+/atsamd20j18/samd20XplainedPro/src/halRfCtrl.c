/**************************************************************************//**
\file   halRfCtrl.c

\brief  mac pin interface implementation.

\author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

\internal
  History:
    30/08/13 Viswanadham Kotla - Created.
    23/09/13 Viswanadham Kotla - Modified.    
******************************************************************************/
/******************************************************************************
 *   WARNING: CHANGING THIS FILE MAY AFFECT CORE FUNCTIONALITY OF THE STACK.  *
 *   EXPERT USERS SHOULD PROCEED WITH CAUTION.                                *
 ******************************************************************************/

/******************************************************************************
                        Includes section.
******************************************************************************/
#include <halAppClock.h>
#include <halRfSpi.h>
#include <halRfPio.h>
#include <halRfCtrl.h>
#include <halInterrupt.h>
#include <halMacIsr.h>
#include <halIrq.h>
#include <halRfPio.h>
/******************************************************************************
                   Define(s) section
******************************************************************************/
#define RF_REGISTER_READ_ACCESS_MODE      0x80
#define RF_REGISTER_TRX_STATUS_ADDRESS    0x01
#define RF_TRX_OFF_STATE                  0x08

/******************************************************************************
                   Prototypes section
******************************************************************************/
/**************************************************************************//**
\brief  MAC RF interrupt handler
******************************************************************************/
void phyDispatcheRfInterrupt(void);

#ifdef _HAL_RF_RX_TX_INDICATOR_
/**************************************************************************//**
\brief  Turn on pin 1 (DIG3) and pin 2 (DIG4) to indicate the transmit state of
the radio transceiver.
******************************************************************************/
void phyRxTxSwitcherOn(void);

#endif //_HAL_RF_RX_TX_INDICATOR_

#ifdef _HAL_ANT_DIVERSITY_
/**************************************************************************//**
\brief  Enable antenna diversity feature.
******************************************************************************/
void phyAntennaDiversityInit(void);

/**************************************************************************//**
\brief  Enable antenna diversity in the receive state of the radio transceiver.
******************************************************************************/
void phyRxAntennaDiversity(void);

/**************************************************************************//**
\brief  Enable antenna diversity in the transmit state of the radio transceiver.
******************************************************************************/
void phyTxAntennaDiversity(void);

#endif //_HAL_ANT_DIVERSITY_

/******************************************************************************
                    Implementations section
******************************************************************************/
/******************************************************************************
  Delay in us
******************************************************************************/
void HAL_Delay(uint8_t us)
{
  halDelayUs(us);
}

/******************************************************************************
  Clear the irq.
******************************************************************************/
void HAL_ClearRfIrqFlag(void)
{
  halClearExtIrq(IRQ_RF_PIN);
}

/******************************************************************************
  Enables the irq.
******************************************************************************/
void HAL_EnableRfIrq(void)
{
  halEnableExtIrq(IRQ_RF_PIN); 
}

/******************************************************************************
  Disables the irq.
******************************************************************************/
uint8_t HAL_DisableRfIrq(void)
{
  return halDisableExtIrq(IRQ_RF_PIN);
}

/******************************************************************************
  Sets SLP_TR pin to 1.
******************************************************************************/
void HAL_SetRfSlpTr(void)
{
  GPIO_RF_SLP_TR_set();
}

/******************************************************************************
  Clears SLP_TR pin to 0.
******************************************************************************/
void HAL_ClearRfSlpTr(void)
{
  GPIO_RF_SLP_TR_clr();
}

/******************************************************************************
  Makes SLP_TR pin as input.
******************************************************************************/
void HAL_MakeInRfSlpTr(void)
{
  GPIO_RF_SLP_TR_make_in();
}

/******************************************************************************
  Makes SLP_TR pin as input.
******************************************************************************/
void HAL_MakeOutRfSlpTr(void)
{
  GPIO_RF_SLP_TR_make_out();
}

/******************************************************************************
  Sets RST_TR pin to 1.
******************************************************************************/
void HAL_SetRfRst(void)
{
  GPIO_RF_RST_set();
}

/******************************************************************************
  Clears RST_TR pin to 1.
******************************************************************************/
void HAL_ClearRfRst(void)
{
  GPIO_RF_RST_clr();
}

/******************************************************************************
  Init pins that controls RF chip.
******************************************************************************/
void HAL_InitRfPins(void)
{
  GPIO_RF_SLP_TR_clr();
  GPIO_RF_SLP_TR_make_out();

  GPIO_RF_RST_set();
  GPIO_RF_RST_make_out();
}

/******************************************************************************
  Initialization rf irq.
******************************************************************************/
void HAL_InitRfIrq(void)
{
  /* configure IRQ */ 
  HAL_IrqMode_t mode;
  
  PORTB_PINCFG14 |= PORTB_PINCFG14_PMUXEN; //IRQ
  PORTB_PMUX7 = PORTB_PMUX7_PMUXE(0); ////peripheral function A

  mode = IRQ_RISING_EDGE;
  halRegisterExtIrq(IRQ_RF_PIN, mode, phyDispatcheRfInterrupt);

}
/******************************************************************************
  Returns current frequency code.
******************************************************************************/
HalSysFreq_t HAL_GetRfFreq(void)
{
  return HAL_FREQ_1MHZ;
}

/**************************************************************************//**
  \brief Wait for when radio will be waked up.

  \param none.
  \return none.
******************************************************************************/
void halWaitRadio(void)
{
  uint8_t tempValue = 0;

  do {
    HAL_SelectRfSpi();
    HAL_WriteByteRfSpi(RF_REGISTER_READ_ACCESS_MODE | RF_REGISTER_TRX_STATUS_ADDRESS);
    tempValue = HAL_WriteByteRfSpi(tempValue);
    HAL_DeselectRfSpi();
  } while(RF_TRX_OFF_STATE != tempValue);
}

/**************************************************************************//**
  \brief Enables RX TX indicator for radio if that is supported.
******************************************************************************/
void HAL_EnableRxTxSwitcher(void)
{
  #ifdef _HAL_RF_RX_TX_INDICATOR_
    phyRxTxSwitcherOn();
  #endif //_HAL_RF_RX_TX_INDICATOR_
}

/**************************************************************************//**
  \brief Enables Antenna diversity option for radio if that is supported.
******************************************************************************/
void HAL_InitAntennaDiversity(void)
{
  #ifdef _HAL_ANT_DIVERSITY_
    phyAntennaDiversityInit();
  #endif //_HAL_ANT_DIVERSITY_
}

/**************************************************************************//**
  \brief Enables Antenna diversity in RX mode for radio if that is supported.
******************************************************************************/
void HAL_EnableRxAntennaDiversity(void)
{
  #ifdef _HAL_ANT_DIVERSITY_
    phyRxAntennaDiversity();
  #endif //_HAL_ANT_DIVERSITY_
}

/**************************************************************************//**
  \brief Enables Antenna diversity in TX mode for radio if that is supported.
******************************************************************************/
void HAL_EnableTxAntennaDiversity(void)
{/* Commented out as Tx antenna diversity is not required */
/*  #ifdef _HAL_ANT_DIVERSITY_
    phyTxAntennaDiversity();
  #endif //_HAL_ANT_DIVERSITY_
*/
}

//eof halRfCtrl.c
