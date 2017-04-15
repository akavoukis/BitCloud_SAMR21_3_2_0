/**************************************************************************//**
  \file ciOnOffCluster.c

  \brief
    Combined Interface On/Off cluster implementation.

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
#include <ciOnOffCluster.h>
#include <haClusters.h>
#include <uartManager.h>
#include <commandManager.h>

/******************************************************************************
                    Global variables section
******************************************************************************/
ZCL_OnOffClusterCommands_t ciOnOffCommands =
{
  ZCL_DEFINE_ONOFF_CLUSTER_COMMANDS(NULL, NULL, NULL)
};

/******************************************************************************
                    Prototypes section
******************************************************************************/
static void ciOnOffReportInd(ZCL_Addressing_t *addressing, uint8_t reportLength, uint8_t *reportPayload);
static void ZCL_ConfigureReportingResp(ZCL_Notify_t *ntfy);
/******************************************************************************
                    Implementation section
******************************************************************************/
/**************************************************************************//**
\brief Initializes On/Off cluster
******************************************************************************/
void onOffClusterInit(void)
{
  ZCL_Cluster_t *cluster = ZCL_GetCluster(APP_SRC_ENDPOINT_ID, ONOFF_CLUSTER_ID, ZCL_CLUSTER_SIDE_CLIENT);

  if (cluster)
    cluster->ZCL_ReportInd = ciOnOffReportInd;
}

/**************************************************************************//**
\brief Sends On, Off or Toggle command to bound devices

\param[in] mode    - address mode;
\param[in] addr    - short address of destination node or number of group;
\param[in] ep      - endpoint number of destination device;
\param[in] command - command id
******************************************************************************/
void onOffSendOnOffToggle(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep,
  OnOffToggle_t command)
{
  ZCL_Request_t *req;

  if (!(req = getFreeCommand()))
    return;

  fillCommandRequest(req, command, 0);
  fillDstAddressing(&req->dstAddressing, mode, addr, ep, ONOFF_CLUSTER_ID);
  commandManagerSendCommand(req);
}
/**************************************************************************//**
\brief Sends the Configure Reporting for onOff cluster

\param[in] mode - address mode;
\param[in] addr - short address of destination node;
\param[in] ep   - destination endpoint;
\param[in] attrId - attribute id;
\param[in] attrType - attribute type
\param[in] min  - the minimum reporting interval;
\param[in] max  - the maximum reporting interval
******************************************************************************/
void onOffConfigureReporting(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep,
  ZCL_AttributeId_t attrId, uint8_t attrType, ZCL_ReportTime_t min, ZCL_ReportTime_t max)
{
  ZCL_Request_t *req;
  ZCL_NextElement_t element;
  ZCL_ConfigureReportingReq_t configureReportingReq;

  if (!(req = getFreeCommand()))
    return;

  configureReportingReq.direction            = ZCL_FRAME_CONTROL_DIRECTION_CLIENT_TO_SERVER;
  configureReportingReq.attributeId          = attrId;
  configureReportingReq.attributeType        = attrType;
  configureReportingReq.minReportingInterval = min;
  configureReportingReq.maxReportingInterval = max;

  element.payloadLength = 0;
  element.payload = req->requestPayload;
  element.id = ZCL_CONFIGURE_REPORTING_COMMAND_ID;
  element.content = &configureReportingReq;
  ZCL_PutNextElement(&element);

  fillCommandRequest(req, ZCL_CONFIGURE_REPORTING_COMMAND_ID, element.payloadLength);
  fillDstAddressing(&req->dstAddressing, mode, addr, ep, ONOFF_CLUSTER_ID);
  req->ZCL_Notify = ZCL_ConfigureReportingResp;

  commandManagerSendAttribute(req);
}
/**************************************************************************//**
\brief Report attribute indication handler

\param[in] addressing - pointer to addressing information;
\param[in] reportLength - data payload length;
\param[in] reportPayload - data pointer
******************************************************************************/
static void ciOnOffReportInd(ZCL_Addressing_t *addressing, uint8_t reportLength, uint8_t *reportPayload)
{
  ZCL_Report_t *rep = (ZCL_Report_t *)reportPayload;

  LOG_STRING(reportAttrIndStr, "<-On/Off Attr Report: t = %d\r\n");
  appSnprintf(reportAttrIndStr, (int)rep->value[0]);

  (void)addressing, (void)reportLength, (void)rep;
}
/**************************************************************************//**
\brief Indication of configure reporting response

\param[in] ntfy - pointer to response
******************************************************************************/
static void ZCL_ConfigureReportingResp(ZCL_Notify_t *ntfy)
{
  (void)ntfy;
}
#endif // APP_DEVICE_TYPE_COMBINED_INTERFACE

// eof ciOnOffCluster.c

