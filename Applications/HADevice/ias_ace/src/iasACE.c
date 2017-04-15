/**************************************************************************//**
  \file iasACE.c

  \brief
    Intruder Alarm System -  Ancillary Control Equipment.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    18/11/2014 Yogesh  - Created
******************************************************************************/
#ifdef APP_DEVICE_TYPE_IAS_ACE

/******************************************************************************
                             Includes section
******************************************************************************/
#include <iasACECluster.h>
#include <iasACEZoneCluster.h>
#include <basicCluster.h>
#include <identifyCluster.h>
#include <zclDevice.h>
#include <zclSecurityManager.h>
#include <uartManager.h>
#include <console.h>
#include <pdsDataServer.h>
#include <ezModeManager.h>
#include <haClusters.h>
#include <otauService.h>
#include <iasACEIdentifyCluster.h>
#include <iasACEDiagnosticsCluster.h>
#include <iasACEBasicCluster.h>

/******************************************************************************
                   Define(s) section
******************************************************************************/

/*******************************************************************************
                    Static functions section
*******************************************************************************/
static void updateCommissioningStateCb(ZCL_Addressing_t *addressing, ZCL_UpdateCommissioningState_t *payload);
/******************************************************************************
                    Local variables section
******************************************************************************/
static ZCL_DeviceEndpoint_t iasACEEndpoint =
{
  .simpleDescriptor =
  {
    .endpoint            = APP_SRC_ENDPOINT_ID,
    .AppProfileId        = PROFILE_ID_HOME_AUTOMATION,
    .AppDeviceId         = HA_IAS_ACE_DEVICE_ID,
    .AppInClustersCount  = ARRAY_SIZE(iasACEServerClusterIds),
    .AppInClustersList   = iasACEServerClusterIds,
    .AppOutClustersCount = ARRAY_SIZE(iasACEClientClusterIds),
    .AppOutClustersList  = iasACEClientClusterIds,
  },
  .serverCluster = iasACEServerClusters,
  .clientCluster = iasACEClientClusters,
};

static ZCL_LinkKeyDesc_t iasZoneKeyDesc = {CCPU_TO_LE64(APS_UNIVERSAL_EXTENDED_ADDRESS)  /*addr*/,HA_LINK_KEY /*key*/};

static IdentifySubscriber_t subcriber =
{
  .updateCommissioningState = updateCommissioningStateCb
};

/******************************************************************************
                    Implementation section
******************************************************************************/

/**************************************************************************//**
\brief Device initialization routine
******************************************************************************/
void appDeviceInit(void)
{
  ZCL_RegisterEndpoint(&iasACEEndpoint);

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
  diagnosticsClusterInit();
  iasZoneClusterInit();
  iasACEClusterInit();

  //PDS store for Attributes - IAS Zones
  if (PDS_IsAbleToRestore(APP_IAS_ACE_ZONE_STATE_MEM_ID))
    PDS_Restore(APP_IAS_ACE_ZONE_STATE_MEM_ID);
  if (PDS_IsAbleToRestore(APP_IAS_ACE_ZONE_TYPE_MEM_ID))
    PDS_Restore(APP_IAS_ACE_ZONE_TYPE_MEM_ID);
  if (PDS_IsAbleToRestore(APP_IAS_ACE_ZONE_STATUS_MEM_ID))
    PDS_Restore(APP_IAS_ACE_ZONE_STATUS_MEM_ID);
  if (PDS_IsAbleToRestore(APP_IAS_ACE_ZONE_CIE_ADDR_MEM_ID))
    PDS_Restore(APP_IAS_ACE_ZONE_CIE_ADDR_MEM_ID);
  if (PDS_IsAbleToRestore(APP_IAS_ACE_ZONE_ID_MEM_ID))
    PDS_Restore(APP_IAS_ACE_ZONE_ID_MEM_ID);
  if (PDS_IsAbleToRestore(APP_IAS_ACE_ZONE_NO_SENSITIVITY_LEVELS_MEM_ID))
    PDS_Restore(APP_IAS_ACE_ZONE_NO_SENSITIVITY_LEVELS_MEM_ID);
  if (PDS_IsAbleToRestore(APP_IAS_ACE_ZONE_NO_CURR_SENSITIVITY_LEV_MEM_ID))
    PDS_Restore(APP_IAS_ACE_ZONE_NO_CURR_SENSITIVITY_LEV_MEM_ID);
}

/**************************************************************************//**
\breif Performs security initialization actions
******************************************************************************/
void appSecurityInit(void)
{
  ZCL_Set_t zclSet;

  ZCL_ResetSecurity();
  zclSet.attr.id = ZCL_LINK_KEY_DESC_ID;
  zclSet.attr.value.linkKeyDesc = &iasZoneKeyDesc;
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
  startOtauClient(&iasACEClientClusters[IAS_ACE_CLIENT_CLUSTERS_COUNT - 1]);
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
#if APP_ENABLE_CONSOLE != 1
  sendZoneEnrollRequestCommand(addressing->addr.shortAddress);
#endif  
  (void)addressing, (void)payload;
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
#endif // APP_DEVICE_TYPE_THERMOSTAT
// eof iasACE.c
