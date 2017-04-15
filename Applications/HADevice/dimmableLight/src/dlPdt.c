/******************************************************************************
  \file dlPdt.c

  \brief
    Dimmable Light Persistent Data Table implementation.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2010 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    19.12.12 N. Fomin - Created.
******************************************************************************/
#ifdef APP_DEVICE_TYPE_DIMMABLE_LIGHT

/******************************************************************************
                    Includes section
******************************************************************************/
#include <pdsDataServer.h>
#include <dlScenes.h>
#include <dlOnOffCluster.h>
#include <dlLevelControlCluster.h>

/******************************************************************************
                    PDT definitions
******************************************************************************/
#ifdef _ENABLE_PERSISTENT_SERVER_
/* Dimmable Light application data file descriptors.
   Shall be placed in the PDS_FF code segment. */
PDS_DECLARE_FILE(APP_DL_SCENES_MEM_ID,        MAX_SCENES_AMOUNT * sizeof(Scene_t),                        scenePool,                                           NO_FILE_MARKS);
PDS_DECLARE_FILE(APP_DL_ONOFF_MEM_ID,         sizeof(dlOnOffClusterServerAttributes.onOff),               &dlOnOffClusterServerAttributes.onOff,               NO_FILE_MARKS);
PDS_DECLARE_FILE(APP_DL_LEVEL_CONTROL_MEM_ID, sizeof(dlLevelControlClusterServerAttributes.currentLevel), &dlLevelControlClusterServerAttributes.currentLevel, NO_FILE_MARKS);

/* Dimmable Light application data file identifiers list.
   Will be placed in flash. */
PROGMEM_DECLARE(PDS_MemId_t appDlMemoryIdsTable[]) =
{
  APP_DL_SCENES_MEM_ID,
  APP_DL_ONOFF_MEM_ID,
  APP_DL_LEVEL_CONTROL_MEM_ID
};

/* Dimmable Light application directory descriptor.
   Shall be placed in the PDS_FD code segment. */
PDS_DECLARE_DIR(PDS_DirDescr_t appEsiMemoryDirDescr) =
{
  .list       = appDlMemoryIdsTable,
  .filesCount = ARRAY_SIZE(appDlMemoryIdsTable),
  .memoryId   = HA_APP_MEMORY_MEM_ID
};

#endif // _ENABLE_PERSISTENT_SERVER_
#endif // APP_DEVICE_TYPE_DIMMABLE_LIGHT

// eof dlPdt.c
