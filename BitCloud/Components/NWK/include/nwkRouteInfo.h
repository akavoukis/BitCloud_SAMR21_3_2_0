/**************************************************************************//**
  \file nwkRouteInfo.h

  \brief Public route information.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
   History:
    2010-05-07 Max Gekk - Created.
   Last change:
    $Id: nwkRouteInfo.h 27584 2015-01-09 14:45:42Z unithra.c $
 ******************************************************************************/
#if !defined _NWK_ROUTE_INFO_H
#define _NWK_ROUTE_INFO_H

/******************************************************************************
                               Includes section
 ******************************************************************************/
#include <appFramework.h>

/******************************************************************************
                              Definitions section
 ******************************************************************************/
/* Invalid concentrator descriptor. */
#define NWK_INVALID_CONCENTRATOR (UINT16_MAX)
/* Macro return true if concentrator descriptor is valid. */
#define IS_VALID_CONCENTRATOR(descr) (NWK_INVALID_CONCENTRATOR != (descr))

/******************************************************************************
                                Types section
 ******************************************************************************/
/* Type of concentrator descriptor. */
typedef uint16_t NWK_Concentrator_t;

/* Type of concentrator indication structure.
   Deprecated. Use generic subscription to event BC_EVENT_NEW_CONCENTRATOR instead. */
typedef struct _NWK_ConcentratorInd_t
{
  /** Service fields - for internal needs (event receiver for compatibility with new event system). */
  SYS_EventService_t service;
  /* This function is called when new concentrator is found.
     New argument 'id' was added as a transition to generic event system.
     Please update you software and ignore this argument for a moment. */
  void (* NWK_ConcentratorInd)(SYS_EventId_t id, SYS_EventData_t data);
} NWK_ConcentratorInd_t;

/******************************************************************************
                              Prototypes section
 ******************************************************************************/
/**************************************************************************//**
  \brief This function return the 16-bit network address of the next hop on
     the way to the destination.

  \return The network address of the next hop.
 ******************************************************************************/
ShortAddr_t NWK_GetNextHop(ShortAddr_t dstAddr);

/**************************************************************************//**
  \brief Get descriptor of next concentrator.

  Example:
    NWK_Concentrator_t c = NWK_INVALID_CONCENTRATOR;

    while (IS_VALID_CONCENTRATOR(c = NWK_NextConcentrator(c)))
    {
      cAddr = NWK_ShortAddrOfConcentrator(c);
      if (MASTER_CONCENTRATOR_ADDR == cAddr)
        ...
      ...
    }

  \param[in] prevConcentrator - descriptor of previous concentrator or
    NWK_INVALID_CONCENTRATOR if it's initial call.

  \return if next concentrator is found then return valid descriptor otherwise
    return NWK_INVALID_CONCENTRATOR.
 ******************************************************************************/
NWK_Concentrator_t NWK_NextConcentrator(const NWK_Concentrator_t prevConcentrator);

/**************************************************************************//**
  \brief Get short address of given concentrator.

    Note: Call this function and NWK_NextConcentrator() in same task.

  \param[in] concentrator - descriptor of concentrator (see NWK_NextConcentrator).
  \return Short address of concentrator.
 ******************************************************************************/
ShortAddr_t NWK_ShortAddrOfConcentrator(const NWK_Concentrator_t concentrator);

/**************************************************************************//**
  \brief Get short address of next hop node for given concentrator.

    Note: Call this function and NWK_NextConcentrator() in same task.

  \param[in] concentrator - descriptor of concentrator (see NWK_NextConcentrator).
  \return Short address of next hop.
 ******************************************************************************/
ShortAddr_t NWK_NextHopToConcentrator(const NWK_Concentrator_t concentrator);

/**************************************************************************//**
  \brief Subscribe to indication about new concentrators.

  Deprecated. Subscribe to generic BC_EVENT_NEW_CONCENTRATOR instead.

  \param[in] ind - pointer to concentrator indication structure.
  \return None.
 ******************************************************************************/
/*DEPRECATED*/ void NWK_SubscribeToConcentratorInfo(NWK_ConcentratorInd_t *const ind);

/**************************************************************************//**
  \brief Unsubscribe from indication about new concentrators.

  Deprecated. Unsubscribe from generic BC_EVENT_NEW_CONCENTRATOR instead.

  \param[in] ind - pointer to concentrator indication structure.
  \return None.
 ******************************************************************************/
/*DEPRECATED*/ void NWK_UnsubscribeFromConcentratorInfo(NWK_ConcentratorInd_t *const ind);

#if defined _CUSTOM_4_SECURITY_MODE_
/**************************************************************************//**
  \brief Add a known concentrator information.

  \param[in] shortAddr - short address of the concentrator.
  \param[in] nextHopAddr - next hop address on a rote to the concentrator.
  \param[in] noRouteCache - noRouteCahce flag of the concentrator.
  \return None.
 ******************************************************************************/
void NWK_AddConcentrator(const ShortAddr_t shortAddr, const ShortAddr_t nextHopAddr,
  const bool noRouteCache);
#endif /* _CUSTOM_4_SECURITY_MODE_ */

#endif /* _NWK_ROUTE_INFO_H */
/** eof nwkRouteInfo.h */

