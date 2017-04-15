/**************************************************************************//**
  \file ciTemperatureMeasurementCluster.h

  \brief
    Combined Interface Temepearture Measurement cluster interface.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2013, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    28.05.14 Viswanadham Kotla - Created.
******************************************************************************/
#ifndef _CITEMERATUREMEASUREMENTCLUSTER_H
#define _CITEMERATUREMEASUREMENTCLUSTER_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zclTemperatureMeasurementCluster.h>
#include <haClusters.h>
/******************************************************************************
                    Prototypes section
******************************************************************************/
/**************************************************************************//**
\brief Initializes Temepearture Measurement cluster
******************************************************************************/
void temperatureMeasurementClusterInit(void);

/******************************************************************************
                    Prototypes section
******************************************************************************/
/**************************************************************************//**
\brief Sends Read Attribute command unicastly

\param[in] mode - address mode;
\param[in] addr - short address of destination node;
\param[in] ep   - destination endpoint;
\param[in] attr - attribute id;
\param[in] cb   - callback function
******************************************************************************/
void temperatureMeasurementReadAttribute(APS_AddrMode_t mode,ShortAddr_t addr, Endpoint_t ep,
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
void temperatureMeasurementWriteAttribute(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep,
  uint16_t attr, uint8_t type, AttributeWriteCallback_t cb, void *data, uint8_t size);

/**************************************************************************//**
\brief Sends the Configure Reporting for Temperature Measurement cluster

\param[in] mode - address mode;
\param[in] addr - short address of destination node;
\param[in] ep   - destination endpoint;
\param[in] min  - the minimum reporting interval;
\param[in] max  - the maximum reporting interval
******************************************************************************/
void temperatureMeasurementConfigureReporting(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep,
  ZCL_AttributeId_t attrId, uint8_t attrType, ZCL_ReportTime_t min, ZCL_ReportTime_t max);

#endif // _CITEMERATUREMEASUREMENTCLUSTER_H

// eof ciTemperatureMeasurementCluster.h
