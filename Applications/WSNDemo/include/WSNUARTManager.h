/***************************************************************************//**
  \file WSNUARTManager.h

  \brief Contains USART interface function prototypes.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:
    24/01/12 D. Kolmakov - Created

  Last change:
    $Id: WSNUARTManager.h 27584 2015-01-09 14:45:42Z unithra.c $
*******************************************************************************/
#ifndef _WSNUARTMANAGER_H
#define _WSNUARTMANAGER_H

/*****************************************************************************
                              Prototypes section
******************************************************************************/
/******************************************************************************
  \brief Init USART, register USART callbacks.

  \param None.

  \return None.
******************************************************************************/
void appStartUsartManager(void);

/******************************************************************************
  \brief Stops USART.

  \param None.

  \return None.
 ******************************************************************************/
void appStopUsartManager(void);

/******************************************************************************
  \brief New message being sent into USART has to be put into queue.

  \param[in] newMessage - new message fields.

  \return true if sending was successful, false otherwise.
 ******************************************************************************/
bool appSendMessageToUsart(void *data, uint8_t dataLength);


#endif // _WSNUARTMANAGER_H
