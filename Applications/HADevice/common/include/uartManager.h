/************************************************************************//**
  \file uartManager.h

  \brief
    UART manager interface declaration.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    11.01.09 A. Taradov - Created.
******************************************************************************/

#ifndef _UARTMANAGER_H
#define _UARTMANAGER_H

/*******************************************************************************
                             Includes section
*******************************************************************************/
#include <usart.h>

#if APP_INTERFACE == APP_INTERFACE_UART
  #include <uart.h>
#endif // APP_INTERFACE_UART

#if APP_INTERFACE == APP_INTERFACE_VCP
  #include <vcpVirtualUsart.h>
#endif // APP_INTERFACE_VCP

#if APP_INTERFACE == APP_INTERFACE_USBFIFO
  #include <usbFifoUsart.h>
#endif // APP_INTERFACE_USBFIFO

#if APP_INTERFACE == APP_INTERFACE_STDIO
  #include <stdioAdapter.h>
#endif // APP_INTERFACE_STDIO
#ifdef BOARD_PC
  #include <stdio.h>
#endif
#if APP_USE_OTAU == 1
  #include <isdImageStorage.h>
#endif // APP_USE_OTAU == 1

/*******************************************************************************
                             Definitions section
*******************************************************************************/
#if APP_INTERFACE == APP_INTERFACE_USART
  #ifndef OTAU_SERVER
    #define OPEN_USART             HAL_OpenUsart
    #define CLOSE_USART            HAL_CloseUsart
    #define WRITE_USART            HAL_WriteUsart
    #define READ_USART             HAL_ReadUsart
    #define USART_CHANNEL          APP_USART_CHANNEL
    #define USART_RX_BUFFER_LENGTH 50
  #else
    #define OPEN_USART             ISD_OpenTunnel
    #define CLOSE_USART            ISD_CloseTunnel
    #define WRITE_USART            ISD_WriteTunnel
    #define READ_USART             ISD_ReadTunnel
    #define USART_CHANNEL          APP_USART_CHANNEL
    #define USART_RX_BUFFER_LENGTH 50
  #endif
#endif // APP_INTERFACE_USART

#if APP_INTERFACE == APP_INTERFACE_UART
  #define OPEN_USART            HAL_OpenUart
  #define CLOSE_USART           HAL_CloseUart
  #define WRITE_USART           HAL_WriteUart
  #define READ_USART            HAL_ReadUart
  #define USART_CHANNEL         APP_UART_CHANNEL
  #define USART_RX_BUFFER_LENGTH 50
#endif // APP_INTERFACE_UART

#if APP_INTERFACE == APP_INTERFACE_USBFIFO
    #ifndef OTAU_SERVER
    #define OPEN_USART            USBFIFO_OpenUsart
    #define CLOSE_USART           USBFIFO_CloseUsart
    #define WRITE_USART           USBFIFO_WriteUsart
    #define READ_USART            USBFIFO_ReadUsart
    #define USART_CHANNEL         USART_CHANNEL_USBFIFO
    #define USART_RX_BUFFER_LENGTH 50
  #else
    #define OPEN_USART             ISD_OpenTunnel
    #define CLOSE_USART            ISD_CloseTunnel
    #define WRITE_USART            ISD_WriteTunnel
    #define READ_USART             ISD_ReadTunnel
    #define USART_CHANNEL          USART_CHANNEL_USBFIFO
    #define USART_RX_BUFFER_LENGTH 50
  #endif
#endif // APP_INTERFACE_USBFIFO

#if APP_INTERFACE == APP_INTERFACE_VCP
  #define OPEN_USART            VCP_OpenUsart
  #define CLOSE_USART           VCP_CloseUsart
  #define WRITE_USART           VCP_WriteUsart
  #define READ_USART            VCP_ReadUsart
  #define USART_CHANNEL         USART_CHANNEL_VCP
  #define USART_RX_BUFFER_LENGTH 64
#endif // APP_INTERFACE_VCP

#if APP_INTERFACE == APP_INTERFACE_STDIO
  #define OPEN_USART            HAL_OpenStdio
  #define CLOSE_USART           HAL_CloseStdio
  #define WRITE_USART           HAL_WriteStdout
  #define READ_USART            HAL_ReadStdin
  #define USART_CHANNEL         APP_USART_CHANNEL
  #define USART_RX_BUFFER_LENGTH 50
#endif // APP_INTERFACE_STDIO

#if APP_DEVICE_EVENTS_LOGGING == 1
  #ifdef  BOARD_PC
    #define appSnprintf(...) fprintf(stdout, __VA_ARGS__)
  #else
    #define appSnprintf(...) appSnprintf(__VA_ARGS__)
  #endif
#else
  #define appSnprintf(...) do{}while(0)
#endif

#if APP_DEVICE_EVENTS_LOGGING == 1
  #define LOG_STRING(name, str) char const name[] = str
#else
  #define LOG_STRING(name, str)
#endif

/*******************************************************************************
                             Prototypes section
*******************************************************************************/
#if APP_DEVICE_EVENTS_LOGGING == 1 && !defined BOARD_PC
/**************************************************************************//**
\brief Outputs formated string to serial interface

\param[in] formt - formatted string pointer
******************************************************************************/
PRINTF_STYLE void appSnprintf(const char *formt, ...);
#endif

/**************************************************************************//**
\brief Initializes serial interface
******************************************************************************/
void uartInit(void);

/**************************************************************************//**
\brief Sends data to the Serial Interface

\param[in] data   - pointer to data to be sent;
\param[in] length - number of bytes (length) of data to be sent
******************************************************************************/
void sendDataToUart(uint8_t *data, uint8_t length);

/**************************************************************************//**
\brief Reads data from the Serial Interface

\params[out] data - pointer to receive buffer;
\params[in]  length - number of bytes (length) in receive buffer;

\returns amount of read bytes
******************************************************************************/
uint8_t readDataFromUart(uint8_t *data, uint8_t length);

#endif // _UARTMANAGER_H
