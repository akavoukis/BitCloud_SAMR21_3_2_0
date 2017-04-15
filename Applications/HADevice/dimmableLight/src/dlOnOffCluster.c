/**************************************************************************//**
  \file dlOnOffCluster.c

  \brief
    Dimmable Light On/Off cluster implementation.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    10.12.12 N. Fomin - Created.
******************************************************************************/
#ifdef APP_DEVICE_TYPE_DIMMABLE_LIGHT

/******************************************************************************
                    Includes section
******************************************************************************/
#include <dlOnOffCluster.h>
#include <dlScenesCluster.h>
#include <uartManager.h>
#include <pdsDataServer.h>

/******************************************************************************
                    Prototypes section
******************************************************************************/
static ZCL_Status_t onInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload);
static ZCL_Status_t offInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload);
static ZCL_Status_t toggleInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload);

/******************************************************************************
                    Global variables section
******************************************************************************/
ZCL_OnOffClusterServerAttributes_t dlOnOffClusterServerAttributes =
{
  ZCL_DEFINE_ONOFF_CLUSTER_SERVER_ATTRIBUTES(ONOFF_VAL_MIN_REPORT_PERIOD, ONOFF_VAL_MAX_REPORT_PERIOD)
};
ZCL_OnOffClusterCommands_t         dlOnOffCommands =
{
  ZCL_DEFINE_ONOFF_CLUSTER_COMMANDS(onInd, offInd, toggleInd)
};

/******************************************************************************
                    Implementation section
******************************************************************************/
/**************************************************************************//**
\brief Initializes On/Off cluster
******************************************************************************/
void onOffClusterInit(void)
{
  dlOnOffClusterServerAttributes.onOff.value = false;
}

/**************************************************************************//**
\brief Sets on/off state
******************************************************************************/
void onOffSetOnOffState(bool state)
{
  bool previousOnOffValue = dlOnOffClusterServerAttributes.onOff.value;

  dlOnOffClusterServerAttributes.onOff.value = state;
  ZCL_ReportOnChangeIfNeeded(&dlOnOffClusterServerAttributes.onOff);
  if (previousOnOffValue != state)
  {
    scenesInvalidate();
    PDS_Store(APP_DL_ONOFF_MEM_ID);
  }
}

/**************************************************************************//**
\brief gets on/off state

\return on/off state
******************************************************************************/
bool onOffState(void)
{
  return dlOnOffClusterServerAttributes.onOff.value;
}

/**************************************************************************//**
\brief Callback on receiving On command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
ZCL_Status_t onInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload)
{
  LOG_STRING(onStr, "On\r\n");
  appSnprintf(onStr);

  onOffSetOnOffState(true);

  (void)addressing, (void)payloadLength, (void)payload;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receiving Off command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
ZCL_Status_t offInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload)
{
  LOG_STRING(offStr, "Off\r\n");
  appSnprintf(offStr);

  onOffSetOnOffState(false);

  (void)addressing, (void)payloadLength, (void)payload;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receiving Toggle command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
ZCL_Status_t toggleInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload)
{
  LOG_STRING(toggleStr, "Toggle\r\n");
  appSnprintf(toggleStr);

  onOffSetOnOffState(!dlOnOffClusterServerAttributes.onOff.value);

  (void)addressing, (void)payloadLength, (void)payload;
  return ZCL_SUCCESS_STATUS;
}

#endif // APP_DEVICE_TYPE_DIMMABLE_LIGHT

// eof dlOnOffCluster.c

