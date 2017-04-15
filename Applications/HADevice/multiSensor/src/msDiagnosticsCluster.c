/**************************************************************************//**
  \file msDiagnosticsCluster.c

  \brief
    Multi-Sensor Diagnostics cluster implementation.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    11.11.14 Parthasarathy G - Created.
******************************************************************************/
#ifdef APP_DEVICE_TYPE_MULTI_SENSOR

/******************************************************************************
                    Includes section
******************************************************************************/
#include <haClusters.h>
#include <uartManager.h>
#include <commandManager.h>
#include <pdsDataServer.h>
#include <zclDevice.h>
#include <ezModeManager.h>
#include <msDiagnosticsCluster.h>

/******************************************************************************
                    Definition(s) section
******************************************************************************/


/******************************************************************************
                    Prototypes section
******************************************************************************/
static void msDiagnosticsEventListener(SYS_EventId_t eventId, SYS_EventData_t data);

/******************************************************************************
                    Global variables section
******************************************************************************/
ZCL_DiagnosticsClusterServerAttributes_t msDiagnosticsClusterServerAttributes =
{
  ZCL_DEFINE_DIAGNOSTICS_CLUSTER_SERVER_ATTRIBUTES()
};

/******************************************************************************
                    Static variables section
******************************************************************************/
static SYS_EventReceiver_t msEventReceiver = { .func = msDiagnosticsEventListener};
/******************************************************************************
                    Implementation section
******************************************************************************/
/**************************************************************************//**
\brief Initializes diagnostics cluster
******************************************************************************/
void diagnosticsClusterInit(void)
{
  msDiagnosticsClusterServerAttributes.averageMACRetryPerAPSMessageSent.value = 0;
  msDiagnosticsClusterServerAttributes.lastMessageLQI.value = 0;
  msDiagnosticsClusterServerAttributes.lastMessageRSSI.value = 0;
  SYS_SubscribeToEvent(BC_EVENT_APS_DATA_INDICATION, &msEventReceiver);
  SYS_SubscribeToEvent(BC_EVENT_NWK_DATA_CONFIRM, &msEventReceiver);
}

static void msDiagnosticsEventListener(SYS_EventId_t eventId, SYS_EventData_t data)
{
  switch(eventId)
  {
    case BC_EVENT_APS_DATA_INDICATION:
      if(NULL != (APS_DataQualityIndicator_t *)data)
      {
        APS_DataQualityIndicator_t *apsDataQualityIndicator = (APS_DataQualityIndicator_t *)data;
        msDiagnosticsClusterServerAttributes.lastMessageLQI.value = apsDataQualityIndicator->linkQuality;
        msDiagnosticsClusterServerAttributes.lastMessageRSSI.value = apsDataQualityIndicator->rssi;
      }
      break;

    case BC_EVENT_NWK_DATA_CONFIRM:
      if(NULL != (uint16_t*)data)
      {
        static bool firstPacket = 1;
        if(firstPacket)
        {
          msDiagnosticsClusterServerAttributes.averageMACRetryPerAPSMessageSent.value
            = *(uint16_t*)data;
          firstPacket = 0;
        }
        else
        {
          msDiagnosticsClusterServerAttributes.averageMACRetryPerAPSMessageSent.value
            = (msDiagnosticsClusterServerAttributes.averageMACRetryPerAPSMessageSent.value 
              + *(uint16_t*)data) / 2;
        }
      }
      break;
    default:
      break;
  }
}
#endif // APP_DEVICE_TYPE_MULTI_SENSOR

// eof msDiagnosticsCluster.c

