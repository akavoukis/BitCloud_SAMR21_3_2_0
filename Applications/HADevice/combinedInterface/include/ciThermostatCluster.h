/**************************************************************************//**
  \file ciThermostatCluster.h

  \brief
    Combined Interface Thermostat cluster interface.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2013, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    09/09/2014 Unithra.C - Created.
******************************************************************************/
#ifndef _CITHERMOSTATCLUSTER_H
#define _CITHERMOSTATCLUSTER_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zclThermostatCluster.h>
#include <haClusters.h>
/******************************************************************************
                    Defines section
******************************************************************************/
#define THERMOSTAT_LOCAL_TEMPERATURE_SCALE 100
/******************************************************************************
                    Externals
******************************************************************************/
extern ZCL_ThermostatClusterCommands_t ciThermostatClusterCommands;

/******************************************************************************
                    Prototypes section
******************************************************************************/

/**************************************************************************//**
\brief Initializes Thermostat cluster
******************************************************************************/
void thermostatClusterInit(void);

/**************************************************************************//**
\brief Sends Read Attribute command unicastly

\param[in] mode - address mode;
\param[in] addr - short address of destination node;
\param[in] ep   - destination endpoint;
\param[in] attr - attribute id;
\param[in] cb   - callback function
******************************************************************************/
void thermostatReadAttribute(APS_AddrMode_t mode,ShortAddr_t addr, Endpoint_t ep,
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
void thermostatWriteAttribute(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep,
  uint16_t attr, uint8_t type, AttributeWriteCallback_t cb, void *data, uint8_t size);

/**************************************************************************//**
\brief Sends the Configure Reporting for Thermostat cluster

\param[in] mode     - address mode;
\param[in] addr     - short address of destination node;
\param[in] ep       - destination endpoint;
\param[in] attrId   - attr id;
\param[in] attrType - attr id;
\param[in] min      - the minimum reporting interval;
\param[in] max      - the maximum reporting interval
******************************************************************************/
void thermostatConfigureReporting(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep,
  ZCL_AttributeId_t attrId, uint8_t attrType, ZCL_ReportTime_t min, ZCL_ReportTime_t max);

/**************************************************************************//**
  \brief Sends Setpoint Raise/Lower command

  \param[in] mode - address mode;
  \param[in] addr - short address of destination node;
  \param[in] ep   - destination endpoint;
  \param mode - set points to be adjusted
  \param amount - amount of increase/decrease to setpoint value
        (in steps of 0.1°C.)
  \return none
******************************************************************************/
void ciSendSetpointRaiseLowerCommand(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep,
  int8_t setPointMode, int8_t amount);

#endif // _CITHERMOSTATCLUSTER_H

// eof ciThermostatCluster.h
