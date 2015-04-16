#include "Coils.h"
#include <stm32f10x.h>
#include "base/ISR.h"
#include "base/clocker.h"
/**
  Private data
**/

namespace Coils
{
    tCoilsInternal m_c;
}



/**
  Setters
**/

void Coils::syncBlink()
{
    for(uint8_t i = 0;i<16;i++)
    {
        Coils::m_c.periodC[i] = 0;
    }
}

void Coils::setCoil(uint8_t num, bool state)
{
    uint16_t m = 1 << num;
    if(state)
    {
      //clear blink
        Coils::m_c.blinkC &= ~m;
      //set coil
        Coils::m_c.statC |= m;
      //turn on
        GPIOF->BSRR = m;
    }
    else
    {
      //clear coil
        Coils::m_c.statC &= ~m;
        if((Coils::m_c.blinkC & m)==0)//if(! blink)
            GPIOF->BRR = m;//turn off

    }
}
void Coils::setBlink(uint8_t num, bool state)
{
    uint16_t m = 1 << num;
    if(state)
    {
      //clear coli
        Coils::m_c.statC &= ~m;
      //set blink
        Coils::m_c.blinkC |= m;
      //turn on
        GPIOF->BSRR = m;
    }
    else
    {
      //clear blink
        Coils::m_c.blinkC &= ~m;
        if((Coils::m_c.statC & m)==0)//if(! coil)
            GPIOF->BRR = m;//turn off

    }

}


void Coils::setCoils(uint16_t statC, uint16_t blinkC)
{
    //Remove collisions
    uint16_t wrong = statC & blinkC;
    if(wrong)
    {
        statC &= ~wrong;
    }
    //set GPIO
    GPIOF->ODR = statC | blinkC;
    Coils::m_c.statC = statC;
    Coils::m_c.blinkC = blinkC;

}

void Coils::setFreq(uint8_t coilNum, uint16_t decesecPeriod)
{
    Coils::m_c.period[coilNum] = decesecPeriod;
}

/**
  Init
**/

void Coils::init()
{
    RCCEnable(RCC->APB2ENR, RCC_APB2ENR_IOPFEN);
    RCCEnable(RCC->APB1ENR, RCC_APB1ENR_TIM7EN);
 //setup GPIO
    GPIOF->ODR = 0;
    GPIOF->CRH = 0x22222222;
    GPIOF->CRL = 0x22222222;
 //Write initial values to struct
    for(uint8_t i = 0;i<16;i++)
    {
        Coils::m_c.period[i] = 5;
    }
    Coils::m_c.statC = 0;
    Coils::m_c.blinkC = 0;
 //setup timer
    TIM7->CR1       = TIM_CR1_CEN ;
    TIM7->PSC       = 30000-1;
    TIM7->ARR       = 99;
    TIM7->DIER      = TIM_DIER_UIE;
 //setup timer IRQ
    NVIC_EnableIRQ(IRQn::TIM7_IRQn);
    NVIC_SetPriority(IRQn::TIM7_IRQn,8);
}
/**
  Irq
**/


void ISR::TIM7_IRQ()
{
    TIM7->SR = ~TIM_SR_UIF;
    for(uint8_t i = 0 ;i<16;i++)
    {
        uint16_t m = (1 << i);
        if((Coils::m_c.blinkC & m) == 0)
            continue;
        Coils::m_c.periodC[i]++;
        if(Coils::m_c.periodC[i] > Coils::m_c.period[i])
        {
            Coils::m_c.periodC[i] = 0;
            if(GPIOF->ODR & m)
                GPIOF->BRR = m;
            else
                GPIOF->BSRR = m;
        }
    }
}


