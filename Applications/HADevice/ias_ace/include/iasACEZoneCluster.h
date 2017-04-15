/**************************************************************************//**
  \file iasACEZoneCluster.h

  \brief
    IAS-Zone Cluster interface.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:    
    18/11/14 Yogesh Bellan - Created.
******************************************************************************/
#ifndef _IASZONECLUSTER_H
#define _IASZONECLUSTER_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zcl.h>
#include <zclIasZoneCluster.h>

/******************************************************************************
                    Definition(s) section
******************************************************************************/
/* Some default values for attributes */
#define APP_IAS_ZONE_TYPE_ATTRIBUTE_VALUE               0x000D
#define APP_IAS_ZONE_CIE_ADDRESS_ATTRIBUTE_VALUE        0x0000
#define ZONE_NOTI_PERIOD                                20000u
#define EXTENDED_STATE_DEFAULT                          0x00
#define ADRESS_MODE                                     0x02
#define CIE_ADDR                                        0x0000
#define CIE_ENDPT                                       0x14
#define TIME_IN_SECONDS                                 1000u
#define DEFAULT_VAL                                     0x00
#define ZONE_MAXIMUM_LIMIT_VALUE                        CCPU_TO_LE16(0x02FF)

/******************************************************************************
                    Externals
******************************************************************************/
extern ZCL_IasZoneClusterAttributes_t iasACEZoneClusterServerAttributes;
extern ZCL_IasZoneClusterCommands_t iasACEZoneClusterServerCommands;

/******************************************************************************
                    Prototypes section
******************************************************************************/
/**************************************************************************//**
 \brief iasZoneClusterInit
 \param none
 \return none
******************************************************************************/
void iasZoneClusterInit(void);

/**************************************************************************//**
 \brief zoneStatusChangeNotification Command
 \param mode - Adress Mode
 \param addr - short addr
 \param ep  -  Endpoint of the device
 \param zoneStatus - zone status
 \param extendedStatus - extended status
 \return none
******************************************************************************/
void zoneStatusChangeNotificationCommand(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep,uint16_t zoneStatus, uint8_t extendedStatus);

/**************************************************************************//**
 \brief zoneEnrollRequest Command
 \param mode - Adress Mode
 \param addr - short addr
 \param ep  -  Endpoint of the device
 \param zone_id -  index of the zone table
 \param manuf_code  -  manufacturer code
 \return none
******************************************************************************/
void zoneEnrollRequestCommand(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep, uint16_t zoneId, uint16_t manufCode);

/**************************************************************************//**
 \brief Initiating ZoneEnrollRequest Command
 \param shortAddress - short address
 \return none
******************************************************************************/
void sendZoneEnrollRequestCommand(uint16_t shortAddress);

/***************************************************************************//**
 \brief zoneChange change to send out the notification to CIE
 \param zoneStatusChangeValue - value of the status to trigger some actions
*******************************************************************************/
void zoneStatusChangeCommand(uint16_t zoneStatusChangeValue);
#endif // _IASZONECLUSTER_H

// eof iasACEZoneCluster.h
