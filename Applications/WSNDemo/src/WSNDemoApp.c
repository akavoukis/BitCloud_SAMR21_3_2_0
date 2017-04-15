/**********************************************************************//**
  \file WSNDemoApp.c
  \brief

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:
    26/12/14 Prashanth.Udumula - modified
    15/03/12 D. Kolmakov - Refactored

  Last change:
    $Id: WSNDemoApp.c 27584 2015-01-09 14:45:42Z unithra.c $
**************************************************************************/

/*****************************************************************************
                              Includes section
******************************************************************************/
#include <sysUtils.h>
#include <WSNDemoApp.h>
#include <WSNVisualizer.h>
#include <sysTaskManager.h>
#include <zdo.h>
#include <configServer.h>
#include <aps.h>
#include <mac.h>
#include <WSNCommandHandler.h>
#include <WSNMessageSender.h>
#include <WSNCoord.h>
#include <WSNRouter.h>
#include <WSNEndDevice.h>
#include <bspUid.h>

#if APP_USE_OTAU == 1
#include <WSNZclManager.h>
#endif // APP_USE_OTAU

#if defined(_ENABLE_PERSISTENT_SERVER_) && (APP_USE_PDS == 1)
  #include <pdsDataServer.h>
  #include <resetReason.h>
#endif // _ENABLE_PERSISTENT_SERVER_ && APP_USE_PDS

#ifdef ZAPPSI_HOST
#include <zsiNotify.h>
#endif // ZAPPSI_HOST

/*****************************************************************************
                               Definitions section
******************************************************************************/
// Period of blinking during starting network
#define START_NETWORK_BLINKING_INTERVAL 500

// Wakeup period
#define TIMER_WAKEUP 50

/*****************************************************************************
                              Types section
******************************************************************************/
typedef enum
{
  START_BLINKING,
  STOP_BLINKING
} BlinkingAction_t;

/*****************************************************************************
                              Prototypes section
******************************************************************************/
void APL_TaskHandler(void);
void ZDO_MgmtNwkUpdateNotf(ZDO_MgmtNwkUpdateNotf_t *nwkParams);
void ZDO_WakeUpInd(void);

/*****************************************************************************
                              Global variables section
******************************************************************************/
AppNwkInfoCmdPayload_t  appNwkInfo =
{
  .softVersion     = CCPU_TO_LE32(0x01010100),
  .channelMask     = CCPU_TO_LE32(CS_CHANNEL_MASK),
  .boardInfo = {
    .boardType       = MESHBEAN_SENSORS_TYPE,
    .sensorsSize     = sizeof(appNwkInfo.boardInfo.meshbean),
  },
#if APP_USE_DEVICE_CAPTION == 1
  .deviceCaption = {
    .fieldType = DEVICE_CAPTION_FIELD_TYPE,
    .size      = APP_DEVICE_CAPTION_SIZE,
    .caption   = APP_DEVICE_CAPTION
  }
#endif /* APP_USE_DEVICE_CAPTION == 1 */
};
/*****************************************************************************
                              Local variables section
******************************************************************************/
static ZDO_ZdpReq_t leaveReq;
static ZDO_StartNetworkReq_t zdoStartReq;
static SpecialDeviceInterface_t deviceInterface;
static SimpleDescriptor_t simpleDescriptor;
static APS_RegisterEndpointReq_t endpointParams;
// Application state
static AppState_t appState = APP_INITING_STATE;
static struct
{
  uint8_t appSubTaskPosted  : 1;
  uint8_t appCmdHandlerTaskPosted  : 1;
  uint8_t appMsgSenderTaskPosted  : 1;
} appTaskFlags =
{
  .appSubTaskPosted = false,
  .appCmdHandlerTaskPosted = false,
  .appMsgSenderTaskPosted = false
};

// Timer indicating starting network
static HAL_AppTimer_t startingNetworkTimer;
static HAL_AppTimer_t identifyTimer;
static uint16_t identifyDuration = 0;
#if defined(_ENABLE_PERSISTENT_SERVER_) && (APP_USE_PDS == 1) && defined (_LINK_SECURITY_)
static bool restoredFromPds;
#endif

/****************************************************************************
                              Static functions prototypes section
******************************************************************************/
static void appPostGlobalTask(void);
static void appInitialization(void);
static void appZdoNwkUpdateHandler(ZDO_MgmtNwkUpdateNotf_t *updateParam);

static void appZdoStartNetworkConf(ZDO_StartNetworkConf_t *confirmInfo);
static void appZdpLeaveResp(ZDO_ZdpResp_t *zdpResp);
static void appApsDataIndHandler(APS_DataInd_t *ind);

static void manageBlinkingDuringRejoin(BlinkingAction_t action);
static void startingNetworkTimerFired(void);
static void identifyTimerFired(void);
static void appInitializePds(void);

#ifdef _SECURITY_
static void appInitSecurity(void);
#endif
/******************************************************************************
                              Implementations section
******************************************************************************/

/*******************************************************************************
  \brief Application task handler. The function is called by the internal
  task scheduler to process an application task. The task scheduler
  understands that a new application task appeared when the SYS_PostTask()
  function is called with APL_TASK_ID as an argument.

  Application task handler is used to implement the application's state machine.
  Typically, an application changes its state on occurence of some event
  or invocation of a callback function, then calls SYS_PostTask(APL_TASK_ID),
  and the task scheduler directs this call to the APL_TaskHandler() function
  which switches between the application states.

  Mandatory function: must be present in any application.

  In the WSNDemo application each device type (coordinator, router and end device)
  has its own state machine and the corresponding task handler, in addition to the
  global application state machine maintained by APL_TaskHandler(). The latter
  directs application tasks to device-specific task handlers once the node enters
  a network. Application components for sending messages and queueing commands
  also have own local task handlers.

  \return none
*******************************************************************************/
void APL_TaskHandler(void)
{
  switch (appState)
  {
    //Initial application state.
    //The application performs initialization and changes its
    //state to starting network state.
    case APP_INITING_STATE:
    {
      visualizeAppStarting();
      //Invocation of the initialization function
      appInitialization();
      appState = APP_STARTING_NETWORK_STATE;
      appPostGlobalTask();
    }
    break;

    //Main application working state in which the application gets after joining
    //(or forming) a network. The node is in the network now and can send and
    //receive data to and from the outside.
    //Depending on the posted task's type the application directs it
    //to differend handlers.
    case APP_IN_NETWORK_STATE:
    {
      if (appTaskFlags.appSubTaskPosted)
      {
        appTaskFlags.appSubTaskPosted = false;

        //Invocation of task handler function specific to
        //device type (coordinator, router or end device)
        if (deviceInterface.appDeviceTaskHandler)
          deviceInterface.appDeviceTaskHandler();
      }

      if (appTaskFlags.appMsgSenderTaskPosted)
      {
        appTaskFlags.appMsgSenderTaskPosted = false;
        appMsgSender();
      }

      if (appTaskFlags.appCmdHandlerTaskPosted)
      {
        appTaskFlags.appCmdHandlerTaskPosted = false;
        appCmdHandler();
      }
    }
    break;

    //The state in which the application performs network start
    //to join (or form) a ZigBee network
    case APP_STARTING_NETWORK_STATE:
    {
      visualizeNwkStarting();
      manageBlinkingDuringRejoin(START_BLINKING);

      //Starting network (results in joining to or forming a ZigBee network)
      zdoStartReq.ZDO_StartNetworkConf = appZdoStartNetworkConf; //Setting the callback function
      ZDO_StartNetworkReq(&zdoStartReq); //Sending a request to the stack
    }
    break;

    //The state means that the node has received a command from the
    //coordinator to leave the network. The application sends the leave
    //network ZDP request addressed to the own node.
    case APP_LEAVING_NETWORK_STATE:
    {
      //Get the pointer to the request's payload
      ZDO_MgmtLeaveReq_t *zdpLeaveReq = &leaveReq.req.reqPayload.mgmtLeaveReq;

      visualizeNwkLeaving();
      //Configure parameters of the leave network ZDP request
      leaveReq.ZDO_ZdpResp =  appZdpLeaveResp; //Set the callback function
      leaveReq.reqCluster = MGMT_LEAVE_CLID; //Set the request' type
      leaveReq.dstAddrMode = APS_EXT_ADDRESS;
      COPY_EXT_ADDR(leaveReq.dstAddress.extAddress, *MAC_GetExtAddr());
      zdpLeaveReq->deviceAddr = 0; //The current node is requested to leave the network
      zdpLeaveReq->rejoin = 0; //Without rejoining the network after leaving it
      zdpLeaveReq->removeChildren = 1; //Command all end device children to leave the network as well
      zdpLeaveReq->reserved = 0;
      //Send the configure ZDP request to the stack
      ZDO_ZdpReq(&leaveReq);
    }
    break;

    default:
    break;
  }
}

/**************************************************************************//**
  \brief Main application initialization function (common to all device
  types)

  \return none
******************************************************************************/
static void appInitialization(void)
{
  ExtAddr_t uid;
  //Reads the UID set in configuration.h
  CS_ReadParameter(CS_UID_ID,&uid);
  if (uid == 0 || uid > APS_MAX_UNICAST_EXT_ADDRESS)
  {
    BSP_ReadUid(&uid); //Will read the UID from chip
    CS_WriteParameter(CS_UID_ID, &uid); //Writes the read UID to the ram
  }
  
  DeviceType_t deviceType;

#if APP_DEVICE_TYPE == DEV_TYPE_COORDINATOR
  // Serial manager start procedure shall be called here for the case
  // when VCP port on SAM7X_EK platform is used, because it requires
  // as soon as possible initialization.
  appStartUsartManager();
  appCoordinatorGetInterface(&deviceInterface);
#elif APP_DEVICE_TYPE == DEV_TYPE_ROUTER
  appRouterGetInterface(&deviceInterface);
#else
  appEndDeviceGetInterface(&deviceInterface);
#endif

  appInitializePds();

  deviceType = WSN_DEMO_DEVICE_TYPE;
  CS_WriteParameter(CS_DEVICE_TYPE_ID, &deviceType);
  appNwkInfo.nodeType = deviceType;

  //Register an application endpoint to enable the application to
  //receive data from other nodes
  simpleDescriptor.endpoint = WSNDEMO_ENDPOINT;
  simpleDescriptor.AppProfileId = CCPU_TO_LE16(WSNDEMO_PROFILE_ID);
  simpleDescriptor.AppDeviceId = CCPU_TO_LE16(WSNDEMO_DEVICE_ID);
  simpleDescriptor.AppDeviceVersion = WSNDEMO_DEVICE_VERSION;
  endpointParams.simpleDescriptor = &simpleDescriptor;
  endpointParams.APS_DataInd = appApsDataIndHandler; //Set the callback function that will be called on receipt of data frames
  APS_RegisterEndpointReq(&endpointParams); //Send the request to the stack

  startingNetworkTimer.interval = START_NETWORK_BLINKING_INTERVAL;
  startingNetworkTimer.mode     = TIMER_REPEAT_MODE;
  startingNetworkTimer.callback = startingNetworkTimerFired;

#ifdef _SECURITY_
  appInitSecurity();
#endif

  {
    // To remove unalignment access warning for ARM.
    ExtAddr_t extAddr;

    CS_ReadParameter(CS_UID_ID, &extAddr);
    appNwkInfo.extAddr = extAddr;
  }

#if APP_USE_OTAU == 1
  appZclManagerInit();
#endif // APP_USE_OTAU

  //Invocation of the initialization function for specific device
  //type (coordinator, router or end device)
  if (deviceInterface.appDeviceInitialization)
    deviceInterface.appDeviceInitialization();
  appInitMsgSender();
  appInitCmdHandler();
}

#ifdef _SECURITY_
/**************************************************************************//**
  \brief Security initialization

  \return none
******************************************************************************/
static void appInitSecurity(void)
{
  ExtAddr_t extAddr;
  
  // In this application the Coordinator is the TrustCenter so we have to 
  // assign extended address of the Coordinator to the TrustCenter
#if APP_DEVICE_TYPE == DEV_TYPE_COORDINATOR
  // Here we are reading the extended address of the Coordinator which was 
  // written in appInitialization();
  CS_ReadParameter(CS_UID_ID, &extAddr);
  // Here we are writing back the read extended address
  CS_WriteParameter(CS_APS_TRUST_CENTER_ADDRESS_ID, &extAddr);
#else
  // For other devices the TrustCenter address should 
  // be APS_UNIVERSAL_EXTENDED_ADDRESS for them to discover the TrustCenter
  extAddr = APS_UNIVERSAL_EXTENDED_ADDRESS;
  // Here we are writing back the APS_UNIVERSAL_EXTENDED_ADDRESS
  CS_WriteParameter(CS_APS_TRUST_CENTER_ADDRESS_ID, &extAddr);
#endif

#if APP_DEVICE_TYPE == DEV_TYPE_COORDINATOR
  uint8_t nwkDefaultKey[SECURITY_KEY_SIZE];

  CS_ReadParameter(CS_NETWORK_KEY_ID, &nwkDefaultKey);
  NWK_SetKey(nwkDefaultKey, NWK_STARTUP_ACTIVE_KEY_SEQUENCE_NUMBER);
  NWK_ActivateKey(NWK_STARTUP_ACTIVE_KEY_SEQUENCE_NUMBER);
#endif

#ifdef _LINK_SECURITY_
#if defined(_ENABLE_PERSISTENT_SERVER_) && (APP_USE_PDS == 1)
  if (!restoredFromPds)
#endif
  {
    uint8_t linkKey[16] = LINK_KEY;

    ExtAddr_t extAddr = APS_UNIVERSAL_EXTENDED_ADDRESS;
    APS_SetLinkKey(&extAddr, linkKey);
  }
#endif // _LINK_SECURITY_
}
#endif // _SECURITY_

/**************************************************************************//**
  \brief Initialization of PDS to protect system parameters in case
  of power failure

  \return none
******************************************************************************/
static void appInitializePds(void)
{
#if defined(_ENABLE_PERSISTENT_SERVER_) && (APP_USE_PDS == 1)
  //Configure PDS to store parameters in non-volatile memory and update them
  //on occurence of BitCloud events
  PDS_StoreByEvents(BC_ALL_MEMORY_MEM_ID);

  BSP_OpenButtons(NULL, NULL);

  //Restore required configuration from non-volatile memory,
  //or reset non-volatile memory if the button is being pressed
  if (BSP_ReadButtonsState() & 0x01)
    PDS_Delete(PDS_ALL_EXISTENT_MEMORY);
  else if (PDS_IsAbleToRestore(BC_ALL_MEMORY_MEM_ID))
  {
#ifdef _LINK_SECURITY_
    restoredFromPds = true;
#endif // _LINK_SECURITY_
    PDS_Restore(BC_ALL_MEMORY_MEM_ID);
  }

  BSP_CloseButtons();
#endif // _ENABLE_PERSISTENT_SERVER_ && APP_USE_PDS
}

/**************************************************************************//**
  \brief Leave response callback. The response means that the command has
         been received successfully but not precessed yet.

  \param[in]  zdpResp - ZDP response
  \return none
******************************************************************************/
static void appZdpLeaveResp(ZDO_ZdpResp_t *zdpResp)
{
  if (ZDO_SUCCESS_STATUS == zdpResp->respPayload.status)
    appState = APP_STOP_STATE;
  else
    appPostGlobalTask();
}

/**************************************************************************//**
  \brief The callback function for the start network request - is called by
  the stack to indicate that the node has joined (or formed) a network or
  report an error.

  \param[in]  startInfo - confirmation information
  \return none
******************************************************************************/
static void appZdoStartNetworkConf(ZDO_StartNetworkConf_t *startInfo)
{
  manageBlinkingDuringRejoin(STOP_BLINKING);

  //Check if the node has successfully started the network
  if (ZDO_SUCCESS_STATUS == startInfo->status)
  {
    appState = APP_IN_NETWORK_STATE;
    visualizeNwkStarted();
#if APP_USE_OTAU == 1
    runOtauService();
#endif // APP_USE_OTAU
    if (deviceInterface.appDeviceTaskReset)
      deviceInterface.appDeviceTaskReset();

    // Network parameters, such as short address, should be saved
    appNwkInfo.panID           = startInfo->PANId;
    appNwkInfo.shortAddr       = startInfo->shortAddr;
    appNwkInfo.parentShortAddr = startInfo->parentAddr;
    appNwkInfo.workingChannel  = startInfo->activeChannel;
  }
  else
    appPostGlobalTask();
}

/*******************************************************************************
  \brief The function is called by the stack to notify the application about
  various network-related events. See detailed description in API Reference.

  Mandatory function: must be present in any application.

  \param[in] nwkParams - contains notification type and additional data varying
             an event
  \return none
*******************************************************************************/
void ZDO_MgmtNwkUpdateNotf(ZDO_MgmtNwkUpdateNotf_t *nwkParams)
{
  //No link key is set for the joining device in the APS key-pair set
  if (ZDO_NO_KEY_PAIR_DESCRIPTOR_STATUS == nwkParams->status)
  {
#ifdef _LINK_SECURITY_
    ExtAddr_t addr        = nwkParams->childInfo.extAddr;
    uint8_t   linkKey[16] = LINK_KEY;
    APS_SetLinkKey(&addr, linkKey);
#endif
  }
  else
    appZdoNwkUpdateHandler(nwkParams);
}

/**************************************************************************//**
  \brief Application handling of network parameters update event

  \param[in]  updateParam - network parameters update notification
  \return none
******************************************************************************/
static void appZdoNwkUpdateHandler(ZDO_MgmtNwkUpdateNotf_t *updateParam)
{
  switch (updateParam->status)
  {
    case ZDO_NETWORK_LOST_STATUS:
      appState = APP_STOP_STATE;
      break;

    case ZDO_NETWORK_LEFT_STATUS:
      visualizeNwkLeft();
      appState = APP_STARTING_NETWORK_STATE;
      appPostGlobalTask();
      break;

    case ZDO_NWK_UPDATE_STATUS:
    case ZDO_NETWORK_STARTED_STATUS:
      appNwkInfo.shortAddr       = updateParam->nwkUpdateInf.shortAddr;
      appNwkInfo.panID           = updateParam->nwkUpdateInf.panId;
      appNwkInfo.parentShortAddr = updateParam->nwkUpdateInf.parentShortAddr;
      appNwkInfo.workingChannel  = updateParam->nwkUpdateInf.currentChannel;

      manageBlinkingDuringRejoin(STOP_BLINKING);
      visualizeNwkStarted();

      if (APP_STARTING_NETWORK_STATE == appState)
      {
#if APP_USE_OTAU == 1
        runOtauService();
#endif // APP_USE_OTAU
        if (deviceInterface.appDeviceTaskReset)
          deviceInterface.appDeviceTaskReset();
      }
      if (APP_STOP_STATE == appState)
      {
        appState = APP_IN_NETWORK_STATE;
        if (deviceInterface.appDeviceTaskReset)
          deviceInterface.appDeviceTaskReset();
        appPostGlobalTask();
      }
      appState = APP_IN_NETWORK_STATE;

      break;

    default:
      break;
  }
}

/*******************************************************************************
  \brief The function is called by the stack when the node wakes up by timer.

  When the device starts after hardware reset the stack posts an application
  task (via SYS_PostTask()) once, giving control to the application, while
  upon wake up the stack only calls this indication function. So, to provide
  control to the application on wake up, change the application state and post
  an application task via SYS_PostTask(APL_TASK_ID) from this function.

  Mandatory function: must be present in any application.

  \return none
*******************************************************************************/
void ZDO_WakeUpInd(void)
{
}

/**************************************************************************//**
  \brief Blinking during rejoin control

  \param[in]  action - blinking action
  \return none
******************************************************************************/
static void manageBlinkingDuringRejoin(BlinkingAction_t action)
{
  static bool run = false;

  if (START_BLINKING == action)
  {
    if (!run)
    {
      HAL_StartAppTimer(&startingNetworkTimer);
      run = true;
    }
  }

  if (STOP_BLINKING == action)
  {
    run = false;
    HAL_StopAppTimer(&startingNetworkTimer);
  }
}

/**************************************************************************//**
  \brief Network starting timer event

  \return none
******************************************************************************/
static void startingNetworkTimerFired(void)
{
  visualizeNwkStarting();
}
/**************************************************************************//**
  \brief Reads LQI and RSSI for a parent node into appNwkInfo structure

  \return none
******************************************************************************/
void appReadLqiRssi(void)
{
  ZDO_GetLqiRssi_t lqiRssi;

  lqiRssi.nodeAddr = appNwkInfo.parentShortAddr;
  ZDO_GetLqiRssi(&lqiRssi);

  appNwkInfo.lqi  = lqiRssi.lqi;
  appNwkInfo.rssi = lqiRssi.rssi;
}
/**************************************************************************//**
  \brief Posts application's global task. As a result, the stack will
  call the APL_TaskHandler() function to process the task.

  \return none
******************************************************************************/
static void appPostGlobalTask(void)
{
  SYS_PostTask(APL_TASK_ID);
}

/**************************************************************************//**
  \brief Posts an application subtask - a task that will be passed to
  the task handler function specific to ZigBee device type (coordinator,
  router or end device)

  \return none
******************************************************************************/
void appPostSubTaskTask(void)
{
  if (APP_IN_NETWORK_STATE == appState)
  {
    appTaskFlags.appSubTaskPosted = true;
    SYS_PostTask(APL_TASK_ID);
  }
}

/**************************************************************************//**
  \brief Posts command handler task - will be passed to the appCmdHandler()
  function

  \return none
******************************************************************************/
void appPostCmdHandlerTask(void)
{
  if (APP_IN_NETWORK_STATE == appState)
  {
    appTaskFlags.appCmdHandlerTaskPosted = true;
    SYS_PostTask(APL_TASK_ID);
  }
}

/**************************************************************************//**
  \brief Posts message sender task - will be passed to the appMsgSender()
  function

  \return none
******************************************************************************/
void appPostMsgSenderTask(void)
{
  if (APP_IN_NETWORK_STATE == appState)
  {
    appTaskFlags.appMsgSenderTaskPosted = true;
    SYS_PostTask(APL_TASK_ID);
  }
}

/**************************************************************************//**
  \brief Initiate leave network procedure

  \return none
******************************************************************************/
void appLeaveNetwork(void)
{
  if (APP_IN_NETWORK_STATE == appState)
  {
    appState = APP_LEAVING_NETWORK_STATE;
    appPostGlobalTask();
  }
}

/**************************************************************************//**
  \brief New command received from PC event handler.

  \param[in] command - pointer to received command.
  \param[in] cmdSize - received command size.

  \return none
******************************************************************************/
void appPcCmdReceived(void *command, uint8_t cmdSize)
{
  AppCommand_t *pCommand = (AppCommand_t *)command;

  appCreateCommand(&pCommand);

  // Warning prevention
  (void)cmdSize;
}

/**************************************************************************//**
  \brief Starts blinking for identifying device.

  \param[in] blinkDuration - blinking duration.
  \param[in] blinkPeriod - blinking period.

  \return none
******************************************************************************/
void appStartIdentifyVisualization(uint16_t blinkDuration, uint16_t blinkPeriod)
{
  if (blinkDuration && blinkPeriod)
  {
    identifyDuration = blinkDuration;

    HAL_StopAppTimer(&identifyTimer); // Have to be stopped before start
    identifyTimer.interval = blinkPeriod;
    identifyTimer.mode     = TIMER_REPEAT_MODE;
    identifyTimer.callback = identifyTimerFired;
    HAL_StartAppTimer(&identifyTimer);
  }
}

/**************************************************************************//**
  \brief Identify timer event.

  \return none
******************************************************************************/
static void identifyTimerFired(void)
{
  visualizeIdentity();

  identifyDuration -= MIN(identifyDuration, identifyTimer.interval);

  if (!identifyDuration)
  {
    visualizeWakeUp();
    HAL_StopAppTimer(&identifyTimer);
  }
}

/**************************************************************************//**
  \brief Finds command descriptor in appCmdDescTable.

  \param[in, out] pCmdDesc - pointer to command descriptor
  \param[in] cmdId - command identificator.

  \return true if search has been successful, false otherwise.
******************************************************************************/
bool appGetCmdDescriptor(AppCommandDescriptor_t *pCmdDesc, uint8_t cmdId)
{
  if (deviceInterface.appDeviceCmdDescTable)
  {
    for (uint8_t i = 0; i < deviceInterface.appDeviceCmdDescTableSize; i++)
    {
      memcpy_P(pCmdDesc, &deviceInterface.appDeviceCmdDescTable[i], sizeof(AppCommandDescriptor_t));

      if (cmdId == pCmdDesc->commandID)
      {
        return true;
      }
    }
  }

  memset(pCmdDesc, 0, sizeof(AppCommandDescriptor_t));
  return false;
}

/**************************************************************************//**
  \brief APS data indication handler.

  \param ind - received data.

  \return none
******************************************************************************/
static void appApsDataIndHandler(APS_DataInd_t *ind)
{
  AppCommand_t *pCommand = (AppCommand_t *)ind->asdu;

  visualizeAirRxFinished();
  appCreateCommand(&pCommand);
}

#ifdef _BINDING_
/***********************************************************************************
  \brief The function is called by the stack to notify the application that a
  binding request has been received from a remote node.

  Mandatory function: must be present in any application.

  \param[in] bindInd - information about the bound device
  \return none
 ***********************************************************************************/
void ZDO_BindIndication(ZDO_BindInd_t *bindInd)
{
  (void)bindInd;
}

/***********************************************************************************
  \brief The function is called by the stack to notify the application that a
  binding request has been received from a remote node.

  Mandatory function: must be present in any application.

  \param[in] unbindInd - information about the unbound device
  \return none
 ***********************************************************************************/
void ZDO_UnbindIndication(ZDO_UnbindInd_t *unbindInd)
{
  (void)unbindInd;
}
#endif //_BINDING_

#ifdef ZAPPSI_HOST
/**************************************************************************//**
\brief Indicates zsi status update.

\param[out] notf - ZSI staus update indication parameters structure pointer. For details go to
            ZSI_UpdateNotf_t declaration.
\return none
******************************************************************************/
void ZSI_StatusUpdateNotf(ZSI_UpdateNotf_t *notf)
{
  (void *)notf;
}
#endif // ZAPPSI_HOST

/**********************************************************************//**
  \brief The entry point of the program. This function should not be
  changed by the user without necessity and must always include an
  invocation of the SYS_SysInit() function and an infinite loop with
  SYS_RunTask() function called on each step.

  \return none
**************************************************************************/
int main(void)
{
  //Initialization of the System Environment
  SYS_SysInit();

  //The infinite loop maintaing task management
  for(;;)
  {
    //Each time this function is called, the task
    //scheduler processes the next task posted by one
    //of the BitCloud components or the application
    SYS_RunTask();
  }
}
//eof WSNDemoApp.c

