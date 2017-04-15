/************************************************************************//**
  \file combinedInterface.c

  \brief
    Combined Interface implementation

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2013, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    26/12/14 Prashanth.Udumula - modified
    13/06/14 Viswanadham Kotla - modified
    05/08/14 Unithra C         - modified
    18/11/14 Yogesh            - modified
******************************************************************************/
#ifdef APP_DEVICE_TYPE_COMBINED_INTERFACE

/******************************************************************************
                        Includes section
******************************************************************************/
#include <ciClusters.h>
#include <basicCluster.h>
#include <identifyCluster.h>
#include <ciOnOffCluster.h>
#include <ciLevelControlCluster.h>
#include <ciGroupsCluster.h>
#include <ciOccupancySensingCluster.h>
#include <ciTemperatureMeasurementCluster.h>
#include <ciHumidityMeasurementCluster.h>
#include <ciIlluminanceMeasurementCluster.h>
#include <ciThermostatCluster.h>
#include <ciThermostatUiConfCluster.h>
#include <ciTimeCluster.h>
#include <ciScenesCluster.h>
#include <ciFanControlCluster.h>
#include <ciIasZoneCluster.h>
#include <ciIasACECluster.h>
#include <ciPowerConfigurationCluster.h>
#include <zclDevice.h>
#include <uartManager.h>
#include <console.h>
#include <zclSecurityManager.h>
#include <resetReason.h>
#include <commandManager.h>
#include <ezModeManager.h>
#include <otauService.h>
#include <mac.h>
/******************************************************************************
                    Local variables section
******************************************************************************/
static ZCL_DeviceEndpoint_t ciEndpoint =
{
  .simpleDescriptor =
  {
    .endpoint            = APP_SRC_ENDPOINT_ID,
    .AppProfileId        = PROFILE_ID_HOME_AUTOMATION,
    .AppDeviceId         = HA_COMBINED_INTERFACE_ID,
    .AppInClustersCount  = ARRAY_SIZE(ciServerClusterIds),
    .AppInClustersList   = ciServerClusterIds,
    .AppOutClustersCount = ARRAY_SIZE(ciClientClusterIds),
    .AppOutClustersList  = ciClientClusterIds,
  },
  .serverCluster = ciServerClusters,
  .clientCluster = ciClientClusters,
};

static ClusterId_t ciClientClusterToBindIds[] =
{
  ONOFF_CLUSTER_ID,
  LEVEL_CONTROL_CLUSTER_ID,
  GROUPS_CLUSTER_ID,
  SCENES_CLUSTER_ID,
  OCCUPANCY_SENSING_CLUSTER_ID,
  TEMPERATURE_MEASUREMENT_CLUSTER_ID,
  HUMIDITY_MEASUREMENT_CLUSTER_ID,
  ILLUMINANCE_MEASUREMENT_CLUSTER_ID,
  THERMOSTAT_CLUSTER_ID,
  THERMOSTAT_UI_CONF_CLUSTER_ID,
  DIAGNOSTICS_CLUSTER_ID,
  ALARMS_CLUSTER_ID,
  POWER_CONFIGURATION_CLUSTER_ID,
  FAN_CONTROL_CLUSTER_ID,
  IAS_ZONE_CLUSTER_ID,
};
static ClusterId_t ciServerClusterToBindIds[] =
{
  TIME_CLUSTER_ID,
  IAS_ACE_CLUSTER_ID,  
};
static AppBindReq_t ciBindReq =
{
  .nwkAddrOfInterest = RX_ON_WHEN_IDLE_ADDR,
  .remoteServers     = ciClientClusterToBindIds,
  .remoteServersCnt  = ARRAY_SIZE(ciClientClusterToBindIds),
  .remoteClients     = ciServerClusterToBindIds,
  .remoteClientsCnt  = ARRAY_SIZE(ciServerClusterToBindIds),
  .profile           = PROFILE_ID_HOME_AUTOMATION,
  .srcEndpoint       = APP_SRC_ENDPOINT_ID,
  .callback          = NULL,
};

static AppBindReq_t* deviceBindReqs[APP_ENDPOINTS_AMOUNT];

static ZCL_LinkKeyDesc_t lightKeyDesc = {CCPU_TO_LE64(APS_UNIVERSAL_EXTENDED_ADDRESS), HA_LINK_KEY};

/******************************************************************************
                        Implementations section
******************************************************************************/
/**************************************************************************//**
\brief Device initialization routine
******************************************************************************/
void appDeviceInit(void)
{
  ZCL_RegisterEndpoint(&ciEndpoint);

#if (APP_ENABLE_CONSOLE == 1) || (APP_DEVICE_EVENTS_LOGGING == 1)
  uartInit();
#endif
#if APP_ENABLE_CONSOLE == 1
  initConsole();
#endif
  /* Bind request with clusters to bind for initiator device */
  deviceBindReqs[0] = &ciBindReq;

  commandManagerInit();

  basicClusterInit();
  identifyClusterInit();
  onOffClusterInit();
  levelControlClusterInit();
  groupsClusterInit();
  scenesClusterInit();
  occupancySensingClusterInit();
  temperatureMeasurementClusterInit();
  humidityMeasurementClusterInit();
  illuminanceMeasurementClusterInit();
  thermostatClusterInit();
  timeClusterInit();
  fanControlClusterInit();
  iaszoneClusterInit();
  iasACEClusterInit();
  powerConfigurationClusterInit();
}

/**************************************************************************//**
\brief Performs security initialization actions
******************************************************************************/
void appSecurityInit(void)
{
  ZCL_Set_t zclSet;
  ExtAddr_t trustCenterAddress;
  ExtAddr_t macAddr;
  APS_TcMode_t tcMode;
  DeviceType_t deviceType;
  // Setup security parameters
  bool securityOn;

  CS_ReadParameter(CS_SECURITY_ON_ID, &securityOn);
  if (securityOn)
  {
    uint8_t preconfiguredStatus;
    CS_ReadParameter(CS_APS_TRUST_CENTER_ADDRESS_ID, &trustCenterAddress);
    CS_ReadParameter(CS_UID_ID, &macAddr);
    if (IS_EQ_EXT_ADDR(macAddr, trustCenterAddress))
      tcMode = APS_CENTRALIZED_TRUST_CENTER;
    else
      tcMode = APS_NOT_TRUST_CENTER;

    CS_ReadParameter(CS_ZDO_SECURITY_STATUS_ID, &preconfiguredStatus);
    CS_ReadParameter(CS_DEVICE_TYPE_ID, &deviceType);

    if ((PRECONFIGURED_NETWORK_KEY == preconfiguredStatus)
      || (APS_CENTRALIZED_TRUST_CENTER == tcMode)
    )
    {
      uint8_t nwkDefaultKey[SECURITY_KEY_SIZE];

      CS_ReadParameter(CS_NETWORK_KEY_ID, &nwkDefaultKey);
      NWK_SetKey(nwkDefaultKey, NWK_STARTUP_ACTIVE_KEY_SEQUENCE_NUMBER);
      NWK_ActivateKey(NWK_STARTUP_ACTIVE_KEY_SEQUENCE_NUMBER);
    }
  }

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
        startOtauServer(&ciServerClusters[CI_SERVER_CLUSTERS_COUNT - 1]);
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

#endif // APP_DEVICE_TYPE_COMBINED_INTERFACE
// eof combinedInterface.c