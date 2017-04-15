/**************************************************************************//**
  \file msDiagnosticsCluster.h

  \brief
    Multi-Sensor diagnostics cluster interface.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    11.10.14 Parthasarathy G - Created.
******************************************************************************/
#ifndef _MSDIAGNOSTICSCLUSTER_H
#define _MSDIAGNOSTICSCLUSTER_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zclDiagnosticsCluster.h>

/******************************************************************************
                    External variables section
******************************************************************************/
extern ZCL_DiagnosticsClusterServerAttributes_t msDiagnosticsClusterServerAttributes;

/******************************************************************************
                    Prototypes section
******************************************************************************/
/**************************************************************************//**
\brief Initializes diagnositcs cluster
******************************************************************************/
void diagnosticsClusterInit(void);


#endif // _MSDIAGNOSTICSCLUSTER_H

// eof msDiagnosticsCluster.h

