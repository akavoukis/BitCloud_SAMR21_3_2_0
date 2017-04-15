/**************************************************************************//**
  \file ciGroupsCluster.c

  \brief
    Combined Interface Groups cluster implementation.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2013, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    03.09.13 N. Fomin - Created.
******************************************************************************/
#ifdef APP_DEVICE_TYPE_COMBINED_INTERFACE

/******************************************************************************
                    Includes section
******************************************************************************/
#include <ciGroupsCluster.h>
#include <haClusters.h>
#include <zclOnOffCluster.h>
#include <zclLevelControlCluster.h>
#include <commandManager.h>
#include <uartManager.h>

/******************************************************************************
                    Prototypes section
******************************************************************************/
static ZCL_Status_t addGroupResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_AddGroupResponse_t *payload);
static ZCL_Status_t viewGroupResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ViewGroupResponse_t *payload);
static ZCL_Status_t getGroupMembershipResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_GetGroupMembershipResponse_t *payload);
static ZCL_Status_t removeGroupResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_RemoveGroupResponse_t *payload);

static void ciFillAddGroupIfIdentifyingPayload(ZCL_AddGroup_t *payload, uint16_t group);
static void ciFillViewRemoveGroupPayload(ZCL_ViewGroup_t *payload, uint16_t group);
static uint8_t ciFillGetGroupMembershipPayload(ZCL_GetGroupMembership_t *payload, uint8_t count, uint16_t *list);

/******************************************************************************
                    Global variables section
******************************************************************************/
ZCL_GroupsClusterCommands_t ciGroupsCommands =
{
  ZCL_DEFINE_GROUPS_CLUSTER_COMMANDS(NULL, NULL, NULL, NULL, NULL, NULL,
                                     addGroupResponseInd, viewGroupResponseInd,
                                     getGroupMembershipResponseInd, removeGroupResponseInd)
};

/******************************************************************************
                    Implementation section
******************************************************************************/
/**************************************************************************//**
\brief Initializes Groups cluster
******************************************************************************/
void groupsClusterInit(void)
{}

/**************************************************************************//**
\brief Sends Add Group command to bound devices

\param[in] mode  - address mode;
\param[in] addr  - short address of destination node or number of group;
\param[in] ep    - endpoint number of destination device;
\param[in] group - group id
******************************************************************************/
void groupsSendAddGroup(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep,
  uint16_t group)
{
  ZCL_Request_t *req;

  if (!(req = getFreeCommand()))
    return;

  fillCommandRequest(req, ZCL_GROUPS_CLUSTER_ADD_GROUP_COMMAND_ID, sizeof(ZCL_AddGroup_t) - sizeof(uint8_t));
  ciFillAddGroupIfIdentifyingPayload((ZCL_AddGroup_t *)req->requestPayload, group);
  fillDstAddressing(&req->dstAddressing, mode, addr, ep, GROUPS_CLUSTER_ID);
  commandManagerSendCommand(req);
}

/**************************************************************************//**
\brief Sends View Group command to bound devices

\param[in] mode  - address mode;
\param[in] addr  - short address of destination node or number of group;
\param[in] ep    - endpoint number of destination device;
\param[in] group - group id
******************************************************************************/
void groupsSendViewGroup(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep,
  uint16_t group)
{
  ZCL_Request_t *req;

  if (!(req = getFreeCommand()))
    return;

  fillCommandRequest(req, ZCL_GROUPS_CLUSTER_VIEW_GROUP_COMMAND_ID, sizeof(ZCL_ViewGroup_t));
  ciFillViewRemoveGroupPayload((ZCL_ViewGroup_t *)req->requestPayload, group);
  fillDstAddressing(&req->dstAddressing, mode, addr, ep, GROUPS_CLUSTER_ID);
  commandManagerSendCommand(req);
}

/**************************************************************************//**
\brief Sends Get Group Membership command to bound devices

\param[in] mode  - address mode;
\param[in] addr  - short address of destination node or number of group;
\param[in] ep    - endpoint number of destination device;
\param[in] count - group count;
\param[in] list  - group list;
******************************************************************************/
void groupsSendGetGroupMembership(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep,
  uint8_t count, uint16_t *list)
{
  ZCL_Request_t *req;
  uint8_t size;

  if (!(req = getFreeCommand()))
    return;

  size = ciFillGetGroupMembershipPayload((ZCL_GetGroupMembership_t *)req->requestPayload, count, list);
  fillCommandRequest(req, ZCL_GROUPS_CLUSTER_GET_GROUP_MEMBERSHIP_COMMAND_ID, size);
  fillDstAddressing(&req->dstAddressing, mode, addr, ep, GROUPS_CLUSTER_ID);
  commandManagerSendCommand(req);
}

/**************************************************************************//**
\brief Sends Remove Group command to bound devices

\param[in] mode  - address mode;
\param[in] addr  - short address of destination node or number of group;
\param[in] ep    - endpoint number of destination device;
\param[in] group - group id
******************************************************************************/
void groupsSendRemoveGroup(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep,
  uint16_t group)
{
  ZCL_Request_t *req;

  if (!(req = getFreeCommand()))
    return;

  fillCommandRequest(req, ZCL_GROUPS_CLUSTER_REMOVE_GROUP_COMMAND_ID, sizeof(ZCL_RemoveGroup_t));
  ciFillViewRemoveGroupPayload((ZCL_ViewGroup_t *)req->requestPayload, group);
  fillDstAddressing(&req->dstAddressing, mode, addr, ep, GROUPS_CLUSTER_ID);
  commandManagerSendCommand(req);
}

/**************************************************************************//**
\brief Sends Remove All Groups command to bound devices

\param[in] mode  - address mode;
\param[in] addr  - short address of destination node or number of group;
\param[in] ep    - endpoint number of destination device;
\param[in] group - group id
******************************************************************************/
void groupsSendRemoveAllGroups(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep)
{
  ZCL_Request_t *req;

  if (!(req = getFreeCommand()))
    return;

  fillCommandRequest(req, ZCL_GROUPS_CLUSTER_REMOVE_ALL_GROUPS_COMMAND_ID, 0);
  fillDstAddressing(&req->dstAddressing, mode, addr, ep, GROUPS_CLUSTER_ID);
  commandManagerSendCommand(req);
}

/**************************************************************************//**
\brief Sends Add Group If Identifying command to bound devices

\param[in] mode  - address mode;
\param[in] addr  - short address of destination node or number of group;
\param[in] ep    - endpoint number of destination device;
\param[in] group - group id
******************************************************************************/
void groupsSendAddGroupIfIdentifying(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep,
  uint16_t group)
{
  ZCL_Request_t *req;

  if (!(req = getFreeCommand()))
    return;

  fillCommandRequest(req, ZCL_GROUPS_CLUSTER_ADD_GROUP_IF_IDENTIFYING_COMMAND_ID, sizeof(ZCL_AddGroup_t) - sizeof(uint8_t));
  ciFillAddGroupIfIdentifyingPayload((ZCL_AddGroup_t *)req->requestPayload, group);
  fillDstAddressing(&req->dstAddressing, mode, addr, ep, GROUPS_CLUSTER_ID);
  commandManagerSendCommand(req);
}

/**************************************************************************//**
\brief Callback on receiving Add Group Response command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
static ZCL_Status_t addGroupResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_AddGroupResponse_t *payload)
{
  LOG_STRING(addGroupRespStr, "addGroupResponseInd()\r\n");

  appSnprintf(addGroupRespStr);
  (void)addressing, (void)payloadLength, (void)payload;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receiving View Group Response command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
static ZCL_Status_t viewGroupResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ViewGroupResponse_t *payload)
{
  LOG_STRING(respStr, "viewGroupResponse(): status = 0x%02x\r\n");
  LOG_STRING(groupStr, "groupId = 0x%04x\r\n");

  appSnprintf(respStr, payload->status);
  appSnprintf(groupStr, payload->groupId);

  (void)addressing, (void)payloadLength, (void)payload;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receiving Group Membership Response command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
static ZCL_Status_t getGroupMembershipResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_GetGroupMembershipResponse_t *payload)
{
  LOG_STRING(respStr, "getGroupMembershipResponse()\r\n");
  LOG_STRING(groupCountStr, "groupCount = %d\r\n");
  LOG_STRING(groupStr, "groupId = 0x%04x\r\n");

  appSnprintf(respStr);
  appSnprintf(groupCountStr, payload->groupCount);

  for (uint8_t i = 0; i < payload->groupCount; i++)
    appSnprintf(groupStr, payload->groupList[i]);

  (void)addressing, (void)payloadLength, (void)payload;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receiving Remove Group Response command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
static ZCL_Status_t removeGroupResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_RemoveGroupResponse_t *payload)
{
  LOG_STRING(removeGroupRespStr, "removeGroupResponseInd()\r\n");
  appSnprintf(removeGroupRespStr);

  (void)addressing, (void)payloadLength, (void)payload;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Fills Add Group and Add Group If Identifying command structure

\param[out] payload - pointer to command structure;
\param[in]  group   - group id
******************************************************************************/
static void ciFillAddGroupIfIdentifyingPayload(ZCL_AddGroup_t *payload, uint16_t group)
{
  payload->groupId      = group;
  payload->groupName[0] = 0;
}

/**************************************************************************//**
\brief Fills View Group and Remove Group command structure

\param[out] payload - pointer to command structure;
\param[in]  group   - group id
******************************************************************************/
static void ciFillViewRemoveGroupPayload(ZCL_ViewGroup_t *payload, uint16_t group)
{
  payload->groupId = group;
}

/**************************************************************************//**
\brief Fills Get Group Membership command structure

\param[out] payload - pointer to command structure;
\param[in]  group   - group id
******************************************************************************/
static uint8_t ciFillGetGroupMembershipPayload(ZCL_GetGroupMembership_t *payload, uint8_t count, uint16_t *list)
{
  payload->groupCount = count;

  if (!count)
    return sizeof(ZCL_GetGroupMembership_t) - sizeof(uint16_t); /*groupList[1]*/

  for (uint8_t i = 0; i < count; i++)
    payload->groupList[i] = list[i];

  return sizeof(ZCL_GetGroupMembership_t) - sizeof(uint16_t) /*groupList[1]*/ + count * sizeof(uint16_t);
}

#endif // APP_DEVICE_TYPE_COMBINED_INTERFACE
// eof ciGroupsCluster.c

