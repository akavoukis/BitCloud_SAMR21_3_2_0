/**************************************************************************//**
  \file colorSceneRemoteBasicCluster.c

  \brief
    Color Scene Remote device Basic cluster implementation.

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
#include <zclParser.h>
#include <zllDemo.h>
#include <zcl.h>
#include <zclZllBasicCluster.h>
#include <clusters.h>
#include <commandManager.h>
#include <colorSceneRemoteLevelControlCluster.h>
#include <colorSceneRemoteClusters.h>

/******************************************************************************
                    Prototypes section
******************************************************************************/
static void readAttributeResp(ZCL_Notify_t *ntfy);

/******************************************************************************
                    Global variables
******************************************************************************/
ZCL_BasicClusterServerAttributes_t basicClusterServerAttributes =
{
  ZCL_DEFINE_BASIC_CLUSTER_SERVER_ATTRIBUTES()
};

/******************************************************************************
                    Implementations section
******************************************************************************/

/**************************************************************************//**
\brief Initialize Basic cluster.
******************************************************************************/
void basicClusterInit(void)
{
  basicClusterServerAttributes.zclVersion.value = 1;
  basicClusterServerAttributes.applicationVersion.value = 2;
  basicClusterServerAttributes.stackVersion.value = 3;
  basicClusterServerAttributes.hwVersion.value = 4;
  basicClusterServerAttributes.powerSource.value = 0x03; // Battery

  memcpy(basicClusterServerAttributes.manufacturerName.value, "\x07 Atmel ", 8);
  memcpy(basicClusterServerAttributes.modelIdentifier.value, "\x07 Remote", 8);
  memcpy(basicClusterServerAttributes.dateCode.value, "\x09 20111223", 10);
  memcpy(basicClusterServerAttributes.swBuildId.value, "\x08 Phoenix", 9);
#if APP_ENABLE_CERTIFICATION_EXTENSION == 1
  ZCL_Cluster_t *basicCluster = ZCL_GetCluster(APP_ENDPOINT_COLOR_SCENE_REMOTE,
                                                  BASIC_CLUSTER_ID,
                                                  ZCL_CLUSTER_SIDE_CLIENT);

  basicCluster->ZCL_DefaultRespInd = commandManagerDefaultResponseHandler;
#endif // APP_ENABLE_CERTIFICATION_EXTENSION == 1
}

/**************************************************************************//**
\brief Sends Basic Cluster read attribute command

\param[in] attributeId - attribute of interest identifier
******************************************************************************/
void basicSendReadAttribute(uint16_t attributeId)
{
  CommandDescriptor_t *cmd;

  if (!(cmd = clustersAllocCommand()))
    return;

  cmd->clusterId = BASIC_CLUSTER_ID;
  cmd->commandId = ZCL_READ_ATTRIBUTES_COMMAND_ID;
  cmd->payload.readAttribute.id = attributeId;
  cmd->size = sizeof(ZCL_ReadAttributeReq_t);
  cmd->isAttributeOperation = true;
  cmd->ZCL_Notify = readAttributeResp;
  clustersSendCommand(cmd);
}

/**************************************************************************//**
\brief Sends Basic Cluster write attribute command

\param[in] attributeId - attribute of interest identifier
******************************************************************************/
void basicSendWriteAttribute(uint16_t attributeId, void *value, uint8_t type)
{
  CommandDescriptor_t *cmd;
  ZCL_DataTypeDescriptor_t attrDesc;

  if (!(cmd = clustersAllocCommand()))
    return;

  ZCL_GetDataTypeDescriptor(type, value, &attrDesc);

  cmd->clusterId = BASIC_CLUSTER_ID;
  cmd->commandId = ZCL_WRITE_ATTRIBUTES_COMMAND_ID;
  cmd->payload.writeAttribute.id = attributeId;
  cmd->payload.writeAttribute.type = type;
  memcpy(cmd->payload.writeAttribute.value, value, attrDesc.length);
  cmd->size = sizeof(uint16_t) + sizeof(uint8_t) + attrDesc.length;
  cmd->isAttributeOperation = true;
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
    else if (ZCL_CHARACTER_STRING_DATA_TYPE_ID == readAttrResp->type)
    {
      LOG_STRING(attrValueStr, "Attr 0x%04x = ");
      LOG_STRING(endStr, "\r\n");
      appSnprintf(attrValueStr, (unsigned)readAttrResp->id);
      appSnprintf((char *)readAttrResp->value);
      appSnprintf(endStr);
    }
  }
}

#endif // APP_ZLL_DEVICE_TYPE == APP_DEVICE_TYPE_COLOR_SCENE_REMOTE

// eof colorSceneRemoteCluster.c
