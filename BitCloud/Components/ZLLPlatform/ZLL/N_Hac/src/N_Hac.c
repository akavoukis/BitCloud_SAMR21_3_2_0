/**************************************************************************//**
  \file N_Hac.c

  \brief Implementation of Home Automation Profile converter

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    12.12.12 A. Razinkov - created
******************************************************************************/

/******************************************************************************
                    Includes section
******************************************************************************/
#include <N_Hac_Bindings.h>
#include <N_Hac.h>
#include <N_ErrH.h>

#include <N_PacketDistributor.h>

/******************************************************************************
                    Defines section
******************************************************************************/
#define COMPID "N_Hac"

#ifndef MAX_ZCL_ENDPOINTS
  #define MAX_ZCL_ENDPOINTS 10U
#endif /* MAX_ZCL_ENDPOINTS */

/******************************************************************************
                    Prototypes section
******************************************************************************/
static void nHacObserver(SYS_EventId_t eventId, SYS_EventData_t data);
static void nHacRegisterEndpoint(ZLL_Endpoint_t* zllEp);

/******************************************************************************
                    Static variables section
******************************************************************************/
static ZLL_Endpoint_t* zllEndpoints[MAX_ZCL_ENDPOINTS];
/* BitCloud events receiver */
static SYS_EventReceiver_t bcEventReceiver = { .func = nHacObserver};

static uint8_t freeEndpointCell = 0;

/******************************************************************************
                    Implementation section
******************************************************************************/
/** Register the end-point with the AF layer with the translation of the
    profile id from ZLL to HAP.
 */
void N_Hac_RegisterEndpoint_Impl(ZLL_Endpoint_t* zllEp, uint8_t groupCount)
{
  N_PacketDistributor_RegisterEndpoint(zllEp, groupCount);
  nHacRegisterEndpoint(zllEp);

  /* Subscribe to frames with unexpected ProfileId indication events */
  SYS_SubscribeToEvent(BC_EVENT_ACCESS_REQUEST, &bcEventReceiver);
}

/** Handle interception of frames with ProfileId different to destination endpoint
 *
 *  \param eventId Event ID
 *  \param data Data associated with event occured
 */
static void nHacObserver(SYS_EventId_t eventId, SYS_EventData_t data)
{
  if (BC_EVENT_ACCESS_REQUEST == eventId)
  {
    BcAccessReq_t *const accessReq = (BcAccessReq_t*)data;

    if (BC_FRAME_FILTERING_BY_PROFILE_ID_ACTION == accessReq->action)
    {
      APS_FrameFilteringByProfileIdContext_t *frameFilteringContext =
        (APS_FrameFilteringByProfileIdContext_t*)accessReq->context;
      ZLL_Endpoint_t *hacEndpoint;

      /* Deny reception by default */
      accessReq->denied = true;

      for (uint8_t i = 0; i < MAX_ZCL_ENDPOINTS; i++)
      {
        hacEndpoint = zllEndpoints[i];
        if (!hacEndpoint)
          return;

        /* Accept HAP frames to endpoints registered in N_Hac */
        if ((hacEndpoint->simpleDescriptor->endpoint ==
             frameFilteringContext->endpoint->simpleDescriptor->endpoint) &&
            ((PROFILE_ID_HOME_AUTOMATION == frameFilteringContext->profileId) ||
            (APS_WILDCARD_PROFILE_ID == frameFilteringContext->profileId)))
        {
          accessReq->denied = false;
          return;
        }
      }
    }
  }
}

static void nHacRegisterEndpoint(ZLL_Endpoint_t* zllEp)
{
  N_ERRH_ASSERT_FATAL(freeEndpointCell < MAX_ZCL_ENDPOINTS); // Not enough memory to register Endpoint

  zllEndpoints[freeEndpointCell++] = zllEp;
}

/* eof N_Hac.c */
