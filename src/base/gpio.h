#ifndef DEK_GPIO_H
#define DEK_GPIO_H
#include <stm32f10x.h>
#include <stm32f10x_gpio.h>
#include "BitBanding.h"

enum gpioState
{                   //CFMD
    IO_inAnalog      = 0b0000,

    IO_outPP10MHz    = 0b0001,
    IO_outPP2MHz     = 0b0010,
    IO_outPP50MHz    = 0b0011,

    IO_inFloat       = 0b0100,

    IO_outOD10MHz    = 0b0101,
    IO_outOD2MHz     = 0b0110,
    IO_outOD50MHz    = 0b0111,

    IO_inPUPD        = 0b1000,

    IO_outAFPP10MHz  = 0b1001,
    IO_outAFPP2MHz   = 0b1010,
    IO_outAFPP50MHz  = 0b1011,

    z__reserved   = 0b1100,

    IO_outAFOD10MHz  = 0b1101,
    IO_outAFOD2MHz   = 0b1110,
    IO_outAFOD50MHz  = 0b1111
};
enum gpioBase //GPIO_TypeDef &
{                   //CFMD
    IOA = GPIOA_BASE,
    IOB = GPIOB_BASE,
    IOC = GPIOC_BASE,
    IOD = GPIOD_BASE,
    IOE = GPIOE_BASE,
    IOF = GPIOF_BASE,
    IOG = GPIOG_BASE,
};

__attribute__((always_inline)) static inline constexpr GPIO_TypeDef *GP(gpioBase port){return (GPIO_TypeDef *)port;};
static constexpr uint32_t GP_ODR(gpioBase port)
{
    return ((uint32_t)((uint8_t*)(GP(IOA))) + (uint32_t)(&((GPIO_TypeDef*)0)->ODR));
}

static constexpr uint8_t __getSubBit(const uint32_t word, const uint32_t bitNum)
{
    return ((uint8_t)((word >> bitNum) & 1));
}

//#define gpioBase GPIO_Typedef &
static constexpr uint32_t __getGPIOAddr(const gpioBase addr,const uint8_t portNum)
{
    return (portNum > 15)?
    0:
        (
         (portNum > 7)?
            ((uint32_t)&(((GPIO_TypeDef*)addr)->CRH)):
            ((uint32_t)&(((GPIO_TypeDef*)addr)->CRL))
         );

}
template <gpioState state, gpioBase addr, uint8_t portNum> struct __GGPP
{
    //static_assert(__getGPIOAddr(addr, portNum) , "Wrong portNum");
    static uint32_t l;
    static uint32_t cleanMask;
    static uint32_t addMask;
    static uint8_t firstBit;
    static uint8_t stateBits0;
    static uint8_t stateBits1;
    static uint8_t stateBits2;
    static uint8_t stateBits3;
};
template <const gpioState state, const gpioBase addr, const uint8_t portNum> uint32_t __GGPP<state,addr,portNum>::l = __getGPIOAddr(addr, portNum);
template <const gpioState state, const gpioBase addr, const uint8_t portNum> uint32_t __GGPP<state,addr,portNum>::cleanMask = ~((0b1111) << ((portNum & 0x7) * 4));
template <const gpioState state, const gpioBase addr, const uint8_t portNum> uint8_t __GGPP<state,addr,portNum>::firstBit = ((portNum & 0x7) * 4);
template <const gpioState state, const gpioBase addr, const uint8_t portNum> uint32_t __GGPP<state,addr,portNum>::addMask = ((uint32_t)state) << ((portNum & 0x7) * 4);

template <const gpioState state, const gpioBase addr, const uint8_t portNum> uint8_t __GGPP<state,addr,portNum>::stateBits0 = __getSubBit((uint32_t)state,0);
template <const gpioState state, const gpioBase addr, const uint8_t portNum> uint8_t __GGPP<state,addr,portNum>::stateBits1 = __getSubBit((uint32_t)state,1);
template <const gpioState state, const gpioBase addr, const uint8_t portNum> uint8_t __GGPP<state,addr,portNum>::stateBits2 = __getSubBit((uint32_t)state,2);
template <const gpioState state, const gpioBase addr, const uint8_t portNum> uint8_t __GGPP<state,addr,portNum>::stateBits3 = __getSubBit((uint32_t)state,3);




template <const gpioBase addr, const uint8_t portNum, const gpioState state>
__attribute__((always_inline)) inline void IOSetup()
    {
        *((uint32_t*)(__GGPP<state,addr,portNum>::l)) =
        (*((uint32_t*)(__GGPP<state,addr,portNum>::l)) & __GGPP<state,addr,portNum>::cleanMask) | __GGPP<state,addr,portNum>::addMask;

    };
template <const gpioBase addr, const uint8_t portNum, const gpioState state>
__attribute__((always_inline)) inline void SafeIOSetup()
    {
        *(uint32_t *)(PERIPH_BB_BASE + ((__getGPIOAddr(addr,portNum) - PERIPH_BASE) * 32) + ((portNum & 0x7)* 4 * 4)) =
            __GGPP<state,addr,portNum>::stateBits0;
        *(uint32_t *)(PERIPH_BB_BASE + ((__getGPIOAddr(addr,portNum) - PERIPH_BASE) * 32) + ((((portNum & 0x7)* 4 ) + 1 ) * 4)) =
            __GGPP<state,addr,portNum>::stateBits1;
        *(uint32_t *)(PERIPH_BB_BASE + ((__getGPIOAddr(addr,portNum) - PERIPH_BASE) * 32) + ((((portNum & 0x7)* 4 ) + 2) * 4)) =
            __GGPP<state,addr,portNum>::stateBits2;
        *(uint32_t *)(PERIPH_BB_BASE + ((__getGPIOAddr(addr,portNum) - PERIPH_BASE) * 32) + ((((portNum & 0x7)* 4 ) + 3) * 4)) =
            __GGPP<state,addr,portNum>::stateBits3;

    };


#endif // DEK_GPIO_H
