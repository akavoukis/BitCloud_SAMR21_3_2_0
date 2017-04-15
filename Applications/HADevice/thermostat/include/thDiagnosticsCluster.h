/**************************************************************************//**
  \file thDiagnosticsCluster.h

  \brief
    Thermostat diagnostics cluster interface.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    14.11.14 Parthasarathy G - Created.
******************************************************************************/
#ifndef _THDIAGNOSTICSCLUSTER_H
#define _THDIAGNOSTICSCLUSTER_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zclDiagnosticsCluster.h>

/******************************************************************************
                    External variables section
******************************************************************************/
extern ZCL_DiagnosticsClusterServerAttributes_t thDiagnosticsClusterServerAttributes;

/******************************************************************************
                    Prototypes section
******************************************************************************/
/**************************************************************************//**
\brief Initializes diagnositcs cluster
******************************************************************************/
void diagnosticsClusterInit(void);

#endif // _THDIAGNOSTICSCLUSTER_H

// eof thDiagnosticsCluster.h

