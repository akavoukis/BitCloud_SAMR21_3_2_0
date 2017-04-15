/**************************************************************************//**
  \file iasACEDiagnosticsCluster.h

  \brief
    IAS ACE diagnostics cluster interface.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2013, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    18/11/2014 Yogesh- Created.
******************************************************************************/
#ifndef _IASACEDIAGNOSTICSCLUSTER_H
#define _IASACEDIAGNOSTICSCLUSTER_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zclDiagnosticsCluster.h>

/******************************************************************************
                    External variables section
******************************************************************************/
extern ZCL_DiagnosticsClusterServerAttributes_t iasACEDiagnosticsClusterServerAttributes;

/******************************************************************************
                    Prototypes section
******************************************************************************/
/**************************************************************************//**
\brief Initializes diagnositcs cluster
******************************************************************************/
void diagnosticsClusterInit(void);

#endif // _IASACEDIAGNOSTICSCLUSTER_H

// eof iasACEDiagnosticsCluster.h

