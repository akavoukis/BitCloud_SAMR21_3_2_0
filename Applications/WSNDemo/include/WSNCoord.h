/***************************************************************************//**
  \file WSNCoord.h

  \brief Contains function prototypes related to coordinator functionality.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:
    15/03/12 D. Kolmakov - Created

  Last change:
    $Id: WSNCoord.h 27584 2015-01-09 14:45:42Z unithra.c $
*******************************************************************************/
#ifndef _WSNCOORD_H
#define _WSNCOORD_H

/*****************************************************************************
                              Includes section
******************************************************************************/
#include <WSNDemoApp.h>

/*****************************************************************************
                              Prototypes section
******************************************************************************/
/**************************************************************************//**
  \brief Fills device interface structure with functions related to coordinator.

  \param[in, out] deviceInterface - pointer to device interface structure.

  \return None.
******************************************************************************/
void appCoordinatorGetInterface(SpecialDeviceInterface_t *deviceInterface);

#endif // _WSNCOORD_H
