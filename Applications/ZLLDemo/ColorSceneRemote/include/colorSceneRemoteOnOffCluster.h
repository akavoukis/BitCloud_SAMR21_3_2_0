/**************************************************************************//**
  \file colorSceneRemoteOnOffCluster.h

  \brief
    Color Scene Remote device On/Off cluster interface.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    28.06.11 A. Taradov - Created.
******************************************************************************/
#ifndef _COLORSCENEREMOTEONOFFCLUSTER_H
#define _COLORSCENEREMOTEONOFFCLUSTER_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zcl.h>
#include <zclZllOnOffCluster.h>

/******************************************************************************
                    Externals
******************************************************************************/
extern ZCL_OnOffClusterCommands_t onOffClusterCommands;

/******************************************************************************
                    Prototypes section
******************************************************************************/
#if APP_ENABLE_CERTIFICATION_EXTENSION == 0
/**************************************************************************//**
\brief Sends On/Off command

\param[in] mode    - address mode;
\param[in] addr    - short address of destination node or number of group;
\param[in] command - 0 - off command, 1 - on command;
\param[in] ep      - endpoint number of destination device
******************************************************************************/
void colorSceneRemoteSendOnOffCommand(APS_AddrMode_t mode, ShortAddr_t addr, uint8_t command, Endpoint_t ep);

#else // APP_ENABLE_CERTIFICATION_EXTENSION == 1
/**************************************************************************//**
\brief Sends On/Off/Toggle commands

\param[in] command - 0 - off command, 1 - on command, 2 - toggle;
******************************************************************************/
void colorSceneRemoteSendOnOffCommand(uint8_t command);

/**************************************************************************//**
\brief Sends Off with Effect command

\param[in] effectIdentifier - identifier of the effect to be used
\param[in] effectVariant - effect variant
******************************************************************************/
void colorSceneRemoteSendOffWithEffectCommand(uint8_t effectIdentifier, uint8_t effectVariant);

/**************************************************************************//**
\brief Sends On with timed off command

\param[in] onOffControl - on/off control field value
\param[in] onTime - on time field value
\param[in] offWaitTime - off wait time value
******************************************************************************/
void colorSceneRemoteSendOnWithTimedOffCommand(uint8_t onOffControl, uint16_t onTime, uint16_t offWaitTime);

/**************************************************************************//**
\brief Sends On/off Cluster read attribute command

\param[in] attributeId - attribute of interest identifier
******************************************************************************/
void onOffSendReadAttribute(uint16_t attributeId);
#endif // APP_ENABLE_CERTIFICATION_EXTENSION
#endif // _COLORSCENEREMOTEONOFFCLUSTER_H

// eof colorSceneRemoteOnOffCluster.h
