/**************************************************************************//**
  \file otauService.h

  \brief
    OTAU interface declaration.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    06.12.13 N. Fomin - Created.
******************************************************************************/
#ifndef _OTAUSERVICE_H
#define _OTAUSERVICE_H

/******************************************************************************
                    Defines section
******************************************************************************/
#include <zcl.h>

/******************************************************************************
                    Defines section
******************************************************************************/
#define SOFTWARE_VERSION CCPU_TO_LE32(0xAABBCCDD);

/******************************************************************************
                    Prototypes section
******************************************************************************/
/**************************************************************************//**
\brief Starts Over-the-air update server service.

\param[out] - pointer to otau cluster
******************************************************************************/
void startOtauServer(ZCL_Cluster_t *otauCluster);

/**************************************************************************//**
\brief Starts Over-the-air update client service.

\param[out] - pointer to otau cluster
******************************************************************************/
void startOtauClient(ZCL_Cluster_t *otauCluster);

#endif // _OTAUSERVICE_H
// eof otauService.h