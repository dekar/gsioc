#ifndef IRLOGIC_H
#define IRLOGIC_H
#include <stdint.h>

namespace IRlogic
{
    void init();
    void checkBattery(void (*callback)(bool) = 0);
    void sendToBattery(uint8_t bright, uint8_t num,void (*callback)(bool) = 0);
    void rawSend(const uint8_t data[3]);
    void resetMachine();
    uint16_t batStatus();
    uint8_t getNum();
    uint8_t getBright();
};

#endif // IRLOGIC_H
