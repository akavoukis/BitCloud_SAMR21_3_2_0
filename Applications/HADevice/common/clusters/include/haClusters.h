/**************************************************************************//**
  \file clusters.h

  \brief
    Clusters interface.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2013, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    10.09.13 N. Fomin - Created.
******************************************************************************/
#ifndef _CLUSTER_H
#define _CLUSTER_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zcl.h>

/******************************************************************************
                    Types section
******************************************************************************/
typedef void (*AttibuteReadCallback_t)(void *data);
typedef void (*AttributeWriteCallback_t)(void);
typedef void (*ConfigureReportResp_t)(ZCL_Notify_t *ntfy);
/******************************************************************************
                    Prototypes section
******************************************************************************/
/**************************************************************************//**
\brief Fills ZCL Request structure

\param[out] req     - pointer to zcl command request;
\param[in]  command - command id;
\param[in] size     - the size of request payload
******************************************************************************/
void fillCommandRequest(ZCL_Request_t *req, uint8_t command, uint8_t size);

/**************************************************************************//**
\brief Fills zcl addressing structure

\param[out] addressing - pointer to the structure to be filled;
\param[in]  mode       - addressing mode;
\param[in]  addr       - short address of destination mode;
\param[in]  ep         - endpoint number of destination node;
\param[in]  cluster    - cluster id
******************************************************************************/
void fillDstAddressing(ZCL_Addressing_t *addressing, APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep, ClusterId_t cluster);

/**************************************************************************//**
\brief Fills zcl addressing structure

\param[out] addressing - pointer to the structure to be filled;
\param[in]  mode       - addressing mode;
\param[in]  addr       - short address of destination mode;
\param[in]  ep         - endpoint number of destination node;
\param[in]  cluster    - cluster id
******************************************************************************/
void fillDstAddressingServer(ZCL_Addressing_t *addressing, APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep, ClusterId_t cluster);

/**************************************************************************//**
\brief Gets free command buffer

\returns pointer to a command buffer
******************************************************************************/
ZCL_Request_t *getFreeCommand(void);

/**************************************************************************//**
\brief Fills ZCL Addressing structure

\param[out] srcAddressing - pointer to zcl addressing request of source node;
\param[in]  dstAddressing - pointer to zcl addressing request of destination node;
\param[in]  side          - cluster side of recipient side
******************************************************************************/
void fillDstAddressingViaSourceAddressing(ZCL_Addressing_t *srcAddressing, ZCL_Addressing_t *dstAddressing, uint8_t side);

/**************************************************************************//**
\brief Sends configure reporting request to notify another device about reporting

\param[in] endpoint  - destination endpoint;
\param[in] clusterId - cluster id;
\param[in] attrId    - attribute id;
]param[in] period    - report period
******************************************************************************/
void sendConfigureReportingToNotify(Endpoint_t srcEndpoint, Endpoint_t dstEndpoint, ClusterId_t clusterId, ZCL_AttributeId_t attrId, ZCL_ReportTime_t period, ConfigureReportResp_t configureRespCb);

#endif // _CLUSTER_H

// eof clusters.h
