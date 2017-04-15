/**************************************************************************//**
  \file lightColorSchemesConversion.h

  \brief
    Light device color schemes conversion interface

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    11.10.12 N. Fomin - Created.
******************************************************************************/
#ifndef _LIGHTCOLORSCHEMESCONVERTION_H
#define _LIGHTCOLORSCHEMESCONVERTION_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <sysTypes.h>

/******************************************************************************
                    Prototypes section
******************************************************************************/
/**************************************************************************//**
\brief Converts color temperature to appropriate XY coordinates

\param[in] temperature - color temperature (attribute value);
\param[out] x          - x coordinate (attribute value);
\param[out] y          - y coordinate (attribute value)
******************************************************************************/
void lightConvertColorToXY(uint16_t temperature, uint16_t *x, uint16_t *y);

/**************************************************************************//**
\brief Converts XY coordinates to appropriate color temperature

\param[in] x - x coordinate (attribute value);
\param[in] y - y coordinate (attribute value)

\returns color temperature (attribute value)
******************************************************************************/
uint16_t lightConvertXYToColor(uint16_t x, uint16_t y);

#endif // _LIGHTCOLORSCHEMESCONVERTION_H

// eof lightColorSchemesConversion.h

