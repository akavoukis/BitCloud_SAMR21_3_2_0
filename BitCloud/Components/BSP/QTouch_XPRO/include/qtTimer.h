/**************************************************************************//**
\file  qtTimer.h

\brief Header file of Timer module.

\author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2012, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

\internal
  History:
   14.08.14 Kanchana - Created.
*******************************************************************************/
#ifndef _QTTIMER_H
#define _QTTIMER_H
#ifdef BOARD_QTOUCH_XPRO
/******************************************************************************
                   Prototypes section
******************************************************************************/
/**************************************************************************//**
\brief configure, enable and start timer counter channel
******************************************************************************/
void StartAppClock(void);

/**************************************************************************//**
\brief Stop and disable timer
******************************************************************************/
void StopAppClock(void);
#endif
#endif
