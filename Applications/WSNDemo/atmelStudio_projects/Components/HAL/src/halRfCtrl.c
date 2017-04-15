/**************************************************************************//**
\file   halRfCtrl.c

\brief  mac pin interface implementation.

\author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2012, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

\internal
  History:
    07/04/14 karthik.p_u - Created
  Last Change:
    $Id$
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
#include <gpio.h>
/******************************************************************************
                   Define(s) section
******************************************************************************/
#define RF_REGISTER_READ_ACCESS_MODE      0x80
#define RF_REGISTER_TRX_STATUS_ADDRESS    0x01
#define RF_TRX_OFF_STATE                  0x08
#define RF_REGISTER_TRX_REG_ADDRESS       0x02
#define RFCTRL_CFG_ANT_DIV                0x04
/******************************************************************************
                   Prototypes section
******************************************************************************/
/**************************************************************************//**
\brief  Read transceiver state
******************************************************************************/
static uint8_t readTrxState(void);

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
/**************************************************************************//**
\brief  read the antenna used for last transmission and switch to other antenna 
******************************************************************************/
void phySwitchLastTxAntenna(void);

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

/* samR21 custom Pro */
  PORTB_PINCFG0 |= PORTB_PINCFG0_PMUXEN; //IRQ
  PORTB_PMUX0 = PORTB_PMUX0_PMUXE(0); ////peripheral function A

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
  while(RF_TRX_OFF_STATE != readTrxState());
}

/**************************************************************************//**
\brief  Read transceiver state
******************************************************************************/
static uint8_t readTrxState(void)
{
  uint8_t tempValue = 0;

  HAL_SelectRfSpi();
  HAL_WriteByteRfSpi(RF_REGISTER_READ_ACCESS_MODE | RF_REGISTER_TRX_STATUS_ADDRESS);
  tempValue = HAL_WriteByteRfSpi(tempValue);
  HAL_DeselectRfSpi();

  return tempValue;
}

/**************************************************************************//**
  \brief Check whether transceiver in TRX_OFF state
******************************************************************************/
bool halRadioInTrxOff(void)
{
  return (RF_TRX_OFF_STATE == readTrxState());

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
  PinConfig_t rfctrl1,rfctrl2;

  /* Configure PIOs for RFCTRL */
  rfctrl1.portNum = PORT_A;
  rfctrl1.pinNum = 9;
  rfctrl1.functionConfig = 5;
  GPIO_make_out(&rfctrl1);
  GPIO_pinfunc_config(&rfctrl1);

  rfctrl2.portNum = PORT_A;
  rfctrl2.pinNum = 12;
  rfctrl2.functionConfig = 5;
  GPIO_make_out(&rfctrl2);
  GPIO_pinfunc_config(&rfctrl2);

  /* Enable the clock of RFCTRL */
  PM_APBCMASK |= PM_APBCMASK_RFCTRL;

  RFCTRL_FECFG = RFCTRL_CFG_ANT_DIV;

  /* Antenna 1 or 2 selection */ 
/*  HAL_SelectRfSpi();
  HAL_WriteByteRfSpi(RF_REGISTER_WRITE_ACCESS_MODE | RF_ANT_DIV_REG );
  HAL_WriteByteRfSpi( ANT_CTRL_SWITCH_ENABLE | ANT_CTRL_ANTENNA_1);//on chip antenna
  HAL_DeselectRfSpi(); */

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

/**************************************************************************//**
  \brief To switch from the antenna used for last transmission to the other
******************************************************************************/
void HAL_SwitchLastTxAntenna(void)
{
  #ifdef _HAL_ANT_DIVERSITY_
    phySwitchLastTxAntenna();
  #endif //_HAL_ANT_DIVERSITY_
}

//eof halRfCtrl.c
