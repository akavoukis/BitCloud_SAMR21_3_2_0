/************************************************************************//**
  \file keyboardPoll.c

  \brief
    Keyborad poll implementation.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2013, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    30.09.13 N. Fomin - Created.
******************************************************************************/

#if defined ZAPPSI_HOST && defined WIN
/*******************************************************************************
                    Includes section
*******************************************************************************/
#include <keyboardPoll.h>
#include <conio.h>
#include <console.h>
#include <stdio.h>

/*******************************************************************************
                    Implementation section
*******************************************************************************/
/**************************************************************************//**
\brief Poll if any key is pressed and call processing routint if any
******************************************************************************/
void pollKeyboard(void)
{
  int ch;

  if (0 != _kbhit())
  {
    ch = _getch();
    putch(ch);
    consoleRx(ch);
    if ('\r' == ch)
    {
      putch('\n');
      consoleRx('\n');
    }
  }
}

#endif // defined ZAPPSI_HOST && defined WIN
// eof keyboardPoll.c
