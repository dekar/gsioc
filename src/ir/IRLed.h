#ifndef IRLED_H
#define IRLED_H
#include <stm32f10x.h>
#include "base/gpio.h"


namespace IRLed
{
    //setup
    static TIM_TypeDef * const timer = TIM3;
    //prototipes
    void init();
    //inlines
    /*static inline void powerOff() {IOSetup<IOB,5,IO_outPP2MHz>();IRLed::timer->CR1 = 0;};
    static inline void powerOn() {IOSetup<IOB,5,IO_outAFPP2MHz>();IRLed::timer->CR1 = TIM_CR1_CEN | TIM_CR1_CKD_1;};*/
    static inline void powerOff() {IOSetup<IOA,7,IO_outPP2MHz>();IRLed::timer->CR1 = 0;};
    static inline void powerOn() {IOSetup<IOA,7,IO_outAFPP2MHz>();IRLed::timer->CR1 = TIM_CR1_CEN | TIM_CR1_CKD_1;};
};

#endif // IRLED_H
