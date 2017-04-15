/**************************************************************************//**
  \file bridgeCommissioningCluster.c

  \brief
    Control Bridge device Commissioning cluster implementation.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    22.01.13  N. Fomin - Created.
******************************************************************************/

#if APP_ZLL_DEVICE_TYPE == APP_DEVICE_TYPE_BRIDGE

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zcl.h>
#include <zclZllCommissioningCluster.h>

/******************************************************************************
                    Prototypes section
******************************************************************************/
static ZCL_Status_t getGroupIdentifiersInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_GetGroupIdentifiers_t *payload);
static ZCL_Status_t getEndpointListInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_GetEndpointList_t *payload);
static ZCL_Status_t endpointInformationResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_EndpointInformation_t *payload);
static ZCL_Status_t getGroupIdentifiersResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_GetGroupIdentifiersResponse_t *payload);
static ZCL_Status_t getEndpointListResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_GetEndpointListResponse_t *payload);

/******************************************************************************
                    Global variables
******************************************************************************/
ZCL_CommissioningClusterCommands_t commissioningClusterCommands =
{
  ZCL_DEFINE_COMMISSIONING_CLUSTER_COMMANDS(getGroupIdentifiersInd, getEndpointListInd,
      endpointInformationResponseInd, getGroupIdentifiersResponseInd, getEndpointListResponseInd)
};

/******************************************************************************
                    Implementations section
******************************************************************************/
/**************************************************************************//**
\brief Callback on receive of Get Group Identifiers command
******************************************************************************/
static ZCL_Status_t getGroupIdentifiersInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_GetGroupIdentifiers_t *payload)
{
  (void)addressing;
  (void)payloadLength;
  (void)payload;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receive of Get Endpoint List command
******************************************************************************/
static ZCL_Status_t getEndpointListInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_GetEndpointList_t *payload)
{
  (void)addressing;
  (void)payloadLength;
  (void)payload;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receive of Endpoint Information command
******************************************************************************/
static ZCL_Status_t endpointInformationResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_EndpointInformation_t *payload)
{
  (void)addressing;
  (void)payloadLength;
  (void)payload;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receive of Get Group Identifiers Response command
******************************************************************************/
static ZCL_Status_t getGroupIdentifiersResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_GetGroupIdentifiersResponse_t *payload)
{
  (void)addressing;
  (void)payloadLength;
  (void)payload;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receive of Get Endpoint List Response command
******************************************************************************/
static ZCL_Status_t getEndpointListResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_GetEndpointListResponse_t *payload)
{
  (void)addressing;
  (void)payloadLength;
  (void)payload;
  return ZCL_SUCCESS_STATUS;
}

#endif // APP_ZLL_DEVICE_TYPE == APP_DEVICE_TYPE_BRIDGE

// eof bridgeCommissioningCluster.c
