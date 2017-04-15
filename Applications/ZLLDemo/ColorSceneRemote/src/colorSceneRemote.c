/**************************************************************************//**
  \file colorSceneRemote.c

  \brief
    Color Scene Remote device implementation.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    26/12/14 Prashanth.Udumula - modified
******************************************************************************/

#if APP_ZLL_DEVICE_TYPE == APP_DEVICE_TYPE_COLOR_SCENE_REMOTE

/******************************************************************************
                    Includes section
******************************************************************************/
#include <sysUtils.h>
#include <mac.h>
#include <zdo.h>
#include <aps.h>
#include <buttons.h>
#ifdef BOARD_MEGARF
#include <buttonsExt.h>
#include <lcdExt.h>
#endif
#if BSP_SUPPORT == BOARD_SAMR21_ZLLEK
#include <lcdExt.h>
#include <joyStick.h>
#endif
#if defined(BOARD_MEGARF) || defined(BOARD_SAMR21)
#include <ledsExt.h>
#endif
#include <leds.h>
#include <debug.h>
#include <stdlib.h>
#include <resetReason.h>
#include <pdsDataServer.h>
#include <zllDemo.h>
#include <networkJoining.h>
#include <otauService.h>
#include <sysIdleHandler.h>
#include <sleep.h>
#include <bspUid.h>
#include <halSleep.h>

#include <zclLinkInfoCluster.h>

#include <zcl.h>
#include <commandManager.h>
#include <buttonHandlers.h>
#include <colorSceneRemoteTesting.h>
#include <colorSceneRemoteFsm.h>
#include <colorSceneRemoteClusters.h>
#include <colorSceneRemoteBasicCluster.h>
#include <colorSceneRemoteOnOffCluster.h>
#include <colorSceneRemoteGroupsCluster.h>
#include <colorSceneRemoteIdentifyCluster.h>
#include <colorSceneRemoteScenesCluster.h>
#include <colorSceneRemoteLevelControlCluster.h>
#include <colorSceneRemoteColorControlCluster.h>
#include <colorSceneRemoteLinkInfoCluster.h>

#include <colorSceneRemoteConsole.h>
#include <uartManager.h>
#if APP_ENABLE_CONSOLE == 1
  #include <console.h>
#endif // APP_ENABLE_CONSOLE == 1

#include <colorSceneRemoteBindings.h>

#include <N_LinkInitiator.h>
#include <N_LinkInitiator_Init.h>
#include <N_LinkTarget.h>
#include <N_LinkTarget_Init.h>
#include <N_Connection.h>
#include <N_ConnectionEndDevice_Init.h>
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
#include <N_Zdp.h>
#include <N_ZllEndpoint.h>
#include <N_PacketDistributor.h>
#include <N_Hac.h>
#include <N_EndDeviceRobustness_Init.h>
#include <N_ReconnectHandler_Init.h>
#include <N_EndDeviceRobustness_Bindings.h>
#include <N_EndDeviceRobustness.h>
#include <N_Connection_Internal.h>
/******************************************************************************
                    Definitions section
******************************************************************************/
#define APP_GROUP_IDS               1u
#define DEFAULT_SCREEN_TIMER_PERIOD 20000u
#define ACTIVITY_TIMER_PERIOD       5000u

#define TOUCHLINK_RSSI_CORRECTION         10u
#define TOUCHLINK_RSSI_THRESHOLD          -60

#if BSP_SUPPORT == BOARD_SAMR21_ZLLEK
#define BUTTON_RESET_TO_FN  BSP_KEY0
#endif

/******************************************************************************
                    Types section
******************************************************************************/
typedef enum _AppState_t
{
  APP_INITING,
  APP_WORKING,
  APP_JOINING,
} AppState_t;

/******************************************************************************
                    Prototypes section
******************************************************************************/
static void init(void);
#if BSP_SUPPORT == BOARD_RCB_KEY_REMOTE

static void appButtonsInd(BSP_ButtonEvent_t event, BSP_ButtonId_t button, uint8_t data);
#elif BSP_SUPPORT == BOARD_SAMR21_ZLLEK
static void buttonReleased(uint8_t button);
static void appJoyStickInd(BSP_JoystickState_t state);
#endif
static void initMacLayerDone(void);
static void activityTimerFired(void);
static void startNetworkDone(void);
static void sleepEventHandler(SYS_EventId_t eventId, SYS_EventData_t data);
#if defined (_SLEEP_WHEN_IDLE_) && (APP_ENABLE_CONSOLE == 1)
static void sleepModeHandler(SYS_EventId_t eventId, SYS_EventData_t data);
#endif
static void isBusyOrPollCheck(SYS_EventId_t eventId, SYS_EventData_t data);
static void ZDO_WakeUpConf(ZDO_WakeUpConf_t *conf);
void appResetToFactoryNew(void);

/******************************************************************************
                    Local variables
******************************************************************************/
static AppState_t           appState = APP_INITING;
static ZLL_Endpoint_t       appEndpoint;
//static bool                 resetTargetToFactoryNew;
bool                        bindButtonPressed;

//static bool resetToFactoryNew = false;
#if BSP_SUPPORT == BOARD_RCB_KEY_REMOTE
static uint8_t altFunc = 0;
#endif // BSP_SUPPORT == BOARD_RCB_KEY_REMOTE
AppColorSceneRemoteAppData_t appData;

extern bool isAuthenticationRequired;

static const N_Task_HandleEvent_t s_taskArray[] =
{
  // Add tasks here.
  ColorSceneRemote_EventHandler,
  N_ConnectionEndDevice_EventHandler,
  N_LinkInitiator_EventHandler,
  N_DeviceInfo_EventHandler,
  N_LinkTarget_EventHandler,
  N_ReconnectHandler_EventHandler,

 // System_EventHandler,        // Must be the last in the list!
};

static HAL_AppTimer_t activityTimer =
{
  .mode     = TIMER_ONE_SHOT_MODE,
  .interval = ACTIVITY_TIMER_PERIOD,
  .callback = activityTimerFired
};

static ZDO_WakeUpReq_t zdoWakeUpReq;
static SYS_EventReceiver_t sleepEventListener = {.func = sleepEventHandler};
#if defined (_SLEEP_WHEN_IDLE_) && (APP_ENABLE_CONSOLE == 1)
static SYS_EventReceiver_t sleepModeListener = {.func = sleepModeHandler};
#endif
static SYS_EventReceiver_t zdoBusyPollCheck = { .func = isBusyOrPollCheck};
#if (USE_IMAGE_SECURITY == 1)
static void configureImageKeyDone(void);
#endif

/******************************************************************************
                    Implementations section
******************************************************************************/

/**************************************************************************//**
\brief Initialize the application
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

  /* Restore memory in case of power failure */
  if (PDS_IsAbleToRestore(ZLL_APP_MEMORY_MEM_ID))
    PDS_Restore(ZLL_APP_MEMORY_MEM_ID);

  ZCL_DeviceEndpoint_t *ep = &appEndpoint.deviceEndpoint;

  /* Initialize the LCD screen */
  LCD_INIT();

#if (APP_ENABLE_CONSOLE == 1) || (APP_DEVICE_EVENTS_LOGGING == 1)
  uartInit();
#endif
#if APP_ENABLE_CONSOLE == 1
  initConsole();
#endif

  /* Initialize leds */
  TOUCHLINK_LED_INIT();

  /* Enable buttons */
#if BSP_SUPPORT == BOARD_RCB_KEY_REMOTE
  BSP_InitButtons(appButtonsInd);

  BSP_SetButtonThreshold(BUTTON_PWR, 10);
  BSP_SetButtonThreshold(BUTTON_SEL, 30);
#elif BSP_SUPPORT == BOARD_SAMR21_ZLLEK
  BSP_OpenButtons(NULL, buttonReleased);
  BSP_OpenJoystick(appJoyStickInd);
#else
  BSP_OpenButtons(NULL, NULL);
  if (BSP_ReadButtonsState() & 0x01)
    appResetToFactoryNew();
  else
    BSP_CloseButtons();
#endif // BSP_SUPPORT == BOARD_RCB_KEY_REMOTE

  colorSceneRemoteAddOTAUClientCluster();
  /* Configure and register an endpoint */
  ep->simpleDescriptor.endpoint = APP_ENDPOINT_COLOR_SCENE_REMOTE;
  ep->simpleDescriptor.AppProfileId = APP_PROFILE_ID;
  ep->simpleDescriptor.AppDeviceId = APP_DEVICE_ID;
  ep->simpleDescriptor.AppDeviceVersion = APP_VERSION;
  ep->simpleDescriptor.AppInClustersCount = COLOR_SCENE_REMOTE_SERVER_CLUSTERS_COUNT;
  ep->simpleDescriptor.AppInClustersList = colorSceneRemoteServerClusterIds;
  ep->simpleDescriptor.AppOutClustersCount = COLOR_SCENE_REMOTE_CLIENT_CLUSTERS_COUNT;
  ep->simpleDescriptor.AppOutClustersList = colorSceneRemoteClientClusterIds;
  ep->serverCluster = colorSceneRemoteServerClusters;
  ep->clientCluster = colorSceneRemoteClientClusters;
  // Register the end point with AF layer 
  // to handle the frames with ProfileId different from destination endpoint's profile id
  N_Hac_RegisterEndpoint(&appEndpoint, 0u);

  N_Task_Init((uint8_t)N_UTIL_ARRAY_SIZE(s_taskArray), s_taskArray);
  N_Timer_Init();
  errHInit();
  N_DeviceInfo_Init(TOUCHLINK_RSSI_CORRECTION, TOUCHLINK_RSSI_THRESHOLD, TRUE, TRUE, TOUCHLINK_ZERO_DBM_TX_POWER);
  N_DeviceInfo_SetPrimaryChannelMask(APP_PRIMARY_CHANNELS_MASK);
  N_DeviceInfo_SetSecondaryChannelMask(APP_SECONDARY_CHANNELS_MASK);
  N_Radio_Init();
  N_ConnectionEndDevice_Init();
  N_InterPan_Init();
  N_LinkTarget_Init();
  ColorSceneRemote_FsmInit();
  N_Cmi_Init();
  N_Cmi_InitMacLayer(initMacLayerDone);
}

/**************************************************************************//**
\brief Continue application initialization after MAC layer configuration
******************************************************************************/
static void initMacLayerDone(void)
{
  DstAddressing_t addressing = {
    .mode = APS_GROUP_ADDRESS,
    .ep = 0,
    .addr = appData.groupId
  };

  N_AddressManager_Init();
  N_LinkInitiator_Init();
  N_EndDeviceRobustness_Init();
  N_ReconnectHandler_Init();
  initTestingExtension();

  /* Initialize the supported clusters */
  clustersInit();
  basicClusterInit();
  identifyClusterInit();
  colorControlClusterInit();
  addressing.addr = appData.groupId;
  clustersSetDstAddressing(&addressing);

#if (USE_IMAGE_SECURITY == 1)
  ZCL_ConfigureOtauImageKey(configureImageKeyDone);
#endif

#if defined (_SLEEP_WHEN_IDLE_)
  SYS_EnableSleepWhenIdle();
#if (APP_ENABLE_CONSOLE == 1)
  SYS_SubscribeToEvent(HAL_EVENT_FALLING_ASLEEP, &sleepModeListener);
  SYS_SubscribeToEvent(HAL_EVENT_CONTINUING_SLEEP, &sleepModeListener);
#endif
#endif
  SYS_SubscribeToEvent(HAL_EVENT_WAKING_UP, &sleepEventListener);
  SYS_SubscribeToEvent(BC_EVENT_BUSY_REQUEST, &zdoBusyPollCheck);
  SYS_SubscribeToEvent(BC_EVENT_POLL_REQUEST, &zdoBusyPollCheck);

#if (APP_SCAN_ON_STARTUP == 1)
  if (N_DeviceInfo_IsFactoryNew())
  {
    initiateStartingNetwork();
  }
  else
#endif // (APP_SCAN_ON_STARTUP == 1)
  {
    appState = APP_WORKING;
#if !defined _SLEEP_WHEN_IDLE_
    restartActivity();
#else
    appData.busy = false;
#endif
    // try to reconnect if NFN but not connected
    if (!N_DeviceInfo_IsFactoryNew() && !N_Connection_IsConnected())
    {
      N_Connection_ReconnectUrgent();
    }
  }
}

#if (USE_IMAGE_SECURITY == 1)
/**************************************************************************//**
\brief Callback about confguring image key on EEPROM
******************************************************************************/
static void configureImageKeyDone(void)
{}
#endif

/**************************************************************************//**
\brief Returns true if initialization has been done
******************************************************************************/
bool N_Init_IsInitDone(void)
{
  return (APP_WORKING == appState);
}

/**************************************************************************//**
\brief Restarts end device activity (parent polling)
******************************************************************************/
void restartActivity(void)
{
#if !defined _SLEEP_WHEN_IDLE_ || (APP_ENABLE_CERTIFICATION_EXTENSION == 1)
  if (ZDO_IN_NETWORK_STATUS == ZDO_GetNwkStatus())
  {
    if (APP_WORKING == appState)
    {
      appData.busy = true;
      ZDO_StartSyncReq();
    }
    HAL_StopAppTimer(&activityTimer);
    HAL_StartAppTimer(&activityTimer);
  }
#endif /* _SLEEP_WHEN_IDLE_ */
}

/**************************************************************************//**
\brief Activity timer has fired
******************************************************************************/
static void activityTimerFired(void)
{
  if (transmissionIsInProgress()
#if (APP_USE_OTAU == 1)
    || ZCL_IsOtauBusy()
#endif
      )
  {
    HAL_StartAppTimer(&activityTimer);
    return;
  }
  if (ZDO_IN_NETWORK_STATUS == ZDO_GetNwkStatus())
  {
    appData.busy = false;
    ZDO_StopSyncReq();
  }
}

/**************************************************************************//**
\brief Sends permit join request

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
\brief Network update notification

\param[in] notify - update notification parameters
******************************************************************************/
void ZDO_MgmtNwkUpdateNotf(ZDO_MgmtNwkUpdateNotf_t *notify)
{
#if APP_ENABLE_CERTIFICATION_EXTENSION == 0
  LOG_STRING(nwkUpdateStatusStr, "Network update status - 0x%02x\r\n");

  appSnprintf(nwkUpdateStatusStr, notify->status);
//  zclZllIB.device.nwkUpdateId = NWK_GetUpdateId();

  if (ZDO_NETWORK_LOST_STATUS == notify->status || ZDO_NETWORK_LEFT_STATUS == notify->status)
  {
//    if (resetToFactoryNew)
//      appResetToFactoryNew();
//    else;
//      //reborn();
  }
#else
  (void)notify;
#endif /* APP_ENABLE_CERTIFICATION_EXTENSION == 0 */
}

/**************************************************************************//**
\brief ResetToFactoryNew execution routine
******************************************************************************/
void appResetToFactoryNew(void)
{
  PDS_DeleteAll(false);
  N_DeviceInfo_SetFactoryNew(true);
  HAL_WarmReset();
}

#if BSP_SUPPORT == BOARD_RCB_KEY_REMOTE
/**************************************************************************//**
\brief Process color scene remote's power button's press
******************************************************************************/
static void processPwrButtonPressedEvent(void)
{
  if (APP_WORKING != appState)
    return;

  switch (altFunc & 0x03)
  {
    case 0:
      performTouchlink();
      break;

    case 1:
      initiateStartingNetwork();
      break;

    case 2:
      appResetToFactoryNew();
      break;

    case 3:
      performResetDeviceToFn();
      break;

    default:
      break;
  }
}

/**************************************************************************//**
\brief Process color scene remote's power button's press
******************************************************************************/
static void processPwrButtonReleasedEvent(void)
{
  if (APP_WORKING != appState)
    return;

  stopTouchlink();
}

/**************************************************************************//**
\brief Buttons handler

\param[in] event - event
\param[in] button - index
\param[in] data - data (AKA hold time)
******************************************************************************/
void appButtonsInd(BSP_ButtonEvent_t event, BSP_ButtonId_t button, uint8_t data)
{
  LOG_STRING(buttonIndStr, "btn = %d, ev = %d, data = %d\r\n");

  appSnprintf(buttonIndStr, button, event, data);

  if (BUTTON_RIGHT_M == button)
  {
    if (BUTTON_PRESSED_EVENT == event)
      altFunc |= 0x02;
    else if (BUTTON_RELEASED_EVENT == event)
      altFunc &= ~0x02;
  }

  if (BUTTON_RELEASED_EVENT == event)
  {
    if ((2 == altFunc)  && (BUTTON_LEFT_M == button))
    {
      //isAuthenticationRequired = true;
    }
  }

  if (BUTTON_PWR == button)
  {
    if (BUTTON_PRESSED_EVENT == event)
    {
      processPwrButtonPressedEvent();
    }
    else if (BUTTON_RELEASED_EVENT == event)
    {
      processPwrButtonReleasedEvent();
    }
  }

  if (BUTTON_RIGHT_P == button)
  {
    if (BUTTON_PRESSED_EVENT == event)
      altFunc |= 0x01;
    else if (BUTTON_RELEASED_EVENT == event)
      altFunc &= ~0x01;
  }

  if (BUTTON_RIGHT_M == button)
  {
    if (BUTTON_PRESSED_EVENT == event)
      altFunc |= 0x02;
    else if (BUTTON_RELEASED_EVENT == event)
      altFunc &= ~0x02;
  }

  if (BUTTON_RELEASED_EVENT == event)
  {
    if ((appState == APP_WORKING) && isAnyDeviceBound())
    {
      /* Try to reestablish network communication */
      restartActivity();
      buttonHandler(button, data, altFunc);
    }
  }
}

#elif BSP_SUPPORT == BOARD_SAMR21_ZLLEK
/**************************************************************************//**
\brief Button handler

\param[in] state - joystick state
******************************************************************************/
static void buttonReleased(uint8_t button)
{
  switch(button)
  {
    case BUTTON_RESET_TO_FN:
      appResetToFactoryNew();
      break;
    default:
      break;
  }
}
/**************************************************************************//**
\brief JoyStick handler

\param[in] state - joystick state
******************************************************************************/
static void appJoyStickInd(BSP_JoystickState_t state)
{
  CommandDescriptor_t *cmd;
  switch (state)
  {
    case JOYSTICK_PUSH:
    {
      performTouchlink();
    }
    break; 
    case JOYSTICK_LEFT:
    case JOYSTICK_RIGHT:
    {     
      if (!(cmd = clustersAllocCommand()))
        return;
      cmd->isAttributeOperation = false;
      cmd->clusterId = LEVEL_CONTROL_CLUSTER_ID;
      cmd->commandId = ZCL_LEVEL_CONTROL_CLUSTER_STEP_COMMAND_ID;
      if (JOYSTICK_LEFT == state)
      {
        cmd->payload.stepLevel.stepMode = ZLL_LEVEL_CONTROL_UP_DIRECTION;
      }
      else
      {
        cmd->payload.stepLevel.stepMode = ZLL_LEVEL_CONTROL_DOWN_DIRECTION;
      }
      cmd->payload.stepLevel.stepSize = 20;
      cmd->payload.stepLevel.transitionTime = 5;
      cmd->size = sizeof(cmd->payload.stepLevel);
      clustersSendCommand(cmd);
    }
    break;
    case JOYSTICK_UP:
    case JOYSTICK_DOWN:
    {
      if (!(cmd = clustersAllocCommand()))
        return;
      cmd->isAttributeOperation = false;
      cmd->clusterId = ONOFF_CLUSTER_ID;
      if (JOYSTICK_UP == state)
      {
        cmd->commandId = ZCL_ONOFF_CLUSTER_ON_COMMAND_ID;
      }
      else
      {
        cmd->commandId = ZCL_ONOFF_CLUSTER_OFF_COMMAND_ID;
      }
      clustersSendCommand(cmd);
    }
    break;
    default:
      break;
  }
}
#endif // BSP_SUPPORT == BOARD_RCB_KEY_REMOTE

/**************************************************************************//**
  \brief Processes HAL_EVENT_WAKING_UP event

  \param[in] eventId - id of raised event;
  \param[in] data    - event's data.
******************************************************************************/
static void sleepEventHandler(SYS_EventId_t eventId, SYS_EventData_t data)
{
  HAL_SleepControl_t *sleepControl = (HAL_SleepControl_t *)data;

  if (HAL_WAKEUP_SOURCE_EXT_IRQ == sleepControl->wakeupSource)
  {
    zdoWakeUpReq.ZDO_WakeUpConf = ZDO_WakeUpConf;
    ZDO_WakeUpReq(&zdoWakeUpReq);
  }
  (void)eventId; /* Do nothing, to avoid compiler warning */
}

#if defined (_SLEEP_WHEN_IDLE_) && (APP_ENABLE_CONSOLE == 1)
/**************************************************************************//**
  \brief Processes HAL_EVENT_FALL_ASLEEP & HAL_EVENT_CONITUING_SLEEP events

  \param[in] eventId - id of raised event;
  \param[in] data    - event's data.
******************************************************************************/
static void sleepModeHandler(SYS_EventId_t eventId, SYS_EventData_t data)
{
  // when console is enabled, we go to idle mode to handle UART Rx interrupt
  // because UART Rx interrupt will not wake up the MCU from power save or power down modes
  *(HAL_SleepMode_t *)data = HAL_SLEEP_MODE_IDLE;
  (void)eventId;
}
#endif

/**************************************************************************//**
  \brief Processes BC_EVENT_BUSY_REQUEST and BC_EVENT_POLL_REQUEST events

  \param[in] eventId - id of raised event;
  \param[in] data    - event's data.
******************************************************************************/
static void isBusyOrPollCheck(SYS_EventId_t eventId, SYS_EventData_t data)
{
#if defined (_SLEEP_WHEN_IDLE_)
  bool *check = (bool *)data;

  if (BC_EVENT_POLL_REQUEST == eventId)
    *check |= appData.busy;
#else
  (void)eventId, (void)data;
#endif
}

/**************************************************************************//**
  \brief Wake up confirmation handler.

  \param[in] conf - confirmation parameters.
*****************************************************************************/
static void ZDO_WakeUpConf(ZDO_WakeUpConf_t *conf)
{
  (void)conf;
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
  startOtauClient();
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
\brief Wake up indication called when the device wakes up
******************************************************************************/
void ZDO_WakeUpInd(void)
{
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

#endif // APP_ZLL_DEVICE_TYPE == APP_DEVICE_TYPE_COLOR_SCENE_REMOTE

// eof colorSceneRemote.c
