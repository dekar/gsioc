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

  //GPIOA->BSRR = GPIO_BSRR_BS8;
  //GPIOC->BSRR = GPIO_BSRR_BS11;
  IOSetup<IOA,8,IO_outPP2MHz>();

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
      GPIOA->BSRR = GPIO_BSRR_BR8;

  }
  else
  {
      GPIOA->BSRR = GPIO_BSRR_BS8;
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
    if(__usb_recieveSize)
    {
        if(USB::incommingFunc == 0)
        {
            __usb_recieveSize = 0;
            return;
        }
        if(USB::incommingFunc(__usb_recieveBuf,__usb_recieveSize))
            __usb_recieveSize = 0;
            return;
    }
}
void USB::sendRawData(const uint8_t* data, uint16_t size)
{
    /*while(writeLock);
    writeLock = true;*/
    UserToPMABufferCopy(const_cast<uint8_t*>(data),EP_CONFIG_TX_ADDR,size);
    _SetEPTxCount(EP_CONFIG_TX, size);
    _SetEPTxValid(EP_CONFIG_TX);
}

/**
C callbacks for USB stack
*/

extern "C"{
void EP2_OUT_Callback()
{
    if(GetEPRxCount(EP_CONFIG_RX) == 64)
    {
        SetEPRxValid(EP_CONFIG_RX);
        return;
    }

    if(__usb_recieveSize)
    {
        _SetEPRxStatus(EP_CONFIG_RX,EP_RX_NAK);
        return;
    }
    __usb_recieveSize = GetEPRxCount(EP_CONFIG_RX);
    // Резервирую место для пакета
    PMAToUserBufferCopy(__usb_recieveBuf, EP_CONFIG_RX_ADDR, __usb_recieveSize);
    SetEPRxValid(EP_CONFIG_RX);
}
void EP1_IN_Callback()
{
// send OK
    //writeLock = false;

}

}
