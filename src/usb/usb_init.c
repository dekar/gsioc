#include "usb_init.h"
#define BITBAND_PERI_REF   0x40000000
#define BITBAND_PERI_BASE  0x42000000
#define BITBAND_PERI(a,b) *(uint32_t*)((BITBAND_PERI_BASE + (((int)a)-BITBAND_PERI_REF)*32 + (b*4)))  // Convert PERI address


/*******************************************************************************
* Function Name  : USB_Init
* Description    : main init function for USB stack
* Input          : None.
* Return         : None.
*******************************************************************************/
void myUSB_Init (void)
{

}

/*void ISR::USB_LP_CAN1_RX0_IRQ()
{

}*/

/*******************************************************************************
* Function Name  : USB_Interrupts_Config
* Description    : Configures the USB interrupts
* Input          : None.
* Return         : None.
*******************************************************************************/
/*void USB_Interrupts_Config(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

 }*/

/*******************************************************************************
* Function Name  : USB_Cable_Config
* Description    : Software Connection/Disconnection of USB Cable
* Input          : None.
* Return         : Status
*******************************************************************************/
void USB_Cable_Config (FunctionalState NewState)
{

}

