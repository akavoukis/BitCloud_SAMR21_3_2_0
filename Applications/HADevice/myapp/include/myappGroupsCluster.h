/**************************************************************************//**
  \file dlGroupsCluster.h

  \brief
    Dimmable Light Groups cluster interface.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    11.12.12 N. Fomin - Created.
******************************************************************************/
#ifndef _MYAPPGROUPSCLUSTER_H
#define _MYAPPGROUPSCLUSTER_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zclGroupsCluster.h>

/******************************************************************************
                    Externals
******************************************************************************/
extern ZCL_GroupsClusterServerAttributes_t dlGroupsClusterServerAttributes;
extern ZCL_GroupsClusterCommands_t         dlGroupsCommands;

/******************************************************************************
                    Prototypes section
******************************************************************************/
/**************************************************************************//**
\brief Initializes Groups cluster
******************************************************************************/
void groupsClusterInit(void);

#endif // _DLGROUPSCLUSTER_H

// eof dlGroupsCluster.h

