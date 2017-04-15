/**************************************************************************//**
  \file lightColorControlCluster.h

  \brief
    Light device Color Control cluster interface.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    28.06.11 A. Taradov - Created.
******************************************************************************/
#ifndef _LIGHTCOLORCONTROLCLUSTER_H
#define _LIGHTCOLORCONTROLCLUSTER_H

/******************************************************************************
                    Includes
******************************************************************************/
#include <zcl.h>
#include <zclZllColorControlCluster.h>
#include <zllDemo.h>

/******************************************************************************
                    Externals
******************************************************************************/
extern ZCL_ColorControlClusterServerAttributes_t colorControlClusterServerAttributes;
extern ZCL_ColorControlClusterCommands_t colorControlClusterServerCommands;

/******************************************************************************
                    Prototypes
******************************************************************************/
void colorControlClusterInit(void);
void colorControlClusterSetExtensionField(Scene_t *scene);

/**************************************************************************//**
\brief Show identify effect.

\param[in] enhancedHue - enhanced hue to move to.
******************************************************************************/
void colorControlShowIdentifyEffect(uint16_t enhancedHue);

/**************************************************************************//**
\brief Stop showing identify effect and return to previous state.
******************************************************************************/
void colorControlStopIdentifyEffect(void);

#endif // _LIGHTCOLORCONTROLCLUSTER_H

// eof lightColorControlCluster.h
