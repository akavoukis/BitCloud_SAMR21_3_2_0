/**************************************************************************//**
  \file ciAlarmsCluster.h

  \brief
    Combined Interface Alarm cluster interface.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2013, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    21.10.14 Agasthian - Created.
******************************************************************************/
#ifndef _CIALARMSCLUSTER_H
#define _CIALARMSCLUSTER_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zclAlarmsCluster.h>
#include <haClusters.h>

/******************************************************************************
                    Externals
******************************************************************************/
extern ZCL_AlarmsClusterClientCommands_t   ciAlarmsCommands;

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
void alarmsReadAttribute(APS_AddrMode_t mode,ShortAddr_t addr, Endpoint_t ep,
  uint16_t attr, AttibuteReadCallback_t cb);

/**************************************************************************//**
\brief Sends Reset alarm command unicastly

\param[in] mode - address mode;
\param[in] addr - short address of destination node;
\param[in] ep   - destination endpoint;
\param[in] alarmCode - alarm code to be reset;
\param[in] clsuetrId   - cluster identifier;
******************************************************************************/
void alarmsSendResetAlarm(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep, ClusterId_t clusterId, uint8_t alarmCode);

/**************************************************************************//**
\brief Sends Reset all alarms command unicastly

\param[in] mode - address mode;
\param[in] addr - short address of destination node;
\param[in] ep   - destination endpoint;
******************************************************************************/
void alarmsSendResetAllAlarms(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep);

/**************************************************************************//**
\brief Sends Get Alarm command unicastly

\param[in] mode - address mode;
\param[in] addr - short address of destination node;
\param[in] ep   - destination endpoint;
******************************************************************************/
void alarmsSendGetAlarm(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep);

/**************************************************************************//**
\brief Sends Get Alarm command unicastly

\param[in] mode - address mode;
\param[in] addr - short address of destination node;
\param[in] ep   - destination endpoint;
******************************************************************************/
void alarmsSendResetAlarmLog(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep);

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
void alarmsWriteAttribute(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep,
  uint16_t attr, uint8_t type, AttributeWriteCallback_t cb, void *data, uint8_t size);

#endif // _CIALARMSCLUSTER_H

// eof ciAlarmsCluster.h
