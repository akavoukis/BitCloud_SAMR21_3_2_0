/**************************************************************************//**
  \file thGroupsCluster.h

  \brief
    Thermostat Groups server cluster interface.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    21.11.14 Viswanadham kotla - Created.
******************************************************************************/
#ifndef _THGROUPSCLUSTER_H
#define _THGROUPSCLUSTER_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zclGroupsCluster.h>

/******************************************************************************
                    Externals
******************************************************************************/
extern ZCL_GroupsClusterServerAttributes_t thGroupsClusterServerAttributes;
extern ZCL_GroupsClusterCommands_t         thGroupsCommands;

/******************************************************************************
                    Prototypes section
******************************************************************************/
/**************************************************************************//**
\brief Initializes Groups cluster
******************************************************************************/
void groupsClusterInit(void);

#endif // _THGROUPSCLUSTER_H

// eof thGroupsCluster.h

