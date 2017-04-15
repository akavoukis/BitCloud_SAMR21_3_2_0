/**************************************************************************//**
  \file thGroupsCluster.c

  \brief
    Thermostat Groups server cluster implementation.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    21.11.14 Viswanadham Kotla - Created.
******************************************************************************/
#ifdef APP_DEVICE_TYPE_THERMOSTAT

/******************************************************************************
                    Includes section
******************************************************************************/
#include <thGroupsCluster.h>
#include <thIdentifyCluster.h>
#include <thScenesCluster.h>
#include <haClusters.h>
#include <uartManager.h>
#include <commandManager.h>
#include <thScenes.h>
#include <pdsDataServer.h>

/******************************************************************************
                    Prototypes section
******************************************************************************/
static ZCL_Status_t addGroupInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_AddGroup_t *payload);
static ZCL_Status_t viewGroupInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ViewGroup_t *payload);
static ZCL_Status_t getGroupMembershipInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_GetGroupMembership_t *payload);
static ZCL_Status_t removeGroupInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_RemoveGroup_t *payload);
static ZCL_Status_t removeAllGroupsInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, void *payload);
static ZCL_Status_t addGroupIfidentifyingInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_AddGroupIfIdentifying_t * payload);

static void thFillAddGroupResponsePayload(ZCL_AddGroupResponse_t *payload, uint16_t group, uint8_t status);
static void thFillViewGroupResponsePayload(ZCL_ViewGroupResponse_t *payload, uint16_t group);
static uint8_t thFillGetGroupMembershipPayload(ZCL_GetGroupMembershipResponse_t *payload, ZCL_GetGroupMembership_t *req);
static void thFillRemoveGroupResponsePayload(ZCL_RemoveGroupResponse_t *payload, uint16_t group, uint8_t status);

static ZCL_Status_t addGroup(uint16_t group);
static ZCL_Status_t removeGroup(uint16_t group);
static void removeAllGroups(void);
static void addGroupIfIdentifying(uint16_t group);

/******************************************************************************
                    Global variables section
******************************************************************************/
ZCL_GroupsClusterServerAttributes_t thGroupsClusterServerAttributes =
{
  ZCL_DEFINE_GROUPS_CLUSTER_SERVER_ATTRIBUTES()
};
ZCL_GroupsClusterCommands_t         thGroupsCommands =
{
  ZCL_DEFINE_GROUPS_CLUSTER_COMMANDS(addGroupInd, viewGroupInd, getGroupMembershipInd,
                                     removeGroupInd, removeAllGroupsInd, addGroupIfidentifyingInd,
                                     NULL, NULL, NULL, NULL)
};

/******************************************************************************
                    Implementation section
******************************************************************************/
/**************************************************************************//**
\brief Initializes Groups cluster
******************************************************************************/
void groupsClusterInit(void)
{
  thGroupsClusterServerAttributes.nameSupport.value = 0;
}

/**************************************************************************//**
\brief Callback on receiving Add Group command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
static ZCL_Status_t addGroupInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_AddGroup_t *payload)
{
  ZCL_Request_t *req;
  uint8_t status;

  LOG_STRING(addGroupStr, "addGroupInd(): 0x%04x\r\n");
  appSnprintf(addGroupStr, payload->groupId);

  status = addGroup(payload->groupId);

  // If received via multicast or broadcast service no response shall be given
  if (addressing->nonUnicast)
    return ZCL_SUCCESS_STATUS;

  if (!(req = getFreeCommand()))
    return ZCL_INSUFFICIENT_SPACE_STATUS;

  fillCommandRequest(req, ZCL_GROUPS_CLUSTER_ADD_GROUP_RESPONSE_COMMAND_ID,
                       sizeof(ZCL_AddGroupResponse_t));
  thFillAddGroupResponsePayload((ZCL_AddGroupResponse_t *)req->requestPayload, payload->groupId, status);
  fillDstAddressingViaSourceAddressing(&req->dstAddressing, addressing, ZCL_CLUSTER_SIDE_CLIENT);
  commandManagerSendCommand(req);

  (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receiving View Group command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
static ZCL_Status_t viewGroupInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ViewGroup_t *payload)
{
  ZCL_Request_t *req;

  LOG_STRING(viewGroupStr, "viewGroupInd(): 0x%04x\r\n");
  appSnprintf(viewGroupStr, payload->groupId);

  // If received via multicast or broadcast service no response shall be given
  if (addressing->nonUnicast)
    return ZCL_SUCCESS_STATUS;

  if (!(req = getFreeCommand()))
    return ZCL_INSUFFICIENT_SPACE_STATUS;

  fillCommandRequest(req, ZCL_GROUPS_CLUSTER_VIEW_GROUP_RESPONSE_COMMAND_ID,
                       sizeof(ZCL_ViewGroupResponse_t));
  thFillViewGroupResponsePayload((ZCL_ViewGroupResponse_t *)req->requestPayload, payload->groupId);
  fillDstAddressingViaSourceAddressing(&req->dstAddressing, addressing, ZCL_CLUSTER_SIDE_CLIENT);
  commandManagerSendCommand(req);

  (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receiving Get Group Membership command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
static ZCL_Status_t getGroupMembershipInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_GetGroupMembership_t *payload)
{
  ZCL_Request_t *req;
  uint8_t size;

  LOG_STRING(getGroupMembershipStr, "getGroupMembershipInd()\r\n");
  appSnprintf(getGroupMembershipStr);

  // If received via multicast or broadcast service no response shall be given
  if (addressing->nonUnicast)
    return ZCL_SUCCESS_STATUS;

  if (!(req = getFreeCommand()))
    return ZCL_INSUFFICIENT_SPACE_STATUS;

  size = thFillGetGroupMembershipPayload((ZCL_GetGroupMembershipResponse_t *)req->requestPayload, payload);
  fillCommandRequest(req, ZCL_GROUPS_CLUSTER_GET_GROUP_MEMBERSHIP_RESPONSE_COMMAND_ID, size);
  fillDstAddressingViaSourceAddressing(&req->dstAddressing, addressing, ZCL_CLUSTER_SIDE_CLIENT);
  commandManagerSendCommand(req);

  (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receiving Remove Group command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
static ZCL_Status_t removeGroupInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_RemoveGroup_t *payload)
{
  ZCL_Request_t *req;
  uint8_t status;

  LOG_STRING(removeGroupStr, "removeGroupInd(): 0x%04x\r\n");
  appSnprintf(removeGroupStr, payload->groupId);

  status = removeGroup(payload->groupId);

  // If received via multicast or broadcast service no response shall be given
  if (addressing->nonUnicast)
    return ZCL_SUCCESS_STATUS;

  if (!(req = getFreeCommand()))
    return ZCL_INSUFFICIENT_SPACE_STATUS;

  fillCommandRequest(req, ZCL_GROUPS_CLUSTER_REMOVE_GROUP_RESPONSE_COMMAND_ID,
                       sizeof(ZCL_RemoveGroupResponse_t));
  thFillRemoveGroupResponsePayload((ZCL_RemoveGroupResponse_t *)req->requestPayload, payload->groupId, status);
  fillDstAddressingViaSourceAddressing(&req->dstAddressing, addressing, ZCL_CLUSTER_SIDE_CLIENT);
  commandManagerSendCommand(req);

  (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receiving Remove All Groups command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
static ZCL_Status_t removeAllGroupsInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, void *payload)
{
  LOG_STRING(removeAllGroupsStr, "removeAllGroupsInd()\r\n");
  appSnprintf(removeAllGroupsStr);

  removeAllGroups();

  (void)addressing, (void)payloadLength, (void)payload;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receiving Add Group If Identifying command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
static ZCL_Status_t addGroupIfidentifyingInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_AddGroupIfIdentifying_t * payload)
{
  LOG_STRING(addGroupIfIdentifyingStr, "addGroupIfIdentifyingInd(): 0x%04x\r\n");
  appSnprintf(addGroupIfIdentifyingStr, payload->groupId);

  addGroupIfIdentifying(payload->groupId);

  (void)addressing, (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Fills Add Group Response command structure

\param[out] payload - pointer to command structure;
\param[in]  group   - group id;
\param[in]  status  - status of group adding
******************************************************************************/
static void thFillAddGroupResponsePayload(ZCL_AddGroupResponse_t *payload, uint16_t group, uint8_t status)
{
  payload->status  = status;
  payload->groupId = group;
}

/**************************************************************************//**
\brief Fills View Group Response command structure

\param[out] payload - pointer to command structure;
\param[in]  group   - group id
******************************************************************************/
static void thFillViewGroupResponsePayload(ZCL_ViewGroupResponse_t *payload, uint16_t group)
{
  if (NWK_IsGroupMember(group, APP_SRC_ENDPOINT_ID))
    payload->status = ZCL_SUCCESS_STATUS;
  else
    payload->status = ZCL_NOT_FOUND_STATUS;
  payload->groupId = group;
}

/**************************************************************************//**
\brief Fills Get Group Membership Response command structure

\param[out] payload - pointer to command structure;
\param[in]  req     - pointer to appropriate request

\returns the amount of group ids in reponse
******************************************************************************/
static uint8_t thFillGetGroupMembershipPayload(ZCL_GetGroupMembershipResponse_t *payload, ZCL_GetGroupMembership_t *req)
{
  payload->capacity   = NWK_GroupCapacity();
  payload->groupCount = 0;

  if (req->groupCount)
    for (uint8_t i = 0; i < req->groupCount; i++)
    {
      if (NWK_IsGroupMember(req->groupList[i], APP_SRC_ENDPOINT_ID))
        payload->groupList[payload->groupCount++] = req->groupList[i];
    }
  else
  {
    NWK_GroupTableEntry_t *group = NULL;

    while ((group = NWK_NextGroup(group)))
      payload->groupList[payload->groupCount++] = group->addr;
  }

  return sizeof(ZCL_GetGroupMembershipResponse_t) + sizeof(uint16_t) * payload->groupCount - sizeof(uint16_t);
}

/**************************************************************************//**
\brief Fills Remove Group Response command structure

\param[out] payload - pointer to command structure;
\param[in]  group   - group id;
\param[in]  status  - status of group adding
******************************************************************************/
static void thFillRemoveGroupResponsePayload(ZCL_RemoveGroupResponse_t *payload, uint16_t group, uint8_t status)
{
  payload->status  = status;
  payload->groupId = group;
}

/**************************************************************************//**
\brief Adds group to group table

\param[in] group - group id

\returns status of group adding
******************************************************************************/
static ZCL_Status_t addGroup(uint16_t group)
{
  if (!NWK_IsGroupMember(group, APP_SRC_ENDPOINT_ID))
  {
    if (NWK_AddGroup(group, APP_SRC_ENDPOINT_ID))
      return ZCL_SUCCESS_STATUS;
    else
      return ZCL_INSUFFICIENT_SPACE_STATUS;
  }

  return ZCL_DUPLICATE_EXISTS_STATUS;
}

/**************************************************************************//**
\brief Removes group from group table

\param[in] group - group id

\returns status of group removing
******************************************************************************/
static ZCL_Status_t removeGroup(uint16_t group)
{
  if (NWK_RemoveGroup(group, APP_SRC_ENDPOINT_ID))
  {
    removeScenesByGroup(group);
    PDS_Store(APP_TH_SCENES_MEM_ID);
    return ZCL_SUCCESS_STATUS;
  }
  else
    return ZCL_NOT_FOUND_STATUS;
}

/**************************************************************************//**
\brief Removes all groups from group table
******************************************************************************/
static void removeAllGroups(void)
{
  NWK_GroupTableEntry_t *group = NULL;

  while (NULL != (group = NWK_NextGroup(group)))
    removeScenesByGroup(group->addr);

  NWK_RemoveAllGroups(APP_SRC_ENDPOINT_ID);
  PDS_Store(APP_TH_SCENES_MEM_ID);
}

/**************************************************************************//**
\brief Adds group to group table if device is in identifying state

\param[in] group - group id
******************************************************************************/
static void addGroupIfIdentifying(uint16_t group)
{
  if (identifyIsIdentifying())
    if (!NWK_IsGroupMember(group, APP_SRC_ENDPOINT_ID))
      NWK_AddGroup(group, APP_SRC_ENDPOINT_ID);
}

#endif // APP_DEVICE_TYPE_THERMOSTAT
// eof thGroupsCluster.c

