/************************************************************************//**
  \file ezModeManager.h

  \brief
    EZ-Mode interface declaration.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2013, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    10.09.13 N. Fomin - Created.
******************************************************************************/

#ifndef _EZMODEMANAGER_H
#define _EZMODEMANAGER_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <sysTypes.h>

/******************************************************************************
                    Prototypes section
******************************************************************************/
/**************************************************************************//**
\brief Initializes EZ-Mode manager

\param[in] isInitiator - should be set to true is device acts as an initiator
  of EZ-Mode, to false otherwise
******************************************************************************/
void initEzModeManager(bool isInitiator);

/**************************************************************************//**
\brief Starts EZ-Mode

\param[in] cb - callback which is called when EZ+Mode is finished
******************************************************************************/
void invokeEzMode(void (*cb)(void));

/**************************************************************************//**
\brief Checks whether EZ-Mode commissioning is in progress

\returns true if it is, false otherwise
******************************************************************************/
bool isEzModeInProgress(void);

/**************************************************************************//**
\brief resets ezmodeInProgress state
******************************************************************************/
void resetEzModeInProgress(void);
#endif // _EZMODEMANAGER_H

// eof ezModeManager.h
