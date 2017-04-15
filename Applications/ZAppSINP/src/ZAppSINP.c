/**************************************************************************//**
  \file ZAppSINP.c

  \brief ZAppSI Network Processor application.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2011, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
******************************************************************************/
#include <zdo.h>
#include <zsiNotify.h>

/*******************************************************************************
  \brief Application task handler. The function is called by the internal
  task scheduler to process an application task. The task scheduler
  understands that a new application task appeared when the SYS_PostTask()
  function is called with APL_TASK_ID as an argument.

  Application task handler is used to implement the application's state machine. 
  Typically, an application changes its state on occurence of some event
  or invocation of a callback function, then calls SYS_PostTask(APL_TASK_ID),
  and the task scheduler directs this call to the APL_TaskHandler() function
  which switches between the application states.

  Mandatory function: must be present in any application.

  \return none
*******************************************************************************/
void APL_TaskHandler(void)
{
}

/**************************************************************************//**
\brief Indicates zsi status update.

\param[out] notf - ZSI staus update indication parameters structure pointer. For details go to
            ZSI_UpdateNotf_t declaration.
\return none
******************************************************************************/
void ZSI_StatusUpdateNotf(ZSI_UpdateNotf_t *notf)
{
  (void)notf;
}

/**********************************************************************//**
  \brief The entry point of the program. This function should not be
  changed by the user without necessity and must always include an
  invocation of the SYS_SysInit() function and an infinite loop with
  SYS_RunTask() function called on each step.

  \return none
**************************************************************************/
int main(void)
{
  //Initialization of the System Environment
  SYS_SysInit();

  //The infinite loop maintaing task management
  for(;;)
  {
    //Each time this function is called, the task
    //scheduler processes the next task posted by one
    //of the BitCloud components or the application
    SYS_RunTask();
  }
}

//eof ZAppSINP.c
