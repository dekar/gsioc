#include "IRlogic.h"
#include "KsotarIr.h"
#include "timerService.h"
namespace IRlogic_private
{
    volatile uint8_t batBright;
    volatile uint8_t batNum;
    volatile uint8_t present;
    volatile uint8_t isAckRecieved;
    const uint8_t numberOfAttempts = 4;
    const uint8_t checkPkg[3]={'B',255,255};
    uint8_t sendPkg[3]={'B',255,255};
    void (*sendBatCallback)(bool);
    void (*checkCallback)(bool);
};

/// /// /// /// /// /// /// /// /// /// /// ///
void L_sendToBattery(bool isPresent);
void L_retryCheck(uint32_t arg);
void L_recieveCheck(uint8_t data1, uint8_t data2);
void L_retryBat(uint32_t arg);
void L_recieveBat(uint8_t data1, uint8_t data2);


void IRlogic::init()
{
    IRlogic_private::batBright = 255;
    IRlogic_private::batNum = 255;
    IRlogic_private::present = 0;
    IRlogic_private::sendBatCallback = 0;
    IRlogic_private::checkCallback = 0;
    KsotarIr::init();
}

void IRlogic::resetMachine()
{
    IRlogic_private::present = 0;
    IRlogic_private::sendBatCallback = 0;
    IRlogic_private::checkCallback = 0;
    KsotarIr::init();
}

void IRlogic::rawSend(const uint8_t data[3])
{
    KsotarIr::rawSend(data,3);
}
/**
**/
void IRlogic::sendToBattery(uint8_t bright, uint8_t num,void (*callback)(bool))
{
    if(IRlogic_private::sendBatCallback)
        return;
    IRlogic_private::sendPkg[1] = bright;
    IRlogic_private::sendPkg[2] = num;
    IRlogic_private::sendBatCallback = callback;
    IRlogic::checkBattery(L_sendToBattery);
}
void L_sendToBattery(bool isPresent)
{
    if(isPresent)
    {
        // Bat present!
        IRlogic_private::isAckRecieved = 0;
        KsotarIr::readyCallBack = L_recieveBat;
        KsotarIr::rawSend(IRlogic_private::sendPkg,3);
        TS::addTask(150,L_retryBat,IRlogic_private::numberOfAttempts);
    }
    else
    {
        if(IRlogic_private::sendBatCallback)
        {
            IRlogic_private::sendBatCallback(false);
            IRlogic_private::sendBatCallback = 0;
        }

    }
}
void L_retryBat(uint32_t arg)
{
    if(IRlogic_private::isAckRecieved)
        return;
    if(arg == 0)
    {
        //TIMEOUT
        if(IRlogic_private::sendBatCallback)
        {
            IRlogic_private::sendBatCallback(false);
            IRlogic_private::sendBatCallback = 0;
        }
        return;
    }
    else
    {
        KsotarIr::rawSend(IRlogic_private::sendPkg,3);
        TS::addTask(150,L_retryBat,arg - 1);
    }

}
void L_recieveBat(uint8_t data1, uint8_t data2)
{
    IRlogic_private::isAckRecieved =1;
    IRlogic_private::batBright = data1;
    IRlogic_private::batNum = data2;
    if(IRlogic_private::sendBatCallback)
    {
        IRlogic_private::sendBatCallback(true);
        IRlogic_private::sendBatCallback = 0;
    }

}
/**
**/

uint8_t IRlogic::getNum()
{
    return IRlogic_private::batNum;
}
uint8_t IRlogic::getBright()
{
    return IRlogic_private::batBright;
}

void IRlogic::checkBattery(void (*callback)(bool))
{
    if(IRlogic_private::checkCallback)
        return;
    IRlogic_private::present = 0;
    IRlogic_private::checkCallback = callback;
    KsotarIr::readyCallBack = L_recieveCheck;
    KsotarIr::rawSend(IRlogic_private::checkPkg,3);
    TS::addTask(150,L_retryCheck,IRlogic_private::numberOfAttempts);
}
void L_retryCheck(uint32_t arg)
{
    if(IRlogic_private::present)
        return;
    if(arg == 0)
    {
        //TIMEOUT
        if(IRlogic_private::checkCallback)
        {
            IRlogic_private::checkCallback(false);
            IRlogic_private::checkCallback = 0;
        }

        return;
    }
    else
    {
        KsotarIr::rawSend(IRlogic_private::checkPkg,3);
        TS::addTask(150,L_retryCheck,arg - 1);
    }

}
void L_recieveCheck(uint8_t data1, uint8_t data2)
{
    IRlogic_private::present = 1;
    IRlogic_private::batBright = data1;
    IRlogic_private::batNum = data2;
    if(IRlogic_private::checkCallback)
    {
        IRlogic_private::checkCallback(true);
        IRlogic_private::checkCallback = 0;
    }

}

/**
**/


volatile uint8_t ackRecieved;
inline void sendCharge()
{
    uint8_t batPkg[3];
    batPkg[0] = 'B';
    batPkg[1] = 30;
    batPkg[2] = 10;
    KsotarIr::rawSend(batPkg, sizeof(batPkg));
}
void ackCallBack(uint8_t b1, uint8_t b2)
{
    if((b1 == 30) && (b2 == 10))
    {
        ackRecieved = 1;
        KsotarIr::readyCallBack = 0;
        //TODO: add status change
    }
}

void resendCharge(uint32_t arg)
{
    if(ackRecieved == 1)
        return;
    sendCharge();
    if (arg)
        TS::addTask(150,resendCharge,arg - 1);
}

bool _chargeBattery()
{

    ackRecieved = 0;
    KsotarIr::readyCallBack = ackCallBack;
    TS::addTask(150,resendCharge,3);
    return true;
}

