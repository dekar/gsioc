#include "UserLogic.h"
#include "usart.h"
#include "timerService.h"
#include "apps.h"
#include "buzzer.h"
#include "usb/USB.h"
#include "packets.h"
#include "base/gpio.h"
#include "ir/IRlogic.h"
#include "UsartRFID.h"
#include "Coils.h"


#define MAGNET_ON GPIOA->BSRR = GPIO_BSRR_BR1
#define MAGNET_OFF GPIOA->BSRR = GPIO_BSRR_BS1

#define IS_BATTERY ((GPIOA->IDR & (1<<5)) == 0)
#define IS_CHARGED ((GPIOA->IDR & (1<<6)) == 0)
#define DISCAHRGE_ON GPIOA->BSRR = GPIO_BSRR_BS7
#define DISCAHRGE_OFF GPIOA->BSRR = GPIO_BSRR_BR7



void mySendPkg(const uint8_t *buf, uint8_t size)
{
    if(USB::isPCConnected())
        USB::sendRawData(buf,size);
    else
        USART::send(buf,size);
}

bool dataToRS485(uint8_t *buf, uint8_t size)
{
    while(size)
    {
        size--;
    }
    return true;
}

bool Bz(uint8_t size,const uint8_t *buf)
{
    const Packets::Buzzer * const  p = (const Packets::Buzzer *)buf;
    if(p->on)
        Buzzer::powerOn();
    else
        Buzzer::powerOff();
    Buzzer::setFreq(p->freq);
    return true;
}

bool send(uint8_t size,const uint8_t *buf)
{
    const Packets::writeRS * const  p = (const Packets::writeRS *)buf;
    //Seg7::setBr(p->bright);
/*    uint8_t *point = p->data;
    uint8_t address = *point++;
    uint8_t address = *point++;

    //USART::send(p->data, p->size, p->address);*/
    USART::sendRaw(p->data, p->size);
    return true;
}

bool Magnet(uint8_t size,const uint8_t *buf)
{
    if(buf[0])
        MAGNET_ON;
    else
        MAGNET_OFF;
    return true;

}
void batteryReset(uint32_t b)
{
    DISCAHRGE_OFF;
}

bool batteryDischarge(uint8_t size,const uint8_t *buf)
{
    DISCAHRGE_ON;
    TS::addTask(100,batteryReset);
    return true;
}

bool isBattery(uint8_t size,const uint8_t *buf)
{
    uint8_t b[3] = {'l',0,0};
    if(IS_BATTERY)
        b[1] =1;
    else
        b[1] =0;
    if(IS_CHARGED)
        b[2] =1;
    else
        b[2] =0;

    USB::sendRawData(b,3);
    return true;

}
bool rfidSend(uint8_t *data, uint8_t size)
{
    //const uint8_t b[2] = {'R',1};
    data[0] = 'r';
    USB::sendRawData(data,size);
    return true;

}
bool rfidOn(uint8_t size,const uint8_t *buf)
{
    UsartRFID::regCB(rfidSend);
    UsartRFID::start();
    return true;
}
bool light(uint8_t size,const uint8_t *buf)
{
    const uint16_t *b = (const uint16_t*)buf;
    uint16_t Coils = b[0];
    uint16_t Blink = b[1];
    Coils::setCoils(Coils, Blink);
    return true;//
}



static bool batteryPresent;

void UserLogic::init()
{
    IOSetup<IOA,5,IO_inPUPD>(); //IR_plug
    IOSetup<IOA,6,IO_inPUPD>(); //IR_plug
    GPIOA->BSRR = GPIO_BSRR_BR5|GPIO_BSRR_BR6;
    IOSetup<IOA,7,IO_outPP2MHz>(); // Magnet

    IOSetup<IOA,1,IO_outPP2MHz>(); // Magnet

    IOSetup<IOB,15,IO_outPP2MHz>(); // Magnet
    IOSetup<IOB,14,IO_outPP2MHz>(); // Magnet
    IOSetup<IOB,13,IO_outPP2MHz>(); // Magnet
    IOSetup<IOB,12,IO_outPP2MHz>(); // Magnet
    IOSetup<IOB,11,IO_outPP2MHz>(); // Magnet
    IOSetup<IOB,10,IO_outPP2MHz>(); // Magnet
    IOSetup<IOB,9,IO_outPP2MHz>(); // Magnet
    IOSetup<IOB,8,IO_outPP2MHz>(); // Magnet
    GPIOB->BSRR = 0xEF00;

    MAGNET_ON;
    APPS::regFunc(Bz,'B');
    APPS::regFunc(Magnet,'M');
    APPS::regFunc(isBattery,'l');
//    APPS::regFunc(batteryCheck,'c');
    APPS::regFunc(batteryDischarge,'D');
    APPS::regFunc(rfidOn,'r');
    APPS::regFunc(light,'L');


    //APPS::regFunc(play,'y');
    APPS::regFunc(send,'s');
    USART::setAddress(0);

    batteryPresent = false;
}
//uint8_t [[4]

void UserLogic::pool()
{
    //if(IS_BUTTON)
}
