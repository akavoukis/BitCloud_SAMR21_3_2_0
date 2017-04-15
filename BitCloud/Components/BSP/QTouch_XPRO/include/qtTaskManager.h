/************************************************************************//**
  \file qtTaskManager.h

  \brief
    The header file is for the qtTaskManager.c

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2012, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    14.08.14 Kanchana - Created.
******************************************************************************/

#ifndef _QTTASKMANAGER_H
#define _QTTASKMANAGER_H

/******************************************************************************
                   Includes section
******************************************************************************/
#include <gpio.h>
/**************************************************************************//**
                    Types section
******************************************************************************/
typedef enum _BSP_TouchEvent_t
{
  TOUCHKEY_NO_EVENT,
  TOUCHKEY_PRESSED_EVENT,
  TOUCHKEY_RELEASED_EVENT,
  TOUCHKEY_SLIDER_EVENT
} BSP_TouchEvent_t;

typedef enum _BSP_ButtonId_t
{
  NONE,
  BUTTON_L,
  BUTTON_R,
  BUTTON_SLIDER
}BSP_ButtonId_t;


#define halInitLed0()     GPIO_A13_make_out()
#define halOnLed0()       GPIO_A13_clr()
#define halOffLed0()      GPIO_A13_set()

#define halInitLed1()     GPIO_B3_make_out()
#define halPullupLed1()     GPIO_B3_make_pullup()
#define halOnLed1()       GPIO_B3_clr()
#define halOffLed1()      GPIO_B3_set()

#define halInitLed2()     GPIO_A18_make_out()
#define halOnLed2()       GPIO_A18_clr()
#define halOffLed2()      GPIO_A18_set()

#define halInitLed3()     GPIO_A19_make_out()
#define halOnLed3()       GPIO_A19_clr()
#define halOffLed3()      GPIO_A19_set()

#define halInitLed4()     GPIO_A22_make_out()
#define halOnLed4()       GPIO_A22_clr()
#define halOffLed4()      GPIO_A22_set()

#define halInitLed5()     GPIO_A23_make_out()
#define halOnLed5()       GPIO_A23_clr()
#define halOffLed5()      GPIO_A23_set()

#define halInitLed6()     GPIO_B22_make_out()
#define halOnLed6()       GPIO_B22_clr()
#define halOffLed6()      GPIO_B22_set()

#define halInitLed7()     GPIO_B23_make_out()
#define halOnLed7()       GPIO_B23_clr()
#define halOffLed7()      GPIO_B23_set()

#define halInitLed8()     GPIO_A14_make_out()
#define halOnLed8()       GPIO_A14_clr()
#define halOffLed8()      GPIO_A14_set()

#define halInitLed9()     GPIO_A15_make_out()
#define halOnLed9()       GPIO_A15_clr()
#define halOffLed9()      GPIO_A15_set()

/** Type of buttons event handler */
typedef void (* BSP_TouchEventHandler_t)(BSP_TouchEvent_t event, BSP_ButtonId_t button, uint8_t data);

void BSP_InitQTouch();

void Timer_overflow_callback(void);

void Slider_LED_Off(void);

void Slider_LED_On(uint8_t slider_position);

void ButtonR_LED_Ind(bool off);

void ButtonL_LED_Ind(bool off);

void bspTouchHandler(void);

#endif// _QTTASKMANAGER_H

//eof qtTaskManager.h
