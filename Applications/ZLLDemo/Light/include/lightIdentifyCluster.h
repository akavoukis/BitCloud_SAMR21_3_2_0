/**************************************************************************//**
  \file lightIdentifyCluster.h

  \brief
    Light device Identify cluster interface.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    28.06.11 A. Taradov - Created.
******************************************************************************/
#ifndef _LIGHTIDENTIFYCLUSTER_H
#define _LIGHTIDENTIFYCLUSTER_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zcl.h>
#include <zclZllIdentifyCluster.h>

/******************************************************************************
                    Defines section
******************************************************************************/
#define IDENTIFY_NON_COLOR_EFFECT false
#define IDENTIFY_COLOR_EFFECT     true

/******************************************************************************
                    Externals
******************************************************************************/
extern ZCL_IdentifyClusterCommands_t identifyClusterServerCommands;
extern ZCL_IdentifyClusterAttributes_t identifyClusterServerAttributes;

/******************************************************************************
                    Prototypes section
******************************************************************************/
void identifyClusterInit(void);
bool identifyClusterIsIdentifying(void);
void identifyStart(uint16_t identifyTime, bool colorEffect, uint16_t enhancedHue);
void identifyFinish(void);
void identifyStop(void);

#endif // _LIGHTIDENTIFYCLUSTER_H

// eof lightIdentifyCluster.h
