#include "base/ISR.h"

#include <stm32f10x_gpio.h>
#include <stm32f10x.h>
#include <core_cm3.h>
#include "base/BitBanding.h"
#include "base/gpio.h"
#include "base/clocker.h"

#include "usart.h"
#include "timerService.h"
#include "apps.h"
#include "buzzer.h"
#include "usb/USB.h"
#include "UserLogic.h"

#include "ir/IRlogic.h"

#include "UsartRFID.h"
#include "Coils.h"



void start()
{

    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPBEN |RCC_APB2ENR_IOPCEN |RCC_APB2ENR_AFIOEN;
    IOSetup<IOC,13,IO_outPP50MHz>();
    IOSetup<IOC,14,IO_outPP50MHz>();
    IOSetup<IOC,15,IO_outPP50MHz>();
    GPIOC->BRR = GPIO_Pin_13 |GPIO_Pin_14 | GPIO_Pin_15;




    Clocker::setHightClock();



  // MCO enable
//    IOSetup<IOA,8,IO_outAFPP50MHz>();
//    RCC->CFGR |= RCC_CFGR_MCO_2;
    //GPIOA->BSRR = GPIO_BSRR_BS8;

    //IOSetup<IOB,9,IO_outPP2MHz>();
    //IOSetup<IOA,10,IO_outPP50MHz>();

    Coils::init();

    //Buzzer::init();


    USART::setup();
    //UsartRFID::init();
    __enable_irq ();

    //TS::init(0,0);//Seg7::sendTimeDotTG,Clock::minuteTask);
    //Clock::forceRenew();
    //IRlogic::init();
    APPS::init();
    USB::init();
    USB::incommingFunc = APPS::pushPkg;
    UserLogic::init();

    //USART::send((uint8_t*)"Go",2);
    //Clocker::setLowClock();
    USB::cableConnect(true);



    while(1)
    {
        USB::pool();
        USART::pool();
        UserLogic::pool();
        /*uint16_t l = TIM3->CNT;
        uint32_t c = 0xF0000;
        while(c) c--;
        Seg7::sendTimeDotTG();*/
    }
}

