/***************************************************************************//**
  \file WSNMessageSender.h

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
    $Id: WSNMessageSender.h 27584 2015-01-09 14:45:42Z unithra.c $
*******************************************************************************/
#ifndef _WSNMESSAGESENDER_H
#define _WSNMESSAGESENDER_H

/*****************************************************************************
                              Includes section
******************************************************************************/
#include <WSNDemoApp.h>

/*****************************************************************************
                               Types section
******************************************************************************/
/** Message sender frame */
typedef struct _AppCmdHandlerTxFrame_t
{
  AppCommandFrame_t cmdFrame;
  APS_DataReq_t msgParams;
} AppCmdHandlerTxFrame_t;

/*****************************************************************************
                              Prototypes section
******************************************************************************/

/**************************************************************************//**
  \brief Initializes message sender.

  \param  None.

  \return None.
******************************************************************************/
void appInitMsgSender(void);

/**************************************************************************//**
  \brief Performs message transmiting.

  \param  None.

  \return None.
******************************************************************************/
void appMsgSender(void);

/**************************************************************************//**
  \brief Inserts new element into the tx queue.

  \param[in, out] pMsgParamsPtr - pointer to pointer to APS_DataReq_t. If
                  *pMsgParamsPtr == NULL copying won't be executed. On the output
                  if function returns true *pMsgParamsPtr will refer to allocated cell.
  \param[in, out] pCommandPtr - pointer to pointer to AppCommand_t. If
                  *pCommandPtr == NULL copying won't be executed. On the output
                  if function returns true *pCommandPtr will refer to allocated cell.
  \param[in]      onTxFinishedCb - pointer to a callback function called upon transmission
                  end. If onTxFinishedCb == NULL nothing will be done upon
                  transmission end.

  \return true if insertion was successful, false otherwise.
******************************************************************************/
bool appCreateTxFrame(APS_DataReq_t **pMsgParamsPtr, AppCommand_t **pCommandPtr, 
                      void (*onTxFinishedCb)(AppCmdHandlerTxFrame_t *txFrame));

/**************************************************************************//**
  \brief Returs current tx queue status.

  \param  None.

  \return true if tx queue is free, false otherwise.
******************************************************************************/
bool appIsTxQueueFree(void);

#endif // _WSNMESSAGESENDER_H
