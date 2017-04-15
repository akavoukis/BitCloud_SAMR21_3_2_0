/**************************************************************************//**
  \file bridgeScenesCluster.c

  \brief
    Control Bridge device Scenes cluster implementation.

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
                    Includes section
******************************************************************************/
#include <zcl.h>
#include <zclZllScenesCluster.h>
#include <commandManager.h>
#include <bridgeClusters.h>

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

static void bridgeFillScenePayload(ZCL_StoreScene_t *payload, uint16_t group, uint8_t scene);

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
/**************************************************************************//**
\brief Sends Store/Recall/Remove Scene command

\param[in] mode    - address mode;
\param[in] addr    - short address of destination node or number of group;
\param[in] ep      - endpoint number of destination device;
\param[in] command - command id;
\param[in] group   - id of a group;
\param[in] scene   - id of a scene
******************************************************************************/
void bridgeStoreRecallRemoveSceneCommand(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep,
                                                   uint8_t command, uint16_t group, uint8_t scene)
{
  CommandDescriptor_t *cmd;
  ZCL_Addressing_t addressing;

  if (!(cmd = bridgeGetFreeCommand()))
    return;

  bridgeFillCommandRequest(cmd, command, SCENES_CLUSTER_ID, sizeof(cmd->payload.storeScene));
  bridgeFillScenePayload(&cmd->payload.storeScene, group, scene);
  bridgeFillDstAddressing(&addressing, mode, addr, ep);

  clustersSendCommandWithAddressing(cmd, &addressing);
}

/**************************************************************************//**
\brief Callback on receive of Add Scene Response command
******************************************************************************/
static ZCL_Status_t addSceneResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_AddSceneResponse_t *payload)
{
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
  (void)addressing;
  (void)payloadLength;
  (void)payload;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receive of Get Scene Membership Response command
******************************************************************************/
static ZCL_Status_t getSceneMembershipResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_GetSceneMembershipResponse_t *payload)
{
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
static void bridgeFillScenePayload(ZCL_StoreScene_t *payload, uint16_t group, uint8_t scene)
{
  payload->groupId = group;
  payload->sceneId = scene;
}

#endif // APP_ZLL_DEVICE_TYPE == APP_DEVICE_TYPE_BRIDGE

// eof bridgeScenesCluster.c
