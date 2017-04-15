/*****************************************************************************//**
  \file serialInterface.h

  \brief

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
******************************************************************************/
#ifndef _SERIALINTERFACE_H
#define _SERIALINTERFACE_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <usart.h>
#include <rs232Controller.h>

/******************************************************************************
                    Defines section
******************************************************************************/
#if APP_INTERFACE == APP_INTERFACE_VCP
  #include <vcpVirtualUsart.h>
#endif // APP_INTERFACE_VCP

#if APP_INTERFACE == APP_INTERFACE_USBFIFO
  #include <usbFifoUsart.h>
#endif // APP_INTERFACE_USBFIFO

#if APP_INTERFACE == APP_INTERFACE_UART
  #include <uart.h>
#endif // APP_INTERFACE_UART

#ifndef APP_INTERFACE
  INLINE int OPEN_USART(HAL_UsartDescriptor_t *descriptor)\
  {\
    (void)descriptor;\
    return 0;\
  }
  INLINE int CLOSE_USART(HAL_UsartDescriptor_t *descriptor)\
  {\
    (void)descriptor;\
    return 0;\
  }
  INLINE int WRITE_USART(HAL_UsartDescriptor_t *descriptor, uint8_t *buffer, uint8_t length)\
  {\
    (void)descriptor;\
    (void)buffer;\
    return length;\
  }
  INLINE int READ_USART(HAL_UsartDescriptor_t *descriptor, uint8_t *buffer, uint8_t length)\
  {\
    (void)descriptor;\
    (void)buffer;\
    (void)length;\
    return 0;\
  }
  #define USART_CHANNEL         APP_USART_CHANNEL
  #define USART_RX_BUFFER_LENGTH 0
#endif // APP_INTERFACE_USART

#if APP_INTERFACE == APP_INTERFACE_USART
  INLINE int OPEN_USART(HAL_UsartDescriptor_t *descriptor)\
  {\
    BSP_EnableRs232();
    return HAL_OpenUsart(descriptor);\
  }
  INLINE int CLOSE_USART(HAL_UsartDescriptor_t *descriptor)\
  {\
    BSP_DisableRs232();
    return HAL_CloseUsart(descriptor);\
  }
  #define WRITE_USART           HAL_WriteUsart
  #define READ_USART            HAL_ReadUsart
  #define USART_CHANNEL         APP_USART_CHANNEL
  #define USART_RX_BUFFER_LENGTH 0
#endif // APP_INTERFACE_USART

#if APP_INTERFACE == APP_INTERFACE_VCP
  #define OPEN_USART            VCP_OpenUsart
  #define CLOSE_USART           VCP_CloseUsart
  #define WRITE_USART           VCP_WriteUsart
  #define READ_USART            VCP_ReadUsart
  #define USART_CHANNEL         USART_CHANNEL_VCP
  #define USART_RX_BUFFER_LENGTH 64
#endif // APP_INTERFACE_VCP

#if APP_INTERFACE == APP_INTERFACE_UART
  #define OPEN_USART            HAL_OpenUart
  #define CLOSE_USART           HAL_CloseUart
  #define WRITE_USART           HAL_WriteUart
  #define READ_USART            HAL_ReadUart
  #define USART_CHANNEL         APP_UART_CHANNEL
  #define USART_RX_BUFFER_LENGTH 0
#endif // APP_INTERFACE_UART

#if APP_INTERFACE == APP_INTERFACE_USBFIFO
  #define OPEN_USART            USBFIFO_OpenUsart
  #define CLOSE_USART           USBFIFO_CloseUsart
  #define WRITE_USART           USBFIFO_WriteUsart
  #define READ_USART            USBFIFO_ReadUsart
  #define USART_CHANNEL         USART_CHANNEL_USBFIFO
  #define USART_RX_BUFFER_LENGTH 0
#endif // APP_INTERFACE_USBFIFO

#if APP_USART_SPEED == 9600
  #define USART_SPEED       USART_BAUDRATE_9600
#else
  #define USART_SPEED       USART_BAUDRATE_38400
#endif

#ifndef USART_CHANNEL
  #error USART interface is not defined.
#endif // OPEN_USART

#endif // _SERIALINTERFACE_H

// eof serialInterface.h
