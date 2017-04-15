/**************************************************************************//**
  \file commandManager.h

  \brief
    Interface to provide command managenent for application.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    10.04.12 N.Fomin - Created.
******************************************************************************/
#ifndef _COMMANDMANAGER_H
#define _COMMANDMANAGER_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zcl.h>

/******************************************************************************
                    Prototypes
******************************************************************************/
/**************************************************************************//**
\brief Initialize common cluster functionality
******************************************************************************/
void commandManagerInit(void);

/**************************************************************************//**
\brief Get free ZCL command buffer

\returns command buffer pointer or NULL if no free buffers left
******************************************************************************/
ZCL_Request_t *commandManagerAllocCommand(void);

/**************************************************************************//**
\brief Sends command

\param[in] req - request parameters
******************************************************************************/
void commandManagerSendCommand(ZCL_Request_t *req);

/**************************************************************************//**
\brief Sends attribute request
\param[in] req - request parameters
******************************************************************************/
void commandManagerSendAttribute(ZCL_Request_t *req);

#endif // _COMMANDMANAGER_H

// eof commandManager.h
