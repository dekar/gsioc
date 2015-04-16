#include "KsotarIr.h"
#include "IRLed.h"
#include <stm32f10x.h>
#include "base/clocker.h"
#include "base/ISR.h"
#include "base/gpio.h"
/**
**/
namespace KsotarIr
{
        //const uint16_t TimerPrescaler = (21704*2) ; // For 1 per 600us
        const uint16_t TimerPrescaler = 1356; //32 per 600us
        volatile uint8_t buf[16];
        volatile uint8_t bitNum;
        volatile uint8_t byteNum;
        void (*readyCallBack)(uint8_t b1, uint8_t b2);

}

namespace Detector
{
    void (*risingCallBack)();
    void (*fallingCallBack)();
}
volatile uint8_t buf[16];
volatile uint8_t bitNum;
void detectorStateReset();
void KsotarIr::init()
{
    //IR led ON
    IRLed::init();

    RCCEnable(RCC->APB2ENR,RCC_APB2ENR_TIM1EN);
    RCCEnable(RCC->APB2ENR,RCC_APB2ENR_IOPCEN);
    //IOSetup<IOC,7,IO_outPP2MHz>();
    //PB9

    TIM1->CR1       = 0;
    TIM1->PSC       = KsotarIr::TimerPrescaler;
    TIM1->ARR       = 192;
    TIM1->CCR1      = 32;
    TIM1->CCR2      = 64;
    TIM1->CCR3      = 32;
    TIM1->CCR4      = 128;
    DBGMCU->CR |= DBGMCU_CR_DBG_TIM1_STOP;
    //TIM1->DIER = TIM_DIER_CC1IE | TIM_DIER_CC2IE |TIM_DIER_UIE;
    NVIC_EnableIRQ(IRQn::TIM1_CC_IRQn);


    KsotarIr::bitNum = 255;

///////////////////////////////////////////////////
//    RCCEnable(RCC->APB1ENR,RCC_APB1);
    //PB9

    KsotarIr::readyCallBack = 0;

    IOSetup<IOA,6,IO_inPUPD>();
    GPIOA->BSRR = GPIO_BSRR_BS6;

//EXTI configurator
    //AFIO->EXTICR[1] = AFIO->EXTICR[1] | 1;// select gpio
    EXTI->IMR |= EXTI_IMR_MR6; //mask line
    EXTI->FTSR |= (1 << 6);//select edge
    EXTI->RTSR |= (1 << 6);//select edge


    detectorStateReset();

    NVIC_EnableIRQ(IRQn::EXTI9_5_IRQn);

}


inline void timerStart()
{
    TIM1->SR = 0;
    TIM1->CNT = 0;
    TIM1->CR1 = TIM_CR1_CEN ;

}
inline void timerStop()
{
    TIM1->CR1 =0;
    TIM1->DIER = 0;
}
inline void transmitOn()
{
    GPIOC->BSRR = (1 << 7);
    IRLed::powerOn();
}
inline void transmitOff()
{
    GPIOC->BRR = (1 << 7);
    IRLed::powerOff();
}
inline void sendPreambula()
{
    TIM1->SR = 0;
    TIM1->DIER = TIM_DIER_CC4IE;
    transmitOn();

}
inline void send1()
{
    TIM1->DIER = TIM_DIER_CC2IE;
    transmitOn();
}
inline void send0()
{
    TIM1->DIER = TIM_DIER_CC1IE;
    transmitOn();
}


/**
**/
void ISR::TIM1_CC_IRQ()
{
    TIM1->CNT = 0;
    if(TIM1->DIER & TIM_SR_CC3IF) // Break end
    {
        TIM1->SR = 0;
        //!!
        uint8_t byte = KsotarIr::bitNum >> 3;// byteInBuf
        if(byte == KsotarIr::byteNum)
        {
            //End!
            KsotarIr::bitNum = 255;
            timerStop();
            NVIC_EnableIRQ(IRQn::EXTI9_5_IRQn);
            return;
        }
        uint8_t bitMask = 1 << (KsotarIr::bitNum &7);
        if(KsotarIr::buf[byte] & bitMask)
            send1();
        else
            send0();
        KsotarIr::bitNum ++ ;
        return;
    }
    transmitOff();
    TIM1->SR = 0;
    TIM1->DIER = TIM_DIER_CC3IE;
}

bool KsotarIr::rawSend(const uint8_t *data, uint8_t size)
{
    TIM1->CNT = 0;
    if(KsotarIr::bitNum != 255)
        return false;
    NVIC_DisableIRQ(IRQn::EXTI9_5_IRQn);
    TIM1->CCR1      = 32;
    TIM1->CCR2      = 64;
    TIM1->CCR3      = 32;
    TIM1->CCR4      = 128;
    KsotarIr::bitNum = 0;
    if(size > 16)
        size = 16;

    for(KsotarIr::byteNum = 0; KsotarIr::byteNum < size; KsotarIr::byteNum ++)
    {
        KsotarIr::buf[KsotarIr::byteNum] = data[KsotarIr::byteNum];
    }
    KsotarIr::byteNum = size;
    timerStart();
    sendPreambula();
    return true;
}
/**********************************************************************************/



void CBstartDetector();

static const uint8_t messageLenght = 24;
void fullMessageRecieve()
{
    TIM1->DIER = 0;
    Detector::risingCallBack = 0;
    Detector::fallingCallBack = CBstartDetector;
    TIM1->CR1 = 0;
    bitNum = 0;
    if(buf[0] == 'M')
    {
        if(KsotarIr::readyCallBack)
            KsotarIr::readyCallBack(buf[1],buf[2]);
    }
}

void detectorStateReset()
{
    TIM1->DIER = 0;
    Detector::risingCallBack = 0;
    Detector::fallingCallBack = CBstartDetector;
    TIM1->CR1 = 0;
    if(bitNum == 24)
    {
        fullMessageRecieve();
    }
    bitNum = 0;
}

void timerReStart()
{
    TIM1->CR1 = 0;
    TIM1->DIER = 0;
    TIM1->CNT = 0;
    TIM1->CR1 = TIM_CR1_CEN;
    TIM1->SR = 0;
    TIM1->DIER  = TIM_DIER_UIE;
}
void CBwaitBit()
{
    uint16_t c = TIM1->CNT;
    timerReStart();
    if(c < 26)
    {
        detectorStateReset();
        return;
    }
    if(c < 36)
    {
        uint8_t byte = bitNum >> 3;// byteInBuf
        uint8_t bitMask = ~(1 << (bitNum &7));
        buf[byte] &= bitMask;
        bitNum ++;
        if(bitNum == messageLenght)
            fullMessageRecieve();
        //oneBit
        return;
    }
    if( c < 58)
    {
        detectorStateReset();
        return;
    }
    if(c < 70)
    {
        uint8_t byte = bitNum >> 3;// byteInBuf
        uint8_t bitMask = (1 << (bitNum &7));
        buf[byte] |= bitMask;
        bitNum ++;
        if(bitNum == messageLenght)
            fullMessageRecieve();
        //twoBit
        return;
    }
    detectorStateReset(); // WRONG!
}
void CBwaitSpace()
{
    uint16_t c = TIM1->CNT;
    timerReStart();
    if(c < 29)
    {
        detectorStateReset(); // WRONG!
        return;
    }
    if(c > 40)
    {
        detectorStateReset(); // WRONG!
        return;
    }
}

void CBstartCalculate()
{
    uint16_t c = TIM1->CNT;
    timerReStart();

    if(c < 58)
    {
        detectorStateReset(); // WRONG!
        return;
    }

    if(c > 70)
    {
        //FoundStartCondition!
        Detector::fallingCallBack = CBwaitSpace;
        Detector::risingCallBack = CBwaitBit;
    }
    else
        Detector::risingCallBack = 0;
}

void CBstartDetector ()
{
    timerReStart();
    Detector::risingCallBack = CBstartCalculate;
}

void ISR::EXTI9_5_IRQ()
{
    if(GPIOA->IDR & (1 << 6))
    {
        if(Detector::risingCallBack)
            Detector::risingCallBack();
    }
    else
    {
        if(Detector::fallingCallBack)
            Detector::fallingCallBack();
    }
    EXTI->PR = (1 << 6); //clear Pending Bit
}

void ISR::TIM1_UP_TIM10_IRQ()
{
    TIM1->SR = ~(TIM_SR_UIF);
    TIM1->CR1 = 0;
    detectorStateReset();
}




