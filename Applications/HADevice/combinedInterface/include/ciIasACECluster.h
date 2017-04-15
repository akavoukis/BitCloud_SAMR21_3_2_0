/**************************************************************************//**
  \file ciIasZoneCluster.h

  \brief
    Combined Interface IAS Zone cluster.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2013, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    18/11/2014 Yogesh - Created.
******************************************************************************/
#ifndef _CIIASACECLUSTER_H
#define _CIIASACECLUSTER_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zclIasACECluster.h>
#include <ciIasZoneCluster.h>
#include <haClusters.h>
/******************************************************************************
                    Defines section
******************************************************************************/
#define ZONE_TABLE_ENTRIES      APP_ZONE_TABLE_SIZE
#define DEFAULT_VAL             0x00
#define PANEL_DEFAULT_STATE     DEFAULT_VAL
#define TIME_REMAINING_DEFAULT  DEFAULT_VAL
#define NO_ALARM                DEFAULT_VAL
#define ACE_ENDPT               APP_ENDPOINT_IAS_ACE
#define DEFAULT_SOUND           0x01
#define ADRESS_MODE             0x02
#define PAYLOAD_SIZE            0x32
#define PANEL_STAUS_TIMER       1000u

/******************************************************************************
                    Externals
******************************************************************************/
extern ZCL_IasACEClusterCommands_t ciIASACEClusterCommands;
extern zoneTable_t zoneTables[ZONE_TABLE_ENTRIES];

/******************************************************************************
                    Type section
******************************************************************************/
BEGIN_PACK
typedef struct PACK
{
  uint8_t totalZones;
  bypassList_t bypassTable[ZONE_TABLE_ENTRIES];
}bypassTable_t;
END_PACK

/******************************************************************************
                    Prototypes section
******************************************************************************/
/**************************************************************************//**
\brief Initializes ias ACE cluster
******************************************************************************/
void iasACEClusterInit(void);

/**************************************************************************//**
\brief Sends Read Attribute command unicastly

\param[in] mode - address mode;
\param[in] addr - short address of destination node;
\param[in] ep   - destination endpoint;
\param[in] attr - attribute id;
\param[in] cb   - callback function
******************************************************************************/
void iasACEReadAttribute(APS_AddrMode_t mode,ShortAddr_t addr, Endpoint_t ep,
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
void iasACEWriteAttribute(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep,
                          uint16_t attr, uint8_t type, AttributeWriteCallback_t cb, void *data, uint8_t size);

/**************************************************************************//**
\brief Sends ACEPanelStatusChanged Command

\param[in] mode - address mode;
\param[in] addr - short address of destination node;
\param[in] panel_status - Panel status value;
\param[in] seconds_remaining  - seconds remaining for the panel status;
\param[in] audible_noti - audible notificaiton;
\param[in] alarmstatus   - alarm status;
******************************************************************************/
void acePanelStatusChangedCommand(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep,ZCL_PanelStatus_t panelStatus,
                                     uint8_t secondsRemaining, ZCL_AudibleNotification_t audibleNoti,ZCL_AlarmStatus_t alarmStatus);

/**************************************************************************//**
\brief Sends ACEZoneStatusChanged Command

\param[in] mode - address mode;
\param[in] addr - short address of destination node;
\param[in] zoneId - zone_id which changed the status;
\param[in] zoneStatus  - status of the zoneId which changed;
\param[in] audible_sound - audible sound;
\param[in] zone_label   - zone label;
******************************************************************************/
void aceZoneStatusChangedCommand(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep,
                                 uint8_t zoneId, uint8_t zoneStatus, uint8_t audibleSound, uint16_t zoneLabel);

#endif // _CIIASACECLUSTER_H

// eof ciIasZoneCluster.h
