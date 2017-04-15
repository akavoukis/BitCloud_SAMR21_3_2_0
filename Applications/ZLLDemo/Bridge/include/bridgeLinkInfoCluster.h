/**************************************************************************//**
  \file bridgeLinkInfoCluster.h

  \brief
    Control Bridge device Link Info cluster interface.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2013, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    25.01.13 N. Fomin - Created.
******************************************************************************/
#ifndef _BRIDGELINKINFOCLUSTER_H
#define _BRIDGELINKINFOCLUSTER_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zclLinkInfoCluster.h>

/******************************************************************************
                    Externals
******************************************************************************/
extern ZCL_LinkInfoClusterCommands_t linkInfoCommands;

/******************************************************************************
                    Prototypes section
******************************************************************************/
/**************************************************************************//**
\brief Initialize Link Info cluster
******************************************************************************/
void linkInfoClusterInit(void);

#endif // _BRIDGELINKINFOCLUSTER_H

// eof bridgeLinkInfoCluster.h
