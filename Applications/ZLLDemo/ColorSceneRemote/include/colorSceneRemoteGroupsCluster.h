/**************************************************************************//**
  \file colorSceneRemoteGroupsCluster.h

  \brief
    Color Scene Remote device Groups cluster interface.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    28.06.11 A. Taradov - Created.
******************************************************************************/
#ifndef _COLORSCENEREMOTEGROUPSCLUSTER_H
#define _COLORSCENEREMOTEGROUPSCLUSTER_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zcl.h>
#include <zclZllGroupsCluster.h>

/******************************************************************************
                    Types section
******************************************************************************/
typedef void (*AddGroupResponseCb_t)(uint8_t status, uint16_t groupId);

/******************************************************************************
                    Externals
******************************************************************************/
extern ZCL_GroupsClusterCommands_t groupsClusterCommands;

/******************************************************************************
                    Prototypes section
******************************************************************************/
/**************************************************************************//**
\brief Sends Add Group command

\param[in] addr    - network address of destination node;
\param[in] ep      - endpoint number of destination node;
\param[in] groupId - group id
\param[in] cb - callback which is called on add group response reception
******************************************************************************/
void colorSceneRemoteSendAddGroupCommand(ShortAddr_t addr, Endpoint_t ep, uint16_t groupId, AddGroupResponseCb_t cb);

#if APP_ENABLE_CERTIFICATION_EXTENSION == 0
/**************************************************************************//**
\brief Sends Remove Group command

\param[in] addr    - network address of destination node;
\param[in] ep      - endpoint number of destination node;
\param[in] groupId - group id
******************************************************************************/
void colorSceneRemoteSendRemoveGroupCommand(ShortAddr_t addr, Endpoint_t ep, uint16_t groupId);

#else // APP_ENABLE_CERTIFICATION_EXTENSION == 1
/**************************************************************************//**
\brief Sends Remove Group command

\param[in] groupId - group id
******************************************************************************/
void colorSceneRemoteSendRemoveGroupCommand(uint16_t groupId);

/**************************************************************************//**
\brief Sends Remove Group command
******************************************************************************/
void colorSceneRemoteSendRemoveAllGroupsCommand(void);

/**************************************************************************//**
\brief Sends Get Group Membership command

\param[in] groupCount - an amount of group ids to put into request
\param[in] groupList - group ids list to put into request
******************************************************************************/
void colorSceneRemoteSendGetGroupMembershipCommand(uint8_t groupCount, const uint16_t *groupList);

/**************************************************************************//**
\brief Sends View Group command

\param[in] groupId - group id to get information of
******************************************************************************/
void colorSceneRemoteSendViewGroupCommand(uint16_t groupId);

/**************************************************************************//**
\brief Sends Add Group If Identifying command

\param[in] groupId - group id to get information of
******************************************************************************/
void colorSceneRemoteSendAddGroupIfIdentifyingCommand(uint16_t groupId);

/**************************************************************************//**
\brief Sends Groups Cluster read attribute command

\param[in] attributeId - attribute of interest identifier
******************************************************************************/
void groupsSendReadAttribute(uint16_t attributeId);

#endif // APP_ENABLE_CERTIFICATION_EXTENSION

#endif // _COLORSCENEREMOTEGROUPSCLUSTER_H

// eof colorSceneRemoteGroupsCluster.h
