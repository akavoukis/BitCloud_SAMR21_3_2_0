/**************************************************************************//**
  \file colorSceneRemoteBasicCluster.h

  \brief
    Color Scene Remote device Basic cluster interface.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    28.06.11 A. Taradov - Created.
******************************************************************************/
#ifndef _COLORSCENEREMOTEBASICCLUSTER_H
#define _COLORSCENEREMOTEBASICCLUSTER_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zcl.h>
#include <zclZllBasicCluster.h>

/******************************************************************************
                    Externals
******************************************************************************/
extern ZCL_BasicClusterServerAttributes_t basicClusterServerAttributes;

/******************************************************************************
                    Prototypes section
******************************************************************************/
/**************************************************************************//**
\brief Initialize Basic cluster.
******************************************************************************/
void basicClusterInit(void);

/**************************************************************************//**
\brief Sends Basic Cluster read attribute command

\param[in] attributeId - attribute of interest identifier
******************************************************************************/
void basicSendReadAttribute(uint16_t attributeId);

/**************************************************************************//**
\brief Sends Basic Cluster write attribute command

\param[in] attributeId - attribute of interest identifier
******************************************************************************/
void basicSendWriteAttribute(uint16_t attributeId, void *value, uint8_t type);

#endif // _COLORSCENEREMOTEBASICCLUSTER_H

// eof colorSceneRemoteBasicCluster.h
