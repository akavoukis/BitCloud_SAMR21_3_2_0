/**************************************************************************//**
  \file colorSceneRemoteTesting.c

  \brief
    Color Scene Remote device testing implementation.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    01.02.13 N. Fomin - Created.
******************************************************************************/
#if APP_ZLL_DEVICE_TYPE == APP_DEVICE_TYPE_COLOR_SCENE_REMOTE
/******************************************************************************
                    Includes section
******************************************************************************/
#include <colorSceneRemoteTesting.h>
#include <uartManager.h>

#include <N_InterPan_Bindings.h>
#include <N_InterPan.h>
#include <N_ConnectionEnddevice_Bindings.h>
#include <N_Connection.h>

/******************************************************************************
                    Prototypes section
******************************************************************************/
void ReceivedScanResponse(N_InterPan_ScanResponse_t* payload, int8_t rssi, N_Address_Extended_t* sourceAddress);
void ReceivedDeviceInfoRequest(N_InterPan_DeviceInfoRequest_t* payload, N_Address_Extended_t* sourceAddress);
void ReceivedDeviceInfoResponse(N_InterPan_DeviceInfoResponse_t* payload, N_Address_Extended_t* sourceAddress);
void ReceivedIdentifyRequest(N_InterPan_IdentifyRequest_t* payload, N_Address_Extended_t* sourceAddress);
void ReceivedNetworkStartRequest(N_InterPan_NetworkStartRequest_t* payload, N_Address_Extended_t* sourceAddress);
void ReceivedNetworkStartResponse(N_InterPan_NetworkStartResponse_t* payload, N_Address_Extended_t* sourceAddress);
void ReceivedNetworkJoinRouterRequest(N_InterPan_NetworkJoinRequest_t* payload, N_Address_Extended_t* sourceAddress);
void ReceivedNetworkJoinRouterResponse(N_InterPan_NetworkJoinResponse_t* payload, N_Address_Extended_t* sourceAddress);
void ReceivedNetworkJoinEndDeviceRequest(N_InterPan_NetworkJoinRequest_t* payload, N_Address_Extended_t* sourceAddress);
void ReceivedNetworkJoinEndDeviceResponse(N_InterPan_NetworkJoinResponse_t* payload, N_Address_Extended_t* sourceAddress);

void Connected(void);
void NetworkJoined(void);

/******************************************************************************
                    Static variables section
******************************************************************************/
static N_InterPan_Callback_t interPanCallback =
{
  NULL, //ReceivedScanRequest,
  ReceivedScanResponse,
  ReceivedDeviceInfoRequest,
  ReceivedDeviceInfoResponse,
  ReceivedIdentifyRequest,
  ReceivedNetworkStartRequest,
  ReceivedNetworkStartResponse,
  ReceivedNetworkJoinRouterRequest,
  ReceivedNetworkJoinRouterResponse,
  ReceivedNetworkJoinEndDeviceRequest,
  ReceivedNetworkJoinEndDeviceResponse,
  NULL, // ReceivedNetworkUpdateRequest,
  NULL, // ReceivedResetToFactoryNewRequest,
  NULL, // ReceivedInterPanCommand
  -1
};

static const N_Connection_Callback_t connectionCallback =
{
  Connected,
  NULL, //void (*Disconnected)(void);
  NetworkJoined, //void (*NetworkJoined)(void);
  NULL, // ResetToFactoryDefaults
  NULL, // ChildAssociated
  -1
};

/******************************************************************************
                    Implementations section
******************************************************************************/
/**************************************************************************//**
\brief Initializes testing extension
******************************************************************************/
void initTestingExtension(void)
{
  N_InterPan_Subscribe(&interPanCallback);
  N_Connection_Subscribe(&connectionCallback);
}

/**************************************************************************//**
\brief Scan response received callback function

\param[in] payload - a pointer to scan response payload;
\param[in] rssi    - rssi;
\param[in] sourceAddress - the extended address of a sender device
******************************************************************************/
void ReceivedScanResponse(N_InterPan_ScanResponse_t* payload, int8_t rssi, N_Address_Extended_t* sourceAddress)
{
  LOG_STRING(scanRespStr, "Scan Response received\r\n");
  appSnprintf(scanRespStr);
  (void)payload;
  (void)rssi;
  (void)sourceAddress;
}

/**************************************************************************//**
\brief Device Info request received callback function

\param[in] payload - a pointer to device info request payload;
\param[in] sourceAddress - the extended address of a sender device
******************************************************************************/
void ReceivedDeviceInfoRequest(N_InterPan_DeviceInfoRequest_t* payload, N_Address_Extended_t* sourceAddress)
{
  LOG_STRING(deviceInfoReqStr, "Device Info request received\r\n");
  appSnprintf(deviceInfoReqStr);
  (void)payload;
  (void)sourceAddress;
}

/**************************************************************************//**
\brief Device Info response received callback function

\param[in] payload - a pointer to device info respinse payload;
\param[in] sourceAddress - the extended address of a sender device
******************************************************************************/
void ReceivedDeviceInfoResponse(N_InterPan_DeviceInfoResponse_t* payload, N_Address_Extended_t* sourceAddress)
{
  LOG_STRING(deviceInfoRespStr, "Device Info response received\r\n");
  appSnprintf(deviceInfoRespStr);
  (void)payload;
  (void)sourceAddress;
}

/**************************************************************************//**
\brief Identify request received callback function

\param[in] payload - a pointer to device info request payload;
\param[in] sourceAddress - the extended address of a sender device
******************************************************************************/
void ReceivedIdentifyRequest(N_InterPan_IdentifyRequest_t* payload, N_Address_Extended_t* sourceAddress)
{
  LOG_STRING(identifyReqStr, "Identify request received\r\n");
  appSnprintf(identifyReqStr);
  (void)payload;
  (void)sourceAddress;
}

/**************************************************************************//**
\brief Network Start request received callback function

\param[in] payload - a pointer to network start request payload;
\param[in] sourceAddress - the extended address of a sender device
******************************************************************************/
void ReceivedNetworkStartRequest(N_InterPan_NetworkStartRequest_t* payload, N_Address_Extended_t* sourceAddress)
{
  LOG_STRING(networkStartReqStr, "Network Start request received\r\n");
  appSnprintf(networkStartReqStr);
  (void)payload;
  (void)sourceAddress;
}

/**************************************************************************//**
\brief Network Start response received callback function

\param[in] payload - a pointer to network start response payload;
\param[in] sourceAddress - the extended address of a sender device
******************************************************************************/
void ReceivedNetworkStartResponse(N_InterPan_NetworkStartResponse_t* payload, N_Address_Extended_t* sourceAddress)
{
  LOG_STRING(networkStartRespStr, "Network Start response received\r\n");
  appSnprintf(networkStartRespStr);
  (void)payload;
  (void)sourceAddress;
}

/**************************************************************************//**
\brief Network Join Router request received callback function

\param[in] payload - a pointer to network join router request payload;
\param[in] sourceAddress - the extended address of a sender device
******************************************************************************/
void ReceivedNetworkJoinRouterRequest(N_InterPan_NetworkJoinRequest_t* payload, N_Address_Extended_t* sourceAddress)
{
  LOG_STRING(networkJoinRouterReqStr, "Network Join Router request received\r\n");
  appSnprintf(networkJoinRouterReqStr);
  (void)payload;
  (void)sourceAddress;
}

/**************************************************************************//**
\brief Network Join Router response received callback function

\param[in] payload - a pointer to network join response request payload;
\param[in] sourceAddress - the extended address of a sender device
******************************************************************************/
void ReceivedNetworkJoinRouterResponse(N_InterPan_NetworkJoinResponse_t* payload, N_Address_Extended_t* sourceAddress)
{
  LOG_STRING(networkJoinRouterRespStr, "Network Join Router response received\r\n");
  appSnprintf(networkJoinRouterRespStr);
  (void)payload;
  (void)sourceAddress;
}

/**************************************************************************//**
\brief Network Join End Device request received callback function

\param[in] payload - a pointer to network join end device request payload;
\param[in] sourceAddress - the extended address of a sender device
******************************************************************************/
void ReceivedNetworkJoinEndDeviceRequest(N_InterPan_NetworkJoinRequest_t* payload, N_Address_Extended_t* sourceAddress)
{
  LOG_STRING(networkJoinEndDeviceReqStr, "Network Join End Device request received\r\n");
  appSnprintf(networkJoinEndDeviceReqStr);
  (void)payload;
  (void)sourceAddress;
}

/**************************************************************************//**
\brief Network Join End Device response received callback function

\param[in] payload - a pointer to network join end device response payload;
\param[in] sourceAddress - the extended address of a sender device
******************************************************************************/
void ReceivedNetworkJoinEndDeviceResponse(N_InterPan_NetworkJoinResponse_t* payload, N_Address_Extended_t* sourceAddress)
{
  LOG_STRING(networkJoinEndDeviceRespStr, "Network Join End Device response received\r\n");
  appSnprintf(networkJoinEndDeviceRespStr);
  (void)payload;
  (void)sourceAddress;
}

/**************************************************************************//**
\brief Callback function which is called when an end device has
  a connection to parent
******************************************************************************/
void Connected(void)
{
  LOG_STRING(connectedStr, "Connected\r\n");
  appSnprintf(connectedStr);
}

/**************************************************************************//**
\brief Callback function which is called when a ed joined network.
******************************************************************************/
void NetworkJoined(void)
{
  LOG_STRING(joinedStr, "Joining succeded\r\n");
  appSnprintf(joinedStr);
}

#endif // APP_ZLL_DEVICE_TYPE == APP_DEVICE_TYPE_COLOR_SCENE_REMOTE

// eof colorSceneRemoteTesting.c