/**************************************************************************//**
  \file dimmableLight.c

  \brief
    Dimmable Light implementation.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    26/12/14 Prashanth.Udumula - modified
******************************************************************************/
#ifdef APP_DEVICE_TYPE_MYAPP

/******************************************************************************
                             Includes section
******************************************************************************/
#include <myappClusters.h>
#include <basicCluster.h>
#include <identifyCluster.h>
#include <myappOnOffCluster.h>
#include <myappLevelControlCluster.h>
#include <myappGroupsCluster.h>
#include <myappScenesCluster.h>
#include <zclDevice.h>
#include <zclSecurityManager.h>
#include <uartManager.h>
#include <console.h>
#include <pdsDataServer.h>
#include <ezModeManager.h>
#include <haClusters.h>
#include <otauService.h>
#include <bspLeds.h>
#include <buttons.h>
#include <resetReason.h>

/*******************************************************************************
                    Static functions section
*******************************************************************************/
static void updateCommissioningStateCb(ZCL_Addressing_t *addressing, ZCL_UpdateCommissioningState_t *payload);
static void buttonsReleased(uint8_t buttonNumber);          // Button release event handler
static void buttonsPressed(uint8_t buttonNumber);          // Button release event handler


/******************************************************************************
                    Local variables section
***********************************************f*******************************/
static ZCL_DeviceEndpoint_t dlEndpoint =
{
  .simpleDescriptor =
  {
    .endpoint            = APP_SRC_ENDPOINT_ID,
    .AppProfileId        = PROFILE_ID_HOME_AUTOMATION,
    .AppDeviceId         = HA_DIMMABLE_LIGHT_DEVICE_ID,
    .AppInClustersCount  = ARRAY_SIZE(dlServerClusterIds),
    .AppInClustersList   = dlServerClusterIds,
#ifdef OTAU_CLIENT
    .AppOutClustersCount = ARRAY_SIZE(dlClientClusterIds),
    .AppOutClustersList  = dlClientClusterIds,
#else
    .AppOutClustersCount = 0,
    .AppOutClustersList  = NULL,
#endif
  },
  .serverCluster = dlServerClusters,
#ifdef OTAU_CLIENT
  .clientCluster = dlClientClusters,
#else
  .clientCluster = NULL,
#endif
};

static ZCL_LinkKeyDesc_t lightKeyDesc = {APS_UNIVERSAL_EXTENDED_ADDRESS  /*addr*/,
                                         HA_LINK_KEY /*key*/};

static IdentifySubscriber_t subcriber =
{
  .updateCommissioningState = updateCommissioningStateCb
};
uint32_t time_button_pressed;

/******************************************************************************
                    Prototypes section
******************************************************************************/
static void dlConfigureReportingResp(ZCL_Notify_t *ntfy);

/******************************************************************************
                    Implementation section
******************************************************************************/
/**************************************************************************//**
\brief Device initialization routine
******************************************************************************/
void appDeviceInit(void)
{
  ZCL_RegisterEndpoint(&dlEndpoint);

#if (APP_ENABLE_CONSOLE == 1) || (APP_DEVICE_EVENTS_LOGGING == 1)
  uartInit();
#endif
#if APP_ENABLE_CONSOLE == 1
  initConsole();
#endif
  /* Subscribe the Commissioning update command for Target devices */
  identifySubscribe(&subcriber);

  basicClusterInit();
  identifyClusterInit();
  onOffClusterInit();
  levelControlClusterInit();
  groupsClusterInit();
  scenesClusterInit();
  
  // my lines
  //BSP_OpenLeds();
  BSP_OpenButtons(buttonsPressed, buttonsReleased);
  
  GPIO_A19_make_out();
  GPIO_A16_make_out();
  GPIO_B23_make_out();


  if (PDS_IsAbleToRestore(APP_DL_SCENES_MEM_ID))
    PDS_Restore(APP_DL_SCENES_MEM_ID);
  if (PDS_IsAbleToRestore(APP_DL_ONOFF_MEM_ID))
    PDS_Restore(APP_DL_ONOFF_MEM_ID);
  if (PDS_IsAbleToRestore(APP_DL_LEVEL_CONTROL_MEM_ID))
    PDS_Restore(APP_DL_LEVEL_CONTROL_MEM_ID);

  ZCL_StartReporting();
}

/*******************************************************************************
  \brief Button release event handler

  \return none
*******************************************************************************/
static void buttonsReleased(uint8_t buttonNumber)
{
	(void)buttonNumber;
	uint32_t time_button_released = HAL_GetSystemTime();
	uint32_t diff = time_button_released - time_button_pressed;
	if (diff > 600)
	{
		PDS_DeleteAll(false);
		HAL_WarmReset();
	}
}
/*******************************************************************************
  \brief Button pressed event handler

  \return none
*******************************************************************************/
static void buttonsPressed(uint8_t buttonNumber)
{
	(void)buttonNumber;
	time_button_pressed = HAL_GetSystemTime();
}

/**************************************************************************//**
\breif Performs security initialization actions
******************************************************************************/
void appSecurityInit(void)
{
  ZCL_Set_t zclSet;

  ZCL_ResetSecurity();
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
      }
#ifdef OTAU_CLIENT
      startOtauClient(&dlClientClusters[DL_CLIENT_CLUSTERS_COUNT - 1]);
#endif
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
  return NULL;
}

/**************************************************************************//**
\brief Stops application
******************************************************************************/
void appStop(void)
{
  identifyClusterStop();
  levelControlClusterStop();
}

/**************************************************************************//**
\brief Asks device if it is an initiator

\returns true if it is, false otherwise
******************************************************************************/
bool appIsInitiator(void)
{
  return false;
}

/**************************************************************************//**
\brief EZ-Mode done callback

\returns function which is called by EZ-Mode manager when it is done
******************************************************************************/
void appEzModeDone(void)
{}

/**************************************************************************//**
\brief Update Commissioning State received callback

\param[in] addressing - pointer to addressing information;
\param[in] payload - data pointer
******************************************************************************/
static void updateCommissioningStateCb(ZCL_Addressing_t *addressing, ZCL_UpdateCommissioningState_t *payload)
{
  sendConfigureReportingToNotify(APP_SRC_ENDPOINT_ID, APP_ENDPOINT_COMBINED_INTERFACE,
                                 ONOFF_CLUSTER_ID, ZCL_ONOFF_CLUSTER_ONOFF_SERVER_ATTRIBUTE_ID,
                                 ONOFF_VAL_MAX_REPORT_PERIOD * 2, dlConfigureReportingResp);
  (void)addressing, (void)payload;
}
/**************************************************************************//**
\brief Indication of configure reporting response

\param[in] ntfy - pointer to response
******************************************************************************/
static void dlConfigureReportingResp(ZCL_Notify_t *ntfy)
{
  sendConfigureReportingToNotify(APP_SRC_ENDPOINT_ID, APP_ENDPOINT_COMBINED_INTERFACE, 
                                 LEVEL_CONTROL_CLUSTER_ID,ZCL_LEVEL_CONTROL_CLUSTER_CURRENT_LEVEL_ATTRIBUTE_ID, 
                                 LEVEL_CONTROL_VAL_MAX_REPORT_PERIOD * 2, NULL);
  ZCL_StartReporting();
  (void)ntfy;
}
/**************************************************************************//**
\brief ZDO Binding indication function

\param[out] bindInd - ZDO bind indication parameters structure pointer. For details go to
            ZDO_BindInd_t declaration
******************************************************************************/
void ZDO_BindIndication(ZDO_BindInd_t *bindInd)
{
  (void)bindInd;
}

/**************************************************************************//**
\brief ZDO Unbinding indication function

\param[out] unbindInd - ZDO unbind indication parameters structure pointer. For details go to
            ZDO_UnbindInd_t declaration
******************************************************************************/
void ZDO_UnbindIndication(ZDO_UnbindInd_t *unbindInd)
{
  (void)unbindInd;
}

#endif // APP_DEVICE_TYPE_MYAPP
// eof dimmableLight.c