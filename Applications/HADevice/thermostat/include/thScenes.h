/**************************************************************************//**
  \file thScenes.h

  \brief
    Thermostat Scenes interface.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    21.11.14 Viswanadham kotla - Created.
******************************************************************************/
#ifndef _THSCENES_H
#define _THSCENES_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <sysTypes.h>

/******************************************************************************
                    Definition(s) section
******************************************************************************/
#define MAX_SCENES_AMOUNT 16u

/******************************************************************************
                    Types section
******************************************************************************/
typedef struct
{
  bool      busy;
  uint8_t   sceneId;
  uint16_t  groupId;
  uint16_t  transitionTime;
  /* Scenes Extensions for thermostat */
  int16_t   occupiedCoolingSetpoint;
  int16_t   occupiedHeatingSetpoint;
  uint8_t   systemMode;
} Scene_t;

/******************************************************************************
                    External variables section
******************************************************************************/
extern Scene_t scenePool[MAX_SCENES_AMOUNT];

/******************************************************************************
                    Prototypes section
******************************************************************************/
/**************************************************************************//**
\brief Initializes scene
******************************************************************************/
void initScenes(void);

/**************************************************************************//**
\brief Allocates scene

\returns the pointer to allocated scene if allocation is successful,
  NULL otherwise
******************************************************************************/
Scene_t *allocateScene(void);

/**************************************************************************//**
\brief Frees scene

\param[in] scene - the pointer to the scene to be freed
******************************************************************************/
void freeScene(Scene_t *scene);

/**************************************************************************//**
\brief Gets appropriate scene by group id and scene id

\param[in] group - group id
\param[in] scene - scene id

\returns the pointer to scene if it is found, NULL otherwise
******************************************************************************/
Scene_t *findSceneBySceneAndGroup(uint16_t group, uint8_t scene);

/**************************************************************************//**
\brief Removes all scenes associated with the given group

\param[in] group - group id

\return amount of removed groups
******************************************************************************/
uint8_t removeScenesByGroup(uint16_t group);

/**************************************************************************//**
\brief Gets next scene by group id

\param[in] scene - the pointer to current scene or NULL to get the first busy scene
\param[in] group - group id

\returns the pointer to scene if it is found, NULL otherwise
******************************************************************************/
Scene_t *getNextSceneByGroup(Scene_t *scene, uint16_t group);

#endif // _THSCENES_H

// eof thScenes.h