/***************************************************************************//**
  \file WSNCommand.h

  \brief Contains application command descriptions.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:
    15/03/12 D. Kolmakov - Created

  Last change:
    $Id: WSNCommand.h 27584 2015-01-09 14:45:42Z unithra.c $
*******************************************************************************/
#ifndef _WSNCOMMAND_H
#define _WSNCOMMAND_H

/*****************************************************************************
                              Includes section
******************************************************************************/
#include <macAddr.h>
#include <aps.h>

/*****************************************************************************
                              Defines section
******************************************************************************/
// Application command identifiers
#define APP_NETWORK_INFO_COMMAND_ID    0x01
#define APP_IDENTIFY_COMMAND_ID        0x10
#define APP_IDENTIFY_NOTF_COMMAND_ID   0x11

#if APP_USE_DEVICE_CAPTION == 1
#define APP_MAX_DEVICE_CAPTION_SIZE   16U
#define APP_DEVICE_CAPTION_SIZE       (sizeof(APP_DEVICE_CAPTION) - 1) /* Except End Of Line character */
#else
#define APP_MAX_DEVICE_CAPTION_SIZE   0U
#define APP_DEVICE_CAPTION_SIZE       0U
#endif /* APP_USE_DEVICE_CAPTION == 1 */

// Command descriptor construction macro
#define APP_COMMAND_DESCRIPTOR(ID, SERV_VECT) {.commandID = ID, .serviceVector = SERV_VECT}

/*****************************************************************************
                              Types section
******************************************************************************/
BEGIN_PACK

#if APP_USE_DEVICE_CAPTION == 1
typedef struct _AppDeviceCaption_t
{
  uint8_t fieldType;
  uint8_t size;
  char caption[APP_DEVICE_CAPTION_SIZE];
} PACK AppDeviceCaption_t;
#endif /* APP_USE_DEVICE_CAPTION == 1 */

typedef struct PACK _AppBoardInfo_t
{
  uint8_t     boardType;//1
  uint8_t     sensorsSize;//1
  struct
  {
    int32_t  battery;
    int32_t  temperature;
    int32_t  light;
  } meshbean;
} PACK AppBoardInfo_t;

/** Payload of network information command  */
typedef struct PACK _AppNwkInfoCmdPayload_t
{
  uint8_t        nodeType;
  ExtAddr_t      extAddr;
  ShortAddr_t    shortAddr;
  uint32_t       softVersion;
  uint32_t       channelMask;
  PanId_t        panID;
  Channel_t      workingChannel;
  ShortAddr_t    parentShortAddr;
  uint8_t        lqi;
  int8_t         rssi;
  AppBoardInfo_t boardInfo;
#if APP_USE_DEVICE_CAPTION == 1
  AppDeviceCaption_t deviceCaption;
#endif
} PACK AppNwkInfoCmdPayload_t;

/** Payload of identify command  */
typedef struct PACK _AppIdentifyReqPayload_t
{
  ExtAddr_t     dstAddress;
  uint16_t      blinkDurationMs;
  uint16_t      blinkPeriodMs;
} AppIdentifyReqPayload_t;

/** Payload of identify notification command */
typedef struct PACK _AppIdentifyNotfPayload_t
{
  uint8_t       status;
  ExtAddr_t     srcAddress;
} AppIdentifyNotfPayload_t;

typedef struct PACK _AppCommand_t
{
  uint8_t                    id;
  union
  {
    AppNwkInfoCmdPayload_t           nwkInfo;
    AppIdentifyReqPayload_t          identify;
    AppIdentifyNotfPayload_t         identifyNotf;
  } payload;
} PACK AppCommand_t;

/** Transmittion frame format */
typedef struct PACK _AppCommandFrame_t
{
  uint8_t      header[APS_ASDU_OFFSET];
  AppCommand_t command;
  uint8_t      footer[APS_AFFIX_LENGTH - APS_ASDU_OFFSET];
} PACK AppCommandFrame_t;

END_PACK

/**//**
  /brief Pointer to command handling function.
 */
typedef bool (*CommandServiceVector_t)(AppCommand_t *pCommand);

/**//**
  /brief Aplication command descriptor.
 */
typedef struct _AppCmdDescriptor_t
{
  uint8_t                  commandID;     //!< Command identificator
  CommandServiceVector_t   serviceVector; //!< Pointer to handling fuction
} AppCommandDescriptor_t;

#endif // _WSNCOMMAND_H
