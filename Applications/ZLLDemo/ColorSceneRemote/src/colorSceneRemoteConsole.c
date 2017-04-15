/**************************************************************************//**
  \file colorSceneRemoteConsole.c

  \brief
    Color Scene Remote console implementation.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    10.04.2012 N.Fomin - Created
******************************************************************************/
#if APP_ZLL_DEVICE_TYPE == APP_DEVICE_TYPE_COLOR_SCENE_REMOTE
#if APP_ENABLE_CONSOLE == 1

/******************************************************************************
                    Includes section
******************************************************************************/
#include <mac.h>
#include <debug.h>
#include <uartManager.h>
#include <console.h>
#include <resetReason.h>
#include <apsCommon.h>
#include <pdsDataServer.h>
#include <commandManager.h>
#include <colorSceneRemoteLevelControlCluster.h>
#include <colorSceneRemoteOnOffCluster.h>
#include <colorSceneRemoteGroupsCluster.h>
#include <colorSceneremoteColorControlCluster.h>
#include <colorSceneRemoteidentifyCluster.h>
#include <colorSceneRemoteIdentifyCluster.h>
#include <colorSceneRemoteScenesCluster.h>
#include <colorSceneRemoteLinkInfoCluster.h>
#include <colorSceneRemoteBasicCluster.h>
#include <colorSceneRemoteCommissioningCluster.h>
#include <colorSceneRemoteFsm.h>
#include <colorSceneRemoteConsole.h>
#include <otauService.h>

#include <colorSceneRemoteBindings.h>
#include <N_DeviceInfo.h>
#include <N_LinkInitiator.h>
#include <N_LinkTarget.h>
#include <N_Zdp.h>
#include <N_AddressManager_Bindings.h>
#include <N_AddressManager.h>

/******************************************************************************
                    Definitions section
******************************************************************************/
#define FOUND_DEVICES_ARRAY_SIZE 1

/******************************************************************************
                    Prototypes section
******************************************************************************/
static void processHelpCmd(const ScanValue_t *args);
static void processResetCmd(const ScanValue_t *args);
static void processTouchlinkCmd(const ScanValue_t *args);
static void processOnOffCmd(const ScanValue_t *args);
static void processAddGroupCmd(const ScanValue_t *args);
static void processRemoveGroupCmd(const ScanValue_t *args);
static void processIdentifyCmd(const ScanValue_t *args);
static void processSceneCmd(const ScanValue_t *args);
static void processTransmitLinkInfoCmd(const ScanValue_t *args);
static void processResetToFnCmd(const ScanValue_t *args);
static void processResetToFdCmd(const ScanValue_t *args);
static void processGetExtAddrCmd(const ScanValue_t *args);
static void processPerformScanCmd(const ScanValue_t *args);
static void scanDone(N_LinkInitiator_Status_t status, uint8_t numDevicesFound);
static void processResetDeviceToFnCmd(const ScanValue_t *args);
static void requestDone(N_LinkInitiator_Status_t status);
static void processIdentifyDeviceCmd(const ScanValue_t *args);
static void processStopOtauCmd(const ScanValue_t *args);
static void processStartOtauCmd(const ScanValue_t *args);

#if APP_ENABLE_CERTIFICATION_EXTENSION == 0
static APS_AddrMode_t determineAddressMode(const ScanValue_t *arg);
static void processSetColorCmd(const ScanValue_t *args);
static void processSetBrightnessCmd(const ScanValue_t *args);
#else // APP_ENABLE_CERTIFICATION_EXTENSION == 1
static void processGetCsChannelMask(const ScanValue_t *args);
static void processRemoveAllGroupsCmd(const ScanValue_t *args);
static void processMacBanNodeCmd(const ScanValue_t *args);
static void processMacResetBanTableCmd(const ScanValue_t *args);
static void processSetTargetTypeCmd(const ScanValue_t *args);
static void setTypeDone(void);
static void processSendNwkUpdateReqCmd(const ScanValue_t *args);
static void processIsDeviceFnCmd(const ScanValue_t *args);
static void processIsEndDeviceCmd(const ScanValue_t *args);
static void processGetDeviceTypeCmd(const ScanValue_t *args);
static void processReadBasicAttrCmd(const ScanValue_t *args);
static void processSetAddressingCmd(const ScanValue_t *args);
static void processGetNetworkAddressCmd(const ScanValue_t *args);
static void processSendMgmtBindReqCmd(const ScanValue_t *args);
static void processSetNwkSecurityCmd(const ScanValue_t *args);
static void processRestartActivityCmd(const ScanValue_t *args);
static void processReadOnOffAttrCmd(const ScanValue_t *args);
static void processOffWithEffectCmd(const ScanValue_t *args);
static void processOnWithTimedOffCmd(const ScanValue_t *args);
static void processReadLevelControlAttrCmd(const ScanValue_t *args);
static void processMoveCmd(const ScanValue_t *args);
static void processStepCmd(const ScanValue_t *args);
static void processMoveToLevelCmd(const ScanValue_t *args);
static void processLevelControlCmd(const ScanValue_t *args);
static void processWriteBasicAttributeCmd(const ScanValue_t *args);
static void processReadIdentifyAttrCmd(const ScanValue_t *args);
static void processWriteIdentifyAttributeCmd(const ScanValue_t *args);
static void processGetChannelCmd(const ScanValue_t *args);
static void processGetChannelMaskCmd(const ScanValue_t *args);
static void processPseudoPowerOffCmd(const ScanValue_t *args);
static void rxEnableConf(MAC_RxEnableConf_t *conf);
static void processSetPrimaryChannelMaskCmd(const ScanValue_t *args);
static void processSetSecondaryChannelMaskCmd(const ScanValue_t *args);
static void processNwkAssociationCmd(const ScanValue_t *args);
static void processIdentifyQueryCmd(const ScanValue_t *args);
static void processTriggerEffectCmd(const ScanValue_t *args);
static void processWriteAttrUndividedCmd(const ScanValue_t *args);
static void processWriteAttrNoRespCmd(const ScanValue_t *args);
static void processGetGroupMembershipCmd(const ScanValue_t *args);
static void processViewGroupCmd(const ScanValue_t *args);
static void processAddGroupIfIdentifyingCmd(const ScanValue_t *args);
static void processReadGroupsAttrCmd(const ScanValue_t *args);
static void processGetSceneMembershipCmd(const ScanValue_t *args);
static void processRemoveAllScenesCmd(const ScanValue_t *args);
static void processAddSceneCmd(const ScanValue_t *args);
static void processRemoveSceneCmd(const ScanValue_t *args);
static void processEnhancedAddSceneCmd(const ScanValue_t *args);
static void processCopySceneCmd(const ScanValue_t *args);
static void processReadScenesAttrCmd(const ScanValue_t *args);

static void processMoveToHueCmd(const ScanValue_t *args);
static void processMoveHueCmd(const ScanValue_t *args);
static void processStepHueCmd(const ScanValue_t *args);
static void processMoveToSaturationCmd(const ScanValue_t *args);
static void processMoveSaturationCmd(const ScanValue_t *args);
static void processStepSaturationCmd(const ScanValue_t *args);
static void processMoveToHueAndSaturationCmd(const ScanValue_t *args);
static void processMoveToColorCmd(const ScanValue_t *args);
static void processMoveColorCmd(const ScanValue_t *args);
static void processStepColorCmd(const ScanValue_t *args);
static void processEnhancedMoveToHueCmd(const ScanValue_t *args);
static void processEnhancedMoveHueCmd(const ScanValue_t *args);
static void processEnhancedStepHueCmd(const ScanValue_t *args);
static void processEnhancedMoveToHueAndSaturationCmd(const ScanValue_t *args);
static void processMoveStepHueCmd(const ScanValue_t *args);
static void processMoveToColorTemperatureCmd(const ScanValue_t *args);
static void processMoveColorTemperatureCmd(const ScanValue_t *args);
static void processStepColorTemperatureCmd(const ScanValue_t *args);
static void processColorControlReadAttrCmd(const ScanValue_t *args);
static void processColorControlWriteAttrCmd(const ScanValue_t *args);
static void processColorSetLoopCmd(const ScanValue_t *args);

static void processGetGroupIdentifiersReqCmd(const ScanValue_t *args);
static void processGetEndpointListReqCmd(const ScanValue_t *args);
#endif // APP_ENABLE_CERTIFICATION_EXTENSION

/******************************************************************************
                    Local variables
******************************************************************************/
static uint8_t  readBuffer[USART_RX_BUFFER_LENGTH];
static const ConsoleCommand_t cmds[] =
{
  {"help", "", processHelpCmd, "->Show help you're reading now: help\r\n"},
  {"reset", "", processResetCmd, "->Reset device\r\n"},
  {"touchlink", "", processTouchlinkCmd, "Perform touchlink: touchlink\r\n"},
  {"addGroup", "ddd", processAddGroupCmd, "Sends Add Group command: addGroup [addr][ep][group]\r\n"},
  {"transmitLinkInfo", "dd", processTransmitLinkInfoCmd, "Transmit Link Info: transmitLinkInfo [addr][ep]\r\n"},
  {"resetToFN", "", processResetToFnCmd, "Reset to Factory New, persistant items retained: resetToFN\r\n"},
  {"resetToFD", "", processResetToFdCmd, "Reset to Factory Default, deletes everything including persistant items: resetToFD\r\n"},
  {"devInfoGetExtAddr", "", processGetExtAddrCmd, "-> Gets ExtAddr: devInfoGetExtAddr\r\n"},
  {"performScan", "d", processPerformScanCmd, "-> Start scan: performScan <scanType>\r\n"},
  {"resetDeviceToFN", "", processResetDeviceToFnCmd, "Reset device to FN: resetDeviceToFN\r\n"},
  {"identifyDevice", "d", processIdentifyDeviceCmd, "Perform identify request: identifyDevice <timeoutInSec>\r\n"},
  {"stopOtau", "", processStopOtauCmd, "Stop OTAU process\r\n"},
  {"startOtau", "", processStartOtauCmd, "Start OTAU process after stop\r\n"},
#if APP_ENABLE_CERTIFICATION_EXTENSION == 0
  {"setColor", "sddddd", processSetColorCmd, "Sets color: setColor [addrMode][addr][ep][hue][sat][time]\r\n"},
  {"onOff", "sdds", processOnOffCmd, "Sends On/Off command: onOff [addrMode][addr][ep][onOff: -on for On, -off for Off]\r\n"},
  {"identify", "sdd", processIdentifyCmd, "Sends identify request: identify [addrMode][addr][ep]\r\n"},
  {"scene", "sddsdd", processSceneCmd, "Sends store/recall/remove scene: scene [addrMode][addr][ep][cmd][group][scene]\r\n"},
  {"removeGroup", "ddd", processRemoveGroupCmd, "Sends Add Group command: removeGroup [addr][ep][group]\r\n"},
  {"setBrightness", "sdddd", processSetBrightnessCmd, "Sets brightness: setBrightness [addrMode][addr][ep][level][time]\r\n"},
#else // APP_ENABLE_CERTIFICATION_EXTENSION == 1
  {"getCsChannelMask", "", processGetCsChannelMask, "Returns channel mask from configuration server: getCsChannelMask\r\n"},
  {"onOff", "d", processOnOffCmd, "Turns on/off or toggles lamp(s): onOff [command]\r\n"},
  {"identify", "d", processIdentifyCmd, "Sends identify request: identify <time>\r\n"},
  {"scene", "ddd", processSceneCmd, "Sends store/recall/remove scene: scene [cmd][scene]\r\n"},
  {"removeGroup", "d", processRemoveGroupCmd, "Sends Add Group command: removeGroup [group]\r\n"},
  {"removeAllGroups", "", processRemoveAllGroupsCmd, "Sends Remove All Groups command: removeAllGroups\r\n"},
  {"macBanNode", "ddd", processMacBanNodeCmd, "-> Sets specified link cost: <extAddr> <cost>\r\n"},
  {"macResetBanTable", "", processMacResetBanTableCmd, "-> Resets mac ban table\r\n"},
  {"setTargetType", "d", processSetTargetTypeCmd, "-> Sets target type: setTargetType <type>\r\n"},
  {"sendNwkMgmtUpdateReq", "ddd", processSendNwkUpdateReqCmd, "-> Sends nwkMgmtUpdateReq: sendNwkMgmtUpdateReq <channel> <scanDuration> <nwkAddr>\r\n"},
  {"isDeviceFn", "", processIsDeviceFnCmd, "-> Request for device FN flag: isDeviceFn\r\n"},
  {"isEndDevice", "", processIsEndDeviceCmd, "-> Request for device type: isEndDevice\r\n"},
  {"getDeviceType", "", processGetDeviceTypeCmd, "-> Request for device type: getDeviceType\r\n"},
  {"setAddressing", "ddddd", processSetAddressingCmd, "-> Set addressing: setAddressing <mode><addr><dstEp><manSpecCode><defaultResp>\r\n"},
  {"getNetworkAddress", "", processGetNetworkAddressCmd, "-> Returns network address: getNetworkAddress\r\n"},
  {"sendMgmtBindReq", "dd", processSendMgmtBindReqCmd, "-> Sends ZdpMgmtBindReq: sendMgmtBindReq <startIndex> <destNwkAddr>\r\n"},
  {"setNwkSecurity", "d", processSetNwkSecurityCmd, "-> Enable/disable NWK security: setNwkSecurityReq <enable>\r\n"},
  {"restartActivity", "", processRestartActivityCmd, "-> Restarts remote's activity: restartActivity\r\n"},
  {"readBasicAttr", "d", processReadBasicAttrCmd, "->Reads Basic cluster Attribure: readBasicAttr <attrId>\r\n"},
  {"readOnOffAttr", "d", processReadOnOffAttrCmd, "->Reads On/off cluster Attribure: readOnOffAttr <attrId>\r\n"},
  {"offWithEffect", "dd", processOffWithEffectCmd, "->Sends off with effect command: offWithEffect <effectId> <effectVar>\r\n"},
  {"onWithTimedOff", "ddd", processOnWithTimedOffCmd, "->Sends on with timed off command: onWithTimedOff <onOffCtrl><onTime><offWaitTime>\r\n"},
  {"readLevelControlAttr", "d", processReadLevelControlAttrCmd, "->Reads Level control cluster Attribure: readLevelControlAttr <attrId>\r\n"},
  {"move", "ddd", processMoveCmd, "->Sends Level control cluster move command: move <command> <mode> <rate>\r\n"},
  {"step", "dddd", processStepCmd, "->Sends Level control cluster step command: step <command> <mode> <size> <time>\r\n"},
  {"moveToLevel", "ddd", processMoveToLevelCmd, "Sends Move to level command: moveToLevel [cmd][level][time]\r\n"},
  {"levelControl", "d", processLevelControlCmd, "Sends command without payload: levelControl [cmd]\r\n"},
  {"writeBasicAttr", "ddd", processWriteBasicAttributeCmd, "->Writes Basic cluster Attribure: writeBasicAttr <attrId><type><val>\r\n"},
  {"readIdentifyAttr", "d", processReadIdentifyAttrCmd, "->Reads Identify cluster Attribure: readIdentifyAttr <attrId>\r\n"},
  {"writeIdentifyAttr", "ddd", processWriteIdentifyAttributeCmd, "->Writes Identify cluster Attribure: writeIdentifyAttr <attrId><type><val>\r\n"},
  {"getChannel", "", processGetChannelCmd, "-> Returns current channel: getChannel\r\n"},
  {"getChannelMask", "", processGetChannelMaskCmd, "-> Returns current channel mask: getChannelMask\r\n"},
  {"setPrimaryChannelMask", "d", processSetPrimaryChannelMaskCmd, "-> Sets primary channel mask: setPrimaryChannelMask [mask]\r\n"},
  {"setSecondaryChannelMask", "d", processSetSecondaryChannelMaskCmd, "-> Sets secondary channel mask: setSecondaryChannelMask [mask]\r\n"},
  {"nwkAssociation", "", processNwkAssociationCmd, "-> Associates to network been found\r\n"},
  {"powerOff", "", processPseudoPowerOffCmd, "-> Powers off device: powerOff\r\n"},
  {"identifyQuery", "", processIdentifyQueryCmd, "-> Sends identify query command: identifyQuery\r\n"},
  {"triggerEffect", "dd", processTriggerEffectCmd, "-> Sends trigger effect command: triggerEffect <id><variant>\r\n"},
  {"writeAttrUndivided", "ddddddd", processWriteAttrUndividedCmd, "-> Sends write attribute undivided cmd: writeAttrUndivided\r\n"},
  {"writeAttrNoResp", "dddd", processWriteAttrNoRespCmd, "-> Sends write attribute no response cmd: writeAttrNoResp\r\n"},
  {"getGroupMembership", "dd", processGetGroupMembershipCmd, "-> Sends get group membership cmd: getGroupMembership <cnt><groupId1>\r\n"},
  {"viewGroup", "d", processViewGroupCmd, "-> Sends view group cmd: viewGroup <groupId>\r\n"},
  {"addGroupIfIdentifying", "d", processAddGroupIfIdentifyingCmd, "-> Sends add group if identifying cmd: addGroupIfIdentifying <groupId>\r\n"},
  {"readGroupsAttr", "d", processReadGroupsAttrCmd, "->Reads Groups cluster Attribure: readGroupsAttr <attrId>\r\n"},
  {"getSceneMembership", "d", processGetSceneMembershipCmd, "->Sends get scene membership command: getSceneMembership <groupId>\r\n"},
  {"removeAllScenes", "d", processRemoveAllScenesCmd, "->Sends remove all scenes command: removeAllScenes <groupId>\r\n"},
  {"addScene", "ddd", processAddSceneCmd, "->Sends add scene command: addScene <groupId><sceneId><transitionTime>\r\n"},
  {"removeScene", "dd", processRemoveSceneCmd, "->Sends remove scene command: removeScene <groupId><sceneId>\r\n"},
  {"enhancedAddScene", "ddd", processEnhancedAddSceneCmd, "->Sends enhanced add scene command: enhancedAddScene <groupId><sceneId><transitionTime>\r\n"},
  {"copyScene", "ddddd", processCopySceneCmd, "->Sends copy scene command: addScene <dstGroupId><dstSceneId><srcGroupId><srcSceneId><mode>\r\n"},
  {"readSceneAttr", "d", processReadScenesAttrCmd, "->Reads Scenes cluster Attribure: readScenesAttr <attrId>\r\n"},

  {"moveToHue", "ddd", processMoveToHueCmd, "->Sends move to hue command: moveToHue <hue><dir><time>\r\n"},
  {"moveHue", "dd", processMoveHueCmd, "->Sends move hue command: moveHue <mode><rate>\r\n"},
  {"stepHue", "ddd", processStepHueCmd, "->Sends step hue command: stepHue <mode><size><time>\r\n"},
  {"moveToSaturation", "dd", processMoveToSaturationCmd, "->Sends move to saturation command: moveToSaturation <saturation><time>\r\n"},
  {"moveSaturation", "dd", processMoveSaturationCmd, "->Sends move saturation command: moveSaturation <mode><rate>\r\n"},
  {"stepSaturation", "ddd", processStepSaturationCmd, "->Sends step saturation command: stepSaturation <mode><size><time>\r\n"},
  {"moveToHueAndSaturation", "ddd", processMoveToHueAndSaturationCmd, "->Sends move to hue and saturation command: moveToHueAndSaturation\r\n"},
  {"moveToColor", "ddd", processMoveToColorCmd, "->Sends move to color command: moveToColor\r\n"},
  {"moveColor", "dd", processMoveColorCmd, "->Sends move color command: moveColor\r\n"},
  {"stepColor", "ddd", processStepColorCmd, "->Sends step color command: stepColor\r\n"},
  {"enhancedMoveToHue", "ddd", processEnhancedMoveToHueCmd, "->Sends enhanced move to hue command: enhancedMoveToHue <hue><dir><time>\r\n"},
  {"enhancedMoveHue", "dd", processEnhancedMoveHueCmd, "->Sends enhanced move hue command: enhancedMoveHue <mode><rate>\r\n"},
  {"enhancedStepHue", "ddd", processEnhancedStepHueCmd, "->Sends enhanced step hue command: enhancedStepHue <mode><size><time>\r\n"},
  {"enhancedMoveToHueAndSaturation", "ddd", processEnhancedMoveToHueAndSaturationCmd, "->Sends enhanced move to hue and saturation command: moveToHueAndSaturation\r\n"},
  {"stopMoveStepHue", "", processMoveStepHueCmd, "->Sends move step hue command: stopMoveStepHue\r\n"},
  {"moveToColorTemperature", "dd", processMoveToColorTemperatureCmd, "->Sends move to color temp command: moveToColorTemperature\r\n"},
  {"moveColorTemperature", "dddd", processMoveColorTemperatureCmd, "->Sends move color temp command: moveColorTemperature\r\n"},
  {"stepColorTemperature", "ddddd", processStepColorTemperatureCmd, "->Sends step color temp command: stepColorTemperature\r\n"},
  {"readColorControlAttr", "d", processColorControlReadAttrCmd, "->Sends read attribute command: readColorControlAttr <attr>\r\n"},
  {"writeColorControlAttr", "ddd", processColorControlWriteAttrCmd, "->Sends write attribute command: writeColorControlAttr <attr>\r\n"},
  {"colorLoopSet", "ddddd", processColorSetLoopCmd, "->Sends color loop set command: colorLoopSet\r\n"},

  {"getGroupIdentifiersReq", "d", processGetGroupIdentifiersReqCmd, "->Sends get group identifiers request command: getGroupIdentifiersReq <startIndx>\r\n"},
  {"getEndpointListReq", "d", processGetEndpointListReqCmd, "->Sends get endpoint list request command: getEndpointListReq <startIndx>\r\n"},
#endif // APP_ENABLE_CERTIFICATION_EXTENSION
  {0, 0, 0, 0},
};

static N_LinkInitiator_Device_t foundDevices[FOUND_DEVICES_ARRAY_SIZE];
static uint8_t foundDevicesAmount;

#if APP_ENABLE_CERTIFICATION_EXTENSION == 1
MAC_RxEnableReq_t rxEnableReq = {
  .MAC_RxEnableConf = NULL,
};
#endif // APP_ENABLE_CERTIFICATION_EXTENSION == 1

/******************************************************************************
                    Implementation section
******************************************************************************/
/**************************************************************************//**
\brief Sends single char to serial interface
******************************************************************************/
void consoleTx(char chr)
{
  appSnprintf(&chr);
  (void)chr;  /*Do nothing, just to avoid compiler warning*/
}

/**************************************************************************//**
\brief Processes single char read from serial interface

\param[in] char - read char
******************************************************************************/
void consoleTxStr(const char *str)
{
  appSnprintf(str);
  (void)str;  /*Do nothing, just to avoid compiler warning*/
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
  (void)args; /*Do nothing, just to avoid compiler warning*/
}

/**************************************************************************//**
\brief Processes reset command: reset device

\param[in] args - array of command arguments
******************************************************************************/
static void processResetCmd(const ScanValue_t *args)
{
  HAL_WarmReset();
  (void)args; /*Do nothing, just to avoid compiler warning*/
}

/**************************************************************************//**
\brief Processes touchlink command: starts touchlinking

\param[in] args - array of command arguments
******************************************************************************/
static void processTouchlinkCmd(const ScanValue_t *args)
{
  performTouchlink();
  (void)args;  /*Do nothing, just to avoid compiler warning*/
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
  restartActivity();
  //check groupId for the valid range
  if(args[2].uint16 >= validGroupIdMin && args[2].uint16 <= validGroupIdMax)
    colorSceneRemoteSendAddGroupCommand(args[0].uint16, args[1].uint8, args[2].uint16, NULL);
  else
  {
    appSnprintf("Enter valid groupId\r\n");
    appSnprintf("Min - %d & Max - %u\r\n",validGroupIdMin,validGroupIdMax);
  }
}

/**************************************************************************//**
\brief Processes transmit link info command

\param[in] args - array of command arguments
******************************************************************************/
static void processTransmitLinkInfoCmd(const ScanValue_t *args)
{
  restartActivity();
  linkInfoSendReadyToTransmitCommand(args[0].uint16, args[1].uint8);
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
\brief Processes get extended address command

\param[in] args - array of command arguments
******************************************************************************/
static void processGetExtAddrCmd(const ScanValue_t *args)
{
  const uint8_t* extAddr = N_DeviceInfo_GetIEEEAddress();

  for (uint8_t i = 0; i < 8; i++)
  {
    appSnprintf("%02x", extAddr[i]);
  }    
  appSnprintf("\r\n");
  (void)args; /*Do nothing, just to avoid compiler warning*/
  (void)extAddr; /*Do nothing, just to avoid compiler warning*/
}

/**************************************************************************//**
\brief Processes Link Initiator Scan command

\param[in] args - array of command arguments
******************************************************************************/
static void processPerformScanCmd(const ScanValue_t *args)
{
  N_LinkInitiator_Scan(args[0].uint8,            // scanType - see comments above
                       foundDevices,             // array to store found devices
                       FOUND_DEVICES_ARRAY_SIZE, // size of an array to store found devices
                       scanDone);                // callback function
}

/**************************************************************************//**
\brief Callback function about scanning completion

\param[in] status          - status of scanning
\param[in] numDevicesFound - amounr of found devices
******************************************************************************/
static void scanDone(N_LinkInitiator_Status_t status, uint8_t numDevicesFound)
{
  LOG_STRING(scanDoneStr, "Scan is Done\r\nStatus is %d\r\nDevice amount is %d\r\n");
  appSnprintf(scanDoneStr, status, numDevicesFound);
  foundDevicesAmount = numDevicesFound;
  (void)status;  /*Do nothing, just to avoid compiler warning*/
}

/**************************************************************************//**
\brief Processes Link Initiator reset device to FN command

\param[in] args - array of command arguments
******************************************************************************/
static void processResetDeviceToFnCmd(const ScanValue_t *args)
{
  sysAssert(foundDevicesAmount, REMOTECONSOLE_RESETDEVICETOFN_0);
  N_LinkInitiator_ResetDeviceToFactoryNew(&foundDevices[0], requestDone);
  (void)args; /*Do nothing, just to avoid compiler warning*/
}

/**************************************************************************//**
\brief Processes Link Initiator reset device to FN command

\param[in] args - array of command arguments
******************************************************************************/
static void processIdentifyDeviceCmd(const ScanValue_t *args)
{
  sysAssert(foundDevicesAmount, REMOTECONSOLE_IDENTIFYDEVICE_0);
  N_LinkInitiator_IdentifyStartRequest(&foundDevices[0],
                                       args[0].uint16,
                                       requestDone);
}

/**************************************************************************//**
\brief \brief Processes stop otau cmd

\param[in] args - array of command arguments
******************************************************************************/
static void processStopOtauCmd(const ScanValue_t *args)
{
#if (APP_USE_OTAU == 1)
  stopOtauClient();
#else
  LOG_STRING(otauErrorStr, "OTAU is not supported\r\n");
  appSnprintf(otauErrorStr);
#endif /* #if (APP_USE_OTAU == 1) */
  (void)args;
}

/**************************************************************************//**
\brief \brief Processes start otau cmd

\param[in] args - array of command arguments
******************************************************************************/
static void processStartOtauCmd(const ScanValue_t *args)
{
#if (APP_USE_OTAU == 1)
  startOtauClient();
#else
  LOG_STRING(otauErrorStr, "OTAU is not supported\r\n");
  appSnprintf(otauErrorStr);
#endif /* #if (APP_USE_OTAU == 1) */
  (void)args;
}

/**************************************************************************//**
\brief Callback function about request completion

\param[in] status          - status of scanning
******************************************************************************/
static void requestDone(N_LinkInitiator_Status_t status)
{
  LOG_STRING(requestDoneStr, "Done  0x%02x\r\n");
  appSnprintf(requestDoneStr, status);
  (void)status;  /*Do nothing, just to avoid compiler warning*/
}

#if APP_ENABLE_CERTIFICATION_EXTENSION == 0

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
\brief Processes move to hue and saturation command

\param[in] args - array of command arguments
******************************************************************************/
static void processSetColorCmd(const ScanValue_t *args)
{
  restartActivity();
  colorSceneRemoteSendMoveToHueAndSaturationCommand(determineAddressMode(args), args[1].uint16, args[2].uint8,
                                                               args[3].uint8, args[4].uint8, args[5].uint16);
}

/**************************************************************************//**
\brief Processes set brightness command

\param[in] args - array of command arguments
******************************************************************************/
static void processSetBrightnessCmd(const ScanValue_t *args)
{
  restartActivity();
  colorSceneRemoteSendMoveToLevelCommand(determineAddressMode(args), args[1].uint16, args[3].uint8, args[4].uint16, args[2].uint8);
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

  restartActivity();
  colorSceneRemoteSendOnOffCommand(determineAddressMode(args), args[1].uint16, command, args[2].uint8);
}

/**************************************************************************//**
\brief Processes identify command

\param[in] args - array of command arguments
******************************************************************************/
static void processIdentifyCmd(const ScanValue_t *args)
{
  restartActivity();
  colorSceneRemoteSendIdentifyCommand(determineAddressMode(args), args[1].uint16, args[2].uint8);
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

  restartActivity();
  colorSceneRemoteStoreRecallRemoveSceneCommand(determineAddressMode(args), args[1].uint16, args[2].uint8,
                                                command, args[4].uint16, args[5].uint8);
}

/**************************************************************************//**
\brief Processes remove group command

\param[in] args - array of command arguments
******************************************************************************/
static void processRemoveGroupCmd(const ScanValue_t *args)
{
  restartActivity();
  colorSceneRemoteSendRemoveGroupCommand(args[0].uint16, args[1].uint8, args[2].uint16);
}

#else // APP_ENABLE_CERTIFICATION_EXTENSION == 1

/**************************************************************************//**
\brief Processes get channel mask from config server command

\param[in] args - array of command arguments
******************************************************************************/
static void processGetCsChannelMask(const ScanValue_t *args)
{
  uint32_t channelMask;

  CS_ReadParameter(CS_CHANNEL_MASK_ID, &channelMask);
  appSnprintf("%08lx\r\n", channelMask);
  (void)args;
}

/**************************************************************************//**
\brief Processes on/off command

\param[in] args - array of command arguments
******************************************************************************/
static void processOnOffCmd(const ScanValue_t *args)
{
  restartActivity();
  colorSceneRemoteSendOnOffCommand(args[0].uint8);
}

/**************************************************************************//**
\brief Processes identify command

\param[in] args - array of command arguments
******************************************************************************/
static void processIdentifyCmd(const ScanValue_t *args)
{
  restartActivity();
  colorSceneRemoteSendIdentifyCommand(args[0].uint16);
}

/**************************************************************************//**
\brief Processes scene command

\param[in] args - array of command arguments
******************************************************************************/
static void processSceneCmd(const ScanValue_t *args)
{
  restartActivity();
  colorSceneRemoteStoreRecallRemoveSceneCommand(args[0].uint16, args[1].uint16, args[2].uint8);
}

/**************************************************************************//**
\brief Processes remove group command

\param[in] args - array of command arguments
******************************************************************************/
static void processRemoveGroupCmd(const ScanValue_t *args)
{
  restartActivity();
  colorSceneRemoteSendRemoveGroupCommand(args[0].uint16);
}

/**************************************************************************//**
\brief Processes remove all groups command

\param[in] args - array of command arguments
******************************************************************************/
static void processRemoveAllGroupsCmd(const ScanValue_t *args)
{
  restartActivity();
  colorSceneRemoteSendRemoveAllGroupsCommand();
  (void)args;
}

/**************************************************************************//**
\brief Processes mac ban node command

\param[in] args - array of command arguments
******************************************************************************/
static void processMacBanNodeCmd(const ScanValue_t *args)
{
  ExtAddr_t extAddr = ((uint64_t)args[0].uint32 << 32);
  extAddr |= args[1].uint32;
  LOG_STRING(setTypeDoneSTtr, "Done\r\n");

  MAC_BanNode(0, extAddr, 4, args[2].uint8);
  appSnprintf(setTypeDoneSTtr);
}

/**************************************************************************//**
\brief Processes mac ban node command

\param[in] args - array of command arguments
******************************************************************************/
static void processMacResetBanTableCmd(const ScanValue_t *args)
{
  LOG_STRING(setTypeDoneSTtr, "Done\r\n");

  MAC_ResetBanTable();
  appSnprintf(setTypeDoneSTtr);
  (void)args;
}

/**************************************************************************//**
\brief Processes Set Target Type command

\param[in] args - array of command arguments
******************************************************************************/
static void processSetTargetTypeCmd(const ScanValue_t *args)
{
  N_LinkTarget_SetTargetType(args[0].uint8, setTypeDone);
}

/**************************************************************************//**
\brief Set type routine completion callback
******************************************************************************/
static void setTypeDone(void)
{
  LOG_STRING(setTypeDoneSTtr, "Done\r\n");
  appSnprintf(setTypeDoneSTtr);
}

/**************************************************************************//**
\brief Processes Change channel command

\param[in] args - array of command arguments
******************************************************************************/
static void processSendNwkUpdateReqCmd(const ScanValue_t *args)
{
  N_Address_t dstAddress = {{0}, N_Address_Mode_Short, 0, 0};
  LOG_STRING(setTypeDoneSTtr, "Done\r\n");

  dstAddress.address.shortAddress = args[2].uint16;

  N_Zdp_SendMgmtNwkUpdateReq((1UL << args[0].uint8),
                             args[1].uint8, 0U,
                             NWK_GetUpdateId() + 1, 0U,
                             &dstAddress);
  restartActivity();
  appSnprintf(setTypeDoneSTtr);
}

/**************************************************************************//**
\brief Processes request for FN flag

\param[in] args - array of command arguments
******************************************************************************/
static void processIsDeviceFnCmd(const ScanValue_t *args)
{
  LOG_STRING(deviceFnStatusStr, "DeviceIsFN = %d\r\n");
  appSnprintf(deviceFnStatusStr, N_DeviceInfo_IsFactoryNew());
  (void)args;
}

/**************************************************************************//**
\brief Processes request for EndDevice flag

\param[in] args - array of command arguments
******************************************************************************/
static void processIsEndDeviceCmd(const ScanValue_t *args)
{
  LOG_STRING(deviceFnStatusStr, "IsEndDevice = %d\r\n");
  appSnprintf(deviceFnStatusStr, N_DeviceInfo_IsEndDevice());
  (void)args;
}

/**************************************************************************//**
\brief Processes request for device type obtaining

\param[in] args - array of command arguments
******************************************************************************/
static void processGetDeviceTypeCmd(const ScanValue_t *args)
{
  LOG_STRING(deviceFnStatusStr, "DeviceType = %d\r\n");
  appSnprintf(deviceFnStatusStr, N_DeviceInfo_IsEndDevice());
  (void)args;
}

/**************************************************************************//**
\brief Processes read Basic Cluster attribute command

\param[in] args - array of command arguments
******************************************************************************/
static void processReadBasicAttrCmd(const ScanValue_t *args)
{
  restartActivity();
  basicSendReadAttribute(args[0].uint16);
  (void)args;
}

/**************************************************************************//**
\brief Processes set addressing command

\param[in] args - array of command arguments
******************************************************************************/
static void processSetAddressingCmd(const ScanValue_t *args)
{
  DstAddressing_t dstAddressing;

  dstAddressing.mode = args[0].uint8;
  dstAddressing.addr = args[1].uint16;
  dstAddressing.ep = args[2].uint8;
  dstAddressing.manufacturerSpecCode = args[3].uint16;
  dstAddressing.defaultResponse = args[4].uint8;
  clustersSetDstAddressing(&dstAddressing);
}

/**************************************************************************//**
\brief Processes get network address command

\param[in] args - array of command arguments
******************************************************************************/
static void processGetNetworkAddressCmd(const ScanValue_t *args)
{
  appSnprintf("%04x\r\n", N_DeviceInfo_GetNetworkAddress());
  (void)args;
}

/**************************************************************************//**
\brief Processes send mgmt bind request command

\param[in] args - array of command arguments
******************************************************************************/
static void processSendMgmtBindReqCmd(const ScanValue_t *args)
{
  N_Address_t dstAddress = {{0}, N_Address_Mode_Short, 0, 0};
  LOG_STRING(doneStr, "Done\r\n");

  restartActivity();

  dstAddress.address.shortAddress = args[1].uint16;
  N_Zdp_SendMgmtBindReq(args[0].uint8,
                        &dstAddress);
  appSnprintf(doneStr);
}

/**************************************************************************//**
\brief Processes set nwk security command

\param[in] args - array of command arguments
******************************************************************************/
static void processSetNwkSecurityCmd(const ScanValue_t *args)
{
  CS_WriteParameter(CS_SECURITY_ON_ID, &args[0].uint8);
  (void)args;
}

/**************************************************************************//**
\brief Processes restart activity command

\param[in] args - array of command arguments
******************************************************************************/
static void processRestartActivityCmd(const ScanValue_t *args)
{
  restartActivity();
  (void)args;
}

/**************************************************************************//**
\brief Processes read On/off Cluster attribute command

\param[in] args - array of command arguments
******************************************************************************/
static void processReadOnOffAttrCmd(const ScanValue_t *args)
{
  restartActivity();
  onOffSendReadAttribute(args[0].uint16);
}

/**************************************************************************//**
\brief Processes off with effect command

\param[in] args - array of command arguments
******************************************************************************/
static void processOffWithEffectCmd(const ScanValue_t *args)
{
  restartActivity();
  colorSceneRemoteSendOffWithEffectCommand(args[0].uint8, args[1].uint8);
}

/**************************************************************************//**
\brief Processes on with timed off command

\param[in] args - array of command arguments
******************************************************************************/
static void processOnWithTimedOffCmd(const ScanValue_t *args)
{
  restartActivity();
  colorSceneRemoteSendOnWithTimedOffCommand(args[0].uint8, args[1].uint16, args[2].uint16);
}

/**************************************************************************//**
\brief Processes read level control attribute command

\param[in] args - array of command arguments
******************************************************************************/
static void processReadLevelControlAttrCmd(const ScanValue_t *args)
{
  restartActivity();
  levelControlSendReadAttribute(args[0].uint16);
}

/**************************************************************************//**
\brief Processes move command

\param[in] args - array of command arguments
******************************************************************************/
static void processMoveCmd(const ScanValue_t *args)
{
  restartActivity();
  colorSceneRemoteSendMoveCommand(args[0].uint8, args[1].uint8, args[2].uint8);
}

/**************************************************************************//**
\brief Processes step command

\param[in] args - array of command arguments
******************************************************************************/
static void processStepCmd(const ScanValue_t *args)
{
  restartActivity();
  colorSceneRemoteSendStepCommand(args[0].uint8, args[1].uint8, args[2].uint8, args[3].uint16);
}

/**************************************************************************//**
\brief Processes move to level command

\param[in] args - array of command arguments
******************************************************************************/
static void processMoveToLevelCmd(const ScanValue_t *args)
{
  restartActivity();
  colorSceneRemoteSendMoveToLevelCommand(args[0].uint8, args[1].uint8, args[2].uint16);
}

/**************************************************************************//**
\brief Processes level control command

\param[in] args - array of command arguments
******************************************************************************/
static void processLevelControlCmd(const ScanValue_t *args)
{
  restartActivity();
  colorSceneRemoteSendLevelControlCommand(args[0].uint8);
}

/**************************************************************************//**
\brief Processes write basic cluster attribute command

\param[in] args - array of command arguments
******************************************************************************/
static void processWriteBasicAttributeCmd(const ScanValue_t *args)
{
  uint32_t value = args[2].uint32;
  restartActivity();
  basicSendWriteAttribute(args[0].uint8, &value, args[1].uint8);
}

/**************************************************************************//**
\brief Processes read Identify Cluster attribute command

\param[in] args - array of command arguments
******************************************************************************/
static void processReadIdentifyAttrCmd(const ScanValue_t *args)
{
  restartActivity();
  identifySendReadAttribute(args[0].uint16);
}

/**************************************************************************//**
\brief Processes write Identify Cluster attribute command

\param[in] args - array of command arguments
******************************************************************************/
static void processWriteIdentifyAttributeCmd(const ScanValue_t *args)
{
  uint32_t value = args[2].uint32;
  restartActivity();
  identifySendWriteAttribute(args[0].uint8, &value, args[1].uint8);
}

/**************************************************************************//**
\brief Processes get channel command

\param[in] args - array of command arguments
******************************************************************************/
static void processGetChannelCmd(const ScanValue_t *args)
{
  appSnprintf("%d\r\n", N_DeviceInfo_GetNetworkChannel());
  (void)args;
}

/**************************************************************************//**
\brief Processes get channel mask command

\param[in] args - array of command arguments
******************************************************************************/
static void processGetChannelMaskCmd(const ScanValue_t *args)
{
  appSnprintf("%08lx\r\n", N_DeviceInfo_GetPrimaryChannelMask());
  (void)args;
}

/**************************************************************************//**
\brief Processes pseudo power off command

\param[in] args - array of command arguments
******************************************************************************/
static void processPseudoPowerOffCmd(const ScanValue_t *args)
{
  if (!rxEnableReq.MAC_RxEnableConf)
  {
    rxEnableReq.rxOnDuration = 0;
    rxEnableReq.MAC_RxEnableConf = rxEnableConf;
    MAC_RxEnableReq(&rxEnableReq);
  }
  (void)args;
}

/**************************************************************************//**
\brief Rx enable callback

\param[in] result - return code of join network procedure
******************************************************************************/
static void rxEnableConf(MAC_RxEnableConf_t *conf)
{
  /* Disable BitCloud tasks for preventing calls to the radio.
     HAL is enabled so it it allows to receive commands through UART. */
  SYS_DisableTask(ZDO_TASK_ID);
  SYS_DisableTask(APS_TASK_ID);
  SYS_DisableTask(NWK_TASK_ID);
  SYS_DisableTask(MAC_PHY_HWD_TASK_ID);
  (void)conf;
}

/**************************************************************************//**
\brief Processes Set Primary Channel Mask command

\param[in] args - array of command arguments
******************************************************************************/
static void processSetPrimaryChannelMaskCmd(const ScanValue_t *args)
{
  N_DeviceInfo_SetPrimaryChannelMask(args[0].uint32);
  (void)args;
}

/**************************************************************************//**
\brief Processes Set Secondary Channel Mask command

\param[in] args - array of command arguments
******************************************************************************/
static void processSetSecondaryChannelMaskCmd(const ScanValue_t *args)
{
  N_DeviceInfo_SetSecondaryChannelMask(args[0].uint32);
  (void)args;
}

/**************************************************************************//**
\brief Processes NWK Association console command

\param[in] args - array of command arguments
******************************************************************************/
static void processNwkAssociationCmd(const ScanValue_t *args)
{
  initiateStartingNetwork();

  (void)args;
}

/**************************************************************************//**
\brief Processes identify query command

\param[in] args - array of command arguments
******************************************************************************/
static void processIdentifyQueryCmd(const ScanValue_t *args)
{
  restartActivity();
  colorSceneRemoteSendIdentifyQueryCommand();
  (void)args;
}

/**************************************************************************//**
\brief Processes trigger effect command

\param[in] args - array of command arguments
******************************************************************************/
static void processTriggerEffectCmd(const ScanValue_t *args)
{
  restartActivity();
  colorSceneRemoteSendTriggerEffectCommand(args[0].uint8, args[1].uint8);
}

/**************************************************************************//**
\brief Processes write attributes undivided command

\param[in] args - array of command arguments
******************************************************************************/
static void processWriteAttrUndividedCmd(const ScanValue_t *args)
{
  ZCL_WriteAttributeReq_t *writeAttributeReq;
  CommandDescriptor_t *cmd;
  uint8_t attrLength;

  if (!(cmd = clustersAllocCommand()))
    return;

  writeAttributeReq = (ZCL_WriteAttributeReq_t *)cmd->payload.writeAttributesUndivided;

  for (uint8_t i = 0; i < 2; i++)
  {
    uint8_t indxShift = i * 3 + 1;

    attrLength = ZCL_GetAttributeLength(args[indxShift + 1].uint8, &args[indxShift + 2].uint8);
    writeAttributeReq->id = args[indxShift + 0].uint16;
    writeAttributeReq->type = args[indxShift + 1].uint8;
    memcpy(writeAttributeReq->value, &args[indxShift + 2].uint8, attrLength);

    writeAttributeReq = (ZCL_WriteAttributeReq_t *)((uint8_t *)writeAttributeReq +
                        sizeof(ZCL_WriteAttributeReq_t) - 1 + attrLength);
  }

  cmd->clusterId = args[0].uint16;
  cmd->commandId = ZCL_WRITE_ATTRIBUTES_UNDIVIDED_COMMAND_ID;
  cmd->size = (uint8_t *)writeAttributeReq - cmd->payload.writeAttributesUndivided;
  cmd->isAttributeOperation = true;

  restartActivity();
  clustersSendCommand(cmd);
}

/**************************************************************************//**
\brief Processes write attributes no response command

\param[in] args - array of command arguments
******************************************************************************/
static void processWriteAttrNoRespCmd(const ScanValue_t *args)
{
  CommandDescriptor_t *cmd;
  uint8_t attrLength;

  if (!(cmd = clustersAllocCommand()))
    return;

  attrLength = ZCL_GetAttributeLength(args[2].uint8, &args[3].uint8);

  cmd->clusterId = args[0].uint16;
  cmd->commandId = ZCL_WRITE_ATTRIBUTES_NO_RESPONSE_COMMAND_ID;
  cmd->payload.writeAttribute.id = args[1].uint16;
  cmd->payload.writeAttribute.type = args[2].uint8;
  memcpy(cmd->payload.writeAttribute.value, &args[3].uint8, attrLength);
  cmd->size = sizeof(uint16_t) + sizeof(uint8_t) + attrLength;
  cmd->isAttributeOperation = true;

  restartActivity();
  clustersSendCommand(cmd);
}

/**************************************************************************//**
\brief Processes get group membership command

\param[in] args - array of command arguments
******************************************************************************/
static void processGetGroupMembershipCmd(const ScanValue_t *args)
{
  restartActivity();
  colorSceneRemoteSendGetGroupMembershipCommand(args[0].uint8, &args[1].uint16);
}

/**************************************************************************//**
\brief Processes view group command

\param[in] args - array of command arguments
******************************************************************************/
static void processViewGroupCmd(const ScanValue_t *args)
{
  restartActivity();
  colorSceneRemoteSendViewGroupCommand(args[0].uint16);
}

/**************************************************************************//**
\brief Processes add group if identifying group command

\param[in] args - array of command arguments
******************************************************************************/
static void processAddGroupIfIdentifyingCmd(const ScanValue_t *args)
{
  restartActivity();
  colorSceneRemoteSendAddGroupIfIdentifyingCommand(args[0].uint16);
}

/**************************************************************************//**
\brief Processes read groups attribute command

\param[in] args - array of command arguments
******************************************************************************/
static void processReadGroupsAttrCmd(const ScanValue_t *args)
{
  restartActivity();
  groupsSendReadAttribute(args[0].uint16);
}

/**************************************************************************//**
\brief Processes get scene membership command

\param[in] args - array of command arguments
******************************************************************************/
static void processGetSceneMembershipCmd(const ScanValue_t *args)
{
  restartActivity();
  colorSceneRemoteGetSceneMembershipCommand(args[0].uint16);
}

/**************************************************************************//**
\brief Processes remove all scenes command

\param[in] args - array of command arguments
******************************************************************************/
static void processRemoveAllScenesCmd(const ScanValue_t *args)
{
  restartActivity();
  colorSceneRemoteRemoveAllScenesCommand(args[0].uint16);
}

/**************************************************************************//**
\brief Processes add scene command

\param[in] args - array of command arguments
******************************************************************************/
static void processAddSceneCmd(const ScanValue_t *args)
{
  restartActivity();
  colorSceneRemoteAddSceneCommand(args[0].uint16, args[1].uint8, args[2].uint16);
}

/**************************************************************************//**
\brief Processes remove scene command

\param[in] args - array of command arguments
******************************************************************************/
static void processRemoveSceneCmd(const ScanValue_t *args)
{
  restartActivity();
  colorSceneRemoteRemoveSceneCommand(args[0].uint16, args[1].uint8);
}

/**************************************************************************//**
\brief Processes enhanced add scene command

\param[in] args - array of command arguments
******************************************************************************/
static void processEnhancedAddSceneCmd(const ScanValue_t *args)
{
  restartActivity();
  colorSceneRemoteEnhancedAddSceneCommand(args[0].uint16, args[1].uint8, args[2].uint16);
}

/**************************************************************************//**
\brief Processes copy scene command

\param[in] args - array of command arguments
******************************************************************************/
static void processCopySceneCmd(const ScanValue_t *args)
{
  restartActivity();
  colorSceneRemoteCopySceneCommand(args[0].uint16, args[1].uint8, args[2].uint16, args[3].uint8, args[4].uint8);
}

/**************************************************************************//**
\brief Processes read scenes attribute command

\param[in] args - array of command arguments
******************************************************************************/
static void processReadScenesAttrCmd(const ScanValue_t *args)
{
  restartActivity();
  scenesSendReadAttribute(args[0].uint16);
}

/**************************************************************************//**
\brief Processes move to hue command

\param[in] args - array of command arguments
******************************************************************************/
static void processMoveToHueCmd(const ScanValue_t *args)
{
  restartActivity();
  colorSceneRemoteSendMoveToHueCommand(args[0].uint8, args[1].uint8, args[2].uint16);
}

/**************************************************************************//**
\brief Processes move hue command

\param[in] args - array of command arguments
******************************************************************************/
static void processMoveHueCmd(const ScanValue_t *args)
{
  restartActivity();
  colorSceneRemoteSendMoveHueCommand(args[0].uint8, args[1].uint8);
}

/**************************************************************************//**
\brief Processes step hue command

\param[in] args - array of command arguments
******************************************************************************/
static void processStepHueCmd(const ScanValue_t *args)
{
  restartActivity();
  colorSceneRemoteSendStepHueCommand(args[0].uint8, args[1].uint8, args[2].uint16);
}

/**************************************************************************//**
\brief Processes move to saturation command

\param[in] args - array of command arguments
******************************************************************************/
static void processMoveToSaturationCmd(const ScanValue_t *args)
{
  restartActivity();
  colorSceneRemoteSendMoveToSaturationCommand(args[0].uint8, args[1].uint16);
}

/**************************************************************************//**
\brief Processes move saturation command

\param[in] args - array of command arguments
******************************************************************************/
static void processMoveSaturationCmd(const ScanValue_t *args)
{
  restartActivity();
  colorSceneRemoteSendMoveSaturationCommand(args[0].uint8, args[1].uint8);
}

/**************************************************************************//**
\brief Processes step saturation command

\param[in] args - array of command arguments
******************************************************************************/
static void processStepSaturationCmd(const ScanValue_t *args)
{
  restartActivity();
  colorSceneRemoteSendStepSaturationCommand(args[0].uint8, args[1].uint8, args[2].uint16);
}

/**************************************************************************//**
\brief Processes move to hue and saturation command

\param[in] args - array of command arguments
******************************************************************************/
static void processMoveToHueAndSaturationCmd(const ScanValue_t *args)
{
  restartActivity();
  colorSceneRemoteSendMoveToHueAndSaturationCommandCert(args[0].uint8, args[1].uint8, args[2].uint16);
}

/**************************************************************************//**
\brief Processes move to color command

\param[in] args - array of command arguments
******************************************************************************/
static void processMoveToColorCmd(const ScanValue_t *args)
{
  restartActivity();
  colorSceneRemoteSendMoveToColorCommand(args[0].uint16, args[1].uint16, args[2].uint16);
}

/**************************************************************************//**
\brief Processes move color command

\param[in] args - array of command arguments
******************************************************************************/
static void processMoveColorCmd(const ScanValue_t *args)
{
  restartActivity();
  colorSceneRemoteSendMoveColorCommand(args[0].int16, args[1].int16);
}

/**************************************************************************//**
\brief Processes step color command

\param[in] args - array of command arguments
******************************************************************************/
static void processStepColorCmd(const ScanValue_t *args)
{
  restartActivity();
  colorSceneRemoteSendStepColorCommand(args[0].int16, args[1].int16, args[2].uint16);
}

/**************************************************************************//**
\brief Processes enhanced move to hue command

\param[in] args - array of command arguments
******************************************************************************/
static void processEnhancedMoveToHueCmd(const ScanValue_t *args)
{
  restartActivity();
  colorSceneRemoteSendEnhancedMoveToHueCommand(args[0].uint16, args[1].uint8, args[2].uint16);
}

/**************************************************************************//**
\brief Processes enhanced move hue command

\param[in] args - array of command arguments
******************************************************************************/
static void processEnhancedMoveHueCmd(const ScanValue_t *args)
{
  restartActivity();
  colorSceneRemoteSendEnhancedMoveHueCommand(args[0].uint16, args[1].uint16);
}

/**************************************************************************//**
\brief Processes enhanced step hue command

\param[in] args - array of command arguments
******************************************************************************/
static void processEnhancedStepHueCmd(const ScanValue_t *args)
{
  restartActivity();
  colorSceneRemoteSendEnhancedStepHueCommand(args[0].uint8, args[1].uint16, args[2].uint16);
}

/**************************************************************************//**
\brief Processes enhanced move to hue and saturation command

\param[in] args - array of command arguments
******************************************************************************/
static void processEnhancedMoveToHueAndSaturationCmd(const ScanValue_t *args)
{
  restartActivity();
  colorSceneRemoteSendEnhancedMoveToHueAndSaturationCommand(args[0].uint16, args[1].uint8, args[2].uint16);
}

/**************************************************************************//**
\brief Processes MoveStepHue command

\param[in] args - array of command arguments
******************************************************************************/
static void processMoveStepHueCmd(const ScanValue_t *args)
{
  restartActivity();
  colorSceneRemoteSendMoveStepHueCommand();
  (void)args;
}

/**************************************************************************//**
\brief Processes move to color temperature command

\param[in] args - array of command arguments
******************************************************************************/
static void processMoveToColorTemperatureCmd(const ScanValue_t *args)
{
  restartActivity();
  colorSceneRemoteSendMoveToColorTemperatureCommandCert(args[0].uint16, args[1].uint16);
}

/**************************************************************************//**
\brief Processes move color temperature command

\param[in] args - array of command arguments
******************************************************************************/
static void processMoveColorTemperatureCmd(const ScanValue_t *args)
{
  restartActivity();
  colorSceneRemoteSendMoveColorTemperatureCommandCert(args[0].uint8, args[1].uint16, args[2].uint16, args[3].uint16);
}

/**************************************************************************//**
\brief Processes step color temperature command

\param[in] args - array of command arguments
******************************************************************************/
static void processStepColorTemperatureCmd(const ScanValue_t *args)
{
  restartActivity();
  colorSceneRemoteSendStepColorTemperatureCommandCert(args[0].uint8, args[1].uint16, args[2].uint16, args[3].uint16, args[4].uint16);
}

/**************************************************************************//**
\brief Processes color control read attribute command

\param[in] args - array of command arguments
******************************************************************************/
static void processColorControlReadAttrCmd(const ScanValue_t *args)
{
  restartActivity();
  colorControlSendReadAttribute(args[0].uint16);
}

/**************************************************************************//**
\brief Processes color control write attribute command

\param[in] args - array of command arguments
******************************************************************************/
static void processColorControlWriteAttrCmd(const ScanValue_t *args)
{
  uint32_t value = args[2].uint32;

  restartActivity();
  colorControlSendWriteAttribute(args[0].uint16, &value, args[1].uint8);
}

/**************************************************************************//**
\brief Processes color set loop command

\param[in] args - array of command arguments
******************************************************************************/
static void processColorSetLoopCmd(const ScanValue_t *args)
{
  restartActivity();
  colorSceneRemoteSendColorLoopSetCommand(args[0].uint8, args[1].uint8, args[2].uint8,
                                          args[3].uint16, args[4].uint16);
}

/**************************************************************************//**
\brief Processes send get group identifiers request command

\param[in] args - array of command arguments
******************************************************************************/
static void processGetGroupIdentifiersReqCmd(const ScanValue_t *args)
{
  colorSceneRemoteSendGroupIdentifiersReqCommand(args[0].uint8);
}

/**************************************************************************//**
\brief Processes send get endpoint list request command

\param[in] args - array of command arguments
******************************************************************************/
static void processGetEndpointListReqCmd(const ScanValue_t *args)
{
  colorSceneRemoteSendEndpointListReqCommand(args[0].uint8);
}

#endif // APP_ENABLE_CERTIFICATION_EXTENSION

#endif // APP_ENABLE_CONSOLE == 1
#endif // APP_ZLL_DEVICE_TYPE == APP_DEVICE_TYPE_COLOR_SCENE_REMOTE

// eof colorSceneRemoteConsole.c
