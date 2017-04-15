/**************************************************************************//**
  \file dsConsole.c

  \brief
    Dimmer Switch console implementation.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    13.12.2012 N.Fomin - Created
******************************************************************************/
#ifdef APP_DEVICE_TYPE_DIMMER_SWITCH
#if APP_ENABLE_CONSOLE == 1

/******************************************************************************
                    Includes section
******************************************************************************/
#include <uartManager.h>
#include <console.h>
#include <dsOnOffCluster.h>
#include <dsLevelControlCluster.h>
#include <dsPowerConfigurationCluster.h>
#include <resetReason.h>
#include <zclDevice.h>
#include <pdsDataServer.h>
#include <ezModeManager.h>

/* This value used in ZLL tests to identify non-ZLL EndDevice */
#define TEST_DEVICE_TYPE_HA_END_DEVICE 0x04U

/******************************************************************************
                    Prototypes section
******************************************************************************/
static void processHelpCmd(const ScanValue_t *args);
static void processResetCmd(const ScanValue_t *args);
static void processInvokeEzModeCmd(const ScanValue_t *args);
static void processOnOffToggleCmd(const ScanValue_t *args);
static void processMoveToLevelCmd(const ScanValue_t *args);
static void processMoveCmd(const ScanValue_t *args);
static void processStepCmd(const ScanValue_t *args);
static void processStopCmd(const ScanValue_t *args);
static void processGetDeviceTypeCmd(const ScanValue_t *args);
static void processResetToFactoryFreshCmd(const ScanValue_t *args);
static void processPseudoPowerOffCmd(const ScanValue_t *args);
static APS_AddrMode_t determineAddressMode(const ScanValue_t *arg);
static void processRestartNwkCmd(const ScanValue_t *args);
static void processGetNetworkAddressCmd(const ScanValue_t *args);
#if (APP_ENABLE_CERTIFICATION_EXTENSION == 0)
static void processSetBatteryVoltage(const ScanValue_t *args);
static void processSetBatteryPercentage(const ScanValue_t *args);
static void processSetBatteryVoltageMinThreshold(const ScanValue_t *args);
static void processSetBatteryVoltageThresholdOne(const ScanValue_t *args);
static void processSetBatteryVoltageThresholdTwo(const ScanValue_t *args);
static void processSetBatteryVoltageThresholdThree(const ScanValue_t *args);
static void processSetBatteryPercentageMinThreshold(const ScanValue_t *args);
static void processSetBatteryPercentageThresholdOne(const ScanValue_t *args);
static void processSetBatteryPercentageThresholdTwo(const ScanValue_t *args);
static void processSetBatteryPercentageThresholdThree(const ScanValue_t *args);
static void processSetBatteryAlarmMask(const ScanValue_t *args);
static void processReadBatteryVoltage(const ScanValue_t *args);
static void processReadBatteryPercentage(const ScanValue_t *args);
static void processReadBatteryVoltageMinThreshold(const ScanValue_t *args);
static void processReadBatteryVoltageThresholdOne(const ScanValue_t *args);
static void processReadBatteryVoltageThresholdTwo(const ScanValue_t *args);
static void processReadBatteryVoltageThresholdThree(const ScanValue_t *args);
static void processReadBatteryPercentageMinThreshold(const ScanValue_t *args);
static void processReadBatteryPercentageThresholdOne(const ScanValue_t *args);
static void processReadBatteryPercentageThresholdTwo(const ScanValue_t *args);
static void processReadBatteryPercentageThresholdThree(const ScanValue_t *args);
static void processReadBatteryAlarmMask(const ScanValue_t *args);
static void processReadBatteryAlarmState(const ScanValue_t *args);
static void processResetBatteryState(const ScanValue_t *args);
#endif

/******************************************************************************
                    Local variables section
******************************************************************************/
static uint8_t readBuffer[USART_RX_BUFFER_LENGTH];
static const ConsoleCommand_t cmds[] =
{
  {"help", "",processHelpCmd, "->Show help you're reading now:  help\r\n"},
  {"reset", "", processResetCmd, "->Reset device\r\n"},
  {"getDeviceType", "", processGetDeviceTypeCmd, "-> Request for device type: getDeviceType\r\n"},
  {"powerOff", "", processPseudoPowerOffCmd, "-> Powers off device: powerOff\r\n"},
  {"invokeEZMode", "", processInvokeEzModeCmd, "->Start finding and binding process\r\n"},
  {"onOff", "sdds", processOnOffToggleCmd,
    "Sends On/Off command: onOff [addrMode][addr][ep][onOff: -on for On, -off for Off]\r\n"},
  {"moveToLevel", "sddddd", processMoveToLevelCmd,
    "->Send Move To Level (with On/Off) command: moveToLevel [addrMode][addr][ep][level][transitionTime][onOff]\r\n"},
  {"move", "sddddd", processMoveCmd,
    "->Send Move (with On/Off) command: move [addrMode][addr][ep][mode][rate][onOff]\r\n"},
  {"step", "sdddddd", processStepCmd,
    "->Send Step (with On/Off) command: step [addrMode][addr][ep][mode][stepSize][transitionTime][onOff]\r\n"},
  {"stop", "sddd", processStopCmd, "->Send Stop (with On/Off) command: stop [addrMode][addr][ep][onOff]\r\n"},
  {"resetToFN", "", processResetToFactoryFreshCmd, "->Reset to factory fresh settings: resetToFN\r\n"},
  {"getNetworkAddress", "", processGetNetworkAddressCmd, "-> Returns network address: getNetworkAddress\r\n"},
  {"restartNwk", "d", processRestartNwkCmd, "-> Restarts network on particular channel [channel]\r\n"},
#if (APP_ENABLE_CERTIFICATION_EXTENSION == 0)
  {"setBattVolt", "d", processSetBatteryVoltage, "-> Sets Battery Voltage: setBattVolt [volt]\r\n"},
  {"setBattPer", "d", processSetBatteryPercentage, "-> Sets Battery Percentage: setBattPer [per]\r\n"},
  {"setBattAlarmMask", "d", processSetBatteryAlarmMask, "-> Sets Battery Alarm Mask: setBattAlarmMask [mask]\r\n"},
  {"setBattVoltMinTh", "d", processSetBatteryVoltageMinThreshold, "-> Sets Battery Voltage Min Threshold: setBattVoltMinTh [volt]\r\n"},
  {"setBattVoltThOne", "d", processSetBatteryVoltageThresholdOne, "-> Sets Battery Voltage Threshold One: setBattVoltThOne [volt]\r\n"},
  {"setBattVoltThTwo", "d", processSetBatteryVoltageThresholdTwo, "-> Sets Battery Voltage Threshold Two: setBattVoltThTwo [volt]\r\n"},
  {"setBattVoltThThree", "d", processSetBatteryVoltageThresholdThree, "-> Sets Battery Voltage Threshold Three: setBattVoltThThree [volt]\r\n"},
  {"setBattPerMinTh", "d", processSetBatteryPercentageMinThreshold, "-> Sets Battery Voltage Min Threshold: setBattPerMinTh [per]\r\n"},
  {"setBattPerThOne", "d", processSetBatteryPercentageThresholdOne, "-> Sets Battery Voltage Threshold One: setBattPerThOne [per]\r\n"},
  {"setBattPerThTwo", "d", processSetBatteryPercentageThresholdTwo, "-> Sets Battery Voltage Threshold Two: setBattPerThTwo [per]\r\n"},
  {"setBattPerThThree", "d", processSetBatteryPercentageThresholdThree, "-> Sets Battery Voltage Threshold Three: setBattPerThThree [per]\r\n"},
  {"readBattVoltMinTh", "", processReadBatteryVoltageMinThreshold, "-> Reads Battery Voltage Min Threshold: readBattVoltMinTh [volt]\r\n"},
  {"readBattVoltThOne", "", processReadBatteryVoltageThresholdOne, "-> Reads Battery Voltage Threshold One: readBattVoltThOne [volt]\r\n"},
  {"readBattVoltThTwo", "", processReadBatteryVoltageThresholdTwo, "-> Reads Battery Voltage Threshold Two: readBattVoltThTwo [volt]\r\n"},
  {"readBattVoltThThree", "", processReadBatteryVoltageThresholdThree, "-> Reads Battery Voltage Threshold Three: readBattVoltThThree [volt]\r\n"},
  {"readBattPerMinTh", "", processReadBatteryPercentageMinThreshold, "-> Reads Battery Voltage Min Threshold: readBattPerMinTh [per]\r\n"},
  {"readBattPerThOne", "", processReadBatteryPercentageThresholdOne, "-> Reads Battery Voltage Threshold One: readBattPerThOne [per]\r\n"},
  {"readBattPerThTwo", "", processReadBatteryPercentageThresholdTwo, "-> Reads Battery Voltage Threshold Two: readBattPerThTwo [per]\r\n"},
  {"readBattPerThThree", "", processReadBatteryPercentageThresholdThree, "-> Reads Battery Voltage Threshold Three: readBattPerThThree [per]\r\n"},
  {"readBattAlarmMask", "", processReadBatteryAlarmMask, "-> Reads Battery Alarm Mask: readBattAlarmMask [mask]\r\n"},
  {"readBattAlarmState", "", processReadBatteryAlarmState, "-> Reads Battery Alarm State: readBattAlarmState [state]\r\n"},
  {"resetBattState", "", processResetBatteryState, "-> Resets Battery State: resetBattState [state]\r\n"},
  {"readBattVolt", "", processReadBatteryVoltage, "-> Reads Battery Voltage: readBattPerMinTh [volts]\r\n"},
  {"readBattPer", "", processReadBatteryPercentage, "-> Reads Battery Percentage: readBattPerMinTh [per]\r\n"},
#endif
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
\brief Processes request for device type obtaining

\param[in] args - array of command arguments
******************************************************************************/
static void processGetDeviceTypeCmd(const ScanValue_t *args)
{
  LOG_STRING(deviceFnStatusStr, "DeviceType = %d\r\n");
  appSnprintf(deviceFnStatusStr, TEST_DEVICE_TYPE_HA_END_DEVICE);
  (void)args;
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
\brief Processes On/Off/Toggle command

\param[in] args - array of command arguments
******************************************************************************/
static void processOnOffToggleCmd(const ScanValue_t *args)
{
  uint8_t command;

  if (!memcmp("-on", args[3].str, 3))
    command = 1;
  else if (!memcmp("-toggle", args[3].str, 7))
    command = 2;
  else
    command = 0;

  onOffSendOnOffToggle(determineAddressMode(args), args[1].uint16, args[2].uint8, command);
}

/**************************************************************************//**
\brief Processes Move to level command

\param[in] args - array of command arguments
******************************************************************************/
static void processMoveToLevelCmd(const ScanValue_t *args)
{
  levelControlSendMoveToLevel(determineAddressMode(args), args[1].uint16, args[2].uint8,
    args[3].uint8, args[4].uint16, args[5].uint8);
}

/**************************************************************************//**
\brief Processes Move command

\param[in] args - array of command arguments
******************************************************************************/
static void processMoveCmd(const ScanValue_t *args)
{
  levelControlSendMove(determineAddressMode(args), args[1].uint16, args[2].uint8,
    args[3].uint8, args[4].uint8, args[5].uint8);
}

/**************************************************************************//**
\brief Processes Step command

\param[in] args - array of command arguments
******************************************************************************/
static void processStepCmd(const ScanValue_t *args)
{
  levelControlSendStep(determineAddressMode(args), args[1].uint16, args[2].uint8,
    args[3].uint8, args[4].uint8, args[5].uint16, args[6].uint8);
}

/**************************************************************************//**
\brief Processes Stop command

\param[in] args - array of command arguments
******************************************************************************/
static void processStopCmd(const ScanValue_t *args)
{
  levelControlSendStop(determineAddressMode(args), args[1].uint16, args[2].uint8,
    args[3].uint8);
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
\brief Processes get network address command

\param[in] args - array of command arguments
******************************************************************************/
static void processGetNetworkAddressCmd(const ScanValue_t *args)
{
  (void)args;
  appSnprintf("%04x\r\n", NWK_GetShortAddr());
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

#if (APP_ENABLE_CERTIFICATION_EXTENSION == 0)

/**************************************************************************//**
\brief Processes Set Battery Voltage

\param[in] args - array of command arguments
******************************************************************************/
static void processSetBatteryVoltage(const ScanValue_t *args)
{
  dsPowerConfigurationClusterServerAttributes.batterySourceOneVoltage.value = args[0].uint8;
}

/**************************************************************************//**
\brief Processes Set Battery Percentage

\param[in] args - array of command arguments
******************************************************************************/
static void processSetBatteryPercentage(const ScanValue_t *args)
{
  dsPowerConfigurationClusterServerAttributes.batterySourceOnePercentageRemaining.value = (args[0].uint8)*2;
}

/**************************************************************************//**
\brief Processes Set Battery Voltage Min Threshold

\param[in] args - array of command arguments
******************************************************************************/
static void processSetBatteryVoltageMinThreshold(const ScanValue_t *args)
{
  dsPowerConfigurationClusterServerAttributes.batterySourceOneVoltageMinThreshold.value = args[0].uint8;
}

/**************************************************************************//**
\brief Processes Set Battery Voltage Threshold One

\param[in] args - array of command arguments
******************************************************************************/
static void processSetBatteryVoltageThresholdOne(const ScanValue_t *args)
{
  dsPowerConfigurationClusterServerAttributes.batterySourceOneVoltageThreshold_1.value = args[0].uint8;
}

/**************************************************************************//**
\brief Processes Set Battery Voltage Threshold Two

\param[in] args - array of command arguments
******************************************************************************/
static void processSetBatteryVoltageThresholdTwo(const ScanValue_t *args)
{
  dsPowerConfigurationClusterServerAttributes.batterySourceOneVoltageThreshold_2.value = args[0].uint8;
}

/**************************************************************************//**
\brief Processes Set Battery Voltage Threshold Three

\param[in] args - array of command arguments
******************************************************************************/
static void processSetBatteryVoltageThresholdThree(const ScanValue_t *args)
{
  dsPowerConfigurationClusterServerAttributes.batterySourceOneVoltageThreshold_3.value = args[0].uint8;
}

/**************************************************************************//**
\brief Processes Set Battery Percentage Min Threshold

\param[in] args - array of command arguments
******************************************************************************/
static void processSetBatteryPercentageMinThreshold(const ScanValue_t *args)
{
  dsPowerConfigurationClusterServerAttributes.batterySourceOnePercentageMinThreshold.value = args[0].uint8;
}

/**************************************************************************//**
\brief Processes Set Battery Percentage Threshold One

\param[in] args - array of command arguments
******************************************************************************/
static void processSetBatteryPercentageThresholdOne(const ScanValue_t *args)
{
  dsPowerConfigurationClusterServerAttributes.batterySourceOnePercentageThreshold_1.value = args[0].uint8;
}

/**************************************************************************//**
\brief Processes Set Battery Percentage Threshold Two

\param[in] args - array of command arguments
******************************************************************************/
static void processSetBatteryPercentageThresholdTwo(const ScanValue_t *args)
{
  dsPowerConfigurationClusterServerAttributes.batterySourceOnePercentageThreshold_2.value = args[0].uint8;
}

/**************************************************************************//**
\brief Processes Set Battery Percentage Threshold Three

\param[in] args - array of command arguments
******************************************************************************/
static void processSetBatteryPercentageThresholdThree(const ScanValue_t *args)
{
  dsPowerConfigurationClusterServerAttributes.batterySourceOnePercentageThreshold_3.value = args[0].uint8;
}

/**************************************************************************//**
\brief Processes Set Battery Alarm Mask

\param[in] args - array of command arguments
******************************************************************************/
static void processSetBatteryAlarmMask(const ScanValue_t *args)
{
  uint8_t value = ((args[0].uint8) & 0x0F);
  memcpy(&dsPowerConfigurationClusterServerAttributes.batterySourceOneAlarmMask.value,&value, sizeof(uint8_t));
}

/**************************************************************************//**
\brief Processes Read Battery Voltage

\param[in] args - array of command arguments
******************************************************************************/
static void processReadBatteryVoltage(const ScanValue_t *args)
{
  (void)args;
  LOG_STRING(readBattVoltStr, "Battery Voltage = %d\r\n");
  appSnprintf(readBattVoltStr, dsPowerConfigurationClusterServerAttributes.batterySourceOneVoltage.value);
}

/**************************************************************************//**
\brief Processes Read Battery Percentage

\param[in] args - array of command arguments
******************************************************************************/
static void processReadBatteryPercentage(const ScanValue_t *args)
{
  (void)args;
  LOG_STRING(readBattPerStr, "Battery Percentage = %d\r\n");
  appSnprintf(readBattPerStr, (dsPowerConfigurationClusterServerAttributes.batterySourceOnePercentageRemaining.value/2));
}

/**************************************************************************//**
\brief Processes Read Battery Voltage Min Threshold

\param[in] args - array of command arguments
******************************************************************************/
static void processReadBatteryVoltageMinThreshold(const ScanValue_t *args)
{
  (void)args;
  LOG_STRING(readBattVoltMinThStr, "Battery Voltage Min Threshold = %d\r\n");
  appSnprintf(readBattVoltMinThStr, dsPowerConfigurationClusterServerAttributes.batterySourceOneVoltageMinThreshold.value);
}

/**************************************************************************//**
\brief Processes Read Battery Voltage Threshold One

\param[in] args - array of command arguments
******************************************************************************/
static void processReadBatteryVoltageThresholdOne(const ScanValue_t *args)
{
  (void)args;
  LOG_STRING(readBattVoltThOneStr, "Battery Voltage Threshold One = %d\r\n");
  appSnprintf(readBattVoltThOneStr, dsPowerConfigurationClusterServerAttributes.batterySourceOneVoltageThreshold_1.value);
}

/**************************************************************************//**
\brief Processes Read Battery Voltage Threshold Two

\param[in] args - array of command arguments
******************************************************************************/
static void processReadBatteryVoltageThresholdTwo(const ScanValue_t *args)
{
  (void)args;
  LOG_STRING(readBattVoltThTwoStr, "Battery Voltage Threshold Two = %d\r\n");
  appSnprintf(readBattVoltThTwoStr, dsPowerConfigurationClusterServerAttributes.batterySourceOneVoltageThreshold_2.value);
}

/**************************************************************************//**
\brief Processes Read Battery Voltage Threshold Three

\param[in] args - array of command arguments
******************************************************************************/
static void processReadBatteryVoltageThresholdThree(const ScanValue_t *args)
{
  (void)args;
  LOG_STRING(readBattVoltThThreeStr, "Battery Voltage Threshold Three = %d\r\n");
  appSnprintf(readBattVoltThThreeStr, dsPowerConfigurationClusterServerAttributes.batterySourceOneVoltageThreshold_3.value);
}

/**************************************************************************//**
\brief Processes Read Battery Percentage Min Threshold

\param[in] args - array of command arguments
******************************************************************************/
static void processReadBatteryPercentageMinThreshold(const ScanValue_t *args)
{
  (void)args;
  LOG_STRING(readBattPerMinThStr, "Battery Percentage Min Threshold = %d\r\n");
  appSnprintf(readBattPerMinThStr, dsPowerConfigurationClusterServerAttributes.batterySourceOnePercentageMinThreshold.value);
}

/**************************************************************************//**
\brief Processes Read Battery Percentage Threshold One

\param[in] args - array of command arguments
******************************************************************************/
static void processReadBatteryPercentageThresholdOne(const ScanValue_t *args)
{
  (void)args;
  LOG_STRING(readBattPerThOneStr, "Battery Percentage Threshold One = %d\r\n");
  appSnprintf(readBattPerThOneStr, dsPowerConfigurationClusterServerAttributes.batterySourceOneVoltageThreshold_1.value);
}

/**************************************************************************//**
\brief Processes Read Battery Percentage Threshold Two

\param[in] args - array of command arguments
******************************************************************************/
static void processReadBatteryPercentageThresholdTwo(const ScanValue_t *args)
{
  (void)args;
  LOG_STRING(readBattPerThTwoStr, "Battery Percentage Threshold Two = %d\r\n");
  appSnprintf(readBattPerThTwoStr, dsPowerConfigurationClusterServerAttributes.batterySourceOneVoltageThreshold_2.value);
}

/**************************************************************************//**
\brief Processes Read Battery Percentage Threshold Three

\param[in] args - array of command arguments
******************************************************************************/
static void processReadBatteryPercentageThresholdThree(const ScanValue_t *args)
{
  (void)args;
  LOG_STRING(readBattPerThThreeStr, "Battery Percentage Threshold Three = %d\r\n");
  appSnprintf(readBattPerThThreeStr, dsPowerConfigurationClusterServerAttributes.batterySourceOneVoltageThreshold_3.value);
}

/**************************************************************************//**
\brief Processes Read Battery Alarm Mask

\param[in] args - array of command arguments
******************************************************************************/
static void processReadBatteryAlarmMask(const ScanValue_t *args)
{
  (void)args;
  uint8_t value;
  memcpy(&value,&dsPowerConfigurationClusterServerAttributes.batterySourceOneAlarmMask.value, sizeof(uint8_t));
  LOG_STRING(readBattAlarmMaskStr, "Battery Alarm Mask = %d\r\n");
  appSnprintf(readBattAlarmMaskStr, (value & 0x0f));
}

/**************************************************************************//**
\brief Processes Read Battery Alarm State

\param[in] args - array of command arguments
******************************************************************************/
static void processReadBatteryAlarmState(const ScanValue_t *args)
{
  (void)args;
  LOG_STRING(readBattAlarmStateStr, "currentBatteryAlarmState - 0x%08lx\r\n");
  appSnprintf(readBattAlarmStateStr, dsPowerConfigurationClusterServerAttributes.batterySourceOneAlarmState.value);
}

/**************************************************************************//**
\brief Resets Battery State

\param[in] args - array of command arguments
******************************************************************************/
static void processResetBatteryState(const ScanValue_t *args)
{
  (void)args;
  powerConfigurationClusterInitAttributes();
}

#endif // APP_ENABLE_CERTIFICATION_EXTENSION

#endif // APP_ENABLE_CONSOLE == 1
#endif // APP_DEVICE_TYPE_DIMMER_SWITCH

// eof dsConsole.c
