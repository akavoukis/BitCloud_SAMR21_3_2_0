/**************************************************************************//**
  \file dlLevelControlCluster.h

  \brief
    Dimmable Light Level Control cluster interface.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    11.12.12 N. Fomin - Created.
******************************************************************************/
#ifndef _MYAPPLEVELCONTROLCLUSTER_H
#define _MYAPPLEVELCONTROLCLUSTER_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zclLevelControlCluster.h>

/******************************************************************************
                    Definition(s) section
******************************************************************************/
#define LEVEL_CONTROL_VAL_MIN_REPORT_PERIOD 10
#define LEVEL_CONTROL_VAL_MAX_REPORT_PERIOD 20

/******************************************************************************
                    Externals
******************************************************************************/
extern ZCL_LevelControlClusterServerAttributes_t dlLevelControlClusterServerAttributes;
extern ZCL_LevelControlClusterCommands_t         dlLevelControlCommands;

/******************************************************************************
                    Prototypes section
******************************************************************************/
/**************************************************************************//**
\brief Initializes Level Control cluster
******************************************************************************/
void levelControlClusterInit(void);

/**************************************************************************//**
\brief Stops Level Control cluster
******************************************************************************/
void levelControlClusterStop(void);

/**************************************************************************//**
\brief Gets current color level

\returns current coloe level
******************************************************************************/
uint8_t levelControlCurrentLevel(void);

/**************************************************************************//**
\brief Sets color level

\param[in] level - color level
******************************************************************************/
void levelControlSetLevel(uint8_t level);

#endif // _DLLEVELCONTROLCLUSTER_H

// eof dlLevelControlCluster.h

