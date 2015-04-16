#include "UsartRFID.h"
#include "../base/clocker.h"
#include "../base/gpio.h"
#include "../base/ISR.h"

namespace UsartRFID
{
    bool (*callback)(uint8_t *data, uint8_t size);
    void setup();
    uint8_t buf[40];
};


void  UsartRFID::init()
{
    UsartRFID::callback = 0;
    UsartRFID::setup();
    //ctor
}

void UsartRFID::regCB(bool (*callback)(uint8_t *data, uint8_t size))
{
    UsartRFID::callback = callback;
}

void UsartRFID::setup()
{
  //RCC
    RCCEnable(RCC->APB1ENR,RCC_APB1ENR_USART2EN);
    RCCEnable(RCC->AHBENR, RCC_AHBENR_DMA1EN);


  //GPIO
    IOSetup<IOA,3,IO_inFloat>();
/*    IOSetup<IOA,9,IO_outAFPP2MHz>();
    IOSetup<IOC,13,IO_outPP2MHz>();
    SEND_OFF;*/
  //USART
    //USART2->BRR = (78 << 4) + 2; // (78.(2/16)) - 57600 BAUD Rate

    USART2->BRR = (468 << 4) + 12; // 468.75(468.(12/16)) - 9600 BAUD Rate


/*    USART2->CR1 = USART_CR1_UE  //usart enable
        | USART_CR1_IDLEIE //Idle detector
        | USART_CR1_RE;         // Receiver enable*/
    USART2->CR1 = 0;

    USART2->CR3 =  USART_CR3_DMAR;
    USART2->SR = 0;

  // DMA (TX - DMA1CH4, RX-DMA1CH5)
    //DMA_STOP();
    //DMA1->CCR5

    DMA1_Channel6->CPAR = (uint32_t)&USART2->DR;
    DMA1_Channel6->CMAR = (uint32_t)UsartRFID::buf;
    DMA1_Channel6->CNDTR = 40;
    DMA1_Channel6->CCR  = DMA_CCR1_MINC | DMA_CCR1_EN;


    NVIC_EnableIRQ(IRQn::USART2_IRQn);
    NVIC_SetPriority(IRQn::USART2_IRQn,8);
    //NVIC_EnableIRQ(IRQn::DMA1_Channel6_IRQn);
    //NVIC_EnableIRQ(IRQn::DMA1_Channel5_IRQn);

}

void UsartRFID::start()
{
    DMA1_Channel6->CCR  = DMA_CCR1_MINC | DMA_CCR1_EN;
    DMA1_Channel6->CNDTR = 40;

    USART2->CR1 = USART_CR1_UE  //usart enable
        | USART_CR1_IDLEIE //Idle detector
        | USART_CR1_RE;         // Receiver enable

}
void UsartRFID::stop()
{
    USART2->CR1 = 0;

}

void ISR::USART2_IRQ()
{
    if(USART2->SR & USART_SR_IDLE)
    {
        //USART1->SR &= ~USART_CR1_IDLEIE; // Transmission complete interrupt disable
        USART2->DR;

        DMA1_Channel6->CCR = 0;
        if(UsartRFID::callback)
        {
            if(UsartRFID::callback(UsartRFID::buf, 40 - DMA1_Channel6->CNDTR))
            {
                UsartRFID::stop();
                return;
            }
        }
        DMA1_Channel6->CNDTR = 40;
        DMA1_Channel6->CCR  = DMA_CCR1_MINC | DMA_CCR1_EN;
        //USART->CR1 = 0;


        return;
    }
}
