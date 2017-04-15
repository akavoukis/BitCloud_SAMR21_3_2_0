/**************************************************************************//**
\file  gpio.h

\brief This module contains a set of functions to manipulate GPIO pins.

\author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

\internal
  History:
    29/08/13 ViswanadhM kotla - Created
******************************************************************************/
/******************************************************************************
 *   WARNING: CHANGING THIS FILE MAY AFFECT CORE FUNCTIONALITY OF THE STACK.  *
 *   EXPERT USERS SHOULD PROCEED WITH CAUTION.                                *
 ******************************************************************************/
#ifndef _GPIO_H
#define _GPIO_H

/******************************************************************************
                   Includes section
******************************************************************************/
#include <sysTypes.h>
#include <atsamd20.h>

/******************************************************************************
                   Define(s) section
******************************************************************************/
/******************************************************************************
* void gpioX_set() sets GPIOX pin to logical 1 level.
* void gpioX_clr() clears GPIOX pin to logical 0 level.
* void gpioX_make_in makes GPIOX pin as input.
* void gpioX_make_in makes GPIOX pin as output.
* uint8_t gpioX_read() returns logical level GPIOX pin.
* uint8_t gpioX_state() returns configuration of GPIOX port.
*******************************************************************************/
#define HAL_ASSIGN_PIN(name, port, bit) \
INLINE void  GPIO_##name##_set()           {PORT##port##_OUTSET = (1 << bit); } \
INLINE void  GPIO_##name##_clr()           {PORT##port##_OUTCLR = (1 << bit);} \
INLINE uint8_t  GPIO_##name##_read()       {return (PORT##port##_IN & (1 << bit)) != 0;} \
INLINE uint8_t  GPIO_##name##_state()      {return (PORT##port##_DIR & (1 << bit)) != 0;} \
INLINE void  GPIO_##name##_make_out()      {PORT##port##_DIRSET = (1 << bit);\
                                            PORT##port##_PINCFG##bit |= PORTA_PINCFG##bit##_INEN; } \
INLINE void  GPIO_##name##_make_in()       {PORT##port##_DIRCLR = (1 << bit);   \
                                            PORT##port##_PINCFG##bit |= PORTA_PINCFG##bit##_INEN; \
                                            PORT##port##_PINCFG##bit &= ~PORTA_PINCFG##bit##_PULLEN;  } \
INLINE void  GPIO_##name##_make_pullup()   {PORT##port##_OUTSET = (1 << bit); \
                                            PORT##port##_PINCFG##bit |= PORTA_PINCFG##bit##_PULLEN; }  \
INLINE void  GPIO_##name##_make_pulldown() {PORT##port##_WRCONFIG_s.hwsel = (bit/16) &0x01; \
                                            PORT##port##_WRCONFIG_s.pinmask = (bit%16) & 0xF; \
                                            PORT##port##_WRCONFIG_s.pullen = 0; \
                                            PORT##port##_WRCONFIG_s.wrpincfg = 1; } \
INLINE void  GPIO_##name##_toggle()        {PORT##port##_OUTTGL = (1 << bit);} \
INLINE void  GPIO_##name##_pmuxen(void)   { PORT##port##_PINCFG##bit |= PORTA_PINCFG##bit##_PMUXEN; } \
INLINE void  GPIO_##name##_pmuxdis(void)  { PORT##port##_PINCFG##bit &= ~PORTA_PINCFG##bit##_PMUXEN; }

/******************************************************************************
                   Inline static functions section
******************************************************************************/
// the macros for the manipulation by A14
HAL_ASSIGN_PIN(A14, A, 14);
// the macros for the manipulation by A15
HAL_ASSIGN_PIN(A15, A, 15);
#endif
//eof gpio.h
