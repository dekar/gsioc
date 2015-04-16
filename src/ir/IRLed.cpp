#include "IRLed.h"
#include "base/gpio.h"
#include "base/clocker.h"


namespace IRLed
{
        const uint16_t TimerPrescaler = 2;
        const uint16_t TimerReload = 0xD6;

}

void IRLed::init()
{
    RCCEnable(RCC->APB1ENR,RCC_APB1ENR_TIM3EN);
    //PB9
    //Remap pin
    //AFIO->MAPR = (AFIO->MAPR & (~ AFIO_MAPR_TIM3_REMAP))| AFIO_MAPR_TIM3_REMAP_1;
    IRLed::timer->CR1       = TIM_CR1_CEN | TIM_CR1_CKD_1;
    IRLed::timer->CCMR1     = TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_0 ;
    IRLed::timer->CCER      = TIM_CCER_CC2E ;
    IRLed::timer->PSC       = IRLed::TimerPrescaler;
    IRLed::timer->ARR       = IRLed::TimerReload;
    IRLed::timer->CCR2      = IRLed::TimerReload >> 1;
    IRLed::powerOff();
    //GPIOB->BRR = 1 << 5;;
    GPIOA->BRR = 1 << 7;
}

/*void IRLed::powerOff()
{
    IOSetup<IOB,9,IO_outOD2MHz>();
    GPIOB->BSRR=GPIO_BSRR_BS9;
}

void IRLed::powerOn()
{
    IOSetup<IOB,9,IO_outAFPP2MHz>();
}*/
