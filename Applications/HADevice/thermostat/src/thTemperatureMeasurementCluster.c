/**************************************************************************//**
  \file thTemperatureMeasurementCluster.c

  \brief
    Thermostat Temperature Measurement cluster implementation.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    21.11.14 Parthasarathy G - Created.
******************************************************************************/
#if defined APP_DEVICE_TYPE_THERMOSTAT

/******************************************************************************
                    Includes section
******************************************************************************/
#include <thTemperatureMeasurementCluster.h>
#include <uartManager.h>
#include <commandManager.h>

/******************************************************************************
                    Definition(s) section
******************************************************************************/
#define TEMPERATURE_REPORT_PERIOD   20000UL

/******************************************************************************
                    Global variables
******************************************************************************/
ZCL_TemperatureMeasurementClusterAttributes_t thTemperatureMeasurementClusterServerAttributes =
{
  ZCL_DEFINE_TEMPERATURE_MEASUREMENT_CLUSTER_SERVER_ATTRIBUTES(TEMPERATURE_MEASUREMENT_VAL_MIN_REPORT_PERIOD, TEMPERATURE_MEASUREMENT_VAL_MAX_REPORT_PERIOD)
};

/******************************************************************************
                    Local variables section
******************************************************************************/
static AttibuteReadCallback_t   readAttributeCallback;
static AttributeWriteCallback_t writeAttributeCallback;

static HAL_AppTimer_t readTemperatureimer =
{
  .interval = TEMPERATURE_REPORT_PERIOD,
  .mode     = TIMER_REPEAT_MODE,
  .callback = thTempeartureMeasurementUpdateMeasuredValue,
};

/******************************************************************************
                    Prototypes section
******************************************************************************/
static void ZCL_ReadAttributeResp(ZCL_Notify_t *ntfy);
static void ZCL_WriteAttributeResp(ZCL_Notify_t *ntfy);

static void thTemperatureMeasurementReportInd(ZCL_Addressing_t *addressing, uint8_t reportLength, uint8_t *reportPayload);
static void ZCL_ConfigureReportingResp(ZCL_Notify_t *ntfy);

/******************************************************************************
                    Implementation section
******************************************************************************/
/**************************************************************************//**
\brief Initializes Temperature Measurement cluster
******************************************************************************/
void thTemperatureMeasurementClusterInit(void)
{
  ZCL_Cluster_t *cluster = ZCL_GetCluster(APP_SRC_ENDPOINT_ID, TEMPERATURE_MEASUREMENT_CLUSTER_ID, ZCL_CLUSTER_SIDE_CLIENT);

  if (cluster)
    cluster->ZCL_ReportInd = thTemperatureMeasurementReportInd;

  cluster = ZCL_GetCluster(APP_SRC_ENDPOINT_ID, TEMPERATURE_MEASUREMENT_CLUSTER_ID, ZCL_CLUSTER_SIDE_SERVER);

  if (cluster)
  {
    thTemperatureMeasurementClusterServerAttributes.measuredValue.value = APP_TEMPERATURE_MEASUREMENT_MEASURED_VALUE_ATTRIBUTE_VALUE;
    thTemperatureMeasurementClusterServerAttributes.minMeasuredValue.value = APP_TEMPERATURE_MEASUREMENT_MIN_MEASURED_VALUE_ATTRIBUTE_VALUE;
    thTemperatureMeasurementClusterServerAttributes.maxMeasuredValue.value = APP_TEMPERATURE_MEASUREMENT_MAX_MEASURED_VALUE_ATTRIBUTE_VALUE;
    thTemperatureMeasurementClusterServerAttributes.tolerance.value = APP_TEMPERATURE_MEASUREMENT_TOLERANCE_ATTRIBUTE_VALUE;//to be updated
    HAL_StartAppTimer(&readTemperatureimer);
  }
}

/**************************************************************************//**
\brief Update the measured Value
******************************************************************************/
void thTempeartureMeasurementUpdateMeasuredValue(void)
{
  int16_t measuredValue;

  measuredValue = thTemperatureMeasurementClusterServerAttributes.measuredValue.value - APP_TEMPERATURE_MEASUREMENT_MEASURED_VALUE_PERIODIC_CHANGE;

  if (measuredValue < thTemperatureMeasurementClusterServerAttributes.minMeasuredValue.value)
    thTemperatureMeasurementClusterServerAttributes.measuredValue.value =  thTemperatureMeasurementClusterServerAttributes.maxMeasuredValue.value;
  else
    thTemperatureMeasurementClusterServerAttributes.measuredValue.value = measuredValue;

  ZCL_ReportOnChangeIfNeeded(&thTemperatureMeasurementClusterServerAttributes.measuredValue);
}

/**************************************************************************//**
\brief Update the tolerance value
******************************************************************************/
void thTempeartureMeasurementUpdateTolerance(void)
{
  thTemperatureMeasurementClusterServerAttributes.tolerance.value = 0;
  ZCL_ReportOnChangeIfNeeded(&thTemperatureMeasurementClusterServerAttributes.tolerance);
}

/**************************************************************************//**
\brief Sends Read Attribute command unicastly

\param[in] mode - address mode;
\param[in] addr - short address of destination node;
\param[in] ep   - destination endpoint;
\param[in] attr - attribute id;
\param[in] cb   - callback function
******************************************************************************/
void thTemperatureMeasurementReadAttribute(APS_AddrMode_t mode,ShortAddr_t addr, Endpoint_t ep,
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
  fillDstAddressing(&req->dstAddressing, mode, addr, ep, TEMPERATURE_MEASUREMENT_CLUSTER_ID);
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
void thTemperatureMeasurementWriteAttribute(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep,
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
  fillDstAddressing(&req->dstAddressing, mode, addr, ep, TEMPERATURE_MEASUREMENT_CLUSTER_ID);
  req->ZCL_Notify = ZCL_WriteAttributeResp;

  commandManagerSendAttribute(req);
}

/**************************************************************************//**
\brief Sends the Configure Reporting for Temperature Measurement cluster

\param[in] mode - address mode;
\param[in] addr - short address of destination node;
\param[in] ep   - destination endpoint;
\param[in] min  - the minimum reporting interval;
\param[in] max  - the maximum reporting interval
******************************************************************************/
void thTemperatureMeasurementConfigureReporting(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep,
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
  fillDstAddressing(&req->dstAddressing, mode, addr, ep, TEMPERATURE_MEASUREMENT_CLUSTER_ID);
  req->ZCL_Notify = ZCL_ConfigureReportingResp;

  commandManagerSendAttribute(req);
}

/**************************************************************************//**
\brief Report attribute indication handler

\param[in] addressing - pointer to addressing information;
\param[in] reportLength - data payload length;
\param[in] reportPayload - data pointer
******************************************************************************/
static void thTemperatureMeasurementReportInd(ZCL_Addressing_t *addressing, uint8_t reportLength, uint8_t *reportPayload)
{
  ZCL_Report_t *rep = (ZCL_Report_t *)reportPayload;
  int16_t reportValue;

  memcpy(&reportValue, &rep->value[0], sizeof(int16_t));
  LOG_STRING(reportAttrIndStr, "<-Temperature Measurement Attr Report: t = %d\r\n");
  appSnprintf(reportAttrIndStr, reportValue);

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
  int16_t attributeValue;

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

    if(ZCL_SUCCESS_STATUS == readAttributeResp->status)
    {
      memcpy(&attributeValue, &readAttributeResp->value[0], sizeof(uint16_t));
      LOG_STRING(readAttrSuccessStr, " <-Read Temperature Measurement attribute (0x%x) response: success\r\n  t = %d\r\n");
      appSnprintf(readAttrSuccessStr, (unsigned)readAttributeResp->id, attributeValue);
    }
    else
    {
      LOG_STRING(readAttrFailStr, " +Read Temperature Measurement attribute failed: status = 0x%2x\r\n");
      appSnprintf(readAttrFailStr, (unsigned)readAttributeResp->status);
    }
  }
  else
  {
    LOG_STRING(readAttrFailStr, " +Read Temperature Measurement attribute failed: status = 0x%2x\r\n");
    appSnprintf(readAttrFailStr, (unsigned)ntfy->status);
  }
}

/**************************************************************************//**
\brief Indication of write attribute response

\param[in] resp - pointer to response
******************************************************************************/
static void ZCL_WriteAttributeResp(ZCL_Notify_t *ntfy)
{
  ZCL_NextElement_t element;
  ZCL_WriteAttributeResp_t *writeAttributeResp;

  if (ZCL_SUCCESS_STATUS == ntfy->status)
  {
    element.id            = ZCL_WRITE_ATTRIBUTES_RESPONSE_COMMAND_ID;
    element.payloadLength = ntfy->responseLength;
    element.payload       = ntfy->responsePayload;
    element.content       = NULL;

    ZCL_GetNextElement(&element);
    writeAttributeResp = (ZCL_WriteAttributeResp_t *) element.content;

    if (writeAttributeCallback)
      writeAttributeCallback();

    if(ZCL_SUCCESS_STATUS == writeAttributeResp->status)
    {
      LOG_STRING(writeAttrSuccessStr, " <-Write Temperature Measurement attribute response: success\r\n");
      appSnprintf(writeAttrSuccessStr);
    }
    else
    {
      LOG_STRING(writeAttrFailStrTwo, " +Write Temperature Measurement attribute failed: status = 0x%x\r\n");
      appSnprintf(writeAttrFailStrTwo, (unsigned)writeAttributeResp->status);
    }
  }
  else
  {
    LOG_STRING(writeAttrFailStrTwo, " +Write Temperature Measurement attribute failed: status = 0x%x\r\n");
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

// eof thTemperatureMeasurementCluster.c
