/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : usb_desc.h
* Author             : MCD Application Team
* Version            : V2.2.1
* Date               : 09/22/2008
* Description        : Descriptor Header for Virtual COM Port Device
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USB_DESC_H
#define __USB_DESC_H

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported define -----------------------------------------------------------*/
#define USB_DEVICE_DESCRIPTOR_TYPE              0x01
#define USB_CONFIGURATION_DESCRIPTOR_TYPE       0x02
#define USB_STRING_DESCRIPTOR_TYPE              0x03
#define USB_INTERFACE_DESCRIPTOR_TYPE           0x04
#define USB_ENDPOINT_DESCRIPTOR_TYPE            0x05


#define DEVICE_SIZ_DEVICE_DESC        18
#define DEVICE_SIZ_CONFIG_DESC        9 + 9 + 5 + 5 + 4 + 5 + 7 + 9 + 7 + 7
#define DEVICE_SIZ_STRING_LANGID      4
#define DEVICE_SIZ_STRING_VENDOR      14
#define DEVICE_SIZ_STRING_PRODUCT     24
#define DEVICE_SIZ_STRING_SERIAL      12

#define STANDARD_ENDPOINT_DESC_SIZE             0x09

/* Exported functions ------------------------------------------------------- */

extern const u8 Virtual_Com_Port_ConfigDescriptor[DEVICE_SIZ_CONFIG_DESC];

extern const u8 Virtual_Com_Port_StringLangID[DEVICE_SIZ_STRING_LANGID];
extern const u8 Virtual_Com_Port_StringVendor[DEVICE_SIZ_STRING_VENDOR];
extern const u8 Virtual_Com_Port_StringProduct[DEVICE_SIZ_STRING_PRODUCT];
extern const u8 Virtual_Com_Port_StringSerial[DEVICE_SIZ_STRING_SERIAL];

#endif /* __USB_DESC_H */
/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
