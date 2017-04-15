/**************************************************************************//**
  \file thDiagnosticsCluster.c

  \brief
    Thermostat Diagnostics cluster implementation.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    14.11.14 Parthasarathy G - Created.
******************************************************************************/
#ifdef APP_DEVICE_TYPE_THERMOSTAT

/******************************************************************************
                    Includes section
******************************************************************************/
#include <haClusters.h>
#include <uartManager.h>
#include <commandManager.h>
#include <pdsDataServer.h>
#include <zclDevice.h>
#include <ezModeManager.h>
#include <thDiagnosticsCluster.h>

/******************************************************************************
                    Definition(s) section
******************************************************************************/


/******************************************************************************
                    Prototypes section
******************************************************************************/
static void thDiagnosticsEventListener(SYS_EventId_t eventId, SYS_EventData_t data);

/******************************************************************************
                    Global variables section
******************************************************************************/
ZCL_DiagnosticsClusterServerAttributes_t thDiagnosticsClusterServerAttributes =
{
  ZCL_DEFINE_DIAGNOSTICS_CLUSTER_SERVER_ATTRIBUTES()
};

/******************************************************************************
                    Static variables section
******************************************************************************/
static SYS_EventReceiver_t thEventReceiver = { .func = thDiagnosticsEventListener};
/******************************************************************************
                    Implementation section
******************************************************************************/
/**************************************************************************//**
\brief Initializes diagnostics cluster
******************************************************************************/
void diagnosticsClusterInit(void)
{
  thDiagnosticsClusterServerAttributes.averageMACRetryPerAPSMessageSent.value = 0;
  thDiagnosticsClusterServerAttributes.lastMessageLQI.value = 0;
  thDiagnosticsClusterServerAttributes.lastMessageRSSI.value = 0;
  SYS_SubscribeToEvent(BC_EVENT_APS_DATA_INDICATION, &thEventReceiver);
  SYS_SubscribeToEvent(BC_EVENT_NWK_DATA_CONFIRM, &thEventReceiver);
}

static void thDiagnosticsEventListener(SYS_EventId_t eventId, SYS_EventData_t data)
{
  switch(eventId)
  {
    case BC_EVENT_APS_DATA_INDICATION:
      if(NULL != (APS_DataQualityIndicator_t *)data)
      {
        APS_DataQualityIndicator_t *apsDataQualityIndicator = (APS_DataQualityIndicator_t *)data;
        thDiagnosticsClusterServerAttributes.lastMessageLQI.value = apsDataQualityIndicator->linkQuality;
        thDiagnosticsClusterServerAttributes.lastMessageRSSI.value = apsDataQualityIndicator->rssi;
      }
      break;

    case BC_EVENT_NWK_DATA_CONFIRM:
      if(NULL != (uint16_t*)data)
      {
        static bool firstPacket = 1;
        if(firstPacket)
        {
          thDiagnosticsClusterServerAttributes.averageMACRetryPerAPSMessageSent.value
            = *(uint16_t*)data;
          firstPacket = 0;
        }
        else
        {
          thDiagnosticsClusterServerAttributes.averageMACRetryPerAPSMessageSent.value
            = (thDiagnosticsClusterServerAttributes.averageMACRetryPerAPSMessageSent.value 
              + *(uint16_t*)data) / 2;
        }
      }
      break;
    default:
      break;
  }
}
#endif // APP_DEVICE_TYPE_THERMOSTAT

// eof thDiagnosticsCluster.c

