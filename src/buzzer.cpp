#include "buzzer.h"
#include "base/gpio.h"
#include "base/clocker.h"
#include "timerService.h"

void Buzzer::init()
{
    RCCEnable(RCC->APB1ENR,RCC_APB1ENR_TIM3EN);
    //PB9
    IOSetup<IOB,1,IO_outAFPP2MHz>();
    TIM3->CR1       = TIM_CR1_CEN | TIM_CR1_CKD_1;
    TIM3->CCMR2     = TIM_CCMR2_OC4M_1 | TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4M_0 ;
    TIM3->CCER      = TIM_CCER_CC4E ;
    TIM3->PSC       = 0x02;
    TIM3->ARR       = 0xD6;
    TIM3->CCR4      = TIM3->ARR / 2;
    Buzzer::powerOff();
}

void Buzzer::setFreq(uint16_t freq)
{
    TIM3->PSC = freq;
}

void Buzzer::powerOff()
{
    RCCDisable(RCC->APB1ENR,RCC_APB1ENR_TIM3EN);
    IOSetup<IOB,1,IO_outOD2MHz>();
    GPIOB->BSRR=GPIO_BSRR_BS9;
}

void Buzzer::powerOn()
{
    RCCEnable(RCC->APB1ENR,RCC_APB1ENR_TIM3EN);
    IOSetup<IOB,1,IO_outAFPP2MHz>();
    //GPIOB->BSRR=GPIO_BSRR_BS9;
}


namespace Buzzer
{
    tone music[24];
}


void Buzzer::musicTick(uint32_t toneNum)
{
    if(toneNum == 0)
    {
        Buzzer::powerOff();
        return;
    }

    toneNum--;
    Buzzer::setFreq(Buzzer::music[toneNum].tone);
    TS::addTask(Buzzer::music[toneNum].duraton,Buzzer::musicTick,toneNum);
}

