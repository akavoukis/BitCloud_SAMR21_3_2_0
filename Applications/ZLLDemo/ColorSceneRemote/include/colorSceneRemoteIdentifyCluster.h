/**************************************************************************//**
  \file colorSceneRemoteIdentifyCluster.h

  \brief
    Color Scene Remote device Identify cluster interface.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    28.06.11 A. Taradov - Created.
******************************************************************************/
#ifndef _COLORSCENEREMOTEIDENTIFYCLUSTER_H
#define _COLORSCENEREMOTEIDENTIFYCLUSTER_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zcl.h>
#include <zclZllIdentifyCluster.h>

/******************************************************************************
                    Externals
******************************************************************************/
extern ZCL_IdentifyClusterCommands_t identifyClusterCommands;

/******************************************************************************
                    Prototypes section
******************************************************************************/
/**************************************************************************//**
\brief Initialize Identify cluster.
******************************************************************************/
void identifyClusterInit(void);

#if APP_ENABLE_CERTIFICATION_EXTENSION == 0
/**************************************************************************//**
\brief Sends Identify command

\param[in] mode  - address mode;
\param[in] addr  - short address of destination node or number of group;
\param[in] ep    - endpoint number of destination device
******************************************************************************/
void colorSceneRemoteSendIdentifyCommand(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep);

#else // APP_ENABLE_CERTIFICATION_EXTENSION == 1
/**************************************************************************//**
\brief Sends Identify command
******************************************************************************/
void colorSceneRemoteSendIdentifyCommand(uint16_t identifyTime);

/**************************************************************************//**
\brief Sends Identify Query command
******************************************************************************/
void colorSceneRemoteSendIdentifyQueryCommand(void);

/**************************************************************************//**
\brief Sends Trigger Effect command
******************************************************************************/
void colorSceneRemoteSendTriggerEffectCommand(uint8_t effectIdentifier, uint8_t effectVariant);

/**************************************************************************//**
\brief Sends Identify Cluster read attribute command

\param[in] attributeId - attribute of interest identifier
******************************************************************************/
void identifySendReadAttribute(uint16_t attributeId);

/**************************************************************************//**
\brief Sends Identify Cluster write attribute command

\param[in] attributeId - attribute of interest identifier
******************************************************************************/
void identifySendWriteAttribute(uint16_t attributeId, void *value, uint8_t type);
#endif // APP_ENABLE_CERTIFICATION_EXTENSION

#endif // _COLORSCENEREMOTEIDENTIFYCLUSTER_H

// eof colorSceneRemoteIdentifyCluster.h
