/**************************************************************************//**
  \file thFanControlCluster.h

  \brief
    Thermostat Fan Control cluster interface.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    06.11.14 Viswanadham Kotla - Created.
******************************************************************************/
#ifndef _THFANCONTROLCLUSTER_H
#define _THFANCONTROLCLUSTER_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zclFanControlCluster.h>
#include <haClusters.h>

/******************************************************************************
                    Externals
******************************************************************************/
extern ZCL_FanControlClusterServerAttributes_t thFanControlClusterServerAttributes;

/******************************************************************************
                    Prototypes section
******************************************************************************/
/**************************************************************************//**
\brief Initializes Fan Control cluster

\param[in]- None
\param[out] - None
******************************************************************************/
void fanControlClusterInit(void);

/**************************************************************************//**
\brief Occupancy notification from Occupancy (client/server) cluster

\param[in] occupied - 0 - Not occupied, 1- occupied
\param[out] - None
******************************************************************************/
void thFanControlOccupancyNotify(bool occupied);

#endif // _THFANCONTROLCLUSTER_H

// eof thFanControlCluster.h
