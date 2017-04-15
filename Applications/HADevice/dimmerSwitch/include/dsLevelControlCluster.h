/**************************************************************************//**
  \file dsLevelControlCluster.h

  \brief
    Dimmer Switch Level Control cluster interface.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    13.12.12 N. Fomin - Created.
******************************************************************************/
#ifndef _DSLEVELCONTROLCLUSTER_H
#define _DSLEVELCONTROLCLUSTER_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zclLevelControlCluster.h>

/******************************************************************************
                    Externals
******************************************************************************/
extern ZCL_LevelControlClusterCommands_t dsLevelControlCommands;

/******************************************************************************
                    Prototypes section
******************************************************************************/
/**************************************************************************//**
\brief Initializes Level Control cluster
******************************************************************************/
void levelControlClusterInit(void);

/**************************************************************************//**
\brief Sends Move To Level or Move To Level with On/Off command
  to bound devices

\param[in] mode  - address mode;
\param[in] addr  - short address of destination node or number of group;
\param[in] ep    - endpoint number of destination device;
\param[in] level - color level;
\param[in] time  - transition time in 1/10 of second;
\param[in] onOff - if true then Move To Level with On/Off command is sent,
  otherwise Move To Level command is sent
******************************************************************************/
void levelControlSendMoveToLevel(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep,
  uint8_t level, uint16_t time, bool onOff);

/**************************************************************************//**
\brief Sends Move or Move with On/Off command to bound devices

\param[in] mode     - address mode;
\param[in] addr     - short address of destination node or number of group;
\param[in] ep       - endpoint number of destination device;
\param[in] moveMode - mode mode;
\param[in] rate     - move rate;
\param[in] onOff    - if true then Move with On/Off command is sent,
  otherwise Move command is sent
******************************************************************************/
void levelControlSendMove(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep,
  uint8_t moveMode, uint8_t rate, bool onOff);

/**************************************************************************//**
\brief Sends Step or Step with On/Off command to bound devices

\param[in] mode     - address mode;
\param[in] addr     - short address of destination node or number of group;
\param[in] ep       - endpoint number of destination device;
\param[in] stepMode - step mode;
\param[in] size     - step size;
\param[in] time     - transition time;
\param[in] onOff    - if true then Step with On/Off command is sent,
  otherwise Step command is sent
******************************************************************************/
void levelControlSendStep(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep,
  uint8_t stepMode, uint8_t size, uint16_t time, bool onOff);

/**************************************************************************//**
\brief Sends Stop or Stop with On/Off command to bound devices

\param[in] mode  - address mode;
\param[in] addr  - short address of destination node or number of group;
\param[in] ep    - endpoint number of destination device;
\param[in] onOff - if true then Stop with On/Off command is sent,
  otherwise Stop command is sent
******************************************************************************/
void levelControlSendStop(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep,
  bool onOff);

#endif // _DSLEVELCONTROLCLUSTER_H

// eof dsLevelControlCluster.h

