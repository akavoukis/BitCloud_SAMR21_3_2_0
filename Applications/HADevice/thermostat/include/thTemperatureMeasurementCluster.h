/**************************************************************************//**
  \file thTemperatureMeasurementCluster.h

  \brief
    Thermostat Temperature Measurement cluster interface.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:    
   21.11.14  Parthasarathy G - Created
******************************************************************************/
#ifndef _THTEMPERATUREMEASUREMENTCLUSTER_H
#define _THTEMPERATUREMEASUREMENTCLUSTER_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zclTemperatureMeasurementCluster.h>
#include <haClusters.h>

/******************************************************************************
                    Definition(s) section
******************************************************************************/
#define TEMPERATURE_MEASUREMENT_VAL_MIN_REPORT_PERIOD 30
#define TEMPERATURE_MEASUREMENT_VAL_MAX_REPORT_PERIOD 40

/* Some default values for attributes */
#define APP_TEMPERATURE_MEASUREMENT_MEASURED_VALUE_ATTRIBUTE_VALUE       0x5000
#define APP_TEMPERATURE_MEASUREMENT_MIN_MEASURED_VALUE_ATTRIBUTE_VALUE   0x954d //range 0x954d – 0x7ffe
#define APP_TEMPERATURE_MEASUREMENT_MAX_MEASURED_VALUE_ATTRIBUTE_VALUE   0x7fff //range 0x954e – 0x7fff
#define APP_TEMPERATURE_MEASUREMENT_TOLERANCE_ATTRIBUTE_VALUE            0x0100 //0x0000 – 0x0800

#define APP_TEMPERATURE_MEASUREMENT_MEASURED_VALUE_PERIODIC_CHANGE       1000 //corresponding to 10 degree celsius
/******************************************************************************
                    Externals
******************************************************************************/
extern ZCL_TemperatureMeasurementClusterAttributes_t thTemperatureMeasurementClusterServerAttributes;

/******************************************************************************
                    Prototypes section
******************************************************************************/
/**************************************************************************//**
\brief Initializes Temperature Measurement cluster
******************************************************************************/
void thTemperatureMeasurementClusterInit(void);

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
void thTemperatureMeasurementReadAttribute(APS_AddrMode_t mode,ShortAddr_t addr, Endpoint_t ep,
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
void thTemperatureMeasurementWriteAttribute(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep,
  uint16_t attr, uint8_t type, AttributeWriteCallback_t cb, void *data, uint8_t size);

/**************************************************************************//**
\brief Sends the Configure Reporting for Temperature Measurement cluster

\param[in] mode - address mode;
\param[in] addr - short address of destination node;
\param[in] ep   - destination endpoint;
\param[in] min  - the minimum reporting interval;
\param[in] max  - the maximum reporting interval
******************************************************************************/
void thTemperatureMeasurementConfigureReporting(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep,
  ZCL_AttributeId_t attrId, uint8_t attrType, ZCL_ReportTime_t min, ZCL_ReportTime_t max);

/**************************************************************************//**
\brief Update the measured Value
******************************************************************************/
void thTempeartureMeasurementUpdateMeasuredValue(void);

#endif // _THTEMPERATUREMEASUREMENTCLUSTER_H

// eof thTemperatureMeasurementCluster.h
