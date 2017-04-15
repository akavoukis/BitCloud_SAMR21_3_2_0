/******************************************************************************
  \file colorSceneRemotePdt.c

  \brief
    Color scene remote Persistent Data Table implementation.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2010 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    13.01.12 A. Razinkov - Created.
******************************************************************************/

#if APP_ZLL_DEVICE_TYPE == APP_DEVICE_TYPE_COLOR_SCENE_REMOTE

/******************************************************************************
                    Includes section
******************************************************************************/
#include <pdsDataServer.h>
#include <zllDemo.h>
#include <sysUtils.h>
#include <colorSceneRemoteLinkInfoCluster.h>
//#include <zclZll.h>

/******************************************************************************
                    External variables section
******************************************************************************/
extern AppColorSceneRemoteAppData_t appData;
extern ZCL_LinkInfoClusterClientAttributes_t linkInfoClusterClientAttributes;

/******************************************************************************
                    PDT definitions
******************************************************************************/
/*******************************************
         Color Scene Remote application PD
********************************************/
#ifdef _ENABLE_PERSISTENT_SERVER_
/* Color Scene Remote application data file descriptors.
   Shall be placed in the PDS_FF code segment. */
PDS_DECLARE_FILE(APP_COLOR_SCENE_REMOTE_DATA_MEM_ID, sizeof(AppColorSceneRemoteAppData_t), &appData, NO_FILE_MARKS);
PDS_DECLARE_FILE(APP_COLOR_SCENE_REMOTE_LINK_INFO_CLUSTER_CLIENT_MEM_ID, sizeof(ZCL_LinkInfoClusterClientAttributes_t), &linkInfoClusterClientAttributes, NO_FILE_MARKS)

/* Color Scene Remote application data file identifiers list.
   Will be placed in flash. */
PROGMEM_DECLARE(PDS_MemId_t appZllMemoryIdsTable[]) =
{
  APP_COLOR_SCENE_REMOTE_DATA_MEM_ID,
  APP_COLOR_SCENE_REMOTE_LINK_INFO_CLUSTER_CLIENT_MEM_ID
};

/* Color Scene Remote application directory descriptor.
   Shall be placed in the PDS_FD code segment. */
PDS_DECLARE_DIR(PDS_DirDescr_t appZllMemoryDirDescr) =
{
  .list       = appZllMemoryIdsTable,
  .filesCount = ARRAY_SIZE(appZllMemoryIdsTable),
  .memoryId   = ZLL_APP_MEMORY_MEM_ID
};

#endif /* _ENABLE_PERSISTENT_SERVER_ */
#endif /* APP_ZLL_DEVICE_TYPE == APP_DEVICE_TYPE_COLOR_SCENE_REMOTE */
/* eof colorSceneRemotePdt.c */
