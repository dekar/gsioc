/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : usb_conf.h
* Author             : MCD Application Team
* Version            : V2.2.1
* Date               : 09/22/2008
* Description        : Virtual COM Port Demo configuration  header
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USB_CONF_H
#define __USB_CONF_H

/*-------------------------------------------------------------*/
/* EP_NUM */
/* defines how many endpoints are used by the device */
/*-------------------------------------------------------------*/

#define EP_NUM                          (5)

/*-------------------------------------------------------------*/
/* --------------   Buffer Description Table  -----------------*/
/*-------------------------------------------------------------*/
/* buffer table base address */
/* buffer table base address */
#define BTABLE_SIZE   0x40
#define ENDP0_RX_SIZE 0x40
#define ENDP0_TX_SIZE 0x40
#define ENDP1_TX_SIZE 0x40
#define ENDP2_RX_SIZE 0x40
#define ENDP3_TX_SIZE 0x40
#define ENDP4_RX_SIZE 0x40



#define BTABLE_ADDRESS      (0x00)

/* EP0  */
/* rx/tx buffer base address */
#define ENDP0_RXADDR        BTABLE_ADDRESS + BTABLE_SIZE
#define ENDP0_TXADDR        ENDP0_RXADDR + ENDP0_RX_SIZE

/* EP1  */
/* tx buffer base address */
#define ENDP1_TXADDR        ENDP0_TXADDR + ENDP0_TX_SIZE
#define ENDP2_RXADDR        ENDP1_TXADDR + ENDP1_TX_SIZE
#define ENDP3_TXADDR        ENDP2_RXADDR + ENDP2_RX_SIZE
#define ENDP4_RXADDR        ENDP3_TXADDR + ENDP3_TX_SIZE
#if (ENDP4_RXADDR + ENDP4_RX_SIZE) > 512
    #error USBERROR_BUFEROVEROLAD
#endif


/*-------------------------------------------------------------*/
/* -------------------   ISTR events  -------------------------*/
/*-------------------------------------------------------------*/
/* IMR_MSK */
/* mask defining which events has to be handled */
/* by the device application software */
#define IMR_MSK (CNTR_CTRM  | CNTR_SOFM  | CNTR_RESETM )
//#define IMR_MSK (0xff00)

/*#define CTR_CALLBACK*/
/*#define DOVR_CALLBACK*/
/*#define ERR_CALLBACK*/
/*#define WKUP_CALLBACK*/
/*#define SUSP_CALLBACK*/
/*#define RESET_CALLBACK*/
/*#define SOF_CALLBACK*/
/*#define ESOF_CALLBACK*/

/* CTR service routines */
/* associated to defined endpoints */
//#define  EP1_IN_Callback   NOP_Process
#define  EP2_IN_Callback   NOP_Process
#define  EP3_IN_Callback   NOP_Process
#define  EP4_IN_Callback   NOP_Process
#define  EP5_IN_Callback   NOP_Process
#define  EP6_IN_Callback   NOP_Process
#define  EP7_IN_Callback   NOP_Process

#define  EP1_OUT_Callback   NOP_Process
//#define  EP2_OUT_Callback   NOP_Process
#define  EP3_OUT_Callback   NOP_Process
#define  EP4_OUT_Callback   NOP_Process
#define  EP5_OUT_Callback   NOP_Process
#define  EP6_OUT_Callback   NOP_Process
#define  EP7_OUT_Callback   NOP_Process

#define EP_CONFIG_TX ENDP1
#define EP_CONFIG_TX_ADDR ENDP1_TXADDR
//#define EP_CONFIG_TX_Callback EP1_IN_Callback

//#
#define EP_CONFIG_RX ENDP2
#define EP_CONFIG_RX_ADDR ENDP2_RXADDR
//#define EP_CONFIG_RX_Callback EP2_OUT_Callback

#define EP_SEND_TX ENDP3
#define EP_SEND_TX_ADDR ENDP3_TXADDR
#define EP_SEND_TX_Callback EP3_IN_Callback

#define EP_SEND_RX ENDP4
#define EP_SEND_RX_ADDR ENDP4_RXADDR
#define EP_SEND_RX_Callback EP4_OUT_Callback


#endif /* __USB_CONF_H */

/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
