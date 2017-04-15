/**************************************************************************//**
  \file lightGroupsCluster.c

  \brief
    Light device Groups cluster implementation.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    28.06.11 A. Taradov - Created.
******************************************************************************/

#if APP_ZLL_DEVICE_TYPE >= APP_DEVICE_TYPE_ON_OFF_LIGHT

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zcl.h>
#include <debug.h>
#include <commandManager.h>
#include <zclZllGroupsCluster.h>
#include <lightGroupsCluster.h>
#include <lightScenesCluster.h>
#include <lightIdentifyCluster.h>
#include <pdsDataServer.h>
#include <lightCommissioningCluster.h>
#include <zllDemo.h>

/******************************************************************************
                    Prototypes section
******************************************************************************/
static ZCL_Status_t addGroupInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_AddGroup_t *payload);
static void addGroupResponseResp(ZCL_Notify_t *ntfy);

static ZCL_Status_t viewGroupInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ViewGroup_t *payload);
static ZCL_Status_t getGroupMembershipInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_GetGroupMembership_t *payload);
static ZCL_Status_t removeGroupInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_RemoveGroup_t *payload);
static ZCL_Status_t removeAllGroupsInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, void *payload);
static ZCL_Status_t addGroupIfIdentifyingInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_AddGroupIfIdentifying_t *payload);

/******************************************************************************
                    Global variables
******************************************************************************/
ZCL_GroupsClusterCommands_t groupsClusterServerCommands =
{
  ZCL_DEFINE_GROUPS_CLUSTER_COMMANDS(addGroupInd, viewGroupInd,
      getGroupMembershipInd, removeGroupInd, removeAllGroupsInd,
      addGroupIfIdentifyingInd, NULL, NULL, NULL, NULL)
};

ZCL_GroupsClusterServerAttributes_t groupsClusterServerAttributes =
{
  ZCL_DEFINE_GROUPS_CLUSTER_SERVER_ATTRIBUTES()
};

/******************************************************************************
                    Implementations section
******************************************************************************/

/**************************************************************************//**
\brief Initialize Groups cluster.
******************************************************************************/
void groupsClusterInit(void)
{
  groupsClusterServerAttributes.nameSupport.value = 0;
}

/**************************************************************************//**
\brief Add Group indication
******************************************************************************/
static ZCL_Status_t addGroupInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_AddGroup_t *payload)
{
  ZCL_Status_t status;
  CommandDescriptor_t *cmd;
  ZCL_AddGroupResponse_t *addGroupResp;
  LOG_STRING(addGroupIdStr, "addGroupInd(): 0x%04x\r\n");

  appSnprintf(addGroupIdStr, payload->groupId);

  if (!NWK_IsGroupMember(payload->groupId, APP_ENDPOINT_LIGHT))
  {
    if (NWK_AddGroup(payload->groupId, APP_ENDPOINT_LIGHT))
      status = ZCL_SUCCESS_STATUS;
    else
      status = ZCL_INSUFFICIENT_SPACE_STATUS;
  }
  else
  {
    status = ZCL_DUPLICATE_EXISTS_STATUS;
  }

  // If received via multicast or broadcast service no response shall be given
  if (addressing->nonUnicast)
    return ZCL_SUCCESS_STATUS;

  if (!(cmd = clustersAllocCommand()))
    return ZCL_SUCCESS_STATUS;

  cmd->clusterId = GROUPS_CLUSTER_ID;
  cmd->commandId = ZCL_GROUPS_CLUSTER_ADD_GROUP_RESPONSE_COMMAND_ID;
  cmd->ZCL_Notify = addGroupResponseResp;
  cmd->srcEndpoint = APP_ENDPOINT_LIGHT;
  cmd->seqNumberSpecified = true;

  addGroupResp = &cmd->payload.addGroupResp;
  addGroupResp->status = status;
  addGroupResp->groupId = payload->groupId;

  cmd->size = sizeof(cmd->payload.addGroupResp);

  clustersSendCommandWithAddressing(cmd, addressing);

  (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief ZCL Add Group Response command response
\param[in] ntfy - response parameters
******************************************************************************/
static void addGroupResponseResp(ZCL_Notify_t *ntfy)
{
  ZCL_Request_t *request = GET_PARENT_BY_FIELD(ZCL_Request_t, notify, ntfy);
  ZCL_AddGroupResponse_t *addGroupResp = (ZCL_AddGroupResponse_t *)request->requestPayload;

  // Update group table in non-volatile memory
  if (ZCL_SUCCESS_STATUS == addGroupResp->status)
    PDS_Store(CS_GROUP_TABLE_MEM_ID);

  sendEndpointInformation(&request->dstAddressing);
}

/**************************************************************************//**
\brief View Group indication
******************************************************************************/
static ZCL_Status_t viewGroupInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ViewGroup_t *payload)
{
  ZCL_Status_t status;
  CommandDescriptor_t *cmd;
  ZCL_ViewGroupResponse_t *viewGroupResp;
  LOG_STRING(viewGroupStr, "viewGroupInd(): 0x%04x\r\n");

  appSnprintf(viewGroupStr, payload->groupId);

  if (NWK_IsGroupMember(payload->groupId, APP_ENDPOINT_LIGHT))
    status = ZCL_SUCCESS_STATUS;
  else
    status = ZCL_NOT_FOUND_STATUS;

  // If received via multicast or broadcast service no response shall be given
  if (addressing->nonUnicast)
    return ZCL_SUCCESS_STATUS;

  if (!(cmd = clustersAllocCommand()))
    return ZCL_SUCCESS_STATUS;

  cmd->clusterId = GROUPS_CLUSTER_ID;
  cmd->commandId = ZCL_GROUPS_CLUSTER_VIEW_GROUP_RESPONSE_COMMAND_ID;
  cmd->srcEndpoint = APP_ENDPOINT_LIGHT;
  cmd->seqNumberSpecified = true;

  viewGroupResp = &cmd->payload.viewGroupResp;
  viewGroupResp->status = status;
  viewGroupResp->groupId = payload->groupId;
  viewGroupResp->groupName[0] = 0;

  cmd->size = sizeof(cmd->payload.viewGroupResp);

  clustersSendCommandWithAddressing(cmd, addressing);

  (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Get Group Membership indication
******************************************************************************/
static ZCL_Status_t getGroupMembershipInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_GetGroupMembership_t *payload)
{
  CommandDescriptor_t *cmd;
  ZCL_GetGroupMembershipResponse_t *getGroupMembershipResp;
  LOG_STRING(getGroupMembershipIndStr, "getGroupMembershipInd()\r\n");

  appSnprintf(getGroupMembershipIndStr);

  if (!(cmd = clustersAllocCommand()))
    return ZCL_SUCCESS_STATUS;

  // If received via multicast or broadcast service no response shall be given
  if (addressing->nonUnicast)
    return ZCL_SUCCESS_STATUS;

  getGroupMembershipResp = &cmd->payload.getGroupMembershipResp;

  getGroupMembershipResp->groupCount = 0;
  getGroupMembershipResp->capacity = NWK_GroupCapacity();

  if (payload->groupCount > 0)
  {
    for (int i = 0; i < payload->groupCount; i++)
    {
      if (NWK_IsGroupMember(payload->groupList[i], APP_ENDPOINT_LIGHT))
      {
        getGroupMembershipResp->groupList[getGroupMembershipResp->groupCount] = payload->groupList[i];
        getGroupMembershipResp->groupCount++;
      }
    }

    if (getGroupMembershipResp->groupCount == 0)
      return ZCL_SUCCESS_STATUS;
  }
  else
  {
    NWK_GroupTableEntry_t *group = NULL;

     group = NWK_NextGroup(group);
     while (NULL != group)
    {
      getGroupMembershipResp->groupList[getGroupMembershipResp->groupCount] = group->addr;
      getGroupMembershipResp->groupCount++;
      group = NWK_NextGroup(group);
    }
  }

  cmd->clusterId = GROUPS_CLUSTER_ID;
  cmd->commandId = ZCL_GROUPS_CLUSTER_GET_GROUP_MEMBERSHIP_RESPONSE_COMMAND_ID;
  cmd->srcEndpoint = APP_ENDPOINT_LIGHT;
  cmd->seqNumberSpecified = true;

  cmd->size = sizeof(cmd->payload.getGroupMembershipResp);
  //omit the extra bytes from getGroupMembershipResponse structure which includes space for CS_GROUP_TABLE_SIZE groups by default
  cmd->size -= (CS_GROUP_TABLE_SIZE - getGroupMembershipResp->groupCount) * sizeof(uint16_t);

  clustersSendCommandWithAddressing(cmd, addressing);

  (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Remove Group indication
******************************************************************************/
static ZCL_Status_t removeGroupInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_RemoveGroup_t *payload)
{
  ZCL_Status_t status;
  CommandDescriptor_t *cmd;
  ZCL_RemoveGroupResponse_t *removeGroupResp;
  LOG_STRING(removeGroupIndStr, "removeGroupInd(): 0x%04x\r\n");

  appSnprintf(removeGroupIndStr, payload->groupId);

  if (NWK_RemoveGroup(payload->groupId, APP_ENDPOINT_LIGHT))
  {
    scenesClusterRemoveByGroup(payload->groupId);
    status = ZCL_SUCCESS_STATUS;
  }
  else
  {
    status = ZCL_NOT_FOUND_STATUS;
  }

  // If received via multicast or broadcast service no response shall be given
  if (addressing->nonUnicast)
    return ZCL_SUCCESS_STATUS;

  if (!(cmd = clustersAllocCommand()))
    return ZCL_SUCCESS_STATUS;

  cmd->clusterId = GROUPS_CLUSTER_ID;
  cmd->commandId = ZCL_GROUPS_CLUSTER_REMOVE_GROUP_RESPONSE_COMMAND_ID;
  cmd->srcEndpoint = APP_ENDPOINT_LIGHT;
  cmd->seqNumberSpecified = true;

  removeGroupResp = &cmd->payload.removeGroupResp;
  removeGroupResp->status = status;
  removeGroupResp->groupId = payload->groupId;

  cmd->size = sizeof(cmd->payload.removeGroupResp);

  clustersSendCommandWithAddressing(cmd, addressing);

  (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Remove All Groups indication
******************************************************************************/
static ZCL_Status_t removeAllGroupsInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, void *payload)
{
  LOG_STRING(removeAllGroupsIndStr, "removeAllGroupsInd()\r\n");

  appSnprintf(removeAllGroupsIndStr);

  {
    NWK_GroupTableEntry_t *group = NULL;

    group = NWK_NextGroup(group);
    while (NULL != group)
    {
      scenesClusterRemoveByGroup(group->addr);
      group = NWK_NextGroup(group);
    }
  }

  NWK_RemoveAllGroups(APP_ENDPOINT_LIGHT);

  (void)addressing;
  (void)payloadLength;
  (void)payload;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Add Group If Identifying indication
******************************************************************************/
static ZCL_Status_t addGroupIfIdentifyingInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_AddGroupIfIdentifying_t *payload)
{
  LOG_STRING(addGroupIfIdentifyingIndStr, "addGroupIfIdentifyingInd(): 0x%04x\r\n");

  appSnprintf(addGroupIfIdentifyingIndStr, payload->groupId);

  if (identifyClusterIsIdentifying())
  {
    if (!NWK_IsGroupMember(payload->groupId, APP_ENDPOINT_LIGHT))
      NWK_AddGroup(payload->groupId, APP_ENDPOINT_LIGHT);
  }

  (void)addressing;
  (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}

#endif // APP_ZLL_DEVICE_TYPE >= APP_DEVICE_TYPE_ON_OFF_LIGHT

// eof lightGroupsCluster.c
