/**************************************************************************//**
  \file light.c

  \brief
    Light device implementation.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    26/12/14 Prashanth.Udumula - modified
******************************************************************************/

#if APP_ZLL_DEVICE_TYPE >= APP_DEVICE_TYPE_ON_OFF_LIGHT

/******************************************************************************
                    Includes section
******************************************************************************/
#include <mac.h>
#include <zdo.h>
#include <aps.h>
#include <buttons.h>
#ifdef BOARD_MEGARF
#include <lcdExt.h>
#include <buttonsExt.h>
#endif
#if BSP_SUPPORT == BOARD_SAMR21_ZLLEK
#include <lcdExt.h>
#include <joyStick.h>
#endif
#if defined(BOARD_MEGARF) || defined(BOARD_SAMR21)
#include <ledsExt.h>
#endif
#include <debug.h>
#include <stdlib.h>
#include <zllDemo.h>
#include <resetReason.h>
#include <pdsDataServer.h>
#include <otauService.h>
#include <bspUid.h>

#include <zcl.h>
#include <commandManager.h>
#include <lightTesting.h>
#include <lightClusters.h>
#include <lightIdentifyCluster.h>
#include <lightBasicCluster.h>
#include <lightLevelControlCluster.h>
#include <lightColorControlCluster.h>
#include <lightOnOffCluster.h>
#include <lightScenesCluster.h>
#include <lightGroupsCluster.h>
#include <lightCommissioningCluster.h>
#include <console.h>

#include <lightBindings.h>

#include <N_LinkTarget.h>
#include <N_LinkTarget_Init.h>
#include <N_Connection.h>
#include <N_Connection_Internal.h>
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
#include <N_InterPan.h>
#include <N_InterPan_Init.h>
#include <N_ZllEndpoint.h>
#include <N_PacketDistributor.h>
#include <N_Hac.h>
#include <N_Zdp_Init.h>
#include <N_Connection_Private.h>

#include <networkJoining.h>

/******************************************************************************
                    Definitions section
******************************************************************************/
#define APP_GROUP_IDS             0u
#define DEFAULT_IDENTIFY_TIME     3u // seconds
#define APP_LCD_INIT_DELAY        2000u
#define VISUALIZATION_PERIOD                (100u)
#define INTERPAN_PERIOD           10000u
#define DEFAULT_VISUALIZATION_PERIODS       (1000u / VISUALIZATION_PERIOD)
#define JOIN_NETWORK_VISUALIZATION_PERIODS  (2000u / VISUALIZATION_PERIOD)
#define DEFAULT_IDENTIFY_TIME               3u

#define TOUCHLINK_RSSI_CORRECTION         10u
#define TOUCHLINK_RSSI_THRESHOLD          -60

// When BOARD_RCB_KEY_REMOTE is declared then API for key remote buttons is used,
// otherwise API for standalone button on RCB is used.
#if BSP_SUPPORT == BOARD_SAMR21_ZLLEK
#define BUTTON_PWR                  BSP_KEY0
#define THRESHOLD_TIMER_INTERVAL    1000UL
#endif

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

typedef enum _LightStatus_t
{
  LIGHT_DEFAULT_STATUS,
  LIGHT_INITING_STATUS,
  LIGHT_JOINING_PRIMARY_HA_STATUS,
  LIGHT_JOINING_SECONDARY_HA_STATUS,
  LIGHT_JOINING_STATUS,
  LIGHT_INTERPANNING_STATUS,
  LIGHT_WORKING_STATUS,
  LIGHT_LEAVING_NETWORK_STATUS,
} LightStatus_t;
/******************************************************************************
                    Prototypes section
******************************************************************************/
static void init(void);

static void furtherInitTimerFired(void);
static void appResetToFactoryNew(void);

static void displayStatus(LightStatus_t status);

#if BSP_SUPPORT == BOARD_RCB_KEY_REMOTE
static void appButtonsInd(BSP_ButtonEvent_t event, BSP_ButtonId_t button, uint8_t data);
#endif // BSP_SUPPORT == BOARD_RCB_KEY_REMOTE
#if BSP_SUPPORT == BOARD_SAMR21_ZLLEK
static void buttonsPressed(uint8_t buttonNumber);
static void buttonReleased(uint8_t buttonNumber);
static void resetToFNTimerFired(void);
#endif

static void enableResetToFNButton(void);
#if BSP_SUPPORT != BOARD_SAMR21_ZLLEK
static void disableResetToFNButton(void);
#endif
static void initMacLayerDone(void);
static bool Light_EventHandler(N_Task_Event_t evt);
static void joinNetworkIndication(uint16_t groupIdFirst, uint16_t groupIdLast);
static void leaveNetwork(void);
static void visualizationTimerFired(void);
static void interPanModeTimerFired(void);

static void setTargetTypeDone(void);

static void startNetworkDone(void);

static void zdpLeaveResp(ZDO_ZdpResp_t *leaveResp);
static void ResetIndication(void);
static void IdentifyStartIndication(uint16_t timeoutInSec);
static void IdentifyStopIndication(void);

#if (USE_IMAGE_SECURITY == 1)
static void configureImageKeyDone(void);
#endif
static void nwkLeaveIndHandler(SYS_EventId_t eventId, SYS_EventData_t data);

/******************************************************************************
                    Local variables
******************************************************************************/
static AppState_t appState = APP_INITING;
static ZLL_Endpoint_t appEndpoint;

static bool resetToFactoryNew = false;

static HAL_AppTimer_t furtherInitTimer =
{
  .mode = TIMER_ONE_SHOT_MODE,
  .interval = APP_LCD_INIT_DELAY,
  .callback = furtherInitTimerFired
};
static HAL_AppTimer_t visualizationTimer =
{
  .mode     = TIMER_REPEAT_MODE,
  .interval = VISUALIZATION_PERIOD,
  .callback = visualizationTimerFired
};
static HAL_AppTimer_t interPanModeTimer =
{
  .mode     = TIMER_ONE_SHOT_MODE,
  .interval = INTERPAN_PERIOD,
  .callback = interPanModeTimerFired
};
/* Leave network parameters */
static ZDO_ZdpReq_t leaveReq =
{
  .ZDO_ZdpResp =  zdpLeaveResp,
  .reqCluster = MGMT_LEAVE_CLID,
  .dstAddrMode = APS_EXT_ADDRESS
};
#if BSP_SUPPORT == BOARD_SAMR21_ZLLEK
static HAL_AppTimer_t resetToFNTimer =
{
  .interval = THRESHOLD_TIMER_INTERVAL,
  .mode = TIMER_ONE_SHOT_MODE,
  .callback = resetToFNTimerFired,
};
#endif

static const N_Task_HandleEvent_t s_taskArray[] =
{
  // Add tasks here.
  Light_EventHandler,
  N_ConnectionRouter_EventHandler,
  N_DeviceInfo_EventHandler,
  N_LinkTarget_EventHandler,
};

static const struct N_LinkTarget_Callback_t targetCallbacks =
{
  NULL,//  ScanIndication,
  IdentifyStartIndication,
  IdentifyStopIndication,
  ResetIndication,
  joinNetworkIndication,
  NULL,//  UpdateNetworkIndication,
  -1
};

static bool s_initDone = FALSE;
static uint16_t visualizationPeriodsCounter;
static SYS_EventReceiver_t nwkLeaveIndListener =  { .func = nwkLeaveIndHandler};

/******************************************************************************
                    Implementation section
******************************************************************************/
/**************************************************************************//**
\brief Light event handler

\param[in] evt - event id
******************************************************************************/
static bool Light_EventHandler(N_Task_Event_t evt)
{
  (void)evt;
  return true;
}

/**************************************************************************//**
\brief Start application initialization
******************************************************************************/
static void init(void)
{
  /* Enable buttons and delay further initialization to wait for a SetToFactoryNew
     event triggered from the keyboard */
  enableResetToFNButton();
  ExtAddr_t uid;
  //Reads the UID set in configuration.h
  CS_ReadParameter(CS_UID_ID,&uid);
  if (uid == 0 || uid > APS_MAX_UNICAST_EXT_ADDRESS)
  {
    BSP_ReadUid(&uid); //Will read the UID from chip
    CS_WriteParameter(CS_UID_ID, &uid); //Writes the read UID to the ram
  }
  HAL_StartAppTimer(&furtherInitTimer);
}

void ZCL_ZLLDeviceInformationRespInd(void)
{}

/**************************************************************************//**
\brief Continue initialization of the application
******************************************************************************/
static void furtherInitTimerFired(void)
{
  ZCL_DeviceEndpoint_t *ep = &appEndpoint.deviceEndpoint;
  /* Restore memory in case of power failure */
  if (PDS_IsAbleToRestore(ZLL_APP_MEMORY_MEM_ID) &&
      PDS_IsAbleToRestore(CS_GROUP_TABLE_MEM_ID))
  {
    PDS_Restore(ZLL_APP_MEMORY_MEM_ID);
    PDS_Restore(CS_GROUP_TABLE_MEM_ID);
  }

#if BSP_SUPPORT != BOARD_SAMR21_ZLLEK
  /* Disable buttons, because they will not be used later */
  disableResetToFNButton();
#endif

  /* Initialize the LCD screen */
  LCD_INIT();

#if (APP_ENABLE_CONSOLE == 1) || (APP_DEVICE_EVENTS_LOGGING == 1)
  uartInit();
#endif
#if APP_ENABLE_CONSOLE == 1
  initConsole();
#endif

  /* Initialize LEDs */
  LEDS_INIT();
  TOUCHLINK_LED_INIT();

  lightAddOTAUClientCluster();
  /* Configure and register an endpoint */
  ep->simpleDescriptor.endpoint = APP_ENDPOINT_LIGHT;
  ep->simpleDescriptor.AppProfileId = APP_PROFILE_ID;
  ep->simpleDescriptor.AppDeviceId = APP_DEVICE_ID;
  ep->simpleDescriptor.AppDeviceVersion = APP_VERSION;
  ep->simpleDescriptor.AppInClustersCount = LIGHT_SERVER_CLUSTERS_COUNT;
  ep->simpleDescriptor.AppInClustersList = lightServerClusterIds;
  ep->simpleDescriptor.AppOutClustersCount = LIGHT_CLIENT_CLUSTERS_COUNT;
  ep->simpleDescriptor.AppOutClustersList = lightClientClusterIds;
  ep->serverCluster = lightServerClusters;
  ep->clientCluster = lightClientClusters;
  // Register the end point with AF layer 
  // to handle the frames with ProfileId different from destination endpoint's profile id
  N_Hac_RegisterEndpoint(&appEndpoint, 0u);

  N_Task_Init((uint8_t)N_UTIL_ARRAY_SIZE(s_taskArray), s_taskArray);
  N_Timer_Init();
  errHInit();
  N_DeviceInfo_Init(TOUCHLINK_RSSI_CORRECTION, TOUCHLINK_RSSI_THRESHOLD, FALSE, FALSE, TOUCHLINK_ZERO_DBM_TX_POWER);
  N_DeviceInfo_SetPrimaryChannelMask(APP_PRIMARY_CHANNELS_MASK);
  N_DeviceInfo_SetSecondaryChannelMask(APP_SECONDARY_CHANNELS_MASK);
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
  N_AddressManager_Init();
  N_ConnectionRouter_Init();
  N_InterPan_Init();
  N_LinkTarget_Init();
  N_Zdp_Init();

  s_initDone = TRUE;

  // Subcribing
  N_LinkTarget_Subscribe(&targetCallbacks);

  initTestingExtension();

  /* Initialize the supported cllusters */
  clustersInit();
  basicClusterInit();
  identifyClusterInit();
  levelControlClusterInit();
  colorControlClusterInit();
  onOffClusterInit();
  scenesClusterInit();
  groupsClusterInit();
  commissioningClusterInit();

#if (USE_IMAGE_SECURITY == 1)
  ZCL_ConfigureOtauImageKey(configureImageKeyDone);
#endif

  displayStatus(LIGHT_DEFAULT_STATUS);

  SYS_SubscribeToEvent(BC_EVENT_LEAVE_COMMAND_RECEIVED, &nwkLeaveIndListener);
  if (N_DeviceInfo_IsFactoryNew())
  {
    initiateStartingNetwork();
  }
  else
  {
    appState = APP_WORKING;
    N_LinkTarget_SetTargetType(N_LinkTarget_TargetType_Touchlink, setTargetTypeDone);
    startOtauClient();
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
\brief Callback about setting target type
******************************************************************************/
static void setTargetTypeDone(void)
{}

/**************************************************************************//**
\brief Indication that the device has been linked

\param[in] groupIdFirst - the first group identifier assigned to
  the device during linking; zero if no groups where assigned;
\param[in] groupIdLast  - the last group identifier assigned to
  the device during linking; zero if no groups where assigned
******************************************************************************/
static void joinNetworkIndication(uint16_t groupIdFirst, uint16_t groupIdLast)
{
  displayStatus(LIGHT_DEFAULT_STATUS);

  if (!visualizationPeriodsCounter)
  {
    visualizationPeriodsCounter = JOIN_NETWORK_VISUALIZATION_PERIODS;
    HAL_StartAppTimer(&visualizationTimer);
    TOUCHLINK_LED_ON();
  }
  else
  {
    visualizationPeriodsCounter = MAX(visualizationPeriodsCounter, JOIN_NETWORK_VISUALIZATION_PERIODS);
  }
  (void)groupIdFirst;
  (void)groupIdLast;
}

/**************************************************************************//**
\brief Checks if initialization has been done
******************************************************************************/
static void visualizationTimerFired(void)
{
  if (visualizationPeriodsCounter)
  {
    visualizationPeriodsCounter--;
    TOUCHLINK_LED_TOGGLE();
  }
  else
  {
    HAL_StopAppTimer(&visualizationTimer);
    TOUCHLINK_LED_OFF();
  }
}

/**************************************************************************//**
\brief InterPan mode timer fired
******************************************************************************/
static void interPanModeTimerFired(void)
{
#if APP_ENABLE_CERTIFICATION_EXTENSION == 0
  N_LinkTarget_SetTargetType(N_LinkTarget_TargetType_Touchlink, setTargetTypeDone);
#endif // APP_ENABLE_CERTIFICATION_EXTENSION == 0
}

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
\brief Network update notification
\param notify - update notification parameters
******************************************************************************/
void ZDO_MgmtNwkUpdateNotf(ZDO_MgmtNwkUpdateNotf_t *notify)
{
#if APP_ENABLE_CERTIFICATION_EXTENSION == 0
  LOG_STRING(nwkUpdateNotfStr, "Network update status - 0x%02x\r\n");

  appSnprintf(nwkUpdateNotfStr, notify->status);
#endif /* APP_ENABLE_CERTIFICATION_EXTENSION == 0 */

  if (ZDO_NETWORK_LEFT_STATUS == notify->status)
  {
    if (resetToFactoryNew)
      appResetToFactoryNew();
  }
}

/**************************************************************************//**
\brief Display the current application state on the Key Remote's LCD screen
******************************************************************************/
static void displayStatus(LightStatus_t status)
{
  LCD_PRINT(0, 2, N_DeviceInfo_IsFactoryNew() ? "FN" : "NFN");

  switch (status)
  {
    default:
      LCD_PRINT(4, 2, "           ");
      break;
  }
}

#if BSP_SUPPORT == BOARD_RCB_KEY_REMOTE
/**************************************************************************//**
\brief Buttons handler

\param[in] event - event
\param[in] button - index
\param[in] data - data (AKA hold time)
******************************************************************************/
static void appButtonsInd(BSP_ButtonEvent_t event, BSP_ButtonId_t button, uint8_t data)
{
  LOG_STRING(buttonIndStr, "btn = %d, ev = %d, data = %d\r\n");

  appSnprintf(buttonIndStr, button, event, data);
  (void)event;
  (void)data;
  if (BUTTON_PWR == button)
  {
    HAL_StopAppTimer(&furtherInitTimer);
    appResetToFactoryNew();
  }
}
#endif // BSP_SUPPORT == BOARD_RCB_KEY_REMOTE

/**************************************************************************//**
\brief Enables reset to factory new button
******************************************************************************/
static void enableResetToFNButton(void)
{
#if BSP_SUPPORT == BOARD_RCB_KEY_REMOTE
  // This is API for buttons for a key remote board
  sysAssert(BC_SUCCESS == BSP_InitButtons(appButtonsInd), BSPOPENBUTTONSASSERT_0);
#elif BSP_SUPPORT == BOARD_SAMR21_ZLLEK
  // This is API for a ZLL-EK
  sysAssert(BC_SUCCESS == BSP_OpenButtons(buttonsPressed, buttonReleased), BSPOPENBUTTONSASSERT_0);
#else
  // This is API for other boards
  sysAssert(BC_SUCCESS == BSP_OpenButtons(NULL, NULL), BSPOPENBUTTONSASSERT_0);
  if (BSP_ReadButtonsState() & 0x01)
    appResetToFactoryNew();
#endif
}

#if BSP_SUPPORT != BOARD_SAMR21_ZLLEK
/**************************************************************************//**
\brief Disables reset to factory new button
******************************************************************************/
static void disableResetToFNButton(void)
{
#if BSP_SUPPORT == BOARD_RCB_KEY_REMOTE
  // This is API for buttons for a key remote board
  sysAssert(BC_SUCCESS == BSP_UninitButtons(), BSPCLOSEBUTTONSASSERT_0);
#else
  // This is API for a standalone button on RCB
  sysAssert(BC_SUCCESS == BSP_CloseButtons(), BSPCLOSEBUTTONSASSERT_0);
#endif
}
#endif

#if BSP_SUPPORT == BOARD_SAMR21_ZLLEK
/**************************************************************************//**
\brief Buttons pressed event handler
\param[in] buttonNumber - number of button which is pressed
******************************************************************************/
static void buttonsPressed(uint8_t buttonNumber)
{
  if (BUTTON_PWR == buttonNumber)
  {
    HAL_StopAppTimer(&resetToFNTimer);
    HAL_StartAppTimer(&resetToFNTimer);
  }
}

/**************************************************************************//**
\brief Buttons released event handler
\param[in] buttonNumber - number of button which is released
******************************************************************************/
static void buttonReleased(uint8_t buttonNumber)
{
  if (BUTTON_PWR == buttonNumber)
  {
    HAL_StopAppTimer(&resetToFNTimer);
  }
}

/**************************************************************************//**
\brief Reset to factory new timer handler
******************************************************************************/
static void resetToFNTimerFired(void)
{
  HAL_StopAppTimer(&furtherInitTimer);
  appResetToFactoryNew();
}
#endif // #if BSP_SUPPORT == BOARD_SAMR21_ZLLEK

/**************************************************************************//**
\brief Performs network discovery, network join and target type setting.
******************************************************************************/
void initiateStartingNetwork(void)
{
  appState = APP_JOINING;
  startNetwork(startNetworkDone);
}

/**************************************************************************//**
\brief Posts application task if it in APP_JOINING state.
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
  displayStatus(LIGHT_DEFAULT_STATUS);

  appState = APP_WORKING;
  N_LinkTarget_SetTargetType(N_LinkTarget_TargetType_Touchlink, setTargetTypeDone);
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

/**************************************************************************//**
\brief Reset to factory new indication handler.
******************************************************************************/
static void ResetIndication(void)
{
  resetToFactoryNew = true;
  leaveNetwork();
}

/**************************************************************************//**
\brief Leave network response handler.
    \param leaveResp Leave response parameters
******************************************************************************/
static void zdpLeaveResp(ZDO_ZdpResp_t *leaveResp)
{
  /* Retry until success */
  if (ZDO_SUCCESS_STATUS != leaveResp->respPayload.status)
    leaveNetwork();
}

/**************************************************************************//**
\brief Starts identifying for the specified duration.

\param[in] timeoutInSec - identifying duration
******************************************************************************/
static void IdentifyStartIndication(uint16_t timeoutInSec)
{
  HAL_StopAppTimer(&interPanModeTimer);
  HAL_StartAppTimer(&interPanModeTimer);

  if (!visualizationPeriodsCounter)
  {
    // Converting to ms
    visualizationPeriodsCounter = (timeoutInSec == 0xFFFF) ? DEFAULT_VISUALIZATION_PERIODS : ((timeoutInSec * 1000)/VISUALIZATION_PERIOD);
    HAL_StartAppTimer(&visualizationTimer);
    TOUCHLINK_LED_ON();
    identifyStart(DEFAULT_IDENTIFY_TIME, IDENTIFY_NON_COLOR_EFFECT, 0u);
  }
  else
  {
    // Converting to ms
    visualizationPeriodsCounter = MAX(visualizationPeriodsCounter, ((timeoutInSec * 1000)/VISUALIZATION_PERIOD));
  }
}

/**************************************************************************//**
\brief Stops identifying.
******************************************************************************/
static void IdentifyStopIndication(void)
{
  visualizationPeriodsCounter = 0;
  HAL_StopAppTimer(&visualizationTimer);
  TOUCHLINK_LED_OFF();
}

/** Leave network routine.
*/
static void leaveNetwork(void)
{
  ZDO_MgmtLeaveReq_t *zdpLeaveReq = &leaveReq.req.reqPayload.mgmtLeaveReq;
  NWK_LeaveControl_t leaveControl;

  COPY_EXT_ADDR(leaveReq.dstAddress.extAddress,  *MAC_GetExtAddr());
  COPY_EXT_ADDR(zdpLeaveReq->deviceAddr, *MAC_GetExtAddr());
  zdpLeaveReq->rejoin         = 0;
  zdpLeaveReq->removeChildren = 0;
  zdpLeaveReq->reserved       = 0;

  /* Configure post-leave actions */
  leaveControl.cleanRouteTable    = 1U;
  leaveControl.cleanNeighborTable = 1U;
  leaveControl.cleanAddresmap     = 1U;
  leaveControl.cleanKeyPairSet    = 0U;
  leaveControl.cleanBindingTable  = 0U;
  leaveControl.cleanGroupTable    = 1U;
  leaveControl.cleanNwkSecKeys    = 0U;
  leaveControl.silent             = 0U;
  CS_WriteParameter(CS_LEAVE_NON_REJOIN_CONTROL_ID, &leaveControl);

  ZDO_ZdpReq(&leaveReq);
}

/**************************************************************************//**
\brief Leave indication listener routine.

\param[in] eventId - id of raised event;
\param[in] data    - event's data.
******************************************************************************/
static void nwkLeaveIndHandler(SYS_EventId_t eventId, SYS_EventData_t data)
{
  resetToFactoryNew = true;

  (void)eventId;
  (void)data;
}

#endif // APP_ZLL_DEVICE_TYPE >= APP_DEVICE_TYPE_ON_OFF_LIGHT

// eof light.c
