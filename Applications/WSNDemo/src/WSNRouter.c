/**********************************************************************//**
  \file WSNRouter.c

  \brief

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:
    13/06/07 I. Kalganova - Modified
    15/03/12 D. Kolmakov - Refactored

  Last change:
    $Id: WSNRouter.c 27584 2015-01-09 14:45:42Z unithra.c $
**************************************************************************/
#ifdef _ROUTER_

/*****************************************************************************
                              Includes section
******************************************************************************/
#include <WSNDemoApp.h>
#include <WSNVisualizer.h>
#include <WSNCommandHandler.h>
#include <WSNMessageSender.h>
#include <WSNCommand.h>

/*****************************************************************************
                              Prototypes section
******************************************************************************/
bool appRouterIdentifyCmdHandler(AppCommand_t *pCommand);
bool appRouterNwkInfoCmdHandler(AppCommand_t *pCommand);

/******************************************************************************
                              Constants section
******************************************************************************/
/**//**
 * \brief Command descriptor table. Is used by WSNCommandHandler.
 */
static PROGMEM_DECLARE(AppCommandDescriptor_t appRouterCmdDescTable[]) =
{
  APP_COMMAND_DESCRIPTOR(APP_NETWORK_INFO_COMMAND_ID, appRouterNwkInfoCmdHandler),
  APP_COMMAND_DESCRIPTOR(APP_IDENTIFY_COMMAND_ID, appRouterIdentifyCmdHandler)
};

/*****************************************************************************
                              External variables section
******************************************************************************/
extern AppNwkInfoCmdPayload_t appNwkInfo;
extern AppState_t appState;

/*****************************************************************************
                              Local variables section
******************************************************************************/
static HAL_AppTimer_t deviceTimer;
static DeviceState_t  appDeviceState = INITIAL_DEVICE_STATE;

/****************************************************************************
                              Static functions prototypes section
******************************************************************************/
static void deviceTimerFired(void);
static void appSensorsGot(void);
static void appRouterTaskHandler(void);
static void appRouterInitialization(void);
static void appRouterTaskReset(void);

/******************************************************************************
                              Implementations section
******************************************************************************/
/**************************************************************************//**
  \brief Router application subtask handler.

  \return none
******************************************************************************/
static void appRouterTaskHandler(void)
{
  switch (appDeviceState)
  {
    case READING_SENSORS_STATE:
    {
      appNwkInfo.parentShortAddr = NWK_GetNextHop(0x0000);
      appReadLqiRssi();
      appStartSensorManager();
      appGetSensorData(appSensorsGot);
    }
    break;

    case SENDING_DEVICE_STATE:
    {
      AppCommand_t *pCommand = NULL;

      if (appCreateCommand(&pCommand))
      {
        pCommand->id = APP_NETWORK_INFO_COMMAND_ID;
        memcpy(&pCommand->payload.nwkInfo, &appNwkInfo, sizeof(AppNwkInfoCmdPayload_t));
      }

      appDeviceState = STARTING_TIMER_STATE;
      appPostSubTaskTask();
    }
    break;

    case STARTING_TIMER_STATE:
    {
      HAL_StartAppTimer(&deviceTimer);
    }
    break;

    case INITIAL_DEVICE_STATE:
    {
      HAL_StopAppTimer(&deviceTimer); // Have to be stopped before start
      deviceTimer.interval = APP_TIMER_SENDING_PERIOD;
      deviceTimer.mode     = TIMER_ONE_SHOT_MODE;
      deviceTimer.callback = deviceTimerFired;

      appDeviceState = READING_SENSORS_STATE;
      appPostSubTaskTask();
    }
    break;

    default:
      break;
  }
}

/**************************************************************************//**
  \brief Initializes router application subtask parameters.

  \return none
******************************************************************************/
static void appRouterInitialization(void)
{
  appDeviceState = INITIAL_DEVICE_STATE;
}

/**************************************************************************//**
  \brief Resets router subtask.

  \return none
******************************************************************************/
static void appRouterTaskReset(void)
{
  appDeviceState = INITIAL_DEVICE_STATE;
  appPostSubTaskTask();
}

/**************************************************************************//**
  \brief Sensors reading done callback.

  \return none
******************************************************************************/
static void appSensorsGot(void)
{
  appDeviceState = SENDING_DEVICE_STATE;
  appStopSensorManager();
  appPostSubTaskTask();
}

/**************************************************************************//**
  \brief Device timer event.

  \return none
******************************************************************************/
static void deviceTimerFired(void)
{
  appDeviceState = READING_SENSORS_STATE;
  appPostSubTaskTask();
}

/**************************************************************************//**
  \brief Application network info command handler.

  \param[in] pCommand - pointer to application command.

  \return true if deletion is needed, false otherwise.
******************************************************************************/
bool appRouterNwkInfoCmdHandler(AppCommand_t *pCommand)
{
  APS_DataReq_t *pMsgParams = NULL;

  if (appCreateTxFrame(&pMsgParams, &pCommand, NULL))
  {
    memset(pMsgParams, 0, sizeof(APS_DataReq_t));

    pMsgParams->profileId               = CCPU_TO_LE16(WSNDEMO_PROFILE_ID);
    pMsgParams->dstAddrMode             = APS_SHORT_ADDRESS;
    pMsgParams->dstAddress.shortAddress = CPU_TO_LE16(0);
    pMsgParams->dstEndpoint             = 1;
    pMsgParams->clusterId               = CPU_TO_LE16(1);
    pMsgParams->srcEndpoint             = WSNDEMO_ENDPOINT;
    pMsgParams->asduLength              = sizeof(AppNwkInfoCmdPayload_t) + sizeof(pCommand->id);
    pMsgParams->txOptions.acknowledgedTransmission = 1;
#ifdef _APS_FRAGMENTATION_
    pMsgParams->txOptions.fragmentationPermitted = 1;
#endif
#ifdef _LINK_SECURITY_
    pMsgParams->txOptions.securityEnabledTransmission = 1;
#endif
    pMsgParams->radius                  = 0x0;
  }

  return true;
}

/**************************************************************************//**
  \brief Application identify command handler.

  \param[in] pCommand - pointer to application command.

  \return true if deletion is needed, false otherwise.
******************************************************************************/
bool appRouterIdentifyCmdHandler(AppCommand_t *pCommand)
{
  appStartIdentifyVisualization(pCommand->payload.identify.blinkDurationMs,
                                pCommand->payload.identify.blinkPeriodMs);

  return true;
}

/**************************************************************************//**
  \brief Fills device interface structure with functions related to coordinator.

  \param[in, out] deviceInterface - pointer to device interface structure.

  \return none
******************************************************************************/
void appRouterGetInterface(SpecialDeviceInterface_t *deviceInterface)
{
  deviceInterface->appDeviceCmdDescTable = appRouterCmdDescTable;
  deviceInterface->appDeviceCmdDescTableSize = sizeof(appRouterCmdDescTable);
  deviceInterface->appDeviceInitialization = appRouterInitialization;
  deviceInterface->appDeviceTaskHandler = appRouterTaskHandler;
  deviceInterface->appDeviceTaskReset = appRouterTaskReset;
}

#endif
//eof WSNRouter.c
