/**************************************************************************//**
\file  halUsart.c

\brief Implementation of usart hardware-dependent module.

\author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

\internal
  History:
    06/08/12 N. Fomin - Created
*******************************************************************************/
/******************************************************************************
                   Includes section
******************************************************************************/
#include <windows.h>
#include <stdio.h>
#include <halUsart.h>
#include <appTimer.h>

/******************************************************************************
                   Types section
******************************************************************************/
typedef enum
{
  USART_WRITE_IDLE_STATE,
  USART_WRITE_IS_STARTED_STATE,
} UsartWriteState_t;
typedef enum
{
  USART_READ_IDLE_STATE,
  USART_READ_IS_STARTED_STATE,
} UsartReadState_t;

/******************************************************************************
                    Local variables
******************************************************************************/
static HANDLE hSerial;
static char comName[sizeof("\\\\.\\COM255")];
static OVERLAPPED writeOverlapped, readOverlapped;
static UsartWriteState_t usartWriteState = USART_WRITE_IDLE_STATE;
static UsartReadState_t  usartReadState  = USART_READ_IDLE_STATE;
static uint8_t rxBuffer[1000];

/******************************************************************************
                   Prototypes section
******************************************************************************/
void halPostUsartTask(HalUsartTaskId_t taskId);
static void halCheckWriteOperationCompletion(void);
static void halCheckForInputData(void);
void CALLBACK usartTimerFired(UINT uID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2);

/******************************************************************************
                   Implementations section
******************************************************************************/
/**************************************************************************//**
\brief Opens Usart interface

\param[in] baud     - usart's baud rate
\param[in] size     - amount of bits in a byte
\param[in] stopBits - amount of stopbits
\param[in] parity   - usart's parity
\param[in] channel  - usart's channel
******************************************************************************/
void halOpenUsart(UsartBaudRate_t baud, UsartData_t size, UsartStopBits_t stopBits, UsartParity_t parity, UsartChannel_t channel)
{
  DCB dcbSerialParams;
  COMMTIMEOUTS timeouts;
  TIMECAPS timeCaps;
  uint8_t comPort[3] = {0, 0, 0};
  int8_t i = 2;

  // converting COM port number to string
  while (channel)
  {
    comPort[i--] = channel % 10 + 0x30;
    channel /= 10;
  }
  // creating string like "\\\\.\\COM255" for WinAPI function 
  memcpy(comName, "\\\\.\\COM", sizeof("\\\\.\\COM"));
  memcpy(comName + sizeof("\\\\.\\COM") - 1, comPort + i + 1, sizeof(comPort) - i - 1);

  hSerial = CreateFile(comName,
                       GENERIC_READ | GENERIC_WRITE,
                       0,
                       0,
                       OPEN_EXISTING,
                       FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,
                       0);
  if (INVALID_HANDLE_VALUE == hSerial)
  {
    fprintf(stderr, "Failed to open serial port %s. Error %ld", comName, GetLastError());
    exit(1);
  }

  dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
  if (!GetCommState(hSerial, &dcbSerialParams))
  {
    fprintf(stderr, "Error ocurred while getting port parameters");
    exit(1);
  }
  dcbSerialParams.BaudRate = baud;
  dcbSerialParams.ByteSize = size;
  dcbSerialParams.StopBits = stopBits;
  dcbSerialParams.Parity   = parity;
  /* Added to support Xplained Pro boards */
  dcbSerialParams.fRtsControl = RTS_CONTROL_ENABLE;
  dcbSerialParams.fDtrControl = DTR_CONTROL_ENABLE;
  if (!SetCommState(hSerial, &dcbSerialParams))
  {
    fprintf(stderr, "Error occured while setting port parameters");
    exit(1);
  }
  timeouts.ReadIntervalTimeout         = MAXDWORD;
  timeouts.ReadTotalTimeoutConstant    = 0;
  timeouts.ReadTotalTimeoutMultiplier  = 0;
  timeouts.WriteTotalTimeoutConstant   = 50;
  timeouts.WriteTotalTimeoutMultiplier = 50;
  if (!SetCommTimeouts(hSerial, &timeouts))
  {
    fprintf(stderr, "Error occured while setting port timeouts");
    exit(1);
  }

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
  if (0 == timeSetEvent(10, timeCaps.wPeriodMin, usartTimerFired, 0, TIME_PERIODIC))
  {
    fprintf(stderr, "Error occured while starting multimedia timers");
    exit(1);
  }
}

/**************************************************************************//**
\brief Writes data to Usart interface

\param[in] buffer - pointer to buffer with data to be sent;
\param[in] length - amount of bytes in a buffer
******************************************************************************/
void halWriteUsartData(uint8_t *buffer, uint16_t length)
{
  DWORD bytesWritten;

  usartWriteState = USART_WRITE_IS_STARTED_STATE;
  if(!WriteFile(hSerial, buffer, length, &bytesWritten, &writeOverlapped))
  {
    if (ERROR_IO_PENDING != GetLastError())
    {
      fprintf(stderr,"Serial port writing error");
      exit(1);
    }
  }
  else
  {
    usartWriteState = USART_WRITE_IDLE_STATE;
    halPostUsartTask(HAL_USART_TASK_USART_TXC);
  }

  halCheckWriteOperationCompletion();
}

/**************************************************************************//**
\brief Usart timer has fired
******************************************************************************/
void CALLBACK usartTimerFired(UINT uID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2)
{
  (void)uID, (void)uMsg, (void)dwUser, (void)dw1, (void)dw2;

  halCheckForInputData();
  if (USART_WRITE_IS_STARTED_STATE == usartWriteState)
    halCheckWriteOperationCompletion();
}

/**************************************************************************//**
\brief Checks wheather asynchoronous write operation is complete
******************************************************************************/
static void halCheckWriteOperationCompletion(void)
{
  DWORD bytesWritten;

  if (!GetOverlappedResult(hSerial, &writeOverlapped, &bytesWritten, FALSE))
  {
    if (ERROR_IO_INCOMPLETE != GetLastError())
    {
      fprintf(stderr, "Serial port writing error");
      exit(1);
    }
  }
  else
  {
    usartWriteState = USART_WRITE_IDLE_STATE;
    halPostUsartTask(HAL_USART_TASK_USART_TXC);
  }
}

/**************************************************************************//**
\brief Checks if any data is received
******************************************************************************/
static void halCheckForInputData(void)
{
  DWORD bytesRead;
  if (USART_READ_IDLE_STATE == usartReadState)
  {
    usartReadState = USART_READ_IS_STARTED_STATE;
    if(!ReadFile(hSerial, rxBuffer, sizeof(rxBuffer), &bytesRead, &readOverlapped))
    {
      if (ERROR_IO_PENDING != GetLastError())
      {
        fprintf(stderr,"Serial port reading error");
        exit(1);
      }
    }
    else if (bytesRead)
    {
      usartReadState = USART_READ_IDLE_STATE;
      halPostUsartTask(HAL_USART_TASK_USART_RXC);
    }
    if (!GetOverlappedResult(hSerial, &readOverlapped, &bytesRead, FALSE))
    {
      if (ERROR_IO_INCOMPLETE != GetLastError())
      {
        fprintf(stderr, "Serial port reading error");
        exit(1);
      }
    }
    else if (bytesRead)
    {
      usartReadState = USART_READ_IDLE_STATE;
      halUsartRxBufferFiller(rxBuffer, bytesRead);
      halPostUsartTask(HAL_USART_TASK_USART_RXC);
   }
  }
  else if (USART_READ_IS_STARTED_STATE == usartReadState)
  {
    if (!GetOverlappedResult(hSerial, &readOverlapped, &bytesRead, FALSE))
    {
      if (ERROR_IO_INCOMPLETE != GetLastError())
      {
        fprintf(stderr, "Serial port reading error");
        exit(1);
      }
    }
    else if (bytesRead)
    {
      usartReadState = USART_READ_IDLE_STATE;
      halUsartRxBufferFiller(rxBuffer, bytesRead);
      halPostUsartTask(HAL_USART_TASK_USART_RXC);
    }
    else
      usartReadState = USART_READ_IDLE_STATE;
  }
}

// eof sleep.c
