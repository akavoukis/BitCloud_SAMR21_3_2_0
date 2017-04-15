/**************************************************************************//**
  \file colorSceneRemoteCommissioningCluster.c

  \brief
    Color Scene Remote device Commissioning cluster implementation.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    07.07.11  A. Taradov - Created.
******************************************************************************/

#if APP_ZLL_DEVICE_TYPE == APP_DEVICE_TYPE_COLOR_SCENE_REMOTE

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zcl.h>
#include <zclParser.h>
#include <zclZllCommissioningCluster.h>
#include <commandManager.h>
#include <zllDemo.h>
#include <sysUtils.h>
#include <colorSceneRemoteLinkInfoCluster.h>
#include <uartManager.h>
#include <colorSceneRemoteClusters.h>

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
                    External variables section
******************************************************************************/
extern AppColorSceneRemoteAppData_t appData;

/******************************************************************************
                    Implementations section
******************************************************************************/
/**************************************************************************//**
\brief Send get group identifiers request command.

\param[in] addressing - target device addresing information.
******************************************************************************/
void colorSceneRemoteSendGroupIdentifiersReqCommand(uint8_t startIndx)
{
  CommandDescriptor_t *cmd;

  if (!(cmd = colorSceneRemoteGetFreeCommand()))
    return;

  colorSceneRemoteFillCommandRequest(cmd, ZCL_COMMISSIONING_CLUSTER_GET_GROUP_IDENTIFIERS_COMMAND_ID,
                                     ZLL_COMMISSIONING_CLUSTER_ID, sizeof(cmd->payload.getGroupIdentifiers));
  cmd->payload.getGroupIdentifiers.startIndex = startIndx;
  clustersSendCommand(cmd);
}

/**************************************************************************//**
\brief Send get endpoint list request command.

\param[in] addressing - target device addresing information.
******************************************************************************/
void colorSceneRemoteSendEndpointListReqCommand(uint8_t startIndx)
{
  CommandDescriptor_t *cmd;

  if (!(cmd = colorSceneRemoteGetFreeCommand()))
    return;

  colorSceneRemoteFillCommandRequest(cmd, ZCL_COMMISSIONING_CLUSTER_GET_ENDPOINT_LIST_COMMAND_ID,
                                     ZLL_COMMISSIONING_CLUSTER_ID, sizeof(cmd->payload.getEndpointList));
  cmd->payload.getEndpointList.startIndex = startIndx;
  clustersSendCommand(cmd);
}

/**************************************************************************//**
\brief Callback on receive of Get Group Identifiers command
******************************************************************************/
static ZCL_Status_t getGroupIdentifiersInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_GetGroupIdentifiers_t *payload)
{
  CommandDescriptor_t *cmd;
  uint8_t size, index, n;
  NWK_GroupTableEntry_t *group = NULL;

  if (!(cmd = clustersAllocCommand()))
    return ZCL_SUCCESS_STATUS;

  size = sizeof(uint8_t) /*total*/ + sizeof(uint8_t) /*startIndex*/ + sizeof(uint8_t) /*count*/;
  index = n = 0;

  group = NWK_NextGroup(group);
  while (NULL != group)
  {
    if ( (index >= payload->startIndex) &&
        (n < ARRAY_SIZE(cmd->payload.getGroupIdentifiersResp.recordList)) )
    {
      cmd->payload.getGroupIdentifiersResp.recordList[n].groupId = group->addr;
      cmd->payload.getGroupIdentifiersResp.recordList[n].groupType = 0;
      n++;
      size += sizeof(ZCL_GroupInformationRecord_t);
    }
    index++;
    group = NWK_NextGroup(group);
  }

  addressing->clusterSide = ZCL_CLUSTER_SIDE_CLIENT;

  cmd->clusterId = ZLL_COMMISSIONING_CLUSTER_ID;
  cmd->commandId = ZCL_COMMISSIONING_CLUSTER_GET_GROUP_IDENTIFIERS_RESPONSE_COMMAND_ID;
  cmd->payload.getGroupIdentifiersResp.total = index;
  cmd->payload.getGroupIdentifiersResp.startIndex = payload->startIndex;
  cmd->payload.getGroupIdentifiersResp.count = n;
  cmd->size = size;
  cmd->seqNumberSpecified = true;
  clustersSendCommandWithAddressing(cmd, addressing);

  (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receive of Get Endpoint List command
******************************************************************************/
static ZCL_Status_t getEndpointListInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_GetEndpointList_t *payload)
{
  uint8_t i;
  uint8_t n;
  CommandDescriptor_t *cmd;
  uint8_t size = sizeof(uint8_t) /*total*/ + sizeof(uint8_t) /*startIndex*/ + sizeof(uint8_t) /*count*/;

  if (!(cmd = clustersAllocCommand()))
    return ZCL_SUCCESS_STATUS;

  n = 0;
  cmd->payload.getEndpointListResp.count = 0;
  cmd->payload.getEndpointListResp.total = 0;
  cmd->payload.getEndpointListResp.startIndex = payload->startIndex;

  for (i = 0; i < ZCL_LINK_INFO_CLUSTER_CLIENT_SIDE_ATTRIBUTES_AMOUNT; i++)
  {
    BoundDevice_t *device = linkInfoGetAttrValue(i);
    if (0xFFFF != device->nwkAddr)
    {
      cmd->payload.getEndpointListResp.total++;

      if (payload->startIndex >= i)
      {
        cmd->payload.getEndpointListResp.recordList[n].networkAddress = device->nwkAddr;
        cmd->payload.getEndpointListResp.recordList[n].endpointId = device->endpoint;
        cmd->payload.getEndpointListResp.recordList[n].profileId = device->profileId;
        cmd->payload.getEndpointListResp.recordList[n].deviceId = device->deviceId;
        cmd->payload.getEndpointListResp.recordList[n].version = device->version;

        size += sizeof(ZCL_EndpointInformationRecord_t);
        cmd->payload.getEndpointListResp.count++;
        n++;
      }
    }
  }

  addressing->clusterSide = ZCL_CLUSTER_SIDE_CLIENT;

  cmd->clusterId = ZLL_COMMISSIONING_CLUSTER_ID;
  cmd->commandId = ZCL_COMMISSIONING_CLUSTER_GET_ENDPOINT_LIST_RESPONSE_COMMAND_ID;
  cmd->size = size;
  cmd->seqNumberSpecified = true;
  clustersSendCommandWithAddressing(cmd, addressing);

  (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receive of Endpoint Information command
******************************************************************************/
static ZCL_Status_t endpointInformationResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_EndpointInformation_t *payload)
{
  LOG_STRING(endpointInformationIndStr, "endpointInformationInd(): epId = 0x%02x\r\n");

  appSnprintf(endpointInformationIndStr, payload->endpointId);

  (void)addressing;
  (void)payloadLength;
  (void)payload;
  return ZCL_SUCCESS_WITH_DEFAULT_RESPONSE_STATUS;
}

/**************************************************************************//**
\brief Callback on receive of Get Group Identifiers Response command
******************************************************************************/
static ZCL_Status_t getGroupIdentifiersResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_GetGroupIdentifiersResponse_t *payload)
{
  LOG_STRING(getGroupIdentifiersRespStr, "getGroupIdentifiersResp()\r\n");
  LOG_STRING(getGroupIdentifiersRespTotalStr, "total = %d\r\n");
  LOG_STRING(getGroupIdentifiersRespGroupIdStr, "groupId = 0x%04x\r\n");

  appSnprintf(getGroupIdentifiersRespStr);
  appSnprintf(getGroupIdentifiersRespTotalStr, payload->total);

  for (uint8_t i =0; i < payload->count; i++)
    appSnprintf(getGroupIdentifiersRespGroupIdStr, payload->recordList[i].groupId);

  (void)addressing;
  (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receive of Get Endpoint List Response command
******************************************************************************/
static ZCL_Status_t getEndpointListResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_GetEndpointListResponse_t *payload)
{
  LOG_STRING(getEndpointListRespStr, "GetEndpointListResp()\r\n");

  appSnprintf(getEndpointListRespStr);
  (void)addressing;
  (void)payloadLength;
  (void)payload;
  return ZCL_SUCCESS_STATUS;
}

#endif // APP_ZLL_DEVICE_TYPE == APP_DEVICE_TYPE_COLOR_SCENE_REMOTE

// eof colorSceneRemoteCommissioningCluster.c
