/**************************************************************************//**
  \file lightScenesCluster.h

  \brief
    Light device Scenes cluster interface.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    28.06.11 A. Taradov - Created.
******************************************************************************/
#ifndef _LIGHTSCENESCLUSTER_H
#define _LIGHTSCENESCLUSTER_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zcl.h>
#include <zclZllScenesCluster.h>

/******************************************************************************
                    Externals
******************************************************************************/
extern ZCL_ScenesClusterCommands_t scenesClusterCommands;
extern ZCL_SceneClusterServerAttributes_t scenesClusterServerAttributes;

/******************************************************************************
                    Prototypes section
******************************************************************************/
void scenesClusterInit(void);
void scenesClusterRemoveByGroup(uint16_t group);
void scenesClusterInvalidate(void);
void scenesClusterStoreGlobalScene(void);
void scenesClusterRecallGlobalScene(void);

#endif // _LIGHTSCENESCLUSTER_H

// eof lightScenesCluster.h
