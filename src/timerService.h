#ifndef TIMER_SERVICE_H
#define TIMER_SERVICE_H
#include "stm32f10x.h"

#define TS_USEC (TIM2->CNT + 1000 - TIM2->CCR1)

#define TS_MAX_COUNTER 3600000
namespace TS
{
    typedef struct
    {
        uint16_t mtime;
        void (*function)(uint32_t);
        uint32_t argument;
    }Task_t;

    static TIM_TypeDef * const timer = TIM2;
    static const IRQn timIRQn = IRQn::TIM2_IRQn;


    void init(void (*secondTick)(void)=0,void (*minuteTick)(void)=0);
    void addTask(uint16_t time, void (*function)(uint32_t), uint32_t argument=0);
    //uint32_t getTimeStamp(RTC_TimeTypeDef *currentTime);
    int32_t timeSet(uint32_t timestamp);
    struct timeT
    {
        uint32_t timestamp;
        uint8_t hr;
        uint8_t minute;
        uint8_t sec;
    };

}
extern TS::timeT TStime;

#endif
