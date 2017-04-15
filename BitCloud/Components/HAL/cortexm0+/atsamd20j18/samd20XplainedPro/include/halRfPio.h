/*****************************************************************************//**
\file   halRfPio.h

\brief  AT86RF230 control pins declarations.

\author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

\internal
  History:
    04/09/13 Viswanadham Kotla - Created
    06/09/13 Viswanadham Kotla - modified
**********************************************************************************/
/******************************************************************************
 *   WARNING: CHANGING THIS FILE MAY AFFECT CORE FUNCTIONALITY OF THE STACK.  *
 *   EXPERT USERS SHOULD PROCEED WITH CAUTION.                                *
 ******************************************************************************/

#ifndef _HALRFPIO_H
#define _HALRFPIO_H

/******************************************************************************
                        Includes section.
******************************************************************************/
#include <gpio.h>

/******************************************************************************
                   Define(s) section
******************************************************************************/

#define IRQ_RF_PIN        IRQ_EIC_EXTINT14
#define IRQ_RF_PORT       IRQ_PORT_B
/******************************************************************************
                 Inline static functions prototypes section.
******************************************************************************/

HAL_ASSIGN_PIN(RF_RST,    A, 22);
HAL_ASSIGN_PIN(RF_IRQ,    B, 14);
HAL_ASSIGN_PIN(RF_SLP_TR, B, 15);
HAL_ASSIGN_PIN(RF_CS,     A, 17);
HAL_ASSIGN_PIN(RF_MISO,   A, 16);
HAL_ASSIGN_PIN(RF_MOSI,   A, 18);
HAL_ASSIGN_PIN(RF_SCK,    A, 19);

#endif // _HALRFPIO_H
// eof halRfPio.h
