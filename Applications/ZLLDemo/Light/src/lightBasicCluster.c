/**************************************************************************//**
  \file lightBasicCluster.c

  \brief
    Light device Basic cluster implementation.

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
#include <debug.h>
#include <zclParser.h>
#include <zllDemo.h>
#include <zcl.h>
#include <zclZllBasicCluster.h>
#include <commandManager.h>

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
\brief Initialize the Basic cluster
******************************************************************************/
void basicClusterInit(void)
{
  basicClusterServerAttributes.zclVersion.value = 1;
  basicClusterServerAttributes.applicationVersion.value = 2;
  basicClusterServerAttributes.stackVersion.value = 3;
  basicClusterServerAttributes.hwVersion.value = 4;
  basicClusterServerAttributes.powerSource.value = 0x01; // Mains (single phase)

  memcpy(basicClusterServerAttributes.manufacturerName.value, "\x07 Atmel ", 8);
  memcpy(basicClusterServerAttributes.modelIdentifier.value, "\x07 Light ", 8);
  memcpy(basicClusterServerAttributes.dateCode.value, "\x09 20111223", 10);
  memcpy(basicClusterServerAttributes.swBuildId.value, "\x08 Phoenix", 9);
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
  cmd->payload.readAttribute.id = ZCL_BASIC_CLUSTER_SERVER_ZCL_VERSION_ATTRIBUTE_ID;
  cmd->size = sizeof(ZCL_ReadAttributeReq_t);
  cmd->isAttributeOperation = true;
  cmd->srcEndpoint = APP_ENDPOINT_LIGHT;
  cmd->ZCL_Notify = readAttributeResp;
  clustersSendCommand(cmd);
  
  (void)attributeId;
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

#endif // APP_ZLL_DEVICE_TYPE >= APP_DEVICE_TYPE_ON_OFF_LIGHT

// eof lightBasicCluster.c
