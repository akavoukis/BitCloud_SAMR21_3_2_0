/**************************************************************************//**
  \file lightColorControlCluster.c

  \brief
    Light device Color Control cluster implementation.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    28.06.11 A. Taradov - Created.
******************************************************************************/

#if APP_ZLL_DEVICE_TYPE >= APP_DEVICE_TYPE_COLOR_LIGHT

/******************************************************************************
                    Includes
******************************************************************************/
#ifdef BOARD_MEGARF
#include <buttonsExt.h>
#endif
#if defined(BOARD_MEGARF) || defined(BOARD_SAMR21)
#include <ledsExt.h>
#include <lcdExt.h>
#endif
#include <debug.h>
#include <zcl.h>
#include <zclZllColorControlCluster.h>
#include <lightScenesCluster.h>
#include <lightOnOffCluster.h>
#include <zllDemo.h>
#include <lightColorSchemesConversion.h>

#include <N_DeviceInfo_Bindings.h>
#include <N_DeviceInfo.h>
#include <pdsDataserver.h>

/******************************************************************************
                    Definitions
******************************************************************************/
#define UPDATE_TIMER_INTERVAL    100 // 1/10th of a second as per specification

#define MIN_HUE_LEVEL            0
#define MAX_HUE_LEVEL            0xfeff
#define MIN_SATURATION_LEVEL     0
#define MAX_SATURATION_LEVEL     0xfe
#define MIN_COLOR_LEVEL          0
#define MAX_COLOR_LEVEL          0xfeff

#define DEFAULT_SATURATION_LEVEL (MAX_SATURATION_LEVEL / 2)
#define DEFAULT_TRANSITION_TIME  2

#define HUE_SATURATION_SUPPORTED    (1 << 0)
#define ENHANCED_HUE_SUPPORTED      (1 << 1)
#define COLOR_LOOP_SUPPORTED        (1 << 2)
#define X_Y_ATTRIBUTES_SUPPORTED    (1 << 3)
#define COLOR_TEMPERATURE_SUPPORTED (1 << 4)

#define COLOR_LOOP_UPDATE_ACTION    (1 << 0)
#define COLOR_LOOP_UPDATE_DIRECTION (1 << 1)
#define COLOR_LOOP_UPDATE_TIME      (1 << 2)
#define COLOR_LOOP_UPDATE_START_HUE (1 << 3)

#define ABS(x)  ((x > 0) ? (x) : -(x))

#define ABSOLUTE_MAXIMUM_COLOR_TEMP  0xffff

/******************************************************************************
                    Types
******************************************************************************/
typedef enum _TransitionType_t
{
  NONE        = 0x00,
  ALL         = 0xff,
  HUE         = 0x01,
  SATURATION  = 0x02,
  COLOR       = 0x04,
  COLOR_LOOP  = 0x08,
  TEMPERATURE = 0x10,
} TransitionType_t;

/******************************************************************************
                    Prototypes
******************************************************************************/
#if APP_ZLL_DEVICE_TYPE != APP_DEVICE_TYPE_TEMPERATURE_COLOR_LIGHT
static ZCL_Status_t moveToHueInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ZllMoveToHueCommand_t *payload);
static ZCL_Status_t moveHueInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ZllMoveHueCommand_t *payload);
static ZCL_Status_t stepHueInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ZllStepHueCommand_t *payload);
static ZCL_Status_t moveToSaturationInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ZllMoveToSaturationCommand_t *payload);
static ZCL_Status_t moveSaturationInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ZllMoveSaturationCommand_t *payload);
static ZCL_Status_t stepSaturationInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ZllStepSaturationCommand_t *payload);
static ZCL_Status_t moveToHueAndSaturationInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ZllMoveToHueAndSaturationCommand_t *payload);
static ZCL_Status_t moveToColorInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ZllMoveToColorCommand_t *payload);
static ZCL_Status_t moveColorInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ZllMoveColorCommand_t *payload);
static ZCL_Status_t stepColorInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ZllStepColorCommand_t *payload);
static ZCL_Status_t enhancedMoveToHueInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ZllEnhancedMoveToHueCommand_t *payload);
static ZCL_Status_t enhancedMoveHueInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ZllEnhancedMoveHueCommand_t *payload);
static ZCL_Status_t enhancedStepHueInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ZllEnhancedStepHueCommand_t *payload);
static ZCL_Status_t enhancedMoveToHueAndSaturationInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ZllEnhancedMoveToHueAndSaturationCommand_t *payload);
static ZCL_Status_t colorLoopSetInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ZllColorLoopSetCommand_t *payload);
static ZCL_Status_t stopMoveStepInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, void *payload);
#endif // APP_ZLL_DEVICE_TYPE != APP_DEVICE_TYPE_TEMPERATURE_COLOR_LIGHT
#if APP_ZLL_DEVICE_TYPE >= APP_DEVICE_TYPE_EXTENDED_COLOR_LIGHT
static ZCL_Status_t moveToColorTemperatureInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ZllMoveToColorTemperatureCommand_t *payload);
static ZCL_Status_t moveColorTemperatureInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ZllMoveColorTemperatureCommand_t *payload);
static ZCL_Status_t stepColorTemperatureInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ZllStepColorTemperatureCommand_t *payload);
#endif // APP_ZLL_DEVICE_TYPE >= APP_DEVICE_TYPE_EXTENDED_COLOR_LIGHT

static void setColorMode(uint8_t mode);
static void setHue(uint16_t hue);
static void setSaturation(uint8_t saturation);
static void setColor(uint16_t x, uint16_t y);
static void setColorTemperature(uint16_t temperature);
static void handleColorLoopTransition(void);

static void displayStatus(void);
static void updateTransitionState(void);

static void transitionStart(TransitionType_t type);
static void transitionStop(TransitionType_t type);

#if APP_ZLL_DEVICE_TYPE != APP_DEVICE_TYPE_TEMPERATURE_COLOR_LIGHT
static void setColorLoop(uint8_t colorLoopActive, uint8_t colorLoopDirection, uint16_t colorLoopTime);
static void startColorLoop(ZCL_ZllColorLoopAction_t action);
static TransitionType_t prepareMoveToHue(uint16_t hue, uint8_t direction, uint16_t transitionTime,
                                         bool byStep);
static TransitionType_t prepareMoveToSaturation(uint8_t saturation, uint16_t transitionTime,
                                                bool byStep);
#endif // APP_ZLL_DEVICE_TYPE != APP_DEVICE_TYPE_TEMPERATURE_COLOR_LIGHT
#if APP_ZLL_DEVICE_TYPE >= APP_DEVICE_TYPE_EXTENDED_COLOR_LIGHT
static bool prepareMoveToColorTemperature(uint16_t temperature, uint16_t transitionTime, bool byStep);
static void handleColorTemperatureTransition(void);
static bool prepareMoveColorTemperature(uint8_t moveMode, uint16_t rate, uint16_t tempMin, uint16_t tempMax);
#endif // APP_ZLL_DEVICE_TYPE >= APP_DEVICE_TYPE_EXTENDED_COLOR_LIGHT

/******************************************************************************
                    Global variables
******************************************************************************/
ZCL_ColorControlClusterServerAttributes_t colorControlClusterServerAttributes =
{
  DEFINE_COLOR_CONTROL_CLUSTER_ATTRIBUTES()
};

ZCL_ColorControlClusterCommands_t colorControlClusterServerCommands =
{
#if APP_ZLL_DEVICE_TYPE == APP_DEVICE_TYPE_EXTENDED_COLOR_LIGHT
  ZCL_COLOR_CONTROL_CLUSTER_COMMANDS_FOR_EXTENDED_COLOR_LIGHT(moveToHueInd, moveHueInd, stepHueInd,
      moveToSaturationInd, moveSaturationInd, stepSaturationInd, moveToHueAndSaturationInd, moveToColorInd,
      moveColorInd, stepColorInd, moveToColorTemperatureInd, enhancedMoveToHueInd,
      enhancedMoveHueInd, enhancedStepHueInd, enhancedMoveToHueAndSaturationInd, colorLoopSetInd,
      stopMoveStepInd, moveColorTemperatureInd, stepColorTemperatureInd)
#elif APP_ZLL_DEVICE_TYPE == APP_DEVICE_TYPE_COLOR_LIGHT
  ZCL_COLOR_CONTROL_CLUSTER_COMMANDS_FOR_COLOR_LIGHT(moveToHueInd, moveHueInd, stepHueInd,
      moveToSaturationInd, moveSaturationInd, stepSaturationInd, moveToHueAndSaturationInd, moveToColorInd,
      moveColorInd, stepColorInd, enhancedMoveToHueInd, enhancedMoveHueInd, enhancedStepHueInd,
      enhancedMoveToHueAndSaturationInd, colorLoopSetInd, stopMoveStepInd)
#else
  ZCL_COLOR_CONTROL_CLUSTER_COMMANDS_FOR_TEMPERATURE_COLOR_LIGHT(moveToColorTemperatureInd,
    moveColorTemperatureInd, stepColorTemperatureInd)
#endif
};

/******************************************************************************
                    Local variables
******************************************************************************/
static HAL_AppTimer_t updateTimer;
#if APP_ZLL_DEVICE_TYPE != APP_DEVICE_TYPE_TEMPERATURE_COLOR_LIGHT
static uint8_t bckpSaturation;
static uint16_t bckpEnhacnedHue;
#endif // APP_ZLL_DEVICE_TYPE != APP_DEVICE_TYPE_TEMPERATURE_COLOR_LIGHT

static TransitionType_t inTransition = NONE;

static struct
{
  uint32_t delta;
  uint32_t current;
  uint16_t target;
  bool     direction;
  bool     byStep;
} hueTransition;

static struct
{
  uint32_t delta;
  uint32_t current;
  uint8_t  target;
  bool     direction;
  bool     byStep;
} saturationTransition;

static struct
{
  uint32_t deltaX;
  uint32_t deltaY;
  uint32_t currentX;
  uint32_t currentY;
  uint16_t targetX;
  uint16_t targetY;
  bool     directionX;
  bool     directionY;
} colorTransition;

static struct
{
  uint32_t delta;
  uint32_t current;
  uint16_t target;
  bool     direction;
  bool     byStep;
  uint16_t minTemp;
  uint16_t maxTemp;
} colorTemperatureTransition;

/******************************************************************************
                    Implementations section
******************************************************************************/

/**************************************************************************//**
\brief Initialize Color Control cluster.
******************************************************************************/
void colorControlClusterInit(void)
{
  if (!PDS_IsAbleToRestore(APP_LIGHT_COLOR_CONTROL_CLUSTER_SERVER_ATTR_MEM_ID))
  {
#if APP_ZLL_DEVICE_TYPE == APP_DEVICE_TYPE_TEMPERATURE_COLOR_LIGHT
    uint8_t colorCapabilities = 0;
#else
    uint8_t colorCapabilities = 1;
#endif // APP_ZLL_DEVICE_TYPE == APP_DEVICE_TYPE_TEMPERATURE_COLOR_LIGHT
    colorControlClusterServerAttributes.currentHue.value                 = ZCL_ZLL_CLUSTER_CURRENT_HUE_DEFAULT_VALUE;
    colorControlClusterServerAttributes.currentSaturation.value          = DEFAULT_SATURATION_LEVEL;
    colorControlClusterServerAttributes.remainingTime.value              = ZCL_ZLL_CLUSTER_REMAINING_TIME_DEFAULT_VALUE;
    colorControlClusterServerAttributes.currentX.value                   = ZCL_ZLL_CLUSTER_CURRENT_X_DEFAULT_VALUE;
    colorControlClusterServerAttributes.currentY.value                   = ZCL_ZLL_CLUSTER_CURRENT_Y_DEFAULT_VALUE;
    colorControlClusterServerAttributes.colorTemperature.value           = ZCL_ZCL_CLUSTER_COLOR_TEMP_DEFAULT_VALUE;
    colorControlClusterServerAttributes.colorMode.value                  = ZCL_ZLL_CLUSTER_COLOR_MODE_DEFAULT_VALUE;
    colorControlClusterServerAttributes.numberOfPrimaries.value          = 1;

    colorControlClusterServerAttributes.primary1X.value                  = 41942; // red
    colorControlClusterServerAttributes.primary1Y.value                  = 20971; // red
    colorControlClusterServerAttributes.primary1XIntensity.value         = 0;

    colorControlClusterServerAttributes.primary2X.value                  = 0;
    colorControlClusterServerAttributes.primary2Y.value                  = 0;
    colorControlClusterServerAttributes.primary2XIntensity.value         = 0;

    colorControlClusterServerAttributes.primary3X.value                  = 0;
    colorControlClusterServerAttributes.primary3Y.value                  = 0;
    colorControlClusterServerAttributes.primary3XIntensity.value         = 0;

    colorControlClusterServerAttributes.primary4X.value                  = 0;
    colorControlClusterServerAttributes.primary4Y.value                  = 0;
    colorControlClusterServerAttributes.primary4XIntensity.value         = 0;

    colorControlClusterServerAttributes.primary5X.value                  = 0;
    colorControlClusterServerAttributes.primary5Y.value                  = 0;
    colorControlClusterServerAttributes.primary5XIntensity.value         = 0;

    colorControlClusterServerAttributes.primary6X.value                  = 0;
    colorControlClusterServerAttributes.primary6Y.value                  = 0;
    colorControlClusterServerAttributes.primary6XIntensity.value         = 0;

    colorControlClusterServerAttributes.enhancedCurrentHue.value         = ZCL_ZCL_CLUSTER_ENHANCED_CURRENT_HUE_DEFAULT_VALUE;
    colorControlClusterServerAttributes.enhancedColorMode.value          = ZCL_ZCL_CLUSTER_ENHANCED_COLOR_MODE_DEFAULT_VALUE;
    colorControlClusterServerAttributes.colorLoopActive.value            = ZCL_ZCL_CLUSTER_COLOR_LOOP_ACTIVE_DEFAULT_VALUE;
    colorControlClusterServerAttributes.colorLoopDirection.value         = ZCL_ZCL_CLUSTER_COLOR_LOOP_DIRECTION_DEFAULT_VALUE;
    colorControlClusterServerAttributes.colorLoopTime.value              = ZCL_ZCL_CLUSTER_COLOR_LOOP_TIME_DEFAULT_VALUE;
    colorControlClusterServerAttributes.colorLoopStartEnhancedHue.value  = ZCL_ZCL_CLUSTER_COLOR_LOOP_START_ENHANCED_HUE_DEFAULT_VALUE;
    colorControlClusterServerAttributes.colorLoopStoredEnhancedHue.value = ZCL_ZCL_CLUSTER_COLOR_LOOP_STORED_ENHANCED_HUE_DEFAULT_VALUE;

    colorControlClusterServerAttributes.colorCapabilities.value.hueSaturationSupported = colorCapabilities;
    colorControlClusterServerAttributes.colorCapabilities.value.enhancedHueSupported   = colorCapabilities;
    colorControlClusterServerAttributes.colorCapabilities.value.colorLoopSupported     = colorCapabilities;
    colorControlClusterServerAttributes.colorCapabilities.value.XYAttributesSupported  = colorCapabilities;
#if APP_ZLL_DEVICE_TYPE >= APP_DEVICE_TYPE_EXTENDED_COLOR_LIGHT
    colorControlClusterServerAttributes.colorCapabilities.value.colorTemperatureSupported = 1;
#else
    colorControlClusterServerAttributes.colorCapabilities.value.colorTemperatureSupported = 0;
#endif // APP_ZLL_DEVICE_TYPE >= APP_DEVICE_TYPE_EXTENDED_COLOR_LIGHT

    colorControlClusterServerAttributes.colorTempPhysicalMin.value = ZCL_ZCL_CLUSTER_TEMP_PHYSICAL_MIN_DEFAULT_VALUE;
    colorControlClusterServerAttributes.colorTempPhysicalMax.value = ZCL_ZCL_CLUSTER_TEMP_PHYSICAL_MAX_DEFAULT_VALUE;
  }

  updateTimer.mode = TIMER_REPEAT_MODE;
  updateTimer.interval = UPDATE_TIMER_INTERVAL;
  updateTimer.callback = updateTransitionState;

  displayStatus();
}

/**************************************************************************//**
\brief Set Extension Field Set
******************************************************************************/
void colorControlClusterSetExtensionField(Scene_t *scene)
{
  setColorMode(scene->colorMode);
#if (APP_ZLL_DEVICE_TYPE == APP_DEVICE_TYPE_COLOR_LIGHT) || (APP_ZLL_DEVICE_TYPE == APP_DEVICE_TYPE_EXTENDED_COLOR_LIGHT)
  setHue(scene->enhancedCurrentHue);
  setSaturation(scene->currentSaturation);
  setColorLoop(scene->colorLoopActive, scene->colorLoopDirection, scene->colorLoopTime);
#endif // (APP_ZLL_DEVICE_TYPE == APP_DEVICE_TYPE_COLOR_LIGHT) || (APP_ZLL_DEVICE_TYPE == APP_DEVICE_TYPE_EXTENDED_COLOR_LIGHT)
  setColor(scene->currentX, scene->currentY);
#if APP_ZLL_DEVICE_TYPE >= APP_DEVICE_TYPE_EXTENDED_COLOR_LIGHT
  setColorTemperature(lightConvertXYToColor(scene->currentX, scene->currentY));
#endif // APP_ZLL_DEVICE_TYPE >= APP_DEVICE_TYPE_EXTENDED_COLOR_LIGHT
}

INLINE uint8_t levelControlCalculateIntensity(void)
{
  // Wrong in general..
  return colorControlClusterServerAttributes.currentSaturation.value == UINT8_MAX ?
         UINT8_MAX - 1 : colorControlClusterServerAttributes.currentSaturation.value;
  // Should be something like..
  //return (uint8_t) pow(10.0, ((currentLevel - 1) * 3 / 253 ) - 1);
}

/**************************************************************************//**
\brief Display current level status.
******************************************************************************/
static void displayStatus(void)
{
    // add information about color temperature
#if APP_ZLL_DEVICE_TYPE != APP_DEVICE_TYPE_TEMPERATURE_COLOR_LIGHT
  LCD_PRINT(0, 1, "%5u %5u %5u %3u",
            colorControlClusterServerAttributes.currentX.value,
            colorControlClusterServerAttributes.currentY.value,
            colorControlClusterServerAttributes.enhancedCurrentHue.value,
            colorControlClusterServerAttributes.currentSaturation.value
           );

  if (ZCL_ZLL_CURRENT_HUE_AND_CURRENT_SATURATION == colorControlClusterServerAttributes.colorMode.value)
    LEDS_SET_COLOR_HS(
      colorControlClusterServerAttributes.enhancedCurrentHue.value,
      colorControlClusterServerAttributes.currentSaturation.value
    );
  else
    LEDS_SET_COLOR_XY(
      colorControlClusterServerAttributes.currentX.value,
      colorControlClusterServerAttributes.currentY.value
    );
#else
  LCD_PRINT(0, 1, "%5u", colorControlClusterServerAttributes.colorTemperature.value);
#endif // APP_ZLL_DEVICE_TYPE != APP_DEVICE_TYPE_TEMPERATURE_COLOR_LIGHT
}

/**************************************************************************//**
\brief Set current mode
******************************************************************************/
static void setColorMode(uint8_t mode)
{
  colorControlClusterServerAttributes.enhancedColorMode.value  = mode;

  if (ZCL_ZLL_ENHANCED_CURRENT_HUE_AND_CURRENT_SATURATION == mode)
    colorControlClusterServerAttributes.colorMode.value = ZCL_ZLL_CURRENT_HUE_AND_CURRENT_SATURATION;
  else
    colorControlClusterServerAttributes.colorMode.value = mode;
}

/**************************************************************************//**
\brief Set hue value
******************************************************************************/
static void setHue(uint16_t hue)
{
  if (colorControlClusterServerAttributes.enhancedCurrentHue.value != hue)
  {
    colorControlClusterServerAttributes.enhancedCurrentHue.value = hue;
    colorControlClusterServerAttributes.currentHue.value = hue >> 8;
    scenesClusterInvalidate();
    displayStatus();
  }
}

/**************************************************************************//**
\brief Set saturation value
******************************************************************************/
static void setSaturation(uint8_t saturation)
{
  if (colorControlClusterServerAttributes.currentSaturation.value != saturation)
  {
    colorControlClusterServerAttributes.currentSaturation.value = saturation;
    scenesClusterInvalidate();
    displayStatus();
  }
}

/**************************************************************************//**
\brief Set color value
******************************************************************************/
static void setColor(uint16_t x, uint16_t y)
{
  if (colorControlClusterServerAttributes.currentX.value != x ||
      colorControlClusterServerAttributes.currentY.value != y)
  {
    colorControlClusterServerAttributes.currentX.value = x;
    colorControlClusterServerAttributes.currentY.value = y;
    colorControlClusterServerAttributes.primary1X.value = x;
    colorControlClusterServerAttributes.primary1Y.value = y;
    colorControlClusterServerAttributes.primary1XIntensity.value =
      levelControlCalculateIntensity();

    scenesClusterInvalidate();
    displayStatus();
  }
}

/**************************************************************************//**
\brief Set color temperature value
******************************************************************************/
static void setColorTemperature(uint16_t temperature)
{
  if (colorControlClusterServerAttributes.colorTemperature.value != temperature)
  {
    colorControlClusterServerAttributes.colorTemperature.value = temperature;
    scenesClusterInvalidate();
    displayStatus();
  }
}

#if APP_ZLL_DEVICE_TYPE != APP_DEVICE_TYPE_TEMPERATURE_COLOR_LIGHT
/**************************************************************************//**
\brief Set Color Loop values
******************************************************************************/
static void setColorLoop(uint8_t colorLoopActive, uint8_t colorLoopDirection, uint16_t colorLoopTime)
{
  colorControlClusterServerAttributes.colorLoopActive.value    = colorLoopActive;
  colorControlClusterServerAttributes.colorLoopDirection.value = colorLoopDirection;
  colorControlClusterServerAttributes.colorLoopTime.value      = colorLoopTime;

  if (colorLoopActive)
    startColorLoop(COLOR_LOOP_ACTIVATE_FROM_ECH);
}

/**************************************************************************//**
\brief Stop Color Loop handler.
******************************************************************************/
static void stopColorLoop(void)
{
  transitionStop(ALL);
  colorControlClusterServerAttributes.colorLoopActive.value = 0;
  setHue(colorControlClusterServerAttributes.colorLoopStoredEnhancedHue.value);
}

/**************************************************************************//**
\brief Starts the color loop specified way.

\param[in] action - color loop mode.
******************************************************************************/
static void startColorLoop(ZCL_ZllColorLoopAction_t action)
{
  colorControlClusterServerAttributes.colorLoopStoredEnhancedHue.value =
    colorControlClusterServerAttributes.enhancedCurrentHue.value;

  if (COLOR_LOOP_ACTIVATE_FROM_ECH == action)
    colorControlClusterServerAttributes.colorLoopStartEnhancedHue.value =
      colorControlClusterServerAttributes.enhancedCurrentHue.value;

  colorControlClusterServerAttributes.colorLoopActive.value = 1;

  colorControlClusterServerAttributes.remainingTime.value = 0xffff;
  setColorMode(ZCL_ZLL_ENHANCED_CURRENT_HUE_AND_CURRENT_SATURATION);
  transitionStart(COLOR_LOOP);
}
#endif // APP_ZLL_DEVICE_TYPE != APP_DEVICE_TYPE_TEMPERATURE_COLOR_LIGHT

/**************************************************************************//**
\brief Handle hue transition
******************************************************************************/
static void handleHueTransition(void)
{
  // Up transition
  if (hueTransition.direction)
    hueTransition.current += hueTransition.delta;
  // Down transition
  else
    hueTransition.current -= hueTransition.delta;
    setHue(hueTransition.current >> 16);
}

/**************************************************************************//**
\brief Handle saturation transition
******************************************************************************/
static void handleSaturationTransition(void)
{
  uint8_t saturation;
  bool finish = false;

  // Up transition
  if (saturationTransition.direction)
  {
    if (((uint32_t){MAX_SATURATION_LEVEL} << 16) - saturationTransition.delta < saturationTransition.current)
    {
      saturation = MAX_SATURATION_LEVEL;
      finish = true;
    }
    else
    {
      saturationTransition.current += saturationTransition.delta;
      saturation = saturationTransition.current >> 16;
    }
  }
  // Down transition
  else
  {
    if (saturationTransition.current - ((uint32_t){MIN_SATURATION_LEVEL} << 16) < saturationTransition.delta)
    {
      saturation = MIN_SATURATION_LEVEL;
      finish = true;
    }
    else
    {
      saturationTransition.current -= saturationTransition.delta;
      saturation = saturationTransition.current >> 16;
    }
  }

  setSaturation(saturation);

  if (finish)
    transitionStop(SATURATION);
}

/**************************************************************************//**
\brief Handle color transition
******************************************************************************/
static void handleColorTransition(void)
{
  uint16_t x, y;
  bool finishX = false;
  bool finishY = false;

  // X Up transition
  if (colorTransition.directionX)
  {
    if (((uint32_t){MAX_COLOR_LEVEL} << 16) - colorTransition.deltaX < colorTransition.currentX)
    {
      x = MAX_COLOR_LEVEL;
      finishX = true;
    }
    else
    {
      colorTransition.currentX += colorTransition.deltaX;
      x = colorTransition.currentX >> 16;
    }
  }
  // X Down transition
  else
  {
    if (colorTransition.currentX - ((uint32_t){MIN_COLOR_LEVEL} << 16) < colorTransition.deltaX)
    {
      x = MIN_COLOR_LEVEL;
      finishX = true;
    }
    else
    {
      colorTransition.currentX -= colorTransition.deltaX;
      x = colorTransition.currentX >> 16;
    }
  }

  // Y Up transition
  if (colorTransition.directionY)
  {
    if (((uint32_t){MAX_COLOR_LEVEL} << 16) - colorTransition.deltaY < colorTransition.currentY)
    {
      y = MAX_COLOR_LEVEL;
      finishY = true;
    }
    else
    {
      colorTransition.currentY += colorTransition.deltaY;
      y = colorTransition.currentY >> 16;
    }
  }
  // Y Down transition
  else
  {
    if (colorTransition.currentY - ((uint32_t){MIN_COLOR_LEVEL} << 16) < colorTransition.deltaY)
    {
      y = MIN_COLOR_LEVEL;
      finishY = true;
    }
    else
    {
      colorTransition.currentY -= colorTransition.deltaY;
      y = colorTransition.currentY >> 16;
    }
  }

  // Common
  setColor(x, y);

  if (finishX && finishY)
    transitionStop(COLOR);
}

/**************************************************************************//**
\brief Handle Color Loop transition
******************************************************************************/
static void handleColorLoopTransition(void)
{
  uint16_t delta = (MAX_HUE_LEVEL - MIN_HUE_LEVEL) /
                   (colorControlClusterServerAttributes.colorLoopTime.value * 10);
  int32_t enhancedHue = colorControlClusterServerAttributes.enhancedCurrentHue.value;

  // Up transition
  if (colorControlClusterServerAttributes.colorLoopDirection.value)
    enhancedHue += delta;
  // Down transition
  else
    enhancedHue -= delta;

  if (enhancedHue < MIN_HUE_LEVEL)
    enhancedHue = MAX_HUE_LEVEL;
  else if (MAX_HUE_LEVEL < enhancedHue)
    enhancedHue = MIN_HUE_LEVEL;

  setHue(enhancedHue);
}

/**************************************************************************//**
\brief Handle color temperature transition
******************************************************************************/
static void handleColorTemperatureTransition(void)
{
  uint16_t temp;
  bool finish = false;

  // Temperature Up transition
  if (colorTemperatureTransition.direction)
  {
    if (((uint32_t){colorTemperatureTransition.maxTemp} << 16) - colorTemperatureTransition.delta < colorTemperatureTransition.current)
    {
      temp = colorTemperatureTransition.maxTemp;
      finish = true;
    }
    else
    {
      colorTemperatureTransition.current += colorTemperatureTransition.delta;
      temp = colorTemperatureTransition.current >> 16;
    }
  }
  // Temperature Down transition
  else
  {
    if (colorTemperatureTransition.current - ((uint32_t){colorTemperatureTransition.minTemp} << 16) < colorTemperatureTransition.delta)
    {
      temp = colorTemperatureTransition.minTemp;
      finish = true;
    }
    else
    {
      colorTemperatureTransition.current -= colorTemperatureTransition.delta;
      temp = colorTemperatureTransition.current >> 16;
    }
  }

  // Common
  setColorTemperature(temp);

  if (finish)
    transitionStop(TEMPERATURE);
}

/**************************************************************************//**
\brief Show identify effect.

\param[in] enhancedHue - enhanced hue to move to.
******************************************************************************/
void colorControlShowIdentifyEffect(uint16_t enhancedHue)
{
#if APP_ZLL_DEVICE_TYPE != APP_DEVICE_TYPE_TEMPERATURE_COLOR_LIGHT
  uint8_t proceedWith;

  bckpSaturation = colorControlClusterServerAttributes.currentSaturation.value;
  bckpEnhacnedHue = colorControlClusterServerAttributes.enhancedCurrentHue.value;

  proceedWith = prepareMoveToHue(enhancedHue,
    ZCL_ZLL_MOVE_TO_HUE_DIRECTION_SHORTEST_DISTANCE, DEFAULT_TRANSITION_TIME, false);
  proceedWith |= prepareMoveToSaturation(DEFAULT_SATURATION_LEVEL,
    DEFAULT_TRANSITION_TIME, false);

  if (proceedWith)
  {
    setColorMode(ZCL_ZLL_ENHANCED_CURRENT_HUE_AND_CURRENT_SATURATION);
    transitionStart(proceedWith);
  }
#else
  (void)enhancedHue;
#endif // APP_ZLL_DEVICE_TYPE != APP_DEVICE_TYPE_TEMPERATURE_COLOR_LIGHT
}

/**************************************************************************//**
\brief Stop showing identify effect and return to previous state.
******************************************************************************/
void colorControlStopIdentifyEffect(void)
{
#if APP_ZLL_DEVICE_TYPE != APP_DEVICE_TYPE_TEMPERATURE_COLOR_LIGHT
  uint8_t proceedWith;

  proceedWith = prepareMoveToHue(bckpEnhacnedHue,
    ZCL_ZLL_MOVE_TO_HUE_DIRECTION_SHORTEST_DISTANCE, DEFAULT_TRANSITION_TIME, false);
  proceedWith |= prepareMoveToSaturation(bckpSaturation, DEFAULT_TRANSITION_TIME, false);

  if (proceedWith)
  {
    setColorMode(ZCL_ZLL_ENHANCED_CURRENT_HUE_AND_CURRENT_SATURATION);
    transitionStart(proceedWith);
  }
#endif // APP_ZLL_DEVICE_TYPE != APP_DEVICE_TYPE_TEMPERATURE_COLOR_LIGHT
}

/**************************************************************************//**
\brief Set target transition value
******************************************************************************/
static void setTargetValue()
{
  if (inTransition & HUE)
    setHue(hueTransition.target);

  if (inTransition & SATURATION)
    setSaturation(saturationTransition.target);

  if (inTransition & COLOR)
  {
    setColor(colorTransition.targetX, colorTransition.targetY);
#if APP_ZLL_DEVICE_TYPE >= APP_DEVICE_TYPE_EXTENDED_COLOR_LIGHT
    setColorTemperature(lightConvertXYToColor(colorTransition.targetX, colorTransition.targetY));
#endif // APP_ZLL_DEVICE_TYPE >= APP_DEVICE_TYPE_EXTENDED_COLOR_LIGHT
  }

  if (inTransition & TEMPERATURE)
  {
#if APP_ZLL_DEVICE_TYPE >= APP_DEVICE_TYPE_EXTENDED_COLOR_LIGHT
    uint16_t x, y;

    lightConvertColorToXY(colorTemperatureTransition.target, &x, &y);
    setColor(x, y);
#endif // APP_ZLL_DEVICE_TYPE >= APP_DEVICE_TYPE_EXTENDED_COLOR_LIGHT
    setColorTemperature(colorTemperatureTransition.target);
  }
}

/**************************************************************************//**
\brief Update transition state
******************************************************************************/
static void updateTransitionState(void)
{
  if (!zllDeviceIsOn())
  {
    colorControlClusterServerAttributes.remainingTime.value = 0;
    HAL_StopAppTimer(&updateTimer);
    return;
  }

  if (colorControlClusterServerAttributes.remainingTime.value < 0xffff)
    colorControlClusterServerAttributes.remainingTime.value--;

  if (colorControlClusterServerAttributes.remainingTime.value > 0)
  {
    if (inTransition & HUE)
      handleHueTransition();

    if (inTransition & SATURATION)
      handleSaturationTransition();

    else if (inTransition & COLOR)
      handleColorTransition();

    else if (inTransition & COLOR_LOOP)
      handleColorLoopTransition();

    else if (inTransition & TEMPERATURE)
      handleColorTemperatureTransition();
  }
  else
  {
    setTargetValue();
    transitionStop(ALL);
  }
}

/**************************************************************************//**
\brief Start the transition
******************************************************************************/
static void transitionStart(TransitionType_t type)
{
  inTransition |= type;

  if (colorControlClusterServerAttributes.remainingTime.value > 0)
  {
    HAL_StopAppTimer(&updateTimer);
    HAL_StartAppTimer(&updateTimer);
  }
  else
  {
    setTargetValue();
  }
}

/**************************************************************************//**
\brief Start current transition
******************************************************************************/
static void transitionStop(TransitionType_t type)
{
  inTransition &= ~type;

  if (NONE == inTransition)
  {
    HAL_StopAppTimer(&updateTimer);
    colorControlClusterServerAttributes.remainingTime.value = 0;
  }

  PDS_Store(ZLL_APP_MEMORY_MEM_ID);
}

#if APP_ZLL_DEVICE_TYPE != APP_DEVICE_TYPE_TEMPERATURE_COLOR_LIGHT
/**************************************************************************//**
\brief Prepare Move To Hue parameters
******************************************************************************/
static TransitionType_t prepareMoveToHue(uint16_t hue, uint8_t direction, uint16_t transitionTime,
                                         bool byStep)
{
  uint16_t delta;
  bool dir = true;

  if (!zllDeviceIsOn())
    return NONE;

  if (hue == colorControlClusterServerAttributes.enhancedCurrentHue.value)
    return NONE;

  hueTransition.target = hue;
  hueTransition.byStep = byStep;

  if (!byStep)
  {

    // Get shortest distance direction and delta
    if (hue > colorControlClusterServerAttributes.enhancedCurrentHue.value)
    {
      dir = true;
      delta = hue - colorControlClusterServerAttributes.enhancedCurrentHue.value;
    }
    else
    {
      dir = false;
      delta = colorControlClusterServerAttributes.enhancedCurrentHue.value - hue;
    }

    // Check if change in direction is needed
    if (ZCL_ZLL_MOVE_TO_HUE_DIRECTION_LONGEST_DISTANCE == direction ||
        (ZCL_ZLL_MOVE_TO_HUE_DIRECTION_UP == direction && false == dir) ||
        (ZCL_ZLL_MOVE_TO_HUE_DIRECTION_DOWN == direction && true == dir))
    {
      dir = !dir;
      delta = (MAX_HUE_LEVEL - MIN_HUE_LEVEL) - delta;
    }

    hueTransition.delta = ((uint32_t)delta << 16) / transitionTime;
    hueTransition.current = (uint32_t)colorControlClusterServerAttributes.enhancedCurrentHue.value << 16;
    hueTransition.direction = dir;
  }

  colorControlClusterServerAttributes.remainingTime.value = transitionTime;

  return HUE;
}

/**************************************************************************//**
\brief Prepare Move Hue parameters
******************************************************************************/
static bool prepareMoveHue(uint8_t mode, uint16_t rate)
{
  if (!zllDeviceIsOn())
    return false;

  if (ZCL_ZLL_MOVE_HUE_MOVE_MODE_UP == mode)
    hueTransition.direction = true;
  else
    hueTransition.direction = false;

  hueTransition.current = (uint32_t)colorControlClusterServerAttributes.enhancedCurrentHue.value << 16;
  hueTransition.target = 0;
  hueTransition.delta = ((uint32_t)rate << 16) / 10;
  hueTransition.byStep = false;

  colorControlClusterServerAttributes.remainingTime.value = 0xffff;

  return true;
}

/**************************************************************************//**
\brief Prepare Move To Saturation parameters
******************************************************************************/
static TransitionType_t prepareMoveToSaturation(uint8_t saturation, uint16_t transitionTime,
                                                bool byStep)
{
  uint16_t delta;
  bool dir = true;

  if (!zllDeviceIsOn())
    return NONE;

  if (saturation == colorControlClusterServerAttributes.currentSaturation.value)
    return NONE;

  saturationTransition.target = saturation;
  saturationTransition.byStep = byStep;

  if (!byStep)
  {

    // Get shortest distance direction and delta
    if (saturation > colorControlClusterServerAttributes.currentSaturation.value)
    {
      dir = true;
      delta = saturation - colorControlClusterServerAttributes.currentSaturation.value;
    }
    else
    {
      dir = false;
      delta = colorControlClusterServerAttributes.currentSaturation.value - saturation;
    }

    saturationTransition.delta = ((uint32_t)delta << 16) / (uint32_t)transitionTime;
    saturationTransition.current = (uint32_t)colorControlClusterServerAttributes.currentSaturation.value << 16;
    saturationTransition.direction = dir;
  }

  colorControlClusterServerAttributes.remainingTime.value = transitionTime;

  return SATURATION;
}

/**************************************************************************//**
\brief Prepare Move Saturation parameters
******************************************************************************/
static bool prepareMoveSaturation(uint8_t mode, uint16_t rate)
{
  if (!zllDeviceIsOn())
    return false;

  if (ZCL_ZLL_MOVE_HUE_MOVE_MODE_UP == mode)
    saturationTransition.direction = true;
  else
    saturationTransition.direction = false;

  saturationTransition.current = (uint32_t)colorControlClusterServerAttributes.currentSaturation.value << 16;
  saturationTransition.target = 0;
  saturationTransition.delta = ((uint32_t)rate << 16) / 10;
  saturationTransition.byStep = false;

  colorControlClusterServerAttributes.remainingTime.value = 0xffff;

  return true;
}


/**************************************************************************//**
\brief Prepare Move To Color parameters
******************************************************************************/
static bool prepareMoveToColor(uint16_t x, uint16_t y, uint16_t transitionTime)
{
  uint16_t deltax, deltay;
  bool dirx, diry;

  if (!zllDeviceIsOn())
    return false;

  if (x == colorControlClusterServerAttributes.currentX.value &&
      y == colorControlClusterServerAttributes.currentY.value)
    return false;

  // Get shortest distance direction and delta
  dirx = x > colorControlClusterServerAttributes.currentX.value;

  if (dirx)
    deltax = x - colorControlClusterServerAttributes.currentX.value;
  else
    deltax = colorControlClusterServerAttributes.currentX.value - x;

  diry = y > colorControlClusterServerAttributes.currentY.value;

  if (diry)
    deltay = y - colorControlClusterServerAttributes.currentY.value;
  else
    deltay = colorControlClusterServerAttributes.currentY.value - y;

  colorTransition.deltaX = ((uint32_t)deltax << 16) / transitionTime;
  colorTransition.deltaY = ((uint32_t)deltay << 16) / transitionTime;
  colorTransition.currentX = (uint32_t)colorControlClusterServerAttributes.currentX.value << 16;
  colorTransition.currentY = (uint32_t)colorControlClusterServerAttributes.currentY.value << 16;
  colorTransition.directionX = dirx;
  colorTransition.directionY = diry;
  colorTransition.targetX = x;
  colorTransition.targetY = y;

  colorControlClusterServerAttributes.remainingTime.value = transitionTime;

  return true;
}

/**************************************************************************//**
\brief Prepare Move Color parameters
******************************************************************************/
static bool prepareMoveColor(int16_t ratex, int16_t ratey)
{
  if (!zllDeviceIsOn())
    return false;

  // X
  colorTransition.deltaX = ((uint32_t)ABS(ratex) << 16) / 10;
  colorTransition.currentX = (uint32_t)colorControlClusterServerAttributes.currentX.value << 16;
  colorTransition.directionX = ratex > 0;
  colorTransition.targetX = 0;

  // Y
  colorTransition.deltaY = ((uint32_t)ABS(ratey) << 16) / 10;
  colorTransition.currentY = (uint32_t)colorControlClusterServerAttributes.currentY.value << 16;
  colorTransition.directionY = ratey > 0;
  colorTransition.targetY = 0;

  colorControlClusterServerAttributes.remainingTime.value = 0xffff;

  return true;
}
#endif // APP_ZLL_DEVICE_TYPE != APP_DEVICE_TYPE_TEMPERATURE_COLOR_LIGHT
#if APP_ZLL_DEVICE_TYPE >= APP_DEVICE_TYPE_EXTENDED_COLOR_LIGHT
/**************************************************************************//**
\brief Prepare Move To Color Temperature parameters
******************************************************************************/
static bool prepareMoveToColorTemperature(uint16_t temperature, uint16_t transitionTime, bool byStep)
{
  uint16_t deltaTemp;
  bool dirTemp;

  if (!zllDeviceIsOn())
    return false;

  if (temperature == colorControlClusterServerAttributes.colorTemperature.value)
    return false;

  colorControlClusterServerAttributes.remainingTime.value = transitionTime;
  colorTemperatureTransition.target                       = temperature;
  colorTemperatureTransition.byStep                       = byStep;

  // Get shortest distance direction and delta
  dirTemp = temperature > colorControlClusterServerAttributes.colorTemperature.value;
  if (dirTemp)
    deltaTemp = temperature - colorControlClusterServerAttributes.colorTemperature.value;
  else
    deltaTemp = colorControlClusterServerAttributes.colorTemperature.value - temperature;

  colorTemperatureTransition.delta     = ((uint32_t)deltaTemp << 16) / transitionTime;
  colorTemperatureTransition.current   = (uint32_t)colorControlClusterServerAttributes.colorTemperature.value << 16;
  colorTemperatureTransition.direction = dirTemp;
  colorTemperatureTransition.minTemp   = colorControlClusterServerAttributes.colorTempPhysicalMin.value;
  colorTemperatureTransition.maxTemp   = colorControlClusterServerAttributes.colorTempPhysicalMax.value;

  return true;
}

/**************************************************************************//**
\brief Prepare Move Color Temperature parameters
******************************************************************************/
static bool prepareMoveColorTemperature(uint8_t moveMode, uint16_t rate, uint16_t tempMin, uint16_t tempMax)
{
  if (!zllDeviceIsOn())
    return false;

  colorTemperatureTransition.delta     = ((uint32_t)ABS(rate) << 16) / 10;
  colorTemperatureTransition.current   = (uint32_t)colorControlClusterServerAttributes.colorTemperature.value << 16;
  colorTemperatureTransition.direction = ZCL_ZLL_MOVE_SATURATION_MOVE_MODE_UP == moveMode;
  colorTemperatureTransition.target    = 0;
  colorTemperatureTransition.byStep    = false;
  colorTemperatureTransition.minTemp   = MAX(tempMin, colorControlClusterServerAttributes.colorTempPhysicalMin.value);
  colorTemperatureTransition.maxTemp   = MIN(tempMax, colorControlClusterServerAttributes.colorTempPhysicalMax.value);

  colorControlClusterServerAttributes.remainingTime.value = 0xffff;

  return true;
}
#endif // APP_ZLL_DEVICE_TYPE >= APP_DEVICE_TYPE_EXTENDED_COLOR_LIGHT
#if APP_ZLL_DEVICE_TYPE != APP_DEVICE_TYPE_TEMPERATURE_COLOR_LIGHT
/**************************************************************************//**
\brief Callback on receive of Move To Hue command
******************************************************************************/
static ZCL_Status_t moveToHueInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ZllMoveToHueCommand_t *payload)
{
  LOG_STRING(moveToHueStr, "moveToHueInd()\r\n");

  appSnprintf(moveToHueStr);
  dbgLcdMsg("moveToHue");

  if ((MAX_HUE_LEVEL >> 8) < payload->hue)
    return ZCL_INVALID_VALUE_STATUS;

  if (prepareMoveToHue((uint16_t)payload->hue << 8, payload->direction, payload->transitionTime, false))
  {
    setColorMode(ZCL_ZLL_CURRENT_HUE_AND_CURRENT_SATURATION);
    transitionStart(HUE);
  }

  (void)addressing;
  (void)payloadLength;

  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receive of Move Hue command
******************************************************************************/
static ZCL_Status_t moveHueInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ZllMoveHueCommand_t *payload)
{
  LOG_STRING(moveHueStr, "moveHueInd()\r\n");

  appSnprintf(moveHueStr);
  dbgLcdMsg("moveHue");

  if (!payload->rate)
    return ZCL_INVALID_FIELD_STATUS;

  if (ZCL_ZLL_MOVE_HUE_MOVE_MODE_UP == payload->moveMode ||
      ZCL_ZLL_MOVE_HUE_MOVE_MODE_DOWN == payload->moveMode)
  {
    if (prepareMoveHue(payload->moveMode, (uint16_t)payload->rate << 8))
    {
      setColorMode(ZCL_ZLL_CURRENT_HUE_AND_CURRENT_SATURATION);
      transitionStart(HUE);
    }
  }
  else if (ZCL_ZLL_MOVE_HUE_MOVE_MODE_STOP == payload->moveMode)
  {
    transitionStop(ALL);
  }

  (void)addressing;
  (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receive of Step Hue command
******************************************************************************/
static ZCL_Status_t stepHueInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ZllStepHueCommand_t *payload)
{
  uint16_t hue;
  LOG_STRING(stepHueStr, "stepHueInd()\r\n");

  appSnprintf(stepHueStr);
  dbgLcdMsg("stepHue");

  hue = colorControlClusterServerAttributes.enhancedCurrentHue.value;

  if (ZCL_ZLL_STEP_HUE_STEP_MODE_UP == payload->stepMode)
    hue += (uint16_t)payload->stepSize << 8;
  else if (ZCL_ZLL_STEP_HUE_STEP_MODE_DOWN == payload->stepMode)
    hue -= (uint16_t)payload->stepSize << 8;
  else
    return ZCL_SUCCESS_STATUS;

  if (prepareMoveToHue(hue, ZCL_ZLL_MOVE_TO_HUE_DIRECTION_SHORTEST_DISTANCE, payload->transitionTime, true))
  {
    setColorMode(ZCL_ZLL_CURRENT_HUE_AND_CURRENT_SATURATION);
    transitionStart(HUE);
  }

  (void)addressing;
  (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receive of Move To Saturation command
******************************************************************************/
static ZCL_Status_t moveToSaturationInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ZllMoveToSaturationCommand_t *payload)
{
  LOG_STRING(moveToSaturationStr, "moveToSaturationInd()\r\n");

  appSnprintf(moveToSaturationStr);
  dbgLcdMsg("moveToSat");

  if (MAX_SATURATION_LEVEL < payload->saturation)
    return ZCL_INVALID_VALUE_STATUS;

  if (prepareMoveToSaturation(payload->saturation, payload->transitionTime, false))
  {
    setColorMode(ZCL_ZLL_CURRENT_HUE_AND_CURRENT_SATURATION);
    transitionStart(SATURATION);
  }

  (void)addressing;
  (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receive of Move Saturation command
******************************************************************************/
static ZCL_Status_t moveSaturationInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ZllMoveSaturationCommand_t *payload)
{
  LOG_STRING(moveSaturationStr, "moveSaturationInd()\r\n");

  appSnprintf(moveSaturationStr);
  dbgLcdMsg("moveSat");

  if (!payload->rate)
    return ZCL_INVALID_FIELD_STATUS;

  if (ZCL_ZLL_MOVE_SATURATION_MOVE_MODE_UP == payload->moveMode ||
      ZCL_ZLL_MOVE_SATURATION_MOVE_MODE_DOWN == payload->moveMode)
  {
    if (prepareMoveSaturation(payload->moveMode, payload->rate))
    {
      setColorMode(ZCL_ZLL_CURRENT_HUE_AND_CURRENT_SATURATION);
      transitionStart(SATURATION);
    }
  }
  else if (ZCL_ZLL_MOVE_SATURATION_MOVE_MODE_STOP == payload->moveMode)
  {
    transitionStop(ALL);
  }

  (void)addressing;
  (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receive of Step Saturation command
******************************************************************************/
static ZCL_Status_t stepSaturationInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ZllStepSaturationCommand_t *payload)
{
  int16_t saturation;
  LOG_STRING(stepSaturationStr, "stepSaturationInd()\r\n");

  appSnprintf(stepSaturationStr);
  dbgLcdMsg("stepSat");

  saturation = colorControlClusterServerAttributes.currentSaturation.value;

  if (ZCL_ZLL_STEP_SATURATION_STEP_MODE_UP == payload->stepMode)
    saturation += payload->stepSize;
  else if (ZCL_ZLL_STEP_HUE_STEP_MODE_DOWN == payload->stepMode)
    saturation -= payload->stepSize;
  else
    return ZCL_SUCCESS_STATUS;

  if (saturation < MIN_SATURATION_LEVEL || MAX_SATURATION_LEVEL < saturation)
    return ZCL_INVALID_VALUE_STATUS;

  if (prepareMoveToSaturation(saturation, payload->transitionTime, true))
  {
    setColorMode(ZCL_ZLL_CURRENT_HUE_AND_CURRENT_SATURATION);
    transitionStart(SATURATION);
  }

  (void)addressing;
  (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receive of Move To Hue And Saturation command
******************************************************************************/
static ZCL_Status_t moveToHueAndSaturationInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ZllMoveToHueAndSaturationCommand_t *payload)
{
  uint8_t proceedWith;
  LOG_STRING(moveToHueAndSaturationStr, "moveToHueAndSaturationInd()\r\n");

  appSnprintf(moveToHueAndSaturationStr);
  dbgLcdMsg("moveToHueAndSat");

  if ((MAX_HUE_LEVEL >> 8) < payload->hue ||
      MAX_SATURATION_LEVEL < payload->saturation)
    return ZCL_INVALID_VALUE_STATUS;

  proceedWith = prepareMoveToHue((uint16_t)payload->hue << 8, ZCL_ZLL_MOVE_TO_HUE_DIRECTION_SHORTEST_DISTANCE, payload->transitionTime, false);
  proceedWith |= prepareMoveToSaturation(payload->saturation, payload->transitionTime, false);

  if (proceedWith)
  {
    setColorMode(ZCL_ZLL_CURRENT_HUE_AND_CURRENT_SATURATION);
    transitionStart(proceedWith);
  }

  (void)addressing;
  (void)payloadLength;
  (void)payload;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receive of Move To Color command
******************************************************************************/
static ZCL_Status_t moveToColorInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ZllMoveToColorCommand_t *payload)
{
  LOG_STRING(moveToColorStr, "moveToColorInd()\r\n");

  appSnprintf(moveToColorStr);
  dbgLcdMsg("moveToColor");

  if (MAX_COLOR_LEVEL < payload->colorX || MAX_COLOR_LEVEL < payload->colorY)
    return ZCL_INVALID_VALUE_STATUS;

  if (prepareMoveToColor(payload->colorX, payload->colorY, payload->transitionTime))
  {
    setColorMode(ZCL_ZLL_CURRENT_X_AND_CURRENT_Y);
    transitionStart(COLOR);
  }

  (void)addressing;
  (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receive of Move Color command
******************************************************************************/
static ZCL_Status_t moveColorInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ZllMoveColorCommand_t *payload)
{
  LOG_STRING(moveColorStr, "moveColorInd()\r\n");

  appSnprintf(moveColorStr);
  dbgLcdMsg("moveColor");

  if (prepareMoveColor(payload->rateX, payload->rateY))
  {
    setColorMode(ZCL_ZLL_CURRENT_X_AND_CURRENT_Y);
    transitionStart(COLOR);
  }

  (void)addressing;
  (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receive of Step Color command
******************************************************************************/
static ZCL_Status_t stepColorInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ZllStepColorCommand_t *payload)
{
  int32_t x, y;
  LOG_STRING(stepColorStr, "stepColorInd()\r\n");

  appSnprintf(stepColorStr);
  dbgLcdMsg("stepColor");

  if (0 == payload->stepX && 0 == payload->stepY)
  {
    transitionStop(ALL);
    return ZCL_SUCCESS_STATUS;
  }

  x = (int32_t)colorControlClusterServerAttributes.currentX.value + payload->stepX;
  y = (int32_t)colorControlClusterServerAttributes.currentY.value + payload->stepY;

  if ((x < MIN_COLOR_LEVEL) || (MAX_COLOR_LEVEL < x) ||
      (y < MIN_COLOR_LEVEL) || (MAX_COLOR_LEVEL < y))
    return ZCL_INVALID_VALUE_STATUS;

  if (prepareMoveToColor(x, y, payload->transitionTime))
  {
    setColorMode(ZCL_ZLL_CURRENT_X_AND_CURRENT_Y);
    transitionStart(COLOR);
  }

  (void)addressing;
  (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receive of Enhanced Move To Hue command
******************************************************************************/
static ZCL_Status_t enhancedMoveToHueInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ZllEnhancedMoveToHueCommand_t *payload)
{
  LOG_STRING(enhancedMoveToHueStr, "enhancedMoveToHueInd()\r\n");

  appSnprintf(enhancedMoveToHueStr);
  dbgLcdMsg("eMoveToHue");

  // Check for direction == 1?
  if (MAX_HUE_LEVEL < payload->enhancedHue)
    return ZCL_INVALID_VALUE_STATUS;

  setColorMode(ZCL_ZLL_ENHANCED_CURRENT_HUE_AND_CURRENT_SATURATION);
  if (prepareMoveToHue(payload->enhancedHue, payload->direction, payload->transitionTime, false))
  {
    transitionStart(HUE);
  }

  (void)addressing;
  (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receive of Enhanced Move Hue command
******************************************************************************/
static ZCL_Status_t enhancedMoveHueInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ZllEnhancedMoveHueCommand_t *payload)
{
  LOG_STRING(enhancedMoveHueStr, "enhancedMoveHueInd()\r\n");

  appSnprintf(enhancedMoveHueStr);
  dbgLcdMsg("eMoveHue");


  if (ZCL_ZLL_MOVE_HUE_MOVE_MODE_UP == payload->moveMode ||
      ZCL_ZLL_MOVE_HUE_MOVE_MODE_DOWN == payload->moveMode)
  {
    if (!payload->rate)
      return ZCL_INVALID_FIELD_STATUS;

    if (prepareMoveHue(payload->moveMode, payload->rate))
    {
      setColorMode(ZCL_ZLL_ENHANCED_CURRENT_HUE_AND_CURRENT_SATURATION);
      transitionStart(HUE);
    }
  }
  else if (ZCL_ZLL_MOVE_HUE_MOVE_MODE_STOP == payload->moveMode)
  {
    transitionStop(ALL);
  }

  (void)addressing;
  (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receive of Enhanced Step Hue command
******************************************************************************/
static ZCL_Status_t enhancedStepHueInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ZllEnhancedStepHueCommand_t *payload)
{
  uint16_t hue;
  LOG_STRING(enhancedStepHueStr, "enhancedStepHueInd()\r\n");

  appSnprintf(enhancedStepHueStr);
  dbgLcdMsg("eStepHue");

  hue = colorControlClusterServerAttributes.enhancedCurrentHue.value;

  if (ZCL_ZLL_STEP_HUE_STEP_MODE_UP == payload->stepMode)
    hue += (uint16_t)payload->stepSize;
  else if (ZCL_ZLL_STEP_HUE_STEP_MODE_DOWN == payload->stepMode)
    hue -= (uint16_t)payload->stepSize;
  else
    return ZCL_SUCCESS_STATUS;

  if (prepareMoveToHue(hue, ZCL_ZLL_MOVE_TO_HUE_DIRECTION_SHORTEST_DISTANCE, payload->transitionTime, true))
  {
    setColorMode(ZCL_ZLL_ENHANCED_CURRENT_HUE_AND_CURRENT_SATURATION);
    transitionStart(HUE);
  }

  (void)addressing;
  (void)payloadLength;
  (void)payload;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receive of Enhanced Move To Hue And Saturation command
******************************************************************************/
static ZCL_Status_t enhancedMoveToHueAndSaturationInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ZllEnhancedMoveToHueAndSaturationCommand_t *payload)
{
  uint8_t proceedWith;
  LOG_STRING(enhancedMoveToHueAndSaturationStr, "enhancedMoveToHueAndSaturationInd()\r\n");

  appSnprintf(enhancedMoveToHueAndSaturationStr);
  dbgLcdMsg("eMTHAS");

  if (MAX_HUE_LEVEL < payload->enhancedHue ||
      MAX_SATURATION_LEVEL < payload->saturation)
    return ZCL_INVALID_VALUE_STATUS;

  proceedWith = prepareMoveToHue(payload->enhancedHue, ZCL_ZLL_MOVE_TO_HUE_DIRECTION_SHORTEST_DISTANCE, payload->transitionTime, false);
  proceedWith |= prepareMoveToSaturation(payload->saturation, payload->transitionTime, false);

  if (proceedWith)
  {
    setColorMode(ZCL_ZLL_ENHANCED_CURRENT_HUE_AND_CURRENT_SATURATION);
    transitionStart(proceedWith);
  }

  (void)addressing;
  (void)payloadLength;
  (void)payload;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receive of Color Loop Set command
******************************************************************************/
static ZCL_Status_t colorLoopSetInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ZllColorLoopSetCommand_t *payload)
{
  LOG_STRING(colorLoopSetStr, "colorLoopSetInd()\r\n");

  appSnprintf(colorLoopSetStr);
  dbgLcdMsg("colorLoopSet");

  if (!zllDeviceIsOn())
    return ZCL_SUCCESS_STATUS;

  if (COLOR_LOOP_UPDATE_DIRECTION & payload->updateFlags)
    colorControlClusterServerAttributes.colorLoopDirection.value = payload->direction;

  if (COLOR_LOOP_UPDATE_TIME & payload->updateFlags)
    colorControlClusterServerAttributes.colorLoopTime.value = payload->time;

  if (COLOR_LOOP_UPDATE_START_HUE & payload->updateFlags)
    colorControlClusterServerAttributes.colorLoopStartEnhancedHue.value = payload->startHue;

  if (COLOR_LOOP_UPDATE_ACTION & payload->updateFlags)
  {
    switch (payload->action)
    {
      case COLOR_LOOP_DEACTIVATE:
        if (colorControlClusterServerAttributes.colorLoopActive.value)
          stopColorLoop();
        break;

      case COLOR_LOOP_ACTIVATE_FROM_CLSEH:
        startColorLoop(COLOR_LOOP_ACTIVATE_FROM_CLSEH);
        break;

      case COLOR_LOOP_ACTIVATE_FROM_ECH:
        startColorLoop(COLOR_LOOP_ACTIVATE_FROM_ECH);
        break;

      default:
        break;
    }
  }

  (void)addressing;
  (void)payloadLength;
  (void)payload;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receive of Stop Move Step command
******************************************************************************/
static ZCL_Status_t stopMoveStepInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, void *payload)
{
  LOG_STRING(stopMoveStepStr, "stopMoveStepInd()\r\n");

  appSnprintf(stopMoveStepStr);
  dbgLcdMsg("stopMoveStep");

  transitionStop(ALL);

  (void)addressing;
  (void)payloadLength;
  (void)payload;
  return ZCL_SUCCESS_STATUS;
}
#endif // APP_ZLL_DEVICE_TYPE != APP_DEVICE_TYPE_TEMPERATURE_COLOR_LIGHT

#if APP_ZLL_DEVICE_TYPE >= APP_DEVICE_TYPE_EXTENDED_COLOR_LIGHT
/**************************************************************************//**
\brief Callback on receive of MoveToColorTemperature command
******************************************************************************/
static ZCL_Status_t moveToColorTemperatureInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ZllMoveToColorTemperatureCommand_t *payload)
{
  LOG_STRING(moveToColorTemperatureStr, "moveToColorTemperatureInd()\r\n");

  appSnprintf(moveToColorTemperatureStr);
  dbgLcdMsg("moveToColorTemperature");

  if (colorControlClusterServerAttributes.colorTempPhysicalMin.value > payload->colorTemperature ||
      colorControlClusterServerAttributes.colorTempPhysicalMax.value < payload->colorTemperature)
    return ZCL_INVALID_VALUE_STATUS;

  if (prepareMoveToColorTemperature(payload->colorTemperature, payload->transitionTime, false))
  {
    setColorMode(ZCL_ZLL_COLOR_TEMPERATURE);
    transitionStart(TEMPERATURE);
  }

  (void)addressing;
  (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receive of MoveColorTemperature command
******************************************************************************/
static ZCL_Status_t moveColorTemperatureInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ZllMoveColorTemperatureCommand_t *payload)
{
  LOG_STRING(moveColorTemperatureStr, "moveColorTemperatureInd()\r\n");

  appSnprintf(moveColorTemperatureStr);
  dbgLcdMsg("moveColorTemperature");

  if (ZCL_ZLL_MOVE_COLOR_TEMPERATURE_MOVE_MODE_STOP != payload->moveMode)
    if (!payload->rate)
      return ZCL_INVALID_VALUE_STATUS;

  if (ZCL_ZLL_MOVE_COLOR_TEMPERATURE_MOVE_MODE_UP == payload->moveMode ||
      ZCL_ZLL_MOVE_COLOR_TEMPERATURE_MOVE_MODE_DOWN == payload->moveMode)
  {
    if (prepareMoveColorTemperature(payload->moveMode, payload->rate, payload->colorTemperatureMinimum, payload->colorTemperatureMaximum))
    {
      setColorMode(ZCL_ZLL_COLOR_TEMPERATURE);
      transitionStart(TEMPERATURE);
    }
  }
   else if(ZCL_ZLL_MOVE_COLOR_TEMPERATURE_MOVE_MODE_STOP == payload->moveMode)
     transitionStop(ALL);

  (void)addressing;
  (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receive of StepColorTemperature command
******************************************************************************/
static ZCL_Status_t stepColorTemperatureInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ZllStepColorTemperatureCommand_t *payload)
{
  uint16_t temperature;
  LOG_STRING(stepColorTemperatureStr, "stepColorTemperatureInd()\r\n");

  appSnprintf(stepColorTemperatureStr);
  dbgLcdMsg("stepColorTemperature");

  if (0 == payload->stepSize)
  {
    transitionStop(ALL);
    return ZCL_SUCCESS_STATUS;
  }

  temperature = colorControlClusterServerAttributes.colorTemperature.value;

  if (ZCL_ZLL_STEP_COLOR_TEMPERATURE_STEP_MODE_UP == payload->stepMode)
  {
    if (ABSOLUTE_MAXIMUM_COLOR_TEMP - temperature > payload->stepSize)
      temperature += payload->stepSize;
    else
      temperature = ABSOLUTE_MAXIMUM_COLOR_TEMP;

    if (temperature > payload->colorTemperatureMaximum)
      temperature = payload->colorTemperatureMaximum;
  }
  else if (ZCL_ZLL_STEP_COLOR_TEMPERATURE_STEP_MODE_DOWN == payload->stepMode)
  {
    if (temperature >= payload->stepSize)
      temperature -= payload->stepSize;
    else
      temperature = 0;

    if (temperature < payload->colorTemperatureMinimum)
      temperature = payload->colorTemperatureMinimum;
  }
  else
    return ZCL_SUCCESS_STATUS;

  if (temperature < colorControlClusterServerAttributes.colorTempPhysicalMin.value ||
      colorControlClusterServerAttributes.colorTempPhysicalMax.value < temperature)
    return ZCL_INVALID_VALUE_STATUS;

  if (prepareMoveToColorTemperature(temperature, payload->transitionTime, true))
  {
    setColorMode(ZCL_ZLL_COLOR_TEMPERATURE);
    transitionStart(TEMPERATURE);
  }

  (void)addressing;
  (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}
#endif // APP_ZLL_DEVICE_TYPE >= APP_DEVICE_TYPE_EXTENDED_COLOR_LIGHT

#elif APP_ZLL_DEVICE_TYPE != APP_DEVICE_TYPE_COLOR_SCENE_REMOTE
  void colorControlClusterInit(void) {;}
#endif // APP_ZLL_DEVICE_TYPE >= APP_DEVICE_TYPE_COLOR_LIGHT

// eof lightColorControlCluster.c
