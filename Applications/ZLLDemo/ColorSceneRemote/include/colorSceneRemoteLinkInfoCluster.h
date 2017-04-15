/**************************************************************************//**
  \file colorSceneRemoteLinkInfoCluster.h

  \brief
    Color Scene Remote device Link Info cluster interface.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2013, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    25.01.13 N. Fomin - Created.
******************************************************************************/
#ifndef _COLORSCENEREMOTELINKINFOCLUSTER_H
#define _COLORSCENEREMOTELINKINFOCLUSTER_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zclLinkInfoCluster.h>
#include <zllDemo.h>

/******************************************************************************
                    Externals
******************************************************************************/
extern ZCL_LinkInfoClusterClientAttributes_t linkInfoClusterClientAttributes;
extern ZCL_LinkInfoClusterCommands_t         linkInfoCommands;

/******************************************************************************
                    Prototypes section
******************************************************************************/
/**************************************************************************//**
\brief Initialize Link Info cluster
******************************************************************************/
void linkInfoClusterInit(void);

/**************************************************************************//**
\brief Sends ReadyToTransmit command

\param[in] addr - short address of destination node or number of group;
\param[in] ep   - endpoint number of destination device
******************************************************************************/
void linkInfoSendReadyToTransmitCommand(ShortAddr_t addr, Endpoint_t ep);

/**************************************************************************//**
\brief Gets value of attribute number "i" of Link Info cluster

\param[in] i - attribute number

\returns pointer to attribute value
******************************************************************************/
BoundDevice_t *linkInfoGetAttrValue(uint8_t i);

#endif // _COLORSCENEREMOTELINKINFOCLUSTER_H

// eof colorSceneRemoteLinkInfoCluster.h
