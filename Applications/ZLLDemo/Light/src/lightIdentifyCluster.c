/**************************************************************************//**
  \file lightIdentifyCluster.c

  \brief
    Light device Identify cluster implementation.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    28.06.11 A. Taradov - Created.
******************************************************************************/

#if APP_ZLL_DEVICE_TYPE >= APP_DEVICE_TYPE_ON_OFF_LIGHT

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zcl.h>
#include <commandManager.h>
#include <zclZllIdentifyCluster.h>
#include <lightIdentifyCluster.h>
#include <lightColorControlCluster.h>
#if defined(BOARD_MEGARF) || defined(BOARD_SAMR21)
#include <ledsExt.h>
#include <lcdExt.h>
#endif
#include <debug.h>
#include <lightClusters.h>
#include <zllDemo.h>
#include <lightLevelControlCluster.h>

/******************************************************************************
                    Definitions section
******************************************************************************/
#define DEFAULT_IDENTIFY_TIME 3U

#define BLINK_IDENTIFY_TIME          1U
#define BREATHE_IDENTIFY_TIME        15U
#if APP_ZLL_DEVICE_TYPE >= APP_DEVICE_TYPE_COLOR_LIGHT
  #define OKAY_IDENTIFY_TIME           1U
#else
  #define OKAY_IDENTIFY_TIME           2U
#endif // APP_ZLL_DEVICE_TYPE >= APP_DEVICE_TYPE_COLOR_LIGHT
#define CHANNEL_CHANGE_IDENTIFY_TIME 8U


#define ENHANCED_HUE_GREEN  30000U
#define ENHANCED_HUE_ORANGE 5000U

/******************************************************************************
                    Prototypes section
******************************************************************************/
static ZCL_Status_t identifyCommand(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_Identify_t *payload);
static ZCL_Status_t identifyQueryCommand(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload);
static ZCL_Status_t triggerEffectCommand(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_TriggerEffect_t *payload);
static void ZCL_IdentifyAttributeEventInd(ZCL_Addressing_t *addressing,
  ZCL_AttributeId_t attributeId, ZCL_AttributeEvent_t event);

static void effectTimerFired(void);

/******************************************************************************
                    Global variables
******************************************************************************/
ZCL_IdentifyClusterCommands_t identifyClusterServerCommands =
{
  ZCL_IDENTIFY_CLUSTER_COMMANDS(identifyCommand, identifyQueryCommand, triggerEffectCommand, NULL)
};

ZCL_IdentifyClusterAttributes_t identifyClusterServerAttributes =
{
  ZCL_DEFINE_IDENTIFY_CLUSTER_SERVER_ATTRIBUTES()
};

/******************************************************************************
                    Local variables
******************************************************************************/
static HAL_AppTimer_t effectTimer;
static struct
{
  bool period     : 1;
  bool finish     : 1;
  bool colorEffect: 1;
} identificationStatus;

/******************************************************************************
                    Implementations section
******************************************************************************/

// TODO: Handle situation of direct attribute write.

/**************************************************************************//**
\brief Initialize Identify cluster.
******************************************************************************/
void identifyClusterInit(void)
{
  ZCL_Cluster_t *cluster = ZCL_GetCluster(APP_ENDPOINT_LIGHT, IDENTIFY_CLUSTER_ID, ZCL_CLUSTER_SIDE_SERVER);

  if (cluster)
    cluster->ZCL_AttributeEventInd = ZCL_IdentifyAttributeEventInd;

  identifyClusterServerAttributes.identifyTime.value = 0;
}

/**************************************************************************//**
\brief Get current identifying status
******************************************************************************/
bool identifyClusterIsIdentifying(void)
{
  return identifyClusterServerAttributes.identifyTime.value > 0;
}

/**************************************************************************//**
\brief Shows identification effect in way specified.

\param[in] identifyTime - identifying period in seconds.
\param[in] colorEffect - flag to set for color effects.
\param[in] enhancedHue - enhanced hue to move for color effects.
******************************************************************************/
void identifyStart(uint16_t identifyTime, bool colorEffect, uint16_t enhancedHue)
{
  HAL_StopAppTimer(&effectTimer);
  identificationStatus.finish = false;
  identificationStatus.colorEffect = colorEffect;

  if (colorEffect)
  {
    identifyClusterServerAttributes.identifyTime.value = identifyTime * 2;
#if APP_ZLL_DEVICE_TYPE >= APP_DEVICE_TYPE_COLOR_LIGHT
    colorControlShowIdentifyEffect(enhancedHue);
#else
    (void)enhancedHue;
#endif // APP_ZLL_DEVICE_TYPE >= APP_DEVICE_TYPE_COLOR_LIGHT
  }
  else
    identifyClusterServerAttributes.identifyTime.value = identifyTime;

  LCD_FILL(true);
  LEDS_SET_BRIGHTNESS(MAX_LIGHT_LEVEL);
  effectTimer.mode = TIMER_REPEAT_MODE;
  effectTimer.interval = 500;
  effectTimer.callback = effectTimerFired;
  HAL_StartAppTimer(&effectTimer);
}

/**************************************************************************//**
\brief Finish identification routine.
******************************************************************************/
void identifyFinish(void)
{
  identificationStatus.finish = true;
}

/**************************************************************************//**
\brief Stop identification routine.
******************************************************************************/
void identifyStop(void)
{
#if APP_ZLL_DEVICE_TYPE >= APP_DEVICE_TYPE_COLOR_LIGHT
  if (identificationStatus.colorEffect)
    colorControlStopIdentifyEffect();
#endif // #if APP_ZLL_DEVICE_TYPE >= APP_DEVICE_TYPE_COLOR_LIGHT

  identificationStatus.period = 0;
  HAL_StopAppTimer(&effectTimer);
  identifyClusterServerAttributes.identifyTime.value = 0;
  LCD_FILL(false);
  levelControlDisplayLevel();
}

/**************************************************************************//**
\brief Effect timer callback
******************************************************************************/
static void effectTimerFired(void)
{
  if (identificationStatus.colorEffect)
  {
    identifyClusterServerAttributes.identifyTime.value--;
#if APP_ZLL_DEVICE_TYPE <= APP_DEVICE_TYPE_DIMMABLE_LIGHT
    uint8_t level = identificationStatus.period ? MAX_LIGHT_LEVEL : 0;

    identificationStatus.period = !identificationStatus.period;
    LCD_FILL(!identificationStatus.period);
    LEDS_SET_BRIGHTNESS(level);
    (void)level;
#endif // APP_ZLL_DEVICE_TYPE == APP_DEVICE_TYPE_DIMMABLE_LIGHT
  }
  else
  {
    uint8_t level = 0;
    identificationStatus.period = !identificationStatus.period;

    LCD_FILL(identificationStatus.period);

    if (identificationStatus.period)
    {
      level = MAX_LIGHT_LEVEL;
      identifyClusterServerAttributes.identifyTime.value--;
    }

    LEDS_SET_BRIGHTNESS(level);

    (void)level;
  }

  if (0 == identifyClusterServerAttributes.identifyTime.value ||
      identificationStatus.finish)
    identifyStop();
}

/**************************************************************************//**
\brief Attribute event (writing/reading) callback.

\param[in] addressing - incoming request addressing information.
\param[in] attributeId - attribute identifier.
\param[in] event - attribute event (read/write).
******************************************************************************/
static void ZCL_IdentifyAttributeEventInd(ZCL_Addressing_t *addressing,
  ZCL_AttributeId_t attributeId, ZCL_AttributeEvent_t event)
{
  if ((ZCL_WRITE_ATTRIBUTE_EVENT == event) &&
      (ZCL_IDENTIFY_CLUSTER_IDENTIFY_TIME_ATTRIBUTE_ID == attributeId))
  {
    if (identifyClusterServerAttributes.identifyTime.value)
    {
      identifyStart(identifyClusterServerAttributes.identifyTime.value,
                    IDENTIFY_NON_COLOR_EFFECT, 0);
    }
    else
    {
      identifyStop();
    }
      
    (void)addressing;
  }
}

/**************************************************************************//**
\brief Callback on receive of Identify command
******************************************************************************/
static ZCL_Status_t identifyCommand(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_Identify_t *payload)
{
  LOG_STRING(zclIdentifyStr, "Identify\r\n");

  appSnprintf(zclIdentifyStr);

  if (payload->identifyTime)
    identifyStart(payload->identifyTime, IDENTIFY_NON_COLOR_EFFECT, 0);
  else
    identifyStop();

  (void)addressing;
  (void)payloadLength;
  (void)payload;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receive of Identify Query command
******************************************************************************/
static ZCL_Status_t identifyQueryCommand(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload)
{
  CommandDescriptor_t *cmd;
  ZCL_IdentifyQueryResponse_t *identifyQueryResp;

  // needed by certification
  if (!identifyClusterIsIdentifying())
    return ZCL_SUCCESS_WITH_DEFAULT_RESPONSE_STATUS;

  if (!(cmd = clustersAllocCommand()))
    return ZCL_SUCCESS_STATUS;

  cmd->clusterId = IDENTIFY_CLUSTER_ID;
  cmd->commandId = ZCL_IDENTIFY_CLUSTER_IDENTIFY_QUERY_RESPONSE_COMMAND_ID;
  cmd->srcEndpoint = APP_ENDPOINT_LIGHT;
  cmd->seqNumberSpecified = true;

  identifyQueryResp = &cmd->payload.identifyQueryResp;
  identifyQueryResp->timeout = identifyClusterServerAttributes.identifyTime.value;

  cmd->size = sizeof(cmd->payload.identifyQueryResp);

  clustersSendCommandWithAddressing(cmd, addressing);

  (void)payloadLength;
  (void)payload;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receive of Trigger Effect command
******************************************************************************/
static ZCL_Status_t triggerEffectCommand(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_TriggerEffect_t *payload)
{
  LOG_STRING(zclTriggerEffectStr, "TriggerEffect %d\r\n");

  appSnprintf(zclTriggerEffectStr,  payload->effectIdentifier);

  switch (payload->effectIdentifier)
  {
    case ZCL_EFFECT_IDENTIFIER_BLINK:
      identifyStart(BLINK_IDENTIFY_TIME, IDENTIFY_NON_COLOR_EFFECT, 0);
      break;

    case ZCL_EFFECT_IDENTIFIER_BREATHE:
      identifyStart(BREATHE_IDENTIFY_TIME, IDENTIFY_NON_COLOR_EFFECT, 0);
      break;

    case ZCL_EFFECT_IDENTIFIER_OKAY:
      identifyStart(OKAY_IDENTIFY_TIME, IDENTIFY_COLOR_EFFECT, ENHANCED_HUE_GREEN);
      break;

    case ZCL_EFFECT_IDENTIFIER_CHANNEL_CHANGE:
      identifyStart(CHANNEL_CHANGE_IDENTIFY_TIME, IDENTIFY_COLOR_EFFECT, ENHANCED_HUE_ORANGE);
      break;

    case ZCL_EFFECT_IDENTIFIER_FINISH_EFFECT:
      identifyFinish();
      break;

    case ZCL_EFFECT_IDENTIFIER_STOP_EFFECT:
      identifyStop();
      break;

    default:
      break;
  }

  (void)addressing;
  (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}

#endif // APP_ZLL_DEVICE_TYPE >= APP_DEVICE_TYPE_ON_OFF_LIGHT

// eof lightIdentifyCluster.c
