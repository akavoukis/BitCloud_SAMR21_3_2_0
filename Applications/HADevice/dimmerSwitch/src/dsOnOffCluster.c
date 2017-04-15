/**************************************************************************//**
  \file dsOnOffCluster.c

  \brief
    Dimmer Switch On/Off cluster implementation.

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
#include <dsOnOffCluster.h>
#include <haClusters.h>
#include <uartManager.h>
#include <commandManager.h>

/******************************************************************************
                    Global variables section
******************************************************************************/
ZCL_OnOffClusterCommands_t dsOnOffCommands =
{
  ZCL_DEFINE_ONOFF_CLUSTER_COMMANDS(NULL, NULL, NULL)
};

/******************************************************************************
                    Prototypes section
******************************************************************************/
static void dsOnOffReportInd(ZCL_Addressing_t *addressing, uint8_t reportLength, uint8_t *reportPayload);

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
    cluster->ZCL_ReportInd = dsOnOffReportInd;
}

/**************************************************************************//**
\brief Sends On, Off or Toggle command to bound devices

\param[in] mode    - address mode;
\param[in] addr    - short address of destination node or number of group;
\param[in] ep      - endpoint number of destination device;
\param[in] command - command id
******************************************************************************/
void onOffSendOnOffToggle(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep, OnOffToggle_t command)
{
  ZCL_Request_t *req;

  if (!(req = getFreeCommand()))
    return;

  fillCommandRequest(req, command, 0);
  fillDstAddressing(&req->dstAddressing, mode, addr, ep, ONOFF_CLUSTER_ID);
  commandManagerSendCommand(req);
}

/**************************************************************************//**
\brief Report attribute indication handler

\param[in] addressing - pointer to addressing information;
\param[in] reportLength - data payload length;
\param[in] reportPayload - data pointer
******************************************************************************/
static void dsOnOffReportInd(ZCL_Addressing_t *addressing, uint8_t reportLength, uint8_t *reportPayload)
{
  ZCL_Report_t *rep = (ZCL_Report_t *)reportPayload;

  LOG_STRING(reportAttrIndStr, "<-On/Off Attr Report: t = %d\r\n");
  appSnprintf(reportAttrIndStr, (int)rep->value[0]);

  (void)addressing, (void)reportLength, (void)rep;
}

#endif // APP_DEVICE_TYPE_DIMMER_SWITCH

// eof dsOnOffCluster.c

