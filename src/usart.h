#ifndef USART_H
#define USART_H
#include <stdint.h>
#include <stm32f10x.h>

namespace USART
{
    void setup();
    bool send(const uint8_t *buf, uint8_t size, uint8_t address = 0,uint16_t crc = 0);
    bool sendRaw(const uint8_t *buf, uint8_t size);
    void pool();
    void setAddress(uint8_t address);
    static TIM_TypeDef * const timer = TIM1;
    static const IRQn timIRQn = IRQn::TIM1_CC_IRQn;
}

#endif // USART_H
