/**************************************************************************//**
  \file ciBasicCluster.c

  \brief
    Dimmer Switch Basic cluster implementation.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    03.09.13 N. Fomin - Created.
******************************************************************************/
#ifdef APP_DEVICE_TYPE_COMBINED_INTERFACE

/******************************************************************************
                    Includes section
******************************************************************************/
#include <ciBasicCluster.h>
#include <basicCluster.h>
#include <haClusters.h>
#include <commandManager.h>
#include <uartManager.h>
#include <ciClusters.h>

/******************************************************************************
                    Prototypes section
******************************************************************************/
static ZCL_Status_t resetToFactoryDefaultsInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload);

/******************************************************************************
                    Global variables section
******************************************************************************/
ZCL_BasicClusterServerAttributes_t ciBasicClusterServerAttributes =
{
  ZCL_DEFINE_BASIC_CLUSTER_SERVER_ATTRIBUTES()
};

ZCL_BasicClusterServerCommands_t ciBasicClusterServerCommands =
{
  ZCL_DEFINE_BASIC_CLUSTER_COMMANDS(resetToFactoryDefaultsInd)
};

/******************************************************************************
                    Local variables section
******************************************************************************/
static AttibuteReadCallback_t   readAttributeCallback;
static AttributeWriteCallback_t writeAttributeCallback;

/******************************************************************************
                    Prototypes section
******************************************************************************/
static void ZCL_ReadAttributeResp(ZCL_Notify_t *ntfy);
static void ZCL_WriteAttributeResp(ZCL_Notify_t *ntfy);

/******************************************************************************
                    Implementation section
******************************************************************************/
/**************************************************************************//**
\brief Initializes Basic cluster
******************************************************************************/
void basicClusterInit(void)
{
  ciBasicClusterServerAttributes.zclVersion.value          = 0x01;
  ciBasicClusterServerAttributes.powerSource.value         = 0x04;
  ciBasicClusterServerAttributes.physicalEnvironment.value = 0x00;
  ciBasicClusterServerAttributes.applicationVersion.value  = 2;
  ciBasicClusterServerAttributes.stackVersion.value        = 3;
  ciBasicClusterServerAttributes.hwVersion.value           = 4;

  memcpy(ciBasicClusterServerAttributes.manufacturerName.value, "\x1f Atmel ", 8);
  memcpy(ciBasicClusterServerAttributes.modelIdentifier.value, "\x1f CombinedInterface", 19);
}

/**************************************************************************//**
\brief Callback on receive of resetToFactoryDefaults command
******************************************************************************/
static ZCL_Status_t resetToFactoryDefaultsInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload)
{
  for (uint8_t i=0; i<CI_SERVER_CLUSTER_INIT_COUNT; i++)
  {
    if (ciServerClusterInitFunctions[i])
      (ciServerClusterInitFunctions[i])();
  }

  // needs to enable after app directory is created
  //PDS_Store(HA_APP_MEMORY_MEM_ID);

  (void)addressing;
  (void)payloadLength;
  (void)payload;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Sends Read Attribute command unicastly

\param[in] mode - address mode;
\param[in] addr - short address of destination node;
\param[in] ep   - destination endpoint;
\param[in] attr - attribute id;
\param[in] cb   - callback function
******************************************************************************/
void basicReadAttribute(APS_AddrMode_t mode,ShortAddr_t addr, Endpoint_t ep,
  uint16_t attr, AttibuteReadCallback_t cb)
{
  ZCL_Request_t *req;
  ZCL_NextElement_t element;
  ZCL_ReadAttributeReq_t readAttrReqElement;

  if (!(req = getFreeCommand()))
    return;

  readAttributeCallback = cb;

  readAttrReqElement.id = attr;

  element.payloadLength = 0;
  element.payload = req->requestPayload;
  element.id = ZCL_READ_ATTRIBUTES_COMMAND_ID;
  element.content = &readAttrReqElement;
  ZCL_PutNextElement(&element);

  fillCommandRequest(req, ZCL_READ_ATTRIBUTES_COMMAND_ID, element.payloadLength);
  fillDstAddressing(&req->dstAddressing, mode, addr, ep, BASIC_CLUSTER_ID);
  req->ZCL_Notify = ZCL_ReadAttributeResp;

  commandManagerSendAttribute(req);
}

/**************************************************************************//**
\brief Sends resetToFactoryDefaults command unicastly

\param[in] mode - address mode;
\param[in] addr - short address of destination node;
\param[in] ep   - destination endpoint;
******************************************************************************/
void basicResetToFactoryDefaultsCommand(APS_AddrMode_t mode,ShortAddr_t addr, Endpoint_t ep)
{
  ZCL_Request_t *req;

  if (!(req = getFreeCommand()))
    return;

  fillCommandRequest(req, ZCL_BASIC_CLUSTER_SERVER_RESET_TO_FACTORY_DEFAULTS_COMMAND_ID, 0);
  fillDstAddressing(&req->dstAddressing, mode, addr, ep, BASIC_CLUSTER_ID);

  commandManagerSendCommand(req);
}

/**************************************************************************//**
\brief Sends Write Attribute command unicastly

\param[in] mode - address mode;
\param[in] addr - short address of destination node;
\param[in] attr - attribute id;
\param[in] ep   - destination endpoint;
\param[in] type - attribute type;
\param[in] cb   - callback function;
\param[in] data - the pointer to memory with value to be written;
\param[in] size - size of data parameter in octets
******************************************************************************/
void basicWriteAttribute(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep,
  uint16_t attr, uint8_t type, AttributeWriteCallback_t cb, void *data, uint8_t size)
{
  ZCL_Request_t *req;
  ZCL_WriteAttributeReq_t writeAttrReq;

  if (!(req = getFreeCommand()))
    return;

  writeAttributeCallback = cb;

  writeAttrReq.id = attr;
  writeAttrReq.type = type;
  memcpy(req->requestPayload, (uint8_t *)&writeAttrReq, sizeof(ZCL_WriteAttributeReq_t) - sizeof(uint8_t));
  memcpy(req->requestPayload + sizeof(ZCL_WriteAttributeReq_t) - sizeof(uint8_t), (uint8_t *)data, size);

  fillCommandRequest(req, ZCL_WRITE_ATTRIBUTES_COMMAND_ID, size + sizeof(ZCL_WriteAttributeReq_t) - sizeof(uint8_t));
  fillDstAddressing(&req->dstAddressing, mode, addr, ep, BASIC_CLUSTER_ID);
  req->ZCL_Notify = ZCL_WriteAttributeResp;

  commandManagerSendAttribute(req);
}

/**************************************************************************//**
\brief Indication of read attribute response

\param[in] resp - pointer to response
******************************************************************************/
static void ZCL_ReadAttributeResp(ZCL_Notify_t *ntfy)
{
  ZCL_NextElement_t element;
  ZCL_ReadAttributeResp_t *readAttributeResp;

  if (ZCL_SUCCESS_STATUS == ntfy->status)
  {
    element.id            = ZCL_READ_ATTRIBUTES_RESPONSE_COMMAND_ID;
    element.payloadLength = ntfy->responseLength;
    element.payload       = ntfy->responsePayload;
    element.content       = NULL;

    ZCL_GetNextElement(&element);
    readAttributeResp = (ZCL_ReadAttributeResp_t *) element.content;

    if (readAttributeCallback)
      readAttributeCallback((void *)&readAttributeResp->value[0]);

    if ((ZCL_BASIC_CLUSTER_SERVER_MANUFACTURER_NAME_ATTRIBUTE_ID == readAttributeResp->id) || \
        (ZCL_BASIC_CLUSTER_SERVER_MODEL_IDENTIFIER_ATTRIBUTE_ID == readAttributeResp->id))
    {
      LOG_STRING(readAttrSuccessStr, " <-Read Basic attribute (0x%x) response: success value = %s\r\n");
      appSnprintf(readAttrSuccessStr, (unsigned)readAttributeResp->id, readAttributeResp->value);
    }
    else
    {
      LOG_STRING(readAttrSuccessStr, " <-Read Basic attribute (0x%x) response: success value = %u\r\n");
      appSnprintf(readAttrSuccessStr, (unsigned)readAttributeResp->id, (unsigned)readAttributeResp->value[0]);
    }
  }
  else
  {
    LOG_STRING(readAttrFailStr, " +Read Basic attribute failed: status = 0x%x\r\n");
    appSnprintf(readAttrFailStr, (unsigned)ntfy->status);
  }
}

/**************************************************************************//**
\brief Indication of write attribute response

\param[in] resp - pointer to response
******************************************************************************/
static void ZCL_WriteAttributeResp(ZCL_Notify_t *ntfy)
{
  if (ZCL_SUCCESS_STATUS == ntfy->status)
  {
    if (writeAttributeCallback)
      writeAttributeCallback();

    LOG_STRING(writeAttrSuccessStr, " <-Write Basic attribute response: success\r\n");
    appSnprintf(writeAttrSuccessStr);
  }
  else
  {
    LOG_STRING(writeAttrFailStrTwo, " +Write Basic attribute failed: status = 0x%x\r\n");
    appSnprintf(writeAttrFailStrTwo, (unsigned)ntfy->status);
  }
}

#endif // APP_DEVICE_TYPE_COMBINED_INTERFACE

// eof ciBasicCluster.c
