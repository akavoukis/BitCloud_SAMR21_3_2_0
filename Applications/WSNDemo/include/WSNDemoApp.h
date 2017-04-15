/***************************************************************************//**
  \file WSNDemoApp.h

  \brief

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  Last change:
    $Id: WSNDemoApp.h 27584 2015-01-09 14:45:42Z unithra.c $
*******************************************************************************/
#ifndef _WSNDEMOAPP_H
#define _WSNDEMOAPP_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <configuration.h>
#include <macAddr.h>
#include <appFramework.h>
#include <configServer.h>
#include <appTimer.h>
#include <aps.h>
#include <zdo.h>
#include <dbg.h>
#include <leds.h>
#include <buttons.h>
#include <WSNSensorManager.h>
#include <WSNUARTManager.h>
#include <WSNCommand.h>

/******************************************************************************
                    Defines section
******************************************************************************/
#if APP_DEVICE_TYPE == DEV_TYPE_COORDINATOR && defined(_COORDINATOR_)
  #define WSN_DEMO_DEVICE_TYPE   DEVICE_TYPE_COORDINATOR
#elif APP_DEVICE_TYPE == DEV_TYPE_ROUTER && defined(_ROUTER_)
  #define WSN_DEMO_DEVICE_TYPE   DEVICE_TYPE_ROUTER
#elif APP_DEVICE_TYPE == DEV_TYPE_ENDDEVICE && defined(_ENDDEVICE_)
  #define WSN_DEMO_DEVICE_TYPE   DEVICE_TYPE_END_DEVICE
#else
  #error Chosen application device type does not correspond to the library type.
#endif

#define WSNDEMO_PROFILE_ID            1U
#define WSNDEMO_DEVICE_ID             1U
#define WSNDEMO_DEVICE_VERSION        1U
#define WSNDEMO_ENDPOINT              1U
#define MESHBEAN_SENSORS_TYPE         1U
#define DEVICE_CAPTION_FIELD_TYPE     32U

// Security parameters
#define LINK_KEY {0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa}

// Queues parameters
#define MAX_USART_MESSAGE_QUEUE_COUNT 1U
#define MAX_CMD_QUEUE_COUNT           4U
#define MAX_APP_MSG_QUEUE_COUNT       2U

#define APP_MAX_PAYLOAD               (sizeof(AppCommand_t) - APP_DEVICE_CAPTION_SIZE + APP_MAX_DEVICE_CAPTION_SIZE)

/* In worst case each byte will be transformed to two bytes + size of crc
 * + size of 4 bytes: 0x10, 0x02, 0x10, 0x03. */
#define MAX_RAW_APP_MESSAGE_SIZE  (2 + 2 * APP_MAX_PAYLOAD + 2 + 1)

#ifndef APP_TIMER_SENDING_PERIOD
#define APP_TIMER_SENDING_PERIOD         1000UL
#endif

// Assert codes
#define BSPRESDSENSORDATAASSERT_0  0xf001
#define BSPRESDSENSORDATAASSERT_1  0xf002
#define BSPRESDSENSORDATAASSERT_2  0xf003
#define BSPRESDSENSORDATAASSERT_3  0xf004
#define BSPRESDSENSORDATAASSERT_4  0xf005
#define BSPRESDSENSORDATAASSERT_5  0xf006
#define BSPRESDSENSORDATAASSERT_6  0xf007
#define BSPRESDSENSORDATAASSERT_7  0xf008
#define BSPRESDSENSORDATAASSERT_8  0xf009

#define CMDQUEUEINSERTASSERT_0     0xf020
#define TXQUEUEINSERTASSERT_0      0xf021


/*****************************************************************************
                               Types section
******************************************************************************/
typedef enum
{
  APP_INITING_STATE,
  APP_STARTING_NETWORK_STATE,
  APP_IN_NETWORK_STATE,
  APP_LEAVING_NETWORK_STATE,
  APP_STOP_STATE
} AppState_t;

typedef enum
{
  INITIAL_DEVICE_STATE,
  SENDING_DEVICE_STATE,
  READING_SENSORS_STATE,
  STARTING_TIMER_STATE,
} DeviceState_t;

typedef struct _SpecialDeviceInterface_t
{
  void (*appDeviceTaskHandler)(void);
  void (*appDeviceInitialization)(void);
  void (*appDeviceTaskReset)(void);
  const AppCommandDescriptor_t FLASH_PTR *appDeviceCmdDescTable;
  uint8_t appDeviceCmdDescTableSize;
} SpecialDeviceInterface_t;

/*****************************************************************************
                              Prototypes section
******************************************************************************/
/**************************************************************************//**
  \brief Posts application sub task.

  \param  None.

  \return None.
******************************************************************************/
void appPostSubTaskTask(void);

/**************************************************************************//**
  \brief Posts command handler task.

  \param  None.

  \return None.
******************************************************************************/
void appPostCmdHandlerTask(void);

/**************************************************************************//**
  \brief Posts message sender task.

  \param  None.

  \return None.
******************************************************************************/
void appPostMsgSenderTask(void);

/**************************************************************************//**
  \brief Initiate leave network procedure.

  \param  None.

  \return None.
******************************************************************************/
void appLeaveNetwork(void);

/**************************************************************************//**
  \brief New command received from PC event handler.

  \param[in] command - pointer to received command.
  \param[in] cmdSize - received command size.

  \return None.
******************************************************************************/
void appPcCmdReceived(void *command, uint8_t cmdSize);

/**************************************************************************//**
  \brief Starts blinking for identifying device.

  \param[in] blinkDuration - blinking duration.
  \param[in] blinkPeriod - blinking period.

  \return none
******************************************************************************/
void appStartIdentifyVisualization(uint16_t duration, uint16_t period);

/**************************************************************************//**
  \brief Reads LQI and RSSI for a parent node into appNwkInfo structure.

  \param  None.

  \return None.
******************************************************************************/
void appReadLqiRssi(void);

/**************************************************************************//**
  \brief Finds command descriptor in appCmdDescTable.

  \param[in, out] pCmdDesc - pointer to command descriptor
  \param[in] cmdId - command identificator.

  \return true if search has been successful, false otherwise.
******************************************************************************/
bool appGetCmdDescriptor(AppCommandDescriptor_t *pCmdDesc, uint8_t cmdId);


#endif /*_WSNDEMOAPP_H*/

// eof WSNDemoApp.h
