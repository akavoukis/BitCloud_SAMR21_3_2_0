/**************************************************************************//**
  \file ciIasZoneCluster.h

  \brief
    Combined Interface IASZone cluster implementation.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2013, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    18/11/2014 Yogesh - Created.
******************************************************************************/
#ifndef _CIIASZONECLUSTER_H
#define _CIIASZONECLUSTER_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zclIasZoneCluster.h>
#include <haClusters.h>
/******************************************************************************
                    Defines section
******************************************************************************/
#define DEFAULT_EXT_ADDR     0xFFFFFFFFFFFFFFFF
#define TEST_MODE_DURATION   0x05

/******************************************************************************
                    Externals
******************************************************************************/
extern ZCL_IasZoneClusterCommands_t ciIASZoneClusterServerCommands;
typedef ZCL_ZoneTable_t zoneTable_t;

/******************************************************************************
                    Prototypes section
******************************************************************************/

/**************************************************************************//**
\brief Initializes Thermostat cluster
******************************************************************************/
void iaszoneClusterInit(void);

/**************************************************************************//**
\brief Sends Read Attribute command unicastly

\param[in] mode - address mode;
\param[in] addr - short address of destination node;
\param[in] ep   - destination endpoint;
\param[in] attr - attribute id;
\param[in] cb   - callback function
******************************************************************************/
void iaszoneReadAttribute(APS_AddrMode_t mode,ShortAddr_t addr, Endpoint_t ep,
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
void iaszoneWriteAttribute(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep,
  uint16_t attr, uint8_t type, AttributeWriteCallback_t cb, void *data, uint8_t size);

/**************************************************************************//**
  \brief ZoneInitiateNormalOperatingModeCommand
  \param[in] mode   - address mode;
  \param[in] addr   - short address of destination node;
  \param[in] ep     - destination endpoint;
  \return none
******************************************************************************/
void ZoneInitiateNormalOperatingModeCommand(APS_AddrMode_t mode,ShortAddr_t addr, Endpoint_t ep);

/**************************************************************************//**
  \brief ZoneInitiateTestModeCommand
  \param[in] mode   - address mode;
  \param[in] addr   - short address of destination node;
  \param[in] ep     - destination endpoint;
  \param[in] testmode_duration     - test mode duration;
  \param[in] testmode_duration     - test mode duration;
  \return none
******************************************************************************/
void ZoneInitiateTestModeCommand(APS_AddrMode_t mode,ShortAddr_t addr, Endpoint_t ep, uint8_t testmodeDuration, uint8_t currentZoneSensitivityLevel);
#endif // _CIIASZONECLUSTER_H

// eof ciIasZoneCluster.h
