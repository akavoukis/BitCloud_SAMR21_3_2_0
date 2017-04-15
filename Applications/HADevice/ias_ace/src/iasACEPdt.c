/******************************************************************************
  \file iasACEPdt.c

  \brief
    IAS ACE Persistent Data Table implementation.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    18/11/2014 Yogesh - Created.
******************************************************************************/
#ifdef APP_DEVICE_TYPE_IAS_ACE

/******************************************************************************
                    Includes section
******************************************************************************/
#include <pdsDataServer.h>
#include <iasACEZoneCluster.h>

/******************************************************************************
                    PDT definitions
******************************************************************************/
#ifdef _ENABLE_PERSISTENT_SERVER_
/* IAS ACE application data file descriptors.
   Shall be placed in the PDS_FF code segment. */
PDS_DECLARE_FILE(APP_IAS_ACE_ZONE_STATE_MEM_ID,   sizeof(iasACEZoneClusterServerAttributes.iaszoneState),  &iasACEZoneClusterServerAttributes.iaszoneState,  NO_FILE_MARKS);
PDS_DECLARE_FILE(APP_IAS_ACE_ZONE_TYPE_MEM_ID,    sizeof(iasACEZoneClusterServerAttributes.iaszoneType),   &iasACEZoneClusterServerAttributes.iaszoneType,   NO_FILE_MARKS);
PDS_DECLARE_FILE(APP_IAS_ACE_ZONE_STATUS_MEM_ID,  sizeof(iasACEZoneClusterServerAttributes.iaszoneStatus), &iasACEZoneClusterServerAttributes.iaszoneStatus, NO_FILE_MARKS);
PDS_DECLARE_FILE(APP_IAS_ACE_ZONE_CIE_ADDR_MEM_ID,sizeof(iasACEZoneClusterServerAttributes.iasCieAddress), &iasACEZoneClusterServerAttributes.iasCieAddress, NO_FILE_MARKS);
PDS_DECLARE_FILE(APP_IAS_ACE_ZONE_ID_MEM_ID,      sizeof(iasACEZoneClusterServerAttributes.iasZoneId),     &iasACEZoneClusterServerAttributes.iasZoneId,     NO_FILE_MARKS);
PDS_DECLARE_FILE(APP_IAS_ACE_ZONE_NO_SENSITIVITY_LEVELS_MEM_ID, sizeof(iasACEZoneClusterServerAttributes.iasZoneNumberOfZoneSensitivityLevelsSupported), &iasACEZoneClusterServerAttributes.iasZoneNumberOfZoneSensitivityLevelsSupported, NO_FILE_MARKS);
PDS_DECLARE_FILE(APP_IAS_ACE_ZONE_NO_CURR_SENSITIVITY_LEV_MEM_ID,sizeof(iasACEZoneClusterServerAttributes.iasZoneCurrentZoneSensitivityLevel), &iasACEZoneClusterServerAttributes.iasZoneCurrentZoneSensitivityLevel, NO_FILE_MARKS);
/* IAS ACE application data file identifiers list.
   Will be placed in flash. */
PROGMEM_DECLARE(PDS_MemId_t appiasACEMemoryIdsTable[]) =
{
  APP_IAS_ACE_ZONE_STATE_MEM_ID,
  APP_IAS_ACE_ZONE_TYPE_MEM_ID,
  APP_IAS_ACE_ZONE_STATUS_MEM_ID,
  APP_IAS_ACE_ZONE_CIE_ADDR_MEM_ID,
  APP_IAS_ACE_ZONE_ID_MEM_ID,
  APP_IAS_ACE_ZONE_NO_SENSITIVITY_LEVELS_MEM_ID,
  APP_IAS_ACE_ZONE_NO_CURR_SENSITIVITY_LEV_MEM_ID
};

#endif // _ENABLE_PERSISTENT_SERVER_
#endif // APP_DEVICE_TYPE_IAS_ACE

// eof thPdt.c
