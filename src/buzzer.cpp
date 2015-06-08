#include "buzzer.h"
#include "base/gpio.h"
#include "base/clocker.h"

//PB15 - TIM1CH3N

void Buzzer::init()
{
    RCCEnable(RCC->APB2ENR,RCC_APB2ENR_TIM1EN);
    //PB9
    IOSetup<IOB,15,IO_outAFPP2MHz>();
    IOSetup<IOA,8,IO_inFloat>();



    TIM1->BDTR      = TIM_BDTR_MOE | TIM_BDTR_OSSR;
    TIM1->PSC       = 100;
    TIM1->ARR       = 1;
    TIM1->CCR3      = 1;
    TIM1->CCMR2     = TIM_CCMR2_OC3M_1 | TIM_CCMR2_OC3M_2  | TIM_CCMR2_OC3FE | TIM_CCMR2_OC3PE;
    TIM1->CCER      = TIM_CCER_CC3NE |TIM_CCER_CC3NP;

/*    TIM1->CCR1      = 1;
    TIM1->CCMR1     = TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2  | TIM_CCMR1_OC1FE | TIM_CCMR1_OC1PE;
    TIM1->CCER      |= TIM_CCER_CC1E | TIM_CCER_CC1P;*/

    TIM1->CR1       = TIM_CR1_CEN | TIM_CR1_CKD_1;
    //Buzzer::powerOff();
}

void Buzzer::setFreq(uint16_t freq)
{
    TIM1->PSC = freq;
}




