/**************************************************************************//**
  \file dlScenesCluster.h

  \brief
    Dimmable Light Scenes cluster interface.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    11.12.12 N. Fomin - Created.
******************************************************************************/
#ifndef _DLSCENESCLUSTER_H
#define _DLSCENESCLUSTER_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zclScenesCluster.h>

/******************************************************************************
                    Externals
******************************************************************************/
extern ZCL_SceneClusterServerAttributes_t dlScenesClusterServerAttributes;
extern ZCL_ScenesClusterCommands_t        dlScenesCommands;

/******************************************************************************
                    Prototypes section
******************************************************************************/
/**************************************************************************//**
\brief Initializes Scenes cluster
******************************************************************************/
void scenesClusterInit(void);

/**************************************************************************//**
\brief Invalidates scene
******************************************************************************/
void scenesInvalidate(void);

#endif // _DLSCENESCLUSTER_H

// eof dlScenesCluster.h

