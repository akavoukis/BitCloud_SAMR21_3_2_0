/**********************************************************************//**
  \file WSNVisualizer.c

  \brief

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:
    18/12/08 A. Luzhetsky - Modified
**************************************************************************/

/************************************************************************
**************************************************************************/
#include <WSNDemoApp.h>

/************************************************************************
**************************************************************************/
void visualizeAppStarting(void);
void visualizeNwkStarting(void);
void visualizeNwkStarted(void);
void visualizeNwkLeaving(void);
void visualizeNwkLeft(void);
void visualizeAirTxStarted(void);
void visualizeAirTxFInished(void);
void visualizeAirRxFinished(void);
void visualizeSerialTx(void);
void visualizeWakeUp(void);
void visualizeSleep(void);

/************************************************************************
**************************************************************************/
void visualizeAppStarting(void)
{
  BSP_OpenLeds();
}

/************************************************************************
**************************************************************************/
void visualizeNwkStarting(void)
{
  BSP_ToggleLed(LED_RED);
  BSP_OffLed(LED_YELLOW);
  BSP_OffLed(LED_GREEN);
}

/************************************************************************
**************************************************************************/
void visualizeNwkStarted(void)
{
  BSP_OnLed(LED_RED);
  BSP_OffLed(LED_YELLOW);
  BSP_OffLed(LED_GREEN);
}

/************************************************************************
**************************************************************************/
void visualizeNwkLeaving(void)
{
  BSP_OffLed(LED_GREEN);
}

/************************************************************************
**************************************************************************/
void visualizeNwkLeft(void)
{
  BSP_OffLed(LED_GREEN);
}

/************************************************************************
**************************************************************************/
void visualizeAirTxStarted(void)
{
  BSP_OnLed(LED_GREEN);
}

/************************************************************************
**************************************************************************/
void visualizeAirTxFInished(void)
{
  BSP_OffLed(LED_GREEN);
}

/************************************************************************
**************************************************************************/
void visualizeAirRxFinished(void)
{
  BSP_ToggleLed(LED_YELLOW);
}

/************************************************************************
**************************************************************************/
void visualizeSerialTx(void)
{
  BSP_ToggleLed(LED_GREEN);
}

/************************************************************************
**************************************************************************/
void visualizeWakeUp(void)
{
  BSP_OpenLeds();
  BSP_OnLed(LED_RED);
}

/************************************************************************
**************************************************************************/
void visualizeSleep(void)
{
  BSP_CloseLeds();
}
/************************************************************************
**************************************************************************/
void visualizeIdentity(void)
{
  BSP_ToggleLed(LED_RED);
}

// eof WSNVisualizer.c
