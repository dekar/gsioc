#include "TunerLogic.h"
#include <stm32f10x.h>
//#include "AdcDma.h"
#include "buzzer.h"
#define BASE_TONE 0x1f0
namespace TunerLogic
{
    uint8_t currentTone[4];
    const uint8_t tonesNum[8] = {0,2,1,3,1,2,3,0};
    const uint16_t tonesFreq[4] = {BASE_TONE, BASE_TONE>> 1, BASE_TONE>> 2, BASE_TONE>> 3};
    const uint8_t etalonDurations[4] = {1,3,5,2};
}
void recompileMusic (void)
{
    for(uint8_t i = 0; i<8; i++)
    {
        //uint8_t musicNum = (i << 1) + 1;
        uint8_t musicNum = i;
        uint8_t t = TunerLogic::tonesNum[i];
        Buzzer::music[musicNum].duraton = ((TunerLogic::etalonDurations[t])+1)*100;
        Buzzer::music[musicNum].tone = TunerLogic::tonesFreq[t];
    }
}

void TunerLogic::play()
{
//    Buzzer::music
   //Play
    Buzzer::powerOn();
    Buzzer::musicTick(8);
}
void TunerLogic::init()
{
    Buzzer::init();
    Buzzer::powerOff();


    //insert pauses;
    for(uint8_t i = 0; i<18; i+= 2)
        Buzzer::music[i] = {50,0xffff};
    recompileMusic ();
//    Buzzer::music[15] = {100,0xffff};

}
/*void TunerLogic::setNewTone(uint8_t tone, uint8_t duration)
{

}*/
uint16_t TunerLogic::getCurrentTones()
{
    return TunerLogic::compilledCurrentTones;
}
