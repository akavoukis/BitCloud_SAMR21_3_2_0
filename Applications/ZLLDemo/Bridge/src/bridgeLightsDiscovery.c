/**************************************************************************//**
  \file bridgeLightDiscovery.c

  \brief
    Control Bridge device lights discovery implementation.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2013, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    22.01.13 N. Fomin - Created.
******************************************************************************/

#if APP_ZLL_DEVICE_TYPE == APP_DEVICE_TYPE_BRIDGE

/******************************************************************************
                    Include section
******************************************************************************/
#include <bridgeLightsDiscovery.h>
#include <zdo.h>
#include <zcl.h>
#include <clusters.h>
#include <uartManager.h>
#include <zllDemo.h>

/******************************************************************************
                    Prototypes section
******************************************************************************/
static void zdpMatchDescResp(ZDO_ZdpResp_t *resp);

/******************************************************************************
                    Static variables section
******************************************************************************/
static ZDO_ZdpReq_t zdpReq;
static bool discoveryInProgress;

/******************************************************************************
                    Implementation section
******************************************************************************/
/**************************************************************************//**
\brief Performs lights discovery
******************************************************************************/
void discoverLights(void)
{
  ZDO_MatchDescReq_t *matchDescReq = &zdpReq.req.reqPayload.matchDescReq;
  
  if (discoveryInProgress)
    return;
  discoveryInProgress = true;

  zdpReq.ZDO_ZdpResp             = zdpMatchDescResp;
  zdpReq.reqCluster              = MATCH_DESCRIPTOR_CLID;
  zdpReq.dstAddrMode             = APS_SHORT_ADDRESS;
  zdpReq.dstAddress.shortAddress = RX_ON_WHEN_IDLE_ADDR;

  matchDescReq->nwkAddrOfInterest = RX_ON_WHEN_IDLE_ADDR;
  matchDescReq->profileId         = APP_PROFILE_ID;
  matchDescReq->numInClusters     = 1;
  matchDescReq->numOutClusters    = 0;
  matchDescReq->inClusterList[0]  = ZLL_COMMISSIONING_CLUSTER_ID;

  ZDO_ZdpReq(&zdpReq);
}

/**************************************************************************//**
\brief Response to match descriptor request

\param[in] resp - response parameters
*******************************************************************************/
static void zdpMatchDescResp(ZDO_ZdpResp_t *resp)
{
  ZDO_MatchDescResp_t *matchResp = &resp->respPayload.matchDescResp;
  ZDO_Status_t status = resp->respPayload.status;

  if (ZDO_CMD_COMPLETED_STATUS == status)
  {
    discoveryInProgress = false;
    LOG_STRING(discCompleteStr, "\r\nLights discovery is complete\r\n");
    appSnprintf(discCompleteStr);
  }
  else if (ZDO_SUCCESS_STATUS != status)
  {
    discoveryInProgress = false;
    LOG_STRING(discFailedStr, "\r\nLights discovery failed\r\n");
    appSnprintf(discFailedStr);
  }
  else
  { 
    if (matchResp->nwkAddrOfInterest == NWK_GetShortAddr())
      return;
    LOG_STRING(discoveredStr, "\r\nLight discovered: 0x%x 0x%02x");
    appSnprintf(discoveredStr, matchResp->nwkAddrOfInterest, matchResp->matchList[0]);
  }
  (void)matchResp;
}

#endif // APP_ZLL_DEVICE_TYPE == APP_DEVICE_TYPE_BRIDGE

// eof bridgeLightDiscovery.c