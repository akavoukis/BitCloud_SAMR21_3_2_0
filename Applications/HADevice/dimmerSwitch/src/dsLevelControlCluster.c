/**************************************************************************//**
  \file dsLevelControlCluster.c

  \brief
    Dimmer Switch Level Control cluster implementation.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    13.12.12 N. Fomin - Created.
******************************************************************************/
#ifdef APP_DEVICE_TYPE_DIMMER_SWITCH

/******************************************************************************
                    Includes section
******************************************************************************/
#include <dlLevelControlCluster.h>
#include <uartManager.h>
#include <commandManager.h>
#include <haClusters.h>

/******************************************************************************
                    Global variables section
******************************************************************************/
ZCL_LevelControlClusterCommands_t dsLevelControlCommands =
{
  ZCL_DEFINE_LEVEL_CONTROL_CLUSTER_COMMANDS(NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL)
};

/******************************************************************************
                    Prototypes section
******************************************************************************/
static void dsFillMoveToLevelPayload(ZCL_MoveToLevel_t *payload, uint8_t level, uint16_t time);
static void dsFillMovePayload(ZCL_Move_t *payload, uint8_t mode, uint8_t rate);
static void dsFillStepPayload(ZCL_Step_t *payload, uint8_t mode, uint8_t size, uint16_t time);

static void dsLevelReportInd(ZCL_Addressing_t *addressing, uint8_t reportLength, uint8_t *reportPayload);

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
    cluster->ZCL_ReportInd = dsLevelReportInd;
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
  dsFillMoveToLevelPayload((ZCL_MoveToLevel_t *)req->requestPayload, level, time);
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
  dsFillMovePayload((ZCL_Move_t *)req->requestPayload, moveMode, rate);
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
  dsFillStepPayload((ZCL_Step_t *)req->requestPayload, stepMode, size, time);
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
static void dsFillMoveToLevelPayload(ZCL_MoveToLevel_t *payload, uint8_t level, uint16_t time)
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
static void dsFillMovePayload(ZCL_Move_t *payload, uint8_t mode, uint8_t rate)
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
static void dsFillStepPayload(ZCL_Step_t *payload, uint8_t mode, uint8_t size, uint16_t time)
{
  payload->stepMode       = mode;
  payload->stepSize       = size;
  payload->transitionTime = time;
}

/**************************************************************************//**
\brief Report attribute indication handler

\param[in] addressing - pointer to addressing information;
\param[in] reportLength - data payload length;
\param[in] reportPayload - data pointer
******************************************************************************/
static void dsLevelReportInd(ZCL_Addressing_t *addressing, uint8_t reportLength, uint8_t *reportPayload)
{
  ZCL_Report_t *rep = (ZCL_Report_t *)reportPayload;

  LOG_STRING(reportAttrIndStr, "<-Level Control Attr Report: t = %d\r\n");
  appSnprintf(reportAttrIndStr, (int)rep->value[0]);

  (void)addressing, (void)reportLength, (void)rep;
}

#endif // APP_DEVICE_TYPE_DIMMER_SWITCH
// eof dsLevelControlCluster.c

