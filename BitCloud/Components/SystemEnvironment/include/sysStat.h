/**************************************************************************//**
\file  sysStat.h

\brief Collection of internal runtime data for report

\author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

\internal
  History:
    15/04/11 D. Loskutnikov - Created
*******************************************************************************/
#ifndef _SYS_STAT_H
#define _SYS_STAT_H

#ifdef _REPORT_STATS_
/******************************************************************************
                   Types section
******************************************************************************/
typedef struct _SYS_StatGenerator_t
{
  void *next;
  uint8_t (*gen)(uint8_t *buf, uint8_t maxSize);
} SYS_StatGenerator_t;

/******************************************************************************
                   Prototypes section
******************************************************************************/

/**************************************************************************//**
\brief Register new generator of stat data

\param[in] gen - generator
******************************************************************************/
extern void SYS_RegisterStatGenerator(SYS_StatGenerator_t *gen);

/**************************************************************************//**
\brief Collect stats from registered generators into the supplied buffer

\param[out] buf - buffer to place stat report
\param[in] maxSize - size limit of buffer
\return number of actually placed bytes
******************************************************************************/
extern uint8_t SYS_GenerateStatReport(uint8_t *buf, uint8_t maxSize);

#endif // _REPORT_STATS_

#endif // _SYS_STAT_H
// eof sysStat.h
