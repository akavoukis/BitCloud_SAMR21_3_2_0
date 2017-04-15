/*****************************************************************************//**
\file  halAtomic.h

\brief Declarations of hal atomic module.

\author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

\internal
  History:
    06/08/12 N. Fomin - Created
**********************************************************************************/
#ifndef _HAL_ATOMIC_H
#define _HAL_ATOMIC_H

/******************************************************************************
                   Prototypes section
******************************************************************************/
/******************************************************************************
\brief Initializes critical section
******************************************************************************/
void halInitCriticalSection(void);

/******************************************************************************
\brief disables global interrupt; enters atomic section
******************************************************************************/
void halStartAtomic(void);

/******************************************************************************
\brief Exits atomic section
******************************************************************************/
void halEndAtomic(void);

#endif //_HAL_ATOMIC_H
//eof halAtomic.h
