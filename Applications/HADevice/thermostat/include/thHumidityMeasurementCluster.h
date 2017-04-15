/**************************************************************************//**
  \file thHumidityMeasurementCluster.h

  \brief
    Thermostat Relative Humidity Measurement cluster interface.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    06.11.14 Viswanadham Kotla - Created.
******************************************************************************/
#ifndef _THHUMIDITYMEASUREMENTCLUSTER_H
#define _THHUMIDITYMEASUREMENTCLUSTER_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zclHumidityMeasurementCluster.h>
#include <haClusters.h>

/******************************************************************************
                    Definition(s) section
******************************************************************************/
#define HUMIDITY_MEASUREMENT_VAL_MIN_REPORT_PERIOD 15
#define HUMIDITY_MEASUREMENT_VAL_MAX_REPORT_PERIOD 25

/* Some default values for attributes */
#define APP_HUMIDITY_MEASUREMENT_MEASURED_VALUE_ATTRIBUTE_VALUE       0x1000
#define APP_HUMIDITY_MEASUREMENT_MIN_MEASURED_VALUE_ATTRIBUTE_VALUE   0x0000 //range 0x0 – 0x270f
#define APP_HUMIDITY_MEASUREMENT_MAX_MEASURED_VALUE_ATTRIBUTE_VALUE   0x2710 //range 0x954e – 0x2710
#define APP_HUMIDITY_MEASUREMENT_TOLERANCE_ATTRIBUTE_VALUE            0x0100 //0x0000 – 0x0800

#define APP_HUMIDITY_MEASUREMENT_MEASURED_VALUE_PERIODIC_CHANGE       1000 //coresponding to 10%
/******************************************************************************
                    Externals
******************************************************************************/
extern ZCL_HumidityMeasurementClusterAttributes_t thHumidityMeasurementClusterServerAttributes;

/******************************************************************************
                    Prototypes section
******************************************************************************/
/**************************************************************************//**
\brief Initializes Humidity Measurement cluster
******************************************************************************/
void humidityMeasurementClusterInit(void);

/**************************************************************************//**
\brief Update the measured Value
******************************************************************************/
void humidityMeasurementUpdateMeasuredValue(void);

/**************************************************************************//**
\brief Update the tolerance value
******************************************************************************/
void humidityMeasurementUpdateTolerance(void);

/**************************************************************************//**
\brief Sends Read Attribute command unicastly

\param[in] mode - address mode;
\param[in] addr - short address of destination node;
\param[in] ep   - destination endpoint;
\param[in] attr - attribute id;
\param[in] cb   - callback function
******************************************************************************/
void humidityMeasurementReadAttribute(APS_AddrMode_t mode,ShortAddr_t addr, Endpoint_t ep,
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
void humidityMeasurementWriteAttribute(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep,
  uint16_t attr, uint8_t type, AttributeWriteCallback_t cb, void *data, uint8_t size);

/**************************************************************************//**
\brief Configure reporting for Humidity Measurement cluster

\param[in] mode     - address mode;
\param[in] addr     - short address of destination node;
\param[in] ep       - destination endpoint;
\param[in] attrId   - attribute id;
\param[in] attrType - attribute type;
\param[in] min      - the minimum reporting interval;
\param[in] max      - the maximum reporting interval
******************************************************************************/
void humidityMeasurementConfigureReporting(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep,
  ZCL_AttributeId_t attrId, uint8_t attrType, ZCL_ReportTime_t min, ZCL_ReportTime_t max);

#endif // _THHUMIDITYMEASUREMENTCLUSTER_H

// eof thHumidityMeasurementCluster.h
