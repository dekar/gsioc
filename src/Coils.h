#ifndef COILS_H
#define COILS_H
#include <stdint.h>

struct tCoilsInternal
{
    //volatile uint32_t &realCoils = GPIOF->ODR;

    uint16_t statC;
    uint16_t blinkC;
    uint16_t period[16];
    uint16_t periodC[16];
};


namespace Coils
{
    void init();
    void setCoil(uint8_t num, bool state);
    void setBlink(uint8_t num, bool state);
    void setCoils(uint16_t statC, uint16_t blinkC);
    void setFreq(uint8_t coilNum, uint16_t decesecPeriod);
    void syncBlink();
    extern tCoilsInternal m_c;
};

#endif // COILS_H
