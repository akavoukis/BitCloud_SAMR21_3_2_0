/**************************************************************************//**
\file  halUsart.c

\brief Implementation of uart hardware-dependent module.

\author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

\internal
  History:
    17/09/13 Viswanadham Kotla - Created
*******************************************************************************/
/******************************************************************************
 *   WARNING: CHANGING THIS FILE MAY AFFECT CORE FUNCTIONALITY OF THE STACK.  *
 *   EXPERT USERS SHOULD PROCEED WITH CAUTION.                                *
 ******************************************************************************/
#if defined(HAL_USE_USART)
/******************************************************************************
                   Includes section
******************************************************************************/

#include <usart.h>
#include <halInterrupt.h>

/******************************************************************************
                   Prototypes section
******************************************************************************/
void halPostUsartTask(HalUsartTaskId_t taskId);
void halUartSync(HAL_UsartDescriptor_t *descriptor);
void halSetUsartConfig(HAL_UsartDescriptor_t *descriptor);

/*****************************************************************************
                   Implementations section
******************************************************************************/

/**************************************************************************//**
  \brief Interrupt handler usart0

  \param none
  \return none.
******************************************************************************/
void usart0Handler(void)
{
  uint8_t intFlags; 
  uint16_t status;
  uint32_t data;
  UsartChannel_t tty = USART_CHANNEL_0;
  
  /* get usart status register */
  status = tty->STATUS.reg;
  intFlags = tty->INTFLAG.reg;
  /* check overrun, frame or parity error */
  if (status & (SC3_USART_STATUS_BUFOVF | SC3_USART_STATUS_FERR | SC3_USART_STATUS_PERR))
  {
    tty->STATUS.reg = (SC3_USART_STATUS_BUFOVF | SC3_USART_STATUS_FERR | SC3_USART_STATUS_PERR);

    #if defined(_USE_USART_ERROR_EVENT_)
      halUsartSaveErrorReason(tty, status);
      halPostUsartTask((USART_CHANNEL_0 == tty) ? HAL_USART_TASK_USART0_ERR : HAL_USART_TASK_USART1_ERR);
    #endif
  } /* is any data received */
  else if (intFlags & SC3_USART_INTFLAG_RXC)
  {
    data = tty->DATA.reg;
    halUsartRxBufferFiller(tty, data);
    halPostUsartTask(HAL_USART_TASK_USART0_RXC );
  }/* is data register empty */
  else if((intFlags & SC3_USART_INTFLAG_DRE) && (tty->INTENSET.bit.DRE == 1))
  {
    halDisableUsartDremInterrupt(tty);
    halPostUsartTask(HAL_USART_TASK_USART0_DRE) ;
  } /* is transmission completed */ 
  else if ((intFlags & SC3_USART_INTFLAG_TXC)&& (tty->INTENSET.bit.TXC == 1))
  {
    // We must disable the interrupt because we must "break" context.    
    halDisableUsartTxcInterrupt(tty);
    halPostUsartTask(HAL_USART_TASK_USART0_TXC );
  }
}

/**************************************************************************//**
  \brief Interrupt handler usart1

  \param none
  \return none.
******************************************************************************/
void usart1Handler(void)
{
  uint8_t intFlags; 
  uint16_t status;
  uint32_t data;
  UsartChannel_t tty = USART_CHANNEL_1;

  /* get usart status register */
  status = tty->STATUS.reg;
  intFlags = tty->INTFLAG.reg;
  /* check overrun, frame or parity error */
  if (status & (SC4_USART_STATUS_BUFOVF | SC4_USART_STATUS_FERR | SC4_USART_STATUS_PERR))
  {
    tty->CTRLA.reg = SC3_USART_CTRLA_SWRST;
    #if defined(_USE_USART_ERROR_EVENT_)
      halUsartSaveErrorReason(tty, status);
      halPostUsartTask((USART_CHANNEL_0 == tty) ? HAL_USART_TASK_USART0_ERR : HAL_USART_TASK_USART1_ERR);
    #endif
  }/* is any data received */
  else if (intFlags & SC4_USART_INTFLAG_RXC)
  {
    data = tty->DATA.reg;
    halUsartRxBufferFiller(tty, data);
    halPostUsartTask(HAL_USART_TASK_USART1_RXC);
  }/* is data register empty */
  else if (intFlags & SC4_USART_INTFLAG_DRE)
  {
    halDisableUsartDremInterrupt(tty);
    halPostUsartTask(HAL_USART_TASK_USART1_DRE) ;
  } /* is transmission completed */ 
  else if (intFlags & SC4_USART_INTFLAG_TXC)
  {
    // We must disable the interrupt because we must "break" context. 
    halDisableUsartTxcInterrupt(tty);
    halPostUsartTask(HAL_USART_TASK_USART1_TXC);
  }
}

/**************************************************************************//**
  \brief Sets USART module parameters.

  \param descriptor - pointer to usart descriptor.
  \return none.
******************************************************************************/
void halFoundationsInit(HAL_UsartDescriptor_t *descriptor)
{
  if (USART_CHANNEL_0 == descriptor->tty)
  {
    /* Configure Port Pins for USART0 */
    GPIO_USART0_TXD_make_out();
    GPIO_USART0_TXD_pmuxen();
    GPIO_USART0_RXD_make_in();
    GPIO_USART0_RXD_pmuxen();

    /* Port pins Mux configuration */
    PORTA_PMUX12 = PORTA_PMUX12_PMUXE(2/*C*/) | PORTA_PMUX12_PMUXO(2/*C*/);

    /* clk settings */
    GCLK_CLKCTRL_s.clken = 1;
    GCLK_CLKCTRL_s.id = 0x10;
    GCLK_CLKCTRL_s.gen = 0;

    /* enable the clock of USART */
    PM_APBCMASK_s.sercom3 = 1;
    /* Clear & disable USART interrupt on NVIC */
    NVIC_DisableIRQ(SERCOM3_IRQn);
    NVIC_ClearPendingIRQ(SERCOM3_IRQn);
    /* set priority & enable USART interrupt on NVIC */
    NVIC_EnableIRQ(SERCOM3_IRQn);
  }
  else if (USART_CHANNEL_1 == descriptor->tty)
  {
    /* Configure Port pins for USART1  */
    GPIO_USART1_TXD_make_out();
    GPIO_USART1_TXD_pmuxen();
    GPIO_USART1_RXD_make_in();
    GPIO_USART1_RXD_pmuxen();

    /* Port pins Mux configuration */
    PORTB_PMUX4 = PORTB_PMUX4_PMUXE(2/*C*/) | PORTB_PMUX4_PMUXO(2/*C*/);

    /* clk settings */
    GCLK_CLKCTRL_s.clken = 1;
    GCLK_CLKCTRL_s.id = 0x11;
    GCLK_CLKCTRL_s.gen = 0;

    /* enable the clock of USART */
    PM_APBCMASK_s.sercom4 = 1;
    /* clear & disable USART interrupt on NVIC */
    NVIC_DisableIRQ(SERCOM4_IRQn);
    NVIC_ClearPendingIRQ(SERCOM4_IRQn);
    /* set priority & enable USART interrupt on NVIC */
    NVIC_EnableIRQ(SERCOM4_IRQn);
  }
  
}
/**************************************************************************//**
  \brief Sets USART module parameters.

  \param
    descriptor - USART module descriptor.
  \return
   none.
******************************************************************************/
void halSetUsartConfig(HAL_UsartDescriptor_t *descriptor)
{ 

  halFoundationsInit(descriptor);
  
  descriptor->tty->CTRLA.bit.SWRST = 1; //reset the USART 
  descriptor->tty->CTRLB.reg = ((uint32_t)descriptor->parity | (uint32_t)descriptor->dataLength | (uint32_t)descriptor->stopbits);
  halUartSync(descriptor);

  descriptor->tty->CTRLA.reg |= descriptor->mode ;
  descriptor->tty->CTRLA.bit.MODE = 0x01; //USART with internal clk
  descriptor->tty->CTRLA.bit.DORD = 0x01; //data order LSB first
  descriptor->tty->CTRLA.bit.RXPO = 0x03; //PAD3			  
  descriptor->tty->CTRLA.bit.TXPO = 0x01; //PAD2
  halUartSync(descriptor);

  if (USART_MODE_SYNC == descriptor->mode)
    descriptor->tty->CTRLA.reg  |= descriptor->syncMode;

  descriptor->tty->INTENCLR.reg = (uint8_t)ALL_PERIPHERIAL_INTERRUPT_DISABLE;

  /* Set the baud rate */  
  descriptor->tty->BAUD.reg = descriptor->baudrate;
  halUartSync(descriptor);

  /* Enable Transmitter and Receiver and set the data size */
  descriptor->tty->CTRLB.bit.TXEN  = 1;
  descriptor->tty->CTRLB.bit.RXEN  = 1;
  descriptor->tty->CTRLB.reg |= USART_DATA8;
  halUartSync(descriptor);

  /* Enable the Usart */
  descriptor->tty->CTRLA.bit.ENABLE = 1;
  halUartSync(descriptor);
  /* enable Rx interrupt */
  descriptor->tty->INTENSET.bit.RXC = 1;
  halUartSync(descriptor);
}
/**************************************************************************//**
  \brief Checking for the Sync. flag for USART register access.

  \param
    descriptor - USART module descriptor.
  \return
   none.
******************************************************************************/
void halUartSync(HAL_UsartDescriptor_t *descriptor)
{
  if(descriptor->tty == USART_CHANNEL_0)
    while (descriptor->tty->STATUS.reg & SC3_USART_STATUS_SYNCBUSY);
  else
    while (descriptor->tty->STATUS.reg & SC4_USART_STATUS_SYNCBUSY);
}
#endif // defined(HAL_USE_USART)
// eof halUsart.c
