/**************************************************************************//**
  \file iasACECluster.c

  \brief
    IAS-ACE Cluster implementation.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    18/11/14 Yogesh Bellan - Created.
******************************************************************************/
#if defined APP_DEVICE_TYPE_IAS_ACE

/******************************************************************************
                    Includes section
******************************************************************************/
#include <iasACECluster.h>
#if APP_ENABLE_CONSOLE == 1
#include <uartManager.h>
#endif
#include <iasACEZoneCluster.h>
#include <identifyCluster.h>
#include <basicCluster.h>
#include <iasACEBasicCluster.h>
#include <iasACEIdentifyCluster.h>
#include <iasACEDiagnosticsCluster.h>
#include <iasACEBasicCluster.h>
#include <zclIasZoneCluster.h>
#include <zclIasACECluster.h>
#include <zclBasicCluster.h>
#include <zclIdentifyCluster.h>
#include <haClusters.h>
#include <commandManager.h>

/******************************************************************************
                    Prototypes section
******************************************************************************/
static void iasACEFillGetZoneInfoCommand(ZCL_GetZoneInformationCommand_t *payload , uint8_t zone_id);
static ZCL_Status_t aceArmResponseCommandInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ACEResponseArm_t *payload);
static ZCL_Status_t aceGetZoneIdMapResponseCommandInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_GetZoneIdMapResponse_t *payload);
static ZCL_Status_t aceGetZoneInformationResponseCommandInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_GetZoneInformationResp_t *payload);
static ZCL_Status_t acePanelStatusChangedCommandInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ACEPanelStatusChangedCommand_t *payload);
static ZCL_Status_t aceZoneStatusChangedCommandInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ACEZoneStatusChangedCommand_t *payload);
static ZCL_Status_t aceGetZoneStatusRespCommandInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload);
static ZCL_Status_t aceGetPanelStatusCommandRespInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ACEGetPanelStatusCommandResp_t *payload);
static ZCL_Status_t aceSetByPassesZoneListCommandInd(ZCL_Addressing_t *addressing, uint8_t payloadLength,uint8_t * payload);
static ZCL_Status_t aceByPassResponseCommandInd(ZCL_Addressing_t *addressing, uint8_t payloadLength,uint8_t * payload);

/******************************************************************************
                    Global variables
******************************************************************************/
//IAS ACE Cluster Commands
ZCL_IasACEClusterCommands_t iasACEClusterCommands =
{
  ZCL_DEFINE_IAS_ACE_CLUSTER_COMMANDS(NULL,\
                    aceArmResponseCommandInd,\
                    NULL,\
                    NULL,\
                    NULL,\
                    NULL,\
                    NULL,\
                    aceGetZoneIdMapResponseCommandInd,\
                    NULL,\
                    aceGetZoneInformationResponseCommandInd,\
                    NULL,\
                    aceGetPanelStatusCommandRespInd,\
                    NULL,\
                    aceGetZoneStatusRespCommandInd,\
                    acePanelStatusChangedCommandInd,\
                    aceZoneStatusChangedCommandInd,\
                    NULL,\
                    aceSetByPassesZoneListCommandInd,\
                    aceByPassResponseCommandInd
                    )\
};

//IAS ACE Server Clusters
ZCL_Cluster_t iasACEServerClusters[IAS_ACE_SERVER_CLUSTERS_COUNT] =
{
   ZCL_DEFINE_BASIC_CLUSTER_SERVER(&iasACEBasicClusterServerAttributes,&iasACEBasicClusterServerCommands),
   DEFINE_IDENTIFY_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &iasACEIdentifyClusterServerAttributes, &iasACEIdentifyCommands),
   DEFINE_IAS_ZONE_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &iasACEZoneClusterServerAttributes, &iasACEZoneClusterServerCommands),
   DEFINE_DIAGNOSTICS_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &iasACEDiagnosticsClusterServerAttributes, NULL),
};

//IAS ACE Server Cluster Init Functions
void (*iasACEServerClusterInitFunctions[IAS_ACE_SERVER_CLUSTER_INIT_COUNT])() =
{
  basicClusterInit,
  identifyClusterInit,
  iasZoneClusterInit,
  diagnosticsClusterInit
};

//IAS ACE Server Cluster lists
ClusterId_t iasACEServerClusterIds[IAS_ACE_SERVER_CLUSTERS_COUNT] =
{
  BASIC_CLUSTER_ID,
  IDENTIFY_CLUSTER_ID,
  IAS_ZONE_CLUSTER_ID,
#ifdef OTAU_CLIENT
  OTAU_CLUSTER_ID,
#endif    
};

//IAS ACE Client Cluster lists
ZCL_Cluster_t iasACEClientClusters[IAS_ACE_CLIENT_CLUSTERS_COUNT] =
{
   DEFINE_IDENTIFY_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &iasACEIdentifyClusterServerAttributes, &iasACEIdentifyCommands),
   DEFINE_IAS_ACE_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, NULL, &iasACEClusterCommands)
};

//IAS ACE Client Cluster IDs
ClusterId_t iasACEClientClusterIds[IAS_ACE_CLIENT_CLUSTERS_COUNT] =
{
  IDENTIFY_CLUSTER_ID,
  IAS_ACE_CLUSTER_ID,
#ifdef OTAU_CLIENT
  OTAU_CLUSTER_ID,
#endif    
};

#ifdef OTAU_CLIENT
void (*iasACEClientClusterInitFunctions[IAS_ACE_CLIENT_CLUSTER_INIT_COUNT])() =
{
  NULL // need to call otau client init function
};
#endif

/******************************************************************************
                    Implementation section
******************************************************************************/


/**************************************************************************//**
\brief Initializes iasACE Cluster
******************************************************************************/
void iasACEClusterInit(void)
{
  return;
}

/**************************************************************************//**
\brief iasACEFill Arm Payload
\param[in] payload  - payload of the Arm to fill
\param[in] arm_mode  - differnent arm modes
\param[in] code  - arm diasarm code
\param[in] zoneId  - zone Id information
\return none
******************************************************************************/
static void iasACEFillArmCommand(ZCL_ACEArm_t *payload , uint8_t armMode, char *code , uint8_t zoneId)
{
  payload->armMode       = armMode;
  payload->lengthArmMode = ZCL_IAS_ACE_ARM_DISARM_CODE_SIZE;
  memcpy(payload->armDisarmCode, code,ZCL_IAS_ACE_ARM_DISARM_CODE_SIZE);
  payload->zoneId        = zoneId;
}

/**************************************************************************//**
\brief iasFill GetZoneInfo Command
\param[in] payload  - payload of the GetZone Information
\param[in] zoneId  - index of the zone table
\return none
******************************************************************************/
static void iasACEFillGetZoneInfoCommand(ZCL_GetZoneInformationCommand_t *payload , uint8_t zoneId)
{
  payload->zoneId  = zoneId;
}

/**************************************************************************//**
\brief ACEArmCommand Command
\param mode - Adress Mode
\param addr - Adress detail 
\param ep  -  Endpoint of the device
\param[in] arm_mode  - differnent arm modes
\param[in] code  - arm diasarm code
\param[in] zoneId  - zone Id information
\return none
******************************************************************************/
void aceArmCommand(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep , uint8_t arm_mode , char *code , uint8_t zoneid)
{
  ZCL_Request_t *req;

  if (!(req = getFreeCommand()))
    return ;

  fillCommandRequest(req, ZCL_IAS_ACE_CLUSTER_ARM_COMMAND_ID, sizeof(ZCL_ACEArm_t));
  iasACEFillArmCommand((ZCL_ACEArm_t *)req->requestPayload , arm_mode, code, zoneid);
  fillDstAddressing(&req->dstAddressing, mode, addr, ep, IAS_ACE_CLUSTER_ID);
  commandManagerSendCommand(req);
#if APP_ENABLE_CONSOLE == 1
  LOG_STRING(aceCmdStr, " ->ACEArmCommand Sent\r\n");
  appSnprintf(aceCmdStr);
#endif  
}

/**************************************************************************//**
\brief ACEArm Response Command
\param addressing - Arm Command Response 
\param payloadLength  -  Payload lengeth
\param payload -  Arm payload
\return ZCL_Status_t
******************************************************************************/
static ZCL_Status_t aceArmResponseCommandInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ACEResponseArm_t *payload)
{
  (void)addressing;
  (void)payloadLength;
  (void)payload;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief aceByPass Command
\param mode - Adress Mode
\param addr - short addr
\param ep  -  Endpoint of the device
\param zone_numbers -  total zones
\param zoneId(s) -  index of the zone table
\return none
******************************************************************************/
void aceByPassCommand(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep, uint8_t zone_numbers, 
                      uint8_t zone_id1 , uint8_t zone_id2, uint8_t zone_id3, char *arm_disarm_code)
{
  ZCL_Request_t *req;
  uint8_t payload[PAYLOAD_SIZE];
  uint8_t payload_length =0;

  if (!(req = getFreeCommand()))
    return ;
 
  payload[payload_length++] = zone_numbers;
  switch(zone_numbers)
  {
    case 3:
      payload[payload_length++] = zone_id1;
      payload[payload_length++] = zone_id2;
      payload[payload_length++] = zone_id3;
      break;
    case 2:
      payload[payload_length++] = zone_id1;
      payload[payload_length++] = zone_id2;
      (void) zone_id3;
      break;
    case 1:
      payload[payload_length++] = zone_id1;
      (void) zone_id2;
      (void) zone_id3;
      break;
    default:
       break;
   }
   payload[payload_length++] = ZCL_IAS_ACE_ARM_DISARM_CODE_SIZE;     
   memcpy(&payload[payload_length], arm_disarm_code,ZCL_IAS_ACE_ARM_DISARM_CODE_SIZE);
   payload_length += ZCL_IAS_ACE_ARM_DISARM_CODE_SIZE;
   
   //Allocating Buffer Space for the Command
   fillCommandRequest(req, ZCL_IAS_ACE_CLUSTER_BYPASS_COMMAND_ID, payload_length);
   
   //Payload Copy into the request Payload.
   memcpy(req->requestPayload, &payload[0],payload_length);

   //Filling Destination Address.
   fillDstAddressing(&req->dstAddressing, mode, addr, ep, IAS_ACE_CLUSTER_ID);
   commandManagerSendCommand(req);   
#if APP_ENABLE_CONSOLE == 1
  LOG_STRING(aceCmdStr, " ->ACEByPassCommand Sent\r\n");
  appSnprintf(aceCmdStr);
#endif   
}

/**************************************************************************//**
\brief ACEEmergency Command
\param mode - Adress Mode
\param addr - short addr
\param ep  -  Endpoint of the device
\return none
******************************************************************************/
void aceEmergencyCommand(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep)
{
  ZCL_Request_t *req;

  if (!(req = getFreeCommand()))
    return ;

  fillCommandRequest(req, ZCL_IAS_ACE_CLUSTER_EMERGENCY_COMMAND_ID, 0x00);
  fillDstAddressing(&req->dstAddressing, mode, addr, ep, IAS_ACE_CLUSTER_ID);
  commandManagerSendCommand(req);
#if APP_ENABLE_CONSOLE == 1
  LOG_STRING(aceCmdStr, " ->ACEEmergencyCommand Sent\r\n");
  appSnprintf(aceCmdStr);
#endif    
}

/**************************************************************************//**
\brief ACEFire Command
\param mode - Adress Mode
\param addr - short addr
\param ep  -  Endpoint of the device
\return none
******************************************************************************/
void aceFireCommand(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep)
{
  ZCL_Request_t *req;

  if (!(req = getFreeCommand()))
    return ;

  fillCommandRequest(req, ZCL_IAS_ACE_CLUSTER_FIRE_COMMAND_ID, 0x00);
  fillDstAddressing(&req->dstAddressing, mode, addr, ep, IAS_ACE_CLUSTER_ID);
  commandManagerSendCommand(req);
#if APP_ENABLE_CONSOLE == 1
  LOG_STRING(aceCmdStr, " ->ACEFireCommand Sent\r\n");
  appSnprintf(aceCmdStr);
#endif  
}

/**************************************************************************//**
\brief ACEPanic Command
\param mode - Adress Mode
\param addr - short addr
\param ep  -  Endpoint of the device
\return none
******************************************************************************/
void acePanicCommand(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep)
{
  ZCL_Request_t *req;

  if (!(req = getFreeCommand()))
    return ;

  fillCommandRequest(req, ZCL_IAS_ACE_CLUSTER_PANIC_COMMAND_ID, 0x00);
  fillDstAddressing(&req->dstAddressing, mode, addr, ep, IAS_ACE_CLUSTER_ID);
  commandManagerSendCommand(req); 
#if APP_ENABLE_CONSOLE == 1
  LOG_STRING(aceCmdStr, " ->ACEPanicCommand Sent\r\n");
  appSnprintf(aceCmdStr);
#endif   
}

/**************************************************************************//**
\brief ACEGetZoneIdMap Command
\param mode - Adress Mode
\param addr - short addr
\param ep  -  Endpoint of the device
\return none
******************************************************************************/
void aceGetZoneIdMapCommand(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep)
{
  ZCL_Request_t *req;

  if (!(req = getFreeCommand()))
    return ;

  fillCommandRequest(req, ZCL_IAS_ACE_CLUSTER_GET_ZONE_ID_MAP_COMMAND_ID, 0x00);
  fillDstAddressing(&req->dstAddressing, mode, addr, ep, IAS_ACE_CLUSTER_ID);
  commandManagerSendCommand(req);
#if APP_ENABLE_CONSOLE == 1
  LOG_STRING(aceCmdStr, " ->ACEGetZoneIdMapCommand Sent\r\n");
  appSnprintf(aceCmdStr);
#endif
}

/**************************************************************************//**
\brief ACEGetZoneIdMapResponse Command Indication
\param addressing - ACEGetZoneIdMapResponse Address details 
\param payloadLength  - Payload lengeth
\param payload -  ZOne MapId Response pointer
\return none
******************************************************************************/
static ZCL_Status_t aceGetZoneIdMapResponseCommandInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_GetZoneIdMapResponse_t *payload)
{
  (void)addressing;
  (void)payloadLength;
  (void)payload;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
 \brief aceGetZoneInformation Command
 \param mode - Adress Mode
 \param addr - short addr
 \param ep  -  Endpoint of the device
 \param zoneId  -  zone Id base
 \return none
******************************************************************************/
void aceGetZoneInformationCommand(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep, uint8_t zoneId)
{
  ZCL_Request_t *req;

  if (!(req = getFreeCommand()))
    return ;

  fillCommandRequest(req, ZCL_IAS_ACE_CLUSTER_GET_ZONE_INFORMATION_COMMAND_ID, sizeof(ZCL_GetZoneInformationCommand_t));
  iasACEFillGetZoneInfoCommand((ZCL_GetZoneInformationCommand_t *)req->requestPayload , zoneId);
  fillDstAddressing(&req->dstAddressing, mode, addr, ep, IAS_ACE_CLUSTER_ID);
  commandManagerSendCommand(req);
#if APP_ENABLE_CONSOLE == 1
  LOG_STRING(aceCmdStr, " ->ACEGetZoneInformationCommand Sent\r\n");
  appSnprintf(aceCmdStr);
#endif    
 
}

/**************************************************************************//**
 \brief ACEGetPanelStatus Command
 \param mode - Adress Mode
 \param addr - short addr
 \param ep  -  Endpoint of the device
 \return none
******************************************************************************/
void aceGetPanelStatusCommand(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep)
{
  ZCL_Request_t *req;
  
  if (!(req = getFreeCommand()))
    return ;
  fillCommandRequest(req, ZCL_IAS_ACE_CLUSTER_GET_PANEL_STATUS_COMMAND_ID, 0x00);
  fillDstAddressing(&req->dstAddressing, mode, addr, ep, IAS_ACE_CLUSTER_ID);
  commandManagerSendCommand(req); 
#if APP_ENABLE_CONSOLE == 1
  LOG_STRING(aceCmdStr, " ->ACEGetPanelStatusCommand Sent\r\n");
  appSnprintf(aceCmdStr);
#endif
}

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
void aceGetZoneStatusCommand(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep, uint8_t starting_zone_id, uint8_t max_number_zoneids, uint8_t zonestatus_maskflag, uint16_t zonestatus_mask)
{
  ZCL_Request_t *req;
  ZCL_ACEGetZoneStatusCommand_t *request;

  if (!(req = getFreeCommand()))
    return ;
  
  //Allocating memory and size
  fillCommandRequest(req, ZCL_IAS_ACE_CLUSTER_GET_ZONE_STATUS_COMMAND_ID, sizeof(ZCL_ACEGetZoneStatusCommand_t));
  request = (ZCL_ACEGetZoneStatusCommand_t *) req->requestPayload;
  
  //Filling up payload
  request->starting_zone_id = starting_zone_id;
  request->max_number_zoneids = max_number_zoneids;
  request->zonestatus_maskflag = zonestatus_maskflag;
  request->zonestatus_mask = zonestatus_mask;  
  
  //Destination Address Filling
  fillDstAddressing(&req->dstAddressing, mode, addr, ep, IAS_ACE_CLUSTER_ID);
  commandManagerSendCommand(req);
#if APP_ENABLE_CONSOLE == 1
  LOG_STRING(aceCmdStr, " ->ACEGetZoneStatusCommand Sent\r\n");
  appSnprintf(aceCmdStr);
#endif
}

/**************************************************************************//**
 \brief ACEGetZoneStatus Command
 \param addressing - ACEGetZoneIdMapResponse Address details 
 \param payloadLength  - Payload lengeth
 \param payload -  Panel Status Status Details
 \return none
******************************************************************************/
static ZCL_Status_t aceGetPanelStatusCommandRespInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ACEGetPanelStatusCommandResp_t *payload)
{
  (void)addressing;
  (void)payloadLength;
  (void)payload;
  return ZCL_SUCCESS_STATUS;  
}

/**************************************************************************//**
 \brief ACEGetZoneStatus Command
 \param addressing - ACEGetZoneIdMapResponse Address details 
 \param payloadLength  - Payload lengeth
 \param payload -  Panel Status Status Details
 \return none
******************************************************************************/
static ZCL_Status_t aceGetZoneStatusRespCommandInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload)
{
  (void)payload;
  (void)payloadLength;
  (void)addressing;  
  return ZCL_SUCCESS_STATUS;   
}

/**************************************************************************//**
 \brief ACE Panel Status Command
 \param addressing - ACEGetZoneIdMapResponse Address details 
 \param payloadLength  - Payload lengeth
 \param payload -  Panel Status Status Details
 \return none
******************************************************************************/
static ZCL_Status_t acePanelStatusChangedCommandInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ACEPanelStatusChangedCommand_t *payload)
{
  (void)addressing;
  (void)payloadLength;
  (void)payload; 
  return ZCL_SUCCESS_STATUS;  
}

/**************************************************************************//**
 \brief ACE Zone Status Command
 \param addressing - ACEGetZoneIdMapResponse Address details 
 \param payloadLength  - Payload lengeth
 \param payload -  Panel Status Status Details
 \return none
******************************************************************************/
static ZCL_Status_t aceZoneStatusChangedCommandInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ACEZoneStatusChangedCommand_t *payload)
{
  (void)addressing;
  (void)payloadLength;
  (void)payload; 
  return ZCL_SUCCESS_STATUS;
}
/**************************************************************************//**
 \brief ACEGetZoneInformationResponse Command Indication
 \param addressing - ACEGetZoneIdMapResponse Address details 
 \param payloadLength  - Payload lengeth
 \param payload -  Zone table details
 \return none
******************************************************************************/
static ZCL_Status_t aceGetZoneInformationResponseCommandInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_GetZoneInformationResp_t *payload)
{
  (void)addressing;
  (void)payloadLength;
  (void)payload;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
 \brief ACEGetZoneInformationResponse Command Indication
 \param mode - Adress Mode
 \param addr - short addr
 \param ep  -  Endpoint of the device
 \return none
******************************************************************************/
void getByPassZoneListCommand(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep)
{
  ZCL_Request_t *req;

  if (!(req = getFreeCommand()))
    return ;

  fillCommandRequest(req, ZCL_IAS_ACE_CLUSTER_GET_BYPASSED_ZONE_LIST_COMMAND_ID, 0);
  fillDstAddressing(&req->dstAddressing, mode, addr, ep, IAS_ACE_CLUSTER_ID);
  commandManagerSendCommand(req);
#if APP_ENABLE_CONSOLE == 1
  LOG_STRING(aceCmdStr, " ->GetByPassZoneListCommand Sent\r\n");
  appSnprintf(aceCmdStr);
#endif
}

/**************************************************************************//**
 \brief aceSetByPassesZoneList Command Indication
 \param addressing - Address details 
 \param payloadLength  - Payload lengeth
 \param payload -  Payload pointer
 \return none
******************************************************************************/
static ZCL_Status_t aceSetByPassesZoneListCommandInd(ZCL_Addressing_t *addressing, uint8_t payloadLength,uint8_t * payload)
{
  (void)addressing;
  (void)payloadLength;
  (void)payload;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
 \brief aceByPassResponse Command Indication
 \param addressing - Address details 
 \param payloadLength  - Payload lengeth
 \param payload -  Payload pointer
 \return none
******************************************************************************/
static ZCL_Status_t aceByPassResponseCommandInd(ZCL_Addressing_t *addressing, uint8_t payloadLength,uint8_t * payload)
{
  (void)addressing;
  (void)payloadLength;
  (void)payload;
  return ZCL_SUCCESS_STATUS;
}
#endif // APP_DEVICE_TYPE_IAS_ACE
//// eof iasACECluster.c
