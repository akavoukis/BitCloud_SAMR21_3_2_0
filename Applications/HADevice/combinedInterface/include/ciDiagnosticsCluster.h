/**************************************************************************//**
  \file ciDiagnosticsCluster.h

  \brief
    Combined Interface diagnostics cluster interface.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2013, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    11/06/2014 Parthasarathy G - Created.
******************************************************************************/
#ifndef _CIDIAGNOSTICSCLUSTER_H
#define _CIDIAGNOSTICSCLUSTER_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zclDiagnosticsCluster.h>
#include <haClusters.h>
/******************************************************************************
                    Defines section
******************************************************************************/

/******************************************************************************
                    Prototypes section
******************************************************************************/

/**************************************************************************//**
\brief Initializes Diagnostics cluster
******************************************************************************/
void diagnosticsClusterInit(void);

/**************************************************************************//**
\brief Sends Read Attribute command unicastly

\param[in] mode - address mode;
\param[in] addr - short address of destination node;
\param[in] ep   - destination endpoint;
\param[in] attr - attribute id;
\param[in] cb   - callback function
******************************************************************************/
void diagnosticsReadAttribute(APS_AddrMode_t mode,ShortAddr_t addr, Endpoint_t ep,
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
void diagnosticsWriteAttribute(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep,
  uint16_t attr, uint8_t type, AttributeWriteCallback_t cb, void *data, uint8_t size);


#endif // _CIDIAGNOSTICSCLUSTER_H

// eof ciDiagnosticsCluster.h
