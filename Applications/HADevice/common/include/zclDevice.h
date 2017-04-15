/************************************************************************//**
  \file ZCLdevice.h

  \brief
    Common application header file

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    11.01.09 A. Taradov - Created.
******************************************************************************/

#ifndef _ZCLDEVICE_H
#define _ZCLDEVICE_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <appConsts.h>                                  // Should be included before any other file

/******************************************************************************
                    Types section
******************************************************************************/
typedef enum
{
  DEVICE_INITIAL_STATE,
  DEVICE_ACTIVE_IDLE_STATE,
} AppDeviceState_t;

typedef void (*BindFinishedCallback_t)(ClusterId_t id);

typedef struct
{
  ShortAddr_t nwkAddrOfInterest;
  const ClusterId_t* remoteServers;
  const ClusterId_t* remoteClients;
  BindFinishedCallback_t callback;
  ProfileId_t profile;
  Endpoint_t srcEndpoint;
  uint8_t remoteClientsCnt;
  uint8_t remoteServersCnt;
} AppBindReq_t;

/******************************************************************************
                    Global variables section
******************************************************************************/
extern AppDeviceState_t appDeviceState;

/******************************************************************************
                             Prototypes section
******************************************************************************/
/**************************************************************************//**
\brief Device initialization routine
******************************************************************************/
void appDeviceInit(void);

/**************************************************************************//**
\brief Device initialization routine
******************************************************************************/
void appSecurityInit(void);

/**************************************************************************//**
\brief Device common task handler
******************************************************************************/
void appDeviceTaskHandler(void);

/**************************************************************************//**
\brief Gets bind request

\return pointer to a bind request used by HA device
******************************************************************************/
AppBindReq_t **getDeviceBindRequest(void);

/**************************************************************************//**
\brief Restarts application

\param[in] startBinding - if true then device starts finding and binding procedure
******************************************************************************/
void appRestart(bool startBinding);

/**************************************************************************//**
\brief Stops application
******************************************************************************/
void appStop(void);

/**************************************************************************//**
\brief Asks device if it is an initiator

\returns true if it is, false otherwise
******************************************************************************/
bool appIsInitiator(void);

/**************************************************************************//**
\brief EZ-Mode done callback

\returns function which is called by EZ-Mode manager when it is done
******************************************************************************/
void appEzModeDone(void);

/**************************************************************************//**
\brief restarts Application
******************************************************************************/
void restartApp(void);

#endif // _ZCLDEVICE_H
// eof zclDevice.h
