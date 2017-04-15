/**************************************************************************//**
  \file ciLevelControlCluster.c

  \brief
    Combined Interface Level Control cluster implementation.

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
#include <ciLevelControlCluster.h>
#include <uartManager.h>
#include <commandManager.h>
#include <haClusters.h>

/******************************************************************************
                    Global variables section
******************************************************************************/
ZCL_LevelControlClusterCommands_t ciLevelControlCommands =
{
  ZCL_DEFINE_LEVEL_CONTROL_CLUSTER_COMMANDS(NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL)
};

/******************************************************************************
                    Prototypes section
******************************************************************************/
static void ciFillMoveToLevelPayload(ZCL_MoveToLevel_t *payload, uint8_t level, uint16_t time);
static void ciFillMovePayload(ZCL_Move_t *payload, uint8_t mode, uint8_t rate);
static void ciFillStepPayload(ZCL_Step_t *payload, uint8_t mode, uint8_t size, uint16_t time);

static void ciLevelReportInd(ZCL_Addressing_t *addressing, uint8_t reportLength, uint8_t *reportPayload);
static void ZCL_ConfigureReportingResp(ZCL_Notify_t *ntfy);
/******************************************************************************
                    Implementation section
******************************************************************************/
/**************************************************************************//**
\brief Initializes Level Control cluster
******************************************************************************/
void levelControlClusterInit(void)
{
  ZCL_Cluster_t *cluster = ZCL_GetCluster(APP_SRC_ENDPOINT_ID, LEVEL_CONTROL_CLUSTER_ID, ZCL_CLUSTER_SIDE_CLIENT);

  if (cluster)
    cluster->ZCL_ReportInd = ciLevelReportInd;
}

/**************************************************************************//**
\brief Sends Move To Level or Move To Level with On/Off command
  to bound devices

\param[in] mode  - address mode;
\param[in] addr  - short address of destination node or number of group;
\param[in] ep    - endpoint number of destination device;
\param[in] level - color level;
\param[in] time  - transition time in 1/10 of second;
\param[in] onOff - if true then Move To Level with On/Off command is sent,
  otherwise Move To Level command is sent
******************************************************************************/
void levelControlSendMoveToLevel(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep,
  uint8_t level, uint16_t time, bool onOff)
{
  ZCL_Request_t *req;
  uint8_t command = onOff ? ZCL_LEVEL_CONTROL_CLUSTER_MOVE_TO_LEVEL_W_ONOFF_COMMAND_ID :
    ZCL_LEVEL_CONTROL_CLUSTER_MOVE_TO_LEVEL_COMMAND_ID;

  if (!(req = getFreeCommand()))
    return;

  fillCommandRequest(req, command, sizeof(ZCL_MoveToLevel_t));
  ciFillMoveToLevelPayload((ZCL_MoveToLevel_t *)req->requestPayload, level, time);
  fillDstAddressing(&req->dstAddressing, mode, addr, ep, LEVEL_CONTROL_CLUSTER_ID);
  commandManagerSendCommand(req);
}

/**************************************************************************//**
\brief Sends Move or Move with On/Off command to bound devices

\param[in] mode     - address mode;
\param[in] addr     - short address of destination node or number of group;
\param[in] ep       - endpoint number of destination device;
\param[in] moveMode - mode mode;
\param[in] rate     - move rate;
\param[in] onOff    - if true then Move with On/Off command is sent,
  otherwise Move command is sent
******************************************************************************/
void levelControlSendMove(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep,
  uint8_t moveMode, uint8_t rate, bool onOff)
{
  ZCL_Request_t *req;
  uint8_t command = onOff ? ZCL_LEVEL_CONTROL_CLUSTER_MOVE_W_ONOFF_COMMAND_ID :
    ZCL_LEVEL_CONTROL_CLUSTER_MOVE_COMMAND_ID;

  if (!(req = getFreeCommand()))
    return;

  fillCommandRequest(req, command, sizeof(ZCL_Move_t));
  ciFillMovePayload((ZCL_Move_t *)req->requestPayload, moveMode, rate);
  fillDstAddressing(&req->dstAddressing, mode, addr, ep, LEVEL_CONTROL_CLUSTER_ID);
  commandManagerSendCommand(req);
}

/**************************************************************************//**
\brief Sends Step or Step with On/Off command to bound devices

\param[in] mode     - address mode;
\param[in] addr     - short address of destination node or number of group;
\param[in] ep       - endpoint number of destination device;
\param[in] stepMode - step mode;
\param[in] size     - step size;
\param[in] time     - transition time;
\param[in] onOff    - if true then Step with On/Off command is sent,
  otherwise Step command is sent
******************************************************************************/
void levelControlSendStep(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep,
  uint8_t stepMode, uint8_t size, uint16_t time, bool onOff)
{
  ZCL_Request_t *req;
  uint8_t command = onOff ? ZCL_LEVEL_CONTROL_CLUSTER_STEP_W_ONOFF_COMMAND_ID :
    ZCL_LEVEL_CONTROL_CLUSTER_STEP_COMMAND_ID;

  if (!(req = getFreeCommand()))
    return;

  fillCommandRequest(req, command, sizeof(ZCL_Step_t));
  ciFillStepPayload((ZCL_Step_t *)req->requestPayload, stepMode, size, time);
  fillDstAddressing(&req->dstAddressing, mode, addr, ep, LEVEL_CONTROL_CLUSTER_ID);
  commandManagerSendCommand(req);
}

/**************************************************************************//**
\brief Sends Stop or Stop with On/Off command to bound devices

\param[in] mode  - address mode;
\param[in] addr  - short address of destination node or number of group;
\param[in] ep    - endpoint number of destination device;
\param[in] onOff - if true then Stop with On/Off command is sent,
  otherwise Stop command is sent
******************************************************************************/
void levelControlSendStop(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep,
  bool onOff)
{
  ZCL_Request_t *req;
  uint8_t command = onOff ? ZCL_LEVEL_CONTROL_CLUSTER_STOP_W_ONOFF_COMMAND_ID :
    ZCL_LEVEL_CONTROL_CLUSTER_STOP_COMMAND_ID;

  if (!(req = getFreeCommand()))
    return;

  fillCommandRequest(req, command, 0);
  fillDstAddressing(&req->dstAddressing, mode, addr, ep, LEVEL_CONTROL_CLUSTER_ID);
  commandManagerSendCommand(req);
}

/**************************************************************************//**
\brief Fills Move To Level command structure

\param[out] payload - pointer to command structure;
\param[in]  level   - color level;
\param[in]  time    - transition time
******************************************************************************/
static void ciFillMoveToLevelPayload(ZCL_MoveToLevel_t *payload, uint8_t level, uint16_t time)
{
  payload->level          = level;
  payload->transitionTime = time;
}

/**************************************************************************//**
\brief Fills Move command structure

\param[out] payload - pointer to command structure;
\param[in]  mode    - move mode;
\param[in]  rate    - move rate
******************************************************************************/
static void ciFillMovePayload(ZCL_Move_t *payload, uint8_t mode, uint8_t rate)
{
  payload->moveMode = mode;
  payload->rate     = rate;
}

/**************************************************************************//**
\brief Fills Step command structure

\param[out] payload - pointer to command structure;
\param[in]  mode    - move mode;
\param[in]  size    - step size;
\param[in]  time    - transition time
******************************************************************************/
static void ciFillStepPayload(ZCL_Step_t *payload, uint8_t mode, uint8_t size, uint16_t time)
{
  payload->stepMode       = mode;
  payload->stepSize       = size;
  payload->transitionTime = time;
}
/**************************************************************************//**
\brief Sends the Configure Reporting for level control cluster

\param[in] mode - address mode;
\param[in] addr - short address of destination node;
\param[in] ep   - destination endpoint;
\param[in] attrId - attribute id;
\param[in] attrType - attribute type
\param[in] min  - the minimum reporting interval;
\param[in] max  - the maximum reporting interval
******************************************************************************/
void levelControlConfigureReporting(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep,
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
  fillDstAddressing(&req->dstAddressing, mode, addr, ep, LEVEL_CONTROL_CLUSTER_ID);
  req->ZCL_Notify = ZCL_ConfigureReportingResp;

  commandManagerSendAttribute(req);
}
/**************************************************************************//**
\brief Report attribute indication handler

\param[in] addressing - pointer to addressing information;
\param[in] reportLength - data payload length;
\param[in] reportPayload - data pointer
******************************************************************************/
static void ciLevelReportInd(ZCL_Addressing_t *addressing, uint8_t reportLength, uint8_t *reportPayload)
{
  ZCL_Report_t *rep = (ZCL_Report_t *)reportPayload;

  LOG_STRING(reportAttrIndStr, "<-Level Control Attr Report: t = %d\r\n");
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
// eof ciLevelControlCluster.c

