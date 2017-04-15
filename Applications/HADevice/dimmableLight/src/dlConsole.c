/**************************************************************************//**
  \file dlConsole.c

  \brief
    Dimmable Light console implementation.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    19.12.2012 N.Fomin - Created
******************************************************************************/
#ifdef APP_DEVICE_TYPE_DIMMABLE_LIGHT
#if APP_ENABLE_CONSOLE == 1

/******************************************************************************
                    Includes section
******************************************************************************/
#include <uartManager.h>
#include <console.h>
#include <resetReason.h>
#include <zclDevice.h>
#include <sysUtils.h>
#include <pdsDataServer.h>
#include <zdo.h>
#include <zclDevice.h>
#include <ezModeManager.h>

/******************************************************************************
                    Defines section
******************************************************************************/
/* This value used in ZLL tests to identify non-ZLL Router */
#define TEST_DEVICE_TYPE_HA_ROUTER 0x03U

/******************************************************************************
                    Prototypes section
******************************************************************************/
static void processHelpCmd(const ScanValue_t *args);
static void processResetCmd(const ScanValue_t *args);
static void processInvokeEzModeCmd(const ScanValue_t *args);
static void processResetToFactoryFreshCmd(const ScanValue_t *args);
static void processGetDeviceTypeCmd(const ScanValue_t *args);
static void processPseudoPowerOffCmd(const ScanValue_t *args);
static void processSetPermitJoinCmd(const ScanValue_t *args);
static void processRestartNwkCmd(const ScanValue_t *args);
static void zdoPermitJoiningResponse(ZDO_ZdpResp_t *resp);

/******************************************************************************
                    Local variables section
******************************************************************************/
static ZDO_ZdpReq_t zdpReq;
static uint8_t readBuffer[USART_RX_BUFFER_LENGTH];
static const ConsoleCommand_t cmds[] =
{
  {"help",   "", processHelpCmd, "->Show help you're reading now:  help\r\n"},
  {"reset", "", processResetCmd, "->Reset device\r\n"},
  {"invokeEZMode", "", processInvokeEzModeCmd, "->Start finding and binding process\r\n"},
  {"resetToFN", "", processResetToFactoryFreshCmd, "->Reset to factory fresh settings: resetToFN\r\n"},
  {"getDeviceType", "", processGetDeviceTypeCmd, "-> Request for device type: getDeviceType\r\n"},
  {"powerOff", "", processPseudoPowerOffCmd, "-> Powers off device: powerOff\r\n"},
  {"setPermitJoin", "d", processSetPermitJoinCmd, "-> Sets Permit Join: setPermitJoin [dur]\r\n"},
  {"restartNwk", "d", processRestartNwkCmd, "-> Restarts network on particular channel [channel]\r\n"},
  {0,0,0,0},
};

/******************************************************************************
                    Implementation section
******************************************************************************/
/**************************************************************************//**
\brief Sends single char to serial interface
******************************************************************************/
void consoleTx(char chr)
{
  appSnprintf(&chr);
}

/**************************************************************************//**
\brief Processes single char read from serial interface

\param[in] char - read char
******************************************************************************/
void consoleTxStr(const char *str)
{
  appSnprintf(str);
}

/**************************************************************************//**
\brief Initializes console
******************************************************************************/
void initConsole(void)
{
  consoleRegisterCommands(cmds);
}

/**************************************************************************//**
\brief Processes data received by console
******************************************************************************/
void processConsole(uint16_t length)
{
  int8_t bytesRead = readDataFromUart(readBuffer, MIN(USART_RX_BUFFER_LENGTH, length));

  for (int8_t i = 0; i < bytesRead; i++)
    consoleRx(readBuffer[i]);
}

/**************************************************************************//**
\brief Processes help command

\param[in] args - array of command arguments
******************************************************************************/
static void processHelpCmd(const ScanValue_t *args)
{
  (void)args;

  LOG_STRING(commandStr, "Commands: \r\n");
  appSnprintf(commandStr);
  for (const ConsoleCommand_t *cmd = cmds; cmd->name; cmd++)
    appSnprintf("%s\r\n", cmd->name);
}

/**************************************************************************//**
\brief Processes reset command: reset device

\param[in] args - array of command arguments
******************************************************************************/
static void processResetCmd(const ScanValue_t *args)
{
  (void)args;

  HAL_WarmReset();
}

/**************************************************************************//**
\brief Processes start finding and binding command

\param[in] args - array of command arguments
******************************************************************************/
static void processInvokeEzModeCmd(const ScanValue_t *args)
{
  (void)args;
  invokeEzMode(NULL);
}

/**************************************************************************//**
\brief Processes reset to factory fresh

\param[in] args - array of command arguments
******************************************************************************/
static void processResetToFactoryFreshCmd(const ScanValue_t *args)
{
  (void)args;
  PDS_DeleteAll(false);

  HAL_WarmReset();
}

/**************************************************************************//**
\brief Processes request for device type obtaining

\param[in] args - array of command arguments
******************************************************************************/
static void processGetDeviceTypeCmd(const ScanValue_t *args)
{
  LOG_STRING(deviceFnStatusStr, "DeviceType = %d\r\n");
  appSnprintf(deviceFnStatusStr, TEST_DEVICE_TYPE_HA_ROUTER);
  (void)args;
}

/**************************************************************************//**
\brief Processes pseudo power off command

\param[in] args - array of command arguments
******************************************************************************/
static void processPseudoPowerOffCmd(const ScanValue_t *args)
{
  /* Disable BitCloud tasks for preventing calls to the radio.
     HAL is enabled so it it allows to receive commands through UART. */
  SYS_DisableTask(ZDO_TASK_ID);
  SYS_DisableTask(APS_TASK_ID);
  SYS_DisableTask(NWK_TASK_ID);
  SYS_DisableTask(MAC_PHY_HWD_TASK_ID);
  (void)args;
}

/**************************************************************************//**
\brief Processes Set Permit Join command

\param[in] args - array of command arguments
******************************************************************************/
static void processSetPermitJoinCmd(const ScanValue_t *args)
{
  ZDO_MgmtPermitJoiningReq_t *permit = &zdpReq.req.reqPayload.mgmtPermitJoiningReq;

  zdpReq.ZDO_ZdpResp = zdoPermitJoiningResponse;
  zdpReq.reqCluster = MGMT_PERMIT_JOINING_CLID;
  zdpReq.dstAddrMode = APS_SHORT_ADDRESS;

  zdpReq.dstAddress.shortAddress = NWK_GetShortAddr();

  permit->permitDuration = args[0].uint8;
  permit->tcSignificance = 0x01;

  ZDO_ZdpReq(&zdpReq);
}

/**************************************************************************//**
\brief ZDP device announce response callback

\param[in] leaveResp - pointer to response structure
******************************************************************************/
static void zdoPermitJoiningResponse(ZDO_ZdpResp_t *resp)
{
  LOG_STRING(permitJoinDoneStr, "setPermitJoinRsp %d\r\n");
  appSnprintf(permitJoinDoneStr, resp->respPayload.status);
}

/**************************************************************************//**
\brief Processes Restart Network command

\param[in] args - array of command arguments
******************************************************************************/
static void processRestartNwkCmd(const ScanValue_t *args)
{
  CS_WriteParameter(CS_CHANNEL_MASK_ID, &(uint32_t){1ul << args[0].uint8});

  appRestart(false);
}
#endif // APP_ENABLE_CONSOLE == 1
#endif // APP_DEVICE_TYPE_DIMMABLE_LIGHT

// eof dlConsole.c
