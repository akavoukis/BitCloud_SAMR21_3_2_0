/**********************************************************************//**
  \file halAppClock.cpp
  \brief

  \author

  \internal
  History:
    29/02/12 N. Fomin - Created
**************************************************************************/
/******************************************************************************
                   Includes section
******************************************************************************/
#include <halAppClock.h>
#include <halTaskManager.h>
#include <Windows.h>
#include <stdio.h>

/******************************************************************************
                     Global variables section
******************************************************************************/
uint8_t halAppTimeOvfw = 0;

/******************************************************************************
                     Local variables section
******************************************************************************/
static volatile uint8_t halAppIrqCount = 0;
static uint32_t halAppTime = 0ul;

/******************************************************************************
                   Prototypes section
******************************************************************************/
void CALLBACK sysTimerFired(UINT uID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2);

/******************************************************************************
                   Implementations section
******************************************************************************/
/**************************************************************************//**
\brief Configures, enables and starts timer
******************************************************************************/
void halStartAppClock(void)
{
  TIMECAPS timeCaps;
  if (TIMERR_NOERROR != timeGetDevCaps(&timeCaps, sizeof (TIMECAPS)))
  {
    fprintf(stderr, "Error occured while getting multimedia timer periods");
    exit(1);
  }
  if (TIMERR_NOERROR != timeBeginPeriod(timeCaps.wPeriodMin))
  {
    fprintf(stderr, "Error occured while setting multimedia timer minimum period");
    exit(1);
  }
  if (0 == timeSetEvent(HAL_APPTIMERINTERVAL, timeCaps.wPeriodMin, sysTimerFired, 0, TIME_PERIODIC))
  {
    fprintf(stderr, "Error occured while starting multimedia timers");
    exit(1);
  }
}

/**************************************************************************//**
\brief Returns time of timer

\return time in ms.
******************************************************************************/
uint32_t halGetTimeOfAppTimer(void)
{
  uint8_t tmpCounter;
  uint32_t tmpValue;

  ATOMIC_SECTION_ENTER
  tmpCounter = halAppIrqCount;
  halAppIrqCount = 0;
  ATOMIC_SECTION_LEAVE
  tmpValue = tmpCounter * HAL_APPTIMERINTERVAL;
  halAppTime += tmpValue;
  if (halAppTime < tmpValue)
    halAppTimeOvfw++;

  return halAppTime;
}

/**************************************************************************//**
\brief System timer has fired

uID - Timer ID, returned by timeSetEvent
uMsg - Reserved
lpTimeProc - Pointer to the callback function that we want to be called periodically
dwUser - User data passed to the callback function
dw1, dw2 - Reserved
\param[in] uID      - timer ID, returned by timeSetEvent;
\param[in] uMsg     - reserved;
\param[in] dwUser   - User data passed to the callback function;
\param[in] dw1, dw2 - reserved
******************************************************************************/
void CALLBACK sysTimerFired(UINT uID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2)
{
  (void)uID, (void)uMsg, (void)dwUser, (void)dw1, (void)dw2;

  halAppIrqCount++;
  halPostTask(HAL_APPTIMER);
}
//eof halAppClock.c
