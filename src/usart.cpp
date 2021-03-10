#include "usart.h"
#include "../base/clocker.h"
#include "../base/gpio.h"
#include "../base/ISR.h"
#include "usb/USB.h"



void  USART::init()
{
  //RCC
    RCCEnable(RCC->APB1ENR,RCC_APB1ENR_USART3EN);


  //GPIO
    //AFIO->MAPR |= AFIO_MAPR_USART1_REMAP;
    IOSetup<IOB,11,IO_inFloat>();
    IOSetup<IOB,10,IO_outAFPP2MHz>();
    /*IOSetup<IOC,13,IO_outPP2MHz>();
    SEND_OFF;*/
  //USART
    //USART1->BRR = (78 << 4) + 2; // (78.(2/16)) - 57600 BAUD Rate

    USART3->BRR = //(468 << 4) + 12; // 468.75(468.(12/16)) - 9600 BAUD Rate
            18000000 / 57600;


    USART3->CR1 = USART_CR1_UE  //usart enable
        | USART_CR1_M
        | USART_CR1_PCE
        | USART_CR1_TE
        | USART_CR1_RXNEIE //RX interrupt
        | USART_CR1_RE;         // Receiver enable*/

    USART3->SR = 0;


    NVIC_EnableIRQ(IRQn::USART3_IRQn);
    NVIC_SetPriority(IRQn::USART3_IRQn,8);

}

void ISR::USART3_IRQ()
{
    if(USART3->SR & USART_SR_RXNE)
    {
        uint8_t r = USART3->DR;
        USB::addByte(r);
    }
}
