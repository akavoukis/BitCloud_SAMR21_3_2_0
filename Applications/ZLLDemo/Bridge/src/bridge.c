/**************************************************************************//**
  \file bridge.c

  \brief
    Control Bridge device implementation.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2013, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    26/12/14 Prashanth.Udumula - modified
******************************************************************************/

#if APP_ZLL_DEVICE_TYPE == APP_DEVICE_TYPE_BRIDGE

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zllDemo.h>
#include <pdsDataServer.h>
#include <zcl.h>
#include <commandManager.h>
#include <networkJoining.h>
#include <resetReason.h>
#include <bridgeBasicCluster.h>
#include <uartManager.h>
#include <console.h>
#include <bridgeClusters.h>
#include <otauService.h>
#include <bspUid.h>

#include <bridgeBindings.h>
#include <N_LinkInitiator.h>
#include <N_LinkInitiator_Init.h>
#include <N_LinkTarget.h>
#include <N_LinkTarget_Init.h>
#include <N_Connection.h>
#include <N_ConnectionRouter_Init.h>
#include <N_DeviceInfo_Bindings.h>
#include <N_DeviceInfo.h>
#include <N_DeviceInfo_Init.h>
#include <N_Task_Bindings.h>
#include <N_Task.h>
#include <N_Task_Init.h>
#include <N_Util.h>
#include <N_Timer_Bindings.h>
#include <N_Timer.h>
#include <N_Timer_Init.h>
#include <errH.h>
#include <S_Nv_Bindings.h>
#include <S_Nv.h>
#include <S_Nv_Init.h>
#include <N_Radio.h>
#include <N_Radio_Init.h>
#include <N_Cmi.h>
#include <N_Cmi_Init.h>
#include <N_AddressManager_Bindings.h>
#include <N_AddressManager.h>
#include <N_AddressManager_Init.h>
#include <N_InterPan_Bindings.h>
#include <N_InterPan.h>
#include <N_InterPan_Init.h>
#include <N_ZllEndpoint.h>
#include <N_PacketDistributor.h>
#include <N_Hac.h>
#include <N_Zdp.h>

/******************************************************************************
                    Definitions section
******************************************************************************/
#define TOUCHLINK_RSSI_CORRECTION         10u
#define TOUCHLINK_RSSI_THRESHOLD          -60
#define INTERPAN_PERIOD                   10000u

/******************************************************************************
                    Types section
******************************************************************************/
typedef enum _AppState_t
{
  APP_INITING,
  APP_JOINING_PRIMARY_HA,
  APP_JOINING_SECONDARY_HA,
  APP_JOINING,
  APP_INTERPANNING,
  APP_WORKING,
  APP_LEAVING_NETWORK,
} AppState_t;

/******************************************************************************
                    Prototypes section
******************************************************************************/
static void init(void);
static void appResetToFactoryNew(void);
static void initMacLayerDone(void);
static bool Bridge_EventHandler(N_Task_Event_t evt);
static void setTargetTypeDone(void);
static void startNetworkDone(void);
static void interPanModeTimerFired(void);
static void IdentifyStartIndication(uint16_t timeoutInSec);

/******************************************************************************
                    Local variables
******************************************************************************/
static AppState_t     appState = APP_INITING;
static ZLL_Endpoint_t appEndpoint;

static bool resetToFactoryNew = false;

static const N_Task_HandleEvent_t s_taskArray[] =
{
  // Add tasks here.
  Bridge_EventHandler,
  N_ConnectionRouter_EventHandler,
  N_LinkInitiator_EventHandler,
  N_DeviceInfo_EventHandler,
  N_LinkTarget_EventHandler,
};

static const struct N_LinkTarget_Callback_t targetCallbacks =
{
  NULL,//  ScanIndication,
  IdentifyStartIndication,//  IdentifyStartIndication,
  NULL,//  IdentifyStopIndication,
  NULL,//  ResetIndication,
  NULL,//  JoinNetworkIndication
  NULL,//  UpdateNetworkIndication,
  -1
};

static bool s_initDone = FALSE;

static HAL_AppTimer_t interPanModeTimer =
{
  .mode     = TIMER_ONE_SHOT_MODE,
  .interval = INTERPAN_PERIOD,
  .callback = interPanModeTimerFired
};

/******************************************************************************
                    Implementation section
******************************************************************************/

/**************************************************************************//**
\brief Bridge event handler

\param[in] evt - event id

\returns true if event was proccessed, false - otherwise
******************************************************************************/
static bool Bridge_EventHandler(N_Task_Event_t evt)
{
  (void)evt;
  return true;
}

/**************************************************************************//**
\brief Start application initialization
******************************************************************************/
static void init(void)
{
  ExtAddr_t uid;

  //Reads the UID set in configuration.h
  CS_ReadParameter(CS_UID_ID,&uid);
  if (uid == 0 || uid > APS_MAX_UNICAST_EXT_ADDRESS)
  {
    BSP_ReadUid(&uid); //Will read the UID from chip
    CS_WriteParameter(CS_UID_ID, &uid); //Writes the read UID to the ram
  }
  ZCL_DeviceEndpoint_t *ep = &appEndpoint.deviceEndpoint;
  bridgeAddOTAUServerCluster();
  /* Configure and register an endpoint */
  ep->simpleDescriptor.endpoint = APP_ENDPOINT_BRIDGE;
  ep->simpleDescriptor.AppProfileId = APP_PROFILE_ID;
  ep->simpleDescriptor.AppDeviceVersion = APP_VERSION;
  ep->simpleDescriptor.AppDeviceId = APP_DEVICE_ID;
  ep->simpleDescriptor.AppInClustersCount = BRIDGE_SERVER_CLUSTERS_COUNT;
  ep->simpleDescriptor.AppInClustersList = bridgeServerClusterIds;
  ep->simpleDescriptor.AppOutClustersCount = BRIDGE_CLIENT_CLUSTERS_COUNT;
  ep->simpleDescriptor.AppOutClustersList = bridgeClientClusterIds;
  ep->serverCluster = bridgeServerClusters;
  ep->clientCluster = bridgeClientClusters;
  // Register the end point with AF layer 
  // to handle the frames with ProfileId different from destination endpoint's profile id
  N_Hac_RegisterEndpoint(&appEndpoint, 0u);

  startOtauServer();

  /* Initialize the supported clusters */
  clustersInit();
  basicClusterInit();
#if (APP_ENABLE_CONSOLE == 1) || (APP_DEVICE_EVENTS_LOGGING == 1)
   uartInit();
#endif
#if APP_ENABLE_CONSOLE == 1
   initConsole();
#endif

  N_Task_Init((uint8_t)N_UTIL_ARRAY_SIZE(s_taskArray), s_taskArray);
  N_Timer_Init();
  errHInit();
  N_DeviceInfo_Init(TOUCHLINK_RSSI_CORRECTION, TOUCHLINK_RSSI_THRESHOLD, TRUE, TRUE, TOUCHLINK_ZERO_DBM_TX_POWER);
  N_Radio_Init();
  N_Cmi_Init();
  N_Cmi_UseNwkMulticast(FALSE);
  N_Cmi_InitMacLayer(initMacLayerDone);
}

/**************************************************************************//**
\brief Continue application initialization after MAC layer configuration
******************************************************************************/
static void initMacLayerDone(void)
{
  N_DeviceInfo_SetPrimaryChannelMask(APP_PRIMARY_CHANNELS_MASK);
  N_DeviceInfo_SetSecondaryChannelMask(APP_SECONDARY_CHANNELS_MASK);
  N_AddressManager_Init();
  N_ConnectionRouter_Init();
  N_InterPan_Init();
  N_LinkInitiator_Init();
  N_LinkTarget_Init();

  s_initDone = TRUE;

  // Subcribing
  N_LinkTarget_Subscribe(&targetCallbacks);

  if (N_DeviceInfo_IsFactoryNew())
    initiateStartingNetwork();
  else
  {
    appState = APP_WORKING;
    N_LinkTarget_SetTargetType(N_LinkTarget_TargetType_Touchlink, setTargetTypeDone);
  }
}

/**************************************************************************//**
\brief Callback about setting target type
******************************************************************************/
static void setTargetTypeDone(void)
{}

/**************************************************************************//**
\brief Checks if initialization has been done
******************************************************************************/
bool N_Init_IsInitDone(void)
{
  return s_initDone;
}

/**************************************************************************//**
\brief ResetToFactoryNew execution routine
******************************************************************************/
static void appResetToFactoryNew(void)
{
  PDS_DeleteAll(false);
  N_DeviceInfo_SetFactoryNew(true);
  HAL_WarmReset();
}

/**************************************************************************//**
\brief Sends permit join request to all devices in the network

\param[in] permitJoin - join permittion value
******************************************************************************/
void sendPermitJoinCommand(bool permitJoin)
{
  N_Address_t address =
  {
    .address.shortAddress = 0xfffd,
    .addrMode             = N_Address_Mode_Broadcast,
    .endPoint             = 0xff,
    .panId                = 0
  };

  N_Zdp_SendMgmtPermitJoiningReq(permitJoin ? 0xFF : 0x00, 0x01, &address);
}

/**************************************************************************//**
\brief Performs network discovery, network join and target type setting.
******************************************************************************/
void initiateStartingNetwork(void)
{
  appState = APP_JOINING;
  startNetwork(startNetworkDone);
}

/**************************************************************************//**
\brief Post application task if it in APP_JOINING state.
******************************************************************************/
void postStartNetworkTask(void)
{
  if (APP_JOINING == appState)
    SYS_PostTask(APL_TASK_ID);
}

/**************************************************************************//**
\brief Callback which is called after start network procedure.
******************************************************************************/
static void startNetworkDone(void)
{
  appState = APP_WORKING;
  N_LinkTarget_SetTargetType(N_LinkTarget_TargetType_Touchlink, setTargetTypeDone);
}

/**************************************************************************//**
\brief Network update notification

\param notify - update notification parameters
******************************************************************************/
void ZDO_MgmtNwkUpdateNotf(ZDO_MgmtNwkUpdateNotf_t *notify)
{
  if (ZDO_NETWORK_LEFT_STATUS == notify->status)
  {
    if (resetToFactoryNew)
    {
      appResetToFactoryNew();
    }
  }
  else if (ZDO_NWK_UPDATE_STATUS == notify->status)
  {
  }
}

/**************************************************************************//**
\brief Application task handler - implements applications state machine
******************************************************************************/
void APL_TaskHandler(void)
{
  switch (appState)
  {
    case APP_INITING:
      {
        init();
      }
      break;
    case APP_WORKING:
      break;
    case APP_JOINING:
      startNetworkHandler();
      break;
    default:
      break;
  }
}

/**************************************************************************//**
\brief Application entry point.
******************************************************************************/
int main(void)
{
  SYS_SysInit();

  /* The main infinite operating loop */
  while (1)
  {
    SYS_RunTask();
  }
}

/**************************************************************************//**
\brief Starts identifying for the specified duration.

\param[in] timeoutInSec - identifying duration
******************************************************************************/
static void IdentifyStartIndication(uint16_t timeoutInSec)
{
  HAL_StopAppTimer(&interPanModeTimer);
  HAL_StartAppTimer(&interPanModeTimer);

  (void)timeoutInSec;
}

/**************************************************************************//**
\brief Wake up indication called when the device wakes up
******************************************************************************/
void ZDO_WakeUpInd(void)
{
}

/**************************************************************************//**
\brief InterPan mode timer fired
******************************************************************************/
static void interPanModeTimerFired(void)
{
  N_LinkTarget_SetTargetType(N_LinkTarget_TargetType_Touchlink, setTargetTypeDone);
}

#ifdef _BINDING_
/**************************************************************************//**
\brief Is invoked to indicate that a remote device has bound itself to the local
device via a ZDP binding request

\param[in] bindInd - indication parameters
******************************************************************************/
void ZDO_BindIndication(ZDO_BindInd_t *bindInd)
{
  (void)bindInd;
}

/**************************************************************************//**
\brief Is invoked to indicate that a remote device has unbound itself from the
local device via a ZDP unbinding request

\param[in] bindInd - indication parameters
******************************************************************************/
void ZDO_UnbindIndication(ZDO_UnbindInd_t *unbindInd)
{
  (void)unbindInd;
}
#endif /* _BINDING_ */

#endif // APP_ZLL_DEVICE_TYPE == APP_DEVICE_TYPE_BRIDGE

// eof bridge.c
