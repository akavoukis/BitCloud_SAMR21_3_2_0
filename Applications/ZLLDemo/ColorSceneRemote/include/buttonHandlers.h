/**************************************************************************//**
  \file buttonHandlers.h

  \brief
    Handlers for the buttons pressed during normal operation.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    10.03.12 D. Kolmakov - Created.
******************************************************************************/
#ifndef _BUTTON_HANDLERS_H
#define _BUTTON_HANDLERS_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <sysTypes.h>

/******************************************************************************
                    Prototypes section
******************************************************************************/
/**************************************************************************//**
\brief Button handler
******************************************************************************/
void buttonHandler(uint8_t button, uint8_t time, uint8_t alt);

#endif // _BUTTON_HANDLERS_H

// eof buttonHandlers.h
