#include "base/ISR.h"

#include <stm32f10x_gpio.h>
#include <stm32f10x.h>
#include <core_cm3.h>
#include "base/BitBanding.h"
#include "base/gpio.h"
#include "base/clocker.h"

#include "usart.h"
#include "usb/USB.h"

#include "Coils.h"
#include "buzzer.h"



void start()
{

    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPBEN |RCC_APB2ENR_IOPCEN |RCC_APB2ENR_AFIOEN;
    IOSetup<IOC,13,IO_outPP50MHz>();
    IOSetup<IOC,14,IO_outPP50MHz>();
    IOSetup<IOC,15,IO_outPP50MHz>();
    GPIOC->BSRR = GPIO_Pin_14 ;
    GPIOC->BSRR = GPIO_Pin_13  | GPIO_Pin_15;




    Clocker::setHightClock();



  // MCO enable
//    IOSetup<IOA,8,IO_outAFPP50MHz>();
//    RCC->CFGR |= RCC_CFGR_MCO_2;
    //GPIOA->BSRR = GPIO_BSRR_BS8;

    //IOSetup<IOB,9,IO_outPP2MHz>();
    //IOSetup<IOA,10,IO_outPP50MHz>();

    //Coils::init();



    USART::init();
    Buzzer::init();
    __enable_irq ();

    USB::init();
    //USB::incommingFunc = APPS::pushPkg;

    USB::cableConnect(true);



    while(1)
    {
        //USB::pool();
        //USART::pool();
    }
}

