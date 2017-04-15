/***************************************************************************//**
  \file WSNSensorManager.h

  \brief Contains sensors access function prototypes.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:
    15/03/12 D. Kolmakov - Created

  Last change:
    $Id: WSNSensorManager.h 27584 2015-01-09 14:45:42Z unithra.c $
*******************************************************************************/
#ifndef _WSNSENSORMANAGER_H
#define _WSNSENSORMANAGER_H

/*****************************************************************************
                              Prototypes section
******************************************************************************/
/**************************************************************************//**
  \brief Sensors initialization.

  \param None.

  \return None
******************************************************************************/
void appStartSensorManager(void);

/**************************************************************************//**
  \brief Closes all sensors.

  \param None.

  \return None
******************************************************************************/
void appStopSensorManager();

/**************************************************************************//**
  \brief Sensors data request.

  \param[in] sensorsGot - on sensors reading finished callback.

  \return None.
******************************************************************************/
void appGetSensorData(void (*sensorsGot)(void));

#endif // _WSNSENSORMANAGER_H
