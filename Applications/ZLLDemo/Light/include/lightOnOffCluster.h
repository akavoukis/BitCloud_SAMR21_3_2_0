/**************************************************************************//**
  \file lightOnOffCluster.h

  \brief
    Light device On/Off cluster interface.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    28.06.11 A. Taradov - Created.
******************************************************************************/
#ifndef _LIGHTONOFFCLUSTER_H
#define _LIGHTONOFFCLUSTER_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zcl.h>
#include <zclZllOnOffCluster.h>

/******************************************************************************
                    Externals
******************************************************************************/
extern ZCL_OnOffClusterCommands_t onOffClusterCommands;
extern ZCL_OnOffClusterServerAttributes_t onOffClusterServerAttributes;

/******************************************************************************
                    Prototypes section
******************************************************************************/
void onOffClusterInit(void);
void onOffClusterSetExtensionField(bool onOff);
void onOffClusterSetGlobalSceneControl(void);
bool zllDeviceIsOn(void);

#endif // _LIGHTONOFFCLUSTER_H

// eof lightOnOffCluster.h
