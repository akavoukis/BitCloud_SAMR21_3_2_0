/**************************************************************************//**
  \file ciScenesCluster.c

  \brief
    Combined Interface Scenes cluster implementation.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2013, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    04.09.13 N. Fomin - Created.
******************************************************************************/
#ifdef APP_DEVICE_TYPE_COMBINED_INTERFACE

/******************************************************************************
                    Includes section
******************************************************************************/
#include <ciScenesCluster.h>
#include <haClusters.h>
#include <zclOnOffCluster.h>
#include <zclLevelControlCluster.h>
#include <zclThermostatCluster.h>
#include <commandManager.h>
#include <uartManager.h>

/******************************************************************************
                    Prototypes section
******************************************************************************/
static ZCL_Status_t addSceneResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_AddSceneResponse_t *payload);
static ZCL_Status_t viewSceneResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ViewSceneResponse_t *payload);
static ZCL_Status_t removeSceneResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_RemoveSceneResponse_t *payload);
static ZCL_Status_t removeAllScenesResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_RemoveAllScenesResponse_t *payload);
static ZCL_Status_t storeSceneResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_StoreSceneResponse_t *payload);
static ZCL_Status_t getSceneMembershipResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_GetSceneMembershipResponse_t *payload);

static void ciFillAddSceneToDimmableLightPayload(ZCL_AddScene_t *payload, uint16_t group, uint8_t scene, uint16_t time, bool onOff, uint8_t level);
static void ciFillAddSceneToThermostatPayload(ZCL_AddScene_t *payload, uint16_t group, uint8_t scene, uint16_t time, 
                                              int16_t occupiedCoolingSetPoint, int16_t occupiedHeatingSetPoint, uint8_t systemMode);
static void ciFillViewRemoveStoreRecallScenePayload(ZCL_ViewScene_t *payload, uint16_t group, uint8_t scene);
static void ciFillRemoveAllScenesGetSceneMembershipPayload(ZCL_RemoveAllScenes_t *payload, uint16_t group);

/******************************************************************************
                    Global variables section
******************************************************************************/
ZCL_ScenesClusterCommands_t ciScenesCommands =
{
  ZCL_DEFINE_SCENES_CLUSTER_COMMANDS(NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                     addSceneResponseInd, viewSceneResponseInd, removeSceneResponseInd,
                                     removeAllScenesResponseInd, storeSceneResponseInd, getSceneMembershipResponseInd)
};

/******************************************************************************
                    Implementation section
******************************************************************************/
/**************************************************************************//**
\brief Initializes Scenes cluster
******************************************************************************/
void scenesClusterInit(void)
{}

/**************************************************************************//**
\brief Sends Add Scene command to bound Dimmable Light device

\param[in] mode  - address mode;
\param[in] addr  - short address of destination node or number of group;
\param[in] ep    - endpoint number of destination device;
\param[in] group - group id;
\param[in] scene - scene id;
\param[in] time  - transition time;
\param[in] onOff - onOff extenstion filed value;
\param[in] level - currentLevel extension field value
******************************************************************************/
void scenesSendAddSceneToDimmableLight(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep,
  uint16_t group, uint8_t scene, uint16_t time, bool onOff, uint8_t level)
{
  ZCL_Request_t *req;

  if (!(req = getFreeCommand()))
    return;

  fillCommandRequest(req, ZCL_SCENES_CLUSTER_ADD_SCENE_COMMAND_ID,
    sizeof(ZCL_AddScene_t) + sizeof(ZCL_OnOffClusterExtensionFieldSet_t) +
    sizeof(ZCL_LevelControlSceneExtensionFields_t));
  ciFillAddSceneToDimmableLightPayload((ZCL_AddScene_t *)req->requestPayload, group, scene, time, onOff, level);
  fillDstAddressing(&req->dstAddressing, mode, addr, ep, SCENES_CLUSTER_ID);
  commandManagerSendCommand(req);
}

/**************************************************************************//**
\brief Sends Add Scene command to bound Thermostat device

\param[in] mode  - address mode;
\param[in] addr  - short address of destination node or number of group;
\param[in] ep    - endpoint number of destination device;
\param[in] group - group id;
\param[in] scene - scene id;
\param[in] time  - transition time;
\param[in] occupiedCoolingSetPoint - occupiedCoolingSetPoint extenstion field value;
\param[in] occupiedHeatingSetPoint - occupiedHeatingSetPoint extension field value
\param[in] systemMode              - systemMode extension field value
******************************************************************************/
void scenesSendAddSceneToThermotstat(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep,
  uint16_t group, uint8_t scene, uint16_t time, int16_t occupiedCoolingSetPoint, int16_t occupiedHeatingSetPoint, uint8_t systemMode)
{
  ZCL_Request_t *req;

  if (!(req = getFreeCommand()))
    return;

  fillCommandRequest(req, ZCL_SCENES_CLUSTER_ADD_SCENE_COMMAND_ID,
    sizeof(ZCL_AddScene_t) + sizeof(ZCL_ThermostatClusterExtensionFieldSet_t));

  ciFillAddSceneToThermostatPayload((ZCL_AddScene_t *)req->requestPayload, group, scene, time, 
                                    occupiedCoolingSetPoint, occupiedHeatingSetPoint, systemMode);
  fillDstAddressing(&req->dstAddressing, mode, addr, ep, SCENES_CLUSTER_ID);
  commandManagerSendCommand(req);
}

/**************************************************************************//**
\brief Sends View Scene command to bound devices

\param[in] mode  - address mode;
\param[in] addr  - short address of destination node or number of group;
\param[in] ep    - endpoint number of destination device;
\param[in] group - group id;
\param[in] scene - scene id
******************************************************************************/
void scenesSendViewScene(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep,
  uint16_t group, uint8_t scene)
{
  ZCL_Request_t *req;

  if (!(req = getFreeCommand()))
    return;

  fillCommandRequest(req, ZCL_SCENES_CLUSTER_VIEW_SCENE_COMMAND_ID, sizeof(ZCL_ViewScene_t));
  ciFillViewRemoveStoreRecallScenePayload((ZCL_ViewScene_t *)req->requestPayload, group, scene);
  fillDstAddressing(&req->dstAddressing, mode, addr, ep, SCENES_CLUSTER_ID);
  commandManagerSendCommand(req);
}

/**************************************************************************//**
\brief Sends Remove Scene command to bound devices

\param[in] mode  - address mode;
\param[in] addr  - short address of destination node or number of group;
\param[in] ep    - endpoint number of destination device;
\param[in] group - group id;
\param[in] scene - scene id
******************************************************************************/
void scenesSendRemoveScene(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep,
  uint16_t group, uint8_t scene)
{
  ZCL_Request_t *req;

  if (!(req = getFreeCommand()))
    return;

  fillCommandRequest(req, ZCL_SCENES_CLUSTER_REMOVE_SCENE_COMMAND_ID, sizeof(ZCL_RemoveScene_t));
  ciFillViewRemoveStoreRecallScenePayload((ZCL_ViewScene_t *)req->requestPayload, group, scene);
  fillDstAddressing(&req->dstAddressing, mode, addr, ep, SCENES_CLUSTER_ID);
  commandManagerSendCommand(req);
}

/**************************************************************************//**
\brief Sends Remove All Scenes command to bound devices

\param[in] mode  - address mode;
\param[in] addr  - short address of destination node or number of group;
\param[in] ep    - endpoint number of destination device;
\param[in] group - group id
******************************************************************************/
void scenesSendRemoveAllScenes(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep,
  uint16_t group)
{
  ZCL_Request_t *req;

  if (!(req = getFreeCommand()))
    return;

  fillCommandRequest(req, ZCL_SCENES_CLUSTER_REMOVE_ALL_SCENES_COMMAND_ID, sizeof(ZCL_RemoveAllScenes_t));
  ciFillRemoveAllScenesGetSceneMembershipPayload((ZCL_RemoveAllScenes_t *)req->requestPayload, group);
  fillDstAddressing(&req->dstAddressing, mode, addr, ep, SCENES_CLUSTER_ID);
  commandManagerSendCommand(req);
}

/**************************************************************************//**
\brief Sends Store Scene command to bound devices

\param[in] mode  - address mode;
\param[in] addr  - short address of destination node or number of group;
\param[in] ep    - endpoint number of destination device;
\param[in] group - group id;
\param[in] scene - scene id
******************************************************************************/
void scenesSendStoreScene(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep,
  uint16_t group, uint8_t scene)
{
  ZCL_Request_t *req;

  if (!(req = getFreeCommand()))
    return;

  fillCommandRequest(req, ZCL_SCENES_CLUSTER_STORE_SCENE_COMMAND_ID, sizeof(ZCL_StoreScene_t));
  ciFillViewRemoveStoreRecallScenePayload((ZCL_ViewScene_t *)req->requestPayload, group, scene);
  fillDstAddressing(&req->dstAddressing, mode, addr, ep, SCENES_CLUSTER_ID);
  commandManagerSendCommand(req);
}

/**************************************************************************//**
\brief Sends Recall Scene command to bound devices

\param[in] mode  - address mode;
\param[in] addr  - short address of destination node or number of group;
\param[in] ep    - endpoint number of destination device;
\param[in] group - group id;
\param[in] scene - scene id
******************************************************************************/
void scenesSendRecallScene(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep,
  uint16_t group, uint8_t scene)
{
  ZCL_Request_t *req;

  if (!(req = getFreeCommand()))
    return;

  fillCommandRequest(req, ZCL_SCENES_CLUSTER_RECALL_SCENE_COMMAND_ID, sizeof(ZCL_RecallScene_t));
  ciFillViewRemoveStoreRecallScenePayload((ZCL_ViewScene_t *)req->requestPayload, group, scene);
  fillDstAddressing(&req->dstAddressing, mode, addr, ep, SCENES_CLUSTER_ID);
  commandManagerSendCommand(req);
}

/**************************************************************************//**
\brief Sends Get Scene Membership command to bound devices

\param[in] mode  - address mode;
\param[in] addr  - short address of destination node or number of group;
\param[in] ep    - endpoint number of destination device;
\param[in] group - group id
******************************************************************************/
void scenesSendGetSceneMembership(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep,
  uint16_t group)
{
  ZCL_Request_t *req;

  if (!(req = getFreeCommand()))
    return;

  fillCommandRequest(req, ZCL_SCENES_CLUSTER_GET_SCENE_MEMBERSHIP_COMMAND_ID, sizeof(ZCL_GetSceneMembership_t));
  ciFillRemoveAllScenesGetSceneMembershipPayload((ZCL_RemoveAllScenes_t *)req->requestPayload, group);
  fillDstAddressing(&req->dstAddressing, mode, addr, ep, SCENES_CLUSTER_ID);
  commandManagerSendCommand(req);
}

/**************************************************************************//**
\brief Callback on receiving Add Scene Response command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
static ZCL_Status_t addSceneResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_AddSceneResponse_t *payload)
{
  LOG_STRING(addSceneRespStr, "Add scene response: status = 0x%02x\r\n");
  LOG_STRING(groupStr, "groupId = 0x%04x\r\n");
  LOG_STRING(sceneStr, "sceneId = 0x%02x\r\n");

  appSnprintf(addSceneRespStr, payload->status);
  appSnprintf(groupStr, payload->groupId);
  appSnprintf(sceneStr, payload->sceneId);

  (void)addressing, (void)payloadLength, (void)payload;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receiving View Scene Response command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
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

  (void)addressing, (void)payloadLength, (void)payload;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receiving Remove Scene Response command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
static ZCL_Status_t removeSceneResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_RemoveSceneResponse_t *payload)
{
  LOG_STRING(removeSceneRespStr, "Remove scene response: status = 0x%02x\r\n");
  LOG_STRING(groupStr, "groupId = 0x%04x\r\n");
  LOG_STRING(sceneStr, "sceneId = 0x%02x\r\n");

  appSnprintf(removeSceneRespStr, payload->status);
  appSnprintf(groupStr, payload->groupId);
  appSnprintf(sceneStr, payload->sceneId);

  (void)addressing, (void)payloadLength, (void)payload;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receiving Remove All Scenes Response command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
static ZCL_Status_t removeAllScenesResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_RemoveAllScenesResponse_t *payload)
{
  LOG_STRING(removeAllScenesRespStr, "Remove all scenes response: status = 0x%02x\r\n");
  LOG_STRING(groupStr, "groupId = 0x%04x\r\n");

  appSnprintf(removeAllScenesRespStr, payload->status);
  appSnprintf(groupStr, payload->groupId);

  (void)addressing, (void)payloadLength, (void)payload;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receiving Store Scene Response command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
static ZCL_Status_t storeSceneResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_StoreSceneResponse_t *payload)
{
  LOG_STRING(storeRespStr, "Store scene response: status = 0x%02x\r\n");

  appSnprintf(storeRespStr, payload->status);

  (void)addressing, (void)payloadLength, (void)payload;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receiving Get Scene Membership Response command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
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
    appSnprintf(sceneStr, payload->sceneList[i]);

  (void)addressing, (void)payloadLength, (void)payload;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Fills Add Scene command to DL structure

\param[out] payload - pointer to command structure;
\param[in] group - group id;
\param[in] scene - scene id;
\param[in] time  - transition time;
\param[in] onOff - onOff extenstion filed value;
\param[in] level - currentLevel extension field value
******************************************************************************/
static void ciFillAddSceneToDimmableLightPayload(ZCL_AddScene_t *payload, uint16_t group, uint8_t scene, uint16_t time, bool onOff, uint8_t level)
{
  ZCL_OnOffClusterExtensionFieldSet_t    *onOffExt = (ZCL_OnOffClusterExtensionFieldSet_t *)&payload->name[1];
  uint8_t                                *tmp = (uint8_t *)(&payload->name[1]) + sizeof(ZCL_OnOffClusterExtensionFieldSet_t);
  ZCL_LevelControlSceneExtensionFields_t *levelControlExt = (ZCL_LevelControlSceneExtensionFields_t *)tmp;

  payload->groupId        = group;
  payload->sceneId        = scene;
  payload->transitionTime = time;
  payload->name[0]        = 0;

  onOffExt->clusterId  = ONOFF_CLUSTER_ID;
  onOffExt->length     = sizeof(onOffExt->onOffValue);
  onOffExt->onOffValue = onOff;

  levelControlExt->clusterId    = LEVEL_CONTROL_CLUSTER_ID;
  levelControlExt->length       = sizeof(levelControlExt->currentLevel);
  levelControlExt->currentLevel = level;
}

/**************************************************************************//**
\brief Fills Add Scene command TH structure

\param[out] payload - pointer to command structure;
\param[in] group - group id;
\param[in] scene - scene id;
\param[in] time  - transition time;
\param[in] occupiedCoolingSetPoint - onOff occupiedCoolingSetPoint filed value;
\param[in] occupiedHeatingSetPoint - occupiedHeatingSetPoint extension field value
\param[in] systemMode              - systemMode extension field value
******************************************************************************/
static void ciFillAddSceneToThermostatPayload(ZCL_AddScene_t *payload, uint16_t group, uint8_t scene, uint16_t time, 
                                              int16_t occupiedCoolingSetPoint, int16_t occupiedHeatingSetPoint, uint8_t systemMode)
{
  ZCL_ThermostatClusterExtensionFieldSet_t    *thermostatExt = (ZCL_ThermostatClusterExtensionFieldSet_t *)&payload->name[1];

  payload->groupId        = group;
  payload->sceneId        = scene;
  payload->transitionTime = time;
  payload->name[0]        = 0;

  thermostatExt->clusterId  = THERMOSTAT_CLUSTER_ID;
  thermostatExt->length     = sizeof(ZCL_ThermostatClusterExtensionFieldSet_t) - sizeof(uint8_t) - sizeof(ClusterId_t) ;
  thermostatExt->occupiedCoolingSetpoint = occupiedCoolingSetPoint;
  thermostatExt->occupiedHeatingSetpoint = occupiedHeatingSetPoint;
  thermostatExt->systemMode = systemMode;
}

/**************************************************************************//**
\brief Fills View, Remove, Store or Recall Scene command structure

\param[out] payload - pointer to command structure;
\param[in] group - group id;
\param[in] scene - scene id
******************************************************************************/
static void ciFillViewRemoveStoreRecallScenePayload(ZCL_ViewScene_t *payload, uint16_t group, uint8_t scene)
{
  payload->groupId = group;
  payload->sceneId = scene;
}

/**************************************************************************//**
\brief Fills View, Remove, Store or Recall Scene command structure

\param[out] payload - pointer to command structure;
\param[in] group - group id
******************************************************************************/
static void ciFillRemoveAllScenesGetSceneMembershipPayload(ZCL_RemoveAllScenes_t *payload, uint16_t group)
{
  payload->groupId = group;
}

#endif // APP_DEVICE_TYPE_COMBINED_INTERFACE
//eof ciScenesCluster.c