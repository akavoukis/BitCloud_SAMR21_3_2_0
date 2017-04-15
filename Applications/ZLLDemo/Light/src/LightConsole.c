/**************************************************************************//**
  \file lightConsole.c

  \brief
    Light console implementation.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    10.04.2012 N.Fomin - Created
******************************************************************************/
#if APP_ZLL_DEVICE_TYPE >= APP_DEVICE_TYPE_ON_OFF_LIGHT
#if APP_ENABLE_CONSOLE == 1

/******************************************************************************
                    Includes section
******************************************************************************/
#include <mac.h>
#include <nwk.h>
#include <aps.h>
#include <zllDemo.h>
#include <uartManager.h>
#include <console.h>
#include <resetReason.h>
#include <pdsDataServer.h>
#include <lightBasicCluster.h>
#include <lightCommissioningCluster.h>
#include <commandManager.h>
#include <otauService.h>

#include <lightBindings.h>
#include <N_DeviceInfo_bindings.h>
#include <N_Connection.h>
#include <N_LinkTarget.h>
#include <N_DeviceInfo.h>

/******************************************************************************
                    Prototypes section
******************************************************************************/
static void processHelpCmd(const ScanValue_t *args);
static void processResetCmd(const ScanValue_t *args);
static void processResetToFnCmd(const ScanValue_t *args);
static void processResetToFdCmd(const ScanValue_t *args);
static void processSetTargetTypeCmd(const ScanValue_t *args);
static void setTypeDone(void);
static void processGetExtAddrCmd(const ScanValue_t *args);
static void processMacBanNodeCmd(const ScanValue_t *args);
static void processMacResetBanTableCmd(const ScanValue_t *args);
static void processJoinNetworkCmd(const ScanValue_t *args);
static void joinNetworkDone(N_Connection_Result_t result);
static void processSetPermitJoinCmd(const ScanValue_t *args);
static void zdoPermitJoiningResponse(ZDO_ZdpResp_t *resp);
static void processNwkAssociationCmd(const ScanValue_t *args);
static void processIsDeviceFnCmd(const ScanValue_t *args);
static void processIsEndDeviceCmd(const ScanValue_t *args);
static void processGetDeviceTypeCmd(const ScanValue_t *args);
static void processGetNetworkAddressCmd(const ScanValue_t *args);
static void processApsBindReqCmd(const ScanValue_t *args);
static void processSetNwkSecurityCmd(const ScanValue_t *args);
static void processReadBasicAttrCmd(const ScanValue_t *args);
static void processSetAddressingCmd(const ScanValue_t *args);
static void processGetChannelCmd(const ScanValue_t *args);
static void processGetChannelMaskCmd(const ScanValue_t *args);
static void processSetPrimaryChannelMaskCmd(const ScanValue_t *args);
static void processSetSecondaryChannelMaskCmd(const ScanValue_t *args);
static void processPseudoPowerOffCmd(const ScanValue_t *args);
static void rxEnableConf(MAC_RxEnableConf_t *conf);
static void processSendEndpointInformationCmd(const ScanValue_t *args);
static void processStopOtauCmd(const ScanValue_t *args);
static void processStartOtauCmd(const ScanValue_t *args);

/******************************************************************************
                    Local variables
******************************************************************************/
static ZDO_ZdpReq_t permitJoinReq;
static uint8_t  readBuffer[USART_RX_BUFFER_LENGTH];
static const ConsoleCommand_t cmds[] =
{
  {"help", "", processHelpCmd, "->Show help you're reading now: help\r\n"},
  {"reset", "", processResetCmd, "->Reset device\r\n"},
  {"resetToFN", "", processResetToFnCmd, "Reset to Factory New, persistant items retained: resetToFN\r\n"},
  {"resetToFD", "", processResetToFdCmd, "Reset to Factory Default, deletes everything including persistant items: resetToFD\r\n"},
  {"setTargetType", "d", processSetTargetTypeCmd, "-> Sets target type: setTargetType <type>\r\n"},
  {"devInfoGetExtAddr", "", processGetExtAddrCmd, "-> Gets ExtAddr: devInfoGetExtAddr\r\n"},
  {"macBanNode", "ddd", processMacBanNodeCmd, "-> Sets specified link cost: <extAddr> <cost>\r\n"},
  {"macResetBanTable", "", processMacResetBanTableCmd, "-> Resets mac ban table\r\n"},
  {"joinNetwork", "dddddd", processJoinNetworkCmd, "-> Enters to network: joinNetwork [ePanIdHigh] [ePanIdLow] [ch] [panId] [addr] [updateId]\r\n\r\n"},
  {"setPermitJoin", "d", processSetPermitJoinCmd, "-> Sets Permit Join: setPermitJoin [dur]\r\n"},
  {"nwkAssociation", "", processNwkAssociationCmd, "-> Associates to network been found\r\n"},
  {"isDeviceFn", "", processIsDeviceFnCmd, "-> Request for device FN flag: isDeviceFn\r\n"},
  {"isEndDevice", "", processIsEndDeviceCmd, "-> Check if device is EndDevice: isEndDevice\r\n"},
  {"getDeviceType", "", processGetDeviceTypeCmd, "-> Request for device type: getDeviceType\r\n"},
  {"getNetworkAddress", "", processGetNetworkAddressCmd, "-> Returns network address: getNetworkAddress\r\n"},
  {"apsBindReq", "ddddd", processApsBindReqCmd, \
   "-> Performs APS bind:\r\n apsBindReq <mspDestExtAddr> <lspDestExtAddr> <srcEp> <dstEp> <clusterId>\r\n"},
  {"readBasicAttr", "d", processReadBasicAttrCmd, "->Reads Basic cluster Attribure:\r\n \
    readBasicAttr <attrId> <security>\r\n"},
  {"setAddressing", "ddddd", processSetAddressingCmd, "-> Set addressing: setAddressing <mode> <addr> <dstEp> <manSpec> <defaultResp>\r\n"},
  {"setNwkSecurity", "d", processSetNwkSecurityCmd, "-> Enable/disable NWK security: setNwkSecurityReq <enable>\r\n"},
  {"getChannel", "", processGetChannelCmd, "-> Returns current channel: getChannel\r\n"},
  {"getChannelMask", "", processGetChannelMaskCmd, "-> Returns current channel mask: getChannelMask\r\n"},
  {"setPrimaryChannelMask", "d", processSetPrimaryChannelMaskCmd, "-> Sets primary channel mask: setPrimaryChannelMask [mask]\r\n"},
  {"setSecondaryChannelMask", "d", processSetSecondaryChannelMaskCmd, "-> Sets secondary channel mask: setSecondaryChannelMask [mask]\r\n"},
  {"powerOff", "", processPseudoPowerOffCmd, "-> Powers off device: powerOff\r\n"},
  {"sendEndpointInformation", "d", processSendEndpointInformationCmd, "->Sends endpoint information command: sendEndpointInformation <ep>\r\n"},
  {"stopOtau", "", processStopOtauCmd, "Stop OTAU process\r\n"},
  {"startOtau", "", processStartOtauCmd, "Start OTAU process after stop\r\n"},
  {0, 0, 0, 0},
};

MAC_RxEnableReq_t rxEnableReq = {
  .MAC_RxEnableConf = NULL,
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
  (void)chr;
}

/**************************************************************************//**
\brief Processes single char read from serial interface

\param[in] char - read char
******************************************************************************/
void consoleTxStr(const char *str)
{
  appSnprintf(str);
  (void)str;
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
  (void)args;
  (void)extAddr;
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
\brief Creates new network with specified parameters

\param[in] args - array of command arguments
******************************************************************************/
static void processJoinNetworkCmd(const ScanValue_t *args)
{
  ExtPanId_t extPanId = ((uint64_t)args[0].uint32 << 32);
  extPanId |= args[1].uint32;

  uint8_t key[] = {
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x01,
  };

  N_Connection_JoinNetwork((uint8_t*)&extPanId,   /* ExtPanId */
                           args[2].uint8,         /* Channel */
                           args[3].uint16,        /* PanId */
                           args[4].uint16,        /* NwkAddr */
                           args[5].uint8,         /* NwkUpdateId */
                           key, /* NwkKey */
                           joinNetworkDone);      /* Callback */
}

/**************************************************************************//**
\brief Join network done callback

\param[in] result - return code of join network procedure
******************************************************************************/
static void joinNetworkDone(N_Connection_Result_t result)
{
  LOG_STRING(settingStr, "Join to the network is done - %d\r\n");
  appSnprintf(settingStr, result);
  (void)result;
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
\brief Processes get network address command

\param[in] args - array of command arguments
******************************************************************************/
static void processGetNetworkAddressCmd(const ScanValue_t *args)
{
  appSnprintf("%04x\r\n", N_DeviceInfo_GetNetworkAddress());
  (void)args;
}


/**************************************************************************//**
\brief Processes APS bind request command

\param[in] args - array of command arguments
******************************************************************************/
static void processApsBindReqCmd(const ScanValue_t *args)
{
  APS_BindReq_t apsBindReq;
  ExtAddr_t ownExtAddr;
  ExtAddr_t remoteExtAddr = ((uint64_t)args[0].uint32 << 32);
  LOG_STRING(doneStr, "Done\r\n");

  remoteExtAddr |= args[1].uint32;

  CS_ReadParameter(CS_UID_ID, &ownExtAddr);
  apsBindReq.srcAddr = ownExtAddr;
  apsBindReq.srcEndpoint = args[2].uint8;
  apsBindReq.clusterId = args[4].uint16;
  apsBindReq.dstAddrMode = APS_EXT_ADDRESS;
  apsBindReq.dst.unicast.extAddr = remoteExtAddr;
  apsBindReq.dst.unicast.endpoint = args[3].uint8;
  APS_BindReq(&apsBindReq);

  if (APS_SUCCESS_STATUS == apsBindReq.confirm.status)
    appSnprintf(doneStr);
}

/**************************************************************************//**
\brief Processes set nwk security command

\param[in] args - array of command arguments
******************************************************************************/
static void processSetNwkSecurityCmd(const ScanValue_t *args)
{
  CS_WriteParameter(CS_SECURITY_ON_ID, &args[0].uint8);
}

/**************************************************************************//**
\brief Processes read Basic Cluster attribute command

\param[in] args - array of command arguments
******************************************************************************/
static void processReadBasicAttrCmd(const ScanValue_t *args)
{
  basicSendReadAttribute(args[0].uint16);
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
}

/**************************************************************************//**
\brief Processes Set Secondary Channel Mask command

\param[in] args - array of command arguments
******************************************************************************/
static void processSetSecondaryChannelMaskCmd(const ScanValue_t *args)
{
  N_DeviceInfo_SetSecondaryChannelMask(args[0].uint32);
}

/**************************************************************************//**
\brief Processes send endpoint information command

\param[in] args - array of command arguments
******************************************************************************/
static void processSendEndpointInformationCmd(const ScanValue_t *args)
{
  ZCL_Addressing_t addressing;
  fillDstAddressing(&addressing);
  addressing.clusterSide = ZCL_CLUSTER_SIDE_CLIENT;
  sendEndpointInformation(&addressing);
  (void)args;
}

/**************************************************************************//**
\brief Processes stop otau cmd

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
\brief Processes start otau cmd

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
\brief Processes Set Permit Join command

\param[in] args - array of command arguments
******************************************************************************/
static void processSetPermitJoinCmd(const ScanValue_t *args)
{
  ZDO_MgmtPermitJoiningReq_t *permit = &permitJoinReq.req.reqPayload.mgmtPermitJoiningReq;

  permitJoinReq.ZDO_ZdpResp = zdoPermitJoiningResponse;
  permitJoinReq.reqCluster = MGMT_PERMIT_JOINING_CLID;
  permitJoinReq.dstAddrMode = APS_SHORT_ADDRESS;

  permitJoinReq.dstAddress.shortAddress = N_DeviceInfo_GetNetworkAddress();

  permit->permitDuration = args[0].uint8;
  permit->tcSignificance = 0x01;

  ZDO_ZdpReq(&permitJoinReq);
}

/**************************************************************************//**
\brief ZDP device announce response callback

\param[in] leaveResp - pointer to response structure
******************************************************************************/
static void zdoPermitJoiningResponse(ZDO_ZdpResp_t *resp)
{
  LOG_STRING(permitJoinDoneStr, "setPermitJoinRsp %d\r\n");
  appSnprintf(permitJoinDoneStr, resp->respPayload.status);
  (void)resp;
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

#endif // APP_ENABLE_CONSOLE == 1
#endif // APP_ZLL_DEVICE_TYPE >= APP_DEVICE_TYPE_ON_OFF_LIGHT

// eof lightConsole.c
