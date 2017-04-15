/**************************************************************************//**
  \file blink.c

  \brief Blink application.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
******************************************************************************/

#include <appTimer.h>
#include <zdo.h>
#include <blink.h>
#include <sysTaskManager.h>

static HAL_AppTimer_t blinkTimer;                           // Blink timer

static HAL_AppTimer_t changeBlinkTimer;                     // Buttons emulation timer

static void buttonsReleased(uint8_t buttonNumber);          // Button release event handler
static void blinkTimerFired(void);                          // blinkTimer handler

static void changeTimerFired(void);                         //Buttons emulation timer handler

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
  BSP_OpenLeds(); // Enable LEDs

  BSP_OnLed(LED_RED);
  BSP_OnLed(LED_YELLOW);
  BSP_OnLed(LED_GREEN);

  BSP_OpenButtons(NULL, buttonsReleased);         // Register button event handlers
  // Configure the timer for changing blinking interval
  changeBlinkTimer.interval = 10000;              // Timer interval in milliseconds
  changeBlinkTimer.mode     = TIMER_REPEAT_MODE;  // Repetition mode (TIMER_REPEAT_MODE or TIMER_ONE_SHOT_MODE)
  changeBlinkTimer.callback = changeTimerFired;   // Callback function for timer fire event
  HAL_StartAppTimer(&changeBlinkTimer);           // Start the change blink timer
  // Configure the blink timer
  blinkTimer.interval = APP_BLINK_INTERVAL;       // Timer interval
  blinkTimer.mode     = TIMER_REPEAT_MODE;        // Repeating mode (TIMER_REPEAT_MODE or TIMER_ONE_SHOT_MODE)
  blinkTimer.callback = blinkTimerFired;          // Callback function for timer fire event
  HAL_StartAppTimer(&blinkTimer);                 // Start the blink timer
}

/*******************************************************************************
  \brief Change blink timer handler

  \return none
*******************************************************************************/
void changeTimerFired(void)
{
  static uint8_t button = APP_HALF_PERIOD_BUTTON;
  //Buttons emulation
  buttonsReleased(button);
  if (APP_HALF_PERIOD_BUTTON == button)
    button = APP_DOUBLE_PERIOD_BUTTON;
  else
    button = APP_HALF_PERIOD_BUTTON;
}
/*******************************************************************************
  \brief Blinking timer handler

  \return none
*******************************************************************************/
static void blinkTimerFired()
{
  BSP_ToggleLed(LED_RED);
  BSP_ToggleLed(LED_YELLOW);
  BSP_ToggleLed(LED_GREEN);
}

/*******************************************************************************
  \brief Button release event handler

  \return none
*******************************************************************************/
static void buttonsReleased(uint8_t buttonNumber)
{
  HAL_StopAppTimer(&blinkTimer); // Stop blink timer

  // Dependent on button being released, update blink interval
  if (APP_HALF_PERIOD_BUTTON == buttonNumber)
  {
    blinkTimer.interval /= 2;
    if (blinkTimer.interval < APP_MIN_BLINK_INTERVAL)
      blinkTimer.interval = APP_MIN_BLINK_INTERVAL;
  }
  else if (APP_DOUBLE_PERIOD_BUTTON == buttonNumber)
  {
    blinkTimer.interval *= 2;
    if (blinkTimer.interval > APP_MAX_BLINK_INTERVAL)
      blinkTimer.interval = APP_MAX_BLINK_INTERVAL;
  }

  blinkTimerFired();              // Update LED status immediately.
  HAL_StartAppTimer(&blinkTimer); // Start updated blink timer.
}

/*******************************************************************************
  \brief The function is called by the stack to notify the application about 
  various network-related events. See detailed description in API Reference.
  
  Mandatory function: must be present in any application.

  \param[in] nwkParams - contains notification type and additional data varying
             an event
  \return none
*******************************************************************************/
void ZDO_MgmtNwkUpdateNotf(ZDO_MgmtNwkUpdateNotf_t *nwkParams)
{
  nwkParams = nwkParams;  // Unused parameter warning prevention
}

/*******************************************************************************
  \brief The function is called by the stack when the node wakes up by timer.
  
  When the device starts after hardware reset the stack posts an application
  task (via SYS_PostTask()) once, giving control to the application, while
  upon wake up the stack only calls this indication function. So, to provide 
  control to the application on wake up, change the application state and post
  an application task via SYS_PostTask(APL_TASK_ID) from this function.

  Mandatory function: must be present in any application.
  
  \return none
*******************************************************************************/
void ZDO_WakeUpInd(void)
{
}

#ifdef _BINDING_
/***********************************************************************************
  \brief The function is called by the stack to notify the application that a 
  binding request has been received from a remote node.
  
  Mandatory function: must be present in any application.

  \param[in] bindInd - information about the bound device
  \return none
 ***********************************************************************************/
void ZDO_BindIndication(ZDO_BindInd_t *bindInd)
{
  (void)bindInd;
}

/***********************************************************************************
  \brief The function is called by the stack to notify the application that a 
  binding request has been received from a remote node.

  Mandatory function: must be present in any application.
  
  \param[in] unbindInd - information about the unbound device
  \return none
 ***********************************************************************************/
void ZDO_UnbindIndication(ZDO_UnbindInd_t *unbindInd)
{
  (void)unbindInd;
}
#endif //_BINDING_

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

//eof blink.c
