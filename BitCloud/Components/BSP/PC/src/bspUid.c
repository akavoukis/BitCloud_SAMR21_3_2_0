/**************************************************************************//**
\file  bspUid.c

\brief Implementation of UID interface.

\author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

\internal
  History:
    26/12/14 Prashanth.Udumula - Created
*******************************************************************************/

/******************************************************************************
                   Includes section
******************************************************************************/
#include <bspUid.h>

/******************************************************************************
                   Types section
******************************************************************************/
/** \brief uid type. */
typedef union
{
  uint64_t uid;
  uint8_t array[sizeof(uint64_t)];
} BspUid_t;

/******************************************************************************
                   Global variables section
******************************************************************************/
static BspUid_t bspUid = {.uid = 0ull};

/******************************************************************************
                   Implementations section
******************************************************************************/
/******************************************************************************
 Reads uid from external spi eeprom at25010a.
******************************************************************************/
void bspReadUid(void)
{
}

/******************************************************************************
 Returns number which was read from external eeprom.
 Parameters:
   id - UID buffer pointer.
 Returns:
   0 - if unique ID has been found without error;
  -1 - if there are some erros during UID discovery.
******************************************************************************/
int BSP_ReadUid(uint64_t *id)
{
  if (!id)
    return -1;

  bspReadUid();

  *id = bspUid.uid;
  return 0;
}

// eof bspUid.c
