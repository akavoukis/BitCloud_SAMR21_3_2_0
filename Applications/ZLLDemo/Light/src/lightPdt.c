/******************************************************************************
  \file lLightPdt.c

  \brief
    Light device Persistent Data Table implementation.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2010 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    23.01.12 A. Razinkov - Created.
******************************************************************************/

#if APP_ZLL_DEVICE_TYPE >= APP_DEVICE_TYPE_ON_OFF_LIGHT

/******************************************************************************
                    Includes section
******************************************************************************/
#include <pdsDataServer.h>
#include <zllDemo.h>
#include <sysUtils.h>
#include <zclZllScenesCluster.h>
#include <zclZllColorControlCluster.h>
#include <zclZllLevelControlCluster.h>
#include <zclZllOnOffCluster.h>

/******************************************************************************
                    External variables section
******************************************************************************/
extern Scene_t scene[MAX_NUMBER_OF_SCENES];
extern ZCL_SceneClusterServerAttributes_t scenesClusterServerAttributes;
extern ZCL_ColorControlClusterServerAttributes_t colorControlClusterServerAttributes;
extern ZCL_LevelControlClusterServerAttributes_t levelControlClusterServerAttributes;
extern ZCL_OnOffClusterServerAttributes_t onOffClusterServerAttributes;

/******************************************************************************
                    PDT definitions
******************************************************************************/
/*******************************************
         Light application PDT
********************************************/
#ifdef _ENABLE_PERSISTENT_SERVER_
/* Light application data file descriptors.
   Shall be placed in the PDS_FF code segment. */
PDS_DECLARE_FILE(APP_LIGHT_DATA_MEM_ID,                              sizeof(Scene_t)*MAX_NUMBER_OF_SCENES,              &scene,                               NO_FILE_MARKS);
PDS_DECLARE_FILE(APP_LIGHT_SCENE_CLUSTER_SERVER_ATTR_MEM_ID,         sizeof(ZCL_SceneClusterServerAttributes_t),        &scenesClusterServerAttributes,       NO_FILE_MARKS);
PDS_DECLARE_FILE(APP_LIGHT_ONOFF_CLUSTER_SERVER_ATTR_MEM_ID,         sizeof(ZCL_OnOffClusterServerAttributes_t),        &onOffClusterServerAttributes,        NO_FILE_MARKS);
#if APP_ZLL_DEVICE_TYPE >= APP_DEVICE_TYPE_ON_OFF_LIGHT
PDS_DECLARE_FILE(APP_LIGHT_LEVEL_CONTROL_CLUSTER_SERVER_ATTR_MEM_ID, sizeof(ZCL_LevelControlClusterServerAttributes_t), &levelControlClusterServerAttributes, NO_FILE_MARKS);
#endif // APP_ZLL_DEVICE_TYPE >= APP_DEVICE_TYPE_ON_OFF_LIGHT
#if APP_ZLL_DEVICE_TYPE >= APP_DEVICE_TYPE_COLOR_LIGHT
PDS_DECLARE_FILE(APP_LIGHT_COLOR_CONTROL_CLUSTER_SERVER_ATTR_MEM_ID, sizeof(ZCL_ColorControlClusterServerAttributes_t), &colorControlClusterServerAttributes, NO_FILE_MARKS);
#endif // APP_ZLL_DEVICE_TYPE >= APP_DEVICE_TYPE_COLOR_LIGHT


/* Light application data file identifiers list.
   Will be placed in flash. */
PROGMEM_DECLARE(PDS_MemId_t appZllMemoryIdsTable[]) =
{
  APP_LIGHT_DATA_MEM_ID,
  APP_LIGHT_SCENE_CLUSTER_SERVER_ATTR_MEM_ID,
  APP_LIGHT_ONOFF_CLUSTER_SERVER_ATTR_MEM_ID,
#if APP_ZLL_DEVICE_TYPE >= APP_DEVICE_TYPE_ON_OFF_LIGHT
  APP_LIGHT_LEVEL_CONTROL_CLUSTER_SERVER_ATTR_MEM_ID,
#endif // APP_ZLL_DEVICE_TYPE >= APP_DEVICE_TYPE_ON_OFF_LIGHT
#if APP_ZLL_DEVICE_TYPE >= APP_DEVICE_TYPE_COLOR_LIGHT
  APP_LIGHT_COLOR_CONTROL_CLUSTER_SERVER_ATTR_MEM_ID,
#endif // APP_ZLL_DEVICE_TYPE >= APP_DEVICE_TYPE_COLOR_LIGHT
};

/* Light application directory descriptor.
   Shall be placed in the PDS_FD code segment. */
PDS_DECLARE_DIR(PDS_DirDescr_t appZllMemoryDirDescr) =
{
  .list       = appZllMemoryIdsTable,
  .filesCount = ARRAY_SIZE(appZllMemoryIdsTable),
  .memoryId   = ZLL_APP_MEMORY_MEM_ID
};

#endif /* _ENABLE_PERSISTENT_SERVER_ */
#endif /* APP_ZLL_DEVICE_TYPE >= APP_DEVICE_TYPE_ON_OFF_LIGHT */
/* eof lightPdt.c */
