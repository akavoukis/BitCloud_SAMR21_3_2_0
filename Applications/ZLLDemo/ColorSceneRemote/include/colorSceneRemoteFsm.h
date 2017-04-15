/**************************************************************************//**
  \file colorSceneRemoteFsm.h

  \brief
    Color Scene Remote state machine interface.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    13.12.12 D. Kolmakov - Created.
******************************************************************************/
#ifndef _COLORSCENEREMOTEFSM_H
#define _COLORSCENEREMOTEFSM_H

#include <N_Task.h>
#include <zllDemo.h>

/******************************************************************************
                    Prototypes section
******************************************************************************/
/**************************************************************************//**
\brief Light event handler

\param[in] evt - event id
******************************************************************************/
bool ColorSceneRemote_EventHandler(N_Task_Event_t evt);

/**************************************************************************//**
\brief State machine initialization routine
******************************************************************************/
void ColorSceneRemote_FsmInit(void);

/**************************************************************************//**
\brief Check for any bound device in local table
\return true - if one exist; false - otherwise
******************************************************************************/
bool isAnyDeviceBound(void);

/**************************************************************************//**
\brief Get the next device from the local bind table
\return an index in the table
******************************************************************************/
BoundDevice_t *boundDeviceNext(void);

/**************************************************************************//**
\brief Get the previous device from the local bind table
\return an index in the table
******************************************************************************/
BoundDevice_t *boundDevicePrev(void);

/**************************************************************************//**
\brief Get the next bound device from the local binding table and send
an identify command to it
******************************************************************************/
void selectNextBoundDevice(void);

/**************************************************************************//**
\brief Get the previous bound device from the local binding table and send
an identify command to it
******************************************************************************/
void selectPrevBoundDevice(void);

/**************************************************************************//**
\brief Remove a previously bound device from the application table

\param[in] extAddr - the extended address of the device to be removed
******************************************************************************/
void removeBoundDevice(ExtAddr_t *extAddr);

/**************************************************************************//**
\brief Initiates touchlink performing
******************************************************************************/
void performTouchlink(void);

/**************************************************************************//**
\brief Stops touchlink performing
******************************************************************************/
void stopTouchlink(void);

/**************************************************************************//**
\brief Initiates resetting device to factory new.
******************************************************************************/
void performResetDeviceToFn(void);

/**************************************************************************//**
\brief Stops resetting device to factory new.
******************************************************************************/
void stopResetDeviceToFn(void);

/**************************************************************************//**
\brief Returns current group id
******************************************************************************/
uint16_t getOwnGroupId(void);


#endif // _COLORSCENEREMOTEFSM_H