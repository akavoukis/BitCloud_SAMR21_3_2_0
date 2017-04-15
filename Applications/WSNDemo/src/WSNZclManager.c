/***************************************************************************//**
  \file WSNZclManger.c

  \brief
    WSNDemo ZCL Manager implementation

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    19.04.10 A. Razinkov - Created.
*******************************************************************************/

#if APP_USE_OTAU == 1

/*******************************************************************************
                             Includes section
*******************************************************************************/
#include <WSNZclManager.h>
#include <zclOTAUCluster.h>
#include <WSNDemoApp.h>
#include <resetReason.h>

/*******************************************************************************
                             Defines section
*******************************************************************************/
#if defined(OTAU_CLIENT)

#define OUT_CLUSTERS_COUNT 1
#define IN_CLUSTERS_COUNT 0

#elif defined(OTAU_SERVER)

#define OUT_CLUSTERS_COUNT 0
#define IN_CLUSTERS_COUNT 1

#endif

/*******************************************************************************
                            Local variables section
 ******************************************************************************/
static ZCL_Cluster_t otauCluster;
static ClusterId_t otauClusterId = OTAU_CLUSTER_ID;
static ZCL_OtauInitParams_t otauInitParams;
static ZCL_DeviceEndpoint_t otauClusterEndpoint;

/*******************************************************************************
                        Static functions section
*******************************************************************************/
static void otauClusterIndication(ZCL_OtauAction_t action);
#if (USE_IMAGE_SECURITY == 1) && defined(OTAU_CLIENT)
static void configureImageKeyDone(void);
#endif

/*******************************************************************************
                        Global functions section
*******************************************************************************/

/*******************************************************************************
                        Implementation section
*******************************************************************************/

/*******************************************************************************
  \brief ZCL Manager initialization

  \return none
*******************************************************************************/
void appZclManagerInit(void)
{
#if defined(OTAU_CLIENT)
  otauCluster = ZCL_GetOtauClientCluster();
#elif defined(OTAU_SERVER)
  otauCluster = ZCL_GetOtauServerCluster();
#endif

  // Prepare OTAU endpoint
  otauClusterEndpoint.simpleDescriptor.endpoint = APP_OTAU_CLUSTER_ENDPOINT;
  otauClusterEndpoint.simpleDescriptor.AppProfileId = PROFILE_ID_SMART_ENERGY;
  otauClusterEndpoint.simpleDescriptor.AppDeviceId = WSNDEMO_DEVICE_ID;
  otauClusterEndpoint.simpleDescriptor.AppInClustersCount = IN_CLUSTERS_COUNT;
  otauClusterEndpoint.simpleDescriptor.AppOutClustersCount = OUT_CLUSTERS_COUNT;
#if defined(OTAU_CLIENT)
  otauClusterEndpoint.simpleDescriptor.AppInClustersList = NULL;
  otauClusterEndpoint.simpleDescriptor.AppOutClustersList = &otauClusterId;
  otauClusterEndpoint.serverCluster = NULL;
  otauClusterEndpoint.clientCluster = &otauCluster;
#elif defined(OTAU_SERVER)
  otauClusterEndpoint.simpleDescriptor.AppInClustersList = &otauClusterId;
  otauClusterEndpoint.simpleDescriptor.AppOutClustersList = NULL;
  otauClusterEndpoint.serverCluster = &otauCluster;
  otauClusterEndpoint.clientCluster = NULL;
#endif
  ZCL_RegisterEndpoint(&otauClusterEndpoint);

  // Init OTAU
#if defined(OTAU_CLIENT)
  otauInitParams.clusterSide = ZCL_CLIENT_CLUSTER_TYPE;
  #if (USE_IMAGE_SECURITY == 1)
    ZCL_ConfigureOtauImageKey(configureImageKeyDone);
  #endif // USE_IMAGE_SECURITY
#elif defined(OTAU_SERVER)
  otauInitParams.clusterSide = ZCL_SERVER_CLUSTER_TYPE;
#endif
  otauInitParams.firmwareVersion.memAlloc = APP_OTAU_SOFTWARE_VERSION;
  otauInitParams.otauEndpoint = APP_OTAU_CLUSTER_ENDPOINT;
  otauInitParams.profileId = PROFILE_ID_SMART_ENERGY;
}

#if (USE_IMAGE_SECURITY == 1) && defined(OTAU_CLIENT)
/**************************************************************************//**
\brief Callback about confguring image key on EEPROM
******************************************************************************/
static void configureImageKeyDone(void)
{}
#endif

/*******************************************************************************
  \brief Activates ZCL OTAU component

  \return none
*******************************************************************************/
void runOtauService(void)
{
  if (ZCL_SUCCESS_STATUS != ZCL_StartOtauService(&otauInitParams, otauClusterIndication))
  {
    /* failed to start otau service. Check for param validity */
  }
}

/*******************************************************************************
  \brief Get indication about all otau cluster actions.
  
  \param[in] action - current action
  \return none
*******************************************************************************/
static void otauClusterIndication(ZCL_OtauAction_t action)
{
  if (OTAU_DEVICE_SHALL_CHANGE_IMAGE == action)  // client is ready to change image
    HAL_WarmReset();
}

#endif // APP_USE_OTAU == 1

// eof WSNZclManger.c
