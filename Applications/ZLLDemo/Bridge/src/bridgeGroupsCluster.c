/**************************************************************************//**
  \file bridgeGroupsCluster.c

  \brief
    Control Bridge device Groups cluster implementation.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2013, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    22.01.13 N. Fomin - Created.
******************************************************************************/

#if APP_ZLL_DEVICE_TYPE == APP_DEVICE_TYPE_BRIDGE

/******************************************************************************
                    Includes
******************************************************************************/
#include <zcl.h>
#include <clusters.h>
#include <commandManager.h>
#include <bridgeGroupsCluster.h>
#include <bridgeClusters.h>

/******************************************************************************
                    Prototypes section
******************************************************************************/
static ZCL_Status_t addGroupResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_AddGroupResponse_t *payload);
static ZCL_Status_t removeGroupResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_RemoveGroupResponse_t *payload);

static void bridgeFillAddGroupPayload(ZCL_AddGroup_t *payload, uint16_t groupId);
static void bridgeFillRemoveGroupPayload(ZCL_RemoveGroup_t *payload, uint16_t groupId);

/******************************************************************************
                    Global variables section
******************************************************************************/
ZCL_GroupsClusterCommands_t groupsClusterCommands =
{
  ZCL_DEFINE_GROUPS_CLUSTER_COMMANDS(NULL, NULL, NULL, NULL, NULL, NULL,
    addGroupResponseInd, NULL, NULL, removeGroupResponseInd)
};

/******************************************************************************
                    Implementation section
******************************************************************************/
/**************************************************************************//**
\brief Sends Add Group command

\param[in] mode    - address mode;
\param[in] addr    - network address of destination node;
\param[in] ep      - endpoint number of destination node;
\param[in] groupId - group id
******************************************************************************/
void bridgeSendAddGroupCommand(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep, uint16_t groupId)
{
  CommandDescriptor_t *cmd;
  ZCL_Addressing_t addressing;

  if (!(cmd = bridgeGetFreeCommand()))
    return;

  bridgeFillCommandRequest(cmd, ZCL_GROUPS_CLUSTER_ADD_GROUP_COMMAND_ID,
                                     GROUPS_CLUSTER_ID, sizeof(cmd->payload.addGroup));
  bridgeFillAddGroupPayload(&cmd->payload.addGroup, groupId);
  bridgeFillDstAddressing(&addressing, mode, addr, ep);

  clustersSendCommandWithAddressing(cmd, &addressing);
}

/**************************************************************************//**
\brief Sends Remove Group command

\param[in] mode    - address mode;
\param[in] addr    - network address of destination node;
\param[in] ep      - endpoint number of destination node;
\param[in] groupId - group id
******************************************************************************/
void bridgeSendRemoveGroupCommand(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep, uint16_t groupId)
{
    CommandDescriptor_t *cmd;
  ZCL_Addressing_t addressing;

  if (!(cmd = bridgeGetFreeCommand()))
    return;

  bridgeFillCommandRequest(cmd, ZCL_GROUPS_CLUSTER_REMOVE_GROUP_COMMAND_ID,
                                     GROUPS_CLUSTER_ID, sizeof(cmd->payload.removeGroup));
  bridgeFillRemoveGroupPayload(&cmd->payload.removeGroup, groupId);
  bridgeFillDstAddressing(&addressing, mode, addr, ep);

  clustersSendCommandWithAddressing(cmd, &addressing);
}

/**************************************************************************//**
\brief Callback on receive of AddGroupResponse command; it is a stub
******************************************************************************/
static ZCL_Status_t addGroupResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_AddGroupResponse_t *payload)
{
  (void)addressing;
  (void)payloadLength;
  (void)payload;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receive of RemoveGroupResponse command; it is a stub
******************************************************************************/
static ZCL_Status_t removeGroupResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_RemoveGroupResponse_t *payload)
{
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
static void bridgeFillAddGroupPayload(ZCL_AddGroup_t *payload, uint16_t groupId)
{
  payload->groupId      = groupId;
  payload->groupName[0] = 0;
}

/**************************************************************************//**
\brief Fills Remove Group command structure

\param[out] payload - pointer to command structure;
\param[in]  groupId - id of a group
******************************************************************************/
static void bridgeFillRemoveGroupPayload(ZCL_RemoveGroup_t *payload, uint16_t groupId)
{
  payload->groupId = groupId;
}

#endif // APP_ZLL_DEVICE_TYPE == APP_DEVICE_TYPE_BRIDGE

// eof bridgeGroupsCluster.c
