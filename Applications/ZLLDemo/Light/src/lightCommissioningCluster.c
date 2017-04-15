/**************************************************************************//**
  \file lightCommissioningCluster.c

  \brief
    Light device Commissioning cluster implementation.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    07.07.11  A. Taradov - Created.
******************************************************************************/

#if APP_ZLL_DEVICE_TYPE >= APP_DEVICE_TYPE_ON_OFF_LIGHT

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zcl.h>
#include <zclParser.h>
#include <zclZllCommissioningCluster.h>
#include <commandManager.h>
//#include <zclZllIB.h>
#include <zllDemo.h>
#include <sysUtils.h>
#include <uartManager.h>

/******************************************************************************
                    Prototypes
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
\brief Initialize Commissioning cluster.
******************************************************************************/
void commissioningClusterInit(void)
{
  ZCL_Cluster_t *commissioningCluster = ZCL_GetCluster(APP_ENDPOINT_LIGHT,
                                                       ZLL_COMMISSIONING_CLUSTER_ID,
                                                       ZCL_CLUSTER_SIDE_SERVER);

  commissioningCluster->ZCL_DefaultRespInd = commandManagerDefaultResponseHandler;
}

/**************************************************************************//**
\brief Send Endpoint Information command to target device.

\param[in] addressing - target device addresing information.
******************************************************************************/
void sendEndpointInformation(ZCL_Addressing_t *addressing)
{
  CommandDescriptor_t *cmd;
  ZCL_EndpointInformation_t *endpointInformation;
  ExtAddr_t extAddr;

  if (!(cmd = clustersAllocCommand()))
    return;

  addressing->clusterId = ZLL_COMMISSIONING_CLUSTER_ID;

  cmd->clusterId = ZLL_COMMISSIONING_CLUSTER_ID;
  cmd->commandId = ZCL_COMMISSIONING_CLUSTER_ENDPOINT_INFORMATION_COMMAND_ID;
  cmd->disableDefaultResp = false;
  cmd->srcEndpoint = APP_ENDPOINT_LIGHT;

  endpointInformation = &cmd->payload.endpointInformation;
  memcpy(&extAddr, MAC_GetExtAddr(), sizeof(ExtAddr_t));
  endpointInformation->ieeeAddress = extAddr;
  endpointInformation->networkAddress = NWK_GetShortAddr();//zclZllIB.device.nwkAddr;
  endpointInformation->endpointId = APP_ENDPOINT_LIGHT;//zclZllIB.dit[0].ep;
  endpointInformation->profileId = APP_PROFILE_ID;
  endpointInformation->deviceId = APP_DEVICE_ID;
  endpointInformation->version = APP_VERSION;

  cmd->size = sizeof(cmd->payload.endpointInformation);

  clustersSendCommandWithAddressing(cmd, addressing);
}

/**************************************************************************//**
\brief Callback on receive of Get Group Identifiers command
******************************************************************************/
static ZCL_Status_t getGroupIdentifiersInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_GetGroupIdentifiers_t *payload)
{
  NWK_GroupTableEntry_t *group = NULL;
  uint8_t index, n;
  CommandDescriptor_t *cmd;
  ZCL_GetGroupIdentifiersResponse_t *getGroupIdentifiersResp;
  uint8_t size = sizeof(uint8_t) /*total*/ + sizeof(uint8_t) /*startIndex*/ + sizeof(uint8_t) /*count*/;
  LOG_STRING(getGroupIdentifiersIndStr, "getGroupIdentifiersInd()\r\n");

  appSnprintf(getGroupIdentifiersIndStr);

  if (!(cmd = clustersAllocCommand()))
    return ZCL_SUCCESS_STATUS;

  index = n = 0;
  getGroupIdentifiersResp = &cmd->payload.getGroupIdentifiersResp;

  group = NWK_NextGroup(group);
  while (NULL != group)
  {
    if (index >= payload->startIndex &&
        n < ARRAY_SIZE(getGroupIdentifiersResp->recordList))
    {
      getGroupIdentifiersResp->recordList[n].groupId = group->addr;
      getGroupIdentifiersResp->recordList[n].groupType = 0;
      n++;
      size += sizeof(ZCL_GroupInformationRecord_t);
    }
    group = NWK_NextGroup(group);
    index++;
  }

  cmd->clusterId = ZLL_COMMISSIONING_CLUSTER_ID;
  cmd->commandId = ZCL_COMMISSIONING_CLUSTER_GET_GROUP_IDENTIFIERS_RESPONSE_COMMAND_ID;
  cmd->srcEndpoint = APP_ENDPOINT_LIGHT;
  cmd->seqNumberSpecified = true;

  getGroupIdentifiersResp->total = index;
  getGroupIdentifiersResp->startIndex = payload->startIndex;
  getGroupIdentifiersResp->count = n;

  cmd->size = sizeof(cmd->payload.getGroupIdentifiersResp);

  clustersSendCommandWithAddressing(cmd, addressing);

  (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receive of Get Endpoint List command
******************************************************************************/
static ZCL_Status_t getEndpointListInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_GetEndpointList_t *payload)
{
  CommandDescriptor_t *cmd;
  ZCL_GetEndpointListResponse_t *getEndpointListResp;
  uint8_t size = sizeof(uint8_t) /*total*/ + sizeof(uint8_t) /*startIndex*/ + sizeof(uint8_t) /*count*/;
  LOG_STRING(getEndpointListIndStr, "getEndpointListInd()\r\n");

  appSnprintf(getEndpointListIndStr);

  if (!(cmd = clustersAllocCommand()))
    return ZCL_SUCCESS_STATUS;

  getEndpointListResp = &cmd->payload.getEndpointListResp;

  if (payload->startIndex == 0)
  {
    getEndpointListResp->recordList[0].networkAddress = NWK_GetShortAddr();//zclZllIB.device.nwkAddr;
    getEndpointListResp->recordList[0].endpointId = APP_ENDPOINT_LIGHT;//zclZllIB.dit[0].ep;
    getEndpointListResp->recordList[0].profileId = APP_PROFILE_ID;//zclZllIB.dit[0].profileId;
    getEndpointListResp->recordList[0].deviceId = APP_DEVICE_ID;//zclZllIB.dit[0].deviceId;
    getEndpointListResp->recordList[0].version = APP_VERSION;//zclZllIB.dit[0].version;

    size += sizeof(ZCL_EndpointInformationRecord_t);
    getEndpointListResp->count = 1;
  }
  else
  {
    getEndpointListResp->count = 0;
  }

  cmd->clusterId = ZLL_COMMISSIONING_CLUSTER_ID;
  cmd->commandId = ZCL_COMMISSIONING_CLUSTER_GET_ENDPOINT_LIST_RESPONSE_COMMAND_ID;
  cmd->srcEndpoint = APP_ENDPOINT_LIGHT;
  cmd->seqNumberSpecified = true;

  getEndpointListResp->total = 1;
  getEndpointListResp->startIndex = payload->startIndex;

  cmd->size = sizeof(cmd->payload.getEndpointListResp);

  clustersSendCommandWithAddressing(cmd, addressing);

  (void)payloadLength;
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

#endif // APP_ZLL_DEVICE_TYPE >= APP_DEVICE_TYPE_ON_OFF_LIGHT

// eof lightCommissioningCluster.c
