/**************************************************************************//**
  \file ciThermostatCluster.c

  \brief
    Combined Interface Thermostat cluster implementation.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2013, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    09/09/2014 Unithra.C - Created.
******************************************************************************/
#ifdef APP_DEVICE_TYPE_COMBINED_INTERFACE

/******************************************************************************
                    Includes section
******************************************************************************/
#include <ciThermostatCluster.h>
#include <uartManager.h>
#include <commandManager.h>
#include <haClusters.h>

/******************************************************************************
//                      defines section
*****************************************************************************/

typedef struct PACK
{
  ZCL_AttributeId_t id;
  uint8_t type;
  uint8_t properties;
  int16_t value;
} setPoint_t;

/******************************************************************************
                    Local variables section
******************************************************************************/
static AttibuteReadCallback_t   readAttributeCallback;
static AttributeWriteCallback_t writeAttributeCallback;

/******************************************************************************
                    Prototypes section
******************************************************************************/
static void ZCL_ReadAttributeResp(ZCL_Notify_t *ntfy);
static void ZCL_WriteAttributeResp(ZCL_Notify_t *ntfy);

/*****************************************************************************/
/******************************************************************************
                    Prototypes section
******************************************************************************/
static void ciThermostatReportInd(ZCL_Addressing_t *addressing, uint8_t reportLength, uint8_t *reportPayload);
static void ciThermostatAttrEventInd(ZCL_Addressing_t *addressing, ZCL_AttributeId_t attributeId, ZCL_AttributeEvent_t event);
static void ZCL_ConfigureReportingResp(ZCL_Notify_t *ntfy);

/******************************************************************************
                    Implementation section
******************************************************************************/
/**************************************************************************//**
\brief Initializes Thermostat cluster
******************************************************************************/
void thermostatClusterInit(void)
{
  ZCL_Cluster_t *cluster = ZCL_GetCluster(APP_SRC_ENDPOINT_ID, THERMOSTAT_CLUSTER_ID, ZCL_CLUSTER_SIDE_CLIENT);

  if (cluster)
  {
    cluster->ZCL_ReportInd = ciThermostatReportInd;
    cluster->ZCL_AttributeEventInd = ciThermostatAttrEventInd;
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
void thermostatReadAttribute(APS_AddrMode_t mode,ShortAddr_t addr, Endpoint_t ep,
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
  fillDstAddressing(&req->dstAddressing, mode, addr, ep, THERMOSTAT_CLUSTER_ID);
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
void thermostatWriteAttribute(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep,
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
  fillDstAddressing(&req->dstAddressing, mode, addr, ep, THERMOSTAT_CLUSTER_ID);
  req->ZCL_Notify = ZCL_WriteAttributeResp;

  commandManagerSendAttribute(req);
}

/**************************************************************************//**
\brief Sends the Configure Reporting for Thermostat cluster

\param[in] mode     - address mode;
\param[in] addr     - short address of destination node;
\param[in] ep       - destination endpoint;
\param[in] attrId   - attr id;
\param[in] attrType - attr id;
\param[in] min      - the minimum reporting interval;
\param[in] max      - the maximum reporting interval
******************************************************************************/
void thermostatConfigureReporting(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep,
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
  fillDstAddressing(&req->dstAddressing, mode, addr, ep, THERMOSTAT_CLUSTER_ID);
  req->ZCL_Notify = ZCL_ConfigureReportingResp;

  commandManagerSendAttribute(req);
}

/**************************************************************************//**
\brief Report attribute indication handler

\param[in] addressing - pointer to addressing information;
\param[in] reportLength - data payload length;
\param[in] reportPayload - data pointer
******************************************************************************/
static void ciThermostatReportInd(ZCL_Addressing_t *addressing, uint8_t reportLength, uint8_t *reportPayload)
{
  ZCL_Report_t *rep = (ZCL_Report_t *)reportPayload;
  int16_t reportValue;
  if(rep->id == ZCL_THERMOSTAT_CLUSTER_LOCAL_TEMPERATURE_SERVER_ATTRIBUTE_ID)
  {
    int16_t reportValue;
    memcpy(&reportValue, &rep->value[0], sizeof(int16_t));  
    
    LOG_STRING(reportAttrIndStr, "<-Local Temperature Report: %d.%dC\r\n");
    appSnprintf(reportAttrIndStr, (int)(reportValue/THERMOSTAT_LOCAL_TEMPERATURE_SCALE),(int)(reportValue%THERMOSTAT_LOCAL_TEMPERATURE_SCALE));
  }
  else if(rep->id == ZCL_THERMOSTAT_CLUSTER_OCCUPIED_COOLING_SETPOINT_SERVER_ATTRIBUTE_ID)
  {
    setPoint_t *payload = (setPoint_t*)rep;
    
    LOG_STRING(reportAttrIndStr, "<-Setpoints changed on Thermostat:\r\n");
    appSnprintf(reportAttrIndStr);
    memcpy(&reportValue, &rep->value[1], sizeof(int16_t));
    LOG_STRING(modeStr, "#cool setpoint:%d.%d\r\n");
    appSnprintf(modeStr, (int)(reportValue/THERMOSTAT_LOCAL_TEMPERATURE_SCALE),(int)(reportValue%THERMOSTAT_LOCAL_TEMPERATURE_SCALE));
    payload++;
    LOG_STRING(amtStr, "#heat setpoint: %d.%d\r\n");
    memcpy(&reportValue, &payload->value, sizeof(int16_t));
    appSnprintf(amtStr, (int)(reportValue/THERMOSTAT_LOCAL_TEMPERATURE_SCALE),(int)(reportValue%THERMOSTAT_LOCAL_TEMPERATURE_SCALE));
  }

  (void)addressing, (void)reportLength;
}

/**************************************************************************//**
\brief Attribute Event indication handler(to indicate when attr values have
        read or written)

\param[in] addressing - pointer to addressing information;
\param[in] reportLength - data payload length;
\param[in] reportPayload - data pointer
******************************************************************************/
static void ciThermostatAttrEventInd(ZCL_Addressing_t *addressing, ZCL_AttributeId_t attributeId, ZCL_AttributeEvent_t event)
{
#if (APP_ENABLE_CONSOLE == 1)
  LOG_STRING(AttrEventIndStr, "<-Attr ID 0x%x event 0x%x\r\n");
  appSnprintf(AttrEventIndStr, attributeId, event);
#else
  (void)attributeId;
  (void)event;
#endif
  (void)addressing;
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
    
    memcpy(&attributeValue, &readAttributeResp->value[0], sizeof(uint16_t));
    LOG_STRING(readAttrSuccessStr, "<-Read Thermostat attribute (0x%x) response: success  t = %d\r\n");
    appSnprintf(readAttrSuccessStr, (unsigned)readAttributeResp->id, attributeValue);
  }
  else
  {
    LOG_STRING(readAttrFailStr, " +Read Thermostat attribute failed: status = 0x%2x\r\n");
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

    LOG_STRING(writeAttrSuccessStr, " <-Write Thermostat attribute response: success\r\n");
    appSnprintf(writeAttrSuccessStr);
  }
  else
  {
    LOG_STRING(writeAttrFailStrTwo, " +Write Thermostat attribute failed: status = 0x%x\r\n");
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

/**************************************************************************//**
\brief Setpoint Raise/Lower command payload fillup

\param[out] payload - pointer to command structure;
\param[in] group - group id;
\param[in] scene - scene id
******************************************************************************/
static void ciFillsendSetPointRaiseLowerPayload(ZCL_SetpointRaiseLower_t *payload, int8_t setPointMode, int8_t amount)
{
  payload->mode = setPointMode;
  payload->amount = amount;
}

/**************************************************************************//**
  \brief Sends Setpoint Raise/Lower command
  \param[in] mode - address mode;
  \param[in] addr - short address of destination node;
  \param[in] ep   - destination endpoint;
  \param mode - set points to be adjusted
  \param amount - amount of increase/decrease to setpoint value
        (in steps of 0.1°C.)
  \return none
******************************************************************************/
void ciSendSetpointRaiseLowerCommand(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep,
  int8_t setPointMode, int8_t amount)
{
  ZCL_Request_t *req;

  if (!(req = getFreeCommand()))
    return;

  fillCommandRequest(req, ZCL_THERMOSTAT_CLUSTER_SETPOINT_RAISE_LOWER_COMMAND_ID, sizeof(ZCL_SetpointRaiseLower_t));
  ciFillsendSetPointRaiseLowerPayload((ZCL_SetpointRaiseLower_t *)req->requestPayload, setPointMode, amount);
  fillDstAddressing(&req->dstAddressing, mode, addr, ep, THERMOSTAT_CLUSTER_ID);
  commandManagerSendCommand(req);
}

#endif // APP_DEVICE_TYPE_COMBINED_INTERFACE

// eof ciThermostatCluster.c
