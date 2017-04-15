/**************************************************************************//**
  \file thOccupancySensingCluster.h

  \brief
    Thermostat Occupancy Sensing cluster interface.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    17.10.14 Viswanadham Kotla - Created.
******************************************************************************/
#ifndef _THOCCUPANCYSENSINGCLUSTER_H
#define THOCCUPANCYSENSINGCLUSTER_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zclOccupancySensingCluster.h>
#include <haClusters.h>

/******************************************************************************
                    Definition(s) section
******************************************************************************/
#define OCCUPANCY_SENSING_VAL_MIN_REPORT_PERIOD 10
#define OCCUPANCY_SENSING_VAL_MAX_REPORT_PERIOD 20

/******************************************************************************
                    Externals
******************************************************************************/
extern ZCL_OccupancySensingClusterServerAttributes_t thOccupancySensingClusterServerAttributes;

/******************************************************************************
                    Prototypes section
******************************************************************************/
/**************************************************************************//**
\brief Initializes Occupancy Sensing cluster
******************************************************************************/
void occupancySensingClusterInit(void);

/**************************************************************************//**
\brief Toggles occupancy
******************************************************************************/
void occupancySensingToggleOccupancy(void);

/**************************************************************************//**
\brief Sets occupancy to Occupiad state or Unoccupiad state
******************************************************************************/
void occupancySensingInitiateSetOccupancyState(bool state);

/**************************************************************************//**
\brief Sets occupancy to Occupiad state or Unoccupiad state
******************************************************************************/
void occupancySensingSetSensorType(uint8_t sensorType);

/**************************************************************************//**
\brief Sends Read Attribute command unicastly

\param[in] mode - address mode;
\param[in] addr - short address of destination node;
\param[in] ep   - destination endpoint;
\param[in] attr - attribute id;
\param[in] cb   - callback function
******************************************************************************/
void occupancySensingReadAttribute(APS_AddrMode_t mode,ShortAddr_t addr, Endpoint_t ep,
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
void occupancySensingWriteAttribute(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep,
  uint16_t attr, uint8_t type, AttributeWriteCallback_t cb, void *data, uint8_t size);

/**************************************************************************//**
\brief Sends the Configure Reporting for Occupancy Sensing cluster

\param[in] mode - address mode;
\param[in] addr - short address of destination node;
\param[in] ep   - destination endpoint;
\param[in] min  - the minimum reporting interval;
\param[in] max  - the maximum reporting interval
******************************************************************************/
void occupancySensingConfigureReporting(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep,
  ZCL_AttributeId_t attrId, uint8_t attrType, ZCL_ReportTime_t min, ZCL_ReportTime_t max);

#endif // _THOCCUPANCYSENSINGCLUSTER_H

// eof thOccupancySensingCluster.h
