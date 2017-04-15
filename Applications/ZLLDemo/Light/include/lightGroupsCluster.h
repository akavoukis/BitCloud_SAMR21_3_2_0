/**************************************************************************//**
  \file lightGroupsCluster.h

  \brief
    Light device Groups cluster interface.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    28.06.11 A. Taradov - Created.
******************************************************************************/
#ifndef _LIGHTGROUPSCLUSTER_H
#define _LIGHTGROUPSCLUSTER_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zcl.h>
#include <zclZllGroupsCluster.h>

/******************************************************************************
                    Externals
******************************************************************************/
extern ZCL_GroupsClusterCommands_t groupsClusterServerCommands;
extern ZCL_GroupsClusterServerAttributes_t groupsClusterServerAttributes;

/******************************************************************************
                    Prototypes
******************************************************************************/
void groupsClusterInit(void);

#endif // _LIGHTGROUPSCLUSTER_H

// eof lightGroupsCluster.h
