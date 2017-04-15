/**************************************************************************//**
  \file ciConsole.c

  \brief
    Combined Interface console implementation.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2013, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    03.09.13 N. Fomin - Created.
******************************************************************************/
#ifdef APP_DEVICE_TYPE_COMBINED_INTERFACE
#if APP_ENABLE_CONSOLE == 1

/******************************************************************************
                    Includes section
******************************************************************************/
#include <uartManager.h>
#include <console.h>
#include <ciBasicCluster.h>
#include <identifyCluster.h>
#include <ciIdentifyCluster.h>
#include <ciOnOffCluster.h>
#include <ciLevelControlCluster.h>
#include <ciGroupsCluster.h>
#include <ciScenesCluster.h>
#include <ciOccupancySensingCluster.h>
#include <ciTemperatureMeasurementCluster.h>
#include <ciHumidityMeasurementCluster.h>
#include <ciIlluminanceMeasurementCluster.h>
#include <ciThermostatCluster.h>
#include <ciThermostatUiConfCluster.h>
#include <ciDiagnosticsCluster.h>
#include <ciFanControlCluster.h>
#include <ciPowerConfigurationCluster.h>
#include <ciTimeCluster.h>
#include <ciAlarmsCluster.h>
#include <ciIasACECluster.h>
#include <ciIasZoneCluster.h>
#include <resetReason.h>
#include <zclDevice.h>
#include <pdsDataServer.h>
#include <zdo.h>
#include <nwkAttributes.h>
#include <ezModeManager.h>
#include <sysTaskManager.h>
#ifdef BOARD_PC
  #include <conio.h>
#endif
#ifdef ZAPPSI_HOST
#include <zsiHalSerialization.h>
#endif

/******************************************************************************
                    Defines section
******************************************************************************/
/* This value used in ZLL tests to identify non-ZLL Trust Center */
#define TEST_DEVICE_TYPE_HA_TC 0x02U

/******************************************************************************
                    Prototypes section
******************************************************************************/
static void processHelpCmd(const ScanValue_t *args);

static void processStartEzModeCmd(const ScanValue_t *args);
static void processSetEzModeTypeCmd(const ScanValue_t *args);
static void processReadAttrCmd(const ScanValue_t *args);
static void processWriteAttrCmd(const ScanValue_t *args);
static void processIdentifyCmd(const ScanValue_t *args);
static void processIdentifyQueryCmd(const ScanValue_t *args);
static void processEzModeInvokeCmd(const ScanValue_t *args);
static void processUpdateCommissiningStateCmd(const ScanValue_t *args);
static void processOnOffToggleCmd(const ScanValue_t *args);
static void processMoveToLevelCmd(const ScanValue_t *args);
static void processMoveCmd(const ScanValue_t *args);
static void processStepCmd(const ScanValue_t *args);
static void processStopCmd(const ScanValue_t *args);
static void processAddGroupCmd(const ScanValue_t *args);
static void processViewGroupCmd(const ScanValue_t *args);
static void processGetGroupMembershipCmd(const ScanValue_t *args);
static void processRemoveGroupCmd(const ScanValue_t *args);
static void processRemoveAllGroupsCmd(const ScanValue_t *args);
static void processAddGroupIfIdentifyingCmd(const ScanValue_t *args);
static void processAddSceneToDimmableLightCmd(const ScanValue_t *args);
static void processAddSceneToThermostatCmd(const ScanValue_t *args);
static void processViewSceneCmd(const ScanValue_t *args);
static void processRemoveSceneCmd(const ScanValue_t *args);
static void processRemoveAllScenesCmd(const ScanValue_t *args);
static void processStoreSceneCmd(const ScanValue_t *args);
static void processRecallSceneCmd(const ScanValue_t *args);
static void processGetSceneMembershipCmd(const ScanValue_t *args);
static void processConfigureReportingCmd(const ScanValue_t *args);
static APS_AddrMode_t determineAddressMode(const ScanValue_t *arg);
static void processGetDeviceTypeCmd(const ScanValue_t *args);
static void processSetPermitJoinCmd(const ScanValue_t *args);
static void zdoPermitJoiningResponse(ZDO_ZdpResp_t *resp);
static void processSetPointChangeCmd(const ScanValue_t *args);
static void processResetToFactoryDefaultsCmd(const ScanValue_t *args);
static void processSetUTCTimeCmd(const ScanValue_t *args);
static void processReadTimeCmd(const ScanValue_t *args);
static void parseDateTime(char *str, dateTime_t *tempDateTime);
static void processSetTimeZoneAndDST(const ScanValue_t *args);
static void processSetTimeStatus(const ScanValue_t *args);
static void processResetAlarmCmd(const ScanValue_t *args);
static void processAlarmCmds(const ScanValue_t *args);
static void processSetExtAddr(const ScanValue_t *args);
static void processACEGetPanelStatusChangedCommand(const ScanValue_t *args);
static void processACEGetZoneStatusChangedCommand(const ScanValue_t *args);
static void processZoneInitiateNormalOperatingModeCommand(const ScanValue_t *args);
static void processZoneInitiateTestModeCommand(const ScanValue_t *args);
#ifndef ZAPPSI_HOST /* Hiding this commands for ZappSi */
static void processResetCmd(const ScanValue_t *args);
static void processPseudoPowerOffCmd(const ScanValue_t *args);
static void processResetToFactoryFreshCmd(const ScanValue_t *args);
static void processRestartNwkCmd(const ScanValue_t *args);
#endif

/******************************************************************************
                    Local variables section
******************************************************************************/
static ZDO_ZdpReq_t zdpReq;
static uint8_t readBuffer[USART_RX_BUFFER_LENGTH];
static const ConsoleCommand_t cmds[] =
{
  {"help",   "",     processHelpCmd, "->Show help you're reading now:  help\r\n"},
  {"setEzModeType", "d", processSetEzModeTypeCmd, "->Sets EZ-Mode type: 0 - target, 1 - initiator\r\n"},
  {"startEzMode", "", processStartEzModeCmd, "->Start finding and binding process\r\n"},
  {"readAttribute", "sdddd", processReadAttrCmd,
    "->Read Attribute for specified cluster: readAttribute [addrMode][addr][ep][clusterId][attrId]\r\n"},
  {"writeAttribute", "sddddddd", processWriteAttrCmd,
    "->Write Attribute for specified cluster: writeAttribute [addrMode][addr][ep][clusterId][attrId][type][attrValue][attrSize]\r\n"},
  {"identify", "sddd", processIdentifyCmd,
    "->Send Identify command: identify [addrMode][addr][ep][identifyTime]\r\n"},
  {"identifyQuery", "sdd", processIdentifyQueryCmd,
    "->Send Identify Query command: identifyQuery [addrMode][addr][ep]\r\n"},
  {"EzModeInvoke", "sddd", processEzModeInvokeCmd,
    "->Send EZ-Mode Invoke command: EzModeInvoke [addrMode][addr][ep][action]\r\n"},
  {"updateCommissioningState", "sdddd", processUpdateCommissiningStateCmd,
    "->Send Update Commissioning State command: updateCommissioningState [addrMode][addr][ep][action][mask]\r\n"},
  {"onOff", "sdds", processOnOffToggleCmd,
    "Sends On/Off command: onOff [addrMode][addr][ep][onOff: -on for On, -off for Off]\r\n"},
  {"moveToLevel", "sddddd", processMoveToLevelCmd,
    "->Send Move To Level (with On/Off) command: moveToLevel [addrMode][addr][ep][level][transitionTime][onOff]\r\n"},
  {"move", "sddddd", processMoveCmd,
    "->Send Move (with On/Off) command: move [addrMode][addr][ep][mode][rate][onOff]\r\n"},
  {"step", "sdddddd", processStepCmd,
    "->Send Step (with On/Off) command: step [addrMode][addr][ep][mode][stepSize][transitionTime][onOff]\r\n"},
  {"stop", "sddd", processStopCmd, "->Send Stop (with On/Off) command: stop [addrMode][addr][ep][onOff]\r\n"},
  {"addGroup", "sddd", processAddGroupCmd, "->Send Add Group command: addGroup [addrMode][addr][ep][groupId]\r\n"},
  {"viewGroup", "sddd", processViewGroupCmd, "->Send View Group command: viewGroup [addrMode][addr][ep][groupId]\r\n"},
  {"getGroupMembership", "sdddddddd", processGetGroupMembershipCmd,
    "->Send Get Group Membership command: getGroupMembership [addrMode][addr][ep][count][groupId]*5\r\n"},
  {"removeGroup", "sddd", processRemoveGroupCmd,
    "->Send Remove Group command: removeGroup [addrMode][addr][ep][groupId]\r\n"},
  {"removeAllGroups", "sdd", processRemoveAllGroupsCmd,
    "->Send Remove All Groups command: removeAllGroups [addrMode][addr][ep]\r\n"},
  {"addGroupIfIdentifying", "sddd", processAddGroupIfIdentifyingCmd,
    "->Send Add Group If Identifying command: addGroupIfIdentifying [addrMode][addr][ep][groupId]\r\n"},
  {"addSceneToDL", "sddddddd", processAddSceneToDimmableLightCmd,
    "->Send Add Scene command to Dimmable Light: addScene [addrMode][addr][ep][groupId][sceneId][transitionTime][onOff][level]\r\n"},
  {"addSceneToTH", "sdddddddd", processAddSceneToThermostatCmd,
    "->Send Add Scene command to Thermostat: addScene [addrMode][addr][ep][groupId][sceneId][transitionTime][occupiedCoolingSetpoint][occupiedHeatingSetpoint][systemMode]\r\n"},
  {"viewScene", "sdddd", processViewSceneCmd,
    "->Send View Scene command: viewScene [addrMode][addr][ep][groupId][sceneId]\r\n"},
  {"removeScene", "sdddd", processRemoveSceneCmd,
    "->Send Remove Scene command: removeScene [addrMode][addr][ep][groupId][sceneId]\r\n"},
  {"removeAllScenes", "sddd", processRemoveAllScenesCmd,
    "->Send Remove All Scenes command: removeAllScenes [addrMode][addr][ep][groupId]\r\n"},
  {"storeScene", "sdddd", processStoreSceneCmd,
    "->Send Store Scene command: storeScene [addrMode][addr][ep][groupId][sceneId]\r\n"},
  {"recallScene", "sdddd", processRecallSceneCmd,
    "->Send Recall Scene command: recallScene [addrMode][addr][ep][groupId][sceneId]\r\n"},
  {"getSceneMembership", "sddd", processGetSceneMembershipCmd,
    "->Send Get Scene Membership command: getSceneMembership [addrMode][addr][ep][groupId]\r\n"},
  {"configureReporting", "sddddddd", processConfigureReportingCmd,
    "->Sends configure reporting to specified cluster server: configureReporting [addrMode][addr][ep][clusterId][attrId][type][min][max]\r\n"},
  {"getDeviceType", "", processGetDeviceTypeCmd, "-> Request for device type: getDeviceType\r\n"},
  {"setPermitJoin", "d", processSetPermitJoinCmd, "-> Sets Permit Join: setPermitJoin [dur]\r\n"},
  {"thermSetPointChange", "sdddd", processSetPointChangeCmd, "-> change thermostat setpoints [addrMode][addr][ep][setPtmode][amount]\r\n"},
  {"setUTCTime", "s", processSetUTCTimeCmd, "-> set UTCTime to this date & Time[dd:mm:yr:hr:min:sec]\r\n"},
  {"readTime", "", processReadTimeCmd, "-> read the current UTCTime\r\n"},
  {"setTimeZoneAndDST", "dssd", processSetTimeZoneAndDST, "-> setTimZoneAndDST [timeZone][dstStart][dstEnd][dstShift]\r\n"},
  {"setTimeStatus", "dddd", processSetTimeStatus, "-> setTimeStatus [master][synchronized][masterZoneDst][superseding]\r\n"},  
  {"resetToFactoryDefaults", "sdd", processResetToFactoryDefaultsCmd, "-> reset all cluster attributes to factory defaults [addrMode][addr][ep]\r\n"},
  {"resetAlarm", "sdddd", processResetAlarmCmd, "-> change thermostat setpoints [addrMode][addr][ep][ClusterID][alarmCode]\r\n"},
  {"alarmCmd", "sdds", processAlarmCmds, "-> resetAll/Get/resetAlamrLog commands [addrMode][addr][ep] [resetAllAlarm/getAlarm/resetAlarmLog\r\n"},
  {"setExtAddr", "d",processSetExtAddr, "->Set Ext Address:[value]\r\n"},
  {"ACEGetPanelStatusChangedCommand", "sdddddd",processACEGetPanelStatusChangedCommand,
    "->Panel StatusChanged Command Sent:[addrMode][addr][ep][panel_status][seconds_remaining][audible_noti][alarmstatus]\r\n"},
  {"ACEZoneStatusChangedCommand", "sdddddd",processACEGetZoneStatusChangedCommand,
    "->Zone StatusChanged Command Sent:[addrMode][addr][ep][zoneId][zone_status][audible][zone_label]\r\n"},
  {"ZoneInitiateNormalOperatingModeCommand", "sdd",processZoneInitiateNormalOperatingModeCommand,
    "->Send ZoneInitiateNormalOperatingModeCommand:[addrMode][addr][ep]\r\n"},
  {"ZoneInitiateTestModeCommand", "sdddd",processZoneInitiateTestModeCommand,
    "->Send ZoneInitiateTestModeCommand:[addrMode][addr][ep][Test_Mode_Duration ][Current_Zone_Sensitivity Level]\r\n"},
#ifndef ZAPPSI_HOST /* Hiding this commands for ZappSi */
  {"reset", "", processResetCmd, "->Reset device\r\n"},
  {"resetToFN", "", processResetToFactoryFreshCmd, "->Reset to factory fresh settings: resetToFN\r\n"},
  {"powerOff", "", processPseudoPowerOffCmd, "-> Powers off device: powerOff\r\n"},  
  {"restartNwk", "d", processRestartNwkCmd, "-> Restarts network on particular channel [channel]\r\n"},
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
#ifndef ZAPPSI_HOST
/**************************************************************************//**
\brief Processes reset command: reset device

\param[in] args - array of command arguments
******************************************************************************/
static void processResetCmd(const ScanValue_t *args)
{
  (void)args;
#ifdef ZAPPSI_HOST
  /* In case of reset command received on Host first NP
     then Host application need to be reset
   */
  ZSI_ResetNP();
  restartApp();
#else
  HAL_WarmReset();
#endif

}
#endif

/**************************************************************************//**
\brief Processes start finding and binding command

\param[in] args - array of command arguments
******************************************************************************/
static void processStartEzModeCmd(const ScanValue_t *args)
{
  (void)args;
  invokeEzMode(NULL);
}

/**************************************************************************//**
\brief Processes Set EZ-Mode type command

\param[in] args - array of command arguments
******************************************************************************/
static void processSetEzModeTypeCmd(const ScanValue_t *args)
{
  initEzModeManager(args[0].uint8);
}

/**************************************************************************//**
\brief Processes Read attribute command

\param[in] args - array of command arguments
******************************************************************************/
static void processReadAttrCmd(const ScanValue_t *args)
{
  switch(args[3].uint16) //cluster Id
  {
    case BASIC_CLUSTER_ID:
       basicReadAttribute(determineAddressMode(args), args[1].uint16, args[2].uint8,
         args[4].uint16, NULL);
      break;
    case TEMPERATURE_MEASUREMENT_CLUSTER_ID:
      temperatureMeasurementReadAttribute(determineAddressMode(args), args[1].uint16, args[2].uint8,
        args[4].uint16, NULL);
      break;
    case OCCUPANCY_SENSING_CLUSTER_ID:
      occupancySensingReadAttribute(determineAddressMode(args), args[1].uint16, args[2].uint8,
        args[4].uint16, NULL);
      break;
    case HUMIDITY_MEASUREMENT_CLUSTER_ID:
      humidityMeasurementReadAttribute(determineAddressMode(args), args[1].uint16, args[2].uint8,
        args[4].uint16, NULL);
      break;
    case ILLUMINANCE_MEASUREMENT_CLUSTER_ID:
      illuminanceMeasuredValueReadAttribute(determineAddressMode(args), args[1].uint16, args[2].uint8,
        args[4].uint16, NULL);
      break;
    case THERMOSTAT_CLUSTER_ID:
      thermostatReadAttribute(determineAddressMode(args), args[1].uint16, args[2].uint8,
        args[4].uint16, NULL);
      break;
    case IDENTIFY_CLUSTER_ID:
      identifyReadAttribute(determineAddressMode(args), args[1].uint16, args[2].uint8,
        args[4].uint16, NULL);
      break;
    case THERMOSTAT_UI_CONF_CLUSTER_ID:
      thermostatUiConfReadAttribute(determineAddressMode(args), args[1].uint16, args[2].uint8,
        args[4].uint16, NULL);
      break;
    case FAN_CONTROL_CLUSTER_ID:
      fanControlReadAttribute(determineAddressMode(args), args[1].uint16, args[2].uint8,
        args[4].uint16, NULL);
      break;
    case POWER_CONFIGURATION_CLUSTER_ID:
      powerConfigurationReadAttribute(determineAddressMode(args), args[1].uint16, args[2].uint8,
        args[4].uint16, NULL);
      break;
    case DIAGNOSTICS_CLUSTER_ID:
      diagnosticsReadAttribute(determineAddressMode(args), args[1].uint16, args[2].uint8,
        args[4].uint16, NULL);
      break;
    case ALARMS_CLUSTER_ID:
      alarmsReadAttribute(determineAddressMode(args), args[1].uint16, args[2].uint8,
        args[4].uint16, NULL);
      break;
    case IAS_ZONE_CLUSTER_ID:
      iaszoneReadAttribute(determineAddressMode(args), args[1].uint16, args[2].uint8,
        args[4].uint16, NULL);
      break; 
    case IAS_ACE_CLUSTER_ID:
      iasACEReadAttribute(determineAddressMode(args), args[1].uint16, args[2].uint8,
        args[4].uint16, NULL);
      break;
    default:
      {
        LOG_STRING(unsupportedClusterIdStr, "Unsupported Cluster Id \r\n");
        appSnprintf(unsupportedClusterIdStr);
      }
      break;
  }
}

/**************************************************************************//**
\brief Processes Write attribute command

\param[in] args - array of command arguments
******************************************************************************/
static void processWriteAttrCmd(const ScanValue_t *args)
{
  switch(args[3].uint16) //cluster Id
  {
    case BASIC_CLUSTER_ID:
       basicWriteAttribute(determineAddressMode(args), args[1].uint16, args[2].uint8,
         args[4].uint16, args[5].uint8, NULL, (void *)&args[6].uint8, args[7].uint8);
      break;
    case TEMPERATURE_MEASUREMENT_CLUSTER_ID:
      temperatureMeasurementWriteAttribute(determineAddressMode(args), args[1].uint16, args[2].uint8,
        args[4].uint16, args[5].uint8, NULL, (void *)&args[6].uint8, args[7].uint8);
      break;
    case OCCUPANCY_SENSING_CLUSTER_ID:
      occupancySensingWriteAttribute(determineAddressMode(args), args[1].uint16, args[2].uint8,
        args[4].uint16, args[5].uint8, NULL, (void *)&args[6].uint8, args[7].uint8);
      break;
    case HUMIDITY_MEASUREMENT_CLUSTER_ID:
      humidityMeasurementWriteAttribute(determineAddressMode(args), args[1].uint16, args[2].uint8,
        args[4].uint16, args[5].uint8, NULL, (void *)&args[6].uint8, args[7].uint8);
      break;
    case ILLUMINANCE_MEASUREMENT_CLUSTER_ID:
      illuminanceMeasuredValueWriteAttribute(determineAddressMode(args), args[1].uint16, args[2].uint8,
        args[4].uint16, args[5].uint8, NULL, (void *)&args[6].uint8, args[7].uint8);
      break;
    case THERMOSTAT_CLUSTER_ID:
      thermostatWriteAttribute(determineAddressMode(args), args[1].uint16, args[2].uint8,
        args[4].uint16, args[5].uint8, NULL, (void *)&args[6].uint8, args[7].uint8);
      break;
    case IDENTIFY_CLUSTER_ID:
      identifyWriteAttribute(determineAddressMode(args), args[1].uint16, args[2].uint8,
        args[4].uint16, args[5].uint8, NULL, (void *)&args[6].uint8, args[7].uint8);
      break;
    case THERMOSTAT_UI_CONF_CLUSTER_ID:
      thermostatUiConfWriteAttribute(determineAddressMode(args), args[1].uint16, args[2].uint8,
        args[4].uint16, args[5].uint8, NULL, (void *)&args[6].uint8, args[7].uint8);
      break;
    case FAN_CONTROL_CLUSTER_ID:
      fanControlWriteAttribute(determineAddressMode(args), args[1].uint16, args[2].uint8,
        args[4].uint16, args[5].uint8, NULL, (void *)&args[6].uint8, args[7].uint8);
      break;
    case POWER_CONFIGURATION_CLUSTER_ID:
      powerConfigurationWriteAttribute(determineAddressMode(args), args[1].uint16, args[2].uint8,
        args[4].uint16, args[5].uint8, NULL, (void *)&args[6].uint8, args[7].uint8);
      break;
    case DIAGNOSTICS_CLUSTER_ID:
      diagnosticsWriteAttribute(determineAddressMode(args), args[1].uint16, args[2].uint8,
        args[4].uint16, args[5].uint8, NULL, (void *)&args[6].uint8, args[7].uint8);
      break;
    case ALARMS_CLUSTER_ID:
      alarmsWriteAttribute(determineAddressMode(args), args[1].uint16, args[2].uint8,
        args[4].uint16, args[5].uint8, NULL, (void *)&args[6].uint8, args[7].uint8);
      break;
    case IAS_ZONE_CLUSTER_ID:
      iaszoneWriteAttribute(determineAddressMode(args), args[1].uint16, args[2].uint8,
        args[4].uint16, args[5].uint8, NULL, (void *)&args[6].uint8, args[7].uint8);
      break;
    case IAS_ACE_CLUSTER_ID:
      iasACEWriteAttribute(determineAddressMode(args), args[1].uint16, args[2].uint8,
        args[4].uint16, args[5].uint8, NULL, (void *)&args[6].uint8, args[7].uint8);
      break;
    default:
      {
        LOG_STRING(unsupportedClusterIdStr, "Unsupported Cluster Id \r\n");
        appSnprintf(unsupportedClusterIdStr);
      }
      break;
  }
}

/**************************************************************************//**
\brief Processes Identify command

\param[in] args - array of command arguments
******************************************************************************/
static void processIdentifyCmd(const ScanValue_t *args)
{
  identifySendIdentify(determineAddressMode(args), args[1].uint16, args[2].uint8,
    args[3].uint16);
}

/**************************************************************************//**
\brief Processes Identify Query command

\param[in] args - array of command arguments
******************************************************************************/
static void processIdentifyQueryCmd(const ScanValue_t *args)
{
  identifySendIdentifyQuery(determineAddressMode(args), args[1].uint16, args[2].uint8);
}

/**************************************************************************//**
\brief Processes EZ-Mode invoke command

\param[in] args - array of command arguments
******************************************************************************/
static void processEzModeInvokeCmd(const ScanValue_t *args)
{
  identifySendEzModeInvoke(determineAddressMode(args), args[1].uint16, args[2].uint8,
    args[3].uint8);
}

/**************************************************************************//**
\brief Processes Update Commissioning State command

\param[in] args - array of command arguments
******************************************************************************/
static void processUpdateCommissiningStateCmd(const ScanValue_t *args)
{
  identifySendUpdateCommissioningState(determineAddressMode(args), args[1].uint16, args[2].uint8,
    args[3].uint8, args[4].uint8);
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
\brief Processes Add group command

\param[in] args - array of command arguments
******************************************************************************/
static void processAddGroupCmd(const ScanValue_t *args)
{
  groupsSendAddGroup(determineAddressMode(args), args[1].uint16, args[2].uint8,
    args[3].uint16);
}

/**************************************************************************//**
\brief Processes View group command

\param[in] args - array of command arguments
******************************************************************************/
static void processViewGroupCmd(const ScanValue_t *args)
{
  groupsSendViewGroup(determineAddressMode(args), args[1].uint16, args[2].uint8,
    args[3].uint16);
}

/**************************************************************************//**
\brief Processes Get group membership command

\param[in] args - array of command arguments
******************************************************************************/
static void processGetGroupMembershipCmd(const ScanValue_t *args)
{
  uint16_t groupList[5];

  for (uint8_t i = 0; i < 5; i++)
    groupList[i] = args[i+4].uint16;

  groupsSendGetGroupMembership(determineAddressMode(args), args[1].uint16, args[2].uint8,
    args[3].uint8, groupList);
}

/**************************************************************************//**
\brief Processes Remove group command

\param[in] args - array of command arguments
******************************************************************************/
static void processRemoveGroupCmd(const ScanValue_t *args)
{
  groupsSendRemoveGroup(determineAddressMode(args), args[1].uint16, args[2].uint8,
    args[3].uint16);
}

/**************************************************************************//**
\brief Processes Remove all groups command

\param[in] args - array of command arguments
******************************************************************************/
static void processRemoveAllGroupsCmd(const ScanValue_t *args)
{
  (void)args;
  groupsSendRemoveAllGroups(determineAddressMode(args), args[1].uint16, args[2].uint8);
}

/**************************************************************************//**
\brief Processes Add group if identifying command

\param[in] args - array of command arguments
******************************************************************************/
static void processAddGroupIfIdentifyingCmd(const ScanValue_t *args)
{
  groupsSendAddGroupIfIdentifying(determineAddressMode(args), args[1].uint16, args[2].uint8,
    args[3].uint16);
}

/**************************************************************************//**
\brief Processes Add Scene command to DL

\param[in] args - array of command arguments
******************************************************************************/
static void processAddSceneToDimmableLightCmd(const ScanValue_t *args)
{
  scenesSendAddSceneToDimmableLight(determineAddressMode(args), args[1].uint16, args[2].uint8,
    args[3].uint16, args[4].uint8, args[5].uint16, args[6].uint8, args[7].uint8);
}
/**************************************************************************//**
\brief Processes Add Scene command to Thermostat

\param[in] args - array of command arguments
******************************************************************************/
static void processAddSceneToThermostatCmd(const ScanValue_t *args)
{
  scenesSendAddSceneToThermotstat(determineAddressMode(args), args[1].uint16, args[2].uint8,
    args[3].uint16, args[4].uint8, args[5].uint16, args[6].int16, args[7].int16, args[8].uint8 );
}

/**************************************************************************//**
\brief Processes View Scene command

\param[in] args - array of command arguments
******************************************************************************/
static void processViewSceneCmd(const ScanValue_t *args)
{
  scenesSendViewScene(determineAddressMode(args), args[1].uint16, args[2].uint8,
    args[3].uint16, args[4].uint8);
}

/**************************************************************************//**
\brief Processes Remove group command

\param[in] args - array of command arguments
******************************************************************************/
static void processRemoveSceneCmd(const ScanValue_t *args)
{
  scenesSendRemoveScene(determineAddressMode(args), args[1].uint16, args[2].uint8,
    args[3].uint16, args[4].uint8);
}

/**************************************************************************//**
\brief Processes Remove all scenes command

\param[in] args - array of command arguments
******************************************************************************/
static void processRemoveAllScenesCmd(const ScanValue_t *args)
{
  scenesSendRemoveAllScenes(determineAddressMode(args), args[1].uint16, args[2].uint8,
    args[3].uint16);
}

/**************************************************************************//**
\brief Processes Store scene command

\param[in] args - array of command arguments
******************************************************************************/
static void processStoreSceneCmd(const ScanValue_t *args)
{
  scenesSendStoreScene(determineAddressMode(args), args[1].uint16, args[2].uint8,
    args[3].uint16, args[4].uint8);
}

/**************************************************************************//**
\brief Processes Recall scene command

\param[in] args - array of command arguments
******************************************************************************/
static void processRecallSceneCmd(const ScanValue_t *args)
{
  scenesSendRecallScene(determineAddressMode(args), args[1].uint16, args[2].uint8,
    args[3].uint16, args[4].uint8);
}

/**************************************************************************//**
\brief Processes Get scene membership command

\param[in] args - array of command arguments
******************************************************************************/
static void processGetSceneMembershipCmd(const ScanValue_t *args)
{
  scenesSendGetSceneMembership(determineAddressMode(args), args[1].uint16, args[2].uint8,
    args[3].uint16);
}

/**************************************************************************//**
\brief Processes Configure specified cluster attribute reporting command

\param[in] args - array of command arguments
******************************************************************************/
static void processConfigureReportingCmd(const ScanValue_t *args)
{
  switch(args[3].uint16) //cluster Id
  {
    case TEMPERATURE_MEASUREMENT_CLUSTER_ID:
      temperatureMeasurementConfigureReporting(determineAddressMode(args), args[1].uint16, args[2].uint8,
        args[4].uint16, args[5].uint8, args[6].uint16, args[7].uint16);
      break;
    case OCCUPANCY_SENSING_CLUSTER_ID:
      occupancySensingConfigureReporting(determineAddressMode(args), args[1].uint16, args[2].uint8,
        args[4].uint16, args[5].uint8, args[6].uint16, args[7].uint16);
      break;
    case HUMIDITY_MEASUREMENT_CLUSTER_ID:
      humidityMeasurementConfigureReporting(determineAddressMode(args), args[1].uint16, args[2].uint8,
        args[4].uint16, args[5].uint8, args[6].uint16, args[7].uint16);
      break;
    case ILLUMINANCE_MEASUREMENT_CLUSTER_ID:
      illuminanceMeasurementConfigureReporting(determineAddressMode(args), args[1].uint16, args[2].uint8,
        args[4].uint16, args[5].uint8, args[6].uint16, args[7].uint16);
      break;
    case THERMOSTAT_CLUSTER_ID:
      thermostatConfigureReporting(determineAddressMode(args), args[1].uint16, args[2].uint8,
        args[4].uint16, args[5].uint8, args[6].uint16, args[7].uint16);
      break;
    case POWER_CONFIGURATION_CLUSTER_ID:
      powerConfigConfigureReporting(determineAddressMode(args), args[1].uint16, args[2].uint8,
        args[4].uint16, args[5].uint8, args[6].uint16, args[7].uint16);
      break;
    case LEVEL_CONTROL_CLUSTER_ID:
      levelControlConfigureReporting(determineAddressMode(args), args[1].uint16, args[2].uint8,
        args[4].uint16, args[5].uint8, args[6].uint16, args[7].uint16);
      break;
    case ONOFF_CLUSTER_ID:
      onOffConfigureReporting(determineAddressMode(args), args[1].uint16, args[2].uint8,
        args[4].uint16, args[5].uint8, args[6].uint16, args[7].uint16);
      break;
    default:
      {
        LOG_STRING(unsupportedClusterIdStr, "Unsupported Cluster Id \r\n");
        appSnprintf(unsupportedClusterIdStr);
      }
      break;
  }
}

/**************************************************************************//**
\brief Processes request for device type obtaining

\param[in] args - array of command arguments
******************************************************************************/
static void processGetDeviceTypeCmd(const ScanValue_t *args)
{
  (void)args;
  LOG_STRING(deviceFnStatusStr, "DeviceType = %d\r\n");
  appSnprintf(deviceFnStatusStr, TEST_DEVICE_TYPE_HA_TC);
}

#ifndef ZAPPSI_HOST
/**************************************************************************//**
\brief Processes pseudo power off command

\param[in] args - array of command arguments
******************************************************************************/
static void processPseudoPowerOffCmd(const ScanValue_t *args)
{
  (void)args;
  /* Disable BitCloud tasks for preventing calls to the radio.
     HAL is enabled so it it allows to receive commands through UART. */
  SYS_DisableTask(ZDO_TASK_ID);
  SYS_DisableTask(APS_TASK_ID);
  SYS_DisableTask(NWK_TASK_ID);
  SYS_DisableTask(MAC_PHY_HWD_TASK_ID);
}

/**************************************************************************//**
\brief Processes reset to factory fresh

\param[in] args - array of command arguments
******************************************************************************/
static void processResetToFactoryFreshCmd(const ScanValue_t *args)
{
  (void)args;
#ifndef ZAPPSI_HOST
  PDS_DeleteAll(false);

  HAL_WarmReset();
#endif
}
#endif

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
\brief Processes Setpoint Change command

\param[in] args - array of command arguments
******************************************************************************/
static void processSetPointChangeCmd(const ScanValue_t *args)
{
  ciSendSetpointRaiseLowerCommand(determineAddressMode(args),args[1].uint16,
    args[2].uint8,args[3].int8,args[4].int8);
}

/**************************************************************************//**
\brief Processes reset To factory defaults command

\param[in] args - array of command arguments
******************************************************************************/
static void processResetToFactoryDefaultsCmd(const ScanValue_t *args)
{
  basicResetToFactoryDefaultsCommand(determineAddressMode(args),args[1].uint16,
    args[2].uint8);
}
/**************************************************************************//**
\brief Processes reset alarm command

\param[in] args - array of command arguments
******************************************************************************/
static void processResetAlarmCmd(const ScanValue_t *args)
{
  alarmsSendResetAlarm(determineAddressMode(args),args[1].uint16,
    args[2].uint8, args[3].uint16, args[4].uint8);
}
/**************************************************************************//**
\brief Processes reset To factory defaults command

\param[in] args - array of command arguments
******************************************************************************/
static void processAlarmCmds(const ScanValue_t *args)
{
  if (!memcmp("resetAllAlarms", args[3].str, 14))
  {
    alarmsSendResetAllAlarms(determineAddressMode(args),args[1].uint16,
    args[2].uint8);
  }
  else if (!memcmp("getAlarm", args[3].str, 8))
  {
    alarmsSendGetAlarm(determineAddressMode(args),args[1].uint16,
    args[2].uint8);
  }
  else if (!memcmp("resetAlarmLog", args[3].str, 13))
  {
    alarmsSendResetAlarmLog(determineAddressMode(args),args[1].uint16,
    args[2].uint8);
  }
}
/**************************************************************************//**
\brief Process set UTC time command

\param[in] args - array of command arguments
******************************************************************************/
static void processSetUTCTimeCmd(const ScanValue_t *args)
{
  dateTime_t tempDateTime;
  parseDateTime(args[0].str,&tempDateTime);
  timeSetTimeAttribute(tempDateTime);
}
/**************************************************************************//**
\brief Process read UTC time command

\param[in] args - array of command arguments
******************************************************************************/
static void processReadTimeCmd(const ScanValue_t *args)
{
  LOG_STRING(readTimeStr, "currentUTCTime - 0x%08lx\r\n");
  appSnprintf(readTimeStr,(unsigned long int)timeReadTimeAttribute());
  (void)args;
}
/**************************************************************************//**
\brief Process set time zone and DST attributes

\param[in] args - array of command arguments
******************************************************************************/
static void processSetTimeZoneAndDST(const ScanValue_t *args)
{
  dateTime_t tempDateTime;
  int32_t timeZone;
  uint32_t dstStart;
  uint32_t dstEnd;
  int32_t dstShift;
  
  timeZone = args[0].int32;
  parseDateTime(args[1].str,&tempDateTime);
  dstStart = timeCalculateUTCTime(&tempDateTime);
  parseDateTime(args[2].str,&tempDateTime);
  dstEnd = timeCalculateUTCTime(&tempDateTime);
  dstShift = args[3].int32;
  timeSetTimezoneAndDSTAttributes(timeZone, dstStart, dstEnd, dstShift);
}
/**************************************************************************//**
\brief Process set time status bits

\param[in] args - array of command arguments
******************************************************************************/
static void processSetTimeStatus(const ScanValue_t *args)
{
  timeSetTimeStatus(args[0].uint8, args[1].uint8, args[2].uint8, args[3].uint8);
}
/**************************************************************************//**
\brief Parse the user string dd:mm:yy:hr:min:sec

\param[in] args - array of command arguments
******************************************************************************/
static void parseDateTime(char *str, dateTime_t *tempDateTime)
{
  tempDateTime->date = (str[0]-'0') * 10 + (str[1]-'0');
  tempDateTime->month = (str[3]-'0') * 10 + (str[4]-'0');
  tempDateTime->year = (str[6]-'0') * 1000 + (str[7]-'0') * 100 + (str[8]-'0') * 10 + (str[9]-'0');
  tempDateTime->hour = (str[11]-'0') * 10 + (str[12]-'0');
  tempDateTime->minute = (str[14]-'0') * 10 + (str[15]-'0');
  tempDateTime->seconds = (str[17]-'0') * 10 + (str[18]-'0');
}

/**************************************************************************//**
\brief To set a new entended address

\param[in] args - extended address
******************************************************************************/
static void processSetExtAddr(const ScanValue_t *args)
{
  ExtAddr_t changeExtAddr = 0;
  memcpy(&changeExtAddr, (void *)&args[0].uint8,4);
  CS_WriteParameter(CS_UID_ID , &changeExtAddr);
  csPIB.macAttr.extAddr = changeExtAddr;
}

/**************************************************************************//**
\brief Processes ACE Get Panel Status Change Command

\param[in] args - array of command arguments
******************************************************************************/
static void processACEGetPanelStatusChangedCommand(const ScanValue_t *args)
{
    acePanelStatusChangedCommand(determineAddressMode(args), args[1].uint16, args[2].uint8,
    args[3].uint8, args[4].uint8, args[5].uint8, args[6].uint8);
}

/**************************************************************************//**
\brief Processes ACE Get Zone Status Change Command

\param[in] args - array of command arguments
******************************************************************************/
static void processACEGetZoneStatusChangedCommand(const ScanValue_t *args)
{
    aceZoneStatusChangedCommand(determineAddressMode(args), args[1].uint16, args[2].uint8,
    args[3].uint8, args[4].uint8, args[5].uint8, args[6].uint16);  
}

/**************************************************************************//**
\brief Processes Zone Initiate Normal Operating Mode Command

\param[in] args - array of command arguments
******************************************************************************/
static void processZoneInitiateNormalOperatingModeCommand(const ScanValue_t *args)
{
  ZoneInitiateNormalOperatingModeCommand(determineAddressMode(args), args[1].uint16, args[2].uint8);
}

/**************************************************************************//**
\brief Processes Zone Initiate Test Mode Command

\param[in] args - array of command arguments
******************************************************************************/
static void processZoneInitiateTestModeCommand(const ScanValue_t *args)
{
  ZoneInitiateTestModeCommand(determineAddressMode(args), args[1].uint16, args[2].uint8, args[3].uint8, args[4].uint8);
}

#ifndef ZAPPSI_HOST
/**************************************************************************//**
\brief Processes Restart Network command

\param[in] args - array of command arguments
******************************************************************************/
static void processRestartNwkCmd(const ScanValue_t *args)
{
  CS_WriteParameter(CS_CHANNEL_MASK_ID, &(uint32_t){1ul << args[0].uint8});

  appRestart(false);
}
#endif

#endif // APP_ENABLE_CONSOLE == 1
#endif // APP_DEVICE_TYPE_COMBINED_INTERFACE

// eof ciConsole.c
