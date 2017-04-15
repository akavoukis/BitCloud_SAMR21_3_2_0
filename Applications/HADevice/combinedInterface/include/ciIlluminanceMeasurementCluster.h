/**************************************************************************//**
  \file ciIlluminanceMeasurementCluster.h

  \brief
    Combined Interface illuminance Measurement cluster interface.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    12.06.14 Yogesh Bellan - Created.
******************************************************************************/
#ifndef _CIILLUMINANCEMEASUREMENTCLUSTER_H
#define _CIILLUMINANCEMEASUREMENTCLUSTER_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zclIlluminanceMeasurementCluster.h>
#include <haClusters.h>

/******************************************************************************
                    Prototypes section
******************************************************************************/
/**************************************************************************//**
\brief Initializes Occupancy Sensing cluster
******************************************************************************/
void illuminanceMeasurementClusterInit(void);

/**************************************************************************//**
\brief Sends Read Attribute command unicastly

\param[in] mode - address mode;
\param[in] addr - short address of destination node;
\param[in] ep   - destination endpoint;
\param[in] attr - attribute id;
\param[in] cb   - callback function
******************************************************************************/
void illuminanceMeasuredValueReadAttribute(APS_AddrMode_t mode,ShortAddr_t addr, Endpoint_t ep,
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
void illuminanceMeasuredValueWriteAttribute(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep,
  uint16_t attr, uint8_t type, AttributeWriteCallback_t cb, void *data, uint8_t size);

/**************************************************************************//**
\brief Sends the Configure Reporting for iLLuminance Measurement cluster

\param[in] mode - address mode;
\param[in] addr - short address of destination node;
\param[in] ep   - destination endpoint;
\param[in] min  - the minimum reporting interval;
\param[in] max  - the maximum reporting interval
******************************************************************************/
void illuminanceMeasurementConfigureReporting(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep,
  ZCL_AttributeId_t attrId, uint8_t attrType, ZCL_ReportTime_t min, ZCL_ReportTime_t max);

#endif // _CIBOCCUPANCYSENSINGCLUSTER_H

// eof ciIlluminanceMeasurementCluster.h
