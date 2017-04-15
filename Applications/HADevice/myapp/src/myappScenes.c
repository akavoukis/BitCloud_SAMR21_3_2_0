/**************************************************************************//**
  \file dlScenes.c

  \brief
    Dimmable Light Scenes implementation.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    11.12.12 N. Fomin - Created.
******************************************************************************/
#ifdef APP_DEVICE_TYPE_MYAPP

/******************************************************************************
                    Includes section
******************************************************************************/
#include <myappScenes.h>

/******************************************************************************
                    Global variables section
******************************************************************************/
Scene_t scenePool[MAX_SCENES_AMOUNT];

/******************************************************************************
                    Implementation section
******************************************************************************/
/**************************************************************************//**
\brief Initializes scene
******************************************************************************/
void initScenes(void)
{
  memset(scenePool, 0, sizeof(Scene_t) * MAX_SCENES_AMOUNT);
}

/**************************************************************************//**
\brief Allocates scene

\returns the pointer to allocated scene if allocation is successful,
  NULL otherwise
******************************************************************************/
Scene_t *allocateScene(void)
{
  uint8_t i = 0;

  for (i = 0; i < MAX_SCENES_AMOUNT; i++)
  {
    if (!scenePool[i].busy)
    {
      scenePool[i].busy = true;
      return &scenePool[i];
    }
  }

  return NULL;
}

/**************************************************************************//**
\brief Frees scene

\param[in] scene - the pointer to the scene to be freed
******************************************************************************/
void freeScene(Scene_t *scene)
{
  memset(scene, 0, sizeof(Scene_t));
}

/**************************************************************************//**
\brief Gets appropriate scene by group id and scene id

\param[in] group - group id
\param[in] scene - scene id

\returns the pointer to scene if it is found, NULL otherwise
******************************************************************************/
Scene_t *findSceneBySceneAndGroup(uint16_t group, uint8_t scene)
{
  for (uint8_t i = 0; i < MAX_SCENES_AMOUNT; i++)
  {
    if ((scenePool[i].groupId == group) && (scenePool[i].sceneId == scene))
      return &scenePool[i];
  }

  return NULL;
}

/**************************************************************************//**
\brief Removes all scenes associated with the given group

\param[in] group - group id

\return amount of removed scenes
******************************************************************************/
uint8_t removeScenesByGroup(uint16_t group)
{
  uint8_t amount = 0;

  for (uint8_t i = 0; i < MAX_SCENES_AMOUNT; i++)
  {
    if (scenePool[i].groupId == group)
    {
      freeScene(&scenePool[i]);
      amount++;
    }
  }

  return amount;
}

/**************************************************************************//**
\brief Gets next scene by group id

\param[in] scene - the pointer to current scene or NULL to get the first busy scene
\param[in] group - group id

\returns the pointer to scene if it is found, NULL otherwise
******************************************************************************/
Scene_t *getNextSceneByGroup(Scene_t *scene, uint16_t group)
{
  if (!scene)
  {
    for (uint8_t i = 0; i < MAX_SCENES_AMOUNT; i++)
    {
      if (scenePool[i].busy && (scenePool[i].groupId == group))
        return &scenePool[i];
    }
    return NULL;
  }

  if ((scene < scenePool) || (scene > &scenePool[MAX_SCENES_AMOUNT - 1]))
    return NULL;

  for (uint8_t i = 0; i < MAX_SCENES_AMOUNT; i++)
  {
    if ((scene < &scenePool[i]) && (scenePool[i].busy) && (scenePool[i].groupId == group))
      return &scenePool[i];
  }

  return NULL;
}

#endif // APP_DEVICE_TYPE_MYAPP
// eof dlScenes.c

