/**************************************************************************//**
  \file bridgeOtaCluster.c

  \brief
    Bridge Over-the-air update cluster implementation.

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
#if APP_ZLL_DEVICE_TYPE == APP_DEVICE_TYPE_BRIDGE

#if (APP_USE_OTAU == 1) && !defined OTAU_SERVER
  #error "Please define correct OTAU role"
#endif

/******************************************************************************
                    Includes section
******************************************************************************/
#include <bridgeOtaCluster.h>
#include <resetReason.h>
#include <ZLLDemo.h>

/******************************************************************************
                    Implementation section
******************************************************************************/
/**************************************************************************//**
\brief Starts Over-the-air update server service.
******************************************************************************/
void startOtauServer(void)
{
#ifdef OTAU_SERVER
  ZCL_OtauInitParams_t initParam;

  initParam.clusterSide = ZCL_SERVER_CLUSTER_TYPE;
  initParam.firmwareVersion.memAlloc = SOFTWARE_VERSION;
  initParam.otauEndpoint = APP_ENDPOINT_BRIDGE;
  initParam.profileId = APP_PROFILE_ID;
  if (ZCL_SUCCESS_STATUS != ZCL_StartOtauService(&initParam, NULL))
  {
    /* failed to start otau service. Check for param validity */
  }
#endif //
}

/**************************************************************************//**
\brief Starts Over-the-air update client service.
******************************************************************************/
void startOtauClient(void)
{}

#endif // APP_ZLL_DEVICE_TYPE == APP_DEVICE_TYPE_BRIDGE

// eof bridgeOtaCluster.c
