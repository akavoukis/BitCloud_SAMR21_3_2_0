/************************************************************************//**
  \file uartManager.c

  \brief
    ZclDevice: Uart Manager implementation.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    05.02.09 I. Fedina - Created.
******************************************************************************/
#if (APP_DEVICE_EVENTS_LOGGING == 1) || (APP_ENABLE_CONSOLE == 1)

/*******************************************************************************
                             Includes section
*******************************************************************************/
#include <uartManager.h>
#include <console.h>
#include <stdarg.h>
#include <stdio.h>
#include <rs232Controller.h>

/*******************************************************************************
                             Definitions section
*******************************************************************************/
#define TMP_STRING_BUFFER_SIZE              100

// UART Tx buffer size
#ifndef APP_UART_TX_BUFFER_SIZE
  #if APP_ENABLE_CERTIFICATION_EXTENSION == 0
    #define APP_UART_TX_BUFFER_SIZE           405
  #else
    #define APP_UART_TX_BUFFER_SIZE           1375
  #endif
#endif

/*******************************************************************************
                             Local variables section
*******************************************************************************/
static HAL_UsartDescriptor_t appUsartDescriptor;      // UART descriptor (required by stack)
static uint8_t uartTxBuffer[APP_UART_TX_BUFFER_SIZE]; // UART Tx buffer
static uint8_t uartRxBuffer[USART_RX_BUFFER_LENGTH];  // UART Rx buffer

/*******************************************************************************
                             Prototypes section
*******************************************************************************/
static void uartDataReceived(uint16_t length);

/*******************************************************************************
                             Implementation section
*******************************************************************************/
/**************************************************************************//**
/brief Inits UART, register UART callbacks
*******************************************************************************/
void uartInit(void)
{
  appUsartDescriptor.tty             = USART_CHANNEL;
  appUsartDescriptor.mode            = USART_MODE_ASYNC;
  appUsartDescriptor.baudrate        = USART_BAUDRATE_38400;
  appUsartDescriptor.dataLength      = USART_DATA8;
  appUsartDescriptor.parity          = USART_PARITY_NONE;
  appUsartDescriptor.stopbits        = USART_STOPBIT_1;
  appUsartDescriptor.rxBuffer        = uartRxBuffer;
  appUsartDescriptor.rxBufferLength  = USART_RX_BUFFER_LENGTH;
  appUsartDescriptor.txBuffer        = uartTxBuffer;
  appUsartDescriptor.txBufferLength  = APP_UART_TX_BUFFER_SIZE;
  appUsartDescriptor.rxCallback      = uartDataReceived;
  appUsartDescriptor.txCallback      = NULL;
  appUsartDescriptor.flowControl     = USART_FLOW_CONTROL_NONE;

  #if BSP_ENABLE_RS232_CONTROL == 1 && !defined(OTAU_SERVER)
    BSP_EnableRs232();
  #endif

  OPEN_USART(&appUsartDescriptor);
}

/**************************************************************************//**
\brief Sends data to the Serial Interface

\param[in] data   - pointer to data to be sent;
\param[in] length - number of bytes (length) of data to be sent
******************************************************************************/
void sendDataToUart(uint8_t *data, uint8_t length)
{
  WRITE_USART(&appUsartDescriptor, data, length);
}

/**************************************************************************//**
\brief Reads data from the Serial Interface

\params[out] data - pointer to receive buffer;
\params[in]  length - number of bytes (length) in receive buffer;

\returns amount of read bytes
******************************************************************************/
uint8_t readDataFromUart(uint8_t *data, uint8_t length)
{
  return READ_USART(&appUsartDescriptor, data, length);
}

/**************************************************************************//**
\brief Callback on receiving data via Serial interface

\param[in] length - amount of received bytes
*******************************************************************************/
static void uartDataReceived(uint16_t length)
{
#if APP_ENABLE_CONSOLE == 1
  processConsole(length);
#endif // APP_ENABLE_CONSOLE == 1
}

/******************************************************************************
\brief Outputs formated string to serial interface

param[in] formt - formated string pointer
******************************************************************************/
#if APP_DEVICE_EVENTS_LOGGING == 1
/******************************************************************************
\brief Outputs formated string to serial interface

param[in] formt - formated string pointer
******************************************************************************/
void appSnprintf(const char *formt, ...)
{
  uint8_t str[TMP_STRING_BUFFER_SIZE];
  uint8_t length;
  va_list ap;

  va_start(ap, formt);
  length = vsnprintf((char *) str, TMP_STRING_BUFFER_SIZE, formt, ap);
  sendDataToUart(str, length);
}
#endif // APP_DEVICE_EVENTS_LOGGING == 1
#endif // #if (APP_DEVICE_EVENTS_LOGGING == 1) || (APP_ENABLE_CONSOLE == 1)
// eof uartManager.c
