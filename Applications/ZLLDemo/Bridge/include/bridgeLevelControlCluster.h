/**************************************************************************//**
  \file bridgeLevelControlCluster.h

  \brief
    Control Bridge device Level Control cluster interface.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2013, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    22.01.13 N. Fomin - Created.
******************************************************************************/
#ifndef _BRIDGELEVELCONTROLCLUSTER_H
#define _BRIDGELEVELCONTROLCLUSTER_H

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
/**************************************************************************//**
\brief Sends Move To Level command

\param[in] mode  - address mode;
\param[in] addr  - short address of destination node or number of group;
\param[in] level - color level;
\param[in] time  - transition time;
\param[in] ep    - endpoint number of destination device
******************************************************************************/
void bridgeSendMoveToLevelCommand(APS_AddrMode_t mode, ShortAddr_t addr, uint8_t level,
                                            uint16_t time, Endpoint_t ep);

/**************************************************************************//**
\brief Sends Step Level command

\param[in] addrMode - address mode;
\param[in] addr     - short address of destination node or number of group;
\param[in] ep       - endpoint number of destination device;
\param[in] mode     - step mode;
\param[in] size     - step size;
\param[in] time     - transition time
******************************************************************************/
void bridgeSendStepLevelCommand(APS_AddrMode_t addrMode, ShortAddr_t addr, Endpoint_t ep,
                                          uint8_t mode, uint8_t size, uint16_t time);

#endif // _BRIDGELEVELCONTROLCLUSTER_H

// eof bridgeLevelControlCluster.h
