/**************************************************************************//**
  \file colorSceneRemote.c

  \brief
    Color Scene Remote state machine implementation.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    16.12.12 D. Kolmakov - Created.
******************************************************************************/
#if APP_ZLL_DEVICE_TYPE == APP_DEVICE_TYPE_COLOR_SCENE_REMOTE

/******************************************************************************
                    Includes section
******************************************************************************/
#include <sysUtils.h>
#if defined(BOARD_MEGARF) || defined(BOARD_SAMR21)
#include <lcdExt.h>
#endif
#include <zllDemo.h>
#include <debug.h>
#include <commandManager.h>
#include <colorSceneRemoteGroupsCluster.h>
#include <colorSceneRemoteLinkInfoCluster.h>
#include <colorSceneRemoteFsm.h>
#include <otauService.h>
#include <pdsDataserver.h>

#include <colorSceneRemoteBindings.h>

#include <N_Task_Bindings.h>
#include <N_Task.h>
#include <N_Timer_Bindings.h>
#include <N_Timer.h>
#include <N_AddressManager_Bindings.h>
#include "N_Memory.h"
#include "N_Fsm.h"
#include "N_AddressManager.h"
#include "N_Connection.h"
#include <N_DeviceInfo_Bindings.h>
#include "N_DeviceInfo.h"
#include "N_LinkTarget.h"
#include "N_LinkInitiator.h"
#include "N_Security.h"
#include "N_EndDeviceRobustness.h"

/******************************************************************************
                    Definitions section
******************************************************************************/
//#define COMPID "colorSceneRemoteFsm"

/** The time the status message is shown on the LCD before it reverts to its default message. */
#define TIMEOUT_SHOW_MESSAGE_MS         3000u
#define START_TOUCHLINK_DELAY_MS        500u
#define IDENTIFY_TIMEOUT_MS             2000u
#define JOIN_TIMEOUT_MS                 10000u
#define SELECTION_TIMEOUT_MS            5000u
#define POLLING_TIMEOUT_MS              7000u

#define EVENT_TIMER                     0u
#define EVENT_SCANDONE                  1u
#define EVENT_DEVICEJOINDONE            2u
#define EVENT_IDENTIFYREQUESTDONE       3u
#define EVENT_JOIN_NETWORK_INDICATION   4u
#define EVENT_UPDATE_NETWORK_INDICATION 5u
#define EVENT_SET_TARGET_TYPE_DONE      7u
#define EVENT_DEVICEINFOREQUESTDONE     8u

#define EVENT_IDENITFY_DONE             14u

#define EVENT_RESET_DEVICE_TO_FN        15u
#define EVENT_JOIN_NETWORK_DONE         16u

/** The maximum number of devices a touchlink scan should return. */
#define TOUCHLINK_SCAN_MAX_DEVICES  5u

#define VISUALIZATION_PERIOD 3000u

/******************************************************************************
                    Types section
******************************************************************************/
enum colorSceneRemote_states  // states
{
  sIdle,
  sRequestingDeviceInfo,
  sRequestingDeviceInfoWait,
  sWaitingToBeJoined,
  sSettingIdleTargetType,
  sWaiting,
  sScanAfterSetTargetTypeDone,
  sSetTargetTypeNoneAfterSetTargetTypeDone,
  sScanning,
  sIdentifyAfterSetTargetTypeDone,
  sIdentifyStarting,
  sIdentifyWait,
  sIdentifying,
  sIdentifyStopping,
  sJoining,
  sStoppingScan,
  sWaitForAddGroupResponse,
  sTargetSelected,
  sPolling,
};

enum colorSceneRemote_events  // events
{
  eTimer,
  eButtonPressed,
  eButtonReleased,
  eJoinNetworkIndication,
  eUpdateNetworkIndication,
  eSetTargetTypeDone,
  eScanIndication,
  eScanDone,
  eIdentifyRequestDone,
  eJoinDeviceDone,
  eScanStopped,
  eDeviceInfoRequestDone,
  eAddGroupResponse,
  eTargetSelected,
};

enum colorSceneRemote_conditions // conditions
{
  cIsFactoryNewOrInDistributedTrustCenterMode,
  cDevicesFound,
  cJoinSuccessful,
  cResetTargetToFn,
  cIsFactoryNewAndOtherNotFactoryNew,
  cJoinSuccessfulAndValidEndpoint,
  cAddGroupSuccessful,
};

enum colorSceneRemote_actions // actions
{
  aShowDefault,
  aSetTargetTypeNone_ShowLinkOk,
  aSetTargetTypeNone_ShowNotJoined,
  aStartWaitTimer,
  aStopTimer,
  aSetTargetTypeTouchlink,
  aTouchlinkScanOnPrimaryChannels,
  aTouchlinkScanOnPrimaryAndSecondaryChannels,
  aShowDefault_StopScan,
  aSetTargetTypeNone,
  aShowNoDevicesFound_SetTargetTypeNone,
  aIdentifyStart,
  aStartIdentifyTimer,
  aIdentifyStop_StopIdentifyTimer,
  aResetToFactoryNew,
  aJoinDevice,
  aShowJoinDeviceError,
  aIdentifyStop,
  aShowNoDevicesFound,
  aShowLinkOk,
  aSendDeviceInfoRequest,
  aStopScan_StartJoinTimer,
  aAddBoundDevAndShowLinkOk,
  aShowAddGroupFailed,
  aShowLinkOk_SendAddGroup,
  aShowAddGroupOk_AddBoundDev_StartPollTimer,
  aStartTargetSelectedWaitTimer,
  aSetGroupAddressing_ShowDefault,
  aSetAppNotBusy,
};
/******************************************************************************
                    Prototypes section
******************************************************************************/
static void IdleEntry(void);
static void ScanningEntry(void);
static void IdentifyingEntry(void);
static void StoppingEntry(void);
static void JoiningEntry(void);
static void WaitingToBeJoined(void);

static void PerformAction(N_FSM_Action_t action, int32_t arg1, int32_t arg2);
static bool CheckCondition(N_FSM_Condition_t condition, int32_t arg1, int32_t arg2);

inline static bool JoinSuccessful(void);
inline static bool DevicesFound(void);
inline static bool IsFactoryNewOrInDistributedTrustCenterMode(void);
inline static bool IsFactoryNewAndOtherNotFactoryNew(void);
#if APP_ENABLE_CERTIFICATION_EXTENSION == 0
inline static bool AddGroupSuccessful(void);
#endif // APP_ENABLE_CERTIFICATION_EXTENSION == 0
inline static bool JoinSuccessfulAndValidEndpoint(void);
inline static bool ResetTargetToFn(void);

static inline void ShowDefault(void);
static inline void ShowLinkOk(void);
static inline void ShowNotJoined(void);
static inline void ShowNoDevicesFound(void);
static inline void ShowJoinDeviceError(void);
static inline void ShowRouterOrEndDeviceOnLcd(void);
static inline void ShowFactoryNewStatusOnLcd(void);
static inline void StartWaitTimer(void);
static inline void StartIdentifyTimer(void);
static inline void StartJoinTimer(void);
static inline void StopTimer(void);
static inline void SetTargetTypeNone(void);
static inline void SetTargetTypeTouchlink(void);
static inline void TouchlinkScanOnPrimaryChannels(void);
static inline void TouchlinkScanOnPrimaryAndSecondaryChannels(void);
static inline void StopScan(void);
static inline void IdentifyStart(void);
static inline void IdentifyStop(void);
static inline void ResetToFactoryNew(void);
static inline void JoinDevice(void);
static inline void SendDeviceInfoRequest(void);
static inline void AddBoundDevice(void);
#if APP_ENABLE_CERTIFICATION_EXTENSION == 0
static inline void ShowAddGroupFailed(void);
static inline void ShowAddGroupOk(void);
static inline void SendAddGroup(void);
static inline void StartPollingTimer(void);
#endif // APP_ENABLE_CERTIFICATION_EXTENSION == 0
static inline void StartTargetSelectedWaitTimer(void);
static inline void SetGroupAddressing(void);
static inline void SetAppNotBusy(void);

static void JoinDeviceDone(N_LinkInitiator_Status_t status, uint16_t targetNetworkAddress);
static void IdentifyRequestDone(N_LinkInitiator_Status_t status);
static void ResetToFactoryNewDone(N_LinkInitiator_Status_t status);
static void ScanDone(N_LinkInitiator_Status_t status, uint8_t numDevicesFound);
static void SetTargetTypeDone(void);
static void DeviceInfoRequestDone(N_LinkInitiator_Status_t status);
#if APP_ENABLE_CERTIFICATION_EXTENSION == 0
static void AddGroupResponse(uint8_t status, uint16_t groupId);
#endif // APP_ENABLE_CERTIFICATION_EXTENSION == 0
static void Disconnected(void);
static void Connected(void);
static void ResetToFactoryDefaults(void);

static BoundDevice_t *boundDeviceAlloc(ExtAddr_t *targetExtAddr);
static void boundDeviceTblInit(void);
static void linkedVisualizationTimerFired(void);

/******************************************************************************
                    External variables
******************************************************************************/
extern AppColorSceneRemoteAppData_t appData;

/******************************************************************************
                    External functions
******************************************************************************/
extern void appResetToFactoryNew(void);

/******************************************************************************
                    Local variables
******************************************************************************/
static N_Task_Id_t s_taskId = N_TASK_ID_NONE;
static N_Timer_t s_timer;
static uint8_t s_status;
static uint8_t s_numDevicesFound;
static N_LinkInitiator_Status_t s_linkStatus;
static uint8_t s_currentState;
static bool resetTargetToFactoryNew;
static HAL_AppTimer_t linkedVisualizationTimer =
{
  .mode     = TIMER_ONE_SHOT_MODE,
  .interval = VISUALIZATION_PERIOD,
  .callback = linkedVisualizationTimerFired
};

static N_InterPan_DeviceInfo_t *s_pEpInfo = NULL;
static N_InterPan_ScanRequest_t s_scanIndicationRequest;
static N_LinkInitiator_Device_t *s_pFoundDevices = NULL;

static uint16_t s_targetNetworkAddress = NWK_NO_SHORT_ADDR;
static int8_t currentBoundDevice = -1;

#if APP_ENABLE_CERTIFICATION_EXTENSION == 0
static uint8_t s_addGroupStatus;
#endif // APP_ENABLE_CERTIFICATION_EXTENSION == 0
static bool parentLost = false;
static uint32_t sleepPeriodConfigured;

// Shared between all FSMs
static const N_FSM_StateEntryExit_t s_entryExit[] =
{
  N_FSM_ENTRYEXIT(sIdle, IdleEntry, NULL),
  N_FSM_ENTRYEXIT(sScanning, ScanningEntry, NULL),
  N_FSM_ENTRYEXIT(sIdentifying, IdentifyingEntry, NULL),
  N_FSM_ENTRYEXIT(sStoppingScan, StoppingEntry, NULL),
  N_FSM_ENTRYEXIT(sJoining, JoiningEntry, NULL),
  N_FSM_ENTRYEXIT(sWaitingToBeJoined, WaitingToBeJoined, NULL),
};

static const N_FSM_Transition_t s_transitionTableZllRemote[] =
{
  //     event                    condF                               actF                        newState
  N_FSM_STATE(sIdle),
  N_FSM(eButtonPressed,          N_FSM_NONE,                         aStartWaitTimer,            sWaiting),
  N_FSM(eTimer,                  N_FSM_NONE,                         aShowDefault,               N_FSM_SAME_STATE),
  N_FSM(eTargetSelected,         N_FSM_NONE,                         aStartTargetSelectedWaitTimer, sTargetSelected),

  N_FSM_STATE(sTargetSelected),
  N_FSM(eTargetSelected,         N_FSM_NONE,                         aStartTargetSelectedWaitTimer, N_FSM_SAME_STATE),
  N_FSM(eTimer,                  N_FSM_NONE,                         aSetGroupAddressing_ShowDefault, sIdle),

  N_FSM_STATE(sWaiting),
  N_FSM(eButtonReleased,         N_FSM_NONE,                         aStopTimer,                 sIdle),
  N_FSM(eTimer,                  N_FSM_NONE,                         aSetTargetTypeTouchlink,    sScanAfterSetTargetTypeDone),

  N_FSM_STATE(sScanAfterSetTargetTypeDone),
  N_FSM(eButtonReleased,         N_FSM_NONE,                         N_FSM_NONE,                 sSetTargetTypeNoneAfterSetTargetTypeDone),
  N_FSM(eSetTargetTypeDone,      cIsFactoryNewOrInDistributedTrustCenterMode, aTouchlinkScanOnPrimaryChannels, sScanning),
  N_FSM(eSetTargetTypeDone,      N_FSM_ELSE,                         aTouchlinkScanOnPrimaryAndSecondaryChannels, sScanning),

  N_FSM_STATE(sScanning),
  N_FSM(eButtonReleased,         N_FSM_NONE,                         aShowDefault_StopScan,      sStoppingScan),
  N_FSM(eScanDone,               cDevicesFound,                      aSendDeviceInfoRequest,     sRequestingDeviceInfo),
  N_FSM(eScanDone,               N_FSM_ELSE,                         aShowNoDevicesFound_SetTargetTypeNone, sSettingIdleTargetType),
  N_FSM(eScanIndication,         cIsFactoryNewAndOtherNotFactoryNew, aStopScan_StartJoinTimer,   sWaitingToBeJoined),

  N_FSM_STATE(sRequestingDeviceInfo),
  N_FSM(eDeviceInfoRequestDone,  N_FSM_NONE,                         aSetTargetTypeNone,         sIdentifyAfterSetTargetTypeDone),
  N_FSM(eButtonReleased,         N_FSM_NONE,                         N_FSM_NONE,                 sRequestingDeviceInfoWait),

  N_FSM_STATE(sIdentifyAfterSetTargetTypeDone),
  N_FSM(eButtonReleased,         N_FSM_NONE,                         N_FSM_NONE,                 sSettingIdleTargetType),
  N_FSM(eSetTargetTypeDone,      N_FSM_NONE,                         aIdentifyStart,             sIdentifyStarting),

  N_FSM_STATE(sIdentifyStarting),
  N_FSM(eButtonReleased,         N_FSM_NONE,                         N_FSM_NONE,                 sIdentifyWait),
  N_FSM(eIdentifyRequestDone,    N_FSM_NONE,                         aStartIdentifyTimer,        sIdentifying),

  N_FSM_STATE(sIdentifying),
  N_FSM(eButtonReleased,         N_FSM_NONE,                         aIdentifyStop_StopIdentifyTimer, sIdentifyStopping),
  N_FSM(eTimer,                  cResetTargetToFn,                   aResetToFactoryNew,         sIdle),
  N_FSM(eTimer,                  N_FSM_ELSE,                         aJoinDevice,                sJoining),

  N_FSM_STATE(sJoining),
#if APP_ENABLE_CERTIFICATION_EXTENSION == 0
  N_FSM(eJoinDeviceDone,         cJoinSuccessfulAndValidEndpoint,    aShowLinkOk_SendAddGroup,   sWaitForAddGroupResponse),
#endif
  N_FSM(eJoinDeviceDone,         cJoinSuccessful,                    aAddBoundDevAndShowLinkOk,  sIdle),
  N_FSM(eJoinDeviceDone,         N_FSM_ELSE,                         aShowJoinDeviceError,       sIdle),

  N_FSM_STATE(sWaitForAddGroupResponse),
  N_FSM(eTimer,                  N_FSM_NONE,                         aShowAddGroupFailed,        sIdle),
  N_FSM(eAddGroupResponse,       cAddGroupSuccessful,                aShowAddGroupOk_AddBoundDev_StartPollTimer, sPolling),
  N_FSM(eAddGroupResponse,       N_FSM_ELSE,                         aShowAddGroupFailed,        sIdle),

  N_FSM_STATE(sWaitingToBeJoined),
#if APP_ENABLE_CERTIFICATION_EXTENSION == 0
  N_FSM(eJoinNetworkIndication,  N_FSM_NONE,                         aSetTargetTypeNone_ShowLinkOk, sPolling),
  N_FSM(eUpdateNetworkIndication, N_FSM_NONE,                        aSetTargetTypeNone_ShowLinkOk, sPolling),
#else
  N_FSM(eJoinNetworkIndication,  N_FSM_NONE,                         aSetTargetTypeNone_ShowLinkOk, sSettingIdleTargetType),
  N_FSM(eUpdateNetworkIndication, N_FSM_NONE,                        aSetTargetTypeNone_ShowLinkOk, sSettingIdleTargetType),
#endif
  N_FSM(eTimer,                  N_FSM_NONE,                         aSetTargetTypeNone_ShowNotJoined,   sSettingIdleTargetType),

  N_FSM_STATE(sSetTargetTypeNoneAfterSetTargetTypeDone),
  N_FSM(eSetTargetTypeDone,      N_FSM_NONE,                         aSetTargetTypeNone,         sSettingIdleTargetType),

  N_FSM_STATE(sSettingIdleTargetType),
  N_FSM(eSetTargetTypeDone,      N_FSM_NONE,                         N_FSM_NONE,                 sIdle),

  N_FSM_STATE(sStoppingScan),
  N_FSM(eScanStopped,            N_FSM_NONE,                         aSetTargetTypeNone,         sSettingIdleTargetType),

  N_FSM_STATE(sIdentifyWait),
  N_FSM(eIdentifyRequestDone,    N_FSM_NONE,                         aIdentifyStop,              sIdentifyStopping),

  N_FSM_STATE(sIdentifyStopping),
  N_FSM(eIdentifyRequestDone,    N_FSM_NONE,                         aShowDefault,               sIdle),

  N_FSM_STATE(sRequestingDeviceInfoWait),
  N_FSM(eDeviceInfoRequestDone,  N_FSM_NONE,                         aSetTargetTypeNone,         sSettingIdleTargetType),

  N_FSM_STATE(sPolling),
  N_FSM(eTimer,                  N_FSM_NONE,                         aSetAppNotBusy,              sIdle),
};

N_FSM_DECLARE(s_fsmZllRemote,
              s_transitionTableZllRemote,
              N_FSM_TABLE_SIZE(s_transitionTableZllRemote),
              s_entryExit,
              N_FSM_TABLE_SIZE(s_entryExit),
              PerformAction,
              CheckCondition);

/******************************************************************************
                    Implementations section
******************************************************************************/

/**************************************************************************//**
\brief Perfom default actions on idle state entering
******************************************************************************/
static void IdleEntry(void)
{
  restartActivity();
  N_Timer_Start16(TIMEOUT_SHOW_MESSAGE_MS, &s_timer);
}

/**************************************************************************//**
\brief Perfom default actions on scanning state entering
******************************************************************************/
static void ScanningEntry(void)
{
  LCD_PRINT(0u, LCD_LINE_STATUS, "Scanning.........");
}

/**************************************************************************//**
\brief Perfom default actions on identifying state entering
******************************************************************************/
static void IdentifyingEntry(void)
{
  LCD_PRINT(0u, LCD_LINE_STATUS, "Identifying...");
}

/**************************************************************************//**
\brief Perfom default actions on stopping state entering
******************************************************************************/
static void StoppingEntry(void)
{
  LCD_PRINT(0u, LCD_LINE_STATUS, "Stopping...");
}

/**************************************************************************//**
\brief Perfom default actions on joining state entering
******************************************************************************/
static void JoiningEntry(void)
{
  LCD_PRINT(0u, LCD_LINE_STATUS, "Joining...         ");
}

/**************************************************************************//**
\brief Perfom default actions on waiting to be joined state entering
******************************************************************************/
static void WaitingToBeJoined(void)
{
  LCD_PRINT(0u, LCD_LINE_STATUS, "WaitingForJoin...");
}

/**************************************************************************//**
\brief Performs specified action

\param[in] action - action identifier
\param[in] arg1 - additional data
\param[in] arg2 - additional data

\return result of condition check
******************************************************************************/
static void PerformAction(N_FSM_Action_t action, int32_t arg1, int32_t arg2)
{
  switch (action)
  {
    case aShowDefault:
      ShowDefault();
      break;

    case aSetTargetTypeNone_ShowLinkOk:
      SetTargetTypeNone();
      ShowLinkOk();
#if APP_ENABLE_CERTIFICATION_EXTENSION == 0
      StartPollingTimer();
#endif
      break;

    case aSetTargetTypeNone_ShowNotJoined:
      SetTargetTypeNone();
      ShowNotJoined();
      break;

    case aStartWaitTimer:
      StartWaitTimer();
      break;

    case aStopTimer:
      StopTimer();
      break;

    case aSetTargetTypeTouchlink:
      SetTargetTypeTouchlink();
      break;

    case aTouchlinkScanOnPrimaryChannels:
      TouchlinkScanOnPrimaryChannels();
      break;

    case aTouchlinkScanOnPrimaryAndSecondaryChannels:
      TouchlinkScanOnPrimaryAndSecondaryChannels();
      break;

    case aShowDefault_StopScan:
      ShowDefault();
      StopScan();
      break;

    case aSetTargetTypeNone:
      SetTargetTypeNone();
      break;

    case aAddBoundDevAndShowLinkOk:
      AddBoundDevice();
      ShowLinkOk();
      break;

    case aShowNoDevicesFound_SetTargetTypeNone:
      ShowNoDevicesFound();
      SetTargetTypeNone();
      break;

    case aIdentifyStart:
      IdentifyStart();
      break;

    case aStartIdentifyTimer:
      StartIdentifyTimer();
      break;

    case aIdentifyStop_StopIdentifyTimer:
      IdentifyStop();
      StopTimer();
      break;

    case aJoinDevice:
      restartActivity();
      JoinDevice();
      break;

    case aResetToFactoryNew:
      ResetToFactoryNew();
      break;

    case aShowJoinDeviceError:
      ShowJoinDeviceError();
      break;

    case aIdentifyStop:
      IdentifyStop();
      break;

    case aShowNoDevicesFound:
      ShowNoDevicesFound();
      break;

    case aShowLinkOk:
      ShowLinkOk();
      break;

    case aSendDeviceInfoRequest:
      SendDeviceInfoRequest();
      break;

    case aStopScan_StartJoinTimer:
      StopScan();
      StartJoinTimer();
      break;

#if APP_ENABLE_CERTIFICATION_EXTENSION == 0
    case aShowAddGroupFailed:
      ShowAddGroupFailed();
      break;

    case aShowLinkOk_SendAddGroup:
      ShowLinkOk();
      SendAddGroup();
      break;

    case aShowAddGroupOk_AddBoundDev_StartPollTimer:
      ShowAddGroupOk();
      AddBoundDevice();
      StartPollingTimer();
      break;
#endif // APP_ENABLE_CERTIFICATION_EXTENSION == 0

    case aStartTargetSelectedWaitTimer:
      StartTargetSelectedWaitTimer();
      break;

    case aSetGroupAddressing_ShowDefault:
      SetGroupAddressing();
      ShowDefault();
      break;

    case aSetAppNotBusy:
      SetAppNotBusy();
      break;

    default:
      break;
  }
  (void)arg1;
  (void)arg2;
}

/**************************************************************************//**
\brief Checks specified condition

\param[in] condition - condition identifier
\param[in] arg1 - additional data
\param[in] arg2 - additional data

\return result of condition check
******************************************************************************/
static bool CheckCondition(N_FSM_Condition_t condition, int32_t arg1, int32_t arg2)
{
  switch (condition)
  {
    case cIsFactoryNewOrInDistributedTrustCenterMode:
      return IsFactoryNewOrInDistributedTrustCenterMode();

    case cJoinSuccessful:
      return JoinSuccessful();

    case cDevicesFound:
      return DevicesFound();

    case cIsFactoryNewAndOtherNotFactoryNew:
      return IsFactoryNewAndOtherNotFactoryNew();

#if APP_ENABLE_CERTIFICATION_EXTENSION == 0
    case cAddGroupSuccessful:
      return AddGroupSuccessful();
#endif // APP_ENABLE_CERTIFICATION_EXTENSION == 0

    case cJoinSuccessfulAndValidEndpoint:
      return JoinSuccessfulAndValidEndpoint();

    case cResetTargetToFn:
      return ResetTargetToFn();

    default:
      (void)arg1;
      (void)arg2;
      return TRUE;
  }
}

/**************************************************************************//**
\brief Checks if join has been successful

\return result of condition check
******************************************************************************/
inline static bool JoinSuccessful(void)
{
  return N_UTIL_BOOL((N_LinkInitiator_Status_t)s_status == N_LinkInitiator_Status_Ok);
}

/**************************************************************************//**
\brief Checks if Target needs to reset to FN

\return result of condition check
******************************************************************************/
inline static bool ResetTargetToFn(void)
{
  return N_UTIL_BOOL(resetTargetToFactoryNew == true);
}

/**************************************************************************//**
\brief Checks if any device has been found during scanning

\return result of condition check
******************************************************************************/
inline static bool DevicesFound(void)
{
  return N_UTIL_BOOL(s_numDevicesFound > 0u);
}

/**************************************************************************//**
\brief Checks if device is factory new or in distributed trust center mode

\return result of condition check
******************************************************************************/
inline static bool IsFactoryNewOrInDistributedTrustCenterMode(void)
{
  if (N_DeviceInfo_IsFactoryNew())
    return TRUE;

  if (N_DeviceInfo_GetTrustCenterMode() == N_DeviceInfo_TrustCenterMode_Distributed)
    return TRUE;

  return FALSE;
}

/**************************************************************************//**
\brief Checks if device is factory new and found device is not factory new

\return result of condition check
******************************************************************************/
inline static bool IsFactoryNewAndOtherNotFactoryNew(void)
{
  bool selfFactoryNew = N_DeviceInfo_IsFactoryNew();
  return N_UTIL_BOOL(selfFactoryNew && ((s_scanIndicationRequest.zllInfo & N_INTERPAN_ZLL_INFO_FACTORY_NEW) == 0u));
}

#if APP_ENABLE_CERTIFICATION_EXTENSION == 0
/**************************************************************************//**
\brief Checks if group has been added succesfully

\return result of condition check
******************************************************************************/
inline static bool AddGroupSuccessful(void)
{
  return N_UTIL_BOOL(s_addGroupStatus == ZCL_SUCCESS_STATUS);
}
#endif // APP_ENABLE_CERTIFICATION_EXTENSION == 0
/**************************************************************************//**
\brief Checks if found edpoint is valid

\return result of condition check
******************************************************************************/
inline static bool ValidEndpoint(void)
{
  if (s_pEpInfo != NULL && s_pEpInfo->deviceId < 0x0400u) // every deviceid >0x0400u is a controller, not a light
    return TRUE;

  return FALSE;
}

/**************************************************************************//**
\brief Checks if join has been successful and found edpoint is valid

\return result of condition check
******************************************************************************/
inline static bool JoinSuccessfulAndValidEndpoint(void)
{
  bool joinSuccess = JoinSuccessful();
  bool validEndpoint = ValidEndpoint();
  return N_UTIL_BOOL(joinSuccess && validEndpoint);
}

/**************************************************************************//**
\brief Shows default status on the lcd
******************************************************************************/
static inline void ShowDefault(void)
{
  LCD_PRINT(0u, LCD_LINE_STATUS, "ZLL Remote      ");

  if (isAnyDeviceBound())
    LCD_PRINT(0u, LCD_LINE_TARGET, "Tgt Group: %04x ", appData.groupId);
}

/**************************************************************************//**
\brief Shows linked status on the lcd
******************************************************************************/
static inline void ShowLinkOk(void)
{
  LCD_PRINT(0u, LCD_LINE_STATUS, "Linked!         ");

  HAL_StartAppTimer(&linkedVisualizationTimer);
  TOUCHLINK_LED_ON();
}

/**************************************************************************//**
\brief Shows not joined status on the lcd
******************************************************************************/
static inline void ShowNotJoined(void)
{
  LCD_PRINT(0u, LCD_LINE_STATUS, "Error: no join  ");
}

/**************************************************************************//**
\brief Shows no devices found status on the lcd
******************************************************************************/
static inline void ShowNoDevicesFound(void)
{
  LCD_PRINT(0u, LCD_LINE_STATUS, "No devices found");
}

/**************************************************************************//**
\brief Shows no devices found status on the lcd
******************************************************************************/
static inline void ShowJoinDeviceError(void)
{
  LCD_PRINT(0u, LCD_LINE_STATUS, "Error: %hd", (uint8_t) s_linkStatus);
}

/**************************************************************************//**
\brief Shows device type information on the lcd
******************************************************************************/
static inline void ShowRouterOrEndDeviceOnLcd(void)
{
  char *deviceType = N_DeviceInfo_IsEndDevice() ? "ed" : "r ";
  LCD_PRINT(0u, LCD_LINE_NETWORK_INFO, "%s", deviceType);
  (void)deviceType;  
}

/**************************************************************************//**
\brief Shows factory new status information on the lcd
******************************************************************************/
static inline void ShowFactoryNewStatusOnLcd(void)
{
  if (N_DeviceInfo_IsFactoryNew())
  {
    LCD_PRINT(2u, LCD_LINE_NETWORK_INFO, "FN   c%u", N_DeviceInfo_GetNetworkChannel());
  }
}

#if APP_ENABLE_CERTIFICATION_EXTENSION == 0
/**************************************************************************//**
\brief Shows failed status for group adding procedure
******************************************************************************/
static inline void ShowAddGroupFailed(void)
{
  LCD_PRINT(0u, LCD_LINE_STATUS, "Add Group Failed");
}

/**************************************************************************//**
\brief Shows successful status for group adding procedure
******************************************************************************/
static inline void ShowAddGroupOk(void)
{
  LCD_PRINT(0u, LCD_LINE_STATUS, "Add Group OK    ");
}
#endif // APP_ENABLE_CERTIFICATION_EXTENSION == 0

/**************************************************************************//**
\brief Starts timer with waiting timeout
******************************************************************************/
static inline void StartWaitTimer(void)
{
  N_Timer_Start16(START_TOUCHLINK_DELAY_MS, &s_timer);
}

/**************************************************************************//**
\brief Starts timer with timeout for identify procedure
******************************************************************************/
static inline void StartIdentifyTimer(void)
{
  N_Timer_Start16(IDENTIFY_TIMEOUT_MS, &s_timer);
}

/**************************************************************************//**
\brief Starts timer with timeout for join procedure
******************************************************************************/
static inline void StartJoinTimer(void)
{
  N_Timer_Start16(JOIN_TIMEOUT_MS, &s_timer);
}

/**************************************************************************//**
\brief Starts timer with timeout for select target mode
******************************************************************************/
static inline void StartTargetSelectedWaitTimer(void)
{
  N_Timer_Start16(SELECTION_TIMEOUT_MS, &s_timer);
}

/**************************************************************************//**
\brief Stops timer
******************************************************************************/
static inline void StopTimer(void)
{
  N_Timer_Stop(&s_timer);
}

/**************************************************************************//**
\brief Resets current target type
******************************************************************************/
static inline void SetTargetTypeNone(void)
{
  N_LinkTarget_SetTargetType(N_LinkTarget_TargetType_None, SetTargetTypeDone);
}

/**************************************************************************//**
\brief Set touchlink target type
******************************************************************************/
static inline void SetTargetTypeTouchlink(void)
{
  N_LinkTarget_SetTargetType(N_LinkTarget_TargetType_Touchlink, SetTargetTypeDone);
}

/**************************************************************************//**
\brief Frees and allocates again memory for found device descriptors

\param[in] numDevices - number of descriptors for found devices
******************************************************************************/
static void ReallocFoundDevices(uint8_t numDevices)
{
  if (s_pFoundDevices != NULL)
  {
    N_Memory_Free(s_pFoundDevices);
    s_pFoundDevices = NULL;
  }

  s_pFoundDevices = (N_LinkInitiator_Device_t *) N_Memory_AllocChecked((size_t)(sizeof(*s_pFoundDevices) * numDevices));
}

/**************************************************************************//**
\brief Runs scaning procedure on primary channels
******************************************************************************/
static inline void TouchlinkScanOnPrimaryChannels(void)
{
  ReallocFoundDevices(TOUCHLINK_SCAN_MAX_DEVICES);
  N_LinkInitiator_Scan(N_LinkInitiator_ScanType_Touchlink, s_pFoundDevices, (uint8_t) TOUCHLINK_SCAN_MAX_DEVICES, ScanDone);
}

/**************************************************************************//**
\brief Runs scaning procedure on primary and secondary channels
******************************************************************************/
static inline void TouchlinkScanOnPrimaryAndSecondaryChannels(void)
{
  ReallocFoundDevices(TOUCHLINK_SCAN_MAX_DEVICES);
  N_LinkInitiator_Scan(N_LinkInitiator_ScanType_Touchlink | N_LinkInitiator_ScanType_IncludeSecondaryChannels, s_pFoundDevices, (uint8_t) TOUCHLINK_SCAN_MAX_DEVICES, ScanDone);
}

/**************************************************************************//**
\brief Stops current scaning procedure
******************************************************************************/
static inline void StopScan(void)
{
  N_LinkInitiator_StopScan();
}

/**************************************************************************//**
\brief Runs identifying procedure
******************************************************************************/
static inline void IdentifyStart(void)
{
  N_LinkInitiator_IdentifyStartRequest(&(s_pFoundDevices[0]), N_LINK_IDENTIFY_TIME_DEFAULT, IdentifyRequestDone);
}

/**************************************************************************//**
\brief Runs Reset To Factory New procedure
******************************************************************************/
static inline void ResetToFactoryNew(void)
{
  N_LinkInitiator_ResetDeviceToFactoryNew(&(s_pFoundDevices[0]), ResetToFactoryNewDone);
}

/**************************************************************************//**
\brief Stops identifying procedure
******************************************************************************/
static inline void IdentifyStop(void)
{
  N_LinkInitiator_IdentifyStopRequest(&(s_pFoundDevices[0]), IdentifyRequestDone);
}

/**************************************************************************//**
\brief Runs join procedure
******************************************************************************/
static inline void JoinDevice(void)
{
  sysAssert(s_numDevicesFound > 0u, REMOTEFSM_JOINDEVICE_0);
  N_LinkInitiator_JoinDevice(&(s_pFoundDevices[0]), FALSE, JoinDeviceDone);
}

/**************************************************************************//**
\brief Runs identifying procedure
******************************************************************************/
static inline void SendDeviceInfoRequest(void)
{
  s_pEpInfo = (N_InterPan_DeviceInfo_t *) N_Memory_AllocChecked((size_t)(sizeof(*s_pEpInfo) * s_pFoundDevices[0].scanResponse.numberSubDevices));
  N_LinkInitiator_DeviceInfoRequest(&(s_pFoundDevices[0]), s_pEpInfo, s_pFoundDevices[0].scanResponse.numberSubDevices, DeviceInfoRequestDone);
}

/**************************************************************************//**
\brief Adds device info to the bound devices table
******************************************************************************/
static inline void AddBoundDevice(void)
{
  BoundDevice_t *dev = boundDeviceAlloc((ExtAddr_t *)s_pEpInfo->ieeeAddress);
  ExtAddr_t *pEpInfoIeeeAddr = (ExtAddr_t *)s_pEpInfo->ieeeAddress;
  if (dev)
  {
    dev->nwkAddr = s_targetNetworkAddress;
    COPY_EXT_ADDR(dev->ieeeAddr, *pEpInfoIeeeAddr);
    dev->endpoint = s_pEpInfo->endPoint;
    dev->profileId = s_pEpInfo->profileId;
    dev->deviceId = s_pEpInfo->deviceId;
    dev->version = s_pEpInfo->version;
    dev->groupIds = s_pEpInfo->groupIds;
    dev->isInGroup = false;

    PDS_Store(ZLL_APP_MEMORY_MEM_ID);
  }

  // We can free the DeviceInfoResponse results here
  N_Memory_Free(s_pEpInfo);
}

/**************************************************************************//**
\brief Issues the add group command towards linked device
******************************************************************************/
#if APP_ENABLE_CERTIFICATION_EXTENSION == 0
static inline void SendAddGroup(void)
{
  DstAddressing_t addressing = {
    .mode = APS_GROUP_ADDRESS,
    .ep = 0
  };

  if (0u == appData.groupId)
    N_AddressManager_AllocateGroupId(&appData.groupId);
  addressing.addr = appData.groupId;

  colorSceneRemoteSendAddGroupCommand(s_targetNetworkAddress,
                                      s_pEpInfo->endPoint,
                                      appData.groupId,
                                      AddGroupResponse);

  clustersSetDstAddressing(&addressing);
}

/**************************************************************************//**
\brief Start polling timer
******************************************************************************/
static inline void StartPollingTimer(void)
{
  appData.busy = true;
  N_Timer_Start16(POLLING_TIMEOUT_MS, &s_timer);
}
#endif // APP_ENABLE_CERTIFICATION_EXTENSION == 0
/**************************************************************************//**
\brief Sets group addressing as default
******************************************************************************/
static inline void SetGroupAddressing(void)
{
  DstAddressing_t addressing = {
    .mode = APS_GROUP_ADDRESS,
    .addr = appData.groupId,
    .ep = 0
  };

  clustersSetDstAddressing(&addressing);
}


/**************************************************************************//**
\brief App is not busy anymore
******************************************************************************/
static inline void SetAppNotBusy(void)
{
  appData.busy = false;
}

/**************************************************************************//**
\brief Callback function, see \ref N_LinkTarget_Callback_t::IdentifyStartIndication.
******************************************************************************/
static void IdentifyStartIndication(uint16_t timeoutInSec)
{
  LCD_PRINT(0u, LCD_LINE_STATUS, "Identify!       ");
  (void)timeoutInSec;
}

/**************************************************************************//**
\brief Callback function, see \ref N_LinkTarget_Callback_t::IdentifyStopIndication.
******************************************************************************/
static void IdentifyStopIndication(void)
{
  ShowDefault();
}

// N_LinkTarget Callbacks

/**************************************************************************//**
\brief Callback function, see \ref N_LinkTarget_Callback_t::JoinNetworkIndication.
******************************************************************************/
static void JoinNetworkIndication(uint16_t groupIdFirst, uint16_t groupIdLast)
{
  N_Task_SetEvent(s_taskId, EVENT_JOIN_NETWORK_INDICATION);
  (void)groupIdFirst;
  (void)groupIdLast;
}

/**************************************************************************//**
\brief Callback function, see \ref N_LinkTarget_Callback_t::UpdateNetworkIndication.
******************************************************************************/
static void UpdateNetworkIndication(void)
{
  N_Task_SetEvent(s_taskId, EVENT_UPDATE_NETWORK_INDICATION);
}

/**************************************************************************//**
\brief Callback function, see \ref N_LinkTarget_Callback_t::N_LinkTarget_SetTargetTypeDone_t.
******************************************************************************/
static void SetTargetTypeDone(void)
{
  N_Task_SetEvent(s_taskId, EVENT_SET_TARGET_TYPE_DONE);
}

/**************************************************************************//**
\brief Callback function, see \ref N_LinkTargets_Callback_t::ScanIndication.

\param[in] pScanRequest - pointer to the request parameters
******************************************************************************/
static void ScanIndication(N_InterPan_ScanRequest_t *pScanRequest)
{
  s_scanIndicationRequest = *pScanRequest;
  N_FSM_PROCESS_EVENT(&s_fsmZllRemote, &s_currentState, eScanIndication);
}

// N_DeviceInfo callbacks
/**************************************************************************//**
\brief Callback function, called if network settings has been changed

\param[in] settings - changed settings mask
******************************************************************************/
static void NetworkSettingsChanged(uint16_t settings)
{
  if (N_DeviceInfo_IsFactoryNew())
  {
    ShowRouterOrEndDeviceOnLcd();
    ShowFactoryNewStatusOnLcd();
  }
  else
  {
    LCD_PRINT(2u, LCD_LINE_NETWORK_INFO, "%04X c%hu p%04X",
              N_DeviceInfo_GetNetworkAddress(), N_DeviceInfo_GetNetworkChannel(), N_DeviceInfo_GetNetworkPanId());
  }
  (void)settings;
}

// N_LinkInitiator callbacks
/**************************************************************************//**
\brief Callback function, called on the end of scanning procedure

\param[in] status - result code of scanning procedure
\param[in] numDevicesFound - amount of found devices
******************************************************************************/
static void ScanDone(N_LinkInitiator_Status_t status, uint8_t numDevicesFound)
{
  s_linkStatus = status;
  s_numDevicesFound = numDevicesFound;
  N_Task_SetEvent(s_taskId, EVENT_SCANDONE);
}

/**************************************************************************//**
\brief Decoupled scanning done callback.

\param[in] status - result code of scanning procedure
\param[in] numDevicesFound - amount of found devices
******************************************************************************/
static void Decoupled_ScanDone(N_LinkInitiator_Status_t status, uint8_t numDevicesFound)
{
  switch (status)
  {
    case N_LinkInitiator_Status_Ok:
      N_FSM_PROCESS_EVENT(&s_fsmZllRemote, &s_currentState, eScanDone);
      break;

    case N_LinkInitiator_Status_Stopped:
      N_FSM_PROCESS_EVENT(&s_fsmZllRemote, &s_currentState, eScanStopped);
      break;

    default:
      break;
  }
  (void)numDevicesFound;
}

/**************************************************************************//**
\brief Callback function, called on the end of identifying procedure

\param[in] status - result code of identifying procedure
******************************************************************************/
static void IdentifyRequestDone(N_LinkInitiator_Status_t status)
{
  s_linkStatus = status;
  N_Task_SetEvent(s_taskId, EVENT_IDENTIFYREQUESTDONE);
}

/**************************************************************************//**
\brief Callback function, called on the end of identifying procedure

\param[in] status - result code of identifying procedure
******************************************************************************/
static void ResetToFactoryNewDone(N_LinkInitiator_Status_t status)
{
  s_linkStatus = status;
  N_Task_SetEvent(s_taskId, EVENT_RESET_DEVICE_TO_FN);
}

/**************************************************************************//**
\brief Decoupled identifying request done callback.

\param[in] status - result code of identifying procedure
******************************************************************************/
static void Decoupled_IdentifyRequestDone(N_LinkInitiator_Status_t status)
{
  N_FSM_PROCESS_EVENT(&s_fsmZllRemote, &s_currentState, eIdentifyRequestDone);
  (void)status;
}

/**************************************************************************//**
\brief Callback function, called on the end of device info requesting procedure

\param[in] status - result code of device info requesting procedure
******************************************************************************/
static void DeviceInfoRequestDone(N_LinkInitiator_Status_t status)
{
  s_linkStatus = status;
  N_Task_SetEvent(s_taskId, EVENT_DEVICEINFOREQUESTDONE);
}

/**************************************************************************//**
\brief Decoupled device info request done callback.

\param[in] status - result code of device info requesting procedure
******************************************************************************/
static void Decoupled_DeviceInfoRequestDone(N_LinkInitiator_Status_t status)
{
  N_FSM_PROCESS_EVENT(&s_fsmZllRemote, &s_currentState, eDeviceInfoRequestDone);
  (void)status;
}

/**************************************************************************//**
\brief Callback function, called on the end of joining procedure

\param[in] status - result code of joining procedure
\param[in] targetNetworkAddress - linked device address
******************************************************************************/
static void JoinDeviceDone(N_LinkInitiator_Status_t status, uint16_t targetNetworkAddress)
{
  s_linkStatus = status;
  s_targetNetworkAddress = targetNetworkAddress;
  N_Task_SetEvent(s_taskId, EVENT_DEVICEJOINDONE);
}

/**************************************************************************//**
\brief Decoupled join device done callback

\param[in] status - result code of joining procedure
******************************************************************************/
static void Decoupled_JoinDeviceDone(N_LinkInitiator_Status_t status)
{
  s_status = (uint8_t)status;
  N_FSM_PROCESS_EVENT(&s_fsmZllRemote, &s_currentState, eJoinDeviceDone);
}

#if APP_ENABLE_CERTIFICATION_EXTENSION == 0
/**************************************************************************//**
\brief Callback function, called on add group response reception

\param[in] status - result code
\param[in] groupId - identifier of added group
******************************************************************************/
static void AddGroupResponse(uint8_t status, uint16_t groupId)
{
  s_addGroupStatus = status;
  N_FSM_PROCESS_EVENT(&s_fsmZllRemote, &s_currentState, eAddGroupResponse);
  (void)groupId;
}
#endif // APP_ENABLE_CERTIFICATION_EXTENSION == 0

/**************************************************************************//**
\brief Device disconnected callback
******************************************************************************/
static void Disconnected(void)
{
  uint32_t sleepPeriod;

  LOG_STRING(disconnectedStr, "Disconnected\r\n");
  appSnprintf(disconnectedStr);

  if (N_END_DEVICE_ROBUSTNESS_IDLE != N_EndDeviceRobustness_GetState())
  {
    parentLost = true;
    // When disconnected event happens, then device won't not in network.
    // so settting end device sleep time to zero so that it will not do 
    // slow polling i.e polling in sleep period interval and taking backup of 
    // sleep period value
    CS_ReadParameter(CS_END_DEVICE_SLEEP_PERIOD_ID, &sleepPeriod);
    if (sleepPeriod)
    {
      sleepPeriodConfigured = sleepPeriod;
      sleepPeriod = 0;
      CS_WriteParameter(CS_END_DEVICE_SLEEP_PERIOD_ID, &sleepPeriod);
    }
  }

  N_Connection_Reconnect();
}

/**************************************************************************//**
\brief Device connected callback
******************************************************************************/
static void Connected(void)
{
  if (parentLost)
  {
    // On reconnection, end device will restore its sleep period value
    // because it was set to zero on previous disconnected event
    if (sleepPeriodConfigured)
    {
      CS_WriteParameter(CS_END_DEVICE_SLEEP_PERIOD_ID, &sleepPeriodConfigured);
      sleepPeriodConfigured = 0;
    }
    parentLost = false;
    restartActivity();
  }
  startOtauClient();
}

/**************************************************************************//**
\brief ResetToFactoryDefaults callback
******************************************************************************/
static void ResetToFactoryDefaults(void)
{
  appResetToFactoryNew();
}

/**************************************************************************//**
\brief Light event handler

\param[in] evt - event id
******************************************************************************/
bool ColorSceneRemote_EventHandler(N_Task_Event_t evt)
{
  switch (evt)
  {
    case EVENT_TIMER:
      N_FSM_PROCESS_EVENT(&s_fsmZllRemote, &s_currentState, eTimer);
      break;

    case EVENT_SCANDONE:
      Decoupled_ScanDone(s_linkStatus, s_numDevicesFound);
      break;

    case EVENT_DEVICEJOINDONE:
      Decoupled_JoinDeviceDone(s_linkStatus);
      break;

    case EVENT_IDENTIFYREQUESTDONE:
      Decoupled_IdentifyRequestDone(s_linkStatus);
      break;

    case EVENT_JOIN_NETWORK_DONE:
      break;

    case EVENT_JOIN_NETWORK_INDICATION:
      N_FSM_PROCESS_EVENT(&s_fsmZllRemote, &s_currentState, eJoinNetworkIndication);
      break;

    case EVENT_UPDATE_NETWORK_INDICATION:
      N_FSM_PROCESS_EVENT(&s_fsmZllRemote, &s_currentState, eUpdateNetworkIndication);
      break;

    case EVENT_SET_TARGET_TYPE_DONE:
      N_FSM_PROCESS_EVENT(&s_fsmZllRemote, &s_currentState, eSetTargetTypeDone);
      break;

    case EVENT_DEVICEINFOREQUESTDONE:
      Decoupled_DeviceInfoRequestDone(s_linkStatus);
      break;

    case EVENT_IDENITFY_DONE:
      break;

    case EVENT_RESET_DEVICE_TO_FN:
      break;

    default:
      //Event not handled
      return FALSE;
  }

  //Event handled
  return TRUE;
}

/**************************************************************************//**
\brief State machine initialization routine
******************************************************************************/
void ColorSceneRemote_FsmInit(void)
{
  s_taskId = N_Task_GetIdFromEventHandler(ColorSceneRemote_EventHandler);

  s_timer.task = s_taskId;
  s_timer.evt = EVENT_TIMER;

  // N_Connection
  static const N_Connection_Callback_t s_N_ConnectionCallback =
  {
    Connected,              // Connected
    Disconnected,           // Disconnected
    NULL,                   // NetworkJoined,
    ResetToFactoryDefaults, // ResetToFactoryDefaults
    NULL,                   // ChildAssociated
    -1
  };
  N_Connection_Subscribe(&s_N_ConnectionCallback);

  // N_DeviceInfo
  static const N_DeviceInfo_Callback_t deviceInfoCb =
  {
    NetworkSettingsChanged,
    -1
  };
  N_DeviceInfo_Subscribe(&deviceInfoCb);

  static const N_LinkTarget_Callback_t linkTargetCb =
  {
    ScanIndication,
    IdentifyStartIndication,
    IdentifyStopIndication,
    NULL,
    JoinNetworkIndication,
    UpdateNetworkIndication,
    -1
  };
  N_LinkTarget_Subscribe(&linkTargetCb);

  LCD_CLEAR();
  ShowRouterOrEndDeviceOnLcd();
  ShowFactoryNewStatusOnLcd();
  ShowDefault();
  NetworkSettingsChanged(0);

  if (N_DeviceInfo_IsFactoryNew())
    boundDeviceTblInit();

}

/**************************************************************************//**
\brief Initiates touchlink performing
******************************************************************************/
void performTouchlink(void)
{
  resetTargetToFactoryNew = false;
  N_FSM_PROCESS_EVENT(&s_fsmZllRemote, &s_currentState, eButtonPressed);
}

/**************************************************************************//**
\brief Stops touchlink performing
******************************************************************************/
void stopTouchlink(void)
{
  N_FSM_PROCESS_EVENT(&s_fsmZllRemote, &s_currentState, eButtonReleased);
}

/**************************************************************************//**
\brief Initiates resetting device to factory new.
******************************************************************************/
void performResetDeviceToFn(void)
{
  resetTargetToFactoryNew = true;
  N_FSM_PROCESS_EVENT(&s_fsmZllRemote, &s_currentState, eButtonPressed);
}

/**************************************************************************//**
\brief Find a suitable slot for a device in the local bind table
\return an index in the table
******************************************************************************/
static void boundDeviceTblInit(void)
{
  for (uint8_t i = 0; i < ZCL_LINK_INFO_CLUSTER_CLIENT_SIDE_ATTRIBUTES_AMOUNT; i++)
    linkInfoGetAttrValue(i)->nwkAddr = NWK_NO_SHORT_ADDR;
}

/**************************************************************************//**
\brief Find a suitable slot for a device in the local bind table
\return an index in the table
******************************************************************************/
static BoundDevice_t *boundDeviceAlloc(ExtAddr_t *targetExtAddr)
{
  BoundDevice_t *device;

  for (uint8_t i = 0; i < ZCL_LINK_INFO_CLUSTER_CLIENT_SIDE_ATTRIBUTES_AMOUNT; i++)
  {
    device = linkInfoGetAttrValue(i);
    if (device->ieeeAddr == *targetExtAddr)
      return device;
  }

  for (uint8_t i = 0; i < ZCL_LINK_INFO_CLUSTER_CLIENT_SIDE_ATTRIBUTES_AMOUNT; i++)
  {
    device = linkInfoGetAttrValue(i);
    if (NWK_NO_SHORT_ADDR == device->nwkAddr)
      return device;
  }

  return NULL;
}

/**************************************************************************//**
\brief Check for any bound device in local table
\return true - if one exist; false - otherwise
******************************************************************************/
bool isAnyDeviceBound(void)
{
  for (uint8_t i = 0; i < ZCL_LINK_INFO_CLUSTER_CLIENT_SIDE_ATTRIBUTES_AMOUNT; i++)
    if (NWK_NO_SHORT_ADDR != linkInfoGetAttrValue(i)->nwkAddr)
      return true;

  return false;
}

/**************************************************************************//**
\brief Get the next device from the local bind table
\return an index in the table
******************************************************************************/
BoundDevice_t *boundDeviceNext(void)
{
  int8_t dev = currentBoundDevice + 1;
  BoundDevice_t *device = NULL;

  for (uint8_t i = 0; i < ZCL_LINK_INFO_CLUSTER_CLIENT_SIDE_ATTRIBUTES_AMOUNT; i++)
  {
    if (dev == ZCL_LINK_INFO_CLUSTER_CLIENT_SIDE_ATTRIBUTES_AMOUNT)
      dev = 0;

    device = linkInfoGetAttrValue(dev);
    if ((NULL != device) && (NWK_NO_SHORT_ADDR != device->nwkAddr))
    {
      currentBoundDevice = dev;
      return device;
    }

    dev++;
  }

  return NULL;
}

/**************************************************************************//**
\brief Get the previous device from the local bind table
\return an index in the table
******************************************************************************/
BoundDevice_t *boundDevicePrev(void)
{
  int8_t dev = currentBoundDevice - 1;
  BoundDevice_t *device = NULL;

  for (uint8_t i = 0; i < ZCL_LINK_INFO_CLUSTER_CLIENT_SIDE_ATTRIBUTES_AMOUNT; i++)
  {
    if (dev == -1)
      dev = ZCL_LINK_INFO_CLUSTER_CLIENT_SIDE_ATTRIBUTES_AMOUNT - 1;

    device = linkInfoGetAttrValue(dev);
    if ((NULL != device) && (NWK_NO_SHORT_ADDR != device->nwkAddr))
    {
      currentBoundDevice = dev;
      return device;
    }

    dev--;
  }

  return NULL;
}


/**************************************************************************//**
\brief Send an identify command to the selected device
******************************************************************************/
static void identifySelectedDevice(void)
{
  CommandDescriptor_t *cmd;

  cmd = clustersAllocCommand();

  if (cmd)
  {
    cmd->clusterId = IDENTIFY_CLUSTER_ID;
    cmd->commandId = ZCL_IDENTIFY_CLUSTER_IDENTIFY_COMMAND_ID;
    cmd->payload.identify.identifyTime = 4;
    cmd->size = sizeof(cmd->payload.identify);
    clustersSendCommand(cmd);
  }
}

/**************************************************************************//**
\brief Shows the selected bound device
******************************************************************************/
static void showBoundDevice(BoundDevice_t *dev)
{
  DstAddressing_t addressing = {
    .mode = APS_SHORT_ADDRESS,
    .addr = dev->nwkAddr,
    .ep = dev->endpoint,
    .defaultResponse = true
  };

  clustersSetDstAddressing(&addressing);
  identifySelectedDevice();

  LCD_PRINT(0, LCD_LINE_TARGET, "Tgt Device: %04x ", dev->nwkAddr);

  N_FSM_PROCESS_EVENT(&s_fsmZllRemote, &s_currentState, eTargetSelected);
}


/**************************************************************************//**
\brief Get the next bound device from the local binding table and send
an identify command to it
******************************************************************************/
void selectNextBoundDevice(void)
{
  BoundDevice_t *dev = boundDeviceNext();

  if (dev)
    showBoundDevice(dev);
}

/**************************************************************************//**
\brief Get the previous bound device from the local binding table and send
an identify command to it
******************************************************************************/
void selectPrevBoundDevice(void)
{
  BoundDevice_t *dev = boundDevicePrev();

  if (dev)
    showBoundDevice(dev);
}

/**************************************************************************//**
\brief Remove a previously bound device from the application table

\param[in] extAddr - the extended address of the device to be removed
******************************************************************************/
void removeBoundDevice(ExtAddr_t *extAddr)
{
  BoundDevice_t *device;

  for (uint8_t i = 0; i < ZCL_LINK_INFO_CLUSTER_CLIENT_SIDE_ATTRIBUTES_AMOUNT; i++)
  {
    device = linkInfoGetAttrValue(i);
    if (IS_EQ_EXT_ADDR(device->ieeeAddr, *extAddr))
      device->nwkAddr = NWK_NO_SHORT_ADDR;
  }
}

/**************************************************************************//**
\brief Returns current group id
******************************************************************************/
uint16_t getOwnGroupId(void)
{
  return appData.groupId;
}

/**************************************************************************//**
\brief Linked visualization timer has fired
******************************************************************************/
static void linkedVisualizationTimerFired(void)
{
  TOUCHLINK_LED_OFF();
}
#endif // APP_ZLL_DEVICE_TYPE == APP_DEVICE_TYPE_COLOR_SCENE_REMOTE
