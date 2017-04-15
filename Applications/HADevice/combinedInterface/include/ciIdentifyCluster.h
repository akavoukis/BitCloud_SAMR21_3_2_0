/**************************************************************************//**
  \file ciIdentifyCluster.h

  \brief
    Combined Interface Identify cluster interface.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2013, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    04.09.13 N. Fomin - Created.
******************************************************************************/
#ifndef _CIIDENTIFYCLUSTER_H
#define _CIIDENTIFYCLUSTER_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zclIdentifyCluster.h>
#include <haClusters.h>

/******************************************************************************
                    Externals
******************************************************************************/
extern ZCL_IdentifyClusterAttributes_t ciIdentifyClusterServerAttributes;
extern ZCL_IdentifyClusterCommands_t   ciIdentifyCommands;

/******************************************************************************
                    Prototypes section
******************************************************************************/
/**************************************************************************//**
\brief Sends Identify command

\param[in] mode - address mode;
\param[in] addr - short address of destination node;
\param[in] ep   - destination endpoint;
\param[in] time - identify time
******************************************************************************/
void identifySendIdentify(APS_AddrMode_t mode,ShortAddr_t addr, Endpoint_t ep,
  uint16_t time);

/**************************************************************************//**
\brief Sends EZ-Mode Invoke command

\param[in] mode   - address mode;
\param[in] addr   - short address of destination node;
\param[in] ep     - destination endpoint;
\param[in] action - action to be done upon reception
******************************************************************************/
void identifySendEzModeInvoke(APS_AddrMode_t mode,ShortAddr_t addr, Endpoint_t ep,
  uint8_t action);

/**************************************************************************//**
\brief Sends Read Attribute command unicastly

\param[in] mode - address mode;
\param[in] addr - short address of destination node;
\param[in] ep   - destination endpoint;
\param[in] attr - attribute id;
\param[in] cb   - callback function
******************************************************************************/
void identifyReadAttribute(APS_AddrMode_t mode,ShortAddr_t addr, Endpoint_t ep,  
  uint16_t attr, AttibuteReadCallback_t cb);

/**************************************************************************//**
\brief Sends Write Attribute command unicastly

\param[in] mode - address mode;
\param[in] addr - short address of destination node;
\param[in] attr - attribute id;
\param[in] ep   - destination endpoint;
\param[in] type - attribute type;
\param[in] cb   - callback function;
\param[in] data - the pointer to memory with value to be written;
\param[in] size - size of data parameter in octets
******************************************************************************/
void identifyWriteAttribute(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep,
  uint16_t attr, uint8_t type, AttributeWriteCallback_t cb, void *data, uint8_t size);

#endif // _CIIDENTIFYCLUSTER_H

// eof ciIdentifyCluster.h

