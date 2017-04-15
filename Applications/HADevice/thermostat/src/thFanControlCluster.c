/**************************************************************************//**
  \file thFanControlCluster.c

  \brief
    Thermostat Fan Control cluster implementation.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    06.11.14 Viswanadham Kotla - Created.
******************************************************************************/
#ifdef APP_DEVICE_TYPE_THERMOSTAT

/******************************************************************************
                    Includes section
******************************************************************************/
#include <thfanControlCluster.h>
#if APP_ENABLE_CONSOLE == 1
#include <uartManager.h>
#endif
#include <commandManager.h>
#include <zclAttributes.h>
#include <haClusters.h>

/******************************************************************************
                    Global variables
******************************************************************************/
ZCL_FanControlClusterServerAttributes_t thFanControlClusterServerAttributes =
{
  ZCL_DEFINE_FAN_CONTROL_CLUSTER_SERVER_ATTRIBUTES()
};

/******************************************************************************
                    Prototypes section
******************************************************************************/

static void thFanControlAttrEventInd(ZCL_Addressing_t *addressing, ZCL_AttributeId_t attributeId, ZCL_AttributeEvent_t event);
static void thFanControlEventListener(SYS_EventId_t eventId, SYS_EventData_t data);
static void thFanControlsetFanOnOff(ZCL_FanControlFanMode_t fanState);

/******************************************************************************
                    Local variables
******************************************************************************/
static SYS_EventReceiver_t thFanControlEvent = { .func = thFanControlEventListener};
static ZCL_FanControlFanMode_t fanMotorControl = ZCL_FC_FAN_MODE_OFF;
/*****************************************************************************/

/******************************************************************************
                    Implementation section
******************************************************************************/
/**************************************************************************//**
\brief Initializes Fan Control cluster
******************************************************************************/
void fanControlClusterInit(void)
{
  ZCL_Cluster_t *cluster = ZCL_GetCluster(APP_SRC_ENDPOINT_ID, FAN_CONTROL_CLUSTER_ID, ZCL_CLUSTER_SIDE_SERVER);  

  if (cluster)
  {
    cluster->ZCL_AttributeEventInd = thFanControlAttrEventInd;
  }
  thFanControlClusterServerAttributes.fanMode.value = ZCL_FAN_CONTROL_CL_FAN_MODE_SER_ATTR_DEFAULT_VAL;
  thFanControlClusterServerAttributes.fanModeSequence.value = ZCL_FAN_CONTROL_CL_FAN_SEQUENCE_OPERATION_SER_ATTR_DEFAULT_VAL;
  SYS_SubscribeToEvent(BC_ZCL_EVENT_ACTION_REQUEST, &thFanControlEvent);
}

/**************************************************************************//**
\brief Attribute Event indication handler(to indicate when attr values have
        read or written)

\param[in] addressing - pointer to addressing information;
\param[in] reportLength - data payload length;
\param[in] reportPayload - data pointer
******************************************************************************/
static void thFanControlAttrEventInd(ZCL_Addressing_t *addressing, ZCL_AttributeId_t attributeId, ZCL_AttributeEvent_t event)
{
#if APP_ENABLE_CONSOLE == 1
  LOG_STRING(AttrEventIndStr, "<-Attr ID 0x%x event 0x%x\r\n");
  appSnprintf(AttrEventIndStr, attributeId, event);
#endif
  if ( (attributeId == ZCL_FAN_CONTROL_CLUSTER_FAN_MODE_SERVER_ATTRIBUTE_ID) 
           && (event == ZCL_WRITE_ATTRIBUTE_EVENT) )
  {
    switch(thFanControlClusterServerAttributes.fanMode.value)
    {
      case ZCL_FC_FAN_MODE_LOW:
      case ZCL_FC_FAN_MODE_MEDIUM:
      case ZCL_FC_FAN_MODE_HIGH:
        fanMotorControl = thFanControlClusterServerAttributes.fanMode.value;
        break;
      case ZCL_FC_FAN_MODE_AUTO:
        /*Specification does not define this case, hence setting it to medium
        User may change for actual fan control*/
        fanMotorControl = ZCL_FC_FAN_MODE_MEDIUM;      
        break;
      case ZCL_FC_FAN_MODE_OFF:
      case ZCL_FC_FAN_MODE_ON:
        thFanControlsetFanOnOff(thFanControlClusterServerAttributes.fanMode.value);
        break;
    }
  }
  (void)addressing;
}

/**************************************************************************//**
  \brief  ZCL action request event handler, 
          handles the ZCL_ACTION_WRITE_ATTR_REQUEST for attribute specific validation

  \param[in] ev - must be BC_ZCL_EVENT_ACTION_REQUEST.
  \param[in] data - this field must contain pointer to the BcZCLActionReq_t structure,

  \return None.
 ******************************************************************************/
static void thFanControlEventListener(SYS_EventId_t eventId, SYS_EventData_t data)
{
  BcZCLActionReq_t *const actionReq = (BcZCLActionReq_t*)data;  
  ZCL_FanControlFanMode_t requestedValue = 0;

  if (BC_ZCL_EVENT_ACTION_REQUEST != eventId)
    return;
  
  if (ZCL_ACTION_WRITE_ATTR_REQUEST != actionReq->action)
    return;

  ZCLActionWriteAttrReq_t *const zclWriteAttrReq = (ZCLActionWriteAttrReq_t*)actionReq->context;
  if( (FAN_CONTROL_CLUSTER_ID != zclWriteAttrReq->clusterId) || 
          (ZCL_CLUSTER_SIDE_SERVER != zclWriteAttrReq->clusterSide))
    return;

  requestedValue = *((uint8_t*)(zclWriteAttrReq->attrValue));
  if(ZCL_FAN_CONTROL_CLUSTER_FAN_MODE_SERVER_ATTRIBUTE_ID != zclWriteAttrReq->attrId)
    return;

  switch(thFanControlClusterServerAttributes.fanModeSequence.value)
  {
    case ZCL_FC_FAN_SEQUENCE_OPERATION_LOW_MED_HIGH:
      if(ZCL_FC_FAN_MODE_AUTO == requestedValue)
        actionReq->denied = 1U;
      break;
    case ZCL_FC_FAN_SEQUENCE_OPERATION_LOW_HIGH:
      if((ZCL_FC_FAN_MODE_AUTO == requestedValue) || (ZCL_FC_FAN_MODE_MEDIUM == requestedValue))
        actionReq->denied = 1U;
      break;
    case ZCL_FC_FAN_SEQUENCE_OPERATION_LOW_MED_HIGH_AUTO:
      actionReq->denied = 0U;
      break;
    case ZCL_FC_FAN_SEQUENCE_OPERATION_LOW_HIGH_AUTO:
      if(ZCL_FC_FAN_MODE_MEDIUM == requestedValue)
        actionReq->denied = 1U;
      break;
    case ZCL_FC_FAN_SEQUENCE_OPERATION_ON_AUTO:
      if(ZCL_FC_FAN_MODE_AUTO != requestedValue)
        actionReq->denied = 1U;
      break;
    default:
      actionReq->denied = 0U;
      break;
  }
}

/**************************************************************************//**
\brief Occupancy notification from Occupancy (client/server) cluster

\param[in] occupied - 0 - Not occupied, 1- occupied
\param[out] - None
******************************************************************************/
void thFanControlOccupancyNotify(bool occupied)
{
  if(ZCL_FC_FAN_MODE_SMART == thFanControlClusterServerAttributes.fanMode.value)
  {
    if(occupied)    thFanControlsetFanOnOff(ZCL_FC_FAN_MODE_ON);
    else    thFanControlsetFanOnOff(ZCL_FC_FAN_MODE_OFF);
  }
}

/**************************************************************************//**
\brief Set the fan to ON or OFF (need to modified by the user)

\param[in] fanState : 0 - off, non zero - ON
\param[out] - None
******************************************************************************/
static void thFanControlsetFanOnOff(ZCL_FanControlFanMode_t fanState)
{ 
  /*The user has to implement the functionality to control the actual fan*/
  if(fanState)
  {
#if APP_ENABLE_CONSOLE == 1
    LOG_STRING(AttrEventIndStr,"Fan is turned ON at speed 0x%x\r\n");
    appSnprintf(AttrEventIndStr,fanMotorControl);
#else
    (void)fanMotorControl;
#endif
  }
#if APP_ENABLE_CONSOLE == 1
  else
    appSnprintf("Fan is turned OFF\r\n");
#endif
}
#endif // APP_DEVICE_TYPE_THERMOSTAT

// eof thFanControlCluster.c
