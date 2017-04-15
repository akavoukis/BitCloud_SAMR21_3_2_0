/***************************************************************************//**
  \file WSNVisualizer.h

  \brief

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
******************************************************************************/
#ifndef _WSNVISUALIZER_H
#define _WSNVISUALIZER_H

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
int isVisualizerReadyToSleep(void);
void visualizeIdentity(void);

#endif//  _WSNVISUALIZER_H

// eof WSNVisualizer.h
