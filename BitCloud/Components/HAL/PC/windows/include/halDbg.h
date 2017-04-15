/**********************************************************************//**
  \file halDbg.h
  \brief

  \author

  \internal
  History:
    29/02/12 N. Fomin - Created
**************************************************************************/
#ifndef _HALDBG_H
#define _HALDBG_H

/******************************************************************************
                   Includes section
******************************************************************************/
#include <dbg.h>

/******************************************************************************
                   Define(s) section
******************************************************************************/
enum
{
  APPTIMER_MISTAKE                         = 0x2000,
  INCORRECT_EEPROM_ADDRESS                 = 0x2001,
  MEMORY_CANNOT_WRITE                      = 0x2002,
  USARTC_HALUNKNOWNERRORREASON_0           = 0x2003,
  USARTC_HALUNKNOWNERRORREASON_1           = 0x2004,
  USARTC_HALSIGUSARTTRANSMISSIONCOMPLETE_0 = 0x2005,
  USARTC_HALSIGUSARTRECEPTIONCOMPLETE_0    = 0x2006,
  HSMCI_CLOCK_DIVIDER_ERROR                = 0x2007,
  APPTIMER_HANDLER_0                       = 0x2008,
};

/******************************************************************************
                   Prototypes section
******************************************************************************/

#endif /* _HALDBG_H */

//eof halDbg.h
