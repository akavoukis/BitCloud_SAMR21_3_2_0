/**************************************************************************//**
  \file haClusters.c

  \brief
    Clusters implementation.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2013, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    10.09.13 N. Fomin - Created.
******************************************************************************/

/******************************************************************************
                    Includes section
******************************************************************************/
#include <haClusters.h>
#include <commandManager.h>
#include <uartManager.h>
#include <clusters.h>

/******************************************************************************
                    Prototypes section
******************************************************************************/
static void ZCL_ConfigureReportingResp(ZCL_Notify_t *ntfy);

/******************************************************************************
                    Implementation section
******************************************************************************/
/**************************************************************************//**
\brief Fills ZCL Request structure

\param[out] req     - pointer to zcl command request;
\param[in]  command - command id;
\param[in] size     - the size of request payload
******************************************************************************/
void fillCommandRequest(ZCL_Request_t *req, uint8_t command, uint8_t size)
{
  req->id              = command;
  req->requestLength   = size;
  req->endpointId      = APP_SRC_ENDPOINT_ID;
  req->defaultResponse = ZCL_FRAME_CONTROL_DISABLE_DEFAULT_RESPONSE;
}

/**************************************************************************//**
\brief Fills zcl addressing structure

\param[out] addressing - pointer to the structure to be filled;
\param[in]  mode       - addressing mode;
\param[in]  addr       - short address of destination mode;
\param[in]  ep         - endpoint number of destination node;
\param[in]  cluster    - cluster id
******************************************************************************/
void fillDstAddressing(ZCL_Addressing_t *addressing, APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep, ClusterId_t cluster)
{
  addressing->addrMode             = mode;
  addressing->addr.shortAddress    = addr;
  addressing->profileId            = PROFILE_ID_HOME_AUTOMATION;
  addressing->endpointId           = ep;
  addressing->clusterId            = cluster;
  addressing->clusterSide          = ZCL_CLUSTER_SIDE_SERVER;
  addressing->manufacturerSpecCode = 0;
  addressing->sequenceNumber       = ZCL_GetNextSeqNumber();
}

/**************************************************************************//**
\brief Fills zcl addressing structure

\param[out] addressing - pointer to the structure to be filled;
\param[in]  mode       - addressing mode;
\param[in]  addr       - short address of destination mode;
\param[in]  ep         - endpoint number of destination node;
\param[in]  cluster    - cluster id
******************************************************************************/
void fillDstAddressingServer(ZCL_Addressing_t *addressing, APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep, ClusterId_t cluster)
{
  addressing->addrMode             = mode;
  addressing->addr.shortAddress    = addr;
  addressing->profileId            = PROFILE_ID_HOME_AUTOMATION;
  addressing->endpointId           = ep;
  addressing->clusterId            = cluster;
  addressing->clusterSide          = ZCL_CLUSTER_SIDE_CLIENT;
  addressing->manufacturerSpecCode = 0;
  addressing->sequenceNumber       = ZCL_GetNextSeqNumber();
}

/**************************************************************************//**
\brief Gets free command buffer

\returns pointer to a command buffer
******************************************************************************/
ZCL_Request_t *getFreeCommand(void)
{
  ZCL_Request_t *req;

  if (!(req = commandManagerAllocCommand()))
  {
    LOG_STRING(insufficientBuffersAmountStr, "\r\nNot enough command buffers\r\n");
    appSnprintf(insufficientBuffersAmountStr);
  }

  return req;
}

/**************************************************************************//**
\brief Fills ZCL Addressing structure

\param[out] srcAddressing - pointer to zcl addressing request of source node;
\param[in]  dstAddressing - pointer to zcl addressing request of destination node;
\param[in]  side          - cluster side of recipient side
******************************************************************************/
void fillDstAddressingViaSourceAddressing(ZCL_Addressing_t *srcAddressing, ZCL_Addressing_t *dstAddressing, uint8_t side)
{
  *srcAddressing = *dstAddressing;
  srcAddressing->clusterSide = side;
}

/**************************************************************************//**
\brief Sends configure reporting request to notify another device about reporting

\param[in] endpoint  - destination endpoint;
\param[in] clusterId - cluster id;
\param[in] attrId    - attribute id;
]param[in] period    - report period
******************************************************************************/
void sendConfigureReportingToNotify(Endpoint_t srcEndpoint, Endpoint_t dstEndpoint, ClusterId_t clusterId, ZCL_AttributeId_t attrId, ZCL_ReportTime_t period, ConfigureReportResp_t configureRespCb)
{
  ZCL_Request_t *req;
  ZCL_NextElement_t element;
  ZCL_ConfigureReportingReq_t configureReportingReq;

  if (!(req = getFreeCommand()))
    return;

  configureReportingReq.direction     = ZCL_FRAME_CONTROL_DIRECTION_SERVER_TO_CLIENT;
  configureReportingReq.attributeId   = attrId;
  configureReportingReq.timeoutPeriod = period;

  element.payloadLength = 0;
  element.payload       = req->requestPayload;
  element.id            = ZCL_CONFIGURE_REPORTING_COMMAND_ID;
  element.content       = &configureReportingReq;
  ZCL_PutNextElement(&element);

  fillCommandRequest(req, ZCL_CONFIGURE_REPORTING_COMMAND_ID, element.payloadLength);
  req->endpointId = srcEndpoint;
  fillDstAddressing(&req->dstAddressing, APS_NO_ADDRESS, 0, dstEndpoint, clusterId);
  req->dstAddressing.clusterSide = ZCL_CLUSTER_SIDE_CLIENT;
  if(NULL == configureRespCb)
    req->ZCL_Notify = ZCL_ConfigureReportingResp;
  else
    req->ZCL_Notify = configureRespCb;

  commandManagerSendAttribute(req);
}

/**************************************************************************//**
\brief Indication of configure reporting response

\param[in] resp - pointer to response
******************************************************************************/
static void ZCL_ConfigureReportingResp(ZCL_Notify_t *ntfy)
{
  (void)ntfy;
}

// eof haClusters.c
