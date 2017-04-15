/**************************************************************************//**
  \file colorSceneRemoteScenesCluster.h

  \brief
    Color Scene Remote device Scenes cluster interface.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    28.06.11 A. Taradov - Created.
******************************************************************************/
#ifndef _COLORSCENEREMOTESCENESCLUSTER_H
#define _COLORSCENEREMOTESCENESCLUSTER_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zcl.h>
#include <zclZllScenesCluster.h>

/******************************************************************************
                    Externals section
******************************************************************************/
extern ZCL_ScenesClusterCommands_t scenesClusterCommands;

/******************************************************************************
                    Prototypes section
******************************************************************************/
#if APP_ENABLE_CERTIFICATION_EXTENSION == 0
/**************************************************************************//**
\brief Sends Store/Recall/Remove Scene command

\param[in] mode    - address mode;
\param[in] addr    - short address of destination node or number of group;
\param[in] ep      - endpoint number of destination device;
\param[in] command - command id;
\param[in] group   - id of a group;
\param[in] scene   - id of a scene
******************************************************************************/
void colorSceneRemoteStoreRecallRemoveSceneCommand(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep,
                                                   uint8_t command, uint16_t group, uint8_t scene);

#else // APP_ENABLE_CERTIFICATION_EXTENSION == 1
/**************************************************************************//**
\brief Sends Store/Recall/Remove Scene command

\param[in] command - command id;
\param[in] group   - id of a group
\param[in] scene   - id of a scene
******************************************************************************/
void colorSceneRemoteStoreRecallRemoveSceneCommand(uint16_t command, uint16_t group, uint8_t scene);

/**************************************************************************//**
\brief Sends Get Scene Membership command

\param[in] groupId   - id of a group
******************************************************************************/
void colorSceneRemoteGetSceneMembershipCommand(uint16_t groupId);

/**************************************************************************//**
\brief Sends Remove All Scenes command

\param[in] groupId   - id of a group
******************************************************************************/
void colorSceneRemoteRemoveAllScenesCommand(uint16_t groupId);

/**************************************************************************//**
\brief Sends Add Scene command

\param[in] groupId - id of a group
\param[in] sceneId - id of a scene
\param[in] transitionTime - transition time
******************************************************************************/
void colorSceneRemoteAddSceneCommand(uint16_t groupId, uint8_t sceneId, uint16_t transitionTime);

/**************************************************************************//**
\brief Sends Remove Scene command

\param[in] groupId - id of a group
\param[in] sceneId - id of a scene
******************************************************************************/
void colorSceneRemoteRemoveSceneCommand(uint16_t groupId, uint8_t sceneId);

/**************************************************************************//**
\brief Sends Enhanced Add Scene command

\param[in] groupId - id of a group
\param[in] sceneId - id of a scene
\param[in] transitionTime - transition time
******************************************************************************/
void colorSceneRemoteEnhancedAddSceneCommand(uint16_t groupId, uint8_t sceneId, uint16_t transitionTime);

/**************************************************************************//**
\brief Sends Copy Scene command

\param[in] dstGroupId - id of a destination group
\param[in] dstSceneId - id of a destination scene
\param[in] srcGroupId - id of a source group
\param[in] srcSceneId - id of a source scene
\param[in] mode - mode of a copy scene procedure
******************************************************************************/
void colorSceneRemoteCopySceneCommand(uint16_t dstGroupId, uint8_t dstSceneId, uint16_t srcGroupId, uint8_t srcSceneId, uint8_t mode);

/**************************************************************************//**
\brief Sends Scenes Cluster read attribute command

\param[in] attributeId - attribute of interest identifier
******************************************************************************/
void scenesSendReadAttribute(uint16_t attributeId);

#endif // APP_ENABLE_CERTIFICATION_EXTENSION
#endif // _COLORSCENEREMOTESCENESCLUSTER_H

// eof colorSceneRemoteScenesCluster.h
