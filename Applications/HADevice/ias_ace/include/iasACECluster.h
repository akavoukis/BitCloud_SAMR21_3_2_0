/**************************************************************************//**
  \file iasACECluster.h

  \brief
    IAS-ACE Cluster interface.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:    
    18/11/14 Yogesh Bellan - Created.
******************************************************************************/
#ifndef _IASACECLUSTER_H
#define _IASACECLUSTER_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zcl.h>
#include <zclIasACECluster.h>

/******************************************************************************
                    Definition(s) section
******************************************************************************/
/* Zone Table Size for ACE device*/
#define APP_ZONE_TABLE_ENTRY_SIZE                           0x03
#define PAYLOAD_SIZE                                        0x32

/* Some default values for attributes */
#define APP_IAS_ZONE_ZONE_TYPE_ATTRIBUTE_VALUE              0x0000
#define APP_IAS_ZONE_IAS_CIE_ADDRESS_ATTRIBUTE_VALUE        0x0000
#define SUPERVISION_REPORT_STATE                            0x0010

#define IAS_ACE_SERVER_CLUSTERS_COUNT           4
#ifdef OTAU_CLIENT
  #define IAS_ACE_CLIENT_CLUSTERS_COUNT         3
  #define IAS_ACE_CLIENT_CLUSTER_INIT_COUNT     2
#else
  #define IAS_ACE_CLIENT_CLUSTERS_COUNT         2
  #define IAS_ACE_CLIENT_CLUSTER_INIT_COUNT     0
#endif
#define IAS_ACE_SERVER_CLUSTER_INIT_COUNT IAS_ACE_SERVER_CLUSTERS_COUNT

/******************************************************************************
                    Externals
******************************************************************************/
extern ZCL_Cluster_t iasACEServerClusters[IAS_ACE_SERVER_CLUSTERS_COUNT];
extern ClusterId_t iasACEServerClusterIds[IAS_ACE_SERVER_CLUSTERS_COUNT];
extern void (*iasACEServerClusterInitFunctions[IAS_ACE_SERVER_CLUSTER_INIT_COUNT])();

extern ZCL_Cluster_t iasACEClientClusters[IAS_ACE_CLIENT_CLUSTERS_COUNT];
extern ClusterId_t iasACEClientClusterIds[IAS_ACE_CLIENT_CLUSTERS_COUNT];

#ifdef OTAU_CLIENT
extern void (*iasACEClientClusterInitFunctions[IAS_ACE_CLIENT_CLUSTER_INIT_COUNT])();
#endif

/******************************************************************************
                    Prototypes section
******************************************************************************/
/**************************************************************************//**
\brief Initializes IAS ACE cluster
******************************************************************************/
void iasACEClusterInit(void);

/**************************************************************************//**
 \brief ACEArmCommand Command
 \param mode - Adress Mode
 \param ep  -  Endpoint of the device
 \param arm -  ARM mode
 \return none
******************************************************************************/
void aceArmCommand(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep , uint8_t arm_mode , char *code , uint8_t zoneid);

/**************************************************************************//**
 \brief GetByPassZoneList Command
 \param mode - Adress Mode
 \param addr - short addr
 \param ep  -  Endpoint of the device
 \return none
******************************************************************************/
void getByPassZoneListCommand(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep);

/**************************************************************************//**
 \brief aceByPass Command
 \param mode - Adress Mode
 \param addr - short addr
 \param ep  -  Endpoint of the device
 \param zone_numbers -  total zones
 \param zoneId(s) -  index of the zone table
 \return none
******************************************************************************/
void aceByPassCommand(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep, uint8_t zoneNumbers, uint8_t zoneId1 , uint8_t zoneId2, uint8_t zoneId3, char *armDisarmCode);

/**************************************************************************//**
 \brief aceEmergency Command
 \param mode - Adress Mode
 \param addr - short addr
 \param ep  -  Endpoint of the device
 \return none
******************************************************************************/
void aceEmergencyCommand(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep);

/**************************************************************************//**
 \brief aceFire Command
 \param mode - Adress Mode
 \param addr - short addr
 \param ep  -  Endpoint of the device
 \return none
******************************************************************************/
void aceFireCommand(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep);

/**************************************************************************//**
 \brief acePanic Command
 \param mode - Adress Mode
 \param addr - short addr
 \param ep  -  Endpoint of the device
 \return none
******************************************************************************/
void acePanicCommand(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep);

/**************************************************************************//**
 \brief aceGetZoneInformation Command
 \param mode - Adress Mode
 \param addr - short addr
 \param ep  -  Endpoint of the device
 \param zoneId - zoneId offset
 \return none
******************************************************************************/
void aceGetZoneInformationCommand(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep, uint8_t zoneId);

/**************************************************************************//**
 \brief aceGetZoneIdMap Command
 \param mode - Adress Mode
 \param addr - short addr
 \param ep  -  Endpoint of the device
 \return none
******************************************************************************/
void aceGetZoneIdMapCommand(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep);

/**************************************************************************//**
 \brief aceGetPanelStatus Command
 \param mode - Adress Mode
 \param addr - short addr
 \param ep  -  Endpoint of the device
 \return none
******************************************************************************/
void aceGetPanelStatusCommand(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep);

/**************************************************************************//**
 \brief aceGetZoneStatus Command
 \param mode - Adress Mode
 \param addr - short addr
 \param ep  -  Endpoint of the device
 \param startingZoneId - starting of the zoneId offset
 \param maxNumberZoneids - maximum zoneIdss
 \param zoneStatusMaskFlag - mask flag
 \param zoneStatusMask - status of the zone
 \return none
******************************************************************************/
void aceGetZoneStatusCommand(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep, uint8_t startingZoneId, uint8_t maxNumberZoneids, uint8_t zoneStatusMaskFlag, uint16_t zoneStatusMask);
#endif // _IASACECLUSTER_H

// eof iasACECluster.h
