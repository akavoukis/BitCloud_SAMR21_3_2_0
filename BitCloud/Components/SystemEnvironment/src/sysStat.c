/**************************************************************************//**
\file  sysStat.c

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
#ifdef _REPORT_STATS_

/******************************************************************************
                   Includes section
******************************************************************************/
#include <sysQueue.h>
#include <sysStat.h>

/******************************************************************************
                    Static functions prototypes section
******************************************************************************/
#if defined(ATMEGA1281) || defined(ATMEGA2561) || defined(ATMEGA1284) || defined(AT90USB1287) || defined(ATMEGA128RFA1) \
 || defined(ATMEGA256RFR2)
static inline uint16_t probeStack(const volatile uint8_t *start, const volatile uint8_t *end);
static uint8_t measureStack(uint8_t *buf, uint8_t maxSize);
#endif

/******************************************************************************
                    Static variables section
******************************************************************************/
#if defined(ATMEGA1281) || defined(ATMEGA2561) || defined(ATMEGA1284) || defined(AT90USB1287) || defined(ATMEGA128RFA1) \
 || defined(ATMEGA256RFR2)
// Create queue with one preincluded generator for AVR platforms
static SYS_StatGenerator_t stackStatGenerator = {.gen = measureStack, .next = NULL};
static QueueDescriptor_t statGenerators = {.head = (QueueElement_t*) &stackStatGenerator};
#else
// Create empty queue otherwise
static DECLARE_QUEUE(statGenerators);
#endif

/******************************************************************************
                    Implementation section
******************************************************************************/

/**************************************************************************//**
\brief Register new generator of stat data

\param[in] gen - generator
******************************************************************************/
void SYS_RegisterStatGenerator(SYS_StatGenerator_t *gen)
{
  putQueueElem(&statGenerators, gen);
}

/**************************************************************************//**
\brief Collect stats from registered generators into the supplied buffer

\param[out] buf - buffer to place stat report
\param[in] maxSize - size limit of buffer
\return number of actually placed bytes
******************************************************************************/
uint8_t SYS_GenerateStatReport(uint8_t *buf, uint8_t maxSize)
{
  const SYS_StatGenerator_t *gen;
  uint8_t *p = buf;

  // Assume generators are polite and won't make maxSize negative
  for (gen = getQueueElem(&statGenerators); gen && maxSize; gen = getNextQueueElem(gen))
  {
    uint8_t size = gen->gen(p, maxSize);
    maxSize -= size;
    p += size;
  }
  return p - buf;
}


#if defined(ATMEGA1281) || defined(ATMEGA2561) || defined(ATMEGA1284) || defined(AT90USB1287) || defined(ATMEGA128RFA1) \
 || defined(ATMEGA256RFR2)
// Preincluded generator for reporting stack usage. Only classic AVRs are supported for now

/**************************************************************************//**
\brief Measure stack usage by searching for first overwritten byte of
       default fill pattern

\param[in] start - start of section
\param[in] end - end of section (address of byte after the last one)
\return number of used bytes
******************************************************************************/
static inline uint16_t probeStack(const volatile uint8_t *start, const volatile uint8_t *end)
{
  while (start < end && *start == 0xCD)
    start++;
  return end - start;
}

/**************************************************************************//**
\brief Stat generator for reporting stacks usage

\param[out] buf - output buffer
\param[in] maxSize - buffer size limit
\return number of bytes actually written
******************************************************************************/
#if defined(__ICCAVR__)
static uint8_t measureStack(uint8_t *buf, uint8_t maxSize)
{
  #pragma section = "CSTACK"
  #pragma section = "RSTACK"
  uint16_t used;

  if (maxSize < 2)
    return 0;

  used = probeStack(__segment_begin("CSTACK"), __segment_end("CSTACK"));
  memcpy(buf, &used, 2);

  if (maxSize < 4)
    return 2;

  used = probeStack(__segment_begin("RSTACK"), __segment_end("RSTACK"));
  memcpy(buf + 2, &used, 2);

  return 4;
}
#elif defined(__GNUC__)
static uint8_t measureStack(uint8_t *buf, uint8_t maxSize)
{
  extern uint16_t __stack_start;
  extern uint16_t __stack;
  uint16_t used;

  if (maxSize < 2)
    return 0;

  used = probeStack((volatile uint8_t *)&__stack_start, ((volatile uint8_t *)&__stack) + 1);
  memcpy(buf, &used, 2);

  return 2;
}
#endif
#endif

#endif // _REPORT_STATS_
// eof sysStat.c
