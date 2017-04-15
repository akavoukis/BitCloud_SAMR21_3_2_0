/**************************************************************************//**
  \file ciOnOffCluster.h

  \brief
    Combined Interface On/Off cluster interface.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2013, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    04.09.13 N. Fomin - Created.
******************************************************************************/
#ifndef _CIONOFFCLUSTER_H
#define _CIONOFFCLUSTER_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zclOnOffCluster.h>

/******************************************************************************
                    Types section
******************************************************************************/
typedef enum
{
  OFF_COMMAND    = 0,
  ON_COMMAND     = 1,
  TOGGLE_COMMAND = 2
} OnOffToggle_t;

/******************************************************************************
                    Externals
******************************************************************************/
extern ZCL_OnOffClusterCommands_t ciOnOffCommands;

/******************************************************************************
                    Prototypes section
******************************************************************************/
/**************************************************************************//**
\brief Initializes On/Off cluster
******************************************************************************/
void onOffClusterInit(void);

/**************************************************************************//**
\brief Sends On, Off or Toggle command to bound devices

\param[in] mode    - address mode;
\param[in] addr    - short address of destination node or number of group;
\param[in] ep      - endpoint number of destination device;
\param[in] command - command id
******************************************************************************/
void onOffSendOnOffToggle(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep, OnOffToggle_t command);
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
  ZCL_AttributeId_t attrId, uint8_t attrType, ZCL_ReportTime_t min, ZCL_ReportTime_t max);
#endif // _CIONOFFCLUSTER_H

// eof ciOnOffCluster.h

