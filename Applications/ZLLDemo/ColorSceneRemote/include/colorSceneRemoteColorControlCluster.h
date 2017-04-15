/**************************************************************************//**
  \file colorSceneRemoteColorControlCluster.h

  \brief
    Color Scene Remote device Color Control cluster interface.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    28.06.11 A. Taradov - Created.
******************************************************************************/
#ifndef _COLORSCENEREMOTECOLORCONTROLCLUSTER_H
#define _COLORSCENEREMOTECOLORCONTROLCLUSTER_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zclZllColorControlCluster.h>

/******************************************************************************
                    Externals
******************************************************************************/
extern ZCL_ColorControlClusterCommands_t colorControlClusterCommands;

/******************************************************************************
                    Prototypes
******************************************************************************/
/**************************************************************************//**
\brief Initialize Color Control cluster.
******************************************************************************/
void colorControlClusterInit(void);

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
                                                       uint16_t time);

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
                                                       uint16_t time);

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
                                                     uint16_t minTemp, uint16_t maxTemp);

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
                                                     Endpoint_t ep, uint8_t stepMode, uint16_t step,
                                                     uint16_t time, uint16_t minTemp, uint16_t maxTemp);

#if APP_ENABLE_CERTIFICATION_EXTENSION == 0
#else // APP_ENABLE_CERTIFICATION_EXTENSION == 1

/**************************************************************************//**
\brief Sends Move To Hue command

\param[in] hue - hue;
\param[in] direction - direction;
\param[in] transitionTime - transition time
******************************************************************************/
void colorSceneRemoteSendMoveToHueCommand(uint8_t hue, uint8_t direction, uint16_t transitionTime);

/**************************************************************************//**
\brief Sends Move Hue command

\param[in] mode - mode;
\param[in] rate - rate;
******************************************************************************/
void colorSceneRemoteSendMoveHueCommand(uint8_t mode, uint8_t rate);

/**************************************************************************//**
\brief Sends Step Hue command

\param[in] mode - step mode;
\param[in] size - step size;
\param[in] transitionTime - transition time
******************************************************************************/
void colorSceneRemoteSendStepHueCommand(uint8_t mode, uint8_t size, uint16_t transitionTime);

/**************************************************************************//**
\brief Sends Move To Saturation command

\param[in] saturation - saturation;
\param[in] transitionTime - transition time
******************************************************************************/
void colorSceneRemoteSendMoveToSaturationCommand(uint8_t saturation, uint16_t transitionTime);

/**************************************************************************//**
\brief Sends Move Saturation command

\param[in] mode - move mode;
\param[in] rate - rate
******************************************************************************/
void colorSceneRemoteSendMoveSaturationCommand(uint8_t mode, uint8_t rate);

/**************************************************************************//**
\brief Sends Step Saturation command

\param[in] mode - step mode;
\param[in] stepSize - step size;
\param[in] transitionTime - transition time
******************************************************************************/
void colorSceneRemoteSendStepSaturationCommand(uint8_t mode, uint8_t stepSize, uint16_t transitionTime);

/**************************************************************************//**
\brief Sends Move To Hue and Saturation command

\param[in] hue - hue;
\param[in] saturation - saturation;
\param[in] transitionTime - transition time
******************************************************************************/
void colorSceneRemoteSendMoveToHueAndSaturationCommandCert(uint8_t hue, uint8_t saturation, uint16_t transitionTime);

/**************************************************************************//**
\brief Sends Move To Color command

\param[in] colorX - value of X color channel;
\param[in] colorY - value of Y color channel;
\param[in] transitionTime - transition time
******************************************************************************/
void colorSceneRemoteSendMoveToColorCommand(uint16_t colorX, uint16_t colorY, uint16_t transitionTime);

/**************************************************************************//**
\brief Sends Move Color command

\param[in] rateX - rate for X color channel;
\param[in] rateY - rate for Y color channel;
******************************************************************************/
void colorSceneRemoteSendMoveColorCommand(int16_t rateX, int16_t rateY);

/**************************************************************************//**
\brief Sends Step Color command

\param[in] stepX - step for X color channel;
\param[in] stepY - step for Y color channel;
******************************************************************************/
void colorSceneRemoteSendStepColorCommand(int16_t stepX, int16_t stepY, uint16_t transitionTime);

/**************************************************************************//**
\brief Sends Enhanced Move To Hue command

\param[in] hue - hue;
\param[in] direction - direction;
\param[in] transitionTime - transition time
******************************************************************************/
void colorSceneRemoteSendEnhancedMoveToHueCommand(uint16_t enhancedHue, uint8_t direction, uint16_t transitionTime);

/**************************************************************************//**
\brief Sends Enhanced Move Hue command

\param[in] mode - move mode;
\param[in] rate - rate
******************************************************************************/
void colorSceneRemoteSendEnhancedMoveHueCommand(uint8_t mode, uint16_t enhancedRate);

/**************************************************************************//**
\brief Sends Enhanced Step Hue command

\param[in] mode - step mode;
\param[in] stepSize - step size;
\param[in] transitionTime - transition time
******************************************************************************/
void colorSceneRemoteSendEnhancedStepHueCommand(uint8_t mode, uint16_t enhancedStepSize, uint16_t transitionTime);

/**************************************************************************//**
\brief Sends Enhanced Move To Hue and Saturation command

\param[in] hue - hue;
\param[in] saturation - saturation;
\param[in] transitionTime - transition time
******************************************************************************/
void colorSceneRemoteSendEnhancedMoveToHueAndSaturationCommand(uint16_t hue, uint8_t saturation, uint16_t transitionTime);

/**************************************************************************//**
\brief Sends Move Step Hue command
******************************************************************************/
void colorSceneRemoteSendMoveStepHueCommand(void);

/**************************************************************************//**
\brief Sends Move To Color Temperature command

\param[in] colorTemperature - color temperature;
\param[in] transitionTime - tramsition time;
******************************************************************************/
void colorSceneRemoteSendMoveToColorTemperatureCommandCert(uint16_t colorTemperature, uint16_t transitionTime);

/**************************************************************************//**
\brief Sends Move Color Temperature command

\param[in] moveMode - move mode;
\param[in] rate - tramsition rate;
\param[in] colorTemperatureMinimum - minimum color temperature;
\param[in] colorTemperatureMaximum - maximum color temperature;
******************************************************************************/
void colorSceneRemoteSendMoveColorTemperatureCommandCert(uint8_t mode, uint16_t rate,
                                                     uint16_t colorTemperatureMinimum, uint16_t colorTemperatureMaximum);

/**************************************************************************//**
\brief Sends Step Color Temperature command

\param[in] mode - step mode;
\param[in] size - step size;
\param[in] transitionTime - tramsition time;
\param[in] colorTemperatureMinimum - minimum color temperature;
\param[in] colorTemperatureMaximum - maximum color temperature;
******************************************************************************/
void colorSceneRemoteSendStepColorTemperatureCommandCert(uint8_t mode, uint16_t size, uint16_t transitionTime,
                                                     uint16_t colorTemperatureMinimum, uint16_t colorTemperatureMaximum);

/**************************************************************************//**
\brief Sends Color loop set command

\param[in] flags - update flags;
\param[in] action - color loop action;
\param[in] direction - color loop direction;
\param[in] time - transition time;
\param[in] startHue - initial hue value;
******************************************************************************/
void colorSceneRemoteSendColorLoopSetCommand(uint8_t flags, uint8_t action, uint8_t direction,
                                             uint16_t time, uint16_t startHue);

/**************************************************************************//**
\brief Sends read Color Control Cluster attribute command

\param[in] attributeId - attribute of interest identifier
******************************************************************************/
void colorControlSendReadAttribute(uint16_t attributeId);

/**************************************************************************//**
\brief Sends Color Control Cluster write attribute command

\param[in] attributeId - attribute of interest identifier
******************************************************************************/
void colorControlSendWriteAttribute(uint16_t attributeId, void *value, uint8_t type);
#endif // APP_ENABLE_CERTIFICATION_EXTENSION


#endif // _COLORSCENEREMOTECOLORCONTROLCLUSTER_H

// eof colorSceneRemoteColorControlCluster.h
