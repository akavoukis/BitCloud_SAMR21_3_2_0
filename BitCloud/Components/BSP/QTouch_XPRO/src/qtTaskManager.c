/************************************************************************//**
\file qtTaskManager.c

\brief
The QTouch Task manager

\author
Atmel Corporation: http://www.atmel.com \n
Support email: avr@atmel.com

Copyright (c) 2008-2012, Atmel Corporation. All rights reserved.
Licensed under Atmel's Limited License Agreement (BitCloudTM).

\internal
History:
14.08.14 Kanchana - Created.
******************************************************************************/
#ifdef BOARD_QTOUCH_XPRO
/******************************************************************************
Includes section
******************************************************************************/
#include <touch_api_ptc.h>
#include <atsamr21.h>
#include <qtTaskManager.h>
#include <bspTaskManager.h>
#include <qtTimer.h>
#include <appTimer.h>

/* Macros */

/**
* \def GET_SENSOR_STATE(SENSOR_NUMBER)
* \brief To get the sensor state that it is in detect or not
* \param SENSOR_NUMBER for which the state to be detected
* \return Returns either 0 or 1
* If the bit value is 0, it is not in detect
* If the bit value is 1, it is in detect
* Alternatively, the individual sensor state can be directly accessed using
* p_qm_measure_data->p_sensor_states[(SENSOR_NUMBER/8)] variable.
*/
//#define GET_SELFCAP_SENSOR_STATE(SENSOR_NUMBER) p_selfcap_measure_data-> \
p_sensor_states[(SENSOR_NUMBER / \
  8)] & (1 << (SENSOR_NUMBER % 8))

/**
* \def GET_ROTOR_SLIDER_POSITION(ROTOR_SLIDER_NUMBER)
* \brief To get the rotor angle or slider position.
* These values are valid only when the sensor state for
* corresponding rotor or slider shows in detect.
* \param ROTOR_SLIDER_NUMBER for which the position to be known
* \return Returns rotor angle or sensor position
*/
//#define GET_SELFCAP_ROTOR_SLIDER_POSITION(ROTOR_SLIDER_NUMBER) \
p_selfcap_measure_data->p_rotor_slider_values[ \
  ROTOR_SLIDER_NUMBER]     
    
static uint8_t touch_button_previous_state[2];
static BSP_TouchEventHandler_t bspTouchEventHandler = NULL;
void configure_port_pins(void);
void timer_init( void );


/**************************************************************************//**
\brief callback from Timer
******************************************************************************/
void Timer_overflow_callback(void)
{
  touch_time.time_to_measure_touch = 1;
  touch_time.current_time_ms = touch_time.current_time_ms + touch_time.measurement_period_ms;
  bspPostTask(BSP_TOUCH_BUTTON);
    
}

/**************************************************************************//**
\brief Init timer for qtouch measure
******************************************************************************/
void timer_init(void)
{
  StartAppClock();
}

/**************************************************************************//**
\brief configure port pins for LEDS
******************************************************************************/
void configure_port_pins(void)
{
  halInitLed0();
  halInitLed1();
  halInitLed2();
  halInitLed3();
  halInitLed4();
  halInitLed5();
  halInitLed6();
  halInitLed7();
  halInitLed8();
  halInitLed9();
}

/**************************************************************************//**
\brief LED On for Slider
******************************************************************************/
void Slider_LED_On(uint8_t slider_position)
{
  slider_position = slider_position >> 5;
  Slider_LED_Off();
  switch(slider_position)
  {
  case 0:
    halOnLed0();
    break;
  case 1:
    halOnLed0();
    halOnLed1();
    break;
  case 2:
    halOnLed0();
    halOnLed1();
    halOnLed2();
    break;
  case 3:
    halOnLed0();
    halOnLed1();
    halOnLed2();
    halOnLed3();
    break;
  case 4:
    halOnLed0();
    halOnLed1();
    halOnLed2();
    halOnLed3();
    halOnLed4();
    break;
  case 5:
    halOnLed0();
    halOnLed1();
    halOnLed2();
    halOnLed3();
    halOnLed4();
    halOnLed5();
    break;
  case 6:
    halOnLed0();
    halOnLed1();
    halOnLed2();
    halOnLed3();
    halOnLed4();
    halOnLed5();
    halOnLed6();
    break;
  case 7:
    halOnLed0();
    halOnLed1();
    halOnLed2();
    halOnLed3();
    halOnLed4();
    halOnLed5();
    halOnLed6();
    halOnLed7();
    break;
  default:
    halOnLed0();
    halOnLed1();
    halOnLed2();
    halOnLed3();
    halOnLed4();
    halOnLed5();
    halOnLed6();
    halOnLed7();
    break;
  }
}

/**************************************************************************//**
\brief OFF Slider LED's
******************************************************************************/
void Slider_LED_Off(void)
{
  halOffLed0();
  halOffLed1();
  halOffLed2();
  halOffLed3();
  halOffLed4();
  halOffLed5();
  halOffLed6();
  halOffLed7();
}

/**************************************************************************//**
\brief On/Off Right Button LED
******************************************************************************/
void ButtonR_LED_Ind(bool off)
{
  if(off)
  {
    halOffLed8();
  }
  else
  {
    halOnLed8();
  }
}

/**************************************************************************//**
\brief On/Off Left Button LED
******************************************************************************/
void ButtonL_LED_Ind(bool off)
{
  if(off)
  {
    halOffLed9();
  }
  else
  {
    halOnLed9();
  }
}

/**************************************************************************//**
\brief Init QTouch 
******************************************************************************/
void BSP_InitQTouch(BSP_TouchEventHandler_t handler)
{
  
  __enable_interrupt();
  
  
  /**
  * Initialize timer.
  */
  timer_init();
  
  /**
  * Initialize QTouch library and configure touch sensors.
  */
  touch_sensors_init();
  
  /**
  * Configure port pins
  */
  //configure_port_pins();
  
  /**
  * Turn off all extension board LEDs
  */
  //Slider_LED_Off();
 // ButtonR_LED_Ind(1);
  //ButtonL_LED_Ind(1);
  
  bspTouchEventHandler = handler;
  
}

/**************************************************************************//**
\brief BSP Touch handler
******************************************************************************/
void bspTouchHandler(void)
{ 
  uint8_t button1_state,temp_button1_state;
  uint8_t button2_state,temp_button2_state;
  uint8_t slider_state;
  uint8_t button,event = TOUCHKEY_NO_EVENT;
  uint8_t slider_threshold;
  
  /**
  * Start touch sensor measurement, if touch_time.time_to_measure_touch flag is set by timer.
  */
  touch_sensors_measure();
  
  /**
  * Update touch status once measurement complete flag is set.
  */
  if ((p_mutlcap_measure_data->measurement_done_touch == 1u)) 
  {
    p_mutlcap_measure_data->measurement_done_touch = 0u;
    
    /**
    * Get touch sensor states
    */
    
    button2_state = (p_mutlcap_measure_data->p_sensor_states[0]&0x01);
    button1_state = (p_mutlcap_measure_data->p_sensor_states[0]&0x02);
    slider_state = (p_mutlcap_measure_data->p_sensor_states[0]&0x10);//GET_MUTLCAP_SENSOR_STATE(2);
    
    temp_button1_state = (button1_state >> 0x01) ^ touch_button_previous_state[0];
    temp_button2_state = button2_state ^ touch_button_previous_state[1];
    
    if(temp_button1_state || temp_button2_state || slider_state)
    {
      
      if(button1_state)
      {
        button = BUTTON_L;  // Heat set Point  Right
        event = TOUCHKEY_PRESSED_EVENT;
      }
      else if(temp_button1_state)
      {
        button = BUTTON_L;  // Heat set Point  Right
        event = TOUCHKEY_RELEASED_EVENT;        
      }
      if(button2_state)
      {
        button = BUTTON_R;  // Cool set Point  Left
        event = TOUCHKEY_PRESSED_EVENT; 
      }
      else if (temp_button2_state)
      {
        button = BUTTON_R;  // Cool set Point  Left
        event = TOUCHKEY_RELEASED_EVENT;          
      }
      
      if(slider_state)
      {
        slider_threshold = GET_MUTLCAP_ROTOR_SLIDER_POSITION(0);
        button = BUTTON_SLIDER;
        event = TOUCHKEY_PRESSED_EVENT;
      }
      
      /* Store back the current sensor status */ 
      temp_button1_state = 0;
      temp_button2_state = 0;
      touch_button_previous_state[0] = button1_state >> 0x01;
      touch_button_previous_state[1] = button2_state;
      
      if (event != TOUCHKEY_NO_EVENT)
      {                 
        bspTouchEventHandler(event,button,slider_threshold);
      }
    }
  }
  
}//main

#endif