/**************************************************************************//**
  \file thOccupancySensingCluster.c

  \brief
    Thermostat Occupancy Sensing cluster implementation.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    17.10.14 Viswanadham Kotla - Created.
******************************************************************************/
#if defined APP_DEVICE_TYPE_THERMOSTAT

/******************************************************************************
                    Includes section
******************************************************************************/
#include <thOccupancySensingCluster.h>
#include <thFanControlCluster.h>
#include <commandManager.h>
#include <uartManager.h>


/******************************************************************************
                             Defines section
******************************************************************************/
#define MOVEMENT_DETECTION_PERIOD                       2000UL
#define AMOUNT_MSEC_IN_SEC                              1000UL
#define NO_OF_MOVEMENT_DETECTION_EVENTS_ALLOWED         7U

/******************************************************************************
                    Global variables
******************************************************************************/
ZCL_OccupancySensingClusterServerAttributes_t thOccupancySensingClusterServerAttributes =
{
  ZCL_DEFINE_OCCUPANCY_SENSING_CLUSTER_SERVER_ATTRIBUTES(OCCUPANCY_SENSING_VAL_MIN_REPORT_PERIOD, OCCUPANCY_SENSING_VAL_MAX_REPORT_PERIOD)
};

/*******************************************************************************
                   Types section
*******************************************************************************/
typedef enum
{
  OCCUPANCY_CHANGE_STATE_IDLE,
  OCCUPANCY_CHANGE_STATE_OCCUPIED_TO_UNOCCUPIED_IN_PROGRESS,
  OCCUPANCY_CHANGE_STATE_UNOCCUPIED_TO_OCCUPIED_IN_PROGRESS,
} OccupancyChangeState_t;

/******************************************************************************
                    Static functions
******************************************************************************/
static void occupancySensingSetOccupancyState(void);
static void ZCL_ReadAttributeResp(ZCL_Notify_t *ntfy);
static void ZCL_WriteAttributeResp(ZCL_Notify_t *ntfy);
static void ZCL_ConfigureReportingResp(ZCL_Notify_t *ntfy);
static void thOccupancySensorReportInd(ZCL_Addressing_t *addressing, uint8_t reportLength, uint8_t *reportPayload);
static void occupiedToUnoccupiedHandler(void);
static void unoccupiedToOccupiedHandler(void);
static void movementDetected(void);
static bool verifyOccupancySensorDetection(bool state);

/******************************************************************************
                    Static variables
******************************************************************************/
static HAL_AppTimer_t sensorAttributeUpdateTimer;
static AttibuteReadCallback_t   readAttributeCallback;
static AttributeWriteCallback_t writeAttributeCallback;
static uint8_t occupancyChangeState = OCCUPANCY_CHANGE_STATE_IDLE;
static uint64_t delayStartTime = 0;
static uint8_t eventCount = 0;
static uint8_t threshold;
static uint16_t delay;

static HAL_AppTimer_t movementEventTimer =
{
  .interval = MOVEMENT_DETECTION_PERIOD,
  .mode     = TIMER_REPEAT_MODE,
  .callback = movementDetected,
};

/******************************************************************************
                    Implementation section
******************************************************************************/
/**************************************************************************//**
\brief Initializes Occupancy Sensing cluster
******************************************************************************/
void occupancySensingClusterInit(void)
{
  ZCL_Cluster_t *cluster = ZCL_GetCluster(APP_SRC_ENDPOINT_ID, OCCUPANCY_SENSING_CLUSTER_ID, ZCL_CLUSTER_SIDE_CLIENT);

  if (cluster)
    cluster->ZCL_ReportInd = thOccupancySensorReportInd;

  cluster = ZCL_GetCluster(APP_SRC_ENDPOINT_ID, OCCUPANCY_SENSING_CLUSTER_ID, ZCL_CLUSTER_SIDE_SERVER);
  
  if (cluster)
  {
    thOccupancySensingClusterServerAttributes.occupancySensorType.value = OCCUPANYC_SENSOR_TYPE_ATTRIBUTE_VALUE_PIR;
    thOccupancySensingClusterServerAttributes.occupancy.value = OCCUPANCY_ATTRIBUTE_VALUE_UNOCCUPIED;

    ZCL_ReportOnChangeIfNeeded(&thOccupancySensingClusterServerAttributes.occupancy);

    thOccupancySensingClusterServerAttributes.PIROccupiedToUnoccupiedDelay.value = ZCL_OCCUPANCY_SENSING_CL_PIR_OCCUPIED_TO_UNOCCUPIED_DELAY_SER_ATTR_DEFAULT_VAL;
    thOccupancySensingClusterServerAttributes.PIRUnoccupiedToOccupiedDelay.value = ZCL_OCCUPANCY_SENSING_CL_PIR_UNOCCUPIED_TO_OCCUPIED_DELAY_SER_ATTR_DEFAULT_VAL;
    thOccupancySensingClusterServerAttributes.PIRUnoccupiedToOccupiedThreshold.value = ZCL_OCCUPANCY_SENSING_CL_PIR_UNOCCUPIED_TO_OCCUPIED_THRESHOLD_SER_ATTR_DEFAULT_VAL;

    thOccupancySensingClusterServerAttributes.UltrasonicOccupiedToUnoccupiedDelay.value = ZCL_OCCUPANCY_SENSING_CL_ULTRASONIC_OCCUPIED_TO_UNOCCUPIED_DELAY_SER_ATTR_DEFAULT_VAL;
    thOccupancySensingClusterServerAttributes.UltrasonicUnoccupiedToOccupiedDelay.value = ZCL_OCCUPANCY_SENSING_CL_ULTRASONIC_UNOCCUPIED_TO_OCCUPIED_DELAY_SER_ATTR_DEFAULT_VAL;
    thOccupancySensingClusterServerAttributes.UltrasonicUnoccupiedToOccupiedThreshold.value = ZCL_OCCUPANCY_SENSING_CL_ULTRASONIC_UNOCCUPIED_TO_OCCUPIED_THRESHOLD_SER_ATTR_DEFAULT_VAL;
  }
}

/**************************************************************************//**
\brief Initiates occupancy to Occupied state or Unoccupied state otr vice versa
******************************************************************************/
void occupancySensingInitiateSetOccupancyState(bool state)
{
  if (OCCUPANCY_CHANGE_STATE_IDLE == occupancyChangeState)
  {
    if (OCCUPANCY_ATTRIBUTE_VALUE_UNOCCUPIED == state)
      occupiedToUnoccupiedHandler();
    else
      unoccupiedToOccupiedHandler();
  }
  else
    /* Consider this as movement event detetced from sensor */
    verifyOccupancySensorDetection(state);

}

/***************************************************************************//**
\brief checks the detected movement whether Occupied to Unoccupied or Unoccupied to Occupied
******************************************************************************/
static bool verifyOccupancySensorDetection(bool state)
{
  /* check the occupancy state detected */
  switch(occupancyChangeState)
  {
    case OCCUPANCY_CHANGE_STATE_OCCUPIED_TO_UNOCCUPIED_IN_PROGRESS:
      if (state)
      {
        HAL_StopAppTimer(&sensorAttributeUpdateTimer);
        occupancyChangeState = OCCUPANCY_CHANGE_STATE_IDLE;
      }
      break;
    case OCCUPANCY_CHANGE_STATE_UNOCCUPIED_TO_OCCUPIED_IN_PROGRESS:
      if (!state)
      {
        HAL_StopAppTimer(&movementEventTimer);
        HAL_StopAppTimer(&sensorAttributeUpdateTimer);
        occupancyChangeState = OCCUPANCY_CHANGE_STATE_IDLE;
      }
      else
        return true;
      break;
  }
  return false;
}

/**************************************************************************//**
\brief Handler for changing the occupancy state from occupied to unoccupied
******************************************************************************/
static void occupiedToUnoccupiedHandler(void)
{
  occupancyChangeState = OCCUPANCY_CHANGE_STATE_OCCUPIED_TO_UNOCCUPIED_IN_PROGRESS;

  if (OCCUPANYC_SENSOR_TYPE_ATTRIBUTE_VALUE_PIR == thOccupancySensingClusterServerAttributes.occupancySensorType.value)
  {
    if (!thOccupancySensingClusterServerAttributes.PIROccupiedToUnoccupiedDelay.value)
    {
      occupancySensingSetOccupancyState();
      return;
    }
    else
      sensorAttributeUpdateTimer.interval = thOccupancySensingClusterServerAttributes.PIROccupiedToUnoccupiedDelay.value * AMOUNT_MSEC_IN_SEC;//msec
  }
  else if (OCCUPANYC_SENSOR_TYPE_ATTRIBUTE_VALUE_ULTRASONIC == thOccupancySensingClusterServerAttributes.occupancySensorType.value)
  {
    if (!thOccupancySensingClusterServerAttributes.UltrasonicOccupiedToUnoccupiedDelay.value)
      {
        occupancySensingSetOccupancyState();
        return;
      }
      else
        sensorAttributeUpdateTimer.interval = thOccupancySensingClusterServerAttributes.UltrasonicOccupiedToUnoccupiedDelay.value * AMOUNT_MSEC_IN_SEC;//msec
  }

  sensorAttributeUpdateTimer.mode     = TIMER_ONE_SHOT_MODE,
  sensorAttributeUpdateTimer.callback = occupancySensingSetOccupancyState,
  HAL_StartAppTimer(&sensorAttributeUpdateTimer);
}

/**************************************************************************//**
\brief Handler for changing the occupancy state from unoccupied to occupied 
******************************************************************************/
static void unoccupiedToOccupiedHandler(void)
{
  occupancyChangeState = OCCUPANCY_CHANGE_STATE_UNOCCUPIED_TO_OCCUPIED_IN_PROGRESS;

  if (OCCUPANYC_SENSOR_TYPE_ATTRIBUTE_VALUE_PIR == thOccupancySensingClusterServerAttributes.occupancySensorType.value)
  {
    if (!thOccupancySensingClusterServerAttributes.PIRUnoccupiedToOccupiedDelay.value && !thOccupancySensingClusterServerAttributes.PIRUnoccupiedToOccupiedThreshold.value)
    {
      occupancySensingSetOccupancyState();
      return;
    }
    else
    {
      delay = thOccupancySensingClusterServerAttributes.PIRUnoccupiedToOccupiedDelay.value;
      threshold = thOccupancySensingClusterServerAttributes.PIRUnoccupiedToOccupiedThreshold.value;
    }
  }
  else if (OCCUPANYC_SENSOR_TYPE_ATTRIBUTE_VALUE_ULTRASONIC == thOccupancySensingClusterServerAttributes.occupancySensorType.value)
  {
    if (!thOccupancySensingClusterServerAttributes.UltrasonicUnoccupiedToOccupiedDelay.value)
    {
      occupancySensingSetOccupancyState();
      return;
    }
    else
    {
      delay = thOccupancySensingClusterServerAttributes.UltrasonicUnoccupiedToOccupiedDelay.value;
      threshold = thOccupancySensingClusterServerAttributes.UltrasonicUnoccupiedToOccupiedThreshold.value;
    }
  }
  eventCount++; //this is considered as first movement detetcted
  delayStartTime = HAL_GetSystemTime();
  HAL_StartAppTimer(&movementEventTimer);
}

/**************************************************************************//**
\brief Simulation of occupied movement detection events (for every 2secs )

\param[in] resp - pointer to response
******************************************************************************/
static void movementDetected(void)
{
  uint64_t currentTime = 0;
  /* In general , this should be called on any kind of movement unoccupied to occupied
     or occcupied to unoccupied , but here only called on unoccipied to occupied movement 
     detection event only */
  /* API can added here to read sensor detection event - 0 to 1 or 1 to 0 */
  if (!verifyOccupancySensorDetection(1))
    return;

  if (++eventCount > (threshold & NO_OF_MOVEMENT_DETECTION_EVENTS_ALLOWED) - 1 )
  {
    HAL_StopAppTimer(&movementEventTimer);
    HAL_StopAppTimer(&sensorAttributeUpdateTimer);
    eventCount = 0;
    currentTime = HAL_GetSystemTime();
    if ((currentTime - delayStartTime)/AMOUNT_MSEC_IN_SEC >= delay )
    {
      occupancySensingSetOccupancyState();
    }
    else
    {
      /* remaining time before occupancy delay expires */
      sensorAttributeUpdateTimer.interval = delay * AMOUNT_MSEC_IN_SEC - (currentTime - delayStartTime);
      sensorAttributeUpdateTimer.mode     = TIMER_ONE_SHOT_MODE;
      sensorAttributeUpdateTimer.callback = occupancySensingSetOccupancyState;

      HAL_StartAppTimer(&sensorAttributeUpdateTimer);
    }
  }
}

/**************************************************************************//**
\brief Sets occupancy to Occupied state or Unoccupied state
******************************************************************************/
static void occupancySensingSetOccupancyState(void)
{
  thOccupancySensingClusterServerAttributes.occupancy.value = !(thOccupancySensingClusterServerAttributes.occupancy.value & 0x01);
  ZCL_ReportOnChangeIfNeeded(&thOccupancySensingClusterServerAttributes.occupancy);
  occupancyChangeState = OCCUPANCY_CHANGE_STATE_IDLE;
  eventCount = 0;
}

/**************************************************************************//**
\brief Sets occupancy to Occupied state or Unoccupied state
******************************************************************************/
void occupancySensingSetSensorType(uint8_t sensorType)
{
  if (thOccupancySensingClusterServerAttributes.occupancySensorType.value != sensorType)
  {
    thOccupancySensingClusterServerAttributes.occupancySensorType.value = sensorType;
    thOccupancySensingClusterServerAttributes.occupancy.value = OCCUPANCY_ATTRIBUTE_VALUE_UNOCCUPIED;
    HAL_StopAppTimer(&movementEventTimer);
    HAL_StopAppTimer(&sensorAttributeUpdateTimer);
    eventCount = 0;
  }
}

/**************************************************************************//**
\brief Sends Read Attribute command unicastly

\param[in] mode - address mode;
\param[in] addr - short address of destination node;
\param[in] ep   - destination endpoint;
\param[in] attr - attribute id;
\param[in] cb   - callback function
******************************************************************************/
void occupancySensingReadAttribute(APS_AddrMode_t mode,ShortAddr_t addr, Endpoint_t ep,
  uint16_t attr, AttibuteReadCallback_t cb)
{
  ZCL_Request_t *req;
  ZCL_NextElement_t element;
  ZCL_ReadAttributeReq_t readAttrReqElement;

  if (!(req = getFreeCommand()))
    return;

  readAttributeCallback = cb;

  readAttrReqElement.id = attr;

  element.payloadLength = 0;
  element.payload = req->requestPayload;
  element.id = ZCL_READ_ATTRIBUTES_COMMAND_ID;
  element.content = &readAttrReqElement;
  ZCL_PutNextElement(&element);

  fillCommandRequest(req, ZCL_READ_ATTRIBUTES_COMMAND_ID, element.payloadLength);
  fillDstAddressing(&req->dstAddressing, mode, addr, ep, OCCUPANCY_SENSING_CLUSTER_ID);
  req->ZCL_Notify = ZCL_ReadAttributeResp;

  commandManagerSendAttribute(req);
}

/**************************************************************************//**
\brief Sends Write Attribute command unicastly

\param[in] mode - address mode;
\param[in] addr - short address of destination node;
\param[in] attr - attribute id;
\param[in] ep   - destination endpoint;
\param[in] type - attribute type;
\param[in] cb   - callback function;
\param[in] data - the pointer to memory with value to be written;
\param[in] size - size of data parameter in octets
******************************************************************************/
void occupancySensingWriteAttribute(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep,
  uint16_t attr, uint8_t type, AttributeWriteCallback_t cb, void *data, uint8_t size)
{
  ZCL_Request_t *req;
  ZCL_WriteAttributeReq_t writeAttrReq;

  if (!(req = getFreeCommand()))
    return;

  writeAttributeCallback = cb;

  writeAttrReq.id = attr;
  writeAttrReq.type = type;
  memcpy(req->requestPayload, (uint8_t *)&writeAttrReq, sizeof(ZCL_WriteAttributeReq_t) - sizeof(uint8_t));
  memcpy(req->requestPayload + sizeof(ZCL_WriteAttributeReq_t) - sizeof(uint8_t), (uint8_t *)data, size);

  fillCommandRequest(req, ZCL_WRITE_ATTRIBUTES_COMMAND_ID, size + sizeof(ZCL_WriteAttributeReq_t) - sizeof(uint8_t));
  fillDstAddressing(&req->dstAddressing, mode, addr, ep, OCCUPANCY_SENSING_CLUSTER_ID);
  req->ZCL_Notify = ZCL_WriteAttributeResp;

  commandManagerSendAttribute(req);
}

/**************************************************************************//**
\brief Sends the Configure Reporting for Occupancy Sensing cluster

\param[in] mode - address mode;
\param[in] addr - short address of destination node;
\param[in] ep   - destination endpoint;
\param[in] min  - the minimum reporting interval;
\param[in] max  - the maximum reporting interval
******************************************************************************/
void occupancySensingConfigureReporting(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep,
  ZCL_AttributeId_t attrId, uint8_t attrType, ZCL_ReportTime_t min, ZCL_ReportTime_t max)
{
  ZCL_Request_t *req;
  ZCL_NextElement_t element;
  ZCL_ConfigureReportingReq_t configureReportingReq;

  if (!(req = getFreeCommand()))
    return;

  configureReportingReq.direction            = ZCL_FRAME_CONTROL_DIRECTION_CLIENT_TO_SERVER;
  configureReportingReq.attributeId          = attrId;
  configureReportingReq.attributeType        = attrType;
  configureReportingReq.minReportingInterval = min;
  configureReportingReq.maxReportingInterval = max;

  element.payloadLength = 0;
  element.payload = req->requestPayload;
  element.id = ZCL_CONFIGURE_REPORTING_COMMAND_ID;
  element.content = &configureReportingReq;
  ZCL_PutNextElement(&element);

  fillCommandRequest(req, ZCL_CONFIGURE_REPORTING_COMMAND_ID, element.payloadLength);
  fillDstAddressing(&req->dstAddressing, mode, addr, ep, OCCUPANCY_SENSING_CLUSTER_ID);
  req->ZCL_Notify = ZCL_ConfigureReportingResp;

  commandManagerSendAttribute(req);
}

/**************************************************************************//**
\brief Report attribute indication handler

\param[in] addressing - pointer to addressing information;
\param[in] reportLength - data payload length;
\param[in] reportPayload - data pointer
******************************************************************************/
static void thOccupancySensorReportInd(ZCL_Addressing_t *addressing, uint8_t reportLength, uint8_t *reportPayload)
{
  ZCL_Report_t *rep = (ZCL_Report_t *)reportPayload;

  LOG_STRING(reportAttrIndStr, "<-Occupancy Sensor Attr Report: t = %d\r\n");
  appSnprintf(reportAttrIndStr, (uint8_t)rep->value[0]);

  thFanControlOccupancyNotify((bool)rep->value[0]);
  (void)addressing, (void)reportLength, (void)rep;
}

/**************************************************************************//**
\brief Indication of read attribute response

\param[in] resp - pointer to response
******************************************************************************/
static void ZCL_ReadAttributeResp(ZCL_Notify_t *ntfy)
{
  ZCL_NextElement_t element;
  ZCL_ReadAttributeResp_t *readAttributeResp;

  if (ZCL_SUCCESS_STATUS == ntfy->status)
  {
    element.id            = ZCL_READ_ATTRIBUTES_RESPONSE_COMMAND_ID;
    element.payloadLength = ntfy->responseLength;
    element.payload       = ntfy->responsePayload;
    element.content       = NULL;

    ZCL_GetNextElement(&element);
    readAttributeResp = (ZCL_ReadAttributeResp_t *) element.content;

    if (readAttributeCallback)
      readAttributeCallback((void *)&readAttributeResp->value[0]);

    LOG_STRING(readAttrSuccessStr, " <-Read Occupancy Sensing attribute (0x%x) response: success t = %u\r\n");
    appSnprintf(readAttrSuccessStr, (unsigned)readAttributeResp->id, *((uint8_t*)&readAttributeResp->value[0]));
  }
  else
  {
    LOG_STRING(readAttrFailStr, " +Read Occupancy Sensing attribute failed: status = 0x%2x\r\n");
    appSnprintf(readAttrFailStr, (unsigned)ntfy->status);
  }
}

/**************************************************************************//**
\brief Indication of write attribute response

\param[in] resp - pointer to response
******************************************************************************/
static void ZCL_WriteAttributeResp(ZCL_Notify_t *ntfy)
{
  if (ZCL_SUCCESS_STATUS == ntfy->status)
  {
    if (writeAttributeCallback)
      writeAttributeCallback();

    LOG_STRING(writeAttrSuccessStr, " <-Write Occupancy Sensing attribute response: success\r\n");
    appSnprintf(writeAttrSuccessStr);
  }
  else
  {
    LOG_STRING(writeAttrFailStrTwo, " +Write Occupancy Sensing attribute failed: status = 0x%x\r\n");
    appSnprintf(writeAttrFailStrTwo, (unsigned)ntfy->status);
  }
}

/**************************************************************************//**
\brief Indication of configure reporting response

\param[in] resp - pointer to response
******************************************************************************/
static void ZCL_ConfigureReportingResp(ZCL_Notify_t *ntfy)
{
  (void)ntfy;
}

#endif // APP_DEVICE_TYPE_THERMOSTAT

// eof thOccupancySensingCluster.c
