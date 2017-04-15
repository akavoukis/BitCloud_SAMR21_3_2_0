/**************************************************************************//**
  \file ciFanControlCluster.h

  \brief
    Combined Interface Fan Control Cluster Interface.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2013, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    17/11/2014 Parthasarathy G - Created.
******************************************************************************/
#ifndef _CIFANCONTROLCLUSTER_H
#define _CIFANCONTROLCLUSTER_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zclFanControlCluster.h>
#include <haClusters.h>
/******************************************************************************
                    Defines section
******************************************************************************/

/******************************************************************************
                    Prototypes section
******************************************************************************/

/**************************************************************************//**
\brief Initializes Fan Control cluster client
******************************************************************************/
void fanControlClusterInit(void);

/**************************************************************************//**
\brief Sends Read Attribute command unicastly

\param[in] mode - address mode;
\param[in] addr - short address of destination node;
\param[in] ep   - destination endpoint;
\param[in] attr - attribute id;
\param[in] cb   - callback function
******************************************************************************/
void fanControlReadAttribute(APS_AddrMode_t mode,ShortAddr_t addr, Endpoint_t ep,
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
void fanControlWriteAttribute(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep,
  uint16_t attr, uint8_t type, AttributeWriteCallback_t cb, void *data, uint8_t size);


#endif // _CIFANCONTROLCLUSTER_H

// eof ciFanControlCluster.h
