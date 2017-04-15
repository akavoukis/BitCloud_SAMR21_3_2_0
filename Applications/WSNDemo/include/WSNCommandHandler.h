/***************************************************************************//**
  \file WSNCommandHandler.h

  \brief

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:
    24/01/12 D. Kolmakov - Created

  Last change:
    $Id: WSNCommandHandler.h 27584 2015-01-09 14:45:42Z unithra.c $
*******************************************************************************/
#ifndef _WSNCOMMANDHANDLER_H
#define _WSNCOMMANDHANDLER_H

/*****************************************************************************
                              Includes section
******************************************************************************/
#include <WSNCommand.h>

/*****************************************************************************
                              Prototypes section
******************************************************************************/

/**************************************************************************//**
  \brief Initializes command handler.

  \param  None.

  \return None.
******************************************************************************/
void appInitCmdHandler(void);

/**************************************************************************//**
  \brief Handles application command from appCmdQueue.

  \param  None.

  \return None.
******************************************************************************/
void appCmdHandler(void);

/**************************************************************************//**
  \brief Inserts new element into the command queue.

  \param[in,out] pCommandPtr - pointer to pointer to AppCommand_t. On the output
                               if function returns true *pCommandPtr will
                               refer to allocated cell.

  \return true if insertion was successful, false otherwise.
******************************************************************************/
bool appCreateCommand(AppCommand_t **pCommandPtr);

/**************************************************************************//**
  \brief Returs current command queue status.

  \param  None.

  \return true if command queue is free, false otherwise.
******************************************************************************/
bool appIsCmdQueueFree(void);

#endif // _WSNCOMMANDHANDLER_H
