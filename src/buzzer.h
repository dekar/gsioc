#ifndef BUZZER_H
#define BUZZER_H
#include <stm32f10x.h>
struct tone
{
    uint16_t duraton;
    uint16_t tone;
};



namespace Buzzer
{
    void init();
    void powerOff() ;
    void powerOn() ;
    void setFreq(uint16_t freq);
    void musicTick(uint32_t toneNum);
    extern tone music[24];
    //const inline uint16_t getFreq(){};

}
#endif // BUZZER_H
