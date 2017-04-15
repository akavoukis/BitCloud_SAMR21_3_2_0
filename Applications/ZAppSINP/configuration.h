#ifndef _CONFIGURATION_H_
#define _CONFIGURATION_H_

//-----------------------------------------------
// Includes board-specific peripherals support in application.
//-----------------------------------------------
#include <BoardConfig.h>

//-----------------------------------------------
// BSP identifiers
//-----------------------------------------------
#define BOARD_FAKE 0x01
#define BOARD_RCB 0x02
#define BOARD_RCB_KEY_REMOTE 0x03
#define BOARD_ATMEGA256RFR2_XPRO 0x04
#define BOARD_SAMR21_XPRO 0x05
#define BOARD_SAMR21_ZLLEK 0x06
#define BOARD_SAMR21_CUSTOM 0x07

//-----------------------------------------------
// Atmel communication interfaces identifiers.
// Supported interfaces are platform and application dependent.
//-----------------------------------------------
#define APP_INTERFACE_USART 0x01
#define APP_INTERFACE_VCP 0x02
#define APP_INTERFACE_SPI 0x03
#define APP_INTERFACE_UART 0x04
#define APP_INTERFACE_USBFIFO 0x05
#define APP_INTERFACE_STDIO 0x06

//-----------------------------------------------
// Atmel external memory identifiers.
// Supported memory is platform and application dependent.
//-----------------------------------------------
#define AT25F2048  0x01
#define AT45DB041  0x02
#define AT25DF041A 0x03
#define M25P40VMN6PB 0x04

#define ZAPPSI_NP

// Defines primary serial interface type to be used by ZAppSI.
#define APP_ZAPPSI_INTERFACE APP_INTERFACE_USART
//#define APP_ZAPPSI_INTERFACE APP_INTERFACE_USBFIFO
//#define APP_ZAPPSI_INTERFACE APP_INTERFACE_SPI

// Defines USART interface name to be used by ZAppSI.
#define APP_ZAPPSI_MEDIUM_CHANNEL USART_CHANNEL_1
//#define APP_ZAPPSI_MEDIUM_CHANNEL USART_CHANNEL_0
//#define APP_ZAPPSI_MEDIUM_CHANNEL USART_CHANNEL_USBFIFO
//#define APP_ZAPPSI_MEDIUM_CHANNEL SPI_CHANNEL_2

//-----------------------------------------------
//BOARD_SAMD20_XPLAINED_PRO
//-----------------------------------------------
#ifdef BOARD_SAMD20_XPLAINED_PRO
  // Defines primary serial interface type to be used by ZAppSI.
  #undef APP_ZAPPSI_INTERFACE
  #define APP_ZAPPSI_INTERFACE APP_INTERFACE_USART
  
  // Defines USART interface name to be used by ZAppSI.
  #undef APP_ZAPPSI_MEDIUM_CHANNEL
  #define APP_ZAPPSI_MEDIUM_CHANNEL USART_CHANNEL_1
  //#define APP_ZAPPSI_MEDIUM_CHANNEL USART_CHANNEL_0
#endif

//-----------------------------------------------
//BOARD_SAMR21
//-----------------------------------------------
#ifdef BOARD_SAMR21
  #define BSP_SUPPORT BOARD_SAMR21_XPRO
  //#define BSP_SUPPORT BOARD_SAMR21_ZLLEK
  //#define BSP_SUPPORT BOARD_SAMR21_CUSTOM
  //#define BSP_SUPPORT BOARD_FAKE
  
  // Defines USART interface name to be used by ZAppSI.
  #undef APP_ZAPPSI_MEDIUM_CHANNEL
  #define APP_ZAPPSI_MEDIUM_CHANNEL USART_CHANNEL_1
  //#define APP_ZAPPSI_MEDIUM_CHANNEL USART_CHANNEL_0
  
  // Defines primary serial interface type to be used by ZAppSI.
  #undef APP_ZAPPSI_INTERFACE
  #define APP_ZAPPSI_INTERFACE APP_INTERFACE_USART
#endif

// 32-bit mask of channels to be scanned before network is started. Channels that
// should be used are marked with logical 1 at corresponding bit location.
//  Valid channel numbers for 2.4 GHz band are 0x0b - 0x1a
//  Valid channel numbers for 900 MHz band are 0x00 - 0x0a
// 
//  Notes:
//  1. for small amount of enabled channels it is more convinient to specify list
// of channels in the form of '(1ul << 0x0b)'
//  2. For 900 MHz band you also need to specify channel page
// 
//  Value range: 32-bit values:
//  Valid channel numbers for 2.4 GHz band are 0x0b - 0x1a
//  Valid channel numbers for 900 MHz band are 0x00 - 0x0a
// 
//  C-type: uint32_t
//  Can be set: at any time before network start
#define CS_CHANNEL_MASK (1L<<0x0f)

// ZigBee device type determines network behavior of a given device and functions
// it can perform. To give a brief overview, each networks contains exacty one
// coordinator and an arbirtary number of routers and end devices; an end device
// does not have children, data is passed through the parent, that is, a router or
// the coordinator.
#define CS_DEVICE_TYPE DEVICE_TYPE_ROUTER
//Device is an end device.
//#define CS_DEVICE_TYPE DEVICE_TYPE_END_DEVICE
//Device is a coordinator.
//#define CS_DEVICE_TYPE DEVICE_TYPE_COORDINATOR

// 64-bit Unique Identifier (UID) determining the device extended address. If this
// value is 0 stack will try to read hardware UID from external UID or EEPROM chip.
// at startup. Location of hardware UID is platform dependend and it may not be
// available on all platforms. If the latter case then UID value must be provided
// by user via this parameter. This parameter must be unique for each device in a
// network. This should not be 0 for Coordinator.
#define CS_UID 0x0LL

// The maximum number of direct children that a given device (the coordinator or a
// router) can have.
// 
//  The parameter is only enabled for routers and the coordinator. An end device
// can not have children. If an actual number of children reaches a parameter's
// value, the node will have not been able to accept any more children joining the
// network. The parameter can be set to 0 on a router thus preventing it from
// accepting any children and can help form a desired network topology. For
// example, if the parameter is set to 0 on all routers, then the coordinator will
// be the only device that can have children and the network will have star
// topology.
#define CS_MAX_CHILDREN_AMOUNT 4

// The maximum number of routers among the direct children of the device
// 
//  The parameter determines how many routers the device can have as children. Note
// that the maximum number of end devices is equal to CS_MAX_CHILDREN_AMOUNT -
// CS_MAX_CHILDREN_ROUTER_AMOUNT.
#define CS_MAX_CHILDREN_ROUTER_AMOUNT 2

// The parameter enabled in the high security mode specifies the size of the APS
// key-pair set. The APS key-pair set stores pairs of corresponding extended
// address and a link key or a master key. For each node with which the current
// node is going to communicate it must keep an entry with the remote node extended
// address and a link key. If the link key is unknown, the node can request the
// trust center for it via APS_RequestKeyReq(). The trust center must store a link
// key or a master key depending on the CS_SECURITY_STATUS used for each node it is
// going to authenticate. Entries can also be added manually by APS_SetLinkKey()
// and APS_SetMasterKey().
#define CS_APS_KEY_PAIR_DESCRIPTORS_AMOUNT 6

//-----------------------------------------------
//STANDARD_SECURITY_MODE
//-----------------------------------------------
#ifdef STANDARD_SECURITY_MODE
  // Depending on security key type and security mode this is either network key,
  // master key, link key or initial link key.
  // 
  //  Network key is used to encrypt a part of a data frame occupied by the NWK
  // payload. This type of encryption is applied in both the standard and high
  // security mode. The high security mode also enables encryption of the APS payload
  // with a link key, but if the txOptions.useNwkKey field in APS request parameters
  // is set to 0, the APS payload is encrypted with the network key.
  // 
  //  The network key must be predefined if standard security is used with
  // CS_ZDO_SECURITY_STATUS set to 0. For all other values of CS_ZDO_SECURITY_STATUS
  // the network key is received from the trust center during device authentication.
  // Note that in the standard security mode with CS_ZDO_SECURITY_STATUS equal to 3
  // the network key is transferred to the joining device in an unencrypted frame.
  #define CS_NETWORK_KEY {0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC}
  
  // The maximum number of network keys that can be stored on the device
  // 
  //  A device in a secured network can keep several network keys up to the value of
  // this parameter. Upon frame reception the device extracts key sequence number
  // from the auxiliary header of the frame and decrypts the message with the network
  // key corresponding to this sequence number. Besides, one key is considered active
  // for each device; this is the key that is used for encrypting outgoing frames.
  // The keys are distributed by the trust center with the help of the
  // APS_TransportKeyReq() command. The trust center can also change the active key
  // of a remote node via a call to APS_SwitchKeyReq().
  #define CS_NWK_SECURITY_KEYS_AMOUNT 1
  
  // Address of device responsible for authentication and key distribution (Trust
  // Center).
  // 
  //  The parameter specifies the trust center extended address. The stack makes use
  // of the parameter to support various operations in networks with security
  // enabled. For correct network operation a parameter's value must coincide with
  // the actual trust center address.
  // 
  //  In case the trust center extended address is unknown, for example, for testing
  // purposes, the parameter can be assigned to the universal trust center address
  // which equals APS_SM_UNIVERSAL_TRUST_CENTER_EXT_ADDRESS.
  #define CS_APS_TRUST_CENTER_ADDRESS 0xAAAAAAAAAAAAAAAALL
  
  // Security information waiting timeout before secure network join considered
  // failed.
  // 
  //  A timeout is started when connection with a parent is established. If the
  // security related procedures that are performed after this will not be completed
  // before the timeout exceeds, the device will fail joining the network. A value is
  // measured in milliseconds.
  #define CS_APS_SECURITY_TIMEOUT_PERIOD 10000
#endif

//-----------------------------------------------
//STDLINK_SECURITY_MODE
//-----------------------------------------------
#ifdef STDLINK_SECURITY_MODE
  // The parameter enabled in the high security mode specifies the size of the APS
  // key-pair set. The APS key-pair set stores pairs of corresponding extended
  // address and a link key or a master key. For each node with which the current
  // node is going to communicate it must keep an entry with the remote node extended
  // address and a link key. If the link key is unknown, the node can request the
  // trust center for it via APS_RequestKeyReq(). The trust center must store a link
  // key or a master key depending on the CS_SECURITY_STATUS used for each node it is
  // going to authenticate. Entries can also be added manually by APS_SetLinkKey()
  // and APS_SetMasterKey().
  #undef CS_APS_KEY_PAIR_DESCRIPTORS_AMOUNT
  #define CS_APS_KEY_PAIR_DESCRIPTORS_AMOUNT 6
  
  // Address of device responsible for authentication and key distribution (Trust
  // Center).
  // 
  //  The parameter specifies the trust center extended address. The stack makes use
  // of the parameter to support various operations in networks with security
  // enabled. For correct network operation a parameter's value must coincide with
  // the actual trust center address.
  // 
  //  In case the trust center extended address is unknown, for example, for testing
  // purposes, the parameter can be assigned to the universal trust center address
  // which equals APS_SM_UNIVERSAL_TRUST_CENTER_EXT_ADDRESS.
  #define CS_APS_TRUST_CENTER_ADDRESS 0xAAAAAAAAAAAAAAAALL
  
  // Security information waiting timeout before secure network join considered
  // failed.
  // 
  //  A timeout is started when connection with a parent is established. If the
  // security related procedures that are performed after this will not be completed
  // before the timeout exceeds, the device will fail joining the network. A value is
  // measured in milliseconds.
  #define CS_APS_SECURITY_TIMEOUT_PERIOD 10000
  
  // Depending on security key type and security mode this is either network key,
  // master key, link key or initial link key.
  // 
  //  Network key is used to encrypt a part of a data frame occupied by the NWK
  // payload. This type of encryption is applied in both the standard and high
  // security mode. The high security mode also enables encryption of the APS payload
  // with a link key, but if the txOptions.useNwkKey field in APS request parameters
  // is set to 0, the APS payload is encrypted with the network key.
  // 
  //  The network key must be predefined if standard security is used with
  // CS_ZDO_SECURITY_STATUS set to 0. For all other values of CS_ZDO_SECURITY_STATUS
  // the network key is received from the trust center during device authentication.
  // Note that in the standard security mode with CS_ZDO_SECURITY_STATUS equal to 3
  // the network key is transferred to the joining device in an unencrypted frame.
  #define CS_NETWORK_KEY {0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC}
  
  // The maximum number of network keys that can be stored on the device
  // 
  //  A device in a secured network can keep several network keys up to the value of
  // this parameter. Upon frame reception the device extracts key sequence number
  // from the auxiliary header of the frame and decrypts the message with the network
  // key corresponding to this sequence number. Besides, one key is considered active
  // for each device; this is the key that is used for encrypting outgoing frames.
  // The keys are distributed by the trust center with the help of the
  // APS_TransportKeyReq() command. The trust center can also change the active key
  // of a remote node via a call to APS_SwitchKeyReq().
  #define CS_NWK_SECURITY_KEYS_AMOUNT 1
  
  // Enables or disables Certicom support.
  #define CERTICOM_SUPPORT 0
  //#define CERTICOM_SUPPORT 1
#endif

// Maximum amount of records in the Group Table.
// 
//  The Group Table size cannot be 0. The group table stores pairs of a group
// address and an endpoint. Upon receiving a frame addressed to members of a
// certain group which include the current node as well the stack fires indications
// on all endpoints registered with the group address.
#define CS_GROUP_TABLE_SIZE 1

// Maximum amount of records in the Neighbor Table.
// 
//  The parameter determines the size of the neighbor table which is used to store
// beacon responses from nearby devices. The parameter puts an upper bound over the
// amount of child devices possible for the node.
#define CS_NEIB_TABLE_SIZE 7

// Maximum amount of records in the network Route Table.
// 
//  The parameter sets the maximum number of records that can be kept in the NWK
// route table. The table is used by NWK to store information about established
// routes. Each table entry specifies the next-hop short address for a route from
// the current node to a given destination node. The table is being filled
// automatically during route discovery. An entry is added when a route is
// discovered.
#define CS_ROUTE_TABLE_SIZE 4

// Maximum amount of records in the network Address Map Table.
// 
//  The parameter sets the maximum number of records in the address map table used
// by NWK to store pairs of corresponding short and extended addresses. The stack
// appeals to the table when a data frame is being sent to a specified extended
// address to extract the corresponding short address. If it fails to find the
// short address, an error is reported.
#define CS_ADDRESS_MAP_TABLE_SIZE 5

// Maximum amount of records in the network Route Discovery Table.
// 
//  The parameter specifies the size of the route discovery table used by NWK to
// store next-hop addresses of the nodes for routes that are not yet established.
// Upon exhausting the capacity of the table, the stack starts rewriting old
// entries. If the size of the route table is big enough after all used routes are
// established the table may not be used.
#define CS_ROUTE_DISCOVERY_TABLE_SIZE 3

// Maximim amount of records in the Binding Table
// 
//  The parameter sets the size of the binding table used by APS to store binding
// links, which are structures containing information about source and destination
// extended addresses and endpoints for unicast bindings and just group addresses
// as destinations for group bindings. If the binding is going to be applied to
// send a data frame, then the corresponding entry shall be first inserted into the
// table via the APS_BindingReq() function.
#define CS_APS_BINDING_TABLE_SIZE 15

// The number of buffers for data requests on the APS layer.
// 
//  The parameter specifies the number of buffers that are allocated by APS to
// store data requests parameters. The parameter puts an upper bound to the number
// of data requests that can be processed by APS simultaneously. If all buffers are
// in use and a new data request appears, it is kept in a queue until a buffer is
// released.
#define CS_APS_DATA_REQ_BUFFERS_AMOUNT 3

// The number of buffers for acknowledgement messages sent by APS.
// 
//  This parameter determines the amount of memory that needs to be allocated for a
// special type of buffers used by APS to store payloads for acknowledgement
// frames. The need to use the buffers occurs when the node receives a frame that
// has to be acknowledged. That is, the APS component on the node has to send an
// acknowledgement frame. For frames initiated by the application, the memory for a
// payload is to be allocated by the application on its own, while the payload
// memory for an acknowledgement frame shall be reserved by APS. The request
// parameters are still stored in the data request buffers.
#define CS_APS_ACK_FRAME_BUFFERS_AMOUNT 2

// Amount of buffers on NWK layer used to keep incoming and outgoing frames. This
// parameters affects how many children of a parent are able to get broadcat
// messages.
#define CS_NWK_BUFFERS_AMOUNT 4

// Amount of ZCL memory buffers
#define CS_ZCL_MEMORY_BUFFERS_AMOUNT 5

// The parameter specifies the TX power of the transceiver device, is measured in
// dBm(s). After the node has entered the network the value can only be changed via
// the ZDO_SetTxPowerReq() function.
// 
//  Value range: depends on the hardware. Transmit power must be in the range from
// -17 to 3 dBm for AT86RF231, AT86RF230 and AT86RF230B. For AT86RF233 transmit
// power must be in the range from -17 to 4 dBm. For AT86RF212 transmit power must
// be in the range from -11 to 11 dBm.
#define CS_RF_TX_POWER 3


#endif // _CONFIGURATION_H_
