/**************************************************************************//**
  \file colorSceneRemoteScenesCluster.c

  \brief
    Color Scene Remote device Scenes cluster implementation.

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
                    Includes section
******************************************************************************/
#include <debug.h>
#include <zcl.h>
#include <zclParser.h>
#include <zclZllScenesCluster.h>
#include <commandManager.h>
#include <colorSceneRemoteClusters.h>
#include <colorSceneRemoteFsm.h>

/******************************************************************************
                    Prototypes section
******************************************************************************/
static ZCL_Status_t addSceneResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_AddSceneResponse_t *payload);
static ZCL_Status_t viewSceneResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ViewSceneResponse_t *payload);
static ZCL_Status_t removeSceneResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_RemoveSceneResponse_t *payload);
static ZCL_Status_t removeAllScenesResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_RemoveAllScenesResponse_t *payload);
static ZCL_Status_t storeSceneResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_StoreSceneResponse_t *payload);
static ZCL_Status_t getSceneMembershipResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_GetSceneMembershipResponse_t *payload);
static ZCL_Status_t enhancedAddSceneResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_EnhancedAddSceneResponse_t *payload);
static ZCL_Status_t enhancedViewSceneResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_EnhancedViewSceneResponse_t *payload);
static ZCL_Status_t copySceneResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_CopySceneResponse_t *payload);

static void colorSceneRemoteFillScenePayload(ZCL_StoreScene_t *payload, uint16_t group, uint8_t scene);

#if APP_ENABLE_CERTIFICATION_EXTENSION == 1
static void readAttributeResp(ZCL_Notify_t *ntfy);
#endif
/******************************************************************************
                    Global variables section
******************************************************************************/
ZCL_ScenesClusterCommands_t scenesClusterCommands =
{
  ZCL_DEFINE_SCENES_CLUSTER_CLIENT_COMMANDS(addSceneResponseInd, viewSceneResponseInd,
      removeSceneResponseInd, removeAllScenesResponseInd, storeSceneResponseInd,
      getSceneMembershipResponseInd, enhancedAddSceneResponseInd,
      enhancedViewSceneResponseInd, copySceneResponseInd)
};

/******************************************************************************
                    Implementations section
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
                                                   uint8_t command, uint16_t group, uint8_t scene)
{
  CommandDescriptor_t *cmd;
  ZCL_Addressing_t addressing;

  if (!(cmd = colorSceneRemoteGetFreeCommand()))
    return;

  colorSceneRemoteFillCommandRequest(cmd, command,
                                     SCENES_CLUSTER_ID, sizeof(cmd->payload.storeScene));
  colorSceneRemoteFillScenePayload(&cmd->payload.storeScene, group, scene);
  colorSceneRemoteFillDstAddressing(&addressing, mode, addr, ep);

  clustersSendCommandWithAddressing(cmd, &addressing);
}

#else // APP_ENABLE_CERTIFICATION_EXTENSION == 1
/**************************************************************************//**
\brief Sends Store/Recall/Remove Scene command

\param[in] command - command id;
\param[in] group   - id of a group
\param[in] scene   - id of a scene
******************************************************************************/
void colorSceneRemoteStoreRecallRemoveSceneCommand(uint16_t command, uint16_t group, uint8_t scene)
{
  CommandDescriptor_t *cmd;

  if (!(cmd = colorSceneRemoteGetFreeCommand()))
    return;

  colorSceneRemoteFillCommandRequest(cmd, command,
                                     SCENES_CLUSTER_ID, sizeof(cmd->payload.storeScene));
  colorSceneRemoteFillScenePayload(&cmd->payload.storeScene, group, scene);

  clustersSendCommand(cmd);
}

/**************************************************************************//**
\brief Sends Get Scene Membership command

\param[in] groupId   - id of a group
******************************************************************************/
void colorSceneRemoteGetSceneMembershipCommand(uint16_t groupId)
{
  CommandDescriptor_t *cmd;

  if (!(cmd = colorSceneRemoteGetFreeCommand()))
    return;

  colorSceneRemoteFillCommandRequest(cmd, ZCL_SCENES_CLUSTER_GET_SCENE_MEMBERSHIP_COMMAND_ID,
                                     SCENES_CLUSTER_ID, sizeof(cmd->payload.getSceneMembership));
  cmd->payload.getSceneMembership.groupId = groupId;
  clustersSendCommand(cmd);
}

/**************************************************************************//**
\brief Sends Remove All Scenes command

\param[in] groupId   - id of a group
******************************************************************************/
void colorSceneRemoteRemoveAllScenesCommand(uint16_t groupId)
{
  CommandDescriptor_t *cmd;

  if (!(cmd = colorSceneRemoteGetFreeCommand()))
    return;

  colorSceneRemoteFillCommandRequest(cmd, ZCL_SCENES_CLUSTER_REMOVE_ALL_SCENES_COMMAND_ID,
                                     SCENES_CLUSTER_ID, sizeof(cmd->payload.removeAllScenes));
  cmd->payload.removeAllScenes.groupId = groupId;
  clustersSendCommand(cmd);
}

/**************************************************************************//**
\brief Sends Add Scene command

\param[in] groupId - id of a group
\param[in] sceneId - id of a scene
\param[in] transitionTime - transition time
******************************************************************************/
void colorSceneRemoteAddSceneCommand(uint16_t groupId, uint8_t sceneId, uint16_t transitionTime)
{
  CommandDescriptor_t *cmd;

  if (!(cmd = colorSceneRemoteGetFreeCommand()))
    return;

  colorSceneRemoteFillCommandRequest(cmd, ZCL_SCENES_CLUSTER_ADD_SCENE_COMMAND_ID,
                                     SCENES_CLUSTER_ID, sizeof(cmd->payload.addScene));
  cmd->payload.addScene.groupId = groupId;
  cmd->payload.addScene.sceneId = sceneId;
  cmd->payload.addScene.transitionTime = transitionTime;
  cmd->payload.addScene.name[0] = 0;
  clustersSendCommand(cmd);
}

/**************************************************************************//**
\brief Sends Enhanced Add Scene command

\param[in] groupId - id of a group
\param[in] sceneId - id of a scene
\param[in] transitionTime - transition time
******************************************************************************/
void colorSceneRemoteEnhancedAddSceneCommand(uint16_t groupId, uint8_t sceneId, uint16_t transitionTime)
{
  CommandDescriptor_t *cmd;

  if (!(cmd = colorSceneRemoteGetFreeCommand()))
    return;

  colorSceneRemoteFillCommandRequest(cmd, ZCL_SCENES_CLUSTER_ENHANCED_ADD_SCENE_COMMAND_ID,
                                     SCENES_CLUSTER_ID, sizeof(cmd->payload.enhancedAddScene));
  cmd->payload.enhancedAddScene.groupId = groupId;
  cmd->payload.enhancedAddScene.sceneId = sceneId;
  cmd->payload.enhancedAddScene.transitionTime = transitionTime;
  cmd->payload.enhancedAddScene.name[0] = 0;

  cmd->payload.enhancedAddScene.onOffClusterExtFields.clusterId = ONOFF_CLUSTER_ID;
  cmd->payload.enhancedAddScene.onOffClusterExtFields.length = sizeof(uint8_t);
  cmd->payload.enhancedAddScene.onOffClusterExtFields.onOffValue = 1;

  cmd->payload.enhancedAddScene.levelControlClusterExtFields.clusterId = LEVEL_CONTROL_CLUSTER_ID;
  cmd->payload.enhancedAddScene.levelControlClusterExtFields.length = sizeof(uint8_t);
  cmd->payload.enhancedAddScene.levelControlClusterExtFields.currentLevel = 128;

  cmd->payload.enhancedAddScene.colorControlClusterExtFields.clusterId = COLOR_CONTROL_CLUSTER_ID;
  cmd->payload.enhancedAddScene.colorControlClusterExtFields.length = sizeof(uint8_t) + sizeof(uint16_t) * 4;
  cmd->payload.enhancedAddScene.colorControlClusterExtFields.currentX = 0;
  cmd->payload.enhancedAddScene.colorControlClusterExtFields.currentY = 0;
  cmd->payload.enhancedAddScene.colorControlClusterExtFields.enhancedCurrentHue = 30000; // Green
  cmd->payload.enhancedAddScene.colorControlClusterExtFields.currentSaturation = 128;

  clustersSendCommand(cmd);
}

/**************************************************************************//**
\brief Sends Remove Scene command

\param[in] groupId - id of a group
\param[in] sceneId - id of a scene
******************************************************************************/
void colorSceneRemoteRemoveSceneCommand(uint16_t groupId, uint8_t sceneId)
{
  CommandDescriptor_t *cmd;

  if (!(cmd = colorSceneRemoteGetFreeCommand()))
    return;

  colorSceneRemoteFillCommandRequest(cmd, ZCL_SCENES_CLUSTER_REMOVE_SCENE_COMMAND_ID,
                                     SCENES_CLUSTER_ID, sizeof(cmd->payload.removeScene));
  cmd->payload.removeScene.groupId = groupId;
  cmd->payload.removeScene.sceneId = sceneId;
  clustersSendCommand(cmd);
}

/**************************************************************************//**
\brief Sends Copy Scene command

\param[in] dstGroupId - id of a destination group
\param[in] dstSceneId - id of a destination scene
\param[in] srcGroupId - id of a source group
\param[in] srcSceneId - id of a source scene
\param[in] mode - mode of a copy scene procedure
******************************************************************************/
void colorSceneRemoteCopySceneCommand(uint16_t dstGroupId, uint8_t dstSceneId, uint16_t srcGroupId, uint8_t srcSceneId, uint8_t mode)
{
  CommandDescriptor_t *cmd;

  if (!(cmd = colorSceneRemoteGetFreeCommand()))
    return;

  colorSceneRemoteFillCommandRequest(cmd, ZCL_SCENES_CLUSTER_COPY_SCENE_COMMAND_ID,
                                     SCENES_CLUSTER_ID, sizeof(cmd->payload.copyScene));
  cmd->payload.copyScene.mode = mode;
  cmd->payload.copyScene.groupIdFrom = srcGroupId;
  cmd->payload.copyScene.sceneIdFrom = srcSceneId;
  cmd->payload.copyScene.groupIdTo = dstGroupId;
  cmd->payload.copyScene.sceneIdTo = dstSceneId;
  clustersSendCommand(cmd);
}

/**************************************************************************//**
\brief Sends Scenes Cluster read attribute command

\param[in] attributeId - attribute of interest identifier
******************************************************************************/
void scenesSendReadAttribute(uint16_t attributeId)
{
  CommandDescriptor_t *cmd;

  if (!(cmd = clustersAllocCommand()))
    return;

  cmd->clusterId = SCENES_CLUSTER_ID;
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
\brief Callback on receive of Add Scene Response command
******************************************************************************/
static ZCL_Status_t addSceneResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_AddSceneResponse_t *payload)
{
  LOG_STRING(addSceneRespStr, "Add scene response: status = 0x%02x\r\n");
  LOG_STRING(groupStr, "groupId = 0x%04x\r\n");
  LOG_STRING(sceneStr, "sceneId = 0x%02x\r\n");

  appSnprintf(addSceneRespStr, payload->status);
  appSnprintf(groupStr, payload->groupId);
  appSnprintf(sceneStr, payload->sceneId);

  (void)addressing;
  (void)payloadLength;
  (void)payload;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receive of View Scene Response command
******************************************************************************/
static ZCL_Status_t viewSceneResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ViewSceneResponse_t *payload)
{
  LOG_STRING(viewSceneRespStr, "View scene response: status = 0x%02x\r\n");
  LOG_STRING(groupStr, "groupId = 0x%04x\r\n");
  LOG_STRING(sceneStr, "sceneId = 0x%02x\r\n");
  LOG_STRING(transitionTimeStr, "transitionTime = 0x%04x\r\n");

  appSnprintf(viewSceneRespStr, payload->status);
  appSnprintf(groupStr, payload->groupId);
  appSnprintf(sceneStr, payload->sceneId);
  appSnprintf(transitionTimeStr, payload->transitionTime);

  (void)addressing;
  (void)payloadLength;
  (void)payload;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receive of Remove Scene Response command
******************************************************************************/
static ZCL_Status_t removeSceneResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_RemoveSceneResponse_t *payload)
{
  LOG_STRING(removeSceneRespStr, "Remove scene response: status = 0x%02x\r\n");
  LOG_STRING(groupStr, "groupId = 0x%04x\r\n");
  LOG_STRING(sceneStr, "sceneId = 0x%02x\r\n");

  appSnprintf(removeSceneRespStr, payload->status);
  appSnprintf(groupStr, payload->groupId);
  appSnprintf(sceneStr, payload->sceneId);

  (void)addressing;
  (void)payloadLength;
  (void)payload;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receive of Remove All Scenes Response command
******************************************************************************/
static ZCL_Status_t removeAllScenesResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_RemoveAllScenesResponse_t *payload)
{
  LOG_STRING(removeAllScenesRespStr, "Remove all scenes response: status = 0x%02x\r\n");
  LOG_STRING(groupStr, "groupId = 0x%04x\r\n");

  appSnprintf(removeAllScenesRespStr, payload->status);
  appSnprintf(groupStr, payload->groupId);

  (void)addressing;
  (void)payloadLength;
  (void)payload;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receive of Store Scene Response command
******************************************************************************/
static ZCL_Status_t storeSceneResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_StoreSceneResponse_t *payload)
{
  ZCL_StoreSceneResponse_t *resp = (ZCL_StoreSceneResponse_t *)payload;
  LOG_STRING(storeRespStr, "Store scene response: status = 0x%02x\r\n");

  appSnprintf(storeRespStr, resp->status);

  (void)addressing;
  (void)payloadLength;
  (void)resp;

  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receive of Get Scene Membership Response command
******************************************************************************/
static ZCL_Status_t getSceneMembershipResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_GetSceneMembershipResponse_t *payload)
{
  LOG_STRING(getSceneMembershipRespStr, "Get scene membership response: status = 0x%02x\r\n");
  LOG_STRING(groupStr, "groupId = 0x%04x\r\n");
  LOG_STRING(sceneCountStr, "sceneCount = 0x%02x\r\n");
  LOG_STRING(sceneStr, "sceneId = 0x%02x\r\n");

  appSnprintf(getSceneMembershipRespStr, payload->status);
  appSnprintf(groupStr, payload->groupId);
  appSnprintf(sceneCountStr, payload->sceneCount);

  for (uint8_t i = 0; i < payload->sceneCount; i++)
  {
    appSnprintf(sceneStr, payload->sceneList[i]);
  }

  (void)addressing;
  (void)payloadLength;
  (void)payload;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receive of Enhanced Add Scene Response command
******************************************************************************/
static ZCL_Status_t enhancedAddSceneResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_EnhancedAddSceneResponse_t *payload)
{
  LOG_STRING(addSceneRespStr, "Add scene response: status = 0x%02x\r\n");
  LOG_STRING(groupStr, "groupId = 0x%04x\r\n");
  LOG_STRING(sceneStr, "sceneId = 0x%02x\r\n");

  appSnprintf(addSceneRespStr, payload->status);
  appSnprintf(groupStr, payload->groupId);
  appSnprintf(sceneStr, payload->sceneId);

  (void)addressing;
  (void)payloadLength;
  (void)payload;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receive of Enhanced View Scene Response command
******************************************************************************/
static ZCL_Status_t enhancedViewSceneResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_EnhancedViewSceneResponse_t *payload)
{
  LOG_STRING(viewSceneRespStr, "View scene response: status = 0x%02x\r\n");
  LOG_STRING(groupStr, "groupId = 0x%04x\r\n");
  LOG_STRING(sceneStr, "sceneId = 0x%02x\r\n");
  LOG_STRING(transitionTimeStr, "transitionTime = 0x%04x\r\n");

  appSnprintf(viewSceneRespStr, payload->status);
  appSnprintf(groupStr, payload->groupId);
  appSnprintf(sceneStr, payload->sceneId);
  appSnprintf(transitionTimeStr, payload->transitionTime);

  (void)addressing;
  (void)payloadLength;
  (void)payload;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receive of Copy Scene Response command
******************************************************************************/
static ZCL_Status_t copySceneResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_CopySceneResponse_t *payload)
{
  LOG_STRING(copySceneRespStr, "Copy scene response: status = 0x%02x\r\n");

  appSnprintf(copySceneRespStr, payload->status);
  (void)addressing;
  (void)payloadLength;
  (void)payload;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Fills Store/Recall/Remove command structure

\param[out] payload - pointer to command structure;
\param[in]  group   - id of a group;
\param[in]  scene   - id of a scene
******************************************************************************/
static void colorSceneRemoteFillScenePayload(ZCL_StoreScene_t *payload, uint16_t group, uint8_t scene)
{
  payload->groupId = group;
  payload->sceneId = scene;
}

#endif // APP_ZLL_DEVICE_TYPE == APP_DEVICE_TYPE_COLOR_SCENE_REMOTE

// eof colorSceneRemoteScenesCluster.c
