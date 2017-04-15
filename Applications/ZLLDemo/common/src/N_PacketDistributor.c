/**************************************************************************//**
  \file N_PacketDistributor.c

  \brief
    N_PacketDistributor implementation.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    2808.2012 N.Fomin - Created
******************************************************************************/
/******************************************************************************
                    Includes section
******************************************************************************/
#include <N_PacketDistributor.h>
#include <N_ErrH.h>
#include <sysUtils.h>
#include <zclParser.h>
#include <N_DeviceInfo.h>

/******************************************************************************
                    Definitions section
******************************************************************************/
#define COMPID "N_PacketDistributor"

#ifndef MAX_ZCL_ENDPOINTS
  #define MAX_ZCL_ENDPOINTS  10u
#endif

#ifndef N_PACKET_DISTRIBUTER_MAX_SUBSCRIBERS
  #define N_PACKET_DISTRIBUTER_MAX_SUBSCRIBERS    (MAX_ZCL_ENDPOINTS + 2u)  // One extra for ZDP, one extra for InterPan
#endif

/******************************************************************************
                    Types section
******************************************************************************/

typedef struct N_PacketDistributor_Subscriber_t
{
    uint8_t endpoint;
    const IN_AfIncomingData_Callback_t* pCallback;
} N_PacketDistributor_Subscriber_t;

typedef struct N_PacketDistributor_Registration_t
{
    uint8_t endpoint;
    uint8_t groupCount;
} N_PacketDistributor_Registration_t;

/******************************************************************************
                    Static variables section
******************************************************************************/
static N_PacketDistributor_Subscriber_t s_N_PacketDistributor_Subscribers[N_PACKET_DISTRIBUTER_MAX_SUBSCRIBERS] = { {0u, NULL} };

/******************************************************************************
                    Implementation section
******************************************************************************/
/** Register a ZigBee end-point.
    \param pSimpleDescription Pointer to a filled structure describing
        the end-point. The memory must stay available after the call to
        this function
    \param groupCount The number of groups used by the the endpoint (see the note below)

    \note The groups count should include number of the groups that the endpoint uses as client of
        the ZCL groups cluster, NOT the number of groups used as server of the cluster: e.g. a
        remote control endpoint uses one group (groupCount == 1) to control some dimmable
        light endpoints (groupCount == 0).
*/
void N_PacketDistributor_RegisterEndpoint_Impl(ZLL_Endpoint_t* zllEp, uint8_t groupCount)
{
  zllEp->simpleDescriptor = &zllEp->deviceEndpoint.simpleDescriptor;
  zllEp->groupsAmount     = groupCount;

  zllEp->deviceEndpoint.service.apsEndpoint.simpleDescriptor = zllEp->simpleDescriptor;
  zllEp->deviceEndpoint.service.apsEndpoint.APS_DataInd      = zclDataInd;

  APS_RegisterEndpointReq(&zllEp->deviceEndpoint.service.apsEndpoint);
}

/** Returns the number of Zcl EndPoints (so excluding ZDO and InterPan endpoints)
*/
uint8_t N_PacketDistributor_GetNumberOfZclEndpoints_Impl(void)
{
  APS_RegisterEndpointReq_t *epReq = NULL;
  uint8_t epAmount = 0;

  epReq = APS_NextEndpoint(epReq);
  while(NULL != epReq)
  {
    epAmount++;
    epReq = APS_NextEndpoint(epReq);
  }
  return epAmount;
}

/** Returns the zcl endpoint number for an index (0..NumberOfZclEndpoints-1)
*/
uint8_t N_PacketDistributor_GetZclEndpointFromIndex_Impl(uint8_t index)
{
  APS_RegisterEndpointReq_t *epReq = NULL;
  uint8_t epAmount = 0;

  epReq = APS_NextEndpoint(epReq);
  while((NULL != epReq) && (epAmount < index))
  {
    epAmount++;
    epReq = APS_NextEndpoint(epReq);
  }
  if (NULL == epReq)
  {
    N_ERRH_FATAL();
    return 0;
  }
  return epReq->simpleDescriptor->endpoint;
}

/** Get the group count registered with \ref N_PacketDistributor_RegisterEndpoint.
    \param endpoint The endpoint number for which to get the group count
    \returns The group count
*/
uint8_t N_PacketDistributor_GetGroupCount_Impl(uint8_t endpoint)
{
  APS_RegisterEndpointReq_t *epReq = NULL;
  ZLL_Endpoint_t *zllEp;

  epReq = APS_NextEndpoint(epReq);
  while(NULL != epReq)
  {
    if (epReq->simpleDescriptor->endpoint == endpoint)
    {
      break;
    }    
    epReq = APS_NextEndpoint(epReq);
  }

  if (NULL == epReq)
  {
    N_ERRH_FATAL();
    return 0;
  }
  zllEp = GET_PARENT_BY_FIELD(ZLL_Endpoint_t, deviceEndpoint.service.apsEndpoint, epReq);
  return zllEp->groupsAmount;
}

/** Get the sum of the group counts registered with \ref N_PacketDistributor_RegisterEndpoint for all endpoints.
    \returns The total number of groups
*/
uint8_t N_PacketDistributor_GetTotalGroupCount_Impl(void)
{
  APS_RegisterEndpointReq_t *epReq = NULL;
  ZLL_Endpoint_t *zllEp;
  uint8_t totalCount = 0;

  epReq = APS_NextEndpoint(epReq);
  while(NULL != epReq)
  {
    zllEp = GET_PARENT_BY_FIELD(ZLL_Endpoint_t, deviceEndpoint.service.apsEndpoint, epReq);
    totalCount += zllEp->groupsAmount;
    epReq = APS_NextEndpoint(epReq);
  }
  return totalCount;
}

/** Returns the number of Zll EndPoints
*/
uint8_t N_PacketDistributor_GetNumberOfZllEndpoints_Impl(void)
{
  APS_RegisterEndpointReq_t *epReq = NULL;
  uint8_t epAmount = 0;

  epReq = APS_NextEndpoint(epReq);
  while(NULL != epReq)
  {
    epAmount++;
    epReq = APS_NextEndpoint(epReq);
  }
  return epAmount;
}

/** Get the sum of the group counts for zll endpoints.
    \returns The total number of groups
*/
uint8_t N_PacketDistributor_GetTotalGroupCountZll_Impl(void)
{
  APS_RegisterEndpointReq_t *epReq = NULL;
  ZLL_Endpoint_t *zllEp;
  uint8_t totalCount = 0;

  epReq = APS_NextEndpoint(epReq);
  while(NULL != epReq)
  {
    zllEp = GET_PARENT_BY_FIELD(ZLL_Endpoint_t, deviceEndpoint.service.apsEndpoint, epReq);
    totalCount += zllEp->groupsAmount;
    epReq = APS_NextEndpoint(epReq);
  }
  return totalCount;
}

/** Returns the zll endpoint number for an index (0..NumberOfZllEndpoints-1)
*/
uint8_t N_PacketDistributor_GetZllEndpointFromIndex_Impl(uint8_t index)
{
  APS_RegisterEndpointReq_t *epReq = NULL;
  uint8_t epAmount = 0;

  epReq = APS_NextEndpoint(epReq);
  while((NULL != epReq) && (epAmount < index))
  {
    epAmount++;
    epReq = APS_NextEndpoint(epReq);
  }

  if (NULL == epReq)
  {
    N_ERRH_FATAL();
    return 0;
  }
  return epReq->simpleDescriptor->endpoint;
}

/** Find a registered endpoint.
    \param endpoint Endpoint number
    \returns A pointer to the endpoint description or NULL if the endpoint could not be found.
             Do not free the memory
*/
ZLL_Endpoint_t* N_PacketDistributor_FindEndpoint_Impl(uint8_t endpoint)
{
  APS_RegisterEndpointReq_t *epReq = NULL;

  epReq = APS_NextEndpoint(epReq);
  while(NULL != epReq)
  {
    if (epReq->simpleDescriptor->endpoint == endpoint)
    {
      break;
    }
    epReq = APS_NextEndpoint(epReq);
  }
  
  if (NULL == epReq)
  {
    return NULL;
  }
  return GET_PARENT_BY_FIELD(ZLL_Endpoint_t, deviceEndpoint.service.apsEndpoint, epReq);
}

/** Interface function, see \ref IN_AfIncomingData_Subscribe */
void N_PacketDistributor_Subscribe_Impl(uint8_t endpoint, const IN_AfIncomingData_Callback_t* pCallback)
{
    N_ERRH_ASSERT_FATAL((pCallback               != NULL) &&
                      (pCallback->IncomingData != NULL) &&
                      (pCallback->endOfList    == -1  ) );

    for ( uint8_t i = 0u; i < N_PACKET_DISTRIBUTER_MAX_SUBSCRIBERS; i++ )
    {
        if ( s_N_PacketDistributor_Subscribers[i].pCallback == NULL )
        {
            // add subscription
            s_N_PacketDistributor_Subscribers[i].endpoint = endpoint;
            s_N_PacketDistributor_Subscribers[i].pCallback = pCallback;
            return;
        }
        else
        {
            // only one subscription per end-point allowed
            N_ERRH_ASSERT_FATAL(endpoint != s_N_PacketDistributor_Subscribers[i].endpoint);
        }
    }

    // maximum number of subscribers reached
    N_ERRH_FATAL();
}

