/**********************************************************************//**
  \file WSNMessageSender.c

  \brief Contains functions for sending application commands to the
         radio through ZigBee stack.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:
    24/01/12 D. Kolmakov - Created

  Last change:
    $Id: WSNMessageSender.c 27584 2015-01-09 14:45:42Z unithra.c $
**************************************************************************/

/*****************************************************************************
                              Includes section
******************************************************************************/
#include <sysUtils.h>
#include <sysQueue.h>
#include <WSNDemoApp.h>
#include <WSNMessageSender.h>
#include <WSNVisualizer.h>
#include <WSNCommandHandler.h>

/*****************************************************************************
                               Types section
******************************************************************************/
/* Message transmitter states */
typedef enum
{
  APP_MSG_TX_FREE_STATE,
  APP_MSG_TX_WAITING_STATE,
  APP_MSG_TX_SENDING_DONE_STATE,
  APP_MSG_TX_SENDING_FAILED_STATE
} AppMsgTxState_t;

/* Message queue element */
typedef struct _AppTxQueueElement_t
{
  /** Service field, used for queue support */
  QueueElement_t next;

  /** Application command */
  AppCmdHandlerTxFrame_t message;

  /** On tx finished callback. */
  void (*onTxFinished)(AppCmdHandlerTxFrame_t *txFrame);
    
} AppTxQueueElement_t;

/****************************************************************************
                              Static functions prototypes section
******************************************************************************/
static void msgSenderApsDataConf(APS_DataConf_t *confInfo);
static QueueElement_t *appRemoveQueueElement(QueueDescriptor_t *queue, QueueElement_t *element);
static AppCmdHandlerTxFrame_t *appGetFirstTxFrame(QueueDescriptor_t *queue);

/*****************************************************************************
                              Local variables section
******************************************************************************/
static AppMsgTxState_t txState = APP_MSG_TX_FREE_STATE;
static uint8_t failedTransmission = 0;

/** Buffers for application messages */
static AppTxQueueElement_t  appTxBuffers[MAX_APP_MSG_QUEUE_COUNT];

/** Queue of outcoming application messages. */
static DECLARE_QUEUE(appToSendQueue);

/** Queue of free cells for application messages. */
static DECLARE_QUEUE(appFreeQueue);

/** Queue of sent application messages. */
static DECLARE_QUEUE(appSentQueue);

/** Queue of confirmed application messages. */
static DECLARE_QUEUE(appDoneQueue);

/******************************************************************************
                              Implementations section
******************************************************************************/
/**************************************************************************//**
  \brief Initializes message sender

  \return none
******************************************************************************/
void appInitMsgSender(void)
{
  txState = APP_MSG_TX_FREE_STATE;

  resetQueue(&appToSendQueue);
  resetQueue(&appFreeQueue);
  resetQueue(&appSentQueue);
  resetQueue(&appDoneQueue);

  for (uint8_t i = 0; i < ARRAY_SIZE(appTxBuffers); i++)
  {
    if(!putQueueElem(&appFreeQueue, &appTxBuffers[i].next))
    {
      /* failed to queue */
    }
  }
}

/**************************************************************************//**
  \brief Sends application messages to other nodes in the network

  \return none
******************************************************************************/
void appMsgSender(void)
{
  AppCmdHandlerTxFrame_t *txFrame;

  switch (txState)
  {
    case APP_MSG_TX_FREE_STATE:

      txFrame = appGetFirstTxFrame(&appToSendQueue);

      if (txFrame)
      {
        visualizeAirTxStarted();

        //Set the callback function that will be called to report
        //the state of message's transmission or - if acknowledgement 
        //is requested - delivery
        txFrame->msgParams.APS_DataConf = msgSenderApsDataConf;
        //Set the application payload of the data frame - actual data sent by the
        //application
        txFrame->msgParams.asdu = (uint8_t *)(&txFrame->cmdFrame.command);

        //Send the data request to the stack. As a result the data frame is passed
        //through the stack layers down to the physical layer and is transmitted 
        //to the air.
        APS_DataReq(&txFrame->msgParams);

        if(!putQueueElem(&appSentQueue, deleteHeadQueueElem(&appToSendQueue)))
        {
          /* failed to queue */
        }

        appPostMsgSenderTask();
      }
      break;

    case APP_MSG_TX_SENDING_FAILED_STATE:
#if APP_DEVICE_TYPE != DEV_TYPE_COORDINATOR
      appLeaveNetwork();
#endif

    case APP_MSG_TX_SENDING_DONE_STATE:
      txFrame = appGetFirstTxFrame(&appDoneQueue);

      while (txFrame)
      {
        AppTxQueueElement_t *txQueueElement = GET_STRUCT_BY_FIELD_POINTER(AppTxQueueElement_t, 
                                                                          message, 
                                                                          txFrame);

        if (txQueueElement->onTxFinished)
        {
          txQueueElement->onTxFinished(&txQueueElement->message);
        }

        if(!putQueueElem(&appFreeQueue, appRemoveQueueElement(&appDoneQueue, &txQueueElement->next)))
        {
          /* failed to queue */
        }
        txFrame = appGetFirstTxFrame(&appDoneQueue);
      }

      visualizeAirTxFInished();
      txState = APP_MSG_TX_FREE_STATE;
      appPostMsgSenderTask();
      break;

    default:
      break;
  }
}

/**************************************************************************//**
  \brief Message sender APS data confirm callback

  \param[in] confInfo - confirm information
  \return none
******************************************************************************/
static void msgSenderApsDataConf(APS_DataConf_t *confInfo)
{
  QueueDescriptor_t *dstQueue;
  AppTxQueueElement_t *txQueueElement = GET_STRUCT_BY_FIELD_POINTER(AppTxQueueElement_t,
                                                                    message.msgParams.confirm,
                                                                    confInfo);

  if (APS_SUCCESS_STATUS == confInfo->status)
  {
    failedTransmission = 0;
    txState = APP_MSG_TX_SENDING_DONE_STATE;
    dstQueue = &appDoneQueue;
  }
  else
  {
    if (APP_THRESHOLD_FAILED_TRANSMISSION > ++failedTransmission)
    {
      txState = APP_MSG_TX_FREE_STATE;
      dstQueue = &appToSendQueue;
    }
    else
    {
      failedTransmission = 0;
      txState = APP_MSG_TX_SENDING_FAILED_STATE;
      dstQueue = &appDoneQueue;
    }
  }

  if(!putQueueElem(dstQueue, appRemoveQueueElement(&appSentQueue, &txQueueElement->next)))
  {
    /* failed to queue */
  }
  appPostMsgSenderTask();
}

/**************************************************************************//**
  \brief Removes specified element from queue

  \param[in] queue - queue descriptor
  \param[in] element - element to be removed

  \return pointer to removed element
******************************************************************************/
static QueueElement_t *appRemoveQueueElement(QueueDescriptor_t *queue, QueueElement_t *element)
{
  if (queue->head == element)
  {
    return deleteHeadQueueElem(queue);
  }
  else
  {
    QueueElement_t *prev = queue->head;

    while (prev->next)
    {
      if (prev->next == element)
      {
        prev->next = element->next;
        break;
      }
      prev = prev->next;
    }
  }

  return element;
}

/**************************************************************************//**
  \brief Returs current tx queue status

  \return true if tx queue is free, false otherwise
******************************************************************************/
bool appIsTxQueueFree(void)
{
  return (getQueueElem(&appToSendQueue) || 
          getQueueElem(&appSentQueue) ||
          getQueueElem(&appDoneQueue)) ? false : true;
}

/**************************************************************************//**
  \brief Returns pointer to first frame in specified queue

  \param[in] queue - queue descriptor
  \return pointer to AppCmdHandlerTxFrame_t if queue is not empty, NULL otherwise
******************************************************************************/
static AppCmdHandlerTxFrame_t *appGetFirstTxFrame(QueueDescriptor_t *queue)
{
  QueueElement_t *queueElement = getQueueElem(queue);

  if (queueElement)
  {
    return &(GET_STRUCT_BY_FIELD_POINTER(AppTxQueueElement_t,
                                         next,
                                         queueElement))->message;
  }

  return NULL;
}

/**************************************************************************//**
  \brief Inserts new element into the tx queue

  \param[in, out] pMsgParamsPtr - pointer to pointer to APS_DataReq_t. If
                  *pMsgParamsPtr == NULL copying won't be executed. On the output
                  if function returns true *pMsgParamsPtr will refer to allocated cell.
  \param[in, out] pCommandPtr - pointer to pointer to AppCommand_t. If
                  *pCommandPtr == NULL copying won't be executed. On the output
                  if function returns true *pCommandPtr will refer to allocated cell.
  \param[in]      onTxFinishedCb - pointer to a callback function called upon transmission
                  completion

  \return true if insertion was successful, false otherwise
******************************************************************************/
bool appCreateTxFrame(APS_DataReq_t **pMsgParamsPtr, AppCommand_t **pCommandPtr, void (*onTxFinishedCb)(AppCmdHandlerTxFrame_t *txFrame))
{
  AppTxQueueElement_t *appTxQueueElement = NULL;
  QueueElement_t *freeElement = NULL;
  bool result;

  sysAssert((pCommandPtr && pMsgParamsPtr), TXQUEUEINSERTASSERT_0);

  freeElement = getQueueElem(&appFreeQueue);

  if (freeElement)
  {
    if(!putQueueElem(&appToSendQueue, deleteHeadQueueElem(&appFreeQueue)))
    {
      /* failed to queue */
    }
    appTxQueueElement = GET_STRUCT_BY_FIELD_POINTER(AppTxQueueElement_t,
                                                    next,
                                                    freeElement);

    if (*pCommandPtr)
    {
      memcpy(&appTxQueueElement->message.cmdFrame.command, *pCommandPtr, sizeof(AppCommand_t));
    }

    if (*pMsgParamsPtr)
    {
      memcpy(&appTxQueueElement->message.msgParams, *pMsgParamsPtr, sizeof(APS_DataReq_t));
    }

    *pCommandPtr = &appTxQueueElement->message.cmdFrame.command;
    *pMsgParamsPtr = &appTxQueueElement->message.msgParams;
    appTxQueueElement->onTxFinished = onTxFinishedCb;

    result = true;
  }
  else
  {
    result = false;
  }

  appPostMsgSenderTask();
  return result;
}

