#ifndef _CONFIGURATION_H_
#define _CONFIGURATION_H_

//-----------------------------------------------
// BSP identifiers
//-----------------------------------------------
#define BOARD_FAKE 0x01
#define BOARD_RCB 0x02
#define BOARD_RCB_KEY_REMOTE 0x03
#define BOARD_ATMEGA256RFR2_XPRO 0x04
#define BOARD_SAMR21_XPRO 0x05
#define BOARD_SAMR21_CUSTOM 0x06

//-----------------------------------------------
// Includes board-specific peripherals support in application.
//-----------------------------------------------
#include <BoardConfig.h>

#undef _BUTTONS_

#define APP_INTERFACE_USART 0x01
#define APP_INTERFACE_VCP 0x02
#define APP_INTERFACE_SPI 0x03
#define APP_INTERFACE_UART 0x04
#define APP_INTERFACE_USBFIFO 0x05
#define APP_INTERFACE_STDIO 0x06

#define AT25F2048  0x01
#define AT45DB041  0x02
#define AT25DF041A 0x03

// Enables or disables APS Fragmentation support.
#define APP_FRAGMENTATION 0
//#define APP_FRAGMENTATION 1

// Enables or disables support for OTA Upgrade.
#define APP_USE_OTAU 0
//#define APP_USE_OTAU 1

// Shall be enabled for HA application.
#define ZCL_SUPPORT 1

// Shall be enabled for HA application.
#define HA_PROFILE_EXTENSIONS 1

//#define APP_USE_PWM

// ZigBee Home Automation profile device type
//#define APP_DEVICE_TYPE_COMBINED_INTERFACE
//#define APP_DEVICE_TYPE_IAS_ACE
//#define APP_DEVICE_TYPE_DIMMABLE_LIGHT
#define APP_DEVICE_TYPE_MYAPP
//#define APP_DEVICE_TYPE_THERMOSTAT
//#define APP_DEVICE_TYPE_MULTI_SENSOR
//#define APP_DEVICE_TYPE_DIMMER_SWITCH

/* Enable Different Sensor Type under Multi-Sensor */
//#define APP_SENSOR_TYPE_OCCUPANCY_SENSOR    //Occupancy Sensor Device.
//#define APP_SENSOR_TYPE_TEMPERATURE_SENSOR  //Temperature Sensor Device.
//#define APP_SENSOR_TYPE_HUMIDITY_SENSOR     //Humidity Sensor Device, manufacturer specific
//#define APP_SENSOR_TYPE_LIGHT_SENSOR        //Light Sensor Device.

#ifdef APP_DEVICE_TYPE_COMBINED_INTERFACE
#undef BOARD_QTOUCH_XPRO
#endif

#ifdef BOARD_QTOUCH_XPRO 
#if !defined APP_THERMOSTAT_EXT_ADDRESS
#define CS_UID 0x100
#endif
#endif

/* Enable/Define Zone Table Size */
#define APP_ZONE_TABLE_SIZE  3


// Enables or disables certification testing extension
#define APP_ENABLE_CERTIFICATION_EXTENSION 0
//#define APP_ENABLE_CERTIFICATION_EXTENSION 1

// Enable/disable reading battery voltage/percentage from bsp
#define APP_BSP_READ_BATTERY_VALUE 0
//#define APP_BSP_READ_BATTERY_VALUE 1

// Specifies if logging enabled
#define APP_DEVICE_EVENTS_LOGGING 1
//#define APP_DEVICE_EVENTS_LOGGING 0

#define APP_ENABLE_CONSOLE 1
//#define APP_ENABLE_CONSOLE 0

/* Enable wear-leveling version of PDS */
#define PDS_ENABLE_WEAR_LEVELING 1

/* If Bootloader will be used in parallel with application. this should be commented. */
#define PDS_NO_BOOTLOADER_SUPPORT

/* ZigBee Platform NV items list*/
#define PERSISTENT_NV_ITEMS_PLATFORM    NWK_SECURITY_COUNTERS_MEM_ID
/* Application NV items list */
#define PERSISTENT_NV_ITEMS_APPLICATION 0xFFFu


//-----------------------------------------------
//BOARD_REB_CBB
//-----------------------------------------------
#ifdef BOARD_REB_CBB
  // Defines primary serial interface type to be used by application.
  #define APP_INTERFACE APP_INTERFACE_USART
  
  // Defines USART interface name to be used by application.
  #define APP_USART_CHANNEL USART_CHANNEL_D0
  
  // Defines primary serial interface type to be used by ZAppSI.
  #define APP_ZAPPSI_INTERFACE APP_INTERFACE_USART
  
  // Defines USART interface name to be used by ZAppSI.
  #define APP_ZAPPSI_MEDIUM_CHANNEL USART_CHANNEL_D0
#endif

//-----------------------------------------------
//BOARD_SAM3S_EK
//-----------------------------------------------
#ifdef BOARD_SAM3S_EK
  // Defines USART interface name to be used by ZAppSI.
  #undef APP_ZAPPSI_MEDIUM_CHANNEL
  #define APP_ZAPPSI_MEDIUM_CHANNEL USART_CHANNEL_0
  //#define APP_ZAPPSI_MEDIUM_CHANNEL USART_CHANNEL_1
  
  // Defines primary serial interface type to be used by ZAppSI.
  #undef APP_ZAPPSI_INTERFACE
  #define APP_ZAPPSI_INTERFACE APP_INTERFACE_USART
  
  // Defines primary serial interface type to be used by application.
  #define APP_INTERFACE APP_INTERFACE_USART
  //#define APP_INTERFACE APP_INTERFACE_UART
  //#define APP_INTERFACE APP_INTERFACE_VCP
  
  //-----------------------------------------------
  //APP_INTERFACE == APP_INTERFACE_UART
  //-----------------------------------------------
  #if (APP_INTERFACE == APP_INTERFACE_UART)
    // Defines UART interface name to be used by application.
    #define APP_UART_CHANNEL UART_CHANNEL_0
    //#define APP_UART_CHANNEL UART_CHANNEL_1
  #endif
  
  //-----------------------------------------------
  //APP_INTERFACE == APP_INTERFACE_VCP
  //-----------------------------------------------
  #if (APP_INTERFACE == APP_INTERFACE_VCP)
    // Defines USART interface name to be used by application.
    #define APP_USART_CHANNEL USART_CHANNEL_VCP
  #endif
  
  //-----------------------------------------------
  //APP_INTERFACE == APP_INTERFACE_USART
  //-----------------------------------------------
  #if (APP_INTERFACE == APP_INTERFACE_USART)
    // Defines USART interface name to be used by application.
    #define APP_USART_CHANNEL USART_CHANNEL_1
    //#define APP_USART_CHANNEL USART_CHANNEL_0
  #endif
#endif //

//-----------------------------------------------
//BOARD_STK600
//-----------------------------------------------
#ifdef BOARD_STK600
  // Defines USART interface name to be used by ZAppSI.
  #undef APP_ZAPPSI_MEDIUM_CHANNEL
  #define APP_ZAPPSI_MEDIUM_CHANNEL USART_CHANNEL_1
  //#define APP_ZAPPSI_MEDIUM_CHANNEL USART_CHANNEL_D0
  //#define APP_ZAPPSI_MEDIUM_CHANNEL USART_CHANNEL_F0
  
  // Defines primary serial interface type to be used by ZAppSI.
  #undef APP_ZAPPSI_INTERFACE
  #define APP_ZAPPSI_INTERFACE APP_INTERFACE_USART
  
  // Defines primary serial interface type to be used by application.
  #define APP_INTERFACE APP_INTERFACE_USART
  //#define APP_INTERFACE APP_INTERFACE_SPI
  
  //-----------------------------------------------
  //APP_INTERFACE == APP_INTERFACE_USART
  //-----------------------------------------------
  #if (APP_INTERFACE == APP_INTERFACE_USART)
    // Defines USART interface name to be used by application.
    #define APP_USART_CHANNEL USART_CHANNEL_1
    //#define APP_USART_CHANNEL USART_CHANNEL_D0
    //#define APP_USART_CHANNEL USART_CHANNEL_F0
  #endif
  
  //-----------------------------------------------
  //APP_INTERFACE == APP_INTERFACE_SPI
  //-----------------------------------------------
  #if (APP_INTERFACE == APP_INTERFACE_SPI)
    // Defines SPI interface name to be used by application.
    #define APP_SPI_CHANNEL SPI_CHANNEL_2
    //#define APP_SPI_CHANNEL SPI_CHANNEL_D
    
    // Defines SPI interface mode.
    #define APP_SPI_MASTER_MODE 1
    //#define APP_SPI_MASTER_MODE 0
  #endif
#endif //

//-----------------------------------------------
//BOARD_SAMD20_XPLAINED_PRO
//-----------------------------------------------
#ifdef BOARD_SAMD20_XPLAINED_PRO
  // Defines USART interface name to be used by ZAppSI.
  #undef APP_ZAPPSI_MEDIUM_CHANNEL
  #define APP_ZAPPSI_MEDIUM_CHANNEL USART_CHANNEL_0
  //#define APP_ZAPPSI_MEDIUM_CHANNEL USART_CHANNEL_1
  
  // Defines primary serial interface type to be used by ZAppSI.
  #undef APP_ZAPPSI_INTERFACE
  #define APP_ZAPPSI_INTERFACE APP_INTERFACE_USART
  
  // Defines USART interface name to be used by application.
  #define APP_USART_CHANNEL USART_CHANNEL_0
  //#define APP_USART_CHANNEL USART_CHANNEL_1
  
  // Defines primary serial interface type to be used by application.
  #define APP_INTERFACE APP_INTERFACE_USART
#endif

//-----------------------------------------------
//BOARD_MEGARF
//-----------------------------------------------
#ifdef BOARD_MEGARF
  #define BSP_SUPPORT BOARD_RCB
  //#define BSP_SUPPORT BOARD_ATMEGA256RFR2_XPRO
  //#define BSP_SUPPORT BOARD_RCB_KEY_REMOTE
  //#define BSP_SUPPORT BOARD_FAKE
  
  // Defines primary serial interface type to be used by ZAppSI.
  #undef APP_ZAPPSI_INTERFACE
  #define APP_ZAPPSI_INTERFACE APP_INTERFACE_USART
  //#define APP_ZAPPSI_INTERFACE APP_INTERFACE_USBFIFO
  //#define APP_ZAPPSI_INTERFACE APP_INTERFACE_SPI
  
  // Defines primary serial interface type to be used by application.
  #define APP_INTERFACE APP_INTERFACE_USART
  //#define APP_INTERFACE APP_INTERFACE_USBFIFO
  
  //-----------------------------------------------
  //APP_INTERFACE == APP_INTERFACE_USART
  //-----------------------------------------------
  #if (APP_INTERFACE == APP_INTERFACE_USART)
    // Defines USART interface name to be used by application.
    #define APP_USART_CHANNEL USART_CHANNEL_1
    //#define APP_USART_CHANNEL USART_CHANNEL_0
  #endif
  
  //-----------------------------------------------
  //APP_INTERFACE == APP_INTERFACE_USBFIFO
  //-----------------------------------------------
  #if (APP_INTERFACE == APP_INTERFACE_USBFIFO)
    // Defines USART interface name to be used by application.
    #define APP_USART_CHANNEL USART_CHANNEL_USBFIFO
  #endif
  
  //-----------------------------------------------
  //APP_ZAPPSI_INTERFACE == APP_INTERFACE_USART
  //-----------------------------------------------
  #if (APP_ZAPPSI_INTERFACE == APP_INTERFACE_USART)
    // Defines USART interface name to be used by ZAppSI.
    #undef APP_ZAPPSI_MEDIUM_CHANNEL
    #define APP_ZAPPSI_MEDIUM_CHANNEL USART_CHANNEL_1
    //#define APP_ZAPPSI_MEDIUM_CHANNEL USART_CHANNEL_0
  #endif
  
  //-----------------------------------------------
  //APP_ZAPPSI_INTERFACE == APP_INTERFACE_USBFIFO
  //-----------------------------------------------
  #if (APP_ZAPPSI_INTERFACE == APP_INTERFACE_USBFIFO)
    // Defines USART interface name to be used by ZAppSI.
    #undef APP_ZAPPSI_MEDIUM_CHANNEL
    #define APP_ZAPPSI_MEDIUM_CHANNEL USART_CHANNEL_USBFIFO
  #endif
  
  //-----------------------------------------------
  //APP_ZAPPSI_INTERFACE == APP_INTERFACE_SPI
  //-----------------------------------------------
  #if (APP_ZAPPSI_INTERFACE == APP_INTERFACE_SPI)
    // Defines SPI interface mode.
    #define APP_ZAPPSI_SPI_MASTER_MODE 0
    
    // Defines USART interface name to be used by ZAppSI.
    #undef APP_ZAPPSI_MEDIUM_CHANNEL
    #define APP_ZAPPSI_MEDIUM_CHANNEL SPI_CHANNEL_2
  #endif
#endif //

//-----------------------------------------------
//BOARD_RF231USBRD
//-----------------------------------------------
#ifdef BOARD_RF231USBRD
  // Defines primary serial interface type to be used by application.
  #define APP_INTERFACE APP_INTERFACE_VCP
  //#define APP_INTERFACE APP_INTERFACE_UART
  
  //-----------------------------------------------
  //APP_INTERFACE == APP_INTERFACE_UART
  //-----------------------------------------------
  #if (APP_INTERFACE == APP_INTERFACE_UART)
    // Defines UART interface name to be used by application.
    #define APP_UART_CHANNEL UART_CHANNEL_0
  #endif
  
  //-----------------------------------------------
  //APP_INTERFACE == APP_INTERFACE_VCP
  //-----------------------------------------------
  #if (APP_INTERFACE == APP_INTERFACE_VCP)
    // Defines USART interface name to be used by application.
    #define APP_USART_CHANNEL USART_CHANNEL_VCP
  #endif
#endif

//-----------------------------------------------
//BOARD_PC
//-----------------------------------------------
#ifdef BOARD_PC
  // Defines USART interface name to be used by ZAppSI.
  #undef APP_ZAPPSI_MEDIUM_CHANNEL
  #define APP_ZAPPSI_MEDIUM_CHANNEL COM1
  
  // Defines primary serial interface type to be used by ZAppSI.
  #undef APP_ZAPPSI_INTERFACE
  #define APP_ZAPPSI_INTERFACE APP_INTERFACE_USART
  
  // Defines primary serial interface type to be used by application.
  #define APP_INTERFACE APP_INTERFACE_USART
  //#define APP_INTERFACE APP_INTERFACE_STDIO
  
  //-----------------------------------------------
  //APP_INTERFACE == APP_INTERFACE_STDIO
  //-----------------------------------------------
  #if (APP_INTERFACE == APP_INTERFACE_STDIO)
    // Defines USART interface name to be used by application.
    #define APP_USART_CHANNEL USART_CHANNEL_FAKE
  #endif
  
  //-----------------------------------------------
  //APP_INTERFACE == APP_INTERFACE_USART
  //-----------------------------------------------
  #if (APP_INTERFACE == APP_INTERFACE_USART)
    // Defines USART interface name to be used by application.
    #define APP_USART_CHANNEL USART_CHANNEL_FAKE
  #endif
#endif //

//-----------------------------------------------
//BOARD_SAMR21
//-----------------------------------------------
#ifdef BOARD_SAMR21

  // Defines USART interface name to be used by ZAppSI.
  #undef APP_ZAPPSI_MEDIUM_CHANNEL
  //default #define APP_ZAPPSI_MEDIUM_CHANNEL USART_CHANNEL_0
  #define APP_ZAPPSI_MEDIUM_CHANNEL USART_CHANNEL_1
  
  // Defines primary serial interface type to be used by ZAppSI.
  #undef APP_ZAPPSI_INTERFACE
  #define APP_ZAPPSI_INTERFACE APP_INTERFACE_USART
  
  // Defines USART interface name to be used by application.
  #define APP_USART_CHANNEL USART_CHANNEL_0
  //#define APP_USART_CHANNEL USART_CHANNEL_1
  
  #ifndef BSP_SUPPORT
  #define BSP_SUPPORT BOARD_SAMR21_XPRO
  //#define BSP_SUPPORT BOARD_SAMR21_ZLLEK
  //#define BSP_SUPPORT BOARD_SAMR21_CUSTOM
  //#define BSP_SUPPORT BOARD_FAKE
  #endif
  
  // Defines primary serial interface type to be used by application.
  #define APP_INTERFACE APP_INTERFACE_USART
#endif //

// 16-bit manufacturer code allocated by the ZigBee Alliance. It is being used in
// payload of OTA commands as well as for filtering of manufacturer-specific ZCL
// commands and attributes. See ZigBee Manufacturer Code Database, 053874r16, Atmel
// code.
#define CS_MANUFACTURER_CODE 0x1014

//-----------------------------------------------
//AT86RF212
//-----------------------------------------------
#ifdef AT86RF212
  // Enables or disables Listen Before Talk feature.
  #define CS_LBT_MODE false
  //#define CS_LBT_MODE true
  
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
  //  Persistent: Yes
  #define CS_CHANNEL_MASK (1L<<0x0b)
  
  // Channel page number defines band and modulation scheme that will be used for
  // communication.
  // 
  //  Value range:
  //  0 - 915MHz (BPSK-40, channels 0x01 - 0x0a), 868MHz (BPSK-20, channel 0x00)
  //  2 - 915MHz (O-QPSK-250, channels 0x01 - 0x0a), 868Mhz (O-QPSK-100, channel
  // 0x00)
  //  5 - 780MHz (O-QPSK-250, channels 0x00 - 0x03, Chinese band)
  // 
  //  C-type: uint8_t
  //  Can be set: at any time before network start
  //  Persistent: Yes
  #define CS_CHANNEL_PAGE 0
  //O-QPSK
  //#define CS_CHANNEL_PAGE 2
  //Chinese band
  //#define CS_CHANNEL_PAGE 5
#else
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
  //  Persistent: Yes
  #define CS_CHANNEL_MASK (1L<<0x0b)
#endif

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
// 
//  Value range: from 0 to CS_NEIB_TABLE_SIZE
//  C-type: uint8_t
//  Can be set: at compile time only
//  Persistent: No
#define CS_MAX_CHILDREN_AMOUNT 6

// The maximum number of routers among the direct children of the device
// 
//  The parameter determines how many routers the device can have as children. Note
// that the maximum number of end devices is equal to CS_MAX_CHILDREN_AMOUNT -
// CS_MAX_CHILDREN_ROUTER_AMOUNT.
// 
//  Value range: from 0 to CS_MAX_CHILDREN_AMOUNT
//  C-type: uint8_t
//  Can be set: at compile time only
//  Persistent: No
#define CS_MAX_CHILDREN_ROUTER_AMOUNT 2

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
  // 
  //  Value range: 1 - 255
  //  C-type: uint8_t
  //  Can be set: at compile time only
  //  Persistent: No
  #define CS_APS_KEY_PAIR_DESCRIPTORS_AMOUNT 5
  
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
  // 
  //  Value range: all 128-bit values
  //  C-type: uint8_t[16] or any compatible
  //  Can be set: at any time before network start
  //  Persistent: No
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
  // 
  //  C-type: NwkKeyAmount_t (typedef for uint8_t)
  //  Can be set: at compile time only
  //  Persistent: No
  #define CS_NWK_SECURITY_KEYS_AMOUNT 1
  
  // Security information waiting timeout before secure network join considered
  // failed.
  // 
  //  A timeout is started when connection with a parent is established. If the
  // security related procedures that are performed after this will not be completed
  // before the timeout exceeds, the device will fail joining the network. A value is
  // measured in milliseconds.
  // 
  //  C-type: uint32_t
  //  Can be set: at compile time only
  //  Persistent: No
  #define CS_APS_SECURITY_TIMEOUT_PERIOD 10000
#endif

// Maximum amount of records in the Group Table.
// 
//  The Group Table size cannot be 0. The group table stores pairs of a group
// address and an endpoint. Upon receiving a frame addressed to members of a
// certain group which include the current node as well the stack fires indications
// on all endpoints registered with the group address.
// 
//  C-type: uint8_t
//  Can be set: at compile time only
//  Persistent: No
#define CS_GROUP_TABLE_SIZE 8

// Maximum amount of records in the Neighbor Table.
// 
//  The parameter determines the size of the neighbor table which is used to store
// beacon responses from nearby devices. The parameter puts an upper bound over the
// amount of child devices possible for the node.
// 
//  Value range: at minimum 1, the maximum value is limited to the available memory
//  C-type: uint8_t
//  Can be set: at compile time only
//  Persistent: No
#define CS_NEIB_TABLE_SIZE 5

// Maximum amount of records in the network Route Table.
// 
//  The parameter sets the maximum number of records that can be kept in the NWK
// route table. The table is used by NWK to store information about established
// routes. Each table entry specifies the next-hop short address for a route from
// the current node to a given destination node. The table is being filled
// automatically during route discovery. An entry is added when a route is
// discovered.
// 
//  Since the end device always sends a frame directly to its parent its route
// table size should be set to 0.
// 
//  C-type: uint8_t
//  Can be set: at compile time only
//  Persistent: No
#define CS_ROUTE_TABLE_SIZE 5

// Maximum amount of records in the network Address Map Table.
// 
//  The parameter sets the maximum number of records in the address map table used
// by NWK to store pairs of corresponding short and extended addresses. The stack
// appeals to the table when a data frame is being sent to a specified extended
// address to extract the corresponding short address. If it fails to find the
// short address, an error is reported.
// 
//  C-type: NwkSizeOfAddressMap_t (typedef for uint8_t)
//  Can be set: at compile time only
//  Persistent: No
#define CS_ADDRESS_MAP_TABLE_SIZE 5

// Maximum amount of records in the network Route Discovery Table.
// 
//  The parameter specifies the size of the route discovery table used by NWK to
// store next-hop addresses of the nodes for routes that are not yet established.
// Upon exhausting the capacity of the table, the stack starts rewriting old
// entries. If the size of the route table is big enough after all used routes are
// established the table may not be used.
// 
//  Since the end device always sends a frame directly to its parent its route
// discovery table size should be set to 0.
// 
//  C-type: uint8_t
//  Can be set: at compile time only
//  Persistent: No
#define CS_ROUTE_DISCOVERY_TABLE_SIZE 2

// Maximum amount of records in the Duplicate Rejection Table.
// 
//  The duplicate rejection table is used by APS to store information about
// incoming unicast messages in order to reject messages that have been already
// received and processed. Following ZigBee specification, the parameter should be
// not less than 1.
// 
//  Value range: greater than 1
//  C-type: uint8_t
//  Can be set: at compile time only
//  Persistent: No
#define CS_DUPLICATE_REJECTION_TABLE_SIZE 7

// Maximim amount of records in the Binding Table
// 
//  The parameter sets the size of the binding table used by APS to store binding
// links, which are structures containing information about source and destination
// extended addresses and endpoints for unicast bindings and just group addresses
// as destinations for group bindings. If the binding is going to be applied to
// send a data frame, then the corresponding entry shall be first inserted into the
// table via the APS_BindingReq() function.
// 
//  C-type: uint8_t
//  Can be set: at compile time only
//  Persistent: No
#define CS_APS_BINDING_TABLE_SIZE 14

// The number of buffers for data requests on the APS layer.
// 
//  The parameter specifies the number of buffers that are allocated by APS to
// store data requests parameters. The parameter puts an upper bound to the number
// of data requests that can be processed by APS simultaneously. If all buffers are
// in use and a new data request appears, it is kept in a queue until a buffer is
// released.
// 
//  C-type: uint8_t
//  Can be set: at compile time only
//  Persistent: No
#define CS_APS_DATA_REQ_BUFFERS_AMOUNT 4

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
// 
//  Typically, a value of this parameter equals CS_APS_DATA_REQ_BUFFERS_AMOUNT - 1.
// 
//  C-type: uint8_t
//  Can be set: at compile time only
//  Persistent: No
#define CS_APS_ACK_FRAME_BUFFERS_AMOUNT 3

// Amount of buffers on NWK layer used to keep incoming and outgoing frames. This
// parameters affects how many children of a parent are able to get broadcat
// messages.
#define CS_NWK_BUFFERS_AMOUNT 8

// The parameter specifies the TX power of the transceiver device, is measured in
// dBm(s). After the node has entered the network the value can only be changed via
// the ZDO_SetTxPowerReq() function.
// 
//  Value range: depends on the hardware. Transmit power must be in the range from
// -17 to 3 dBm for AT86RF231, AT86RF230 and AT86RF230B. For AT86RF233 transmit
// power must be in the range from -17 to 4 dBm. For AT86RF212 transmit power must
// be in the range from -11 to 11 dBm.
// 
//  C-type: int8_t
//  Can be set: at any time
//  Persistent: Yes
#define CS_RF_TX_POWER 3

//-----------------------------------------------
//APP_FRAGMENTATION == 1
//-----------------------------------------------
#if (APP_FRAGMENTATION == 1)
  // This parameter limits the number of pieces to which the data sent with one APS
  // request can be split i f the fragmentation feature is applied. Thus it also
  // limits the maximum amount of data sent by the application with a single request:
  //  maximum data length = CS_APS_MAX_BLOCKS_AMOUNT * CS_APS_BLOCK_SIZE if the
  // latter parameter is not 0, else
  //  maximum data length = CS_APS_MAX_BLOCKS_AMOUNT * APS_MAX_ASDU_SIZE.
  //  C-type: uint8_t
  //  Can be set: at compile time only
  //  Persistent: No
  #define CS_APS_MAX_BLOCKS_AMOUNT 4
  
  // Maximim size of a single fragment during fragmented transmission.
  // 
  //  If the value is 0, blocks will be of the maximum possilbe size; that is the
  // size will equal the value of CS_APS_MAX_ASDU_SIZE. The parameter and
  // CS_APS_MAX_BLOCKS_AMOUNT are also used to determine an amount of memory
  // allocated for a special buffer that keeps parts of incoming fragmented message
  // until all of them are received.
  // 
  //  C-type: uint16_t
  //  Can be set: at compile time only
  //  Persistent: No
  #define CS_APS_BLOCK_SIZE 0
#endif

//-----------------------------------------------
//APP_USE_OTAU == 1
//-----------------------------------------------
#if (APP_USE_OTAU == 1)
  #undef ZCL_SUPPORT
  #define ZCL_SUPPORT 1
  
  // Enable or disable console tunneling support in image store driver. Application
  // can send date through tunnel in parallel to ISD driver.
  #define APP_USE_ISD_CONSOLE_TUNNELING 1
  //#define APP_USE_ISD_CONSOLE_TUNNELING 0
  
  // Use fake OFD driver instead of real one. This option is useful for evaluation of
  // OTA Upgrade feature on boards without external flash.
  #define APP_USE_FAKE_OFD_DRIVER 0
  //#define APP_USE_FAKE_OFD_DRIVER 1
  
  // Support OTAU image page request features
  #define APP_SUPPORT_OTAU_PAGE_REQUEST 1
  //#define APP_SUPPORT_OTAU_PAGE_REQUEST 0
  
  // Defines type of used external flash memory chip.
  #define EXTERNAL_MEMORY AT25DF041A
  //#define EXTERNAL_MEMORY M25P40VMN6PB
  //#define EXTERNAL_MEMORY AT25F2048
  //#define EXTERNAL_MEMORY AT45DB041
  
  // Support interrupted OTAU recovery
  #define APP_SUPPORT_OTAU_RECOVERY 0
  //#define APP_SUPPORT_OTAU_RECOVERY 1
  
  // The amount of servers the OTAU client can listen to during upgrade server
  // discovery
  // 
  //  The OTAU client can store information about several discovered OTAU servers.
  // However, the client device tries to connect to discovered servers one by one
  // until the first successful attempt and then communicates and uploads the whole
  // image from the first suitable server.
  // 
  //  The parameter is valid for OTAU clients only.
  // 
  //  Value range: at least 1
  //  C-type: uint8_t
  //  Can be set: at compile time only
  //  Persistent: No
  #define CS_ZCL_OTAU_DISCOVERED_SERVER_AMOUNT 1
  
  // The number of clients that the OTAU server can server simultaneously
  // 
  //  If this parameter equals 1, the OTAU server will upgrade devices in the network
  // one by one. However, the server can process more than one client sessions at a
  // time, if this parameter is greater than 1.
  // 
  //  The parameter is valid for OTAU servers only.
  // 
  //  Value range: at least 1
  //  C-type: uint8_t
  //  Can be set: at compile time only
  //  Persistent: No
  #define CS_ZCL_OTAU_CLIENT_SESSION_AMOUNT 1
  
  // The interval in milliseconds between two attempts to find an upgrade server
  // 
  //  The parameter is valid for OTAU clients only.
  // 
  //  Value range: any 32-bit value
  //  C-type: uint32_t
  //  Can be set: at any time before an OTAU start
  //  Persistent: No
  #define CS_ZCL_OTAU_SERVER_DISCOVERY_PERIOD 60000
  
  // The interval in milliseconds between two successful attempts to query the server
  // 
  //  The parameter is valid only for OTAU clients.
  // 
  //  Value range: any 32-bit value
  //  C-type: uint32_t
  //  Can be set: at any time before an OTAU start
  //  Persistent: No
  #define CS_ZCL_OTAU_QUERY_INTERVAL 5000
  
  // Max retry count for commands (OTAU cluster, ZDO and APS) used for OTAU
  // 
  //  The parameter is valid only for OTAU clients.
  // 
  //  Value range: any 8-bit value
  //  C-type: uint8_t
  //  Can be set: at any time before an OTAU start
  //  Persistent: No
  #define CS_ZCL_OTAU_MAX_RETRY_COUNT 3
  
  // The default address of an upgrade server
  // 
  //  The parameter indicates how the OTAU client will search for OTAU servers in the
  // network. If one of broadcast addresses is specified, the client will attempt to
  // find all devices supporting the OTAU server cluster and will request new images
  // from the first server that will respond. Otherwise, the client will try to
  // connect to a particular device with the specified extended address.
  // 
  //  The parameter is valid for OTAU clients only.
  // 
  //  Value range: any 64-bit value:
  //  0x0000000000000000ull, 0xFFFFFFFFFFFFFFFFull - a server discovery request is
  // broadcast
  //  otherwise, the client tries to connect to a particular node
  // 
  // 
  //  C-type: ExtAddr_t
  //  Can be set: at any time before an OTAU start
  //  Persistent: No
  #define CS_ZCL_OTAU_DEFAULT_UPGRADE_SERVER_IEEE_ADDRESS 0xFFFFFFFFFFFFFFFFull
  
  // Indicates that image page request are used to load an image
  // 
  //  If the parameter is set to 1 the OTAU client will use image page requests
  // (rather than image block requests) to load an application image from the OTAU
  // server. In this case the server will send a whole page (consisting of multiple
  // blocks) without requesting an APS acknowledgement for each block. The client
  // marks not-delivered blocks and sends an image block request for each of missed
  // blocks after the transmission on the page finishes.
  // 
  //  If the parameter is set to 0 image block requests will be used. The APS
  // acknowledgement is sent for each of received blocks. If any of the blocks is
  // missing loading of the image is restarted.
  // 
  //  The parameter is valid only for OTAU clients.
  // 
  //  Value range: 1 or 0
  //  C-type: uint8_t
  //  Can be set: at compile time only
  //  Persistent: No
  #define CS_ZCL_OTAU_IMAGE_PAGE_REQUEST_ENABLE 1
  //#define CS_ZCL_OTAU_IMAGE_PAGE_REQUEST_ENABLE 0
#endif //

//-----------------------------------------------
//CS_ZCL_OTAU_IMAGE_PAGE_REQUEST_ENABLE == 1
//-----------------------------------------------
#if (CS_ZCL_OTAU_IMAGE_PAGE_REQUEST_ENABLE == 1)
  // Period in milliseconds between two image block responses sent from the OTAU
  // server
  // 
  //  The parameter indicates how fast the OTAU server shall send data (via the image
  // block response command) to the OTAU client. The value is set on the client. The
  // server receives the value from the client. The server shall wait for, at
  // minimum, the period specified in the parameter before sending another block to
  // the client.
  // 
  //  The parameter is valid only for OTAU clients.
  // 
  //  Value range: not less than 200ms (according to the OTAU specification)
  //  C-type: uint16_t
  //  Can be set: at compile time only
  //  Persistent: No
  #define CS_ZCL_OTAU_IMAGE_PAGE_REQUEST_RESPONSE_SPACING 200
  
  // The page size - the number of bytes sent for a single image page request
  // 
  //  The parameter sets the number of bytes to be sent by the server for an image
  // page request sent by the OTAU client. A page is transmitted in several data
  // frames, one data frame for each block of data. The client, upon receiving
  // individual blocks, does not send an APS acknowledgement until all blocks for the
  // current page are not sent. Blocks that have not been delivered are requested by
  // the client via image block requests after loading of the current page finishes.
  // 
  //  The page size should be greater than or equal to 64 bytes.
  // 
  //  The parameter is valid only for OTAU clients.
  // 
  //  Value range: equal to or greater than 64
  //  C-type: uint16_t
  //  Can be set: at compile time only
  //  Persistent: No
  #define CS_ZCL_OTAU_IMAGE_PAGE_REQUEST_PAGE_SIZE 256
#endif

//-----------------------------------------------
//APP_DEVICE_TYPE_COMBINED_INTERFACE
//-----------------------------------------------
#ifdef APP_DEVICE_TYPE_COMBINED_INTERFACE
  //-----------------------------------------------
  //APP_USE_OTAU == 1
  //-----------------------------------------------
  #if (APP_USE_OTAU == 1)
    // OTAU device role
    #define OTAU_SERVER
    //#define OTAU_CLIENT
  #endif
#else
  //-----------------------------------------------
  //APP_USE_OTAU == 1
  //-----------------------------------------------
  #if (APP_USE_OTAU == 1)
    // Enable this option if hardware support for AES is present. This has dependency
    // on bootloader support and OTAU application support.
    #define USE_IMAGE_SECURITY 0
    //#define USE_IMAGE_SECURITY 1
    
    //-----------------------------------------------
    //USE_IMAGE_SECURITY == 1
    //-----------------------------------------------
    #if (USE_IMAGE_SECURITY == 1)
      #define IMAGE_KEY {0x01, 0x12, 0x23, 0x34, 0x45, 0x56, 0x67, 0x78, 0x89, 0x90, 0x99, 0x88, 0x77, 0x66, 0x55, 0x44}
      
      #define IMAGE_IV {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    #endif
    
    // OTAU device role
    #define OTAU_CLIENT
    //#define OTAU_SERVER
  #endif
#endif //


#include <appConsts.h>

#endif // _CONFIGURATION_H_
