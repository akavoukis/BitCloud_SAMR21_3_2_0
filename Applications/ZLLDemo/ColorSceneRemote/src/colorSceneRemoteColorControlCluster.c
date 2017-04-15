/**************************************************************************//**
  \file colorSceneRemoteColorControlCluster.c

  \brief
    Color Scene Remote device Color Control cluster implementation.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    28.06.11 A. Taradov - Created.
******************************************************************************/

#if APP_ZLL_DEVICE_TYPE == APP_DEVICE_TYPE_COLOR_SCENE_REMOTE

/******************************************************************************
                    Includes
******************************************************************************/
#include <zcl.h>
#include <zclParser.h>
#include <clusters.h>
#include <commandManager.h>
#include <zclZllColorControlCluster.h>
#include <colorSceneRemoteColorControlCluster.h>
#include <colorSceneRemoteClusters.h>
#include <zllDemo.h>
#include <uartManager.h>

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
static void colorSceneRemoteFillMoveToHueAndSaturationPayload(ZCL_ZllMoveToHueAndSaturationCommand_t *payload,
                                                              uint8_t hue, uint8_t saturation, uint16_t time);
static void colorSceneRemoteFillMoveToColorTemperaturePayload(ZCL_ZllMoveToColorTemperatureCommand_t *payload,
                                                              uint16_t temp, uint16_t time);
static void colorSceneRemoteFillMoveColorTemperaturePayload(ZCL_ZllMoveColorTemperatureCommand_t *payload,
                                                            uint8_t mode, uint16_t rate, uint16_t minTemp,
                                                            uint16_t maxTemp);
static void colorSceneRemoteFillStepColorTemperaturePayload(ZCL_ZllStepColorTemperatureCommand_t *payload,
                                                            uint8_t mode, uint16_t rate, uint16_t time,
                                                            uint16_t minTemp, uint16_t maxTemp);
#if APP_ENABLE_CERTIFICATION_EXTENSION == 1
static void readAttributeResp(ZCL_Notify_t *ntfy);
#endif // APP_ENABLE_CERTIFICATION_EXTENSION == 1

/******************************************************************************
                    Implementations
******************************************************************************/
/**************************************************************************//**
\brief Initialize Color Control cluster.
******************************************************************************/
void colorControlClusterInit(void)
{
#if APP_ENABLE_CERTIFICATION_EXTENSION == 1
  ZCL_Cluster_t *colorControlCluster = ZCL_GetCluster(APP_ENDPOINT_COLOR_SCENE_REMOTE,
                                                  COLOR_CONTROL_CLUSTER_ID,
                                                  ZCL_CLUSTER_SIDE_CLIENT);

  colorControlCluster->ZCL_DefaultRespInd = commandManagerDefaultResponseHandler;
#endif // APP_ENABLE_CERTIFICATION_EXTENSION == 1
}

/**************************************************************************//**
\brief Sends Move To Hue And Saturation command

\param[in] mode       - address mode;
\param[in] addr       - short address of destination node or number of group;
\param[in] ep         - endpoint number of destination device
\param[in] hue        - hue;
\param[in] saturation - saturation;
\param[in] time       - transition time
******************************************************************************/
void colorSceneRemoteSendMoveToHueAndSaturationCommand(APS_AddrMode_t mode, ShortAddr_t addr,
                                                       Endpoint_t ep, uint8_t hue, uint8_t saturation,
                                                       uint16_t time)
{
  CommandDescriptor_t *cmd;
  ZCL_Addressing_t addressing;

  if (!(cmd = colorSceneRemoteGetFreeCommand()))
    return;

  colorSceneRemoteFillCommandRequest(cmd, MOVE_TO_HUE_AND_SATURATION_COMMAND_ID,
                                     COLOR_CONTROL_CLUSTER_ID, sizeof(cmd->payload.moveToHueAndSaturation));
  colorSceneRemoteFillMoveToHueAndSaturationPayload(&cmd->payload.moveToHueAndSaturation, hue, saturation, time);
  colorSceneRemoteFillDstAddressing(&addressing, mode, addr, ep);

  clustersSendCommandWithAddressing(cmd, &addressing);
}

/**************************************************************************//**
\brief Sends Move To Color Temperature command

\param[in] mode       - address mode;
\param[in] addr       - short address of destination node or number of group;
\param[in] ep         - endpoint number of destination device
\param[in] temp       - color temperature;
\param[in] time       - transition time
******************************************************************************/
void colorSceneRemoteSendMoveToColorTemperatureCommand(APS_AddrMode_t mode, ShortAddr_t addr,
                                                       Endpoint_t ep, uint16_t temp,
                                                       uint16_t time)
{
  CommandDescriptor_t *cmd;
  ZCL_Addressing_t addressing;

  if (!(cmd = colorSceneRemoteGetFreeCommand()))
    return;

  colorSceneRemoteFillCommandRequest(cmd, MOVE_TO_COLOR_TEMPERATURE_COMMAND_ID,
                                     COLOR_CONTROL_CLUSTER_ID, sizeof(cmd->payload.moveToColorTemperature));
  colorSceneRemoteFillMoveToColorTemperaturePayload(&cmd->payload.moveToColorTemperature, temp, time);
  colorSceneRemoteFillDstAddressing(&addressing, mode, addr, ep);

  clustersSendCommandWithAddressing(cmd, &addressing);
}

/**************************************************************************//**
\brief Sends Move Color Temperature command

\param[in] mode       - address mode;
\param[in] addr       - short address of destination node or number of group;
\param[in] ep         - endpoint number of destination device
\param[in] moveMode   - move mode;
\param[in] rate       - move rate;
\param[in] minTemp    - maximum temperature limit;
\param[in] maxTemp    - mimimum temperature limit
******************************************************************************/
void colorSceneRemoteSendMoveColorTemperatureCommand(APS_AddrMode_t mode, ShortAddr_t addr,
                                                     Endpoint_t ep, uint8_t moveMode, uint16_t rate,
                                                     uint16_t minTemp, uint16_t maxTemp)
{
  CommandDescriptor_t *cmd;
  ZCL_Addressing_t addressing;

  if (!(cmd = colorSceneRemoteGetFreeCommand()))
    return;

  colorSceneRemoteFillCommandRequest(cmd, MOVE_COLOR_TEMPERATURE_COMMAND_ID,
                                     COLOR_CONTROL_CLUSTER_ID, sizeof(cmd->payload.moveColorTemperature));
  colorSceneRemoteFillMoveColorTemperaturePayload(&cmd->payload.moveColorTemperature, moveMode, rate, minTemp, maxTemp);
  colorSceneRemoteFillDstAddressing(&addressing, mode, addr, ep);

  clustersSendCommandWithAddressing(cmd, &addressing);
}

/**************************************************************************//**
\brief Sends Step Color Temperature command

\param[in] mode       - address mode;
\param[in] addr       - short address of destination node or number of group;
\param[in] ep         - endpoint number of destination device
\param[in] stepMode   - step mode;
\param[in] step       - step size;
\param[in] time       - transition time;
\param[in] minTemp    - maximum temperature limit;
\param[in] maxTemp    - mimimum temperature limit
******************************************************************************/
void colorSceneRemoteSendStepColorTemperatureCommand(APS_AddrMode_t mode, ShortAddr_t addr,
                                                     Endpoint_t ep, uint8_t stepMode, uint16_t rate,
                                                     uint16_t time, uint16_t minTemp, uint16_t maxTemp)
{
  CommandDescriptor_t *cmd;
  ZCL_Addressing_t addressing;

  if (!(cmd = colorSceneRemoteGetFreeCommand()))
    return;

  colorSceneRemoteFillCommandRequest(cmd, STEP_COLOR_TEMPERATURE_COMMAND_ID,
                                     COLOR_CONTROL_CLUSTER_ID, sizeof(cmd->payload.stepColorTemperature));
  colorSceneRemoteFillStepColorTemperaturePayload(&cmd->payload.stepColorTemperature, stepMode, rate,
                                                  time, minTemp, maxTemp);
  colorSceneRemoteFillDstAddressing(&addressing, mode, addr, ep);

  clustersSendCommandWithAddressing(cmd, &addressing);
}

#if APP_ENABLE_CERTIFICATION_EXTENSION == 0
#else // APP_ENABLE_CERTIFICATION_EXTENSION == 1

/**************************************************************************//**
\brief Sends Move To Hue command

\param[in] hue - hue;
\param[in] direction - direction;
\param[in] transitionTime - transition time
******************************************************************************/
void colorSceneRemoteSendMoveToHueCommand(uint8_t hue, uint8_t direction, uint16_t transitionTime)
{
  CommandDescriptor_t *cmd;

  if (!(cmd = colorSceneRemoteGetFreeCommand()))
    return;

  colorSceneRemoteFillCommandRequest(cmd, MOVE_TO_HUE_COMMAND_ID,
                                     COLOR_CONTROL_CLUSTER_ID, sizeof(cmd->payload.moveToHue));
  cmd->payload.moveToHue.hue = hue;
  cmd->payload.moveToHue.direction = direction;
  cmd->payload.moveToHue.transitionTime = transitionTime;
  clustersSendCommand(cmd);
}

/**************************************************************************//**
\brief Sends Move Hue command

\param[in] mode - mode;
\param[in] rate - rate;
******************************************************************************/
void colorSceneRemoteSendMoveHueCommand(uint8_t mode, uint8_t rate)
{
  CommandDescriptor_t *cmd;

  if (!(cmd = colorSceneRemoteGetFreeCommand()))
    return;

  colorSceneRemoteFillCommandRequest(cmd, MOVE_HUE_COMMAND_ID,
                                     COLOR_CONTROL_CLUSTER_ID, sizeof(cmd->payload.moveHue));
  cmd->payload.moveHue.moveMode = mode;
  cmd->payload.moveHue.rate = rate;
  clustersSendCommand(cmd);
}

/**************************************************************************//**
\brief Sends Step Hue command

\param[in] mode - step mode;
\param[in] size - step size;
\param[in] transitionTime - transition time
******************************************************************************/
void colorSceneRemoteSendStepHueCommand(uint8_t mode, uint8_t size, uint16_t transitionTime)
{
  CommandDescriptor_t *cmd;

  if (!(cmd = colorSceneRemoteGetFreeCommand()))
    return;

  colorSceneRemoteFillCommandRequest(cmd, STEP_HUE_COMMAND_ID,
                                     COLOR_CONTROL_CLUSTER_ID, sizeof(cmd->payload.stepHue));
  cmd->payload.stepHue.stepMode = mode;
  cmd->payload.stepHue.stepSize = size;
  cmd->payload.stepHue.transitionTime = transitionTime;
  clustersSendCommand(cmd);
}

/**************************************************************************//**
\brief Sends Move To Saturation command

\param[in] saturation - saturation;
\param[in] transitionTime - transition time
******************************************************************************/
void colorSceneRemoteSendMoveToSaturationCommand(uint8_t saturation, uint16_t transitionTime)
{
  CommandDescriptor_t *cmd;

  if (!(cmd = colorSceneRemoteGetFreeCommand()))
    return;

  colorSceneRemoteFillCommandRequest(cmd, MOVE_TO_SATURATION_COMMAND_ID,
                                     COLOR_CONTROL_CLUSTER_ID, sizeof(cmd->payload.moveToSaturation));
  cmd->payload.moveToSaturation.saturation = saturation;
  cmd->payload.moveToSaturation.transitionTime = transitionTime;
  clustersSendCommand(cmd);
}

/**************************************************************************//**
\brief Sends Move Saturation command

\param[in] mode - move mode;
\param[in] rate - rate
******************************************************************************/
void colorSceneRemoteSendMoveSaturationCommand(uint8_t mode, uint8_t rate)
{
  CommandDescriptor_t *cmd;

  if (!(cmd = colorSceneRemoteGetFreeCommand()))
    return;

  colorSceneRemoteFillCommandRequest(cmd, MOVE_SATURATION_COMMAND_ID,
                                     COLOR_CONTROL_CLUSTER_ID, sizeof(cmd->payload.moveSaturation));
  cmd->payload.moveSaturation.moveMode = mode;
  cmd->payload.moveSaturation.rate = rate;
  clustersSendCommand(cmd);
}

/**************************************************************************//**
\brief Sends Step Saturation command

\param[in] mode - step mode;
\param[in] stepSize - step size;
\param[in] transitionTime - transition time
******************************************************************************/
void colorSceneRemoteSendStepSaturationCommand(uint8_t mode, uint8_t stepSize, uint16_t transitionTime)
{
  CommandDescriptor_t *cmd;

  if (!(cmd = colorSceneRemoteGetFreeCommand()))
    return;

  colorSceneRemoteFillCommandRequest(cmd, STEP_SATURATION_COMMAND_ID,
                                     COLOR_CONTROL_CLUSTER_ID, sizeof(cmd->payload.stepSaturation));
  cmd->payload.stepSaturation.stepMode = mode;
  cmd->payload.stepSaturation.stepSize = stepSize;
  cmd->payload.stepSaturation.transitionTime = transitionTime;
  clustersSendCommand(cmd);
}

/**************************************************************************//**
\brief Sends Move To Hue and Saturation command

\param[in] hue - hue;
\param[in] saturation - saturation;
\param[in] transitionTime - transition time
******************************************************************************/
void colorSceneRemoteSendMoveToHueAndSaturationCommandCert(uint8_t hue, uint8_t saturation, uint16_t transitionTime)
{
  CommandDescriptor_t *cmd;

  if (!(cmd = colorSceneRemoteGetFreeCommand()))
    return;

  colorSceneRemoteFillCommandRequest(cmd, MOVE_TO_HUE_AND_SATURATION_COMMAND_ID,
                                     COLOR_CONTROL_CLUSTER_ID, sizeof(cmd->payload.moveToHueAndSaturation));
  cmd->payload.moveToHueAndSaturation.hue = hue;
  cmd->payload.moveToHueAndSaturation.saturation = saturation;
  cmd->payload.moveToHueAndSaturation.transitionTime = transitionTime;
  clustersSendCommand(cmd);
}

/**************************************************************************//**
\brief Sends Move To Color command

\param[in] colorX - value of X color channel;
\param[in] colorY - value of Y color channel;
\param[in] transitionTime - transition time
******************************************************************************/
void colorSceneRemoteSendMoveToColorCommand(uint16_t colorX, uint16_t colorY, uint16_t transitionTime)
{
  CommandDescriptor_t *cmd;

  if (!(cmd = colorSceneRemoteGetFreeCommand()))
    return;

  colorSceneRemoteFillCommandRequest(cmd, MOVE_TO_COLOR_COMMAND_ID,
                                     COLOR_CONTROL_CLUSTER_ID, sizeof(cmd->payload.moveToColor));
  cmd->payload.moveToColor.colorX = colorX;
  cmd->payload.moveToColor.colorY = colorY;
  cmd->payload.moveToColor.transitionTime = transitionTime;
  clustersSendCommand(cmd);
}

/**************************************************************************//**
\brief Sends Move Color command

\param[in] rateX - rate for X color channel;
\param[in] rateY - rate for Y color channel;
******************************************************************************/
void colorSceneRemoteSendMoveColorCommand(int16_t rateX, int16_t rateY)
{
  CommandDescriptor_t *cmd;

  if (!(cmd = colorSceneRemoteGetFreeCommand()))
    return;

  colorSceneRemoteFillCommandRequest(cmd, MOVE_COLOR_COMMAND_ID,
                                     COLOR_CONTROL_CLUSTER_ID, sizeof(cmd->payload.moveColor));
  cmd->payload.moveColor.rateX = rateX;
  cmd->payload.moveColor.rateY = rateY;
  clustersSendCommand(cmd);
}

/**************************************************************************//**
\brief Sends Step Color command

\param[in] stepX - step for X color channel;
\param[in] stepY - step for Y color channel;
\param[in] transitionTime - transition time
******************************************************************************/
void colorSceneRemoteSendStepColorCommand(int16_t stepX, int16_t stepY, uint16_t transitionTime)
{
  CommandDescriptor_t *cmd;

  if (!(cmd = colorSceneRemoteGetFreeCommand()))
    return;

  colorSceneRemoteFillCommandRequest(cmd, STEP_COLOR_COMMAND_ID,
                                     COLOR_CONTROL_CLUSTER_ID, sizeof(cmd->payload.stepColor));
  cmd->payload.stepColor.stepX = stepX;
  cmd->payload.stepColor.stepY = stepY;
  cmd->payload.stepColor.transitionTime = transitionTime;
  clustersSendCommand(cmd);
}

/**************************************************************************//**
\brief Sends Enhanced Move To Hue command

\param[in] hue - hue;
\param[in] direction - direction;
\param[in] transitionTime - transition time
******************************************************************************/
void colorSceneRemoteSendEnhancedMoveToHueCommand(uint16_t enhancedHue, uint8_t direction, uint16_t transitionTime)
{
  CommandDescriptor_t *cmd;

  if (!(cmd = colorSceneRemoteGetFreeCommand()))
    return;

  colorSceneRemoteFillCommandRequest(cmd, ENHANCED_MOVE_TO_HUE_COMMAND_ID,
                                     COLOR_CONTROL_CLUSTER_ID, sizeof(cmd->payload.enhancedMoveToHue));
  cmd->payload.enhancedMoveToHue.enhancedHue = enhancedHue;
  cmd->payload.enhancedMoveToHue.direction = direction;
  cmd->payload.enhancedMoveToHue.transitionTime = transitionTime;
  clustersSendCommand(cmd);
}

/**************************************************************************//**
\brief Sends Enhanced Move Hue command

\param[in] mode - move mode;
\param[in] rate - rate
******************************************************************************/
void colorSceneRemoteSendEnhancedMoveHueCommand(uint8_t mode, uint16_t enhancedRate)
{
  CommandDescriptor_t *cmd;

  if (!(cmd = colorSceneRemoteGetFreeCommand()))
    return;

  colorSceneRemoteFillCommandRequest(cmd, ENHANCED_MOVE_HUE_COMMAND_ID,
                                     COLOR_CONTROL_CLUSTER_ID, sizeof(cmd->payload.enhancedMoveHue));
  cmd->payload.enhancedMoveHue.moveMode = mode;
  cmd->payload.enhancedMoveHue.rate = enhancedRate;
  clustersSendCommand(cmd);
}

/**************************************************************************//**
\brief Sends Enhanced Step Hue command

\param[in] mode - step mode;
\param[in] stepSize - step size;
\param[in] transitionTime - transition time
******************************************************************************/
void colorSceneRemoteSendEnhancedStepHueCommand(uint8_t mode, uint16_t enhancedStepSize, uint16_t transitionTime)
{
  CommandDescriptor_t *cmd;

  if (!(cmd = colorSceneRemoteGetFreeCommand()))
    return;

  colorSceneRemoteFillCommandRequest(cmd, ENHANCED_STEP_HUE_COMMAND_ID,
                                     COLOR_CONTROL_CLUSTER_ID, sizeof(cmd->payload.enhancedStepHue));
  cmd->payload.enhancedStepHue.stepMode = mode;
  cmd->payload.enhancedStepHue.stepSize = enhancedStepSize;
  cmd->payload.enhancedStepHue.transitionTime = transitionTime;
  clustersSendCommand(cmd);
}

/**************************************************************************//**
\brief Sends Enhanced Move To Hue and Saturation command

\param[in] enhancedHue - hue;
\param[in] saturation - saturation;
\param[in] transitionTime - transition time
******************************************************************************/
void colorSceneRemoteSendEnhancedMoveToHueAndSaturationCommand(uint16_t enhancedHue, uint8_t saturation, uint16_t transitionTime)
{
  CommandDescriptor_t *cmd;

  if (!(cmd = colorSceneRemoteGetFreeCommand()))
    return;

  colorSceneRemoteFillCommandRequest(cmd, ENHANCED_MOVE_TO_HUE_AND_SATURATION_COMMAND_ID,
                                     COLOR_CONTROL_CLUSTER_ID, sizeof(cmd->payload.enhancedMoveToHueAndSaturation));
  cmd->payload.enhancedMoveToHueAndSaturation.enhancedHue = enhancedHue;
  cmd->payload.enhancedMoveToHueAndSaturation.saturation = saturation;
  cmd->payload.enhancedMoveToHueAndSaturation.transitionTime = transitionTime;
  clustersSendCommand(cmd);
}

/**************************************************************************//**
\brief Sends Move Step Hue command
******************************************************************************/
void colorSceneRemoteSendMoveStepHueCommand(void)
{
  CommandDescriptor_t *cmd;

  if (!(cmd = colorSceneRemoteGetFreeCommand()))
    return;

  colorSceneRemoteFillCommandRequest(cmd, STOP_MOVE_STEP_COMMAND_ID,
                                     COLOR_CONTROL_CLUSTER_ID, 0);
  clustersSendCommand(cmd);
}

/**************************************************************************//**
\brief Sends Move To Color Temperature command

\param[in] colorTemperature - color temperature;
\param[in] transitionTime - tramsition time;
******************************************************************************/
void colorSceneRemoteSendMoveToColorTemperatureCommandCert(uint16_t colorTemperature, uint16_t transitionTime)
{
  CommandDescriptor_t *cmd;

  if (!(cmd = colorSceneRemoteGetFreeCommand()))
    return;

  colorSceneRemoteFillCommandRequest(cmd, MOVE_TO_COLOR_TEMPERATURE_COMMAND_ID,
                                     COLOR_CONTROL_CLUSTER_ID, sizeof(cmd->payload.moveToColorTemperature));
  cmd->payload.moveToColorTemperature.colorTemperature = colorTemperature;
  cmd->payload.moveToColorTemperature.transitionTime = transitionTime;
  clustersSendCommand(cmd);
}

/**************************************************************************//**
\brief Sends Move Color Temperature command

\param[in] moveMode - move mode;
\param[in] rate - tramsition rate;
\param[in] colorTemperatureMinimum - minimum color temperature;
\param[in] colorTemperatureMaximum - maximum color temperature;
******************************************************************************/
void colorSceneRemoteSendMoveColorTemperatureCommandCert(uint8_t mode, uint16_t rate,
                                                     uint16_t colorTemperatureMinimum, uint16_t colorTemperatureMaximum)
{
  CommandDescriptor_t *cmd;

  if (!(cmd = colorSceneRemoteGetFreeCommand()))
    return;

  colorSceneRemoteFillCommandRequest(cmd, MOVE_COLOR_TEMPERATURE_COMMAND_ID,
                                     COLOR_CONTROL_CLUSTER_ID, sizeof(cmd->payload.moveColorTemperature));
  cmd->payload.moveColorTemperature.moveMode = mode;
  cmd->payload.moveColorTemperature.rate = rate;
  cmd->payload.moveColorTemperature.colorTemperatureMinimum = colorTemperatureMinimum;
  cmd->payload.moveColorTemperature.colorTemperatureMaximum = colorTemperatureMaximum;
  clustersSendCommand(cmd);
}

/**************************************************************************//**
\brief Sends Step Color Temperature command

\param[in] mode - step mode;
\param[in] size - step size;
\param[in] transitionTime - tramsition time;
\param[in] colorTemperatureMinimum - minimum color temperature;
\param[in] colorTemperatureMaximum - maximum color temperature;
******************************************************************************/
void colorSceneRemoteSendStepColorTemperatureCommandCert(uint8_t mode, uint16_t size, uint16_t transitionTime,
                                                     uint16_t colorTemperatureMinimum, uint16_t colorTemperatureMaximum)
{
  CommandDescriptor_t *cmd;

  if (!(cmd = colorSceneRemoteGetFreeCommand()))
    return;

  colorSceneRemoteFillCommandRequest(cmd, STEP_COLOR_TEMPERATURE_COMMAND_ID,
                                     COLOR_CONTROL_CLUSTER_ID, sizeof(cmd->payload.stepColorTemperature));
  cmd->payload.stepColorTemperature.stepMode = mode;
  cmd->payload.stepColorTemperature.stepSize = size;
  cmd->payload.stepColorTemperature.transitionTime = transitionTime;
  cmd->payload.stepColorTemperature.colorTemperatureMinimum = colorTemperatureMinimum;
  cmd->payload.stepColorTemperature.colorTemperatureMaximum = colorTemperatureMaximum;
  clustersSendCommand(cmd);
}

/**************************************************************************//**
\brief Sends Color loop set command

\param[in] flags - update flags;
\param[in] action - color loop action;
\param[in] direction - color loop direction;
\param[in] time - transition time;
\param[in] startHue - initial hue value;
******************************************************************************/
void colorSceneRemoteSendColorLoopSetCommand(uint8_t flags, uint8_t action, uint8_t direction,
                                             uint16_t time, uint16_t startHue)
{
  CommandDescriptor_t *cmd;

  if (!(cmd = colorSceneRemoteGetFreeCommand()))
    return;

  colorSceneRemoteFillCommandRequest(cmd, COLOR_LOOP_SET_COMMAND_ID,
                                     COLOR_CONTROL_CLUSTER_ID, sizeof(cmd->payload.colorLoopSet));
  cmd->payload.colorLoopSet.updateFlags = flags;
  cmd->payload.colorLoopSet.action = action;
  cmd->payload.colorLoopSet.direction = direction;
  cmd->payload.colorLoopSet.time = time;
  cmd->payload.colorLoopSet.startHue = startHue;
  clustersSendCommand(cmd);
}

/**************************************************************************//**
\brief Sends read Color Control Cluster attribute command

\param[in] attributeId - attribute of interest identifier
******************************************************************************/
void colorControlSendReadAttribute(uint16_t attributeId)
{
  CommandDescriptor_t *cmd;

  if (!(cmd = clustersAllocCommand()))
    return;

  cmd->clusterId = COLOR_CONTROL_CLUSTER_ID;
  cmd->commandId = ZCL_READ_ATTRIBUTES_COMMAND_ID;
  cmd->payload.readAttribute.id = attributeId;
  cmd->size = sizeof(ZCL_ReadAttributeReq_t);
  cmd->isAttributeOperation = true;
  cmd->ZCL_Notify = readAttributeResp;
  clustersSendCommand(cmd);
}

/**************************************************************************//**
\brief Sends Color Control Cluster write attribute command

\param[in] attributeId - attribute of interest identifier
******************************************************************************/
void colorControlSendWriteAttribute(uint16_t attributeId, void *value, uint8_t type)
{
  CommandDescriptor_t *cmd;
  ZCL_DataTypeDescriptor_t attrDesc;

  if (!(cmd = clustersAllocCommand()))
    return;

  ZCL_GetDataTypeDescriptor(type, value, &attrDesc);

  cmd->clusterId = COLOR_CONTROL_CLUSTER_ID;
  cmd->commandId = ZCL_WRITE_ATTRIBUTES_COMMAND_ID;
  cmd->payload.writeAttribute.id = attributeId;
  cmd->payload.writeAttribute.type = type;
  memcpy(cmd->payload.writeAttribute.value, value, attrDesc.length);
  cmd->size = sizeof(uint16_t) + sizeof(uint8_t) + attrDesc.length;
  cmd->isAttributeOperation = true;
  clustersSendCommand(cmd);
}

/**************************************************************************//**
\brief ZCL command response
******************************************************************************/
static void readAttributeResp(ZCL_Notify_t *ntfy)
{
  if (ZCL_ZCL_RESPONSE_ID == ntfy->id && ZCL_SUCCESS_STATUS == ntfy->status)
  {
    ZCL_ReadAttributeResp_t *readAttrResp = (ZCL_ReadAttributeResp_t *)ntfy->responsePayload;
    ZCL_DataTypeDescriptor_t attrDesc;

    ZCL_GetDataTypeDescriptor(readAttrResp->type, readAttrResp->value, &attrDesc);

    if ((ZCL_DATA_TYPE_ANALOG_KIND == attrDesc.kind ||
         ZCL_DATA_TYPE_DISCRETE_KIND == attrDesc.kind) &&
        sizeof(uint32_t) >= attrDesc.length)
    {
      uint32_t value = 0;
      LOG_STRING(attrValueStr, "Attr 0x%04x = %u\r\n");

      memcpy(&value, readAttrResp->value, attrDesc.length);
      appSnprintf(attrValueStr, (unsigned)readAttrResp->id, (unsigned int)value);
    }
    else if (ZCL_CHARACTER_STRING_DATA_TYPE_ID == readAttrResp->type)
    {
      LOG_STRING(attrValueStr, "Attr 0x%04x = ");
      LOG_STRING(endStr, "\r\n");
      appSnprintf(attrValueStr, (unsigned)readAttrResp->id);
      appSnprintf((char *)readAttrResp->value);
      appSnprintf(endStr);
    }
  }
}

#endif // APP_ENABLE_CERTIFICATION_EXTENSION

/**************************************************************************//**
\brief Fills Move To Hue And Saturation command structure

\param[out] payload    - pointer to command structure;
\param[in]  hue        - hue;
\param[in]  saturation - saturation;
\param[in]  time       - transition time
******************************************************************************/
static void colorSceneRemoteFillMoveToHueAndSaturationPayload(ZCL_ZllMoveToHueAndSaturationCommand_t *payload,
                                                              uint8_t hue, uint8_t saturation, uint16_t time)
{
  payload->saturation     = saturation;
  payload->hue            = hue;
  payload->transitionTime = time;
}

/**************************************************************************//**
\brief Fills Move To Color Temperature command structure

\param[out] payload    - pointer to command structure;
\param[in]  temp       - temperature;
\param[in]  time       - transition time
******************************************************************************/
static void colorSceneRemoteFillMoveToColorTemperaturePayload(ZCL_ZllMoveToColorTemperatureCommand_t *payload,
                                                              uint16_t temp, uint16_t time)
{
  payload->colorTemperature = temp;
  payload->transitionTime   = time;
}

/**************************************************************************//**
\brief Fills Move To Color Temperature command structure

\param[out] payload   - pointer to command structure;
\param[in] mode       - move mode;
\param[in] rate       - move rate;
\param[in] minTemp    - maximum temperature limit;
\param[in] maxTemp    - mimimum temperature limit
******************************************************************************/
static void colorSceneRemoteFillMoveColorTemperaturePayload(ZCL_ZllMoveColorTemperatureCommand_t *payload,
                                                            uint8_t mode, uint16_t rate, uint16_t minTemp,
                                                            uint16_t maxTemp)
{
  payload->moveMode                = mode;
  payload->rate                    = rate;
  payload->colorTemperatureMinimum = minTemp;
  payload->colorTemperatureMaximum = maxTemp;
}

/**************************************************************************//**
\brief Fills Step Color Temperature command structure

\param[out] payload   - pointer to command structure;
\param[in] mode       - move mode;
\param[in] rate       - move rate;
\param[in] minTemp    - maximum temperature limit;
\param[in] maxTemp    - mimimum temperature limit
******************************************************************************/
static void colorSceneRemoteFillStepColorTemperaturePayload(ZCL_ZllStepColorTemperatureCommand_t *payload,
                                                            uint8_t mode, uint16_t step, uint16_t time,
                                                            uint16_t minTemp, uint16_t maxTemp)
{
  payload->stepMode                = mode;
  payload->stepSize                = step;
  payload->transitionTime          = time;
  payload->colorTemperatureMinimum = minTemp;
  payload->colorTemperatureMaximum = maxTemp;
}

#endif // APP_ZLL_DEVICE_TYPE == APP_DEVICE_TYPE_COLOR_SCENE_REMOTE

// eof colorSceneRemoteColorControlCluster.c
