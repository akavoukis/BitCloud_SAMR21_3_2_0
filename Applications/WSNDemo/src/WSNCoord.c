/**********************************************************************//**
  \file WSNCoord.c

  \brief Contains subtask handler and functions related to coordinator.

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
    $Id: WSNCoord.c 27584 2015-01-09 14:45:42Z unithra.c $
**************************************************************************/
#ifdef _COORDINATOR_

/*****************************************************************************
                              Includes section
******************************************************************************/
#include <sysTypes.h>
#include <WSNVisualizer.h>
#include <WSNCommandHandler.h>
#include <WSNMessageSender.h>
#include <WSNCommand.h>

/*****************************************************************************
                              Prototypes section
******************************************************************************/
bool appCoordinatorIdentifyCmdHandler(AppCommand_t *pCommand);
bool appCoordinatorNwkInfoCmdHandler(AppCommand_t *pCommand);

/******************************************************************************
                              Constants section
******************************************************************************/
/**//**
 * \brief Command descriptor table. Is used by WSNCommandHandler.
 */
static PROGMEM_DECLARE(AppCommandDescriptor_t appCoordinatorCmdDescTable[]) =
{
  APP_COMMAND_DESCRIPTOR(APP_NETWORK_INFO_COMMAND_ID, appCoordinatorNwkInfoCmdHandler),
  APP_COMMAND_DESCRIPTOR(APP_IDENTIFY_COMMAND_ID, appCoordinatorIdentifyCmdHandler)
};

/*****************************************************************************
                              External variables section
******************************************************************************/
extern AppNwkInfoCmdPayload_t appNwkInfo;

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
static void appCoordinatorTaskHandler(void);
static void appCoordinatorInitialization(void);
static void appCoordinatorTaskReset(void);
static void appCoordinatorConfirmHandler(AppCmdHandlerTxFrame_t *txFrame);

/**************************************************************************//**
  \brief Coordinator application subtask handler.

  \return none
******************************************************************************/
static void appCoordinatorTaskHandler(void)
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
  \brief Initializes coordinator application subtask parameters.

  \return none
******************************************************************************/
static void appCoordinatorInitialization(void)
{
  appDeviceState = INITIAL_DEVICE_STATE;
}

/**************************************************************************//**
  \brief Resets coordinator task.

  \return none
******************************************************************************/
static void appCoordinatorTaskReset(void)
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
bool appCoordinatorNwkInfoCmdHandler(AppCommand_t *pCommand)
{
  visualizeSerialTx();
  appSendMessageToUsart(pCommand, sizeof(AppNwkInfoCmdPayload_t) + sizeof(pCommand->id));

  return true;
}

/**************************************************************************//**
  \brief Application identify command handler.

  \param[in] pCommand - pointer to application command.
  \return true if deletion is needed, false otherwise.
******************************************************************************/
bool appCoordinatorIdentifyCmdHandler(AppCommand_t *pCommand)
{
  bool delCmdNeeded = true;
  bool thisIsDestination = (pCommand->payload.identify.dstAddress == appNwkInfo.extAddr);

  if (thisIsDestination)
  {
    appStartIdentifyVisualization(pCommand->payload.identify.blinkDurationMs,
                                  pCommand->payload.identify.blinkPeriodMs);

    pCommand->id = APP_IDENTIFY_NOTF_COMMAND_ID;
    pCommand->payload.identifyNotf.status = APS_SUCCESS_STATUS;
    pCommand->payload.identifyNotf.srcAddress = appNwkInfo.extAddr;
    appSendMessageToUsart(pCommand, sizeof(AppIdentifyNotfPayload_t) + sizeof(pCommand->id));
    visualizeSerialTx();
  }
  else
  {
    APS_DataReq_t *pMsgParams = NULL;

    if (appCreateTxFrame(&pMsgParams, &pCommand, appCoordinatorConfirmHandler))
    {
      memset(pMsgParams, 0, sizeof(APS_DataReq_t));

      pMsgParams->profileId               = CCPU_TO_LE16(WSNDEMO_PROFILE_ID);
      pMsgParams->dstAddrMode             = APS_EXT_ADDRESS;
      pMsgParams->dstAddress.extAddress   = pCommand->payload.identify.dstAddress;
      pMsgParams->dstEndpoint             = 1;
      pMsgParams->clusterId               = CPU_TO_LE16(1);
      pMsgParams->srcEndpoint             = WSNDEMO_ENDPOINT;
      pMsgParams->asduLength              = sizeof(AppIdentifyReqPayload_t) + sizeof(pCommand->id);
      pMsgParams->txOptions.acknowledgedTransmission = 1;
#ifdef _APS_FRAGMENTATION_
      pMsgParams->txOptions.fragmentationPermitted = 1;
#endif
#ifdef _LINK_SECURITY_
      pMsgParams->txOptions.securityEnabledTransmission = 1;
#endif
      pMsgParams->radius                  = 0x0;
    }
    else
    {
      delCmdNeeded = false;
    }
  }

  return delCmdNeeded;
}

/**************************************************************************//**
  \brief Application transmission confirm handler.

  \param[in] pConfInfo - pointer to confirm information
  \return none
******************************************************************************/
static void appCoordinatorConfirmHandler(AppCmdHandlerTxFrame_t *txFrame)
{
  if (APP_IDENTIFY_COMMAND_ID == txFrame->cmdFrame.command.id)
  {
    AppCommand_t *pCommand = &txFrame->cmdFrame.command;

    pCommand->id = APP_IDENTIFY_NOTF_COMMAND_ID;
    pCommand->payload.identifyNotf.status = txFrame->msgParams.confirm.status;
    pCommand->payload.identifyNotf.srcAddress = txFrame->msgParams.dstAddress.extAddress;
    appSendMessageToUsart(pCommand, sizeof(AppIdentifyNotfPayload_t) + sizeof(pCommand->id));
    visualizeSerialTx();
  }
}

/**************************************************************************//**
  \brief Fills device interface structure with functions related to coordinator.

  \param[in, out] deviceInterface - pointer to device interface structure.
  \return none
******************************************************************************/
void appCoordinatorGetInterface(SpecialDeviceInterface_t *deviceInterface)
{
  deviceInterface->appDeviceCmdDescTable = appCoordinatorCmdDescTable;
  deviceInterface->appDeviceCmdDescTableSize = sizeof(appCoordinatorCmdDescTable);
  deviceInterface->appDeviceInitialization = appCoordinatorInitialization;
  deviceInterface->appDeviceTaskHandler = appCoordinatorTaskHandler;
  deviceInterface->appDeviceTaskReset = appCoordinatorTaskReset;
}

#endif
//eof WSNCoord.c
