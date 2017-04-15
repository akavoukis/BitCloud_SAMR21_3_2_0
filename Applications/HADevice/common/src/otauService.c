/************************************************************************//**
  \file otauService.c

  \brief
    OTAU service implementation.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    06.12.13 N. Fomin - Created.
******************************************************************************/

/*******************************************************************************
                    Includes section
*******************************************************************************/
#include <otauService.h>
#include <zclOTAUCluster.h>
#include <resetReason.h>

/******************************************************************************
                    Prototypes section
******************************************************************************/
#ifdef OTAU_CLIENT
static void otauClusterIndication(ZCL_OtauAction_t action);
#endif // OTAU_CLIENT

/*******************************************************************************
                    Implementation section
*******************************************************************************/
/**************************************************************************//**
\brief Starts Over-the-air update server service.

\param[out] - pointer to otau cluster
******************************************************************************/
void startOtauServer(ZCL_Cluster_t *otauCluster)
{
#ifdef OTAU_SERVER
  ZCL_OtauInitParams_t initParam;

  *otauCluster = ZCL_GetOtauServerCluster();

  initParam.clusterSide = ZCL_SERVER_CLUSTER_TYPE;
  initParam.firmwareVersion.memAlloc = SOFTWARE_VERSION;
  initParam.otauEndpoint = APP_SRC_ENDPOINT_ID;
  initParam.profileId = APP_PROFILE_ID;
  if (ZCL_SUCCESS_STATUS != ZCL_StartOtauService(&initParam, NULL))
  {
    /* failed to start otau service. Check for param validity */
  }
#else
  (void)otauCluster;
#endif // OTAU_SERVER
}

/**************************************************************************//**
\brief Starts Over-the-air update client service.

\param[out] - pointer to otau cluster
******************************************************************************/
void startOtauClient(ZCL_Cluster_t *otauCluster)
{
#ifdef OTAU_CLIENT
  ZCL_OtauInitParams_t initParam;

  *otauCluster = ZCL_GetOtauClientCluster();

  initParam.clusterSide = ZCL_CLIENT_CLUSTER_TYPE;
  initParam.firmwareVersion.memAlloc = SOFTWARE_VERSION;
  initParam.otauEndpoint = APP_SRC_ENDPOINT_ID;
  initParam.profileId = APP_PROFILE_ID;
  if (ZCL_SUCCESS_STATUS != ZCL_StartOtauService(&initParam, otauClusterIndication))
  {
    /* failed to start otau service. Check for param validity */
  }
#else
  (void)otauCluster;  
#endif // OTAU_CLIENT
}

/***************************************************************************//**
\brief Get indication about all otau cluster actions.

\param[in] action - current action
*******************************************************************************/
#ifdef OTAU_CLIENT
static void otauClusterIndication(ZCL_OtauAction_t action)
{
  if (OTAU_DEVICE_SHALL_CHANGE_IMAGE == action) // client is ready to change image
    HAL_WarmReset();
}
#endif // OTAU_CLIENT

// eof otauService.c
