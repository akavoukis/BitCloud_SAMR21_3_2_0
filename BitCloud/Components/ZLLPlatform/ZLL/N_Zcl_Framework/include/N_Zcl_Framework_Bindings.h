// implemented interface(s)
#define N_Zcl_Framework_RegisterFoundationCommand N_Zcl_Framework_RegisterFoundationCommand_Impl
#define N_Zcl_Framework_RegisterCluster N_Zcl_Framework_RegisterCluster_Impl
#define N_Zcl_Framework_AddSubscriber N_Zcl_Framework_AddSubscriber_Impl
#define N_Zcl_Framework_FindSubscriber N_Zcl_Framework_FindSubscriber_Impl
#define N_Zcl_Framework_EnableZclEndpoint N_Zcl_Framework_EnableZclEndpoint_Impl
#define N_Zcl_Framework_GetNextSequenceNumber N_Zcl_Framework_GetNextSequenceNumber_Impl
#define N_Zcl_Framework_SendCommand N_Zcl_Framework_SendCommand_Impl
#define N_Zcl_Framework_SendClusterSpecificRequest N_Zcl_Framework_SendClusterSpecificRequest_Impl
#define N_Zcl_Framework_SendRequest N_Zcl_Framework_SendRequest_Impl
#define N_Zcl_Framework_SendClusterSpecificResponse N_Zcl_Framework_SendClusterSpecificResponse_Impl
#define N_Zcl_Framework_GetSourceAddress N_Zcl_Framework_GetSourceAddress_Impl
#define N_Zcl_Framework_GetDestinationEndpoint N_Zcl_Framework_GetDestinationEndpoint_Impl
#define N_Zcl_Framework_GetReceivedSequenceNumber N_Zcl_Framework_GetReceivedSequenceNumber_Impl
#define N_Zcl_Framework_GetSentSequenceNumber N_Zcl_Framework_GetSentSequenceNumber_Impl
#define N_Zcl_Framework_ReceivedAsUnicast N_Zcl_Framework_ReceivedAsUnicast_Impl
#define N_Zcl_Framework_Subscribe N_Zcl_Framework_Subscribe_Impl

// used interfaces
#if defined(TESTHARNESS)

   // IN_AfDataRequest
#  define IN_AfDataRequest_DataRequest IN_AfDataRequest_Stub_DataRequest

   // IN_AfIncomingData
#  define IN_AfIncomingData_Subscribe IN_AfIncomingData_Stub_Subscribe

   // N_PacketDistributor
#  define N_PacketDistributor_FindEndpoint N_PacketDistributor_Stub_FindEndpoint

#else

#  if defined(DISABLE_BINDING_AND_LOCAL_LOOPBACK)

     // IN_AfDataRequest
#    if defined(ZIGBEE_END_DEVICE)
//#      define IN_AfDataRequest_DataRequest N_EndDeviceRobustness_DataRequest_Impl
#    else
//#      define IN_AfDataRequest_DataRequest N_ChannelChecker_DataRequest_Impl
#    endif

#  endif

#  if defined(ZIGBEE_END_DEVICE)
#    define IN_AfDataRequest_DataRequest N_EndDeviceRobustness_DataRequest_Impl
#  else
#    define IN_AfDataRequest_DataRequest N_Cmi_DataRequest_Impl
#  endif
   // IN_AfIncomingData
#  define IN_AfIncomingData_Subscribe N_PacketDistributor_Subscribe_Impl
   // N_PacketDistributor
#  define N_PacketDistributor_FindEndpoint N_PacketDistributor_FindEndpoint_Impl

   // N_Cmi
#  define N_Cmi_PlatformToBcAddressingConvert N_Cmi_PlatformToBcAddressingConvert_Impl
#  define N_Cmi_PlatformToBcAddressModeConvert N_Cmi_PlatformToBcAddressModeConvert_Impl

   // N_Binding
#  define N_Binding_FindBinding N_Binding_FindBinding_Impl

#endif

