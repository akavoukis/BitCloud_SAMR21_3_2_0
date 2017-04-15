/**************************************************************************//**
  \file lightLevelControlCluster.h

  \brief
    Light device Level Control cluster interface.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    28.06.11 A. Taradov - Created.
******************************************************************************/
#ifndef _LIGHTLEVELCONTROLCLUSTER_H
#define _LIGHTLEVELCONTROLCLUSTER_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zcl.h>
#include <zclZllLevelControlCluster.h>

/******************************************************************************
                    Defines section
******************************************************************************/
#define UPDATE_TIMER_INTERVAL 100 // 1/10th of a second as per specification
#define MIN_LIGHT_LEVEL       1
#define MAX_LIGHT_LEVEL       254
#define MIN_TRANSITION_TIME   1

/******************************************************************************
                    Externals
******************************************************************************/
extern ZCL_LevelControlClusterServerAttributes_t levelControlClusterServerAttributes;
extern ZCL_LevelControlClusterCommands_t levelControlClusterServerCommands;

/******************************************************************************
                    Prototypes
******************************************************************************/
void levelControlClusterInit(void);
void levelControlClusterSetExtensionField(uint16_t currentLevel);

/**************************************************************************//**
\brief Display current level value.
******************************************************************************/
void levelControlDisplayLevel(void);

#endif // _LIGHTLEVELCONTROLCLUSTER_H

// eof lightLevelControlCluster.h
