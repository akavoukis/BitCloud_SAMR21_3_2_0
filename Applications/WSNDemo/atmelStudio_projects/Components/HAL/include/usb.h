/**************************************************************************//**
  \file  usb.h

  \brief The header file describes the usb interface

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:
    17/07/08 A. Khromykh - Created
 ******************************************************************************/
/******************************************************************************
 *   WARNING: CHANGING THIS FILE MAY AFFECT CORE FUNCTIONALITY OF THE STACK.  *
 *   EXPERT USERS SHOULD PROCEED WITH CAUTION.                                *
 ******************************************************************************/

#ifndef _USB_H
#define _USB_H

/******************************************************************************
                   Define(s) section
******************************************************************************/
// \cond
// USB device API return values
// Indicates the operation was successful
#define STATUS_SUCCESS             0
// Endpoint/device is already busy
#define STATUS_BUSY                1
// Operation has been aborted
#define STATUS_ABORTED             2
// Operation has been aborted because the device was configured
#define STATUS_RESET               3

// USB device states
// The device is currently suspended
#define DEVICE_SUSPENDED            0
// USB cable is plugged into the device
#define DEVICE_ATTACHED             1
// Host is providing +5V through the USB cable
#define DEVICE_POWERED              2
// Device has been reset
#define DEVICE_DEFAULT              3
// The device has been given an address on the bus
#define DEVICE_ADDRESS              5
// A valid configuration has been selected
#define DEVICE_CONFIGURED           6
// \endcond

/******************************************************************************
                   Types section
******************************************************************************/
// transaction callback type
typedef void (* TransferCallback_t)(void *pArg, uint8_t status, uint16_t transferred, uint16_t remaining);

BEGIN_PACK
// Usb endpoint descriptor
typedef struct PACK
{
  uint8_t  bLength;          // Size of the descriptor in bytes
  uint8_t  bDescriptorType;  // Descriptor type
  uint8_t  bEndpointAddress; // Address and direction of the endpoint
  uint8_t  bmAttributes;     // Endpoint type and additional characteristics (for isochronous endpoints)
  uint16_t wMaxPacketSize;   // Maximum packet size (in bytes) of the endpoint
  uint8_t  bInterval;        // Polling rate of the endpoint
} HAL_UsbEndPointDescptr_t;
END_PACK

/******************************************************************************
                   Prototypes section
******************************************************************************/
/**************************************************************************//**
\brief Registers user's request handler

\ingroup hal_usb

The request handler should cast its argument to the UsbRequest_t* type and
check the \c bRequest field to find out request's type. Request's codes of
interest include
\li 5 - the USB device shall set its address, extracted from the request,
    using the HAL_SetAddress() function (the USB device may need to send the
    confirmation to the host via HAL_UsbWrite() function first)
\li 6 - the host requests a certain descriptor from the USB device
\li 9 - the USB device shall set a certain configuration with the given number
    via the HAL_SetConfiguration() function and configure endpoints using
    the HAL_ConfigureEndpoint() function

For complete specification of requests and corresponding actions refer to
USB specification. Also see \c BitCloud\Components\HAL\drivers\USBClasses\
component, which contains implementation of certain USB devices.

\param[in]
  f - pointer to user's callback
******************************************************************************/
void HAL_RegisterRequestHandler(void (* f)(uint8_t *req));

/**************************************************************************//**
\brief Registers user's end of bus reset handler

\ingroup hal_usb

The end of bus reset handler is called when the host resets the bus and restarts
the USB device. The handler is always called previous to any request handller
executions and may even be used to set the request handler.

\param[in]
  f - pointer to user's callback
******************************************************************************/
void HAL_RegisterEndOfBusResetHandler(void (* f)(void));

/**************************************************************************//**
\brief Registers user's resume handler

\ingroup hal_usb

\param[in]
  f - pointer to user's callback
******************************************************************************/
void HAL_RegisterResumeHandler(void (* f)(void));

/**************************************************************************//**
\brief Registers user's suspend handler

\ingroup hal_usb

\param[in]
  f - pointer to user's callback
******************************************************************************/
void HAL_RegisterSuspendHandler(void (* f)(void));

/**************************************************************************//**
\brief Configures an endpoint according to its Endpoint Descriptor.

\ingroup hal_usb

\param[in]
  descriptor - Pointer to an Endpoint descriptor.
******************************************************************************/
void HAL_ConfigureEndpoint(HAL_UsbEndPointDescptr_t *descriptor);

/**************************************************************************//**
\brief Sends data through a USB endpoint. Sets up the transfer descriptor,
writes one or two data payloads (depending on the number of FIFO bank
for the endpoint) and then starts the actual transfer. The operation is
complete when all the data has been sent.

\ingroup hal_usb

Data will not be sent immediately after calling this function, but only
when the host initiates the corresponding transaction. Descriptors requested
by the host are sent using this function as well.

If the size of the buffer is greater than the size of the endpoint
(or twice the size if the endpoint has two FIFO banks), then the buffer
must be kept allocated until the transfer is finished. This means that
it is not possible to declare it on the stack (i.e. as a local variable
of a function which returns after starting a transfer).

\param[in]
  eptnum - Endpoint number.
\param[in]
  data - Pointer to a buffer with the data to send.
\param[in]
  size - Size of the data buffer.
\param[in]
  callback - Optional callback function to invoke when the transfer is complete;
             can be set to NULL.
\param[in]
  argument - Optional argument to the callback function.

\return
  STATUS_SUCCESS if the transfer has been started; otherwise, the
  corresponding error status code.
******************************************************************************/
uint8_t HAL_UsbWrite(uint8_t eptnum, void *data, uint32_t size, TransferCallback_t callback, void *argument);

/**************************************************************************//**
\brief Reads incoming data on an USB endpoint This methods sets the transfer
descriptor and activate the endpoint interrupt. The actual transfer is
then carried out by the endpoint interrupt handler. The Read operation
finishes either when the buffer is full, or a short packet (inferior to
endpoint maximum  size) is received.

\ingroup hal_usb

The buffer must be kept allocated until the transfer is finished. Data transfer
may not start immediately after the function has been called. Data will be read
when the host initiates a transaction for this data transfer. The function
may be called at any time, but the callback function will be called when the
data is fuly traserred to the USB device.

\param[in]
  eptnum - Endpoint number.
\param[in]
  data - Pointer to a data buffer.
\param[in]
  size - Size of the data buffer in bytes.
\param[in]
  callback - End-of-transfer callback function; must not be set to NULL.
\param[in]
  argument - Optional argument to the callback function.

\return
  STATUS_SUCCESS if the read operation has been started; otherwise,
  the corresponding error code.
******************************************************************************/
uint8_t HAL_UsbRead(uint8_t eptnum, void *data, uint32_t size, TransferCallback_t callback, void *argument);

/**************************************************************************//**
\brief Sets the HALT feature on the given endpoint (if not already in this state).

\ingroup hal_usb

\param[in]
  eptnum - Endpoint number.
******************************************************************************/
void HAL_Halt(uint8_t eptnum);

/**************************************************************************//**
\brief Clears the Halt feature on the given endpoint.

\ingroup hal_usb

\param[in]
  eptnum - Endpoint number.
******************************************************************************/
void HAL_Unhalt(uint8_t eptnum);

/**************************************************************************//**
\brief Returns the current Halt status of an endpoint.

\ingroup hal_usb

\param[in]
  eptnum - Endpoint number.

\return
  1 - if the endpoint is currently halted;
  0 - otherwise.
******************************************************************************/
uint8_t HAL_IsHalted(uint8_t eptnum);

/**************************************************************************//**
\brief Causes the given endpoint to acknowledge the next packet it receives with
a STALL handshake, preventing the host from repeating the same transaction

\ingroup hal_usb

The function may be used to notify the host that current transaction should not
be repeated when, for example, the descriptor requested in the transaction is
supported on the USB device (in this case call HAL_Stall(0)). If this function
is not called in such case, the host repeat the transaction, sending requests
that cannot be carried out by the USB device.

\param[in]
  eptnum - Endpoint number.

\return
  STATUS_SUCCESS or STATUS_BUSY.
******************************************************************************/
uint8_t HAL_Stall(uint8_t eptnum);

/**************************************************************************//**
\brief Sets the device address to the given value.

\ingroup hal_usb

The function shall be called to set USB device's address when the
host requests this action and the request handler is invoked.

\param[in]
  address - New device address.
******************************************************************************/
void HAL_SetAddress(uint8_t *address);

/**************************************************************************//**
\brief Sets the current device configuration.

\ingroup hal_usb

The function shall be called to set a particular configuration when the
host requests this action and the request handler is invoked.

\param[in]
  cfgnum - Configuration number to set.
******************************************************************************/
void HAL_SetConfiguration(uint8_t cfgnum);

/**************************************************************************//**
\brief Initializes the USB driver. This function must be called before host
bus reset and after pull up is connected to D+. After pull up was connected
to D+ host resets device with 100ms delay.

\ingroup hal_usb

\param[in]
  reqMem - Memory for usb request. Memory is allocated by user.
******************************************************************************/
void HAL_UsbInit(uint8_t *reqMem);

/**************************************************************************//**
\brief Returns the current state of the USB device.

\ingroup hal_usb

\return
  Device current state.
******************************************************************************/
uint8_t HAL_GetState(void);

#endif /* _USB_H */
