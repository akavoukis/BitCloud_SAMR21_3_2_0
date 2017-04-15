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

// Enables or disables support for OTA Upgrade.
#define APP_USE_OTAU 0
//#define APP_USE_OTAU 1

// Enables the ZLL_TaskHandler()
#define _SYS_ZLL_TASK_

#define APP_DEVICE_TYPE_COLOR_SCENE_REMOTE 1

#define APP_DEVICE_TYPE_ON_OFF_LIGHT 3

#define APP_DEVICE_TYPE_DIMMABLE_LIGHT 4

#define APP_DEVICE_TYPE_COLOR_LIGHT 5

#define APP_DEVICE_TYPE_EXTENDED_COLOR_LIGHT 6

#define APP_DEVICE_TYPE_TEMPERATURE_COLOR_LIGHT 7

#define APP_DEVICE_TYPE_BRIDGE 2

// Select ZLL device type: either Color Scene Remote or Light
#define APP_ZLL_DEVICE_TYPE APP_DEVICE_TYPE_COLOR_SCENE_REMOTE
//#define APP_ZLL_DEVICE_TYPE APP_DEVICE_TYPE_COLOR_LIGHT
//#define APP_ZLL_DEVICE_TYPE APP_DEVICE_TYPE_EXTENDED_COLOR_LIGHT
//#define APP_ZLL_DEVICE_TYPE APP_DEVICE_TYPE_DIMMABLE_LIGHT
//#define APP_ZLL_DEVICE_TYPE APP_DEVICE_TYPE_BRIDGE
//#define APP_ZLL_DEVICE_TYPE APP_DEVICE_TYPE_TEMPERATURE_COLOR_LIGHT
//#define APP_ZLL_DEVICE_TYPE APP_DEVICE_TYPE_ON_OFF_LIGHT

// Enables or disables certification testing extension
#define APP_ENABLE_CERTIFICATION_EXTENSION 0
//#define APP_ENABLE_CERTIFICATION_EXTENSION 1

// Specifies if logging enabled
#define APP_DEVICE_EVENTS_LOGGING 1
//#define APP_DEVICE_EVENTS_LOGGING 0

#define APP_ENABLE_CONSOLE 1
//#define APP_ENABLE_CONSOLE 0

// Activate channel scanning on startup for FN Light/remote devices
#define APP_SCAN_ON_STARTUP 0
//#define APP_SCAN_ON_STARTUP 1

// Fix PAN settings for debug purpose
#define APP_ZLL_FIXED_PAN 0
//#define APP_ZLL_FIXED_PAN 1

/* Enable wear-leveling version of PDS */
#define PDS_ENABLE_WEAR_LEVELING 1

/* If PDS uses external flash. this should be uncommented. */
//#define PDS_USE_EXTERNAL_FLASH

/* If Bootloader will be used in parallel with application. this should be commented. */
#define PDS_NO_BOOTLOADER_SUPPORT

/* ZigBee Platform NV items list*/
#define PERSISTENT_NV_ITEMS_PLATFORM    NWK_SECURITY_COUNTERS_MEM_ID
/* Application NV items list */
#define PERSISTENT_NV_ITEMS_APPLICATION 0xFFFu

#if APP_ZLL_DEVICE_TYPE == APP_DEVICE_TYPE_COLOR_SCENE_REMOTE
  #define ZIGBEE_END_DEVICE
#endif

#define ZCL_SUPPORT 1

// Shall be enabled for Atmel generic ZLL Applications.
#define ATMEL_APPLICATION_SUPPORT 1

#define BSP_SUPPORT BOARD_SAMR21_XPRO
//#define BSP_SUPPORT BOARD_SAMR21_ZLLEK
//#define BSP_SUPPORT BOARD_SAMR21_CUSTOM
//#define BSP_SUPPORT BOARD_FAKE

// Defines primary serial interface type to be used by application.
#define APP_INTERFACE APP_INTERFACE_USART

// Defines USART interface name to be used by application.
#define APP_USART_CHANNEL USART_CHANNEL_0
//#define APP_USART_CHANNEL USART_CHANNEL_1

// Size of the buffer used by the MAC component for data frames
#define CS_MAC_FRAME_RX_BUFFER_SIZE 300

// 16-bit manufacturer code allocated by the ZigBee Alliance. It is being used in
// payload of OTA commands as well as for filtering of manufacturer-specific ZCL
// commands and attributes. See ZigBee Manufacturer Code Database, 053874r16, Atmel
// code.
#define CS_MANUFACTURER_CODE 0x1014

// Channels set configuration

#define APP_PRIMARY_CHANNELS_MASK     0x2108800 //standard (11, 15, 20, 25)
#define APP_SECONDARY_CHANNELS_MASK   0x5EF7000 //standard

//#define APP_PRIMARY_CHANNELS_MASK   0x4211000 //standard+1 (12, 16, 21, 26)
//#define APP_SECONDARY_CHANNELS_MASK 0x3DEE800 //standard+1

//#define APP_PRIMARY_CHANNELS_MASK   0x04A2000 //standard+2 (13, 17, 19, 22)
//#define APP_SECONDARY_CHANNELS_MASK 0x7B5D800 //standard+2

//#define APP_PRIMARY_CHANNELS_MASK   0x1844000 //standard+3 (14, 18, 23, 24)
//#define APP_SECONDARY_CHANNELS_MASK 0x67BB800 //standard+3

// A period in ms of polling a parent for data by an end device. On a sleeping end
// device the parameter determines a period with which poll requests are sent to
// the parent while the end device is awaken. A parent of a sleeping end device
// uses the parameter to calculate estimates of the time when the next poll request
// from a child will be received.
#define CS_INDIRECT_POLL_RATE 500

// Maximum amount of a failed sync frame. Before attempting to rejoin.
// 
//  Value range: at minimum 1, the maximum value 255
//  C-type: uint8_t
//  Can be set: at compile time only
#define CS_ZDO_MAX_SYNC_FAIL_AMOUNT 0xff

// The maximum number of retries of send frame to the parent. Before attempting to
// rejoin.
// 
//  Value range: at minimum 1, the maximum value 255
//  C-type: uint8_t
//  Can be set: at compile time only
#define CS_ZDO_PARENT_LINK_RETRY_THRESHOLD 0xff

// While scanning channels during network join the node keeps listening to each
// channel specified by the ::CS_CHANNEL_MASK for a period of time calculated
// according to the formula that for the 2.4GHz frequency band is: 960 * 16 * (2
// raised to a power n + 1) microseconds, providing n is a value of this parameter.
// Note that the formula for the Sub-GHz employs another constant instead of 16.
#define CS_SCAN_DURATION 5

// Determines the maximum number of attempts to enter a network performed by the
// stack during network start. Upon each attempt ZDO sends a beacon request and
// collects beacon responses from nearby devices all over again.
#define CS_ZDO_JOIN_ATTEMPTS 1

// 64-bit Unique Identifier (UID) determining the device extended address. If this
// value is 0 stack will try to read hardware UID from external UID or EEPROM chip.
// at startup. Location of hardware UID is platform dependend and it may not be
// available on all platforms. If the latter case then UID value must be provided
// by user via this parameter. This parameter must be unique for each device in a
// network. This should not be 0 for Coordinator.
#define CS_UID 0x0LL

// If the parameter being switched between 0xff and 0x00, determines whether the
// device accepts or not a child joining the network via MAC association, that is,
// if the joining device does not possess the PANID value of the network and its
// PANID parameter is set to 0.
#define CS_PERMIT_DURATION 0x00
//MAC association is on.
//#define CS_PERMIT_DURATION 0xFF

// Is used to calculate the length of time after which a not responding end device
// child is considered lost. A sleeping end device is considered lost and a
// corresponding notification is raised on the parent, if the end device does not
// polls for data for the time span which duration is calculated by the following
// formula: CS_NWK_END_DEVICE_MAX_FAILURES * (CS_END_DEVICE_SLEEP_PERIOD +
// CS_INDIRECT_POLL_RATE)
#define CS_NWK_END_DEVICE_MAX_FAILURES 4

// Maximum amount of records in the Group Table.
// 
//  The Group Table size cannot be 0. The group table stores pairs of a group
// address and an endpoint. Upon receiving a frame addressed to members of a
// certain group which include the current node as well the stack fires indications
// on all endpoints registered with the group address.
#define CS_GROUP_TABLE_SIZE 10

// Maximum amount of records in the Neighbor Table.
// 
//  The parameter determines the size of the neighbor table which is used to store
// beacon responses from nearby devices. The parameter puts an upper bound over the
// amount of child devices possible for the node.
#define CS_NEIB_TABLE_SIZE 10

// Maximum amount of records in the network Route Table.
// 
//  The parameter sets the maximum number of records that can be kept in the NWK
// route table. The table is used by NWK to store information about established
// routes. Each table entry specifies the next-hop short address for a route from
// the current node to a given destination node. The table is being filled
// automatically during route discovery. An entry is added when a route is
// discovered.
#define CS_ROUTE_TABLE_SIZE 10

// Maximum amount of records in the network Route Discovery Table.
// 
//  The parameter specifies the size of the route discovery table used by NWK to
// store next-hop addresses of the nodes for routes that are not yet established.
// Upon exhausting the capacity of the table, the stack starts rewriting old
// entries. If the size of the route table is big enough after all used routes are
// established the table may not be used.
#define CS_ROUTE_DISCOVERY_TABLE_SIZE 10

// Maximim amount of records in the Binding Table
// 
//  The parameter sets the size of the binding table used by APS to store binding
// links, which are structures containing information about source and destination
// extended addresses and endpoints for unicast bindings and just group addresses
// as destinations for group bindings. If the binding is going to be applied to
// send a data frame, then the corresponding entry shall be first inserted into the
// table via the APS_BindingReq() function.
#define CS_APS_BINDING_TABLE_SIZE 1

// The number of buffers for data requests on the APS layer.
// 
//  The parameter specifies the number of buffers that are allocated by APS to
// store data requests parameters. The parameter puts an upper bound to the number
// of data requests that can be processed by APS simultaneously. If all buffers are
// in use and a new data request appears, it is kept in a queue until a buffer is
// released.
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
#define CS_APS_ACK_FRAME_BUFFERS_AMOUNT 3

//-----------------------------------------------
//APP_ZLL_DEVICE_TYPE == APP_DEVICE_TYPE_COLOR_SCENE_REMOTE
//-----------------------------------------------
#if (APP_ZLL_DEVICE_TYPE == APP_DEVICE_TYPE_COLOR_SCENE_REMOTE)
  // End device sleep period given in milliseconds.
  // 
  //  On an end device this parameter determines the duration of a sleep period.
  // Falling asleep is performed with the ZDO_SleepReq() request. After sleeping
  // period exceeds the node is awakened and the application receives an indication
  // via ZDO_WakeUpInd(). If the parameter's value is 0, then after the node falls
  // asleep it can only be awakened by a hardware interrupt; a callback for a given
  // IRQ is registered via HAL_RegisterIrq().
  // 
  //  On a router or the coordinator, the parameter is used in two ways:
  // 
  //  1) To remove information about lost child end devices. If a parent receives no
  // data polls or data frames from the child end device for
  // CS_NWK_END_DEVICE_MAX_FAILURES * (CS_END_DEVICE_SLEEP_PERIOD +
  // CS_INDIRECT_POLL_RATE) ms, then it assumes it to be lost and deletes all
  // information about such child.
  // 
  //  2) To determine whether to store or drop a message addressed to a child end
  // device. The parent estimates the time when its child end device will wake up by
  // adding this value to the moment when the last poll request has been received. If
  // the time till end device wake up is greater than CS_MAC_TRANSACTION_TIME the
  // frame is stored. Otherwise, the frame is dropped.
  #undef CS_END_DEVICE_SLEEP_PERIOD
  #define CS_END_DEVICE_SLEEP_PERIOD 0L
  
  // Amount of buffers on NWK layer used to keep incoming and outgoing frames. This
  // parameters affects how many children of a parent are able to get broadcat
  // messages.
  #define CS_NWK_BUFFERS_AMOUNT 5
#endif

//-----------------------------------------------
//APP_ZLL_DEVICE_TYPE != APP_DEVICE_TYPE_COLOR_SCENE_REMOTE
//-----------------------------------------------
#if (APP_ZLL_DEVICE_TYPE != APP_DEVICE_TYPE_COLOR_SCENE_REMOTE)
  // Activate channel scanning on startup for FN Light/remote devices
  #undef APP_SCAN_ON_STARTUP
  #define APP_SCAN_ON_STARTUP 1
  //#define APP_SCAN_ON_STARTUP 0
  
  // LED driving method
  #define APP_USE_PWM
  
  // Red channel
  #define ENABLE_DITHERING_A 1
  //#define ENABLE_DITHERING_A 0
  
  // Green channel
  #define ENABLE_DITHERING_B 1
  //#define ENABLE_DITHERING_B 0
  
  // Blue channel
  #define ENABLE_DITHERING_C 1
  //#define ENABLE_DITHERING_C 0
  
  // PWM frequency in Hz
  #define APP_PWM_FREQUENCY 22000
  
  // Maximim amount of records in the Binding Table
  // 
  //  The parameter sets the size of the binding table used by APS to store binding
  // links, which are structures containing information about source and destination
  // extended addresses and endpoints for unicast bindings and just group addresses
  // as destinations for group bindings. If the binding is going to be applied to
  // send a data frame, then the corresponding entry shall be first inserted into the
  // table via the APS_BindingReq() function.
  #undef CS_APS_BINDING_TABLE_SIZE
  #define CS_APS_BINDING_TABLE_SIZE 10
  
  // End device sleep period given in milliseconds.
  // 
  //  On an end device this parameter determines the duration of a sleep period.
  // Falling asleep is performed with the ZDO_SleepReq() request. After sleeping
  // period exceeds the node is awakened and the application receives an indication
  // via ZDO_WakeUpInd(). If the parameter's value is 0, then after the node falls
  // asleep it can only be awakened by a hardware interrupt; a callback for a given
  // IRQ is registered via HAL_RegisterIrq().
  // 
  //  On a router or the coordinator, the parameter is used in two ways:
  // 
  //  1) To remove information about lost child end devices. If a parent receives no
  // data polls or data frames from the child end device for
  // CS_NWK_END_DEVICE_MAX_FAILURES * (CS_END_DEVICE_SLEEP_PERIOD +
  // CS_INDIRECT_POLL_RATE) ms, then it assumes it to be lost and deletes all
  // information about such child.
  // 
  //  2) To determine whether to store or drop a message addressed to a child end
  // device. The parent estimates the time when its child end device will wake up by
  // adding this value to the moment when the last poll request has been received. If
  // the time till end device wake up is greater than CS_MAC_TRANSACTION_TIME the
  // frame is stored. Otherwise, the frame is dropped.
  #define CS_END_DEVICE_SLEEP_PERIOD 3600000L
#endif //

// The maximum number of retries that will be performed by APS layer before
// reporting failed transmission.
// 
//  The parameter sets the number of attempts that will be made by APS layer to
// transmit a data frame. If all these attempts fail due to underlying layers
// failures, then APS response with an error status.
#define CS_APS_MAX_FRAME_RETRIES 1

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
  #define CS_ZCL_OTAU_DISCOVERED_SERVER_AMOUNT 1
  
  // The number of clients that the OTAU server can server simultaneously
  // 
  //  If this parameter equals 1, the OTAU server will upgrade devices in the network
  // one by one. However, the server can process more than one client sessions at a
  // time, if this parameter is greater than 1.
  #define CS_ZCL_OTAU_CLIENT_SESSION_AMOUNT 1
  
  // The interval in milliseconds between two attempts to find an upgrade server
  // 
  //  The parameter is valid for OTAU clients only.
  // 
  //  Value range: any 32-bit value
  //  C-type: uint32_t
  //  Can be set: at any time before an OTAU start
  #define CS_ZCL_OTAU_SERVER_DISCOVERY_PERIOD 60000
  
  // The interval in milliseconds between two successful attempts to query the server
  // 
  //  The parameter is valid only for OTAU clients.
  // 
  //  Value range: any 32-bit value
  //  C-type: uint32_t
  //  Can be set: at any time before an OTAU start
  #define CS_ZCL_OTAU_QUERY_INTERVAL 5000
  
  // Max retry count for commands (OTAU cluster, ZDO and APS) used for OTAU
  // 
  //  The parameter is valid only for OTAU clients.
  // 
  //  Value range: any 8-bit value
  //  C-type: uint8_t
  //  Can be set: at any time before an OTAU start
  #define CS_ZCL_OTAU_MAX_RETRY_COUNT 3
  
  // The default address of an upgrade server
  // 
  //  The parameter indicates how the OTAU client will search for OTAU servers in the
  // network. If one of broadcast addresses is specified, the client will attempt to
  // find all devices supporting the OTAU server cluster and will request new images
  // from the first server that will respond. Otherwise, the client will try to
  // connect to a particular device with the specified extended address.
  #define CS_ZCL_OTAU_DEFAULT_UPGRADE_SERVER_IEEE_ADDRESS 0xFFFFFFFFFFFFFFFFull
  
  // Indicates that image page request are used to load an image
  // 
  //  If the parameter is set to 1 the OTAU client will use image page requests
  // (rather than image block requests) to load an application image from the OTAU
  // server. In this case the server will send a whole page (consisting of multiple
  // blocks) without requesting an APS acknowledgement for each block. The client
  // marks not-delivered blocks and sends an image block request for each of missed
  // blocks after the transmission on the page finishes.
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
  #define CS_ZCL_OTAU_IMAGE_PAGE_REQUEST_RESPONSE_SPACING 200
  
  // The page size - the number of bytes sent for a single image page request
  // 
  //  The parameter sets the number of bytes to be sent by the server for an image
  // page request sent by the OTAU client. A page is transmitted in several data
  // frames, one data frame for each block of data. The client, upon receiving
  // individual blocks, does not send an APS acknowledgement until all blocks for the
  // current page are not sent. Blocks that have not been delivered are requested by
  // the client via image block requests after loading of the current page finishes.
  #define CS_ZCL_OTAU_IMAGE_PAGE_REQUEST_PAGE_SIZE 256
#endif

//-----------------------------------------------
//APP_ZLL_DEVICE_TYPE == APP_DEVICE_TYPE_BRIDGE
//-----------------------------------------------
#if (APP_ZLL_DEVICE_TYPE == APP_DEVICE_TYPE_BRIDGE)
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


#endif // _CONFIGURATION_H_
