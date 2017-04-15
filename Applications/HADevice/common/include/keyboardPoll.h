/************************************************************************//**
  \file keyboardPoll.h

  \brief
    Keyborad poll interface declaration.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2013, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    30.09.13 N. Fomin - Created.
******************************************************************************/

#ifndef _KEYBOARDPOLL_H
#define _KEYBOARDPOLL_H

/*****************************************************************************
                    Includes section
******************************************************************************/
#include <sysTypes.h>

/******************************************************************************
                    Prototypes section
******************************************************************************/
/**************************************************************************//**
\brief Poll if any key is pressed and call processing routint if any
******************************************************************************/
void pollKeyboard(void);

#endif // _KEYBOARDPOLL_H

// eof keyboardPoll.h
