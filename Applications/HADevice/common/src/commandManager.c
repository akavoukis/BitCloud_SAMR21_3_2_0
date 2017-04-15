/**************************************************************************//**
  \file commandManager.c

  \brief
    Command manager implementation.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    11.12.12 N.Fomin - Created.
******************************************************************************/

/******************************************************************************
                    Includes section
******************************************************************************/
#include <sysUtils.h>
#include <commandManager.h>
#include <zclIdentifyCluster.h>
#include <zclLevelControlCluster.h>
#include <zclGroupsCluster.h>
#include <zclScenesCluster.h>
#include <zclIasZoneCluster.h>
#include <zclIasACECluster.h>
#include <zclOnOffCluster.h>
#include <zclThermostatCluster.h>
#include <dlScenes.h>
#include <uartManager.h>

/******************************************************************************
                    Definitions section
******************************************************************************/
#define COMMAND_BUFFERS_AMOUNT 12
#define ALL_ATTRIBUTES_ARE_WRITTEN 1

/******************************************************************************
                    Types section
******************************************************************************/
BEGIN_PACK
typedef union PACK
{
  ZCL_GetGroupMembership_t getGroupMembership;
  uint8_t                  payload[sizeof(ZCL_GetGroupMembership_t) - sizeof(uint16_t) + CS_GROUP_TABLE_SIZE * sizeof(uint16_t)];
                                   /* own structure size */           /* size of stub */  /* up to CS_GROUP_TABLE_SIZE groups in list */
} GetGroupMemeberShip_t;

typedef union PACK
{
  ZCL_GetGroupMembershipResponse_t getGroupMembershipResponse;
  uint8_t                          payload[sizeof(ZCL_GetGroupMembershipResponse_t) - sizeof(uint16_t) + CS_GROUP_TABLE_SIZE * sizeof(uint16_t)];
                                           /* own structure size */                 /* size of stub */  /* up to CS_GROUP_TABLE_SIZE groups in list */
} GetGroupMembershipResponse_t;

typedef union PACK
{
  struct PACK
  {
    ZCL_OnOffClusterExtensionFieldSet_t    onOffExtFields;
    ZCL_LevelControlSceneExtensionFields_t levelControlExtFields;
  } onOffLevelControlExt;
  struct PACK
  {
    ZCL_ThermostatClusterExtensionFieldSet_t thermostatExtFields;
  } thermostatExt;
} SceneExtFields_t;

typedef union PACK
{
  ZCL_AddScene_t addScene;
  uint8_t        payload[sizeof(ZCL_AddScene_t) + sizeof(SceneExtFields_t)];
                         /* own structure size */ /* size of ext fields */
} AddScene_t;

typedef union PACK
{
  ZCL_ViewSceneResponse_t viewSceneResponse;
  uint8_t                 payload[sizeof(ZCL_ViewSceneResponse_t) + sizeof(SceneExtFields_t)];
                                  /* own structure size */          /* size of ext fields */
} ViewSceneResponse_t;

typedef union PACK
{
  ZCL_GetSceneMembershipResponse_t getSceneMembershupResponse;
  uint8_t                          payload[sizeof(ZCL_GetSceneMembershipResponse_t) - sizeof(uint8_t) + MAX_SCENES_AMOUNT * sizeof(uint8_t)];
                                          /* own structure size */                    /* size of stub */ /* up to MAX_SCENES_AMOUNT in list */
} GetSceneMembershipResponse_t;
END_PACK

typedef union
{
  // Identify Cluster
  ZCL_Identify_t                 identify;
  ZCL_IdentifyQueryResponse_t    identifyQueryResponse;
  ZCL_EzModeInvoke_t             ezModeInvoke;
  ZCL_UpdateCommissioningState_t updateCommissioningState;
  // Level Control Cluster
  ZCL_MoveToLevel_t              moveToLevel;
  ZCL_Move_t                     move;
  ZCL_Step_t                     step;
  // Groups Cluster
  ZCL_AddGroup_t                 addGroup;
  ZCL_ViewGroup_t                viewGroup;
  GetGroupMemeberShip_t          getGroupMembership;
  ZCL_RemoveGroup_t              removeGroup;
  ZCL_AddGroupIfIdentifying_t    addGroupIfIdentifying;
  ZCL_AddGroupResponse_t         addGroupResponse;
  ZCL_ViewGroupResponse_t        viewGroupResponse;
  GetGroupMembershipResponse_t   getGroupMembershipResponse;
  ZCL_RemoveGroupResponse_t      removeGroupResponse;
  // Scenes cluster
  AddScene_t                     addScene;
  ZCL_ViewScene_t                viewScene;
  ZCL_RemoveScene_t              removeScene;
  ZCL_RemoveAllScenes_t          removeAllScenes;
  ZCL_StoreScene_t               storeScene;
  ZCL_RecallScene_t              recallScene;
  ZCL_GetSceneMembership_t       getSceneMembership;
  ZCL_AddSceneResponse_t         addSceneResponse;
  ViewSceneResponse_t            viewSceneResponse;
  ZCL_RemoveSceneResponse_t      removeSceneResponse;
  ZCL_RemoveAllScenesResponse_t  removeAllScenesResponse;
  ZCL_StoreSceneResponse_t       storeSceneResponse;
  GetSceneMembershipResponse_t   getSceneMembershupResponse;
} Command_t;

typedef struct
{
  ZCL_Request_t zclRequest;
  Command_t     zclCommand;
  bool          busy;
  void (*ZCL_Notify)(ZCL_Notify_t *ntfy);
} ZclCommandDescriptor_t;

/******************************************************************************
                    Prototypes section
******************************************************************************/
static void commandZclRequestResp(ZCL_Notify_t *ntfy);

/******************************************************************************
                    Local variables section
******************************************************************************/
static ZclCommandDescriptor_t zclCommands[COMMAND_BUFFERS_AMOUNT];

/******************************************************************************
                    Implementations section
******************************************************************************/
/**************************************************************************//**
\brief Initializes command manager
******************************************************************************/
void commandManagerInit(void)
{
  for (uint8_t i = 0; i < COMMAND_BUFFERS_AMOUNT; i++)
    zclCommands[i].busy = false;
}

/**************************************************************************//**
\brief Gets a free buffer for a ZCL command

\return A pointer to a command's buffer or NULL if no free buffers are left
******************************************************************************/
ZCL_Request_t *commandManagerAllocCommand(void)
{
  uint8_t i = 0;

  for (; i < COMMAND_BUFFERS_AMOUNT; i++)
  {
    if (!zclCommands[i].busy)
    {
      zclCommands[i].busy = true;
      memset(&zclCommands[i].zclRequest, 0, sizeof(ZCL_Request_t));
      memset(&zclCommands[i].zclCommand, 0, sizeof(Command_t));
      zclCommands[i].zclRequest.requestPayload = (uint8_t *)&zclCommands[i].zclCommand;
      return &zclCommands[i].zclRequest;
    }
  }

  return NULL;

}

/**************************************************************************//**
\brief Sends command request
\param[in] req - request parameters
******************************************************************************/
void commandManagerSendCommand(ZCL_Request_t *req)
{
  ZclCommandDescriptor_t *command = GET_PARENT_BY_FIELD(ZclCommandDescriptor_t, zclRequest, req);

  command->ZCL_Notify = req->ZCL_Notify;
  req->ZCL_Notify     = commandZclRequestResp;

  ZCL_CommandReq(req);
}

/**************************************************************************//**
\brief Sends attribute request
\param[in] req - request parameters
******************************************************************************/
void commandManagerSendAttribute(ZCL_Request_t *req)
{
  ZclCommandDescriptor_t *command = GET_PARENT_BY_FIELD(ZclCommandDescriptor_t, zclRequest, req);

  command->ZCL_Notify = req->ZCL_Notify;
  req->ZCL_Notify     = commandZclRequestResp;

  ZCL_AttributeReq(req);
}

/**************************************************************************//**
\brief ZCL command response
******************************************************************************/
static void commandZclRequestResp(ZCL_Notify_t *ntfy)
{
  ZclCommandDescriptor_t *command = GET_PARENT_BY_FIELD(ZclCommandDescriptor_t, zclRequest.notify, ntfy);

  if (ZCL_APS_CONFIRM_ID == ntfy->id && ZCL_SUCCESS_STATUS != ntfy->status)
  {
    LOG_STRING(zclConfStr, "ZclConfirm: status = 0x%02x\r\n");
    appSnprintf(zclConfStr, ntfy->status);
  }
  if (ZCL_ZCL_RESPONSE_ID == ntfy->id)
  {
    ZCL_Request_t *req = GET_STRUCT_BY_FIELD_POINTER(ZCL_Request_t, notify, ntfy);
    LOG_STRING(zclRespStr, "ZclResponse: status = 0x%02x\r\n");

    if ((ZCL_WRITE_ATTRIBUTES_COMMAND_ID == req->id ||
         ZCL_WRITE_ATTRIBUTES_UNDIVIDED_COMMAND_ID == req->id) &&
        ALL_ATTRIBUTES_ARE_WRITTEN != req->notify.responseLength)
    {
      ZCL_NextElement_t element;
      ZCL_WriteAttributeResp_t *writeAttributeResp;

      element.id            = ZCL_WRITE_ATTRIBUTES_RESPONSE_COMMAND_ID;
      element.payloadLength = ntfy->responseLength;
      element.payload       = ntfy->responsePayload;
      element.content       = NULL;

      while (element.payloadLength)
      {
        ZCL_GetNextElement(&element);
        writeAttributeResp = (ZCL_WriteAttributeResp_t *) element.content;
        appSnprintf(zclRespStr, writeAttributeResp->status);
        element.content = NULL;
      }

      (void)writeAttributeResp;
    }
    else
      appSnprintf(zclRespStr, ntfy->status);
  }

  if (command->ZCL_Notify)
    command->ZCL_Notify(ntfy);

  command->busy = false;
}

// eof commandManager.c
