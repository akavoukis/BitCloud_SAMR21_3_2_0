/**************************************************************************//**
  \file iasACEConsole.c

  \brief
    IAS ACE console implementation.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    18/11/2014 Yogesh - Created
******************************************************************************/
#ifdef APP_DEVICE_TYPE_IAS_ACE
#if APP_ENABLE_CONSOLE == 1

/******************************************************************************
                    Includes section
******************************************************************************/
#include <uartManager.h>
#include <console.h>
#include <iasACEZoneCluster.h>
#include <iasACECluster.h>
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
#define TEMPERATURE_SCALE 100
/******************************************************************************
                    Types section
******************************************************************************/

/******************************************************************************
                    Prototypes section
******************************************************************************/
static void processHelpCmd(const ScanValue_t *args);
static void processResetCmd(const ScanValue_t *args);
static void processInvokeEzModeCmd(const ScanValue_t *args);
static void processResetToFactoryFreshCmd(const ScanValue_t *args);
static void processGetDeviceTypeCmd(const ScanValue_t *args);
static void processPseudoPowerOffCmd(const ScanValue_t *args);
static void processRestartNwkCmd(const ScanValue_t *args);
static void processGetNetworkAddressCmd(const ScanValue_t *args);
static void processZoneEnrollRequestCommand(const ScanValue_t *args);
static void processZoneStatusChangeNotificationCommand(const ScanValue_t *args);
static APS_AddrMode_t determineAddressMode(const ScanValue_t *args);
static void processIASACEArmCommand(const ScanValue_t *args);
static void processIASACEBypassCommand(const ScanValue_t *args);
static void processIASACEEmergencyommand(const ScanValue_t *args);
static void processIASACEFireCommand(const ScanValue_t *args);
static void processIASACEPanicCommand(const ScanValue_t *args);
static void processIASACEGetZoneIdMapCommand(const ScanValue_t *args);
static void processIASACEGetZoneIdInformationCommand(const ScanValue_t *args);
static void processZoneEnrollRequestCommand(const ScanValue_t *args);
static void processZoneStatusChangeNotificationCommand(const ScanValue_t *args);
static void processZoneStatusChangeCommand(const ScanValue_t *args);
static void processIASACEGetPanelStatusCommand(const ScanValue_t *args);
static void processIASACEGetZoneStatusCommand(const ScanValue_t *args);
static void processGetByPassZoneListCommand(const ScanValue_t *args);

/******************************************************************************
                    Local variables section
******************************************************************************/
static uint8_t readBuffer[USART_RX_BUFFER_LENGTH];
static const ConsoleCommand_t cmds[] =
{
  {"help",   "", processHelpCmd, "->Show help you're reading now:  help\r\n"},
  {"reset", "", processResetCmd, "->Reset device\r\n"},
  {"getNetworkAddress", "", processGetNetworkAddressCmd, "-> Returns network address: getNetworkAddress\r\n"},
  {"invokeEZMode", "", processInvokeEzModeCmd, "->Start finding and binding process\r\n"},
  {"resetToFN", "", processResetToFactoryFreshCmd, "->Reset to factory fresh settings: resetToFN\r\n"},
  {"getDeviceType", "", processGetDeviceTypeCmd, "-> Request for device type: getDeviceType\r\n"},
  {"powerOff", "", processPseudoPowerOffCmd, "-> Powers off device: powerOff\r\n"},
  {"IASACEArmCommand", "sdddsd", processIASACEArmCommand,
    "Sends IASACEAlarmCommand: [addrMode][addr][ep][ArmMode][Arm/Code][ZoneId]\r\n"},
  {"IASACEBypassCommand", "sdddddds", processIASACEBypassCommand,
  "Sends IASACEBypassCommand: [addrMode][addr][ep][zone_numbers][zone_id1][zone_id2][zone_id3][arm_code_code]\r\n"},
  {"IASACEEmergencyCommand", "sdd", processIASACEEmergencyommand,
    "Sends IASACEEmergencyCommand: [addrMode][addr][ep]\r\n"},
  {"IASACEFireCommand", "sdd", processIASACEFireCommand,
    "Sends IASACEFireCommand: [addrMode][addr][ep]\r\n"},
  {"IASACEPanicCommand", "sdd", processIASACEPanicCommand,
    "Sends IASACEPanicCommand: [addrMode][addr][ep]\r\n"},
  {"IASACEGetZoneIdMapCommand", "sdd", processIASACEGetZoneIdMapCommand,
    "Sends IASACEGetZoneIdMapCommand: [addrMode][addr][ep]\r\n"},
  {"IASACEGetZoneIdInformationCommand", "sddd", processIASACEGetZoneIdInformationCommand,
    "Sends IASACEGetZoneIdInformationCommand: [addrMode][addr][ep][zone_id]\r\n"},
  {"IASACEGetPanelStatusCommand", "sdd", processIASACEGetPanelStatusCommand,
    "Sends IASACEIASACEPanelStatusChangeCommand: [addrMode][addr][ep]\r\n"},
  {"IASACEGetZoneStatusCommand", "sdddddd", processIASACEGetZoneStatusCommand,
    "Sends IASACEZoneStatusChangeCommand: [addrMode][addr][ep][starting_zone_id][max_number_zoneids][zonestatus_maskflag][zonestatus_mask]\r\n"},
  {"ZoneEnrollReqCmd", "sdddd", processZoneEnrollRequestCommand,
    "Sends ZoneEnrollRequestCommand: [addrMode][addr][ep][zonetype][manuf_code]\r\n"},
  {"ZoneStatusChangeNotifiCmd", "sdddd", processZoneStatusChangeNotificationCommand,
    "Sends ZoneStatusChangeNotification Command: [addrMode][addr][ep][zonestatus][ext_status]\r\n"},
  {"ZoneStatusChange", "d", processZoneStatusChangeCommand,
    "Chnges Internal Zone Status to Initiate Notifications: [Device_Spec_Bits]\r\n"},
  {"GetByPassZoneList", "sdd", processGetByPassZoneListCommand,
    "To get the list of bypass zones: [addrMode][addr][ep]\r\n"},
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
\brief Processes get network address command

\param[in] args - array of command arguments
******************************************************************************/
static void processGetNetworkAddressCmd(const ScanValue_t *args)
{
  (void)args;
  appSnprintf("%04x\r\n", NWK_GetShortAddr());
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
\brief Processes Restart Network command

\param[in] args - array of command arguments
******************************************************************************/
static void processRestartNwkCmd(const ScanValue_t *args)
{
  CS_WriteParameter(CS_CHANNEL_MASK_ID, &(uint32_t){1ul << args[0].uint8});

  appRestart(false);
}


/**************************************************************************//**
\brief Processes Restart Network command

\param[in] args - array of command arguments
******************************************************************************/
static void processZoneEnrollRequestCommand(const ScanValue_t *args)
{
  zoneEnrollRequestCommand(determineAddressMode(args), args[1].uint16, args[2].uint8, args[3].uint16,args[4].uint16);

}

/**************************************************************************//**
\brief Processes Restart Network command

\param[in] args - array of command arguments
******************************************************************************/
static void processZoneStatusChangeNotificationCommand(const ScanValue_t *args)
{
  zoneStatusChangeNotificationCommand(determineAddressMode(args), args[1].uint16, args[2].uint8, args[3].uint16, args[4].uint8);
}

/**************************************************************************//**
\brief Determines address mode for command

\param[in] arg - pointer to command argument with address mode string

\returns address mode
******************************************************************************/
static APS_AddrMode_t determineAddressMode(const ScanValue_t *arg)
{
  if (!memcmp("-g", arg->str, 2))
    return APS_GROUP_ADDRESS;

  if (!memcmp("-b", arg->str, 2))
    return APS_NO_ADDRESS;

  return APS_SHORT_ADDRESS;
}

/**************************************************************************//**
\brief ACE Client Commands

\param[in] arg - pointer to command argument with address mode string

\returns address mode
******************************************************************************/
static void processIASACEArmCommand(const ScanValue_t *args)
{
  aceArmCommand(determineAddressMode(args), args[1].uint16, args[2].uint8, args[3].uint8, args[4].str, args[5].uint8);
}

/**************************************************************************//**
\brief ACE Client Commands

\param[in] arg - pointer to command argument with address mode string

\returns address mode
******************************************************************************/
static void processIASACEBypassCommand(const ScanValue_t *args)
{
  aceByPassCommand(determineAddressMode(args), args[1].uint16, args[2].uint8, args[3].uint8, args[4].uint8, args[5].uint8,  args[6].uint8, args[7].str);
}

/**************************************************************************//**
\brief ACE Client Commands

\param[in] arg - pointer to command argument with address mode string

\returns address mode
******************************************************************************/
static void processIASACEEmergencyommand(const ScanValue_t *args)
{
  aceEmergencyCommand(determineAddressMode(args), args[1].uint16, args[2].uint8);
}

/**************************************************************************//**
\brief ACE Client Commands

\param[in] arg - pointer to command argument with address mode string

\returns address mode
******************************************************************************/
static void processIASACEFireCommand(const ScanValue_t *args)
{
  aceFireCommand(determineAddressMode(args), args[1].uint16, args[2].uint8);
}
/**************************************************************************//**
\brief ACE Client Commands

\param[in] arg - pointer to command argument with address mode string

\returns address mode
******************************************************************************/
static void processIASACEPanicCommand(const ScanValue_t *args)
{
  acePanicCommand(determineAddressMode(args), args[1].uint16, args[2].uint8);
}

/**************************************************************************//**
\brief ACE Client Commands

\param[in] arg - pointer to command argument with address mode string

\returns address mode
******************************************************************************/
static void processIASACEGetZoneIdMapCommand(const ScanValue_t *args)
{
  aceGetZoneIdMapCommand(determineAddressMode(args), args[1].uint16, args[2].uint8);
}

/**************************************************************************//**
\brief ACE Client Commands

\param[in] arg - pointer to command argument with address mode string

\returns address mode
******************************************************************************/
static void processIASACEGetZoneIdInformationCommand(const ScanValue_t *args)
{
  aceGetZoneInformationCommand(determineAddressMode(args), args[1].uint16, args[2].uint8, args[3].uint8);
}

/**************************************************************************//**
\brief ACE Client Commands

\param[in] arg - pointer to command argument with address mode string

\returns address mode
******************************************************************************/
static void processZoneStatusChangeCommand(const ScanValue_t *args)
{
  zoneStatusChangeCommand(args[0].uint16);
}

/**************************************************************************//**
\brief ACE Client Commands

\param[in] arg - pointer to command argument with address mode string

\returns address mode
******************************************************************************/
static void processIASACEGetPanelStatusCommand(const ScanValue_t *args)
{
  aceGetPanelStatusCommand(determineAddressMode(args), args[1].uint16, args[2].uint8);
}

/**************************************************************************//**
\brief ACE Client Commands

\param[in] arg - pointer to command argument with address mode string

\returns address mode
******************************************************************************/
static void processIASACEGetZoneStatusCommand(const ScanValue_t *args)
{
  aceGetZoneStatusCommand(determineAddressMode(args), args[1].uint16, args[2].uint8, args[3].uint8, args[4].uint8, args[5].uint8, args[6].uint16);
}

/**************************************************************************//**
\brief ACE Client Commands

\param[in] arg - pointer to command argument with address mode string

\returns address mode
******************************************************************************/
static void processGetByPassZoneListCommand(const ScanValue_t *args)
{
  getByPassZoneListCommand(determineAddressMode(args), args[1].uint16, args[2].uint8);
}
#endif // APP_ENABLE_CONSOLE == 1
#endif // APP_DEVICE_TYPE_IAS_ZONE

// eof iasACEConsole.c
