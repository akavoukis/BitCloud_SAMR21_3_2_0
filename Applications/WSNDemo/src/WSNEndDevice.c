/**********************************************************************//**
  \file WSNEndDevice.c

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
    $Id: WSNEndDevice.c 27584 2015-01-09 14:45:42Z unithra.c $
**************************************************************************/
#ifdef _ENDDEVICE_

/*****************************************************************************
                              Includes section
******************************************************************************/
#include <WSNDemoApp.h>
#include <WSNVisualizer.h>
#include <WSNCommandHandler.h>
#include <WSNMessageSender.h>
#include <WSNCommand.h>
#include <sysIdleHandler.h>

/******************************************************************************
                              Defines section
******************************************************************************/
#define APP_TIMER_ENDDEVICE_SENDING_PERIOD         10000UL

/*****************************************************************************
                              Prototypes section
******************************************************************************/
bool appEndDeviceIdentifyCmdHandler(AppCommand_t *pCommand);
bool appEndDeviceNwkInfoCmdHandler(AppCommand_t *pCommand);

/******************************************************************************
                              Constants section
******************************************************************************/
/**//**
 * \brief Command descriptor table. Is used by WSNCommandHandler.
 */
static PROGMEM_DECLARE(AppCommandDescriptor_t appEndDeviceCmdDescTable[]) =
{
  APP_COMMAND_DESCRIPTOR(APP_NETWORK_INFO_COMMAND_ID, appEndDeviceNwkInfoCmdHandler),
  APP_COMMAND_DESCRIPTOR(APP_IDENTIFY_COMMAND_ID, appEndDeviceIdentifyCmdHandler)
};

/*****************************************************************************
                              External variables section
******************************************************************************/
extern AppNwkInfoCmdPayload_t appNwkInfo;
extern AppState_t appState;

/****************************************************************************
                              Static functions prototypes section
******************************************************************************/
static void appSensorsGot(void);
static void deviceTimerFired(void);
static void appEndDeviceTaskHandler(void);
static void appEndDeviceInitialization(void);
static void appEndDeviceTaskReset(void);

/*****************************************************************************
                              Local variables section
******************************************************************************/
static DeviceState_t  appDeviceState = INITIAL_DEVICE_STATE;
static HAL_AppTimer_t deviceTimer;

/******************************************************************************
                              Implementations section
******************************************************************************/
/**************************************************************************//**
  \brief End device application subtask handler.

  \return none
******************************************************************************/
static void appEndDeviceTaskHandler(void)
{
  switch (appDeviceState)
  {

    case READING_SENSORS_STATE:
    {
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
      HAL_StopAppTimer(&deviceTimer);
      deviceTimer.interval = APP_TIMER_ENDDEVICE_SENDING_PERIOD;
      deviceTimer.mode     = TIMER_ONE_SHOT_MODE;
      deviceTimer.callback = deviceTimerFired;

      appDeviceState = READING_SENSORS_STATE;
      appPostSubTaskTask();

#if defined(_SLEEP_WHEN_IDLE_)
      SYS_EnableSleepWhenIdle();
#endif
    }
    break;

    default:
    break;
  }
}

/**************************************************************************//**
  \brief Initializes end device application subtask parameters.

  \return none
******************************************************************************/
static void appEndDeviceInitialization(void)
{
  bool rxOnWhenIdleFlag = false;

  CS_WriteParameter(CS_RX_ON_WHEN_IDLE_ID, &rxOnWhenIdleFlag);
  appDeviceState = INITIAL_DEVICE_STATE;
}

/**************************************************************************//**
  \brief Resets end device subtask.

  \return none
******************************************************************************/
static void appEndDeviceTaskReset(void)
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
  appStopSensorManager();
  appDeviceState = SENDING_DEVICE_STATE;
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
bool appEndDeviceNwkInfoCmdHandler(AppCommand_t *pCommand)
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

  \param[in] pCommand - pointer to application command
  \return true if deletion is needed, false otherwise
******************************************************************************/
bool appEndDeviceIdentifyCmdHandler(AppCommand_t *pCommand)
{
  appStartIdentifyVisualization(pCommand->payload.identify.blinkDurationMs,
                                pCommand->payload.identify.blinkPeriodMs);

  return true;
}

/**************************************************************************//**
  \brief Fills device interface structure with functions related to coordinator.

  \param[in, out] deviceInterface - pointer to device interface structure
  \return none
******************************************************************************/
void appEndDeviceGetInterface(SpecialDeviceInterface_t *deviceInterface)
{
  deviceInterface->appDeviceCmdDescTable = appEndDeviceCmdDescTable;
  deviceInterface->appDeviceCmdDescTableSize = sizeof(appEndDeviceCmdDescTable);
  deviceInterface->appDeviceInitialization = appEndDeviceInitialization;
  deviceInterface->appDeviceTaskHandler = appEndDeviceTaskHandler;
  deviceInterface->appDeviceTaskReset = appEndDeviceTaskReset;
}

#endif
//eof WSNEndDevice.c
