/*********************************************************************************************//**
\file  

\brief 

\author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2013, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

\internal

$Id: IN_AfIncomingData.h 24615 2013-02-27 05:14:24Z arazinkov $

***************************************************************************************************/

#ifndef IN_AFINCOMINGDATA_H
#define IN_AFINCOMINGDATA_H

/***************************************************************************************************
* INCLUDE FILES
***************************************************************************************************/

#include "N_Types.h"

/***************************************************************************************************
* C++ DECLARATION WRAPPER
***************************************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/***************************************************************************************************
* EXPORTED TYPES
***************************************************************************************************/
typedef struct IN_AfIncomingData_Callback_t
{
    /** Pass the incoming data
    *   \param dataInd The incoming data structure
    */
    void (*IncomingData)(APS_DataInd_t* dataInd);

    /** Guard to ensure the initializer contains all functions. Must be -1.
    */
    int8_t endOfList;
} IN_AfIncomingData_Callback_t;

/***************************************************************************************************
* EXPORTED MACROS AND CONSTANTS
***************************************************************************************************/


/***************************************************************************************************
* EXPORTED FUNCTIONS
***************************************************************************************************/

/** Subscribe to this component's callbacks.
    \param endpoint ZigBee end-point to subscribe to.
    \param pCallback Pointer to a callback structure filled with functions to be called,
                     use NULL for callbacks not of interrest.
*/
void IN_AfIncomingData_Subscribe(uint8_t endpoint, const IN_AfIncomingData_Callback_t* pCallback);

/***************************************************************************************************
* END OF C++ DECLARATION WRAPPER
***************************************************************************************************/

#ifdef __cplusplus
}
#endif

#endif // IA_AFINCOMINGDATA_H
