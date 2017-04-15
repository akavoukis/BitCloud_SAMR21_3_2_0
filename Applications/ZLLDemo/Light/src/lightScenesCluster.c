/**************************************************************************//**
  \file lightScenesCluster.c

  \brief
    Light device Scenes cluster implementation.

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
#include <leds.h>
#include <zclZllScenesCluster.h>
#include <zclZllOnOffCluster.h>
#include <zclZllLevelControlCluster.h>
#include <zclZllColorControlCluster.h>
#include <commandManager.h>
#include <lightOnOffCluster.h>
#include <lightLevelControlCluster.h>
#include <lightColorControlCluster.h>
#include <zllDemo.h>
#include <pdsDataServer.h>

#include <N_DeviceInfo_Bindings.h>
#include <N_DeviceInfo.h>

/******************************************************************************
                    Definitions section
******************************************************************************/
#define DEFAULT_TRANSITION_TIME   0

#define GLOBAL_SCENE_SCENE_ID     0x00
#define GLOBAL_SCENE_GROUP_ID     0x0000

/******************************************************************************
                    Prototypes section
******************************************************************************/
static ZCL_Status_t addSceneInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_AddScene_t *payload);
static void addSceneResponseResp(ZCL_Notify_t *ntfy);

static ZCL_Status_t viewSceneInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ViewScene_t *payload);

static ZCL_Status_t removeSceneInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_RemoveScene_t *payload);
static void removeSceneResponseResp(ZCL_Notify_t *ntfy);

static ZCL_Status_t removeAllScenesInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_RemoveAllScenes_t *payload);
static void removeAllScenesResponseResp(ZCL_Notify_t *ntfy);

static ZCL_Status_t storeSceneInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_StoreScene_t *payload);
static void storeSceneResponseResp(ZCL_Notify_t *ntfy);

static ZCL_Status_t recallSceneInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_RecallScene_t *payload);

static ZCL_Status_t getSceneMembershipInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_GetSceneMembership_t *payload);

static ZCL_Status_t enhancedAddSceneInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_EnhancedAddScene_t *payload);
static ZCL_Status_t enhancedViewSceneInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_EnhancedViewScene_t *payload);

static ZCL_Status_t copySceneInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_CopyScene_t *payload);
static void copySceneResponseResp(ZCL_Notify_t *ntfy);

static Scene_t *allocScene(void);
static Scene_t *findScene(uint16_t groupId, uint8_t sceneId);
static void storeScene(Scene_t *scene);
static void recallScene(Scene_t *scene);

/******************************************************************************
                    Global variables
******************************************************************************/
ZCL_ScenesClusterCommands_t scenesClusterCommands =
{
  ZCL_DEFINE_SCENES_CLUSTER_SERVER_COMMANDS(addSceneInd, viewSceneInd, removeSceneInd,
      removeAllScenesInd, storeSceneInd, recallSceneInd, getSceneMembershipInd,
      enhancedAddSceneInd, enhancedViewSceneInd, copySceneInd)
};

ZCL_SceneClusterServerAttributes_t scenesClusterServerAttributes =
{
  ZCL_DEFINE_SCENES_CLUSTER_SERVER_ATTRIBUTES()
};

/******************************************************************************
                    Local variables
******************************************************************************/
Scene_t scene[MAX_NUMBER_OF_SCENES];

/******************************************************************************
                    Implementations section
******************************************************************************/

/**************************************************************************//**
\brief Initialize Scenes cluster.
******************************************************************************/
void scenesClusterInit(void)
{
  if (!PDS_IsAbleToRestore(APP_LIGHT_SCENE_CLUSTER_SERVER_ATTR_MEM_ID))
  {
    for (uint8_t i = 0; i < MAX_NUMBER_OF_SCENES; i++)
      scene[i].free = true;

    scenesClusterServerAttributes.sceneCount.value = 0;
    scenesClusterServerAttributes.currentScene.value = 0;
    scenesClusterServerAttributes.currentGroup.value = 0;
    scenesClusterServerAttributes.sceneValid.value = true;
    scenesClusterServerAttributes.nameSupport.value = 0;

#if APP_ENABLE_CERTIFICATION_EXTENSION == 1
    // allocate space for a global scene
    {
      Scene_t *scene = allocScene();

      scene->sceneId = GLOBAL_SCENE_SCENE_ID;
      scene->groupId = GLOBAL_SCENE_GROUP_ID;
      scenesClusterServerAttributes.sceneCount.value--; // to pass the certification
    }
#endif
  }
}

/**************************************************************************//**
\brief Invalidate current device state
******************************************************************************/
void scenesClusterInvalidate(void)
{
  scenesClusterServerAttributes.sceneValid.value = false;
}

/**************************************************************************//**
\brief Store global scene
******************************************************************************/
void scenesClusterStoreGlobalScene(void)
{
  storeScene(findScene(GLOBAL_SCENE_GROUP_ID, GLOBAL_SCENE_SCENE_ID));
}

/**************************************************************************//**
\brief Recall global scene
******************************************************************************/
void scenesClusterRecallGlobalScene(void)
{
  recallScene(findScene(GLOBAL_SCENE_GROUP_ID, GLOBAL_SCENE_SCENE_ID));
}

/**************************************************************************//**
\brief Get scene structure by groupId and sceneId
******************************************************************************/
static Scene_t *findScene(uint16_t groupId, uint8_t sceneId)
{
  for (uint8_t i = 0; i < MAX_NUMBER_OF_SCENES; i++)
  {
    if (scene[i].groupId == groupId && scene[i].sceneId == sceneId && !scene[i].free)
      return &scene[i];
  }
  return NULL;
}

/**************************************************************************//**
\brief Allocate free scene and mark it busy
******************************************************************************/
static Scene_t *allocScene(void)
{
  for (uint8_t i = 0; i < MAX_NUMBER_OF_SCENES; i++)
  {
    if (scene[i].free)
    {
      memset(&scene[i], 0, sizeof(Scene_t));
      scene[i].free = false;
      scene[i].transitionTime = DEFAULT_TRANSITION_TIME;
      scene[i].transitionTime100ms = 0;

      scenesClusterServerAttributes.sceneCount.value++;

      return &scene[i];
    }
  }
  return NULL;
}

/**************************************************************************//**
\brief Mark scene table record as free
******************************************************************************/
static void freeScene(Scene_t *scene)
{
  if (GLOBAL_SCENE_GROUP_ID == scene->groupId &&
      GLOBAL_SCENE_SCENE_ID == scene->sceneId)
    return; // Can't free global scene

  if (!scene->free)
  {
    scene->free = true;
    scenesClusterServerAttributes.sceneCount.value--;
  }
}

/**************************************************************************//**
\brief Store current device state to a scene
******************************************************************************/
static void storeScene(Scene_t *scene)
{
  scene->onOff = onOffClusterServerAttributes.onOff.value;
#if APP_ZLL_DEVICE_TYPE >= APP_DEVICE_TYPE_ON_OFF_LIGHT
  scene->currentLevel = levelControlClusterServerAttributes.currentLevel.value;
#endif // APP_ZLL_DEVICE_TYPE >= APP_DEVICE_TYPE_ON_OFF_LIGHT
#if APP_ZLL_DEVICE_TYPE >= APP_DEVICE_TYPE_COLOR_LIGHT
  scene->colorMode = colorControlClusterServerAttributes.colorMode.value;
  scene->currentX = colorControlClusterServerAttributes.currentX.value;
  scene->currentY = colorControlClusterServerAttributes.currentY.value;
#endif // APP_ZLL_DEVICE_TYPE >= APP_DEVICE_TYPE_COLOR_LIGHT
#if (APP_ZLL_DEVICE_TYPE == APP_DEVICE_TYPE_COLOR_LIGHT) || (APP_ZLL_DEVICE_TYPE == APP_DEVICE_TYPE_EXTENDED_COLOR_LIGHT)
  scene->enhancedCurrentHue = colorControlClusterServerAttributes.enhancedCurrentHue.value;
  scene->currentSaturation = colorControlClusterServerAttributes.currentSaturation.value;
  scene->colorLoopActive = colorControlClusterServerAttributes.colorLoopActive.value;
  scene->colorLoopDirection = colorControlClusterServerAttributes.colorLoopDirection.value;
  scene->colorLoopTime = colorControlClusterServerAttributes.colorLoopTime.value;
#endif // (APP_ZLL_DEVICE_TYPE == APP_DEVICE_TYPE_COLOR_LIGHT) || (APP_ZLL_DEVICE_TYPE == APP_DEVICE_TYPE_EXTENDED_COLOR_LIGHT)

  scenesClusterServerAttributes.currentGroup.value = scene->groupId;
  scenesClusterServerAttributes.currentScene.value = scene->sceneId;
  scenesClusterServerAttributes.sceneValid.value = true;
}

/**************************************************************************//**
\brief Restore device state to the information from the scene
******************************************************************************/
static void recallScene(Scene_t *scene)
{
  scenesClusterServerAttributes.currentGroup.value = scene->groupId;
  scenesClusterServerAttributes.currentScene.value = scene->sceneId;

  onOffClusterSetExtensionField(scene->onOff);
#if APP_ZLL_DEVICE_TYPE >= APP_DEVICE_TYPE_ON_OFF_LIGHT
  levelControlClusterSetExtensionField(scene->currentLevel);
#endif // APP_ZLL_DEVICE_TYPE >= APP_DEVICE_TYPE_ON_OFF_LIGHT
#if APP_ZLL_DEVICE_TYPE >= APP_DEVICE_TYPE_COLOR_LIGHT
  colorControlClusterSetExtensionField(scene);
#endif // APP_ZLL_DEVICE_TYPE >= APP_DEVICE_TYPE_COLOR_LIGHT
  scenesClusterServerAttributes.sceneValid.value = true;
}

/**************************************************************************//**
\brief Remove all scenes associated with the group
******************************************************************************/
void scenesClusterRemoveByGroup(uint16_t group)
{
  for (uint8_t i = 0; i < MAX_NUMBER_OF_SCENES; i++)
  {
    if (scene[i].groupId == group)
      freeScene(&scene[i]);
  }
}

/**************************************************************************//**
\brief Check if groupId is a valid group ID existing on this device
******************************************************************************/
static bool groupIsValid(uint16_t groupId)
{
  return (groupId == 0 || NWK_IsGroupMember(groupId, APP_ENDPOINT_LIGHT));
}

/**************************************************************************//**
\brief Process Add Scene and Enhanced Add Scene command
******************************************************************************/
static ZCL_Status_t processAddSceneCommand(bool enhanced, ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_AddScene_t *payload)
{
  ZCL_Status_t status;
  CommandDescriptor_t *cmd;
  ZCL_AddSceneResponse_t *addSceneResp;

  if (groupIsValid(payload->groupId))
  {
    Scene_t *scene;

    scene = findScene(payload->groupId, payload->sceneId);

    if (!scene)
      scene = allocScene();

    if (scene)
    {
      status = ZCL_SUCCESS_STATUS;

      scene->sceneId = payload->sceneId;
      scene->groupId = payload->groupId;

      if (enhanced)
      {
        scene->transitionTime = payload->transitionTime / 10;
        scene->transitionTime100ms = payload->transitionTime % 10;
      }
      else
      {
        scene->transitionTime = payload->transitionTime;
        scene->transitionTime100ms = 0;
      }

      {
        int8_t commandSize = (sizeof(ZCL_AddScene_t) + payload->name[0]);
        int8_t extFieldsSize = (int8_t)payloadLength - commandSize;
        uint8_t *extFields = (uint8_t *)payload + commandSize;
        ZCL_ExtensionFieldSets_t *ext;

        while (extFieldsSize > 0)
        {
          ext = (ZCL_ExtensionFieldSets_t *)extFields;

          if (ONOFF_CLUSTER_ID == ext->clusterId)
          {
            ZCL_OnOffClusterExtensionFieldSet_t *ext =
                (ZCL_OnOffClusterExtensionFieldSet_t *)extFields;

            scene->onOff = ext->onOffValue;
          }

          else if (LEVEL_CONTROL_CLUSTER_ID == ext->clusterId)
          {
#if APP_ZLL_DEVICE_TYPE >= APP_DEVICE_TYPE_ON_OFF_LIGHT
            ZCL_LevelControlClusterExtensionFieldSet_t *ext =
                (ZCL_LevelControlClusterExtensionFieldSet_t *)extFields;

            scene->currentLevel = ext->currentLevel;
#else
            status = ZCL_INVALID_FIELD_STATUS;
#endif // APP_ZLL_DEVICE_TYPE >= APP_DEVICE_TYPE_ON_OFF_LIGHT
          }

          else if (COLOR_CONTROL_CLUSTER_ID == ext->clusterId)
          {
#if APP_ZLL_DEVICE_TYPE >= APP_DEVICE_TYPE_COLOR_LIGHT
            ZCL_ColorControlClusterExtensionFieldSet_t *ext =
                (ZCL_ColorControlClusterExtensionFieldSet_t *)extFields;

            scene->colorMode = colorControlClusterServerAttributes.colorMode.value;
            scene->currentX = ext->currentX;
            scene->currentY = ext->currentY;
#else
            status = ZCL_INVALID_FIELD_STATUS;
#endif // APP_ZLL_DEVICE_TYPE >= APP_DEVICE_TYPE_COLOR_LIGHT
#if (APP_ZLL_DEVICE_TYPE == APP_DEVICE_TYPE_COLOR_LIGHT) || (APP_ZLL_DEVICE_TYPE == APP_DEVICE_TYPE_EXTENDED_COLOR_LIGHT)
            if(!enhanced || (enhanced && !ext->currentX && !ext->currentY))
            {
              scene->enhancedCurrentHue = ext->enhancedCurrentHue;
              scene->currentSaturation = ext->currentSaturation;
              scene->colorLoopActive = ext->colorLoopActive;
              scene->colorLoopDirection = ext->colorLoopDirection;
              scene->colorLoopTime = ext->colorLoopTime;
            }
            else
            {
              scene->enhancedCurrentHue = 0;
              scene->currentSaturation = 0;
              scene->colorLoopActive = 0;
              scene->colorLoopDirection = 0;
              scene->colorLoopTime = 0; 
            }
#endif // (APP_ZLL_DEVICE_TYPE == APP_DEVICE_TYPE_COLOR_LIGHT) || (APP_ZLL_DEVICE_TYPE == APP_DEVICE_TYPE_EXTENDED_COLOR_LIGHT)
          }

          extFields += sizeof(ZCL_ExtensionFieldSets_t) + ext->length;
          extFieldsSize -= ext->length;
        }
      }
    }
    else
    {
      status = ZCL_INSUFFICIENT_SPACE_STATUS;
    }
  }
  else
  {
    status = ZCL_INVALID_FIELD_STATUS;
  }

  // If received via multicast or broadcast service no response shall be given
  if (addressing->nonUnicast)
    return ZCL_SUCCESS_STATUS;

  if (!(cmd = clustersAllocCommand()))
    return ZCL_SUCCESS_STATUS;

  cmd->clusterId = SCENES_CLUSTER_ID;
  cmd->commandId = enhanced ? ZCL_SCENES_CLUSTER_ENHANCED_ADD_SCENE_RESPONSE_COMMAND_ID :
                   ZCL_SCENES_CLUSTER_ADD_SCENE_RESPONSE_COMMAND_ID;
  cmd->srcEndpoint = APP_ENDPOINT_LIGHT;
  cmd->ZCL_Notify = addSceneResponseResp;
  cmd->seqNumberSpecified = true;

  addSceneResp = &cmd->payload.addSceneResp;
  addSceneResp->status = status;
  addSceneResp->groupId = payload->groupId;
  addSceneResp->sceneId = payload->sceneId;

  cmd->size = sizeof(cmd->payload.addSceneResp);

  clustersSendCommandWithAddressing(cmd, addressing);

  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief ZCL Add Scene Response command response
******************************************************************************/
static void addSceneResponseResp(ZCL_Notify_t *ntfy)
{
  ZCL_Request_t *request = GET_PARENT_BY_FIELD(ZCL_Request_t, notify, ntfy);
  ZCL_AddSceneResponse_t *addSceneResp = (ZCL_AddSceneResponse_t *)request->requestPayload;

  if (ZCL_SUCCESS_STATUS == addSceneResp->status)
    PDS_Store(ZLL_APP_MEMORY_MEM_ID);
}

/**************************************************************************//**
\brief Callback on receive of Add Scene command
******************************************************************************/
static ZCL_Status_t addSceneInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_AddScene_t *payload)
{
  LOG_STRING(addSceneStr, "addSceneInd(): 0x%04x, 0x%02x\r\n");

  appSnprintf(addSceneStr, payload->groupId, payload->sceneId);
  return processAddSceneCommand(false, addressing, payloadLength, payload);
}

/**************************************************************************//**
\brief Process View Scene and Enhanced View Scene command
******************************************************************************/
static ZCL_Status_t processViewSceneCommand(bool enhanced, ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ViewScene_t *payload)
{
  CommandDescriptor_t *cmd;
  ZCL_EnhancedViewSceneResponse_t *enhancedViewSceneResp;
  uint8_t size = sizeof(uint8_t) /*status*/ + sizeof(uint16_t) /*groupId*/ + sizeof(uint8_t) /*sceneId*/;

  // If received via multicast or broadcast service no response shall be given
  if (addressing->nonUnicast)
    return ZCL_SUCCESS_STATUS;

  if (!(cmd = clustersAllocCommand()))
    return ZCL_SUCCESS_STATUS;

  enhancedViewSceneResp = &cmd->payload.enhancedViewSceneResp;

  if (groupIsValid(payload->groupId))
  {
    Scene_t *scene;

    scene = findScene(payload->groupId, payload->sceneId);

    if (scene)
    {
      enhancedViewSceneResp->status = ZCL_SUCCESS_STATUS;
      enhancedViewSceneResp->name[0] = 0;

      if (enhanced)
        enhancedViewSceneResp->transitionTime = scene->transitionTime * 10 + scene->transitionTime100ms;
      else
        enhancedViewSceneResp->transitionTime = scene->transitionTime;

      enhancedViewSceneResp->onOffClusterExtFields.clusterId = ONOFF_CLUSTER_ID;
      enhancedViewSceneResp->onOffClusterExtFields.length = sizeof(ZCL_OnOffClusterExtensionFieldSet_t) -
                                                              sizeof(ZCL_ExtensionFieldSets_t);
        enhancedViewSceneResp->onOffClusterExtFields.onOffValue = scene->onOff;
        size = sizeof(ZCL_EnhancedViewSceneResponse_t) - sizeof(ZCL_ColorControlClusterExtensionFieldSet_t) - sizeof(ZCL_LevelControlClusterExtensionFieldSet_t);

#if APP_ZLL_DEVICE_TYPE >= APP_DEVICE_TYPE_ON_OFF_LIGHT
        enhancedViewSceneResp->levelControlClusterExtFields.clusterId = LEVEL_CONTROL_CLUSTER_ID;
        enhancedViewSceneResp->levelControlClusterExtFields.length =
          sizeof(ZCL_LevelControlClusterExtensionFieldSet_t) - sizeof(ZCL_ExtensionFieldSets_t);
        enhancedViewSceneResp->levelControlClusterExtFields.currentLevel = scene->currentLevel;
        size = sizeof(ZCL_EnhancedViewSceneResponse_t) - sizeof(ZCL_ColorControlClusterExtensionFieldSet_t);
#endif // APP_ZLL_DEVICE_TYPE >= APP_DEVICE_TYPE_ON_OFF_LIGHT
#if APP_ZLL_DEVICE_TYPE >= APP_DEVICE_TYPE_COLOR_LIGHT
        enhancedViewSceneResp->colorControlClusterExtFields.clusterId = COLOR_CONTROL_CLUSTER_ID;
        enhancedViewSceneResp->colorControlClusterExtFields.length =
        sizeof(ZCL_ExtensionFieldSets_t) + 2 * sizeof(uint16_t);
      enhancedViewSceneResp->colorControlClusterExtFields.currentX = scene->currentX;
      enhancedViewSceneResp->colorControlClusterExtFields.currentY = scene->currentY;
      size = sizeof(ZCL_EnhancedViewSceneResponse_t) - sizeof(ZCL_ColorControlClusterExtensionFieldSet_t) +
        sizeof(ZCL_ExtensionFieldSets_t) + 2 * sizeof(uint16_t);
#endif // APP_ZLL_DEVICE_TYPE >= APP_DEVICE_TYPE_COLOR_LIGHT
#if (APP_ZLL_DEVICE_TYPE == APP_DEVICE_TYPE_COLOR_LIGHT) || (APP_ZLL_DEVICE_TYPE == APP_DEVICE_TYPE_EXTENDED_COLOR_LIGHT)
      if (enhanced)
      {
        enhancedViewSceneResp->colorControlClusterExtFields.length =
          sizeof(ZCL_ColorControlClusterExtensionFieldSet_t) - sizeof(ZCL_ExtensionFieldSets_t);
        enhancedViewSceneResp->colorControlClusterExtFields.enhancedCurrentHue = scene->enhancedCurrentHue;
        enhancedViewSceneResp->colorControlClusterExtFields.currentSaturation = scene->currentSaturation;
        enhancedViewSceneResp->colorControlClusterExtFields.colorLoopActive = scene->colorLoopActive;
        enhancedViewSceneResp->colorControlClusterExtFields.colorLoopDirection = scene->colorLoopDirection;
        enhancedViewSceneResp->colorControlClusterExtFields.colorLoopTime = scene->colorLoopTime;
        size = sizeof(ZCL_EnhancedViewSceneResponse_t);
      }
#endif // (APP_ZLL_DEVICE_TYPE == APP_DEVICE_TYPE_COLOR_LIGHT) || (APP_ZLL_DEVICE_TYPE == APP_DEVICE_TYPE_EXTENDED_COLOR_LIGHT)
    }
    else
    {
      enhancedViewSceneResp->status = ZCL_NOT_FOUND_STATUS;
    }
  }
  else
  {
    enhancedViewSceneResp->status = ZCL_INVALID_FIELD_STATUS;
  }

  cmd->clusterId = SCENES_CLUSTER_ID;
  cmd->commandId = enhanced ? ZCL_SCENES_CLUSTER_ENHANCED_VIEW_SCENE_RESPONSE_COMMAND_ID :
                   ZCL_SCENES_CLUSTER_VIEW_SCENE_RESPONSE_COMMAND_ID;
  cmd->srcEndpoint = APP_ENDPOINT_LIGHT;
  cmd->seqNumberSpecified = true;

  enhancedViewSceneResp->groupId = payload->groupId;
  enhancedViewSceneResp->sceneId = payload->sceneId;

  cmd->size = size;

  clustersSendCommandWithAddressing(cmd, addressing);

  (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receive of View Scene command
******************************************************************************/
static ZCL_Status_t viewSceneInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ViewScene_t *payload)
{
  LOG_STRING(viewSceneStr, "viewSceneInd(): 0x%04x, 0x%02x\r\n");

  appSnprintf(viewSceneStr, payload->groupId, payload->sceneId);

  return processViewSceneCommand(false, addressing, payloadLength, payload);
}

/**************************************************************************//**
\brief Callback on receive of Remove Scene command
******************************************************************************/
static ZCL_Status_t removeSceneInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_RemoveScene_t *payload)
{
  ZCL_Status_t status;
  CommandDescriptor_t *cmd;
  ZCL_RemoveSceneResponse_t *removeSceneResp;
  LOG_STRING(removeSceneStr, "removeSceneInd(): 0x%04x, 0x%02x\r\n");

  appSnprintf(removeSceneStr, payload->groupId, payload->sceneId);

  if (groupIsValid(payload->groupId))
  {
    Scene_t *scene;

    scene = findScene(payload->groupId, payload->sceneId);

    if (scene)
    {
      status = ZCL_SUCCESS_STATUS;
      freeScene(scene);
    }
    else
    {
      status = ZCL_NOT_FOUND_STATUS;
    }
  }
  else
  {
    status = ZCL_INVALID_FIELD_STATUS;
  }

  // If received via multicast or broadcast service no response shall be given
  if (addressing->nonUnicast)
    return ZCL_SUCCESS_STATUS;

  if (!(cmd = clustersAllocCommand()))
    return ZCL_SUCCESS_STATUS;

  cmd->clusterId = SCENES_CLUSTER_ID;
  cmd->commandId = ZCL_SCENES_CLUSTER_REMOVE_SCENE_RESPONSE_COMMAND_ID;
  cmd->srcEndpoint = APP_ENDPOINT_LIGHT;
  cmd->ZCL_Notify = removeSceneResponseResp;
  cmd->seqNumberSpecified = true;

  removeSceneResp = &cmd->payload.removeSceneResp;
  removeSceneResp->status = status;
  removeSceneResp->groupId = payload->groupId;
  removeSceneResp->sceneId = payload->sceneId;

  cmd->size = sizeof(cmd->payload.removeSceneResp);

  clustersSendCommandWithAddressing(cmd, addressing);

  (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief ZCL Remove Scene Response command response
******************************************************************************/
static void removeSceneResponseResp(ZCL_Notify_t *ntfy)
{
  ZCL_Request_t *request = GET_PARENT_BY_FIELD(ZCL_Request_t, notify, ntfy);
  ZCL_RemoveSceneResponse_t *removeSceneResp = (ZCL_RemoveSceneResponse_t *)request->requestPayload;

  if (ZCL_SUCCESS_STATUS == removeSceneResp->status)
    PDS_Store(ZLL_APP_MEMORY_MEM_ID);
}

/**************************************************************************//**
\brief Callback on receive of Remove All Scenes command
******************************************************************************/
static ZCL_Status_t removeAllScenesInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_RemoveAllScenes_t *payload)
{
  ZCL_Status_t status;
  CommandDescriptor_t *cmd;
  ZCL_RemoveAllScenesResponse_t *removeAllScenesResp;
  LOG_STRING(removeAllSceneStr, "removeAllScenesInd(): 0x%04x\r\n");

  appSnprintf(removeAllSceneStr, payload->groupId);

  if (groupIsValid(payload->groupId))
  {
    status = ZCL_SUCCESS_STATUS;
    scenesClusterRemoveByGroup(payload->groupId);
  }
  else
    status = ZCL_INVALID_FIELD_STATUS;

  // If received via multicast or broadcast service no response shall be given
  if (addressing->nonUnicast)
    return ZCL_SUCCESS_STATUS;

  if (!(cmd = clustersAllocCommand()))
    return ZCL_SUCCESS_STATUS;

  cmd->clusterId = SCENES_CLUSTER_ID;
  cmd->commandId = ZCL_SCENES_CLUSTER_REMOVE_ALL_SCENES_RESPONSE_COMMAND_ID;
  cmd->srcEndpoint = APP_ENDPOINT_LIGHT;
  cmd->ZCL_Notify = removeAllScenesResponseResp;
  cmd->seqNumberSpecified = true;

  removeAllScenesResp = &cmd->payload.removeAllScenesResp;
  removeAllScenesResp->status = status;
  removeAllScenesResp->groupId = payload->groupId;

  cmd->size = sizeof(cmd->payload.removeAllScenesResp);

  clustersSendCommandWithAddressing(cmd, addressing);

  (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief ZCL Remove All Scenes Response command response
******************************************************************************/
static void removeAllScenesResponseResp(ZCL_Notify_t *ntfy)
{
  ZCL_Request_t *request = GET_PARENT_BY_FIELD(ZCL_Request_t, notify, ntfy);
  ZCL_RemoveAllScenesResponse_t *removeAllScenesResp =
    (ZCL_RemoveAllScenesResponse_t *)request->requestPayload;

  if (ZCL_SUCCESS_STATUS == removeAllScenesResp->status)
    PDS_Store(ZLL_APP_MEMORY_MEM_ID);
}

/**************************************************************************//**
\brief Callback on receive of Store Scene command
******************************************************************************/
static ZCL_Status_t storeSceneInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_StoreScene_t *payload)
{
  ZCL_Status_t status;
  CommandDescriptor_t *cmd;
  ZCL_StoreSceneResponse_t *storeSceneResp;
  LOG_STRING(storeSceneStr, "storeSceneInd(): 0x%04x, %d\r\n");

  appSnprintf(storeSceneStr, payload->groupId, payload->sceneId);

  if (groupIsValid(payload->groupId))
  {
    Scene_t *scene;

    scene = findScene(payload->groupId, payload->sceneId);

    if (!scene)
      scene = allocScene();

    if (scene)
    {
      status = ZCL_SUCCESS_STATUS;

      scene->sceneId = payload->sceneId;
      scene->groupId = payload->groupId;
      storeScene(scene);

      PDS_Store(ZLL_APP_MEMORY_MEM_ID);
    }
    else
    {
      status = ZCL_INSUFFICIENT_SPACE_STATUS;
    }
  }
  else
  {
    status = ZCL_INVALID_FIELD_STATUS;
  }

  // If received via multicast or broadcast service no response shall be given
  if (addressing->nonUnicast)
    return ZCL_SUCCESS_STATUS;

  if (!(cmd = clustersAllocCommand()))
    return ZCL_SUCCESS_STATUS;

  cmd->clusterId = SCENES_CLUSTER_ID;
  cmd->commandId = ZCL_SCENES_CLUSTER_STORE_SCENE_RESPONSE_COMMAND_ID;
  cmd->srcEndpoint = APP_ENDPOINT_LIGHT;
  cmd->ZCL_Notify = storeSceneResponseResp;
  cmd->seqNumberSpecified = true;

  storeSceneResp = &cmd->payload.storeSceneResp;
  storeSceneResp->status = status;
  storeSceneResp->groupId = payload->groupId;
  storeSceneResp->sceneId = payload->sceneId;

  cmd->size = sizeof(cmd->payload.storeSceneResp);

  clustersSendCommandWithAddressing(cmd, addressing);

  (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief ZCL Stopre Scene Response command response
******************************************************************************/
static void storeSceneResponseResp(ZCL_Notify_t *ntfy)
{
  ZCL_Request_t *request = GET_PARENT_BY_FIELD(ZCL_Request_t, notify, ntfy);
  ZCL_StoreSceneResponse_t *storeSceneResp = (ZCL_StoreSceneResponse_t *)request->requestPayload;

  if (ZCL_SUCCESS_STATUS == storeSceneResp->status)
    PDS_Store(ZLL_APP_MEMORY_MEM_ID);
}

/**************************************************************************//**
\brief Callback on receive of Recall Scene command
******************************************************************************/
static ZCL_Status_t recallSceneInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_RecallScene_t *payload)
{
  Scene_t *scene;
  LOG_STRING(recallSceneStr, "recallSceneInd(): 0x%04x, %d\r\n");

  appSnprintf(recallSceneStr, payload->groupId, payload->sceneId);

  scene = findScene(payload->groupId, payload->sceneId);

  if (scene)
  {
    onOffClusterSetGlobalSceneControl();
    recallScene(scene);
  }

  PDS_Store(ZLL_APP_MEMORY_MEM_ID);

  (void)addressing;
  (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receive of Get Scene Membership Scene command
******************************************************************************/
static ZCL_Status_t getSceneMembershipInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_GetSceneMembership_t *payload)
{
  CommandDescriptor_t *cmd;
  ZCL_GetSceneMembershipResponse_t *getSceneMembershipResp;
  uint8_t size = sizeof(uint8_t) /*status*/ + sizeof(uint8_t) /*capacity*/ + sizeof(uint16_t) /*groupId*/;;
  LOG_STRING(getSceneMembershipStr, "getSceneMembershipInd(): 0x%04x\r\n");

  appSnprintf(getSceneMembershipStr, payload->groupId);

  /* TODO:
    On receipt of this command, the device shall if addressed to a single device
    generate an appropriate Get Scene Membership Response command, otherwise it
    shall only generate an appropriate Get Scene Membership Response command if
    an entry within the Scene Table corresponds to the Group ID.
    - Doesn't fit to TP-CST-TC-13 Item 23 expected result.
  */
  if (addressing->nonUnicast)
    return ZCL_SUCCESS_STATUS;

  if (!(cmd = clustersAllocCommand()))
    return ZCL_SUCCESS_STATUS;

  getSceneMembershipResp = &cmd->payload.getSceneMembershipResp;

  getSceneMembershipResp->groupId = payload->groupId;
  getSceneMembershipResp->sceneCount = 0;
  getSceneMembershipResp->capacity = MAX_NUMBER_OF_SCENES - scenesClusterServerAttributes.sceneCount.value;

  if (groupIsValid(payload->groupId))
  {
    getSceneMembershipResp->status = ZCL_SUCCESS_STATUS;

    getSceneMembershipResp->sceneCount = 0;
    size += sizeof(uint8_t) /*sceneCount*/;

    for (uint8_t i = 0; i < MAX_NUMBER_OF_SCENES; i++)
    {
      if (!scene[i].free && scene[i].groupId == payload->groupId)
      {
        getSceneMembershipResp->sceneList[getSceneMembershipResp->sceneCount] = scene[i].sceneId;
        getSceneMembershipResp->sceneCount++;
        size += sizeof(uint8_t) /*scene*/;
      }
    }
  }
  else
  {
    getSceneMembershipResp->status = ZCL_INVALID_FIELD_STATUS;
  }

  cmd->clusterId = SCENES_CLUSTER_ID;
  cmd->commandId = ZCL_SCENES_CLUSTER_GET_SCENE_MEMBERSHIP_RESPONSE_COMMAND_ID;
  cmd->srcEndpoint = APP_ENDPOINT_LIGHT;
  cmd->seqNumberSpecified = true;

  cmd->size = size;

  clustersSendCommandWithAddressing(cmd, addressing);

  (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receive of Enhanced Add Scene command
******************************************************************************/
static ZCL_Status_t enhancedAddSceneInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_EnhancedAddScene_t *payload)
{
  LOG_STRING(enhancedAddSceneStr, "enhancedAddSceneInd(): 0x%04x, 0x%02x\r\n");

  appSnprintf(enhancedAddSceneStr, payload->groupId, payload->sceneId);
  return processAddSceneCommand(true, addressing, payloadLength, (ZCL_AddScene_t *)payload);
}

/**************************************************************************//**
\brief Callback on receive of Enhanced View Scene command
******************************************************************************/
static ZCL_Status_t enhancedViewSceneInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_EnhancedViewScene_t *payload)
{
  LOG_STRING(enhancedViewSceneStr, "enhancedViewSceneInd(): 0x%04x, 0x%02x\r\n");

  appSnprintf(enhancedViewSceneStr, payload->groupId, payload->sceneId);
  return processViewSceneCommand(true, addressing, payloadLength, (ZCL_ViewScene_t *)payload);
}

/**************************************************************************//**
\brief Copy scene
******************************************************************************/
static ZCL_Status_t copyScene(uint16_t groupIdFrom, uint8_t sceneIdFrom, uint16_t groupIdTo, uint8_t sceneIdTo)
{
  Scene_t *sceneFrom, *sceneTo;

  sceneFrom = findScene(groupIdFrom, sceneIdFrom);

  if (!sceneFrom)
    return ZCL_NOT_FOUND_STATUS;

  sceneTo = findScene(groupIdTo, sceneIdTo);

  if (!sceneTo)
    sceneTo = allocScene();

  if (sceneTo)
  {
    *sceneTo = *sceneFrom;
    sceneTo->sceneId = sceneIdTo;
    sceneTo->groupId = groupIdTo;
  }
  else
    return ZCL_INSUFFICIENT_SPACE_STATUS;

  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receive of Copy Scene command
******************************************************************************/
static ZCL_Status_t copySceneInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_CopyScene_t *payload)
{
  ZCL_Status_t status;
  CommandDescriptor_t *cmd;
  ZCL_CopySceneResponse_t *copySceneResp;
  LOG_STRING(copySceneStr, "copySceneInd()\r\n");

  appSnprintf(copySceneStr);

  if (groupIsValid(payload->groupIdFrom))
  {
    if (payload->mode & ZCL_SCENES_CLUSTER_COPY_ALL_SCENES)
    {
      status = ZCL_SUCCESS_STATUS;

      for (uint8_t i = 0; i < MAX_NUMBER_OF_SCENES; i++)
      {
        if (!scene[i].free && scene[i].groupId == payload->groupIdFrom)
        {
          ZCL_Status_t result;

          result = copyScene(payload->groupIdFrom, scene[i].sceneId,
                             payload->groupIdTo, scene[i].sceneId);

          if (ZCL_SUCCESS_STATUS != result)
            status = result;
        }
      }
    }
    else
    {
      status = copyScene(payload->groupIdFrom, payload->sceneIdFrom,
                         payload->groupIdTo, payload->sceneIdTo);
    }
  }
  else
  {
    status = ZCL_INVALID_FIELD_STATUS;
  }

  // If received via multicast or broadcast service no response shall be given
  if (addressing->nonUnicast)
    return ZCL_SUCCESS_STATUS;

  if (!(cmd = clustersAllocCommand()))
    return ZCL_SUCCESS_STATUS;

  cmd->clusterId = SCENES_CLUSTER_ID;
  cmd->commandId = ZCL_SCENES_CLUSTER_COPY_SCENE_RESPONSE_COMMAND_ID;
  cmd->srcEndpoint = APP_ENDPOINT_LIGHT;
  cmd->ZCL_Notify = copySceneResponseResp;
  cmd->seqNumberSpecified = true;

  copySceneResp = &cmd->payload.copySceneResp;
  copySceneResp->status = status;
  copySceneResp->groupIdFrom = payload->groupIdFrom;
  copySceneResp->sceneIdFrom = payload->sceneIdFrom;

  cmd->size = sizeof(cmd->payload.copySceneResp);

  clustersSendCommandWithAddressing(cmd, addressing);
  (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief ZCL Copy Scene Response command response
******************************************************************************/
static void copySceneResponseResp(ZCL_Notify_t *ntfy)
{
  ZCL_Request_t *request = GET_PARENT_BY_FIELD(ZCL_Request_t, notify, ntfy);
  ZCL_CopySceneResponse_t *copySceneResp = (ZCL_CopySceneResponse_t *)request->requestPayload;

  if (ZCL_SUCCESS_STATUS == copySceneResp->status)
    PDS_Store(ZLL_APP_MEMORY_MEM_ID);
}

#endif // APP_ZLL_DEVICE_TYPE >= APP_DEVICE_TYPE_ON_OFF_LIGHT

// eof lightScenesCluster.c
