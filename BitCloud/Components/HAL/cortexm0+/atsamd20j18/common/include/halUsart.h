/*****************************************************************************//**
\file  halUsart.h

\brief Declarations of usart hardware-dependent module.

\author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

\internal
  History:
    17/09/13 Viswanadham Kotla - Created
**********************************************************************************/
/******************************************************************************
 *   WARNING: CHANGING THIS FILE MAY AFFECT CORE FUNCTIONALITY OF THE STACK.  *
 *   EXPERT USERS SHOULD PROCEED WITH CAUTION.                                *
 ******************************************************************************/
#ifndef _HAL_USART_H
#define _HAL_USART_H

/******************************************************************************
                   Includes section
******************************************************************************/

#include <halClkCtrl.h>
#include <halTaskManager.h>
#include <sysTypes.h>
#include <gpio.h>
#include <usart.h>
/******************************************************************************
                   Define(s) section
******************************************************************************/

#define USART0                 &(SERCOM3->USART)
#define USART1                 &(SERCOM4->USART)

#define USART_CHANNEL_0        USART0
#define USART_CHANNEL_1        USART1

#define HAL_GET_INDEX_BY_CHANNEL(channel)  (USART_CHANNEL_0 == (channel) ? 0 : 1)

/* USART Pin assignments */
HAL_ASSIGN_PIN(USART0_TXD,    A, 24);
HAL_ASSIGN_PIN(USART0_RXD,    A, 25);

HAL_ASSIGN_PIN(USART1_TXD,    B, 8);
HAL_ASSIGN_PIN(USART1_RXD,    B, 9);

/******************************************************************************
                   Types section
******************************************************************************/
// usart channel
typedef SercomUsart* UsartChannel_t;

// usart data speed
typedef enum
{

  USART_BAUDRATE_1200 = ((uint64_t)65536ul * (F_CPU - 16ul * 1200ul) / F_CPU), // 1200 baud rate
  USART_BAUDRATE_2400 = ((uint64_t)65536ul * (F_CPU - 16ul * 2400ul) / F_CPU), // 2400 baud rate
  USART_BAUDRATE_4800 = ((uint64_t)65536ul * (F_CPU - 16ul * 4800ul) / F_CPU), // 4800 baud rate
  USART_BAUDRATE_9600 = ((uint64_t)65536ul * (F_CPU - 16ul * 9600ul) / F_CPU), // 9600 baud rate
  USART_BAUDRATE_19200 = ((uint64_t)65536ul * (F_CPU - 16ul * 19200ul) / F_CPU), // 19200 baud rate
  USART_BAUDRATE_38400 = ((uint64_t)65536ul * (F_CPU - 16ul * 38400ul) / F_CPU), // 38400 baud rate
  USART_BAUDRATE_57600 = ((uint64_t)65536ul * (F_CPU - 16ul * 57600ul) / F_CPU), // 57600 baud rate
  USART_BAUDRATE_115200 =((uint64_t)65536ul * (F_CPU - 16ul * 115200ul)/ F_CPU), // 115200 baud rate
  USART_SYNC_BAUDRATE_1200 = F_CPU / 1200ul,
  USART_SYNC_BAUDRATE_2400 = F_CPU / 2400ul,
  USART_SYNC_BAUDRATE_4800 = F_CPU / 4800ul,
  USART_SYNC_BAUDRATE_9600  = F_CPU / 9600ul,
  USART_SYNC_BAUDRATE_38400 = F_CPU / 38400ul,
  USART_SYNC_BAUDRATE_57600 = F_CPU / 57600ul,
  USART_SYNC_BAUDRATE_115200 = F_CPU / 115200ul
} UsartBaudRate_t;

// USART data length
typedef enum
{
#if defined(USART_CHANNEL_0)
  USART_DATA5 = SC3_USART_CTRLB_CHSIZE(5), // 5 bits data length
  USART_DATA6 = SC3_USART_CTRLB_CHSIZE(6), // 6 bits data length
  USART_DATA7 = SC3_USART_CTRLB_CHSIZE(7), // 7 bits data length
  USART_DATA8 = SC3_USART_CTRLB_CHSIZE(0), // 8 bits data length
  USART_DATA9 = SC3_USART_CTRLB_CHSIZE(1), // 8 bits data length
#else
  USART_DATA5 = SC4_USART_CTRLB_CHSIZE(5), // 5 bits data length
  USART_DATA6 = SC4_USART_CTRLB_CHSIZE(6), // 6 bits data length
  USART_DATA7 = SC4_USART_CTRLB_CHSIZE(7), // 7 bits data length
  USART_DATA8 = SC4_USART_CTRLB_CHSIZE(0), // 8 bits data length
  USART_DATA9 = SC4_USART_CTRLB_CHSIZE(1), // 8 bits data length
#endif
} UsartData_t;

// parity mode
typedef enum
{
#if defined(USART_CHANNEL_0)
  USART_PARITY_NONE  = SC3_USART_CTRLA_FORM(0), // Non parity mode
  USART_PARITY_EVEN  = 0,                       // Even parity mode
  USART_PARITY_ODD   = SC3_USART_CTRLB_PMODE,   // Odd parity mode
#else
  USART_PARITY_NONE  = SC4_USART_CTRLA_FORM(0), // Non parity mode
  USART_PARITY_EVEN  = 0,                       // Even parity mode
  USART_PARITY_ODD   = SC4_USART_CTRLB_PMODE,   // Odd parity mode
#endif
} UsartParity_t;

// number of stop bits
typedef enum
{
#if defined(USART_CHANNEL_0)
  USART_STOPBIT_1  = 0,   // 1 stop bits mode
  USART_STOPBIT_2  = SC3_USART_CTRLB_SBMODE    // 2 stop bits mode
#else
  USART_STOPBIT_1  = 0,   // 1 stop bits mode
  USART_STOPBIT_2  = SC4_USART_CTRLB_SBMODE    // 2 stop bits mode
#endif
} UsartStopBits_t;

// dummy parameter. only for avr compatibility.
typedef enum
{
  USART_EDGE_MODE_FALLING = 0,
  USART_EDGE_MODE_RISING  = 1
} UsartEdgeMode_t;

// clock is output in master mode else input
typedef enum
{
  USART_CLK_MODE_SLAVE  = 0
} UsartClkMode_t;

// USART mode
typedef enum
{
  USART_MODE_ASYNC = 0,
#if defined(USART_CHANNEL_0)
  USART_MODE_SYNC  = SC3_USART_CTRLA_CMODE
#else
  USART_MODE_SYNC  = SC4_USART_CTRLA_CMODE
#endif
} UsartMode_t;

#if defined(_USE_USART_ERROR_EVENT_)
  // usart receiver error reason
  typedef enum
  {
    FRAME_ERROR,
    DATA_OVERRUN,
    PARITY_ERROR
  } UsartErrorReason_t;
#endif

// USART task IDs.
typedef enum
{
  #if defined(HAL_USE_USART_CHANNEL_0)
    HAL_USART_TASK_USART0_DRE,
    HAL_USART_TASK_USART0_TXC,
    HAL_USART_TASK_USART0_RXC,
    #if defined(_USE_USART_ERROR_EVENT_)
      HAL_USART_TASK_USART0_ERR,
    #endif
  #endif

  #if defined(HAL_USE_USART_CHANNEL_1)
    HAL_USART_TASK_USART1_DRE,
    HAL_USART_TASK_USART1_TXC,
    HAL_USART_TASK_USART1_RXC,
    #if defined(_USE_USART_ERROR_EVENT_)
      HAL_USART_TASK_USART1_ERR,
    #endif
  #endif

  HAL_USART_TASKS_NUMBER
} HalUsartTaskId_t;

// usart control
typedef struct
{
  volatile uint16_t txPointOfRead;
  volatile uint16_t txPointOfWrite;
  volatile uint16_t rxPointOfRead;
  volatile uint16_t rxPointOfWrite;
  volatile uint16_t rxBytesInBuffer;
  uint8_t  usartShiftRegisterEmpty;
#if defined(_USE_USART_ERROR_EVENT_)
  uint8_t  errorReason;
#endif
} HalUsartService_t;

/******************************************************************************
                   Prototypes section
******************************************************************************/
/**************************************************************************//**
\brief Puts the byte received to the cyclic buffer.

\param[in]
  tty - channel number.
\param[in]
  data - data to put.
******************************************************************************/
void halUsartRxBufferFiller(UsartChannel_t tty, uint8_t data);

/**************************************************************************//**
\brief Checks the channel number.

\param[in]
  channel - channel to be verified.

\return
  true if channel is possible, \n
  false otherwise.
******************************************************************************/
bool halIsUsartChannelCorrect(UsartChannel_t channel);

#if defined(_USE_USART_ERROR_EVENT_)
/**************************************************************************//**
\brief Save status register for analyzing of the error reason.

\param[in]
  tty - channel number.
\param[in]
  status - usart status register.
******************************************************************************/
void halUsartSaveErrorReason(UsartChannel_t tty, uint8_t status);
#endif

/******************************************************************************
                   Inline static functions section
******************************************************************************/
/**************************************************************************//**
  \brief Disables USART channel

  \param tty - number of USART channel.
  \return 0 - success, nonZero - failure.
******************************************************************************/
INLINE uint8_t halCloseUsart(UsartChannel_t tty)
{
  //disable the clock of USART
  if (USART_CHANNEL_0 == tty)
    PM_APBCMASK &= ~PM_APBCMASK_SERCOM3;
  else
    PM_APBCMASK &= ~PM_APBCMASK_SERCOM4;

  return 0;
}

/**************************************************************************//**
  \brief Enables data register empty interrupt

  \param tty - number of USART channel.
  \return none.
******************************************************************************/
INLINE void halEnableUsartDremInterrupt(UsartChannel_t tty)
{
  if(USART_CHANNEL_0 == tty)
    tty->INTENSET.reg = SC3_USART_INTENSET_DRE;
  else
    tty->INTENSET.reg = SC4_USART_INTENSET_DRE;
}

/**************************************************************************//**
  \brief Disables data register empty interrupt

  \param tty - number of USART channel.
  \return none.
******************************************************************************/
INLINE void halDisableUsartDremInterrupt(UsartChannel_t tty)
{
  if(USART_CHANNEL_0 == tty)
    tty->INTENCLR.reg = SC3_USART_INTENCLR_DRE;
  else
    tty->INTENCLR.reg = SC4_USART_INTENCLR_DRE;
}

/**************************************************************************//**
  \brief Enables transmit complete interrupt

  \param tty - number of USART channel.
  \return none.
******************************************************************************/
INLINE void halEnableUsartTxcInterrupt(UsartChannel_t tty)
{
  if(USART_CHANNEL_0 == tty)
    tty->INTENSET.reg = SC3_USART_INTENSET_TXC;
  else
    tty->INTENSET.reg = SC4_USART_INTENSET_TXC;
}

/**************************************************************************//**
  \brief Disables transmit complete interrupt

  \param tty - number of USART channel.
  return none.
******************************************************************************/
INLINE void halDisableUsartTxcInterrupt(UsartChannel_t tty)
{
  if(USART_CHANNEL_0 == tty)
    tty->INTENCLR.reg = SC3_USART_INTENCLR_TXC;
  else
    tty->INTENCLR.reg = SC4_USART_INTENCLR_TXC;
}

/**************************************************************************//**
  \brief Enables receive complete interrupt

  \param tty - number of USART channel.
  \return none.
******************************************************************************/
INLINE void halEnableUsartRxcInterrupt(UsartChannel_t tty)
{
  if(USART_CHANNEL_0 == tty)
    tty->INTENSET.reg = SC3_USART_INTENSET_RXC;
  else
    tty->INTENSET.reg = SC4_USART_INTENSET_RXC;
}

/**************************************************************************//**
  \brief Disables receive complete interrupt

  \param tty - number of USART channel.
  \return none.
******************************************************************************/
INLINE void halDisableUsartRxcInterrupt(UsartChannel_t tty)
{
  if(USART_CHANNEL_0 == tty)
    tty->INTENCLR.reg = SC3_USART_INTENCLR_RXC;
  else
    tty->INTENCLR.reg = SC4_USART_INTENCLR_RXC;
}

/**************************************************************************//**
  \brief Puts byte to data register of USART

  \param tty - number of USART channel.
         data - byte to send.
  \return none.
******************************************************************************/
INLINE void halSendUsartByte(UsartChannel_t tty, uint8_t data)
{
  tty->DATA.reg = data;
}

#endif // _HAL_USART_H
//eof halUsart.h

