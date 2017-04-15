/************************************************************************//**
  \file dimmerSwitch.c

  \brief
    Dimmer Switch implementation

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    26/12/14 Prashanth.Udumula - modified
******************************************************************************/
#ifdef APP_DEVICE_TYPE_DIMMER_SWITCH

/******************************************************************************
                        Includes section
******************************************************************************/
#include <dsClusters.h>
#include <basicCluster.h>
#include <identifyCluster.h>
#include <dsOnOffCluster.h>
#include <dsLevelControlCluster.h>
#include <dsPowerConfigurationCluster.h>
#include <zclDevice.h>
#include <uartManager.h>
#include <console.h>
#include <zclSecurityManager.h>
#include <sysIdleHandler.h>
#include <ezModeManager.h>
#include <otauService.h>
#include <sleep.h>
#include <halSleep.h>

/******************************************************************************
                        Prototypes section
******************************************************************************/
static void isBusyOrPollCheck(SYS_EventId_t eventId, SYS_EventData_t data);
#if defined (_SLEEP_WHEN_IDLE_)
#if (APP_ENABLE_CONSOLE == 1)
static void sleepModeHandler(SYS_EventId_t eventId, SYS_EventData_t data);
#endif
static void sleepEventHandler(SYS_EventId_t eventId, SYS_EventData_t data);
static void ZDO_WakeUpConf(ZDO_WakeUpConf_t *conf);
#endif

/******************************************************************************
                    Local variables section
******************************************************************************/
static ZCL_DeviceEndpoint_t dsEndpoint =
{
  .simpleDescriptor =
  {
    .endpoint            = APP_SRC_ENDPOINT_ID,
    .AppProfileId        = PROFILE_ID_HOME_AUTOMATION,
    .AppDeviceId         = HA_DIMMER_SWITCH_DEVICE_ID,
    .AppInClustersCount  = ARRAY_SIZE(dsServerClusterIds),
    .AppInClustersList   = dsServerClusterIds,
    .AppOutClustersCount = ARRAY_SIZE(dsClientClusterIds),
    .AppOutClustersList  = dsClientClusterIds,
  },
  .serverCluster = dsServerClusters,
  .clientCluster = dsClientClusters,
};

static ClusterId_t dsClientClusterToBindIds[] =
{
  ONOFF_CLUSTER_ID,
  LEVEL_CONTROL_CLUSTER_ID
};

static ClusterId_t dsServerClusterToBindIds[] =
{
  POWER_CONFIGURATION_CLUSTER_ID,
  ALARMS_CLUSTER_ID
};
static AppBindReq_t dsBindReq =
{
  .nwkAddrOfInterest = RX_ON_WHEN_IDLE_ADDR,
  .remoteServers     = dsClientClusterToBindIds,
  .remoteServersCnt  = ARRAY_SIZE(dsClientClusterToBindIds),
  .remoteClients     = dsServerClusterToBindIds,
  .remoteClientsCnt  = ARRAY_SIZE(dsServerClusterToBindIds),
  .profile           = PROFILE_ID_HOME_AUTOMATION,
  .srcEndpoint       = APP_SRC_ENDPOINT_ID,
  .callback          = NULL,
};

static ZCL_LinkKeyDesc_t lightKeyDesc = {CCPU_TO_LE64(APS_UNIVERSAL_EXTENDED_ADDRESS), HA_LINK_KEY};
static SYS_EventReceiver_t zdoBusyPollCheck = { .func = isBusyOrPollCheck};
#if defined (_SLEEP_WHEN_IDLE_)
static ZDO_WakeUpReq_t zdoWakeUpReq;
static SYS_EventReceiver_t sleepEventListener = {.func = sleepEventHandler};
#if (APP_ENABLE_CONSOLE == 1)
static SYS_EventReceiver_t sleepModeListener = {.func = sleepModeHandler};
#endif
#endif
static AppBindReq_t* deviceBindReqs[APP_ENDPOINTS_AMOUNT];
/******************************************************************************
                        Implementations section
******************************************************************************/
/**************************************************************************//**
\brief Device initialization routine
******************************************************************************/
void appDeviceInit(void)
{
  ZCL_RegisterEndpoint(&dsEndpoint);

#if (APP_ENABLE_CONSOLE == 1) || (APP_DEVICE_EVENTS_LOGGING == 1)
  uartInit();
#endif
#if APP_ENABLE_CONSOLE == 1
  initConsole();
#endif
  /* Bind request with clusters to bind for initiator device */
  deviceBindReqs[0] = &dsBindReq;

  basicClusterInit();
  identifyClusterInit();
  onOffClusterInit();
  levelControlClusterInit();
  powerConfigurationClusterInit();
#if defined (_SLEEP_WHEN_IDLE_)
  SYS_EnableSleepWhenIdle();
#if (APP_ENABLE_CONSOLE == 1)
  SYS_SubscribeToEvent(HAL_EVENT_FALLING_ASLEEP, &sleepModeListener);
  SYS_SubscribeToEvent(HAL_EVENT_CONTINUING_SLEEP, &sleepModeListener);
#endif
  SYS_SubscribeToEvent(HAL_EVENT_WAKING_UP, &sleepEventListener);
#endif
  SYS_SubscribeToEvent(BC_EVENT_POLL_REQUEST, &zdoBusyPollCheck);
}

/**************************************************************************//**
\brief Performs security initialization actions
******************************************************************************/
void appSecurityInit(void)
{
  ZCL_Set_t zclSet;

  ZCL_ResetSecurity();

  //Setting the Link Key Descriptor
  zclSet.attr.id = ZCL_LINK_KEY_DESC_ID;
  zclSet.attr.value.linkKeyDesc = &lightKeyDesc;
  ZCL_Set(&zclSet);
}

/**************************************************************************//**
\brief Device common task handler
******************************************************************************/
void appDeviceTaskHandler(void)
{
  switch (appDeviceState) // Actual device state when one joined network
  {
    case DEVICE_INITIAL_STATE:
      {
        appDeviceState = DEVICE_ACTIVE_IDLE_STATE;
        startOtauClient(&dsClientClusters[DS_CLIENT_CLUSTERS_COUNT - 1]);
      }
      break;
    case DEVICE_ACTIVE_IDLE_STATE:
    default:
      break;
  }
}

/**************************************************************************//**
\brief Gets bind request

\return pointer to a bind request used by HA device
******************************************************************************/
AppBindReq_t **getDeviceBindRequest(void)
{
  return deviceBindReqs;
}

/**************************************************************************//**
\brief Stops application
******************************************************************************/
void appStop(void)
{
  identifyClusterStop();
}

/**************************************************************************//**
\brief Asks device if it is an initiator

\returns true if it is, false otherwise
******************************************************************************/
bool appIsInitiator(void)
{
  return true;
}

/**************************************************************************//**
\brief EZ-Mode done callback

\returns function which is called by EZ-Mode manager when it is done
******************************************************************************/
void appEzModeDone(void)
{}

/**************************************************************************//**
\brief ZDO Binding indication function

\param[out] bindInd - ZDO bind indication parameters structure pointer
******************************************************************************/
void ZDO_BindIndication(ZDO_BindInd_t *bindInd)
{
  (void)bindInd;
}

/**************************************************************************//**
\brief ZDO Unbinding indication function

\param[out] unbindInd - ZDO unbind indication parameters structure pointer
******************************************************************************/
void ZDO_UnbindIndication(ZDO_UnbindInd_t *unbindInd)
{
  (void)unbindInd;
}

/**************************************************************************//**
  \brief Processes BC_EVENT_POLL_REQUEST event

  \param[in] eventId - id of raised event;
  \param[in] data    - event's data.
******************************************************************************/
static void isBusyOrPollCheck(SYS_EventId_t eventId, SYS_EventData_t data)
{
#if defined (_SLEEP_WHEN_IDLE_)
  bool *check = (bool *)data;

  *check |= isEzModeInProgress();
  (void)eventId;
#else
  (void)eventId, (void)data;
#endif
}

#if defined (_SLEEP_WHEN_IDLE_)
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
  (void)eventId;
}

/**************************************************************************//**
  \brief Wake up confirmation handler.

  \param[in] conf - confirmation parameters.
*****************************************************************************/
static void ZDO_WakeUpConf(ZDO_WakeUpConf_t *conf)
{
  (void)conf;
}

#if (APP_ENABLE_CONSOLE == 1)
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
#endif // #if (APP_ENABLE_CONSOLE == 1)
#endif // #if defined (_SLEEP_WHEN_IDLE_)
#endif // APP_DEVICE_TYPE_DIMMER_SWITCH
// eof dimmerSwitch.c