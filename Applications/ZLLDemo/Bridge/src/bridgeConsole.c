/**************************************************************************//**
  \file bridgeConsole.c

  \brief
    Control Bridge console implementation.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2013, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    22.01.2013 N.Fomin - Created
******************************************************************************/
#if APP_ZLL_DEVICE_TYPE == APP_DEVICE_TYPE_BRIDGE
#if APP_ENABLE_CONSOLE == 1

/******************************************************************************
                    Includes section
******************************************************************************/
#include <uartManager.h>
#include <console.h>
#include <resetReason.h>
#include <networkJoining.h>
#include <bridgeLightsDiscovery.h>
#include <apsCommon.h>
#include <bridgeLevelControlCluster.h>
#include <bridgeOnOffCluster.h>
#include <bridgeGroupsCluster.h>
#include <bridgeScenesCluster.h>
#include <bridgeIdentifyCluster.h>
#include <bridgeColorControlCluster.h>
#include <bridgeOtaCluster.h>
#include <zllDemo.h>
#include <lightBindings.h>
#include <N_DeviceInfo_bindings.h>
#include <N_Connection.h>
#include <N_DeviceInfo.h>
#include <N_AddressManager_Bindings.h>
#include <N_AddressManager.h>
#include <pdsDataServer.h>
#include <zdo.h>

/******************************************************************************
                    Prototypes section
******************************************************************************/
static void processHelpCmd(const ScanValue_t *args);
static void processResetCmd(const ScanValue_t *args);
static void processStartNetworkCmd(const ScanValue_t *args);
static void processStartDiscoveryCmd(const ScanValue_t *args);
static void processSetBrightnessCmd(const ScanValue_t *args);
static void processOnOffCmd(const ScanValue_t *args);
static void processAddGroupCmd(const ScanValue_t *args);
static void processRemoveGroupCmd(const ScanValue_t *args);
static void processSetColorCmd(const ScanValue_t *args);
static void processIdentifyCmd(const ScanValue_t *args);
static void processSceneCmd(const ScanValue_t *args);
static void processStepSaturationCmd(const ScanValue_t *args);
static void processStepBrightnessCmd(const ScanValue_t *args);
static void processCreateNetworkCmd(const ScanValue_t *args);
static void processSendPermitJoinCmd(const ScanValue_t *args);
static void processResetToFnCmd(const ScanValue_t *args);
static void processResetToFdCmd(const ScanValue_t *args);

static APS_AddrMode_t determineAddressMode(const ScanValue_t *arg);
static void createNetworkDone(N_Connection_Result_t result);
static void zdoResetNwkConf(ZDO_ResetNetworkConf_t *conf);

static void processImageNotifyCmd(const ScanValue_t *args);
/******************************************************************************
                    Local variables
******************************************************************************/
static uint8_t  readBuffer[USART_RX_BUFFER_LENGTH];
static const ConsoleCommand_t cmds[] =
{
  {"help", "", processHelpCmd, "->Show help you're reading now: help\r\n"},
  {"reset", "", processResetCmd, "->Reset device\r\n"},
  {"startNetwork", "", processStartNetworkCmd, "->Start association: startNetwork\r\n"},
  {"startDiscovery", "", processStartDiscoveryCmd, "->Start lights discovery: startDiscovery\r\n"},
  {"setBrightness", "sdddd", processSetBrightnessCmd, "Sets brightness: setBrightness [addrMode][addr][ep][level][time]\r\n"},
  {"onOff", "sdds", processOnOffCmd, "Sends On/Off command: onOff [addrMode][addr][ep][onOff: -on for On, -off for Off]\r\n"},
  {"addGroup", "sddd", processAddGroupCmd, "Sends Add Group command: addGroup [addrMode][addr][ep][group]\r\n"},
  {"removeGroup", "sddd", processRemoveGroupCmd, "Sends Add Group command: removeGroup [addrMode] [addr][ep][group]\r\n"},
  {"setColor", "sddddd", processSetColorCmd, "Sets color: setColor [addrMode][addr][ep][hue][sat][time]\r\n"},
  {"identify", "sdd", processIdentifyCmd, "Sends identify request: identify [addrMode][addr][ep]\r\n"},
  {"scene", "sddsdd", processSceneCmd, "Sends store/recall/remove scene: scene [addrMode][addr][ep][cmd][group][scene]\r\n"},
  {"stepSaturation", "sddddd", processStepSaturationCmd, "Sends step saturation command: stepSaturation [addrMode][addr][ep][mode][size][time]\r\n"},
  {"stepBrightness", "sddddd", processStepBrightnessCmd, "Sends step brightness command: stepBrightness [addrMode][addr][ep][mode][size][time]\r\n"},
  {"createNetwork", "dddddd", processCreateNetworkCmd, "Creates network: createNetwork [ePanIdHigh][ePanIdLow][ch][panId][addr][updateId]\r\n"},
  {"sendPermitJoin", "d", processSendPermitJoinCmd, "Sends permit join command to all routers: sendPermitJoin [permit]\r\n"},
  {"resetToFN", "", processResetToFnCmd, "Reset to Factory New, persistant items retained: resetToFN\r\n"},
  {"resetToFD", "", processResetToFdCmd, "Reset to Factory Default, deletes everything including persistant items: resetToFD\r\n"},
  {"imageNotify", "dddddd", processImageNotifyCmd, "Sends Image Notify cmd: imageNotify ucastFlag dstEp shortAddress [payloadType] [fwVersionhi16] [fwVersionLo16]\r\n"},
  {0, 0, 0, 0},
};
static ZDO_ResetNetworkReq_t zdoResetNwkReq =
{
  .ZDO_ResetNetworkConf = zdoResetNwkConf
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
  int16_t bytesRead = readDataFromUart(readBuffer, MIN(USART_RX_BUFFER_LENGTH, length));

  for (int16_t i = 0; i < bytesRead; i++)
    consoleRx(readBuffer[i]);
}

/**************************************************************************//**
\brief Processes help command

\param[in] args - array of command arguments
******************************************************************************/
static void processHelpCmd(const ScanValue_t *args)
{
  appSnprintf("Commands: \r\n");

  for (const ConsoleCommand_t *cmd = cmds; cmd->name; cmd++)
  {
    appSnprintf("%s\r\n", cmd->name);
  }
  (void)args;
}

/**************************************************************************//**
\brief Processes reset command: reset device

\param[in] args - array of command arguments
******************************************************************************/
static void processResetCmd(const ScanValue_t *args)
{
  HAL_WarmReset();
  (void)args;
}

/**************************************************************************//**
\brief Processes start network command

\param[in] args - array of command arguments
******************************************************************************/
static void processStartNetworkCmd(const ScanValue_t *args)
{
  ZDO_ResetNetworkReq(&zdoResetNwkReq);
  (void)args;
}

/**************************************************************************//**
\brief Processes start lights discovery command

\param[in] args - array of command arguments
******************************************************************************/
static void processStartDiscoveryCmd(const ScanValue_t *args)
{
  discoverLights();
  (void)args;
}

/**************************************************************************//**
\brief Processes set brightness command

\param[in] args - array of command arguments
******************************************************************************/
static void processSetBrightnessCmd(const ScanValue_t *args)
{
  bridgeSendMoveToLevelCommand(determineAddressMode(args), args[1].uint16, args[3].uint8, args[4].uint16, args[2].uint8);
}

/**************************************************************************//**
\brief Processes on/off command

\param[in] args - array of command arguments
******************************************************************************/
static void processOnOffCmd(const ScanValue_t *args)
{
  uint8_t command = 0;

  if (!memcmp("-on", args[3].str, 3))
    command = 1;

  bridgeSendOnOffCommand(determineAddressMode(args), args[1].uint16, command, args[2].uint8);
}

/**************************************************************************//**
\brief Processes add group command

\param[in] args - array of command arguments
******************************************************************************/
static void processAddGroupCmd(const ScanValue_t *args)
{
  uint16_t validGroupIdMin;
  uint16_t validGroupIdMax;

  N_AddressManager_GetFreeGroupIdRange(&validGroupIdMin, &validGroupIdMax);
  //validGroupIdMax holds the total no of groupCount possible
  validGroupIdMax = validGroupIdMin + validGroupIdMax - 1;
  if(args[3].uint16 >= validGroupIdMin && args[3].uint16 <= validGroupIdMax)
    bridgeSendAddGroupCommand(determineAddressMode(args), args[1].uint16, args[2].uint8, args[3].uint16);
  else
  {
    appSnprintf("Enter valid groupId\r\n");
    appSnprintf("Min - %d & Max - %d\r\n", validGroupIdMin, validGroupIdMax);
  }
}

/**************************************************************************//**
\brief Processes remove group command

\param[in] args - array of command arguments
******************************************************************************/
static void processRemoveGroupCmd(const ScanValue_t *args)
{
  bridgeSendRemoveGroupCommand(determineAddressMode(args), args[1].uint16, args[2].uint8, args[3].uint16);
}

/**************************************************************************//**
\brief Processes move to hue and saturation command

\param[in] args - array of command arguments
******************************************************************************/
static void processSetColorCmd(const ScanValue_t *args)
{
  bridgeSendMoveToHueAndSaturationCommand(determineAddressMode(args), args[1].uint16, args[2].uint8,
                                          args[3].uint8, args[4].uint8, args[5].uint16);
}

/**************************************************************************//**
\brief Processes identify command

\param[in] args - array of command arguments
******************************************************************************/
static void processIdentifyCmd(const ScanValue_t *args)
{
  bridgeSendIdentifyCommand(determineAddressMode(args), args[1].uint16, args[2].uint8);
}

/**************************************************************************//**
\brief Processes scene command

\param[in] args - array of command arguments
******************************************************************************/
static void processSceneCmd(const ScanValue_t *args)
{
  uint8_t command = ZCL_SCENES_CLUSTER_RECALL_SCENE_COMMAND_ID;

  if (!memcmp("-store", args[3].str, 5))
    command = ZCL_SCENES_CLUSTER_STORE_SCENE_COMMAND_ID;
  else if (!memcmp("-remove", args[3].str, 5))
    command = ZCL_SCENES_CLUSTER_REMOVE_SCENE_COMMAND_ID;

  bridgeStoreRecallRemoveSceneCommand(determineAddressMode(args), args[1].uint16, args[2].uint8,
                                      command, args[4].uint16, args[5].uint8);
}

/**************************************************************************//**
\brief Processes image notify command

\param[in] args - array of command arguments
******************************************************************************/
static void processImageNotifyCmd(const ScanValue_t *args)
{
#if APP_USE_OTAU == 1
  bool isUcast = args[0].uint8?true:false;
  ZCL_OtauImageNotify_t imgNtfy;
  uint16_t csManufacturerId;
  ZCL_Addressing_t addr =
  {
  .addrMode             = APS_SHORT_ADDRESS,
  .profileId            = APP_PROFILE_ID,
  .clusterId            = OTAU_CLUSTER_ID,
  .clusterSide          = ZCL_CLIENT_CLUSTER_TYPE,
  .manufacturerSpecCode = 0, 
  };
  CS_ReadParameter(CS_MANUFACTURER_CODE_ID, &csManufacturerId);

  addr.addr.shortAddress = isUcast?args[2].uint16:BROADCAST_ADDR_ALL;
  addr.endpointId        = args[1].uint16;
  addr.sequenceNumber    = ZCL_GetNextSeqNumber();
  
  imgNtfy.payloadType = isUcast?OTAU_PAYLOAD_TYPE_QUERY_JITTER:args[3].uint8;
  imgNtfy.queryJitter = isUcast?OTAU_IMAGE_NOTIFY_MAX_QUERY_JITTER_VALUE:OTAU_IMAGE_NOTIFY_MAX_QUERY_JITTER_VALUE/2;
  imgNtfy.manufacturerCode = csManufacturerId;
  imgNtfy.imageType = OTAU_SPECIFIC_IMAGE_TYPE;
  imgNtfy.newFileVersion = ((uint32_t)args[4].uint16 << 16) + args[5].uint16;
  
  ZCL_ImageNotifyReq(&addr, &imgNtfy);
#endif
  (void)args;
}

/**************************************************************************//**
\brief Processes Step Saturation command

\param[in] args - array of command arguments
******************************************************************************/
static void processStepSaturationCmd(const ScanValue_t *args)
{
  bridgeSendStepSaturationCommand(determineAddressMode(args), args[1].uint16, args[2].uint8, args[3].uint8, args[4].uint8, args[5].uint16);
}

/**************************************************************************//**
\brief Processes Step Color Level command

\param[in] args - array of command arguments
******************************************************************************/
static void processStepBrightnessCmd(const ScanValue_t *args)
{
  bridgeSendStepLevelCommand(determineAddressMode(args), args[1].uint16, args[2].uint8, args[3].uint8, args[4].uint8, args[5].uint16);
}

/**************************************************************************//**
\brief Creates new network with specified parameters

\param[in] args - array of command arguments
******************************************************************************/
static void processCreateNetworkCmd(const ScanValue_t *args)
{
  ExtPanId_t extPanId = ((uint64_t)args[0].uint32 << 32) + args[1].uint32;
  uint8_t key[SECURITY_KEY_SIZE];

  SYS_GetRandomSequence(key, SECURITY_KEY_SIZE);

  appSnprintf("\r\nKey is - ");
  for (uint8_t i = 0; i < SECURITY_KEY_SIZE; i++)
    appSnprintf("%.2x", key[i]);
  appSnprintf("\r\n");

  N_Connection_JoinNetwork((uint8_t*)&extPanId,   /* ExtPanId */
                           args[2].uint8,         /* Channel */
                           args[3].uint16,        /* PanId */
                           args[4].uint16,        /* NwkAddr */
                           args[5].uint8,         /* NwkUpdateId */
                           key, /* NwkKey */
                           createNetworkDone);    /* Callback */
}

/**************************************************************************//**
\brief Join network done callback

\param[in] result - return code of join network procedure
******************************************************************************/
static void createNetworkDone(N_Connection_Result_t result)
{
  LOG_STRING(settingStr, "\r\nCreation of network is done - %d\r\n");
  appSnprintf(settingStr, result);
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
  return APS_SHORT_ADDRESS;
}

/**************************************************************************//**
\brief Processes permit join command

\param[in] args - array of command arguments
******************************************************************************/
static void processSendPermitJoinCmd(const ScanValue_t *args)
{
  sendPermitJoinCommand(args[0].uint8);
}

/**************************************************************************//**
\brief Processes reset to factory new command

\param[in] args - array of command arguments
******************************************************************************/
static void processResetToFnCmd(const ScanValue_t *args)
{
  (void)args;
  PDS_DeleteAll(false);
  N_DeviceInfo_SetFactoryNew(true);
  HAL_WarmReset();
}

/**************************************************************************//**
\brief Processes reset to factory default command

\param[in] args - array of command arguments
******************************************************************************/
static void processResetToFdCmd(const ScanValue_t *args)
{
  (void)args;
  PDS_DeleteAll(true);
  N_DeviceInfo_SetFactoryNew(true);
  HAL_WarmReset();
}

/**************************************************************************//**
\brief Confirm on ZDO Reset Network

\param[in] conf - confiramtion parameters
******************************************************************************/
static void zdoResetNwkConf(ZDO_ResetNetworkConf_t *conf)
{
  initiateStartingNetwork();
  (void)conf;
}

#endif // APP_ENABLE_CONSOLE == 1
#endif // APP_ZLL_DEVICE_TYPE == APP_DEVICE_TYPE_BRIDGE

// eof bridgeConsole.c
