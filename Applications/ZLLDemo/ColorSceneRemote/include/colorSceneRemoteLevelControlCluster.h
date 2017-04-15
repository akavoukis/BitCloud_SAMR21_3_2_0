/**************************************************************************//**
  \file colorSceneRemoteLevelControlCluster.h

  \brief
    Color Scene Remote device Level Control cluster interface.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    28.06.11 A. Taradov - Created.
******************************************************************************/
#ifndef _COLORSCENEREMOTELEVELCONTROLCLUSTER_H
#define _COLORSCENEREMOTELEVELCONTROLCLUSTER_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zcl.h>
#include <zclZllLevelControlCluster.h>

/******************************************************************************
                    Externals
******************************************************************************/
extern ZCL_LevelControlClusterCommands_t levelControlClusterCommands;

/******************************************************************************
                    Prototypes section
******************************************************************************/
#if APP_ENABLE_CERTIFICATION_EXTENSION == 0
/**************************************************************************//**
\brief Sends Move To Level command

\param[in] mode  - address mode;
\param[in] addr  - short address of destination node or number of group;
\param[in] level - color level;
\param[in] time  - transition time;
\param[in] ep    - endpoint number of destination device
******************************************************************************/
void colorSceneRemoteSendMoveToLevelCommand(APS_AddrMode_t mode, ShortAddr_t addr, uint8_t level, uint16_t time, Endpoint_t ep);

#else // APP_ENABLE_CERTIFICATION_EXTENSION == 1
/**************************************************************************//**
\brief Sends commands without payload

\param[in] command - command identifier
******************************************************************************/
void colorSceneRemoteSendLevelControlCommand(uint8_t command);

/**************************************************************************//**
\brief Sends move to level command (ZCL_LEVEL_CONTROL_CLUSTER_MOVE_TO_LEVEL_COMMAND_ID or
                                    ZCL_LEVEL_CONTROL_CLUSTER_MOVE_TO_LEVEL_W_ONOFF_COMMAND_ID)

\param[in] command - command identifier
\param[in] level - color level;
\param[in] time  - transition time;
******************************************************************************/
void colorSceneRemoteSendMoveToLevelCommand(uint8_t command, uint8_t level, uint16_t time);

/**************************************************************************//**
\brief Sends move command

\param[in] command - command identifier (ZCL_LEVEL_CONTROL_CLUSTER_MOVE_W_ONOFF_COMMAND_ID
                     or ZCL_LEVEL_CONTROL_CLUSTER_MOVE_COMMAND_ID);
\param[in] moveMode - move type;
\param[in] rate - rate in units per second;
******************************************************************************/
void colorSceneRemoteSendMoveCommand(uint8_t command, uint8_t moveMode, uint8_t rate);

/**************************************************************************//**
\brief Sends move command

\param[in] command - command identifier (ZCL_LEVEL_CONTROL_CLUSTER_STEP_W_ONOFF_COMMAND_ID
                     or ZCL_LEVEL_CONTROL_CLUSTER_STEP_COMMAND_ID);
\param[in] stepMode - step type;
\param[in] size - step size;
\param[in] time - transition time;
******************************************************************************/
void colorSceneRemoteSendStepCommand(uint8_t command, uint8_t stepMode, uint8_t size, uint16_t time);

/**************************************************************************//**
\brief Sends Level control Cluster read attribute command

\param[in] attributeId - attribute of interest identifier
******************************************************************************/
void levelControlSendReadAttribute(uint16_t attributeId);
#endif // APP_ENABLE_CERTIFICATION_EXTENSION

#endif // _COLORSCENEREMOTELEVELCONTROLCLUSTER_H

// eof colorSceneRemoteLevelControlCluster.h
