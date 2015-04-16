#ifndef TUNERLOGIC_H
#define TUNERLOGIC_H
#include <stdint.h>

namespace TunerLogic
{
    void init();
    void play();
//    void setNewTone(uint8_t tone, uint8_t duration);
    uint16_t getCurrentTones();
    extern uint16_t compilledCurrentTones;
};

#endif // TUNERLOGIC_H
