/**************************************************************************//**
  \file bridgeGroupsCluster.h

  \brief
    Color Scene Remote device Groups cluster interface.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2013, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    22.01.13 N. Fomin - Created.
******************************************************************************/
#ifndef _BRIDGEGROUPSCLUSTER_H
#define _BRIDGEGROUPSCLUSTER_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zcl.h>
#include <zclZllGroupsCluster.h>

/******************************************************************************
                    Externals
******************************************************************************/
extern ZCL_GroupsClusterCommands_t groupsClusterCommands;

/******************************************************************************
                    Prototypes section
******************************************************************************/
/**************************************************************************//**
\brief Sends Add Group command

\param[in] mode    - address mode;
\param[in] addr    - network address of destination node;
\param[in] ep      - endpoint number of destination node;
\param[in] groupId - group id
******************************************************************************/
void bridgeSendAddGroupCommand(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep, uint16_t groupId);

/**************************************************************************//**
\brief Sends Remove Group command

\param[in] mode    - address mode;
\param[in] addr    - network address of destination node;
\param[in] ep      - endpoint number of destination node;
\param[in] groupId - group id
******************************************************************************/
void bridgeSendRemoveGroupCommand(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep, uint16_t groupId);

#endif // _BRIDGEGROUPSCLUSTER_H

// eof bridgeGroupsCluster.h
