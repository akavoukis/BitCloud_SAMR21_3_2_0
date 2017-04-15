/**************************************************************************//**
  \file iasACEDiagnosticsCluster.c

  \brief
    IAS ACE Diagnostics cluster implementation.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    18/11/2014 Yogesh- Created.
******************************************************************************/
#ifdef APP_DEVICE_TYPE_IAS_ACE

/******************************************************************************
                    Includes section
******************************************************************************/
#include <haClusters.h>
#include <uartManager.h>
#include <commandManager.h>
#include <pdsDataServer.h>
#include <zclDevice.h>
#include <ezModeManager.h>
#include <iasACEDiagnosticsCluster.h>

/******************************************************************************
                    Definition(s) section
******************************************************************************/


/******************************************************************************
                    Prototypes section
******************************************************************************/
static void iasACEDiagnosticsEventListener(SYS_EventId_t eventId, SYS_EventData_t data);

/******************************************************************************
                    Global variables section
******************************************************************************/
ZCL_DiagnosticsClusterServerAttributes_t iasACEDiagnosticsClusterServerAttributes =
{
  ZCL_DEFINE_DIAGNOSTICS_CLUSTER_SERVER_ATTRIBUTES()
};

/******************************************************************************
                    Static variables section
******************************************************************************/
static SYS_EventReceiver_t iasACEEventReceiver = { .func = iasACEDiagnosticsEventListener};
/******************************************************************************
                    Implementation section
******************************************************************************/
/**************************************************************************//**
\brief Initializes diagnostics cluster
******************************************************************************/
void diagnosticsClusterInit(void)
{
  iasACEDiagnosticsClusterServerAttributes.averageMACRetryPerAPSMessageSent.value = 0;
  iasACEDiagnosticsClusterServerAttributes.lastMessageLQI.value = 0;
  iasACEDiagnosticsClusterServerAttributes.lastMessageRSSI.value = 0;
  SYS_SubscribeToEvent(BC_EVENT_APS_DATA_INDICATION, &iasACEEventReceiver);
  SYS_SubscribeToEvent(BC_EVENT_NWK_DATA_CONFIRM, &iasACEEventReceiver);
}

/**************************************************************************//**
\brief Initializes diagnostics cluster
\param[in] eventId - eventId list for Diagnostic Cluster
\param[in] data - data associated to Diagnostic CLuster Event Id
******************************************************************************/
static void iasACEDiagnosticsEventListener(SYS_EventId_t eventId, SYS_EventData_t data)
{
  switch(eventId)
  {
    case BC_EVENT_APS_DATA_INDICATION:
      if(NULL != (APS_DataQualityIndicator_t *) data)
      {
        APS_DataQualityIndicator_t *apsDataQualityIndicator = (APS_DataQualityIndicator_t *)data;
        iasACEDiagnosticsClusterServerAttributes.lastMessageLQI.value = apsDataQualityIndicator->linkQuality;
        iasACEDiagnosticsClusterServerAttributes.lastMessageRSSI.value = apsDataQualityIndicator->rssi;
      }
      break;

    case BC_EVENT_NWK_DATA_CONFIRM:
      if(NULL != (uint16_t*) data)
      {
        static bool firstPacket = 1;
        if(firstPacket)
        {
          iasACEDiagnosticsClusterServerAttributes.averageMACRetryPerAPSMessageSent.value
            = *(uint16_t*)data;
          firstPacket = 0;
        }
        else
        {
          iasACEDiagnosticsClusterServerAttributes.averageMACRetryPerAPSMessageSent.value
            = (iasACEDiagnosticsClusterServerAttributes.averageMACRetryPerAPSMessageSent.value 
              + *(uint16_t*)data) / 2;
        }
      }
      break;
    default:
      break;
  }
}
#endif // APP_DEVICE_TYPE_IAS_ACE

// eof iasACEDiagnosticsCluster.c

