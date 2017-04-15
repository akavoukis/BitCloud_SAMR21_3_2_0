/**************************************************************************//**
  \file bridgeColorControlCluster.c

  \brief
    Control Bridge device Color Control cluster implementation.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    22.01.13 N. Fomin - Created.
******************************************************************************/

#if APP_ZLL_DEVICE_TYPE == APP_DEVICE_TYPE_BRIDGE

/******************************************************************************
                    Includes
******************************************************************************/
#include <zcl.h>
#include <clusters.h>
#include <commandManager.h>
#include <zclZllColorControlCluster.h>
#include <bridgeColorControlCluster.h>
#include <bridgeClusters.h>

/******************************************************************************
                    Global variables
******************************************************************************/
ZCL_ColorControlClusterCommands_t colorControlClusterCommands =
{
  ZCL_COLOR_CONTROL_CLUSTER_COMMANDS_FOR_COLOR_REMOTE()
};

/******************************************************************************
                    Local variables
******************************************************************************/

/******************************************************************************
                    Prototypes
******************************************************************************/
static void bridgeFillMoveToHueAndSaturationPayload(ZCL_ZllMoveToHueAndSaturationCommand_t *payload,
                                                    uint8_t hue, uint8_t saturation, uint16_t time);
static void bridgeFillStepSaturationPayload(ZCL_ZllStepSaturationCommand_t *payload,
                                            uint8_t mode, uint8_t size, uint16_t time);

/******************************************************************************
                    Implementations
******************************************************************************/
/**************************************************************************//**
\brief Sends Move To Hue And Saturation command

\param[in] mode       - address mode;
\param[in] addr       - short address of destination node or number of group;
\param[in] ep         - endpoint number of destination device
\param[in] hue        - hue;
\param[in] saturation - saturation;
\param[in] time       - transition time
******************************************************************************/
void bridgeSendMoveToHueAndSaturationCommand(APS_AddrMode_t mode, ShortAddr_t addr,
                                             Endpoint_t ep, uint8_t hue, uint8_t saturation,
                                             uint16_t time)
{
  CommandDescriptor_t *cmd;
  ZCL_Addressing_t addressing;

  if (!(cmd = bridgeGetFreeCommand()))
    return;

  bridgeFillCommandRequest(cmd, MOVE_TO_HUE_AND_SATURATION_COMMAND_ID,
                                     COLOR_CONTROL_CLUSTER_ID, sizeof(cmd->payload.moveToHueAndSaturation));
  bridgeFillMoveToHueAndSaturationPayload(&cmd->payload.moveToHueAndSaturation, hue, saturation, time);
  bridgeFillDstAddressing(&addressing, mode, addr, ep);

  clustersSendCommandWithAddressing(cmd, &addressing);
}

/**************************************************************************//**
\brief Sends Step Saturation command

\param[in] addrMode - address mode;
\param[in] addr     - short address of destination node or number of group;
\param[in] ep       - endpoint number of destination device;
\param[in] mode     - step mode;
\param[in] size     - step size;
\param[in] time     - transition time
******************************************************************************/
void bridgeSendStepSaturationCommand(APS_AddrMode_t addrMode, ShortAddr_t addr, Endpoint_t ep, uint8_t mode, uint8_t size, uint16_t time)
{
  CommandDescriptor_t *cmd;
  ZCL_Addressing_t addressing;

  if (!(cmd = bridgeGetFreeCommand()))
    return;

  bridgeFillCommandRequest(cmd, STEP_SATURATION_COMMAND_ID,
                                     COLOR_CONTROL_CLUSTER_ID, sizeof(cmd->payload.stepSaturation));
  bridgeFillStepSaturationPayload(&cmd->payload.stepSaturation, mode, size, time);
  bridgeFillDstAddressing(&addressing, addrMode, addr, ep);

  clustersSendCommandWithAddressing(cmd, &addressing);
}

/**************************************************************************//**
\brief Fills Move To Hue And Saturation command structure

\param[out] payload    - pointer to command structure;
\param[in]  hue        - hue;
\param[in]  saturation - saturation;
\param[in]  time       - transition time
******************************************************************************/
static void bridgeFillMoveToHueAndSaturationPayload(ZCL_ZllMoveToHueAndSaturationCommand_t *payload,
                                                    uint8_t hue, uint8_t saturation, uint16_t time)
{
  payload->saturation     = saturation;
  payload->hue            = hue;
  payload->transitionTime = time;
}

/**************************************************************************//**
\brief Fills Step Saturation command structure

\param[out] payload    - pointer to command structure;
\param[in] mode     - step mode;
\param[in] size     - step size;
\param[in] time     - transition time
******************************************************************************/
static void bridgeFillStepSaturationPayload(ZCL_ZllStepSaturationCommand_t *payload,
                                                      uint8_t mode, uint8_t size, uint16_t time)
{
  payload->stepMode       = mode;
  payload->stepSize       = size;
  payload->transitionTime = time;
}

#endif // APP_ZLL_DEVICE_TYPE == APP_DEVICE_TYPE_BRIDGE

// eof bridgeColorControlCluster.c
