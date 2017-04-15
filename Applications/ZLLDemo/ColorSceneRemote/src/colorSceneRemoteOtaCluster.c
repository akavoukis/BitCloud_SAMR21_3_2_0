/**************************************************************************//**
  \file colorSceneRemoteOtaCluster.c

  \brief
    Color scene remote Over-the-air update cluster implementation.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    21.05.12 N. Fomin - Created.
    28.01.13 S. Dmitriev - Copied and modified
******************************************************************************/
#if APP_ZLL_DEVICE_TYPE == APP_DEVICE_TYPE_COLOR_SCENE_REMOTE

#if (APP_USE_OTAU == 1) && !defined OTAU_CLIENT
  #error "Please define correct OTAU role"
#endif

/******************************************************************************
                    Includes section
******************************************************************************/
#include <colorSceneRemoteOtaCluster.h>
#include <resetReason.h>
#include <ZLLDemo.h>

/******************************************************************************
                    Prototypes section
******************************************************************************/
#if APP_USE_OTAU == 1
static void otauClusterIndication(ZCL_OtauAction_t action);
#endif // APP_USE_OTAU == 1

/******************************************************************************
                    Implementation section
******************************************************************************/
/**************************************************************************//**
\brief Starts Over-the-air update client service.
******************************************************************************/
void startOtauClient(void)
{
#ifdef OTAU_CLIENT
  ZCL_OtauInitParams_t initParam;

  initParam.clusterSide = ZCL_CLIENT_CLUSTER_TYPE;
  initParam.firmwareVersion.memAlloc = SOFTWARE_VERSION;
  initParam.otauEndpoint = APP_ENDPOINT_COLOR_SCENE_REMOTE;
  initParam.profileId = APP_PROFILE_ID;
  if (ZCL_SUCCESS_STATUS != ZCL_StartOtauService(&initParam, otauClusterIndication) )
  {
    /* failed to start otau service. Check for param validity */
  }
#endif // OTAU_CLIENT
}

/**************************************************************************//**
\brief Stop Over-the-air update client service.
******************************************************************************/
void stopOtauClient(void)
{
#ifdef OTAU_CLIENT
  ZCL_OtauInitParams_t initParam;

  initParam.clusterSide = ZCL_CLIENT_CLUSTER_TYPE;
  initParam.firmwareVersion.memAlloc = SOFTWARE_VERSION;
  initParam.otauEndpoint = APP_ENDPOINT_COLOR_SCENE_REMOTE;
  initParam.profileId = APP_PROFILE_ID;
  if (ZCL_SUCCESS_STATUS != ZCL_StopOtauService(&initParam))
  {
    /* failed to stop otau service. Check for param validity */
  }
#endif // OTAU_CLIENT
}
/***************************************************************************//**
\brief Get indication about all otau cluster actions.

\param[in] action - current action
*******************************************************************************/
#if APP_USE_OTAU == 1
static void otauClusterIndication(ZCL_OtauAction_t action)
{
  switch (action)
  {
    case OTAU_DEVICE_SHALL_CHANGE_IMAGE:
      HAL_WarmReset();
      break;
    case OTAU_SERVER_DISCOVERY_INITIATED:
    case OTAU_UPGRADE_REQUEST_INITIATED:
    case OTAU_IMAGE_BLOCK_REQ_INITIATED:
    case OTAU_QUERY_NEXT_IMAGE_INITIATED:
      // Restart activity timer
      restartActivity();
      break;
    default:
      break;
  }
}
#endif // APP_USE_OTAU == 1
#endif // APP_ZLL_DEVICE_TYPE == APP_DEVICE_TYPE_COLOR_SCENE_REMOTE

// eof colorSceneRemoteOtaCluster.c
