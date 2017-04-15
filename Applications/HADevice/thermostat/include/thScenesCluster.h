/**************************************************************************//**
  \file thScenesCluster.h

  \brief
    Thermostat Scenes cluster interface.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    21.11.14 Viswanadham Kotla - Created.
******************************************************************************/
#ifndef _THSCENESCLUSTER_H
#define _THSCENESCLUSTER_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zclScenesCluster.h>

/******************************************************************************
                    Externals
******************************************************************************/
extern ZCL_SceneClusterServerAttributes_t thScenesClusterServerAttributes;
extern ZCL_ScenesClusterCommands_t        thScenesCommands;

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

#endif // _THSCENESCLUSTER_H

// eof thScenesCluster.h

