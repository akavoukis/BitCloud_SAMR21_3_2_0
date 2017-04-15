/**************************************************************************//**
  \file colorSceneRemoteGroupsCluster.c

  \brief
    Color Scene Remote device Groups cluster implementation.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    28.06.11 A. Taradov - Created.
******************************************************************************/

#if APP_ZLL_DEVICE_TYPE == APP_DEVICE_TYPE_COLOR_SCENE_REMOTE

/******************************************************************************
                    Includes
******************************************************************************/
#include <zcl.h>
#include <zclParser.h>
#include <debug.h>
#include <clusters.h>
#include <commandManager.h>
#include <zclZllGroupsCluster.h>
#include <colorSceneRemoteGroupsCluster.h>
#include <colorSceneRemoteClusters.h>

/******************************************************************************
                    Prototypes section
******************************************************************************/
static ZCL_Status_t addGroupResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_AddGroupResponse_t *payload);
static ZCL_Status_t removeGroupResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_RemoveGroupResponse_t *payload);

static void colorSceneRemoteFillAddGroupPayload(ZCL_AddGroup_t *payload, uint16_t groupId);
static void colorSceneRemoteFillRemoveGroupPayload(ZCL_RemoveGroup_t *payload, uint16_t groupId);

#if APP_ENABLE_CERTIFICATION_EXTENSION == 1
static ZCL_Status_t getGroupMembershipResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_GetGroupMembershipResponse_t *payload);
static ZCL_Status_t viewGroupResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ViewGroupResponse_t *payload);
static void readAttributeResp(ZCL_Notify_t *ntfy);
#endif
/******************************************************************************
                    Global variables section
******************************************************************************/
ZCL_GroupsClusterCommands_t groupsClusterCommands =
{
#if APP_ENABLE_CERTIFICATION_EXTENSION == 0
  ZCL_DEFINE_GROUPS_CLUSTER_COMMANDS(NULL, NULL, NULL, NULL, NULL, NULL,
    addGroupResponseInd, NULL, NULL, removeGroupResponseInd)
#else
  ZCL_DEFINE_GROUPS_CLUSTER_COMMANDS(NULL, NULL, NULL, NULL, NULL, NULL,
    addGroupResponseInd, viewGroupResponseInd, getGroupMembershipResponseInd, removeGroupResponseInd)
#endif
};

AddGroupResponseCb_t serviceCallback = NULL;

/******************************************************************************
                    Implementation section
******************************************************************************/
/**************************************************************************//**
\brief Sends Add Group command

\param[in] addr    - network address of destination node;
\param[in] ep      - endpoint number of destination node;
\param[in] groupId - group id
\param[in] cb - callback which is called on add group response reception
******************************************************************************/
void colorSceneRemoteSendAddGroupCommand(ShortAddr_t addr, Endpoint_t ep, uint16_t groupId, AddGroupResponseCb_t cb)
{
  CommandDescriptor_t *cmd;
  ZCL_Addressing_t addressing;

  if (!(cmd = colorSceneRemoteGetFreeCommand()) || serviceCallback)
    return;

  serviceCallback = cb;
  colorSceneRemoteFillCommandRequest(cmd, ZCL_GROUPS_CLUSTER_ADD_GROUP_COMMAND_ID,
                                     GROUPS_CLUSTER_ID, sizeof(cmd->payload.addGroup));
  colorSceneRemoteFillAddGroupPayload(&cmd->payload.addGroup, groupId);
  colorSceneRemoteFillDstAddressing(&addressing, APS_SHORT_ADDRESS, addr, ep);

  clustersSendCommandWithAddressing(cmd, &addressing);
}

#if APP_ENABLE_CERTIFICATION_EXTENSION == 0
/**************************************************************************//**
\brief Sends Remove Group command

\param[in] addr    - network address of destination node;
\param[in] ep      - endpoint number of destination node;
\param[in] groupId - group id
******************************************************************************/
void colorSceneRemoteSendRemoveGroupCommand(ShortAddr_t addr, Endpoint_t ep, uint16_t groupId)
{
  CommandDescriptor_t *cmd;
  ZCL_Addressing_t addressing;

  if (!(cmd = colorSceneRemoteGetFreeCommand()))
    return;

  colorSceneRemoteFillCommandRequest(cmd, ZCL_GROUPS_CLUSTER_REMOVE_GROUP_COMMAND_ID,
                                     GROUPS_CLUSTER_ID, sizeof(cmd->payload.removeGroup));
  colorSceneRemoteFillRemoveGroupPayload(&cmd->payload.removeGroup, groupId);
  colorSceneRemoteFillDstAddressing(&addressing, APS_SHORT_ADDRESS, addr, ep);

  clustersSendCommandWithAddressing(cmd, &addressing);
}

#else // APP_ENABLE_CERTIFICATION_EXTENSION == 1
/**************************************************************************//**
\brief Sends Remove Group command

\param[in] groupId - group id
******************************************************************************/
void colorSceneRemoteSendRemoveGroupCommand(uint16_t groupId)
{
  CommandDescriptor_t *cmd;

  if (!(cmd = colorSceneRemoteGetFreeCommand()))
    return;

  colorSceneRemoteFillCommandRequest(cmd, ZCL_GROUPS_CLUSTER_REMOVE_GROUP_COMMAND_ID,
                                     GROUPS_CLUSTER_ID, sizeof(cmd->payload.removeGroup));
  colorSceneRemoteFillRemoveGroupPayload(&cmd->payload.removeGroup, groupId);

  clustersSendCommand(cmd);
}

/**************************************************************************//**
\brief Sends Remove Group command
******************************************************************************/
void colorSceneRemoteSendRemoveAllGroupsCommand(void)
{
  CommandDescriptor_t *cmd;

  if (!(cmd = colorSceneRemoteGetFreeCommand()))
    return;

  colorSceneRemoteFillCommandRequest(cmd, ZCL_GROUPS_CLUSTER_REMOVE_ALL_GROUPS_COMMAND_ID,
                                     GROUPS_CLUSTER_ID, sizeof(cmd->payload.removeGroup));

  clustersSendCommand(cmd);
}

/**************************************************************************//**
\brief Sends Get Group Membership command

\param[in] groupCount - an amount of group ids to put into request
\param[in] groupList - group ids list to put into request
******************************************************************************/
void colorSceneRemoteSendGetGroupMembershipCommand(uint8_t groupCount, const uint16_t *groupList)
{
  CommandDescriptor_t *cmd;

  if (!(cmd = colorSceneRemoteGetFreeCommand()))
    return;

  colorSceneRemoteFillCommandRequest(cmd,
                                     ZCL_GROUPS_CLUSTER_GET_GROUP_MEMBERSHIP_COMMAND_ID,
                                     GROUPS_CLUSTER_ID,
                                     sizeof(uint8_t) + sizeof(uint16_t) * groupCount);
  cmd->payload.getGroupMembership.groupCount = groupCount;

  for (uint8_t i = 0; i < groupCount; i++)
    cmd->payload.getGroupMembership.groupList[i] = groupList[i];

  clustersSendCommand(cmd);
}

/**************************************************************************//**
\brief Get Group Membership Response indication
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

  (void)addressing;
  (void)payloadLength;
  (void)payload;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Sends View Group command

\param[in] groupId - group id to get information of
******************************************************************************/
void colorSceneRemoteSendViewGroupCommand(uint16_t groupId)
{
  CommandDescriptor_t *cmd;

  if (!(cmd = colorSceneRemoteGetFreeCommand()))
    return;

  colorSceneRemoteFillCommandRequest(cmd,
                                     ZCL_GROUPS_CLUSTER_VIEW_GROUP_COMMAND_ID,
                                     GROUPS_CLUSTER_ID,
                                     sizeof(cmd->payload.viewGroup));
  cmd->payload.viewGroup.groupId = groupId;

  clustersSendCommand(cmd);
}

/**************************************************************************//**
\brief View Group Response indication
******************************************************************************/
static ZCL_Status_t viewGroupResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ViewGroupResponse_t *payload)
{
  LOG_STRING(respStr, "viewGroupResponse(): status = 0x%02x\r\n");
  LOG_STRING(groupStr, "groupId = 0x%04x\r\n");

  appSnprintf(respStr, payload->status);
  appSnprintf(groupStr, payload->groupId);

  (void)addressing;
  (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Sends Add Group If Identifying command

\param[in] groupId - group id to get information of
******************************************************************************/
void colorSceneRemoteSendAddGroupIfIdentifyingCommand(uint16_t groupId)
{
  CommandDescriptor_t *cmd;

  if (!(cmd = colorSceneRemoteGetFreeCommand()))
    return;

  colorSceneRemoteFillCommandRequest(cmd,
                                     ZCL_GROUPS_CLUSTER_ADD_GROUP_IF_IDENTIFYING_COMMAND_ID,
                                     GROUPS_CLUSTER_ID,
                                     sizeof(cmd->payload.addGroupIfIdentifying));
  cmd->payload.addGroupIfIdentifying.groupId = groupId;
  cmd->payload.addGroupIfIdentifying.groupName[0] = 0;
  clustersSendCommand(cmd);
}

/**************************************************************************//**
\brief Sends Groups Cluster read attribute command

\param[in] attributeId - attribute of interest identifier
******************************************************************************/
void groupsSendReadAttribute(uint16_t attributeId)
{
  CommandDescriptor_t *cmd;

  if (!(cmd = clustersAllocCommand()))
    return;

  cmd->clusterId = GROUPS_CLUSTER_ID;
  cmd->commandId = ZCL_READ_ATTRIBUTES_COMMAND_ID;
  cmd->payload.readAttribute.id = attributeId;
  cmd->size = sizeof(ZCL_ReadAttributeReq_t);
  cmd->isAttributeOperation = true;
  cmd->ZCL_Notify = readAttributeResp;
  clustersSendCommand(cmd);
}

/**************************************************************************//**
\brief ZCL command response
******************************************************************************/
static void readAttributeResp(ZCL_Notify_t *ntfy)
{
  if (ZCL_ZCL_RESPONSE_ID == ntfy->id && ZCL_SUCCESS_STATUS == ntfy->status)
  {
    ZCL_ReadAttributeResp_t *readAttrResp = (ZCL_ReadAttributeResp_t *)ntfy->responsePayload;
    ZCL_DataTypeDescriptor_t attrDesc;

    ZCL_GetDataTypeDescriptor(readAttrResp->type, readAttrResp->value, &attrDesc);

    if ((ZCL_DATA_TYPE_ANALOG_KIND == attrDesc.kind ||
         ZCL_DATA_TYPE_DISCRETE_KIND == attrDesc.kind) &&
        sizeof(uint32_t) >= attrDesc.length)
    {
      uint32_t value = 0;
      LOG_STRING(attrValueStr, "Attr 0x%04x = %u\r\n");

      memcpy(&value, readAttrResp->value, attrDesc.length);
      appSnprintf(attrValueStr, (unsigned)readAttrResp->id, (unsigned int)value);
    }
  }
}

#endif // APP_ENABLE_CERTIFICATION_EXTENSION

/**************************************************************************//**
\brief Callback on receive of AddGroupResponse command; it is a stub
******************************************************************************/
static ZCL_Status_t addGroupResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_AddGroupResponse_t *payload)
{
  LOG_STRING(addGroupRespStr, "addGroupResponseInd()\r\n");

  if (serviceCallback)
  {
    serviceCallback(payload->status, payload->groupId);
    serviceCallback = NULL;
  }

  appSnprintf(addGroupRespStr);
  (void)addressing;
  (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receive of RemoveGroupResponse command; it is a stub
******************************************************************************/
static ZCL_Status_t removeGroupResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_RemoveGroupResponse_t *payload)
{
  LOG_STRING(removeGroupRespStr, "removeGroupResponseInd()\r\n");
  appSnprintf(removeGroupRespStr);

  (void)addressing;
  (void)payloadLength;
  (void)payload;
  return ZCL_SUCCESS_STATUS;
}


/**************************************************************************//**
\brief Fills Add Group command structure

\param[out] payload - pointer to command structure;
\param[in]  groupId - id of a group
******************************************************************************/
static void colorSceneRemoteFillAddGroupPayload(ZCL_AddGroup_t *payload, uint16_t groupId)
{
  payload->groupId      = groupId;
  payload->groupName[0] = 0;
}

/**************************************************************************//**
\brief Fills Remove Group command structure

\param[out] payload - pointer to command structure;
\param[in]  groupId - id of a group
******************************************************************************/
static void colorSceneRemoteFillRemoveGroupPayload(ZCL_RemoveGroup_t *payload, uint16_t groupId)
{
  payload->groupId = groupId;
}

#endif // APP_ZLL_DEVICE_TYPE == APP_DEVICE_TYPE_COLOR_SCENE_REMOTE

// eof colorSceneRemoteGroupsCluster.c
