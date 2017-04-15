/**************************************************************************//**
  \file bridgeColorControlCluster.h

  \brief
    Control Bridge device Color Control cluster interface.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2013, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    22.01.13 N. Fomin - Created.
******************************************************************************/
#ifndef _BRIDGECOLORCONTROLCLUSTER_H
#define _BRIDGECOLORCONTROLCLUSTER_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zclZllColorControlCluster.h>

/******************************************************************************
                    Externals
******************************************************************************/
extern ZCL_ColorControlClusterCommands_t colorControlClusterCommands;

/******************************************************************************
                    Prototypes
******************************************************************************/
/**************************************************************************//**
\brief Sends Move To Hue And Saturation command

\param[in] mode       - address mode;
\param[in] addr       - short address of destination node or number of group;
\param[in] ep         - endpoint number of destination device
\param[in] hue        - hue;
\param[in] saturation - saturation;
\param[in] time       - transition time
******************************************************************************/
void bridgeSendMoveToHueAndSaturationCommand(APS_AddrMode_t mode, ShortAddr_t addr,
                                             Endpoint_t ep, uint8_t hue, uint8_t saturation,
                                             uint16_t time);

/**************************************************************************//**
\brief Sends Step Saturation command

\param[in] addrMode - address mode;
\param[in] addr     - short address of destination node or number of group;
\param[in] ep       - endpoint number of destination device;
\param[in] mode     - step mode;
\param[in] size     - step size;
\param[in] time     - transition time
******************************************************************************/
void bridgeSendStepSaturationCommand(APS_AddrMode_t addrMode, ShortAddr_t addr,
                                               Endpoint_t ep, uint8_t mode, uint8_t size, uint16_t time);

#endif // _BRIDGECOLORCONTROLCLUSTER_H

// eof bridgeColorControlCluster.h
