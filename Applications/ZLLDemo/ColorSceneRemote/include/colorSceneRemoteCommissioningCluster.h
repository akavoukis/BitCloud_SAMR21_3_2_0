/**************************************************************************//**
  \file colorSceneRemoteCommissioningCluster.h

  \brief
    Color Scene Remote device Commissioning cluster interface.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    07.07.11  A. Taradov - Created.
******************************************************************************/
#ifndef _COLORSCENEREMOTECOMMISSIONINGCLUSTER_H
#define _COLORSCENEREMOTECOMMISSIONINGCLUSTER_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zcl.h>
#include <zclZllCommissioningCluster.h>

/******************************************************************************
                    Externals
******************************************************************************/
extern ZCL_CommissioningClusterCommands_t commissioningClusterCommands;

/**************************************************************************//**
\brief Send get group identifiers request command.

\param[in] addressing - target device addresing information.
******************************************************************************/
void colorSceneRemoteSendGroupIdentifiersReqCommand(uint8_t startIndx);

/**************************************************************************//**
\brief Send get endpoint list request command.

\param[in] addressing - target device addresing information.
******************************************************************************/
void colorSceneRemoteSendEndpointListReqCommand(uint8_t startIndx);

#endif // _COLORSCENEREMOTECOMMISSIONINGCLUSTER_H

// eof colorSceneRemoteCommissioningCluster.h
