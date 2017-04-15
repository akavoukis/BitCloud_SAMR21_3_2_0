/**************************************************************************//**
  \file buttonHandlers.c

  \brief
    Handlers for the buttons pressed during normal operation.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    16.08.11 A. Taradov - Created.
******************************************************************************/
#if APP_ZLL_DEVICE_TYPE == APP_DEVICE_TYPE_COLOR_SCENE_REMOTE

/******************************************************************************
                    Includes
******************************************************************************/
#include <leds.h>
#if defined(BOARD_MEGARF) || defined(BOARD_SAMR21)
#include <ledsExt.h>
#endif
#ifdef BOARD_MEGARF
#include <buttonsExt.h>
#endif
#include <zcl.h>
#include <debug.h>
#include <clusters.h>
#include <commandManager.h>
#include <colorSceneRemoteFsm.h>
#include <zllDemo.h>
#include <colorSceneRemoteColorControlCluster.h>

#include <N_DeviceInfo_Bindings.h>
#include <N_DeviceInfo.h>
#include <N_LinkTarget_Bindings.h>
#include <N_PacketDistributor.h>
#define N_Zdp_SendMgmtNwkUpdateReq N_Zdp_SendMgmtNwkUpdateReq_Impl
#include <N_Zdp.h>

/******************************************************************************
                    Implementations
******************************************************************************/

/**************************************************************************//**
\brief Button handler
******************************************************************************/
void buttonHandler(uint8_t button, uint8_t time, uint8_t alt)
{
#ifdef BOARD_MEGARF
  CommandDescriptor_t *cmd;

  if (!(cmd = clustersAllocCommand()))
    return;

  cmd->isAttributeOperation = false;

  if (BUTTON_SEL == button)
  {
    if (0 == alt)
    {
      selectNextBoundDevice();
    }

    if (1 == alt)
    {
      selectPrevBoundDevice();
    }
    else if (2 == alt)
    {
      cmd->clusterId = IDENTIFY_CLUSTER_ID;
      cmd->commandId = ZCL_IDENTIFY_CLUSTER_IDENTIFY_COMMAND_ID;
      cmd->payload.identify.identifyTime = 5;
      cmd->size = sizeof(cmd->payload.identify);
      clustersSendCommand(cmd);
      return;
    }
    else if (3 == alt)
    {
      cmd->clusterId = IDENTIFY_CLUSTER_ID;
      cmd->commandId = ZCL_IDENTIFY_CLUSTER_TRIGGER_EFFECT_COMMAND_ID;
      cmd->payload.triggerEffect.effectIdentifier = ZCL_EFFECT_IDENTIFIER_OKAY;
      cmd->payload.triggerEffect.effectVariant = ZCL_EFFECT_VARIANT_DEFAULT;
      cmd->size = sizeof(cmd->payload.triggerEffect);
      clustersSendCommand(cmd);
      return;
    }
  }

  else if (button <= BUTTON_BLUE) // BUTTON_RED = 0, so  button >= BUTTON_RED is always true
  {
    if (0 == alt)
    {
      uint16_t hue;

      if (BUTTON_RED == button)
        hue = 60000;
      else if (BUTTON_GREEN == button)
        hue = 30000;
      else if (BUTTON_YELLOW == button)
        hue = 15000;
      else // BUTTON_BLUE
        hue = 45000;

      cmd->clusterId = COLOR_CONTROL_CLUSTER_ID;
      cmd->commandId = ENHANCED_MOVE_TO_HUE_COMMAND_ID;
      cmd->payload.enhancedMoveToHue.enhancedHue = hue;
      cmd->payload.enhancedMoveToHue.direction = ZCL_ZLL_MOVE_TO_HUE_DIRECTION_SHORTEST_DISTANCE;
      cmd->payload.enhancedMoveToHue.transitionTime = 5;
      cmd->size = sizeof(cmd->payload.enhancedMoveToHue);
      clustersSendCommand(cmd);
      return;
    }
    else if (1 == alt)
    {
      uint8_t hue;

      if (BUTTON_RED == button)
        hue = 240;
      else if (BUTTON_GREEN == button)
        hue = 120;
      else if (BUTTON_YELLOW == button)
        hue = 60;
      else // BUTTON_BLUE
        hue = 180;

      cmd->clusterId = COLOR_CONTROL_CLUSTER_ID;
      cmd->commandId = MOVE_TO_HUE_COMMAND_ID;
      cmd->payload.moveToHue.hue = hue;
      cmd->payload.moveToHue.direction = ZCL_ZLL_MOVE_TO_HUE_DIRECTION_SHORTEST_DISTANCE;
      cmd->payload.moveToHue.transitionTime = 5;
      cmd->size = sizeof(cmd->payload.moveToHue);
      clustersSendCommand(cmd);
      return;
    }
    else if (2 == alt)
    {
      uint16_t x, y;

      if (BUTTON_RED == button)
      {
        x = 40000;
        y = 20000;
      }
      else if (BUTTON_GREEN == button)
      {
        x = 10000;
        y = 40000;
      }
      else if (BUTTON_YELLOW == button)
      {
        x = 30000;
        y = 30000;
      }
      else // BUTTON_BLUE
      {
        x = 10000;
        y = 10000;
      }

      cmd->clusterId = COLOR_CONTROL_CLUSTER_ID;
      cmd->commandId = MOVE_TO_COLOR_COMMAND_ID;
      cmd->payload.moveToColor.colorX = x;
      cmd->payload.moveToColor.colorY = y;
      cmd->payload.moveToColor.transitionTime = 5;
      cmd->size = sizeof(cmd->payload.moveToColor);
      clustersSendCommand(cmd);
      return;
    }
    else if (3 == alt)
    {
      uint16_t temperature;
      DstAddressing_t *addressing = clustersGetDstAddressing();

      if (BUTTON_RED == button)
        temperature = 1000;
      else if (BUTTON_GREEN == button)
        temperature = 168;
      else if (BUTTON_YELLOW == button)
        temperature = 333;
      else // BUTTON_BLUE
        temperature = 66;

      colorSceneRemoteSendMoveToColorTemperatureCommand(addressing->mode, addressing->addr,
                                                       addressing->ep, temperature, 5);
      clustersFreeCommand(cmd);
      return;
    }
  }

  else if (BUTTON_1 <= button && button <= BUTTON_3)
  {
    uint8_t scene;

    if (BUTTON_1 == button)
      scene = 1;
    else if (BUTTON_2 == button)
      scene = 2;
    else // BUTTON_3
      scene = 3;

    if (0 == alt)
    {
      if (time < 30)
      {
        cmd->clusterId = SCENES_CLUSTER_ID;
        cmd->commandId = ZCL_SCENES_CLUSTER_RECALL_SCENE_COMMAND_ID;
        cmd->payload.recallScene.groupId = getOwnGroupId();
        cmd->payload.recallScene.sceneId = scene;
        cmd->size = sizeof(cmd->payload.recallScene);
      }
      else
      {
        cmd->clusterId = SCENES_CLUSTER_ID;
        cmd->commandId = ZCL_SCENES_CLUSTER_STORE_SCENE_COMMAND_ID;
        cmd->payload.storeScene.groupId = getOwnGroupId();
        cmd->payload.storeScene.sceneId = scene;
        cmd->size = sizeof(cmd->payload.storeScene);
      }
    }
    else if (1 == alt)
    {
      cmd->clusterId = SCENES_CLUSTER_ID;
      cmd->commandId = ZCL_SCENES_CLUSTER_ADD_SCENE_COMMAND_ID;
      cmd->payload.addScene.groupId = getOwnGroupId();
      cmd->payload.addScene.sceneId = scene;
      cmd->payload.addScene.transitionTime = 8;
      cmd->payload.addScene.name[0] = 0;
      cmd->size = sizeof(cmd->payload.addScene);
    }
    else if (2 == alt)
    {
      cmd->clusterId = SCENES_CLUSTER_ID;
      cmd->commandId = ZCL_SCENES_CLUSTER_ENHANCED_ADD_SCENE_COMMAND_ID;
      cmd->payload.enhancedAddScene.groupId = getOwnGroupId();
      cmd->payload.enhancedAddScene.sceneId = scene;
      cmd->payload.enhancedAddScene.transitionTime = 8;
      cmd->payload.enhancedAddScene.name[0] = 0;

      cmd->payload.enhancedAddScene.onOffClusterExtFields.clusterId = ONOFF_CLUSTER_ID;
      cmd->payload.enhancedAddScene.onOffClusterExtFields.length = sizeof(uint8_t);
      cmd->payload.enhancedAddScene.onOffClusterExtFields.onOffValue = 1;

      cmd->payload.enhancedAddScene.levelControlClusterExtFields.clusterId = LEVEL_CONTROL_CLUSTER_ID;
      cmd->payload.enhancedAddScene.levelControlClusterExtFields.length = sizeof(uint8_t);
      cmd->payload.enhancedAddScene.levelControlClusterExtFields.currentLevel = 128;

      cmd->payload.enhancedAddScene.colorControlClusterExtFields.clusterId = COLOR_CONTROL_CLUSTER_ID;
      cmd->payload.enhancedAddScene.colorControlClusterExtFields.length = sizeof(uint8_t) + sizeof(uint16_t) * 4;
      cmd->payload.enhancedAddScene.colorControlClusterExtFields.currentX = 0;
      cmd->payload.enhancedAddScene.colorControlClusterExtFields.currentY = 0;
      cmd->payload.enhancedAddScene.colorControlClusterExtFields.enhancedCurrentHue = 30000; // Green
      cmd->payload.enhancedAddScene.colorControlClusterExtFields.currentSaturation = 128;

      cmd->size = sizeof(cmd->payload.enhancedAddScene);
    }
    else if (3 == alt)
    {
      cmd->clusterId = SCENES_CLUSTER_ID;
      cmd->commandId = ZCL_SCENES_CLUSTER_REMOVE_SCENE_COMMAND_ID;
      cmd->payload.removeScene.groupId = getOwnGroupId();
      cmd->payload.removeScene.sceneId = scene;
      cmd->size = sizeof(cmd->payload.removeScene);
    }

    clustersSendCommand(cmd);
    return;
  }

  else if (BUTTON_4 == button)
  {
    if (1 == alt)
    {
      cmd->clusterId = BASIC_CLUSTER_ID;
      cmd->commandId = ZCL_READ_ATTRIBUTES_COMMAND_ID;
      cmd->payload.readAttribute.id = ZCL_BASIC_CLUSTER_SERVER_ZCL_VERSION_ATTRIBUTE_ID;
      cmd->size = sizeof(ZCL_ReadAttributeReq_t);
      cmd->isAttributeOperation = true;
      clustersSendCommand(cmd);
      return;
    }
    else if (0 == alt)
    {
      N_Address_t dstAddress = {{0}, N_Address_Mode_Short, 0, 0};
      uint8_t channel = N_DeviceInfo_GetNetworkChannel();
      uint32_t newChannel = N_DeviceInfo_GetPrimaryChannelMask();
      
      newChannel &= ~(1ul << channel);
      if (0ul == newChannel)
      {
        newChannel = N_DeviceInfo_GetSecondaryChannelMask();
        newChannel &= ~(1ul << channel);
        if (0ul == newChannel)
        {
          return;
        }
      }
      channel = N_DeviceInfo_GetChannelForIndex(0, newChannel);
      dstAddress.address.shortAddress = 0xfffdu;
      N_Zdp_SendMgmtNwkUpdateReq(1ul << channel,
                             0xFE, 0U,
                             NWK_GetUpdateId() + 1, 0U,
                             &dstAddress);
    }
  }

  else if (BUTTON_5 == button)
  {
    cmd->clusterId = IDENTIFY_CLUSTER_ID;
    cmd->commandId = ZCL_IDENTIFY_CLUSTER_TRIGGER_EFFECT_COMMAND_ID;
    cmd->payload.triggerEffect.effectVariant = ZCL_EFFECT_VARIANT_DEFAULT;
    cmd->size = sizeof(cmd->payload.triggerEffect);

    if (0 == alt)
    {
      cmd->payload.triggerEffect.effectIdentifier = ZCL_EFFECT_IDENTIFIER_BREATHE;
    }

    if (1 == alt)
    {
      cmd->payload.triggerEffect.effectIdentifier = ZCL_EFFECT_IDENTIFIER_FINISH_EFFECT;
    }

    if (2 == alt)
    {
      cmd->payload.triggerEffect.effectIdentifier = ZCL_EFFECT_IDENTIFIER_STOP_EFFECT;
    }

    clustersSendCommand(cmd);
    return;
  }

  else if (BUTTON_6 == button)
  {
    DstAddressing_t *addressing = clustersGetDstAddressing();

    clustersFreeCommand(cmd);
    if (0 == alt)
      colorSceneRemoteSendMoveColorTemperatureCommand(addressing->mode, addressing->addr,
                                                      addressing->ep, ZCL_ZLL_MOVE_COLOR_TEMPERATURE_MOVE_MODE_UP,
                                                      30, 1000, 15000);
    else if (1 == alt)
      colorSceneRemoteSendMoveColorTemperatureCommand(addressing->mode, addressing->addr,
                                                      addressing->ep, ZCL_ZLL_MOVE_COLOR_TEMPERATURE_MOVE_MODE_DOWN,
                                                      30, 1000, 15000);
    else if (2 == alt)
      colorSceneRemoteSendStepColorTemperatureCommand(addressing->mode, addressing->addr,
                                                      addressing->ep, ZCL_ZLL_STEP_COLOR_TEMPERATURE_STEP_MODE_UP,
                                                      20, 5, 1000, 15000);
    else
      colorSceneRemoteSendStepColorTemperatureCommand(addressing->mode, addressing->addr,
                                                      addressing->ep, ZCL_ZLL_STEP_COLOR_TEMPERATURE_STEP_MODE_DOWN,
                                                      20, 5, 1000, 15000);
    return;
  }

  else if (BUTTON_7 <= button && button <= BUTTON_9)
  {
    if (0 == alt || 1 == alt)
    {
      uint8_t level;

      if (BUTTON_7 == button)
        level = 1;
      else if (BUTTON_8 == button)
        level = 128;
      else
        level = 254;

      cmd->clusterId = LEVEL_CONTROL_CLUSTER_ID;
      cmd->commandId = (0 == alt) ? ZCL_LEVEL_CONTROL_CLUSTER_MOVE_TO_LEVEL_COMMAND_ID :
                                    ZCL_LEVEL_CONTROL_CLUSTER_MOVE_TO_LEVEL_W_ONOFF_COMMAND_ID;
      cmd->payload.moveToLevel.level = level;
      cmd->payload.moveToLevel.transitionTime = 5;
      cmd->size = sizeof(cmd->payload.moveToLevel);
      clustersSendCommand(cmd);
      return;
    }
    else if (2 == alt)
    {
      uint8_t saturation;

      if (BUTTON_7 == button)
        saturation = 0;
      else if (BUTTON_8 == button)
        saturation = 128;
      else
        saturation = 255;

      cmd->clusterId = COLOR_CONTROL_CLUSTER_ID;
      cmd->commandId = MOVE_TO_SATURATION_COMMAND_ID;
      cmd->payload.moveToSaturation.saturation = saturation;
      cmd->payload.moveToSaturation.transitionTime = 5;
      cmd->size = sizeof(cmd->payload.moveToSaturation);
      clustersSendCommand(cmd);
      return;
    }
  }

  else if (BUTTON_0 == button)
  {
    if (0 == alt)
    {
      ZCL_Addressing_t dstAddressing;

      fillDstAddressing(&dstAddressing);

      if (APS_SHORT_ADDRESS != dstAddressing.addrMode)
      {
        clustersFreeCommand(cmd);
        return;
      }

      dstAddressing.clusterSide = ZCL_CLUSTER_SIDE_CLIENT;
      dstAddressing.clusterId = ZLL_COMMISSIONING_CLUSTER_ID;
      dstAddressing.manufacturerSpecCode = 0x0000;
	  dstAddressing.sequenceNumber = 0x00;

      cmd->disableDefaultResp = false;
      cmd->clusterId = ZLL_COMMISSIONING_CLUSTER_ID;
      cmd->commandId = ZCL_COMMISSIONING_CLUSTER_ENDPOINT_INFORMATION_COMMAND_ID;
      COPY_EXT_ADDR(cmd->payload.endpointInformation.ieeeAddress, *((ExtAddr_t *)N_DeviceInfo_GetIEEEAddress()));
      cmd->payload.endpointInformation.networkAddress = N_DeviceInfo_GetNetworkAddress();
      cmd->payload.endpointInformation.endpointId = APP_ENDPOINT_COLOR_SCENE_REMOTE;
      cmd->payload.endpointInformation.profileId = APP_PROFILE_ID;
      cmd->payload.endpointInformation.deviceId = APP_DEVICE_ID;
      cmd->payload.endpointInformation.version = APP_VERSION;
      cmd->size = sizeof(cmd->payload.endpointInformation);
      clustersSendCommandWithAddressing(cmd, &dstAddressing);
      return;
    }
    else if (1 == alt)
    {
      sendPermitJoinCommand(true);
    }
    else if (2 == alt)
    {
      sendPermitJoinCommand(false);
    }
  }

  else if (BUTTON_LEFT_P == button)
  {
    cmd->clusterId = ONOFF_CLUSTER_ID;

    if (0 == alt)
    {
      cmd->commandId = ZCL_ONOFF_CLUSTER_ON_COMMAND_ID;
    }
    else if (1 == alt)
    {
      cmd->commandId = ZCL_ONOFF_CLUSTER_ON_WITH_RECALL_GLOBAL_SCENE_COMMAND_ID;
    }
    else if (2 == alt)
    {
      cmd->commandId = ZCL_ONOFF_CLUSTER_ON_WITH_TIMED_OFF_COMMAND_ID;
      cmd->payload.onWithTimedOff.onOffControl = 0;
      cmd->payload.onWithTimedOff.onTime = 100; // 10 seconds
      cmd->payload.onWithTimedOff.offWaitTime = 100; // 10 seconds
      cmd->size = sizeof(cmd->payload.onWithTimedOff);
    }
    else if (3 == alt)
    {
      cmd->commandId = ZCL_ONOFF_CLUSTER_TOGGLE_COMMAND_ID;
    }

    clustersSendCommand(cmd);
    return;
  }

  else if (BUTTON_LEFT_M == button)
  {
    cmd->clusterId = ONOFF_CLUSTER_ID;

    if (0 == alt)
    {
      cmd->commandId = ZCL_ONOFF_CLUSTER_OFF_COMMAND_ID;
      clustersSendCommand(cmd);
      return;
    }
    else if (1 == alt)
    {
      cmd->commandId = ZCL_ONOFF_CLUSTER_OFF_WITH_EFFECT_COMMAND_ID;
      cmd->payload.offWithEffect.effectIdentifier = 0;
      cmd->payload.offWithEffect.effectVariant = 0;
      cmd->size = sizeof(cmd->payload.offWithEffect);
      clustersSendCommand(cmd);
      return;
    }
  }

  else if (BUTTON_UP == button || BUTTON_DOWN == button)
  {
    uint8_t direction;

    direction = (BUTTON_UP == button) ? ZLL_LEVEL_CONTROL_UP_DIRECTION :
                                        ZLL_LEVEL_CONTROL_DOWN_DIRECTION;

    cmd->clusterId = LEVEL_CONTROL_CLUSTER_ID;

    if (0 == alt)
    {
      cmd->commandId = ZCL_LEVEL_CONTROL_CLUSTER_STEP_COMMAND_ID;
      cmd->payload.stepLevel.stepMode = direction;
      cmd->payload.stepLevel.stepSize = 20;
      cmd->payload.stepLevel.transitionTime = 5;
      cmd->size = sizeof(cmd->payload.stepLevel);
    }
    else if (1 == alt)
    {
      cmd->commandId = ZCL_LEVEL_CONTROL_CLUSTER_MOVE_COMMAND_ID;
      cmd->payload.moveLevel.moveMode = direction;
      cmd->payload.moveLevel.rate = 30;
      cmd->size = sizeof(cmd->payload.moveLevel);
    }
    else if (2 == alt)
    {
      cmd->commandId = ZCL_LEVEL_CONTROL_CLUSTER_STEP_W_ONOFF_COMMAND_ID;
      cmd->payload.stepLevel.stepMode = direction;
      cmd->payload.stepLevel.stepSize = 20;
      cmd->payload.stepLevel.transitionTime = 5;
      cmd->size = sizeof(cmd->payload.stepLevel);
    }
    else if (3 == alt)
    {
      cmd->commandId = ZCL_LEVEL_CONTROL_CLUSTER_MOVE_W_ONOFF_COMMAND_ID;
      cmd->payload.moveLevel.moveMode = direction;
      cmd->payload.moveLevel.rate = 30;
      cmd->size = sizeof(cmd->payload.moveLevel);
    }

    clustersSendCommand(cmd);
    return;
  }

  else if (BUTTON_LEFT == button || BUTTON_RIGHT == button)
  {
    cmd->clusterId = COLOR_CONTROL_CLUSTER_ID;

    if (0 == alt)
    {
      cmd->commandId = STEP_SATURATION_COMMAND_ID;
      cmd->payload.stepSaturation.stepMode = (BUTTON_LEFT == button) ?
          ZCL_ZLL_STEP_SATURATION_STEP_MODE_DOWN : ZCL_ZLL_STEP_SATURATION_STEP_MODE_UP;
      cmd->payload.stepSaturation.stepSize = 20;
      cmd->payload.stepSaturation.transitionTime = 5;
      cmd->size = sizeof(cmd->payload.stepSaturation);
    }
    else if (1 == alt)
    {
      cmd->commandId = MOVE_SATURATION_COMMAND_ID;
      cmd->payload.moveSaturation.moveMode = (BUTTON_LEFT == button) ?
          ZCL_ZLL_MOVE_SATURATION_MOVE_MODE_DOWN : ZCL_ZLL_MOVE_SATURATION_MOVE_MODE_UP;
      cmd->payload.moveSaturation.rate = 30;
      cmd->size = sizeof(cmd->payload.moveSaturation);
    }
    else if (2 == alt)
    {
      cmd->commandId = ENHANCED_STEP_HUE_COMMAND_ID;
      cmd->payload.enhancedStepHue.stepMode = (BUTTON_LEFT == button) ?
          ZCL_ZLL_STEP_HUE_STEP_MODE_DOWN : ZCL_ZLL_STEP_HUE_STEP_MODE_UP;
      cmd->payload.enhancedStepHue.stepSize = 20 << 8;
      cmd->payload.enhancedStepHue.transitionTime = 5;
      cmd->size = sizeof(cmd->payload.enhancedStepHue);
    }
    else if (3 == alt)
    {
      cmd->commandId = ENHANCED_MOVE_HUE_COMMAND_ID;
      cmd->payload.enhancedMoveHue.moveMode = (BUTTON_LEFT == button) ?
          ZCL_ZLL_MOVE_HUE_MOVE_MODE_DOWN : ZCL_ZLL_MOVE_HUE_MOVE_MODE_UP;
      cmd->payload.enhancedMoveHue.rate = 20 << 8;
      cmd->size = sizeof(cmd->payload.enhancedMoveHue);
    }

    clustersSendCommand(cmd);
    return;
  }

  if (BUTTON_OK == button)
  {
    if (0 == alt)
    {
      cmd->clusterId = LEVEL_CONTROL_CLUSTER_ID;
      cmd->commandId = ZCL_LEVEL_CONTROL_CLUSTER_STOP_COMMAND_ID;
      clustersSendCommand(cmd);
      return;
    }
    else if (1 == alt)
    {
      cmd->clusterId = COLOR_CONTROL_CLUSTER_ID;
      cmd->commandId = STOP_MOVE_STEP_COMMAND_ID;
      clustersSendCommand(cmd);
      return;
    }
    else if (2 == alt)
    {
    }
    else if (3 == alt)
    {
      cmd->clusterId = COLOR_CONTROL_CLUSTER_ID;
      cmd->commandId = ENHANCED_MOVE_HUE_COMMAND_ID;
      cmd->payload.enhancedMoveHue.moveMode = ZCL_ZLL_MOVE_HUE_MOVE_MODE_STOP;
      cmd->payload.enhancedMoveHue.rate = 0;
      cmd->size = sizeof(cmd->payload.enhancedMoveHue);
      clustersSendCommand(cmd);
      return;
    }
  }

  clustersFreeCommand(cmd);
#else
 (void)button, (void)time, (void)alt;
#endif
}

#endif // APP_ZLL_DEVICE_TYPE == APP_DEVICE_TYPE_COLOR_SCENE_REMOTE

// eof buttonHandlers.c
