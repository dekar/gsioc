#include "USB.h"
#include "base/BitBanding.h"
#include "base/gpio.h"
#include <stm32f10x.h>
#include "base/ISR.h"

extern "C"
{
#include "usb_lib.h"
#include "usb_desc.h"
#include "usb_pwr.h"
#include "usb_istr.h"
extern vu32 bDeviceState;
}



volatile bool writeLock;
//#define NJTAG
namespace USB
{
    GPIO_TypeDef const * connectGPIO = GPIOC;
    uint32_t connectPort = GPIO_Pin_11;
    //GPIO_TypeDef const * connectGPIO = GPIOA;
    //uint32_t connectPort = GPIO_Pin_8;

    bool (*incommingFunc)(const uint8_t * const data, uint8_t size);
    //void (*connectCallBack)(uint8_t newStatus);

}
static uint8_t __usb_recieveSize;
static uint8_t __usb_recieveBuf[64];

bool USB::isPCConnected()
{
    if(bDeviceState == 5)
        return true;
    return false;
}

void USB::init()
{
   /* USBCLK = PLLCLK / 1.5 */
  makeBBPeriph(&RCC->CFGR,RCC_CFGR_USBPRE) = 0;
  /* Enable USB clock */
  //RCC_APB1PeriphClockCmd(RCC_APB1Periph_USB, ENABLE);
  makeBBPeriph(&RCC->APB1ENR,RCC_APB1ENR_USBEN) = 1;

  /* Configure USB pull-up pin */
  USB_Init();
  NVIC_EnableIRQ(USB_LP_CAN1_RX0_IRQn);
  NVIC_SetPriority(USB_LP_CAN1_RX0_IRQn,1);
  USB::cableConnect(false);

  GPIOB->BSRR = GPIO_BSRR_BS14;
  IOSetup<IOB,14,IO_outPP2MHz>();

    writeLock = false;

  __usb_recieveSize = 0;
  USB::incommingFunc = 0;
}
/**
Cabel connection function
**/
void USB::cableConnect(bool enable)
{

  if (enable)
  {
      GPIOB->BSRR = GPIO_BSRR_BR14;

  }
  else
  {
      GPIOB->BSRR = GPIO_BSRR_BS14;
  }

}
/**
Interrupt hendler
**/

void ISR::USB_LP_CAN1_RX0_IRQ()
{
    USB_Istr();
}
/**
Main USB loop
**/
void USB::pool()
{
    //if()

}
void USB::sendRawData(const uint8_t* data, uint16_t size)
{

    UserToPMABufferCopy(const_cast<uint8_t*>(data),EP_USART_TX_ADDR,size);
    _SetEPTxCount(EP_USART_TX, size);
    _SetEPTxValid(EP_USART_TX);
}

/**
C callbacks for USB stack
*/

extern "C"{
void EP2_IN_Callback()
{

}
void EP1_IN_Callback()
{

}
void EP3_OUT_Callback()
{
    // Резервирую место для пакета
    PMAToUserBufferCopy(__usb_recieveBuf, EP_USART_RX_ADDR, 1);

    uint8_t usart = __usb_recieveBuf[0];
    USART3->DR = usart;
    SetEPRxValid(EP_USART_RX);

}

void Bitrate_Callback(uint32_t bitrate)
{

    USART3->BRR = 18000000UL / bitrate;
    // Set clock to 16 x bitrate
    TIM1->PSC = ((36000000UL/16) / bitrate ) -1;
/*
    example:
    set 9600 bps:
    freq = 153600
*/


}

}
