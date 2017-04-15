/**************************************************************************//**
  \file zdoAddrResolvingInt.h

  \brief Contains private prototypes and definitions for ZDO Address Resolving routines.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:
    21.06.12 D. Kolmakov - Created
  Last change:
    $Id: zdoAddrResolvingInt.h 27584 2015-01-09 14:45:42Z unithra.c $
******************************************************************************/
#ifndef _ZDOADDRRESOLVINGINTERNAL_H
#define _ZDOADDRRESOLVINGINTERNAL_H

/******************************************************************************
                        Includes section
******************************************************************************/
#include <zdo.h>

/******************************************************************************
                        Types section
******************************************************************************/
typedef enum _ZdoAddrResolvingState_t
{
  ZDO_ADDRESS_RESOLVING_IDLE_STATE = 0x01,
  ZDO_ADDRESS_RESOLVING_BEGIN_STATE = 0x02,
  ZDO_ADDRESS_RESOLVING_IEEE_ADDR_REQ_STATE = 0x03,
  ZDO_ADDRESS_RESOLVING_NWK_ADDR_REQ_STATE = 0x04,
  ZDO_ADDRESS_RESOLVING_CONFIRM_STATE = 0x05
} ZdoAddrResolvingState_t;

typedef struct _ZdoAddrResolving_t
{
  QueueDescriptor_t         queue;
  ZdoAddrResolvingState_t   state;
} ZdoAddrResolving_t;

/******************************************************************************
                        Prototypes section
******************************************************************************/
/******************************************************************************
  \brief Address Resolving request task handler.
  \param None.
  \return None.
******************************************************************************/
ZDO_PRIVATE void zdoAddrResolvingTaskHandler(void);

/******************************************************************************
  \brief Reset Address Resolving component.
  \param None.
  \return None.
******************************************************************************/
ZDO_PRIVATE void zdoResetAddrResolving(void);

#endif // _ZDOADDRRESOLVINGINTERNAL_H
