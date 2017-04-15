/**************************************************************************//**
  \file bridgeScenesCluster.h

  \brief
    Control Bridge device Scenes cluster interface.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2013, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    22.01.13 N. Fomin - Created.
******************************************************************************/
#ifndef _BRIDGESCENESCLUSTER_H
#define _BRIDGESCENESCLUSTER_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zcl.h>
#include <zclZllScenesCluster.h>

/******************************************************************************
                    Externals section
******************************************************************************/
extern ZCL_ScenesClusterCommands_t scenesClusterCommands;

/******************************************************************************
                    Prototypes section
******************************************************************************/
/**************************************************************************//**
\brief Sends Store/Recall/Remove Scene command

\param[in] mode    - address mode;
\param[in] addr    - short address of destination node or number of group;
\param[in] ep      - endpoint number of destination device;
\param[in] command - command id;
\param[in] group   - id of a group;
\param[in] scene   - id of a scene
******************************************************************************/
void bridgeStoreRecallRemoveSceneCommand(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep,
                                                   uint8_t command, uint16_t group, uint8_t scene);

#endif // _BRIDGESCENESCLUSTER_H

// eof bridgeScenesCluster.h
