/**************************************************************************//**
  \file dlScenesCluster.c

  \brief
    Dimmable Light Scenes cluster implementation.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    11.12.12 N. Fomin - Created.
******************************************************************************/
#ifdef APP_DEVICE_TYPE_DIMMABLE_LIGHT

/******************************************************************************
                    Includes section
******************************************************************************/
#include <dlScenesCluster.h>
#include <dlScenes.h>
#include <dlOnOffCluster.h>
#include <dlLevelControlCluster.h>
#include <haClusters.h>
#include <uartManager.h>
#include <commandManager.h>
#include <pdsDataServer.h>

/******************************************************************************
                    Definitions section
******************************************************************************/
#define GLOBAL_SCENE_SCENE_ID 0u
#define GLOBAL_SCENE_GROUP_ID 0u

/******************************************************************************
                    Prototypes section
******************************************************************************/
static ZCL_Status_t addSceneInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_AddScene_t *payload);
static ZCL_Status_t viewSceneInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ViewScene_t *payload);
static ZCL_Status_t removeSceneInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_RemoveScene_t *payload);
static ZCL_Status_t removeAllScenesInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_RemoveAllScenes_t *payload);
static ZCL_Status_t storeSceneInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_StoreScene_t *payload);
static ZCL_Status_t recallSceneInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_RecallScene_t *payload);
static ZCL_Status_t getSceneMembershipInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_GetSceneMembership_t *payload);

static void dlFillAddRemoveStoreSceneResponsePayload(ZCL_AddSceneResponse_t *payload, uint16_t group, uint8_t scene, uint8_t status);
static uint8_t dlFillViewSceneResponsePayload(ZCL_ViewSceneResponse_t *payload, Scene_t *scene, uint8_t status, ZCL_ViewScene_t *request);
static void dlFillRemoveAllScenesResponsePayload(ZCL_RemoveAllScenesResponse_t *payload, uint16_t group, uint8_t status);
static uint8_t dlFillGetSceneMembershipPayload(ZCL_GetSceneMembershipResponse_t *payload, uint16_t group);

static bool isValidGroup(uint16_t group);
static ZCL_Status_t extractSceneInfo(ZCL_AddScene_t *payload, Scene_t *scene, uint8_t length);

static ZCL_Status_t addScene(ZCL_AddScene_t *addScene, uint8_t payloadLength);
static ZCL_Status_t viewScene(ZCL_ViewScene_t *viewScene, Scene_t **scene);
static ZCL_Status_t removeScene(ZCL_RemoveScene_t *removeScene);
static ZCL_Status_t removeAllScenes(uint16_t group);
static ZCL_Status_t storeScene(ZCL_StoreScene_t *storeScene);
static void recallScene(ZCL_RecallScene_t *recallScene);

/******************************************************************************
                    Global variables section
******************************************************************************/
ZCL_SceneClusterServerAttributes_t dlScenesClusterServerAttributes =
{
  ZCL_DEFINE_SCENES_CLUSTER_SERVER_ATTRIBUTES()
};
ZCL_ScenesClusterCommands_t        dlScenesCommands =
{
  ZCL_DEFINE_SCENES_CLUSTER_COMMANDS(addSceneInd, viewSceneInd, removeSceneInd, removeAllScenesInd,
                                     storeSceneInd, recallSceneInd, getSceneMembershipInd,
                                     NULL, NULL, NULL, NULL, NULL, NULL)
};

/******************************************************************************
                    Implementation section
******************************************************************************/
/**************************************************************************//**
\brief Initializes Scenes cluster
******************************************************************************/
void scenesClusterInit(void)
{
  dlScenesClusterServerAttributes.sceneCount.value   = 0;
  dlScenesClusterServerAttributes.currentScene.value = 0;
  dlScenesClusterServerAttributes.currentGroup.value = 0;
  dlScenesClusterServerAttributes.sceneValid.value   = true;
  dlScenesClusterServerAttributes.nameSupport.value  = 0;

  initScenes();
}

/**************************************************************************//**
\brief Invalidates scene
******************************************************************************/
void scenesInvalidate(void)
{
  dlScenesClusterServerAttributes.sceneValid.value = false;
}

/**************************************************************************//**
\brief Removes all scenes from scene table

\param[in] group - group id

\returns status of scene removing
******************************************************************************/
ZCL_Status_t removeAllScenes(uint16_t group)
{
  if (isValidGroup(group))
    dlScenesClusterServerAttributes.sceneCount.value -= removeScenesByGroup(group);
  else
    return ZCL_INVALID_FIELD_STATUS;

  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receiving Add Scene command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
static ZCL_Status_t addSceneInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_AddScene_t *payload)
{
  ZCL_Status_t status;
  ZCL_Request_t *req;

  LOG_STRING(addSceneStr, "addSceneInd(): 0x%04x, 0x%02x\r\n");
  appSnprintf(addSceneStr, payload->groupId, payload->sceneId);

  status = addScene(payload, payloadLength);

  // Update scenes in non-volatile memory
  if (ZCL_SUCCESS_STATUS == status)
    PDS_Store(APP_DL_SCENES_MEM_ID);

  // If received via multicast or broadcast service no response shall be given
  if (addressing->nonUnicast)
    return ZCL_SUCCESS_STATUS;

  if (!(req = getFreeCommand()))
    return ZCL_INSUFFICIENT_SPACE_STATUS;

  fillCommandRequest(req, ZCL_SCENES_CLUSTER_ADD_SCENE_RESPONSE_COMMAND_ID,
                       sizeof(ZCL_AddSceneResponse_t));
  dlFillAddRemoveStoreSceneResponsePayload((ZCL_AddSceneResponse_t *)req->requestPayload, payload->groupId, payload->sceneId, status);
  fillDstAddressingViaSourceAddressing(&req->dstAddressing, addressing, ZCL_CLUSTER_SIDE_CLIENT);
  commandManagerSendCommand(req);

  (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receiving View Scene command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
static ZCL_Status_t viewSceneInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ViewScene_t *payload)
{
  ZCL_Status_t status;
  ZCL_Request_t *req;
  uint8_t size;
  Scene_t *scene;

  LOG_STRING(viewSceneStr, "viewSceneInd(): 0x%04x, 0x%02x\r\n");
  appSnprintf(viewSceneStr, payload->groupId, payload->sceneId);

  // If received via multicast or broadcast service no response shall be given
  if (addressing->nonUnicast)
    return ZCL_SUCCESS_STATUS;

  if (!(req = getFreeCommand()))
    return ZCL_INSUFFICIENT_SPACE_STATUS;

  status = viewScene(payload, &scene);

  size = dlFillViewSceneResponsePayload((ZCL_ViewSceneResponse_t *)req->requestPayload, scene, status, payload);
  fillCommandRequest(req, ZCL_SCENES_CLUSTER_VIEW_SCENE_RESPONSE_COMMAND_ID,
                       size);
  fillDstAddressingViaSourceAddressing(&req->dstAddressing, addressing, ZCL_CLUSTER_SIDE_CLIENT);
  commandManagerSendCommand(req);

  (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receiving Remove Scene command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
static ZCL_Status_t removeSceneInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_RemoveScene_t *payload)
{
  ZCL_Status_t status;
  ZCL_Request_t *req;

  LOG_STRING(removeSceneStr, "removeSceneInd(): 0x%04x, 0x%02x\r\n");
  appSnprintf(removeSceneStr, payload->groupId, payload->sceneId);

  status = removeScene(payload);

  // Update scenes in non-volatile memory
  if (ZCL_SUCCESS_STATUS == status)
    PDS_Store(APP_DL_SCENES_MEM_ID);

  // If received via multicast or broadcast service no response shall be given
  if (addressing->nonUnicast)
    return ZCL_SUCCESS_STATUS;

  if (!(req = getFreeCommand()))
    return ZCL_INSUFFICIENT_SPACE_STATUS;

  fillCommandRequest(req, ZCL_SCENES_CLUSTER_REMOVE_SCENE_RESPONSE_COMMAND_ID,
                       sizeof(ZCL_RemoveSceneResponse_t));
  dlFillAddRemoveStoreSceneResponsePayload((ZCL_AddSceneResponse_t *)req->requestPayload, payload->groupId, payload->sceneId, status);
  fillDstAddressingViaSourceAddressing(&req->dstAddressing, addressing, ZCL_CLUSTER_SIDE_CLIENT);
  commandManagerSendCommand(req);

  (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receiving Remove All Scenes command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
static ZCL_Status_t removeAllScenesInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_RemoveAllScenes_t *payload)
{
  ZCL_Status_t status;
  ZCL_Request_t *req;

  LOG_STRING(removeAllScenesStr, "removeAllScenesInd(): 0x%04x\r\n");
  appSnprintf(removeAllScenesStr, payload->groupId);

  status = removeAllScenes(payload->groupId);

  // Update scenes in non-volatile memory
  if (ZCL_SUCCESS_STATUS == status)
    PDS_Store(APP_DL_SCENES_MEM_ID);

  // If received via multicast or broadcast service no response shall be given
  if (addressing->nonUnicast)
    return ZCL_SUCCESS_STATUS;

  if (!(req = getFreeCommand()))
    return ZCL_INSUFFICIENT_SPACE_STATUS;

  fillCommandRequest(req, ZCL_SCENES_CLUSTER_REMOVE_ALL_SCENES_RESPONSE_COMMAND_ID,
                       sizeof(ZCL_RemoveAllScenesResponse_t));
  dlFillRemoveAllScenesResponsePayload((ZCL_RemoveAllScenesResponse_t *)req->requestPayload, payload->groupId, status);
  fillDstAddressingViaSourceAddressing(&req->dstAddressing, addressing, ZCL_CLUSTER_SIDE_CLIENT);
  commandManagerSendCommand(req);

  (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receiving Store Scene command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
static ZCL_Status_t storeSceneInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_StoreScene_t *payload)
{
  ZCL_Status_t status;
  ZCL_Request_t *req;

  LOG_STRING(storeSceneStr, "storeSceneInd(): 0x%04x, %d\r\n");
  appSnprintf(storeSceneStr, payload->groupId, payload->sceneId);

  status = storeScene(payload);

  // Update scenes in non-volatile memory
  if (ZCL_SUCCESS_STATUS == status)
    PDS_Store(APP_DL_SCENES_MEM_ID);

  // If received via multicast or broadcast service no response shall be given
  if (addressing->nonUnicast)
    return ZCL_SUCCESS_STATUS;

  if (!(req = getFreeCommand()))
    return ZCL_INSUFFICIENT_SPACE_STATUS;

  fillCommandRequest(req, ZCL_SCENES_CLUSTER_STORE_SCENE_RESPONSE_COMMAND_ID,
                       sizeof(ZCL_StoreSceneResponse_t));
  dlFillAddRemoveStoreSceneResponsePayload((ZCL_AddSceneResponse_t *)req->requestPayload, payload->groupId, payload->sceneId, status);
  fillDstAddressingViaSourceAddressing(&req->dstAddressing, addressing, ZCL_CLUSTER_SIDE_CLIENT);
  commandManagerSendCommand(req);

  (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receiving Recall Scene command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
static ZCL_Status_t recallSceneInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_RecallScene_t *payload)
{
  LOG_STRING(recallSceneStr, "recallSceneInd(): 0x%04x, %d\r\n");
  appSnprintf(recallSceneStr, payload->groupId, payload->sceneId);

  recallScene(payload);

  (void)addressing, (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receiving Get Scenes Membership command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
static ZCL_Status_t getSceneMembershipInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_GetSceneMembership_t *payload)
{
  uint8_t size;
  ZCL_Request_t *req;

  LOG_STRING(getSceneMembershipStr, "getSceneMembershipInd(): 0x%04x\r\n");
  appSnprintf(getSceneMembershipStr, payload->groupId);

  /* A response should be sent if the request is unicast or (the request is broadcast
      and scene(s) for given group exist(s)) */
  if (!(!addressing->nonUnicast ||
    (addressing->nonUnicast && isValidGroup(payload->groupId) && getNextSceneByGroup(NULL, payload->groupId))))
    return ZCL_SUCCESS_STATUS;

  if (!(req = getFreeCommand()))
    return ZCL_INSUFFICIENT_SPACE_STATUS;

  size = dlFillGetSceneMembershipPayload((ZCL_GetSceneMembershipResponse_t *)req->requestPayload, payload->groupId);
  fillCommandRequest(req, ZCL_SCENES_CLUSTER_GET_SCENE_MEMBERSHIP_RESPONSE_COMMAND_ID,
                       size);
  fillDstAddressingViaSourceAddressing(&req->dstAddressing, addressing, ZCL_CLUSTER_SIDE_CLIENT);
  commandManagerSendCommand(req);

  (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Fills Add Scene Response command structure

\param[out] payload - pointer to command structure;
\param[in]  group   - group id;
\param[in]  scene   - scene id;
\param[in]  status  - the status of scene adding
******************************************************************************/
static void dlFillAddRemoveStoreSceneResponsePayload(ZCL_AddSceneResponse_t *payload, uint16_t group, uint8_t scene, uint8_t status)
{
  payload->status  = status;
  payload->groupId = group;
  payload->sceneId = scene;
}

/**************************************************************************//**
\brief Fills View Scene Response command structure

\param[out] payload - pointer to command structure;
\param[in]  scene   - scene info;
\param[in]  status  - the status of scene viewing;
\param[in] request  - the pointer to appropriate View Scene request

\returns size of payload in octets
******************************************************************************/
static uint8_t dlFillViewSceneResponsePayload(ZCL_ViewSceneResponse_t *payload, Scene_t *scene, uint8_t status, ZCL_ViewScene_t *request)
{
  ZCL_OnOffClusterExtensionFieldSet_t    *onOffExt;
  ZCL_LevelControlSceneExtensionFields_t *levelControlExt;
  uint8_t                                *tmp;

  payload->status  = status;
  payload->groupId = request->groupId;
  payload->sceneId = request->sceneId;

  if (ZCL_SUCCESS_STATUS != status)
    return sizeof(ZCL_ViewSceneResponse_t) - sizeof(uint16_t) /*transitionTime*/ - sizeof(uint8_t); /*nameAndExtField*/

  payload->transitionTime     = scene->transitionTime;
  payload->nameAndExtField[0] = 0;

  onOffExt = (ZCL_OnOffClusterExtensionFieldSet_t *)&payload->nameAndExtField[1];
  onOffExt->clusterId  = ONOFF_CLUSTER_ID;
  onOffExt->length     = sizeof(ZCL_OnOffClusterExtensionFieldSet_t) - sizeof(ZCL_ExtensionFieldSets_t);
  onOffExt->onOffValue = scene->onOff;

  tmp = (uint8_t *)&payload->nameAndExtField[1] + sizeof(ZCL_OnOffClusterExtensionFieldSet_t);
  levelControlExt = (ZCL_LevelControlSceneExtensionFields_t *)tmp;

  levelControlExt->clusterId    = LEVEL_CONTROL_CLUSTER_ID;
  levelControlExt->length       = sizeof(ZCL_LevelControlSceneExtensionFields_t) - sizeof(ZCL_ExtensionFieldSets_t);
  levelControlExt->currentLevel = scene->currentLevel;

  return sizeof(ZCL_ViewSceneResponse_t) + sizeof(ZCL_OnOffClusterExtensionFieldSet_t) + sizeof(ZCL_LevelControlSceneExtensionFields_t);
}

/**************************************************************************//**
\brief Fills Remove Scene Response command structure

\param[out] payload - pointer to command structure;
\param[in]  group   - group id;
\param[in]  status  - the status of scenes removing
******************************************************************************/
static void dlFillRemoveAllScenesResponsePayload(ZCL_RemoveAllScenesResponse_t *payload, uint16_t group, uint8_t status)
{
  payload->status  = status;
  payload->groupId = group;
}

/**************************************************************************//**
\brief Fills Get Scene Membership command structure

\param[out] payload - pointer to command structure;
\param[in]  group   - group id;
******************************************************************************/
static uint8_t dlFillGetSceneMembershipPayload(ZCL_GetSceneMembershipResponse_t *payload, uint16_t group)
{
  payload->capacity = MAX_SCENES_AMOUNT - dlScenesClusterServerAttributes.sceneCount.value;
  payload->groupId  = group;

  if (isValidGroup(group))
  {
    Scene_t *scene = NULL;

    while ((scene = getNextSceneByGroup(scene, group)))
      payload->sceneList[payload->sceneCount++] = scene->sceneId;
    payload->status = ZCL_SUCCESS_STATUS;
  }
  else
  {
    payload->status = ZCL_INVALID_FIELD_STATUS;
    return sizeof(ZCL_GetSceneMembershipResponse_t) - sizeof(uint8_t) /*sceneCount*/ - sizeof(uint8_t); /*sceneList*/
  }

  return sizeof(ZCL_GetSceneMembershipResponse_t) + payload->sceneCount - sizeof(uint8_t); /*sceneList*/
}

/**************************************************************************//**
\brief Checks whether given group id is a group id that exists on this device

\param[in] group - group id

\returns true if group id exists on this device, false otherwise
******************************************************************************/
static bool isValidGroup(uint16_t group)
{
  return (group == 0 || NWK_IsGroupMember(group, APP_SRC_ENDPOINT_ID));
}

/**************************************************************************//**
\brief Extracts scene information from received packet and fills scene structure

\param[in]  payload - received packet payload
\param[out] scene   - scene to be filled
******************************************************************************/
static ZCL_Status_t extractSceneInfo(ZCL_AddScene_t *payload, Scene_t *scene, uint8_t length)
{
  int16_t commandSize  = sizeof(ZCL_AddScene_t) + payload->name[0];
  int16_t extFieldSize = (int16_t)length - commandSize;
  uint8_t *extFields   = (uint8_t *)payload + commandSize;
  ZCL_ExtensionFieldSets_t *ext;

  scene->sceneId        = payload->sceneId;
  scene->groupId        = payload->groupId;
  scene->transitionTime = payload->transitionTime;

  while (extFieldSize)
  {
    ext = (ZCL_ExtensionFieldSets_t *)extFields;

    if (ONOFF_CLUSTER_ID == ext->clusterId)
    {
      ZCL_OnOffClusterExtensionFieldSet_t *ext = (ZCL_OnOffClusterExtensionFieldSet_t *)extFields;

      scene->onOff = ext->onOffValue;
    }
    else if (LEVEL_CONTROL_CLUSTER_ID == ext->clusterId)
    {
      ZCL_LevelControlSceneExtensionFields_t *ext =
        (ZCL_LevelControlSceneExtensionFields_t *)extFields;

      scene->currentLevel = ext->currentLevel;
    }
    else
      return ZCL_INVALID_FIELD_STATUS;

    extFields += sizeof(ZCL_ExtensionFieldSets_t) + ext->length;
    extFieldSize -= (sizeof(ZCL_ExtensionFieldSets_t) + ext->length);
  }

  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Adds scene to scene table

\param[in] addScene      - the pointer to Add Scene request;
\param[in] payloadLength - the length of request

\returns status of scene adding
******************************************************************************/
static ZCL_Status_t addScene(ZCL_AddScene_t *addScene, uint8_t payloadLength)
{
  Scene_t *scene;

  if (isValidGroup(addScene->groupId))
  {
    scene = findSceneBySceneAndGroup(addScene->groupId, addScene->sceneId);
    if (!scene)
      scene = allocateScene();

    if (scene)
    {
      dlScenesClusterServerAttributes.sceneCount.value++;
      return extractSceneInfo(addScene, scene, payloadLength);
    }
    else
      return ZCL_INSUFFICIENT_SPACE_STATUS;
  }

  return ZCL_INVALID_FIELD_STATUS;
}

/**************************************************************************//**
\brief Views scene in scene table

\param[in] viewScene - the pointer to View Scene request;
\param[in] scene     - the pointer to the pointer to scene

\returns status of scene viewing
******************************************************************************/
static ZCL_Status_t viewScene(ZCL_ViewScene_t *viewScene, Scene_t **scene)
{
  if (isValidGroup(viewScene->groupId))
  {
    *scene = findSceneBySceneAndGroup(viewScene->groupId, viewScene->sceneId);
    if (!(*scene))
      return ZCL_NOT_FOUND_STATUS;
    else
      return ZCL_SUCCESS_STATUS;
  }

  return ZCL_INVALID_FIELD_STATUS;
}

/**************************************************************************//**
\brief Removes scene from scene table

\param[in] removeScene - the pointer to Remove Scene request

\returns status of scene removing
******************************************************************************/
static ZCL_Status_t removeScene(ZCL_RemoveScene_t *removeScene)
{
  if (isValidGroup(removeScene->groupId))
  {
    Scene_t *scene;

    scene = findSceneBySceneAndGroup(removeScene->groupId, removeScene->sceneId);
    if (!scene)
      return ZCL_NOT_FOUND_STATUS;
    else
    {
      freeScene(scene);
      dlScenesClusterServerAttributes.sceneCount.value--;
      return ZCL_SUCCESS_STATUS;
    }
  }

  return ZCL_INVALID_FIELD_STATUS;
}

/**************************************************************************//**
\brief Stores scene to scene table

\param[in] storeScene - the pointer to Store Scene request

\returns status of scene storing
******************************************************************************/
static ZCL_Status_t storeScene(ZCL_StoreScene_t *storeScene)
{
  if (isValidGroup(storeScene->groupId))
  {
    Scene_t *scene;

    scene = findSceneBySceneAndGroup(storeScene->groupId, storeScene->sceneId);
    if (!scene)
      scene = allocateScene();

    if (scene)
    {
      dlScenesClusterServerAttributes.sceneCount.value++;

      scene->onOff          = onOffState();
      scene->currentLevel   = levelControlCurrentLevel();
      scene->transitionTime = 0;
      scene->groupId        = storeScene->groupId;
      scene->sceneId        = storeScene->sceneId;

      dlScenesClusterServerAttributes.currentScene.value = scene->sceneId;
      dlScenesClusterServerAttributes.currentGroup.value = scene->groupId;
      dlScenesClusterServerAttributes.sceneValid.value   = true;

      return ZCL_SUCCESS_STATUS;
    }
    else
      return ZCL_INSUFFICIENT_SPACE_STATUS;
  }

  return ZCL_INVALID_FIELD_STATUS;
}

/**************************************************************************//**
\brief Recalls scene from scene table

\param[in] recallScene - the pointer to Recall Scene request
******************************************************************************/
static void recallScene(ZCL_RecallScene_t *recallScene)
{
  Scene_t *scene = findSceneBySceneAndGroup(recallScene->groupId, recallScene->sceneId);

  if (scene)
  {
    onOffSetOnOffState(scene->onOff);
    levelControlSetLevel(scene->currentLevel);

    dlScenesClusterServerAttributes.currentScene.value = scene->sceneId;
    dlScenesClusterServerAttributes.currentGroup.value = scene->groupId;
    dlScenesClusterServerAttributes.sceneValid.value   = true;
    PDS_Store(APP_DL_SCENES_MEM_ID);
  }
}

#endif // APP_DEVICE_TYPE_DIMMABLE_LIGH
//eof dlScenesCluster.c