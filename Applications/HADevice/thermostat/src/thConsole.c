/**************************************************************************//**
  \file thConsole.c

  \brief
    Thermostat console implementation.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    09/09/2014 Unithra.C - Created
******************************************************************************/
#ifdef APP_DEVICE_TYPE_THERMOSTAT
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
#include <thThermostatCluster.h>
#include <thOccupancySensingCluster.h>
#include <thTimeCluster.h>
#include <thHumidityMeasurementCluster.h>
#include <thTemperatureMeasurementCluster.h>

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
static void processReadAttrCmd(const ScanValue_t *args);
static void processWriteAttrCmd(const ScanValue_t *args);
static void processConfigureReportingCmd(const ScanValue_t *args);
static void processInvokeEzModeCmd(const ScanValue_t *args);
static void processResetToFactoryFreshCmd(const ScanValue_t *args);
static void processGetDeviceTypeCmd(const ScanValue_t *args);
static void processPseudoPowerOffCmd(const ScanValue_t *args);
static void processSetPermitJoinCmd(const ScanValue_t *args);
static void processRestartNwkCmd(const ScanValue_t *args);
static void processGetNetworkAddressCmd(const ScanValue_t *args);
static void processTriggerAlarmCmd(const ScanValue_t *args);
static void processSetAlarmMaskCmd(const ScanValue_t *args);
static void zdoPermitJoiningResponse(ZDO_ZdpResp_t *resp);
static void processSetOccupancyStateCmd(const ScanValue_t *args);
static void processSetSensorTypeCmd(const ScanValue_t *args);
static APS_AddrMode_t determineAddressMode(const ScanValue_t *arg);
#ifdef ZCL_THERMOSTAT_CLUSTER_INCLUDE_OPTIONAL_ATTRIBUTES
static void processSetOccupancyCmd(const ScanValue_t *args);
#endif
static void processAttrinitDefault(const ScanValue_t *args);

/******************************************************************************
                    Local variables section
******************************************************************************/
static ZDO_ZdpReq_t zdpReq;
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
  {"setPermitJoin", "d", processSetPermitJoinCmd, "-> Sets Permit Join: setPermitJoin [dur]\r\n"},
#ifdef ZCL_THERMOSTAT_CLUSTER_INCLUDE_OPTIONAL_ATTRIBUTES  
  {"setOccupancy", "d", processSetOccupancyCmd, "-> Sets Occupancy [0- UnOccupied/1- Occupied]\r\n"},
#endif
  {"clusterAttrInitDefault", "d", processAttrinitDefault, "-> Initializes all attributes to default values [clusterID]\r\n"},
  {"restartNwk", "d", processRestartNwkCmd, "-> Restarts network on particular channel [channel]\r\n"},
  {"readAttribute", "sdddd", processReadAttrCmd,
    "->Read Attribute for specified cluster: readAttribute [addrMode][addr][ep][clusterId][attrId]\r\n"},
  {"writeAttribute", "sddddddd", processWriteAttrCmd,
    "->Write Attribute for specified cluster: writeAttribute [addrMode][addr][ep][clusterId][attrId][type][attrValue][attrSize]\r\n"},
  {"configureReporting", "sddddddd", processConfigureReportingCmd,
    "->Sends configure reporting to specified cluster server: configureReporting [addrMode][addr][ep][clusterId][attrId][type][min][max]\r\n"},
  {"setOccupancyState", "d", processSetOccupancyStateCmd, "-> Sets the Occupancy state [state]- occupiad - 1,unoccupiad -0\r\n "},
  {"setOccupancySensorType", "d", processSetSensorTypeCmd, "-> Sets the OccupancySensor Type [sensorType]- PIR - 0,Ultrasonic-1, PIR + Ultrasonic-20\r\n "},
  {"triggerAlarm","ddd", processTriggerAlarmCmd, "-> Triggers alarm condition: triggerAlarm [clusterId][alarmCode][0-raise 1-clear]\r\n"},
  {"setAlarmMask","dd", processSetAlarmMaskCmd, "-> Set Alarm Mask: setAlarmMask [clusterId][alarmMask]\r\n"},
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
#ifdef ZCL_THERMOSTAT_CLUSTER_INCLUDE_OPTIONAL_ATTRIBUTES
/**************************************************************************//**
\brief Processes Set Occupancy command

\param[in] args - array of command arguments
******************************************************************************/
static void processSetOccupancyCmd(const ScanValue_t *args)
{ 
  if (ZCL_SUCCESS_STATUS == thermostatSetOccupancy((ZCL_ThOccupancy_t)args[0].uint8))
    appSnprintf("Occupancy set to :%d\r\n",(ZCL_ThOccupancy_t)args[0].uint8);
  else
    appSnprintf("Occupancy not set: Invalid value\r\n");
}
#endif

/**************************************************************************//**
\brief Processes cluster attributes initialization to default

\param[in] args - array of command arguments
******************************************************************************/
static void processAttrinitDefault(const ScanValue_t *args)
{ 
  if(THERMOSTAT_CLUSTER_ID == args[0].uint16)
    thermostatClusterInitAttributes();
  else
    appSnprintf("Invalid Cluster ID\r\n");
}

/**************************************************************************//**
\brief ZDP permit joining response callback

\param[in] leaveResp - pointer to response structure

\return none
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

/**************************************************************************//**
\brief Processes SetOccupancyState command

\param[in] args - array of command arguments
******************************************************************************/
static void processSetOccupancyStateCmd(const ScanValue_t *args)
{
  occupancySensingInitiateSetOccupancyState(args[0].uint8);
}

/**************************************************************************//**
\brief Processes SetOccupancySensorType command

\param[in] args - array of command arguments
******************************************************************************/
static void processSetSensorTypeCmd(const ScanValue_t *args)
{
  occupancySensingSetSensorType(args[0].uint8);
}

/**************************************************************************//**
\brief Processes Read attribute command

\param[in] args - array of command arguments
******************************************************************************/
static void processReadAttrCmd(const ScanValue_t *args)
{
  ZCL_Cluster_t *cluster = ZCL_GetCluster(APP_SRC_ENDPOINT_ID, args[3].uint16 /* cluster id */, ZCL_CLUSTER_SIDE_CLIENT);

  if (!cluster)
  {
    LOG_STRING(unsupportedClusterIdStr, "Unsupported Client Cluster Id \r\n");
    appSnprintf(unsupportedClusterIdStr);
    return;
  }

  switch(args[3].uint16) //cluster Id
  {
    case OCCUPANCY_SENSING_CLUSTER_ID:
      occupancySensingReadAttribute(determineAddressMode(args), args[1].uint16, args[2].uint8,
        args[4].uint16, NULL);
      break;
    case TIME_CLUSTER_ID:
      timeReadAttribute(determineAddressMode(args), args[1].uint16, args[2].uint8,
        args[4].uint16, NULL);
      break;
   case HUMIDITY_MEASUREMENT_CLUSTER_ID:
      humidityMeasurementReadAttribute(determineAddressMode(args), args[1].uint16, args[2].uint8,
        args[4].uint16, NULL);
      break;
   case TEMPERATURE_MEASUREMENT_CLUSTER_ID:
      thTemperatureMeasurementReadAttribute(determineAddressMode(args), args[1].uint16, args[2].uint8,
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
\brief Processes Trigger Alarm command

\param[in] args - array of command arguments
******************************************************************************/
static void processTriggerAlarmCmd(const ScanValue_t *args)
{
  if (THERMOSTAT_CLUSTER_ID == args[0].uint16)
    thermostatSetAlarmCondition(args[1].uint8, (bool)args[2].uint8);
}

/**************************************************************************//**
\brief Processes set alarm mask command

\param[in] args - array of command arguments
******************************************************************************/
static void processSetAlarmMaskCmd(const ScanValue_t *args)
{
  if (THERMOSTAT_CLUSTER_ID == args[0].uint16)
    thermostatSetAlarmMask(args[1].uint8);
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
\brief Processes Write attribute command

\param[in] args - array of command arguments
******************************************************************************/
static void processWriteAttrCmd(const ScanValue_t *args)
{
  ZCL_Cluster_t *cluster = ZCL_GetCluster(APP_SRC_ENDPOINT_ID, args[3].uint16 /* cluster id */, ZCL_CLUSTER_SIDE_CLIENT);
  if (!cluster)
  {
    LOG_STRING(unsupportedClusterIdStr, "Unsupported Client Cluster Id \r\n");
    appSnprintf(unsupportedClusterIdStr);
    return;
  }
  switch(args[3].uint16) //cluster Id
  { 
    case OCCUPANCY_SENSING_CLUSTER_ID:
      occupancySensingWriteAttribute(determineAddressMode(args), args[1].uint16, args[2].uint8,
        args[4].uint16, args[5].uint8, NULL, (void *)&args[6].uint8, args[7].uint8);
      break;
    case TIME_CLUSTER_ID:
      if(args[5].uint8 == ZCL_8BIT_BITMAP_DATA_TYPE_ID)
      {
        timeWriteAttribute(determineAddressMode(args), args[1].uint16, args[2].uint8,
          args[4].uint16, args[5].uint8, NULL, (void *)&args[6].uint8, args[7].uint8);
      }
      else
      {
        timeWriteAttribute(determineAddressMode(args), args[1].uint16, args[2].uint8,
          args[4].uint16, args[5].uint8, NULL, (void *)&args[6].uint32, args[7].uint8);        
      }
      break;
    case HUMIDITY_MEASUREMENT_CLUSTER_ID:
      humidityMeasurementWriteAttribute(determineAddressMode(args), args[1].uint16, args[2].uint8,
        args[4].uint16, args[5].uint8, NULL, (void *)&args[6].uint8, args[7].uint8);
      break;
    case TEMPERATURE_MEASUREMENT_CLUSTER_ID:
      thTemperatureMeasurementWriteAttribute(determineAddressMode(args), args[1].uint16, args[2].uint8,
        args[4].uint16, args[5].uint8, NULL, (void *)&args[6].uint8, args[7].uint8);
      break;
    default:
      {
        LOG_STRING(unsupportedClusterIdStr, "Unsupported Cluster Id \r\n");
        appSnprintf(unsupportedClusterIdStr);
      }
  }
}

/**************************************************************************//**
\brief Processes Configure specified cluster attribute reporting command

\param[in] args - array of command arguments
******************************************************************************/
static void processConfigureReportingCmd(const ScanValue_t *args)
{
  ZCL_Cluster_t *cluster = ZCL_GetCluster(APP_SRC_ENDPOINT_ID, args[3].uint16 /* cluster id */, ZCL_CLUSTER_SIDE_CLIENT);

  if (!cluster)
  {
    LOG_STRING(unsupportedClusterIdStr, "Unsupported Client Cluster Id \r\n");
    appSnprintf(unsupportedClusterIdStr);
    return;
  }
  switch(args[3].uint16) //cluster Id
  {
    case OCCUPANCY_SENSING_CLUSTER_ID:
      occupancySensingConfigureReporting(determineAddressMode(args), args[1].uint16, args[2].uint8,
        args[4].uint16, args[5].uint8, args[6].uint16, args[7].uint16);
      break;
    case HUMIDITY_MEASUREMENT_CLUSTER_ID:
      humidityMeasurementConfigureReporting(determineAddressMode(args), args[1].uint16, args[2].uint8,
        args[4].uint16, args[5].uint8, args[6].uint16, args[7].uint16);
      break;
    case TEMPERATURE_MEASUREMENT_CLUSTER_ID:
      thTemperatureMeasurementConfigureReporting(determineAddressMode(args), args[1].uint16, args[2].uint8,
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

#endif // APP_ENABLE_CONSOLE == 1
#endif // APP_DEVICE_TYPE_THERMOSTAT

// eof thConsole.c
