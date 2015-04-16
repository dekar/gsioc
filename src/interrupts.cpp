#include "base/ISR.h"
#include <stm32f10x.h>
extern void start();
/**
    Copy .data section to system RAM
*/
extern uint32_t _sidata;
extern uint32_t _sdata;
extern uint32_t _edata;
__attribute__((naked)) static void memInit()
{

    register uint32_t srcAddr asm("r4");
    register uint32_t destAddr asm("r5");
    asm volatile("mov r4, %0" : : "r"(&_sidata));
    asm volatile("mov r5, %0" : : "r"(&_sdata));

    while(destAddr < (uint32_t)&_edata)
    {
        *((uint32_t*)destAddr) = *((uint32_t*)srcAddr);
        srcAddr+=4;
        destAddr+=4;
    }
    #ifdef USE_MEMORY_ISR
    SCB->VTOR = 0x20000000;
    #endif // USE_MEMORY_ISR
    asm volatile("bx lr"); //return
}
__attribute__((naked)) void ISR::Reset()
{
    memInit();
    asm volatile("msr msp, %0" : : "r"(&_estack));
    start();
}
__attribute__((naked)) void ISR::HardFault()
{
    while(1);
}
__attribute__((naked)) void ISR::MemManage()
{
    while(1);
}
