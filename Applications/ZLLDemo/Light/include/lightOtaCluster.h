/**************************************************************************//**
  \file lightOtaCluster.h

  \brief
    Light device Over-the-air update cluster interface.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    21.05.12 N. Fomin - Created.
    28.01.13 S. Dmitriev - Copied.
******************************************************************************/
#ifndef _LIGHTOTACLUSTER_H
#define _LIGHTOTACLUSTER_H

/******************************************************************************
                    Includes section
******************************************************************************/
#if APP_USE_OTAU == 1
  #include <zclOTAUCluster.h>
#endif

#endif // _LIGHTOTACLUSTER_H

// eof lightOtaCluster.h
