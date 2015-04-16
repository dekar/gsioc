#ifndef CLOCKER_H
#define CLOCKER_H
#include <stm32f10x.h>
#include "BitBanding.h"
namespace Clocker
{
    RCC_TypeDef * const rcc = ((RCC_TypeDef *) RCC_BASE);
    void setHightClock();
    void setLowClock();
    #define RCCEnable(Bus,Periph) BB<(uint32_t)&Bus, Periph>::r = 1
    #define RCCDisable(Bus,Periph) BB<(uint32_t)&Bus, Periph>::r = 0
};



#endif // CLOCKER_H
