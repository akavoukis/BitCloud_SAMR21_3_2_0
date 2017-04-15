/**************************************************************************//**
  \file identifyCluster.h

  \brief
    Identify cluster interface.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2013, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    10.09.13 N. Fomin - Created.
******************************************************************************/
#ifndef _IDENTIFYCLUSTER_H
#define _IDENTIFYCLUSTER_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <sysTypes.h>
#include <zclIdentifyCluster.h>

/******************************************************************************
                   Definition(s) section
******************************************************************************/
#define RAISE_CALLBACKS_TO_IDENTIFY_SUBSCIBERS(queue, callback) \
  for (IdentifySubscriber_t *subscriber = getQueueElem(&queue); subscriber; subscriber = getNextQueueElem(subscriber)) \
    if (subscriber->callback) \
      subscriber->callback(addressing, payload);

/******************************************************************************
                    Types section
******************************************************************************/
typedef struct
{
  struct
  {
    void *next;
  } service;

  void (*identify)(ZCL_Addressing_t *addressing, ZCL_Identify_t *payload);
  void (*identifyQuery)(ZCL_Addressing_t *addressing, uint8_t *payload);
  void (*identifyQueryResponse)(ZCL_Addressing_t *addressing, ZCL_IdentifyQueryResponse_t *payload);
  void (*ezModeInvoke)(ZCL_Addressing_t *addressing, ZCL_EzModeInvoke_t *payload);
  void (*updateCommissioningState)(ZCL_Addressing_t *addressing, ZCL_UpdateCommissioningState_t *payload);
} IdentifySubscriber_t;

/******************************************************************************
                    Prototypes section
******************************************************************************/
/**************************************************************************//**
\brief Initializes Identify cluster
******************************************************************************/
void identifyClusterInit(void);

/**************************************************************************//**
\brief Stops Identify cluster
******************************************************************************/
void identifyClusterStop(void);

/**************************************************************************//**
\brief Send Identify Query command unicastly

\param[in] nwkState         - new netwrok state;
\param[in] operationalState - new operational state
******************************************************************************/
void identifyUpdateCommissioningState(bool nwkState, bool operationalState);

/**************************************************************************//**
\brief Adds record to a list of subscribers

\param[in] subscriber - pointer to subscriber;
******************************************************************************/
void identifySubscribe(IdentifySubscriber_t *subscriber);

/**************************************************************************//**
\brief Sends Identify command

\param[in] mode - address mode;
\param[in] addr - short address of destination node;
\param[in] ep   - destination endpoint
******************************************************************************/
void identifySendIdentifyQuery(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep);

/**************************************************************************//**
\brief Sends Update Commissioning State command

\param[in] mode   - address mode;
\param[in] addr   - short address of destination node;
\param[in] ep     - destination endpoint;
\param[in] action - action to be done upon reception;
\param[in] mask   - commissiong state mask
******************************************************************************/
void identifySendUpdateCommissioningState(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep,
  ZCL_UpdateCommissioningStateAction_t action, uint8_t mask);

/**************************************************************************//**
\brief Makes device to start identify itself

\param[in] time - identifying time in seconds
******************************************************************************/
void idetifyStartIdentifying(uint16_t time);

/**************************************************************************//**
\brief Resets subscribers queue
******************************************************************************/
void idenityResetSubscribers(void);
#endif // _IDENTIFYCLUSTER_H

// eof identifyCluster.h

