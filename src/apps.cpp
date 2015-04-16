#include "apps.h"
//#include <string.h>
#include "base/ISR.h"
#include "timerService.h"
#include "buzzer.h"
#include "clocker.h"
#include "USB.h"
/*
extern definitions
*/

/*
internal defenitions
*/

namespace APPS
{
/*    void init (void);
    void pool (void);
    void regFunc(bool (*execute)(int, const char* const*), const char* funcName);
    void readSym(uint8_t c);*/
    struct t_FunctionNotes
    {
        char c;
        bool (*function)(uint8_t, uint8_t const *);
    } functions[MAX_NUM_OF_FUNC];
    uint8_t functionCount;

}

//static void rl_run(int argc, const char * const * argv);


/*
internal data
*/

/**
    Register new function in readline
*/


void APPS::regFunc(bool (*function)(uint8_t, const uint8_t  * const), const char c)
{
    if(APPS::functionCount < MAX_NUM_OF_FUNC)
    {

        APPS::functions[APPS::functionCount].function = function;
        APPS::functions[APPS::functionCount].c = c;
        APPS::functionCount++;
    }
}



/**
    Do application Input/Output jobs and call applications, if needed.
*/
/*void appsPool (void)
{
    if(UsbUsart.count_out>0)
    {
        uint8_t chr = UsbUsart.buffer_out[0];
        UsbUsart.count_out --;
        for(uint8_t i=0;i < UsbUsart.count_out; i++)
        {
            UsbUsart.buffer_out[i]=UsbUsart.buffer_out[i+1];
        }
        microrl_insert_char (&rl, chr);
    }
}*/
/***********************************
 Код внутренних функций
*/

/**
-------------------------------------------------------------------------------------
*/
uint16_t atoi(const char *buf)
{
    uint8_t i=0;
    uint16_t res = 0;
    while(buf[i])
    {
        uint8_t l = buf[i]-'0';
        res *= 10;
        res += l;
        i++;
    }
    return res;
}


void itoa(uint8_t *buf, uint8_t shft, int32_t data)
{
        uint8_t sign=0;
        if (data <0)
        {
            sign =1;
            data = data * -1;
        }
        uint8_t pos =0;
        do
        {
            uint8_t tmp = data % 10;
            buf[shft - pos] = "0123456789"[tmp];
            pos++;
        } while ((data /= 10) >0);
        if (sign)
        {
            buf[shft - pos] = '-';
        }
}

/**
    Init microReadline and register all applications;
*/

void APPS::init(void)
{
  // Инициилизирую переменные
    for (uint8_t i=0;
        i <MAX_NUM_OF_FUNC;
        i++)
    {
        APPS::functions[i].function = 0;
        APPS::functions[i].c = 0;
    }
    APPS::functionCount = 0;

}



bool APPS::pushPkg(const uint8_t * pkg, uint8_t size)
{
    for(uint8_t i = 0; i<APPS::functionCount; i++)
    {
        if (APPS::functions[i].c == pkg[0])
        {
            return APPS::functions[i].function(size - 1, pkg + 1);
        }
    }
    return true;

}
