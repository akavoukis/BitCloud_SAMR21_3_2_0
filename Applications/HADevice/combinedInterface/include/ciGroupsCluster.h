/**************************************************************************//**
  \file ciGroupsCluster.h

  \brief
    Combined Interface Groups cluster interface.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2013, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    03.09.13 N. Fomin - Created.
******************************************************************************/
#ifndef _CIGROUPSCLUSTER_H
#define _CIGROUPSCLUSTER_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zclGroupsCluster.h>

/******************************************************************************
                    Externals
******************************************************************************/
extern ZCL_GroupsClusterCommands_t ciGroupsCommands;

/******************************************************************************
                    Prototypes section
******************************************************************************/
/**************************************************************************//**
\brief Initializes Groups cluster
******************************************************************************/
void groupsClusterInit(void);

/**************************************************************************//**
\brief Sends Add Group command to bound devices

\param[in] mode  - address mode;
\param[in] addr  - short address of destination node or number of group;
\param[in] ep    - endpoint number of destination device;
\param[in] group - group id
******************************************************************************/
void groupsSendAddGroup(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep,
  uint16_t group);

/**************************************************************************//**
\brief Sends View Group command to bound devices

\param[in] mode  - address mode;
\param[in] addr  - short address of destination node or number of group;
\param[in] ep    - endpoint number of destination device;
\param[in] group - group id
******************************************************************************/
void groupsSendViewGroup(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep,
  uint16_t group);

/**************************************************************************//**
\brief Sends Get Group Membership command to bound devices

\param[in] mode  - address mode;
\param[in] addr  - short address of destination node or number of group;
\param[in] ep    - endpoint number of destination device;
\param[in] count - group count;
\param[in] list  - group list;
******************************************************************************/
void groupsSendGetGroupMembership(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep,
  uint8_t count, uint16_t *list);

/**************************************************************************//**
\brief Sends Remove Group command to bound devices

\param[in] mode  - address mode;
\param[in] addr  - short address of destination node or number of group;
\param[in] ep    - endpoint number of destination device;
\param[in] group - group id
******************************************************************************/
void groupsSendRemoveGroup(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep,
  uint16_t group);

/**************************************************************************//**
\brief Sends Remove All Groups command to bound devices

\param[in] mode  - address mode;
\param[in] addr  - short address of destination node or number of group;
\param[in] ep    - endpoint number of destination device;
\param[in] group - group id
******************************************************************************/
void groupsSendRemoveAllGroups(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep);

/**************************************************************************//**
\brief Sends Add Group If Identifying command to bound devices

\param[in] mode  - address mode;
\param[in] addr  - short address of destination node or number of group;
\param[in] ep    - endpoint number of destination device;
\param[in] group - group id
******************************************************************************/
void groupsSendAddGroupIfIdentifying(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep,
  uint16_t group);

#endif // _CIGROUPSCLUSTER_H

// eof ciGroupsCluster.h

