/**************************************************************************//**
  \file ciPowerConfigurationCluster.h

  \brief
    Combined Interface Power Configuration Cluster Interface.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2013, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    08/12/2014 Prashanth.Udumula - Created.
******************************************************************************/
#ifndef _CIPOWERCONFIGURATIONCLUSTER_H
#define _CIPOWERCONFIGURATIONCLUSTER_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zclPowerConfigurationCluster.h>
#include <haClusters.h>
/******************************************************************************
                    Defines section
******************************************************************************/

/******************************************************************************
                    Prototypes section
******************************************************************************/

/**************************************************************************//**
\brief Initializes Power Configuration cluster client
******************************************************************************/
void powerConfigurationClusterInit(void);

/**************************************************************************//**
\brief Sends Read Attribute command unicastly

\param[in] mode - address mode;
\param[in] addr - short address of destination node;
\param[in] ep   - destination endpoint;
\param[in] attr - attribute id;
\param[in] cb   - callback function
******************************************************************************/
void powerConfigurationReadAttribute(APS_AddrMode_t mode,ShortAddr_t addr, Endpoint_t ep,
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
void powerConfigurationWriteAttribute(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep,
  uint16_t attr, uint8_t type, AttributeWriteCallback_t cb, void *data, uint8_t size);

/**************************************************************************//**
\brief Sends the Configure reporting for power configuration cluster

\param[in] mode     - address mode;
\param[in] addr     - short address of destination node;
\param[in] ep       - destination endpoint;
\param[in] attrId   - attr id;
\param[in] attrType - attr id;
\param[in] min      - the minimum reporting interval;
\param[in] max      - the maximum reporting interval
******************************************************************************/
void powerConfigConfigureReporting(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep,
  ZCL_AttributeId_t attrId, uint8_t attrType, ZCL_ReportTime_t min, ZCL_ReportTime_t max);

#endif // _CIPOWERCONFIGURATIONCLUSTER_H

// eof ciPowerConfigurationCluster.h
