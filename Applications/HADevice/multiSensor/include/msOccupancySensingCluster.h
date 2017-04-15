/**************************************************************************//**
  \file msOccupancySensingCluster.h

  \brief
    Multi-Sensor Occupancy Sensing cluster interface.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    12.12.12 N. Fomin - Created.
    28.05.14 Viswanadham Kotla - Modified.
******************************************************************************/
#ifndef _MSOCCUPANCYSENSINGCLUSTER_H
#define _MSOCCUPANCYSENSINGCLUSTER_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zclOccupancySensingCluster.h>

/******************************************************************************
                    Definition(s) section
******************************************************************************/
#define OCCUPANCY_SENSING_VAL_MIN_REPORT_PERIOD 10
#define OCCUPANCY_SENSING_VAL_MAX_REPORT_PERIOD 20

/******************************************************************************
                    Externals
******************************************************************************/
extern ZCL_OccupancySensingClusterServerAttributes_t osOccupancySensingClusterServerAttributes;

/******************************************************************************
                    Prototypes section
******************************************************************************/
/**************************************************************************//**
\brief Initializes Occupancy Sensing cluster
******************************************************************************/
void occupancySensingClusterInit(void);

/**************************************************************************//**
\brief Toggles occupancy
******************************************************************************/
void occupancySensingToggleOccupancy(void);

#endif // _MSOCCUPANCYSENSINGCLUSTER_H

// eof msOccupancySensingCluster.h
