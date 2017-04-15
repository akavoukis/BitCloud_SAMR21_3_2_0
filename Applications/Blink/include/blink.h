/**************************************************************************//**
  \file blink.h

  \brief Blink application header file.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
******************************************************************************/

#ifndef _BLINK_H
#define _BLINK_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include "sliders.h"
#include "buttons.h"
#include "leds.h"

/******************************************************************************
                    Defines section
******************************************************************************/
#define APP_BLINK_INTERVAL             (APP_BLINK_PERIOD / 2)       // Blink interval.
#define APP_MIN_BLINK_INTERVAL         (APP_MIN_BLINK_PERIOD / 2)   // Minimum blink interval.
#define APP_MAX_BLINK_INTERVAL         (APP_MAX_BLINK_PERIOD / 2)   // Maximum blink interval.

#define APP_HALF_PERIOD_BUTTON          BSP_KEY0                // Button that reduces blink interval to a half.
#define APP_DOUBLE_PERIOD_BUTTON        BSP_KEY1                // Button that doubles blink interval.

#endif // _BLINK_H

// eof blink.h
