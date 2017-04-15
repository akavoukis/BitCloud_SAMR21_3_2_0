/**************************************************************************//**
  \file colorSceneRemoteLinkInfoCluster.c

  \brief
    Color Scene Remote device Link Info cluster implementation.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    25.01.13 N. Fomin - Created.
******************************************************************************/

#if APP_ZLL_DEVICE_TYPE == APP_DEVICE_TYPE_COLOR_SCENE_REMOTE

/******************************************************************************
                    Includes section
******************************************************************************/
#include <colorSceneRemoteLinkInfoCluster.h>
#include <zllDemo.h>
#include <commandManager.h>
#include <colorSceneRemoteClusters.h>

/******************************************************************************
                    Global variables section
******************************************************************************/
ZCL_LinkInfoClusterClientAttributes_t linkInfoClusterClientAttributes =
{
  ZCL_DEFINE_LINK_INFO_CLUSTER_CLIENT_ATTRIBUTES()
};

ZCL_LinkInfoClusterCommands_t linkInfoCommands =
{
  ZCL_DEFINE_LINK_INFO_CLIENT_SIDE_CLUSTER_COMMANDS()
};

/******************************************************************************
                    Implementations section
******************************************************************************/
/**************************************************************************//**
\brief Initialize Link Info cluster
******************************************************************************/
void linkInfoClusterInit(void)
{
  ZclLinkInfoAttr_t *attr = (ZclLinkInfoAttr_t *)&linkInfoClusterClientAttributes;

  memset(&linkInfoClusterClientAttributes, 0, sizeof(ZCL_LinkInfoClusterClientAttributes_t));

  for (uint8_t i = 0; i < ZCL_LINK_INFO_CLUSTER_CLIENT_SIDE_ATTRIBUTES_AMOUNT; i++)
  {
    ZclLinkInfoAttrValue_t *attrValue = (ZclLinkInfoAttrValue_t *)attr->value;
    BoundDevice_t          *device    = (BoundDevice_t *)attrValue->payload;

    device->nwkAddr   = NWK_NO_SHORT_ADDR;
    attrValue->length = ATTR_LENGTH - 1; // Length field doesn't contain itself length
    attr++;
  }
}

/**************************************************************************//**
\brief Sends ReadyToTransmit command

\param[in] addr    - short address of destination node or number of group;
\param[in] ep      - endpoint number of destination device
******************************************************************************/
void linkInfoSendReadyToTransmitCommand(ShortAddr_t addr, Endpoint_t ep)
{
  uint8_t boundsAmount = 0;
  ZclLinkInfoAttr_t *attr = (ZclLinkInfoAttr_t *)&linkInfoClusterClientAttributes;
  CommandDescriptor_t *cmd;
  ZCL_Addressing_t addressing;

  if (NULL == (cmd = colorSceneRemoteGetFreeCommand()))
    return;

  for (uint8_t i = 0; i < ZCL_LINK_INFO_CLUSTER_CLIENT_SIDE_ATTRIBUTES_AMOUNT; i++)
  {
    ZclLinkInfoAttrValue_t *attrValue = (ZclLinkInfoAttrValue_t *)attr->value;
    BoundDevice_t *device = (BoundDevice_t *)attrValue->payload;

    if (0xFFFF != device->nwkAddr)
      boundsAmount++;

    attr++;
  }

  colorSceneRemoteFillCommandRequest(cmd, ZCL_LINK_INFO_CLUSTER_READY_TO_TRANSMIT_COMMAND_ID,
                                     LINK_INFO_CLUSTER_ID, sizeof(ZCL_ReadyToTransmit_t));
  colorSceneRemoteFillDstAddressing(&addressing, APS_SHORT_ADDRESS, addr, ep);
  addressing.manufacturerSpecCode = 0x1014; //atmel id
  addressing.clusterId = LINK_INFO_CLUSTER_ID;
  cmd->payload.readyToTransmit.boundDevicesAmount = boundsAmount;

  clustersSendCommandWithAddressing(cmd, &addressing);
}

/**************************************************************************//**
\brief Gets value of attribute number "i" of Link Info cluster

\param[in] i - attribute number

\returns pointer to attribute value
******************************************************************************/
BoundDevice_t *linkInfoGetAttrValue(uint8_t i)
{
  ZclLinkInfoAttr_t *attr = (ZclLinkInfoAttr_t *)&linkInfoClusterClientAttributes;
  ZclLinkInfoAttrValue_t *attrValue;

  if (ZCL_LINK_INFO_CLUSTER_CLIENT_SIDE_ATTRIBUTES_AMOUNT <= i)
    return NULL;

  attr += i;
  attrValue = (ZclLinkInfoAttrValue_t *)attr->value;

  return (BoundDevice_t *)attrValue->payload;
}

#endif // APP_ZLL_DEVICE_TYPE == APP_DEVICE_TYPE_COLOR_SCENE_REMOTE

// eof colorSceneRemoteLinkInfoCluster.c
