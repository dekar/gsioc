/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : usb_desc.c
* Author             : MCD Application Team
* Version            : V2.2.1
* Date               : 09/22/2008
* Description        : Descriptors for Virtual Com Port Demo
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "usb_lib.h"
#include "usb_desc.h"
/* USB Standard Device Descriptor */

//#include "devConfig.h"

const u8 Virtual_Com_Port_ConfigDescriptor[] =
  {
  //Configuation Descriptor
        0x09,   // bLength: Configuation Descriptor size
        USB_CONFIGURATION_DESCRIPTOR_TYPE,      // bDescriptorType: Configuration
        DEVICE_SIZ_CONFIG_DESC,       // wTotalLength:no of returned bytes
        0x00,
        0x02,   // bNumInterfaces: 2 interface
        0x01,   // bConfigurationValue: Configuration value
        0x00,   // iConfiguration: Index of string descriptor describing the configuration
        0xC0,   // bmAttributes: self powered
        0x00,   // MaxPower 0 mA
//Interface Descriptor
        0x09,   // bLength: Interface Descriptor size
        USB_INTERFACE_DESCRIPTOR_TYPE,  // bDescriptorType: Interface
                        // Interface descriptor type
        0x00,   // bInterfaceNumber: Number of Interface
        0x00,   // bAlternateSetting: Alternate setting
        0x01,   // bNumEndpoints: One endpoints used
        0x02,   // bInterfaceClass: Communication Interface Class
        0x02,   // bInterfaceSubClass: Abstract Control Model
        0x01,   // bInterfaceProtocol: Common AT commands
        0x00,   // iInterface:
//Header Functional Descriptor
        0x05,   // bLength: Endpoint Descriptor size
        0x24,   // bDescriptorType: CS_INTERFACE
        0x00,   // bDescriptorSubtype: Header Func Desc
        0x10,   // bcdCDC: spec release number
        0x01,
//Call Managment Functional Descriptor
        0x05,   // bFunctionLength
        0x24,   // bDescriptorType: CS_INTERFACE
        0x01,   // bDescriptorSubtype: Call Management Func Desc
        0x00,   // bmCapabilities: D0+D1
        0x01,   // bDataInterface: 1
//ACM Functional Descriptor
        0x04,   // bFunctionLength
        0x24,   // bDescriptorType: CS_INTERFACE
        0x02,   // bDescriptorSubtype: Abstract Control Management desc
        0x02,   // bmCapabilities
//Union Functional Descriptor
        0x05,   // bFunctionLength
        0x24,   // bDescriptorType: CS_INTERFACE
        0x06,   // bDescriptorSubtype: Union func desc
        0x00,   // bMasterInterface: Communication class interface
        0x01,   // bSlaveInterface0: Data Class Interface
//Endpoint 2 Descriptor
        0x07,   // bLength: Endpoint Descriptor size
        USB_ENDPOINT_DESCRIPTOR_TYPE,   // bDescriptorType: Endpoint
        0x82,   // bEndpointAddress: (IN2)
        0x03,   // bmAttributes: Interrupt
        ENDP2_TX_SIZE,      // wMaxPacketSize:
        0x00,
        0x10,   // bInterval:
//Data class interface descriptor
        0x09,   // bLength: Endpoint Descriptor size
        USB_INTERFACE_DESCRIPTOR_TYPE,  // bDescriptorType:
        0x01,   // bInterfaceNumber: Number of Interface
        0x00,   // bAlternateSetting: Alternate setting
        0x02,   // bNumEndpoints: Two endpoints used
        0x0A,   // bInterfaceClass: CDC
        0x00,   // bInterfaceSubClass:
        0x00,   // bInterfaceProtocol:
        0x00,   //iInterface:
//Endpoint 3 Descriptor
        0x07,   // bLength: Endpoint Descriptor size
        USB_ENDPOINT_DESCRIPTOR_TYPE,   // bDescriptorType: Endpoint
        0x03,   // bEndpointAddress: (OUT3)
        0x02,   // bmAttributes: Bulk
        ENDP3_RX_SIZE,             // wMaxPacketSize:
        0x00,
        0x10,   // bInterval: ignore for Bulk transfer
//Endpoint 1 Descriptor
        0x07,   // bLength: Endpoint Descriptor size
        USB_ENDPOINT_DESCRIPTOR_TYPE,   // bDescriptorType: Endpoint
        0x81,   // bEndpointAddress: (IN1)
        0x02,   // bmAttributes: Bulk
        ENDP1_TX_SIZE,             // wMaxPacketSize:
        0x00,
        0x10    // bInterval: ignore for Bulk transfer

  /*
    //Configuation Descriptor
    0x09,   // bLength: Configuation Descriptor size
    USB_CONFIGURATION_DESCRIPTOR_TYPE,      // bDescriptorType: Configuration
    DEVICE_SIZ_CONFIG_DESC,       // wTotalLength:no of returned bytes
    0x00,
    0x02,   // bNumInterfaces: 2 interface
    0x01,   // bConfigurationValue: Configuration value
    0x00,   // iConfiguration: Index of string descriptor describing the configuration
    0xC0,   // bmAttributes: self powered
    0x32,   // MaxPower 0 mA
    //Interface Descriptor
    0x09,   // bLength: Interface Descriptor size
    USB_INTERFACE_DESCRIPTOR_TYPE,  // bDescriptorType: Interface
    // Interface descriptor type
    0x00,   // bInterfaceNumber: Number of Interface
    0x00,   // bAlternateSetting: Alternate setting
    0x02,   // bNumEndpoints: One endpoints used
    0x00,   // bInterfaceClass: USER
    0x00,   // bInterfaceSubClass: USER
    0x00,   // bInterfaceProtocol: USER
    0x00,   // iInterface:

    //Endpoint 1 Descriptor
    0x07,   // bLength: Endpoint Descriptor size
    USB_ENDPOINT_DESCRIPTOR_TYPE,   // bDescriptorType: Endpoint
    0x81,   // bEndpointAddress: (IN1)
    0x03,   // bmAttributes: Interrupt
    ENDP1_TX_SIZE,      // wMaxPacketSize:
    0x00,
    0x10,   // bInterval:
    //Endpoint 2 Descriptor
    0x07,   // bLength: Endpoint Descriptor size
    USB_ENDPOINT_DESCRIPTOR_TYPE,   // bDescriptorType: Endpoint
    0x02,   // bEndpointAddress: (OUT2)
    0x03,   // bmAttributes: Interrupt
    ENDP2_RX_SIZE,      // wMaxPacketSize:
    0x00,
    0x10,   // bInterval:


    //Data class interface descriptor
    0x09,   // bLength: Endpoint Descriptor size
    USB_INTERFACE_DESCRIPTOR_TYPE,  // bDescriptorType:
    0x01,   // bInterfaceNumber: Number of Interface
    0x00,   // bAlternateSetting: Alternate setting
    0x02,   // bNumEndpoints: Two endpoints used
    0x02,   // bInterfaceClass: CDC
    0x02,   // bInterfaceSubClass:
    0x00,   // bInterfaceProtocol:
    0x00,   // iInterface:
    //Header
    0x05,// bFunctionLength, Descriptor size in bytes
    0x24,// bDescriptorType, CS_INTERFACE
    0x00,// bDescriptorSubtype, Header Functional Descriptor
    0x10,0x01,// bcdCDC

     // Abstract Control Management Functional Descriptor
    0x04,// bDescriptorLength, Descriptor size in bytes
    0x24,// bDescriptorType, CS_INTERFACE
    0x02,// bDescriptorSubtype, ACM Functional Descriptor
    0x06,// bmCapabilities

    // Union Functional Descriptor
    0x05,// bFunctionLength, Descriptor size in bytes
    0x24,// bDescriptorType, CS_INTERFACE
    0x06,// bDescriptorSubtype, Union Functional Descriptor
    0x00,// bMasterInterface
    0x01,// bSlaveInterface0

    // Call Management Functional Descriptor
    0x05,// bFunctionLength, Descriptor size in bytes
    0x24,// bDescriptorType, CS_INTERFACE
    0x01,// bDescriptorSubtype, Call Management Funct.Desc.
    0x03,// bmCapabilities
    0x01,// bDataInterface

    //Endpoint 3 Descriptor
    0x07,   // bLength: Endpoint Descriptor size
    USB_ENDPOINT_DESCRIPTOR_TYPE,   // bDescriptorType: Endpoint
    0x83,   // bEndpointAddress: (IN3)
    0x02,   // bmAttributes: Bulk
    ENDP3_TX_SIZE,             // wMaxPacketSize:
    0x00,
    0x00,   // bInterval: ignore for Bulk transfer
    //Endpoint 4 Descriptor
    0x07,   // bLength: Endpoint Descriptor size
    USB_ENDPOINT_DESCRIPTOR_TYPE,   // bDescriptorType: Endpoint
    0x04,   // bEndpointAddress: (OUT4)
    0x02,   // bmAttributes: Bulk
    ENDP4_RX_SIZE,             // wMaxPacketSize:
    0x00,
    0x00,    // bInterval*/
  };

/* USB String Descriptors */
const u8 Virtual_Com_Port_StringLangID[DEVICE_SIZ_STRING_LANGID] =
  {
    DEVICE_SIZ_STRING_LANGID,
    USB_STRING_DESCRIPTOR_TYPE,
    0x09,
    0x04 /* LangID = 0x0409: U.S. English */
  };

const u8 Virtual_Com_Port_StringVendor[DEVICE_SIZ_STRING_VENDOR] =
  {
    DEVICE_SIZ_STRING_VENDOR,     /* Size of Vendor string */
    USB_STRING_DESCRIPTOR_TYPE,             /* bDescriptorType*/
    /* Manufacturer: "STMicroelectronics" */
    'K', 0, 'B', 0, ' ', 0, 'L', 0, 'e', 0, 's', 0
  };

const u8 Virtual_Com_Port_StringProduct[DEVICE_SIZ_STRING_PRODUCT] =
  {
    DEVICE_SIZ_STRING_PRODUCT,          /* bLength */
    USB_STRING_DESCRIPTOR_TYPE,        /* bDescriptorType */
    /* Product name: "STM32 Virtual COM Port" */
    'G', 0, 'S', 0, 'I', 0, 'O', 0, 'C', 0, ' ', 0, 'c', 0, 'o', 0,
    'n', 0, 't', 0, 'r', 0
  };

const u8 Virtual_Com_Port_StringSerial[DEVICE_SIZ_STRING_SERIAL] =
  {
    DEVICE_SIZ_STRING_SERIAL,           /* bLength */
    USB_STRING_DESCRIPTOR_TYPE,                   /* bDescriptorType */
    'v', 0, '0', 0, '.', 0, '5', 0, '1', 0
  }
  ;/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
