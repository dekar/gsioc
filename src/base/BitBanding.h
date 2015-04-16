#ifndef BITBANDING_H
#define BITBANDING_H
#include <stm32f10x.h>
#include <stdint.h>
//BB_ADDR_PER = PERIPH_BB_BASE + ((REG_ADDR - PERIPH_BASE) * 32) + (BIT * 4)

/**

Get Bit constexps

**/

const static uint32_t constexpr  __localGetBit(const uint32_t bitMask,const  uint8_t step)
{
    return (step == 0)?0:(
        (bitMask & (1 << step)) ?
            step :
            __localGetBit(bitMask, step - 1));
}

const static uint8_t constexpr getBit(const uint32_t bitmask)
{
        return __localGetBit(bitmask, 31);
}


/**
    PERIPH
**/
volatile uint32_t constexpr bitBandingPeriphBit(volatile const  void* baseAddr,const  uint8_t bit)
{
    return (uint32_t)(PERIPH_BB_BASE + (((uint32_t)baseAddr - PERIPH_BASE) * 32) + (bit * 4));

};
volatile uint32_t constexpr bitBandingPeriph(volatile const  void* baseAddr,const uint32_t bitMask)
{
    return (uint32_t)(PERIPH_BB_BASE + (((uint32_t)baseAddr - PERIPH_BASE) * 32) + (getBit(bitMask) * 4));
};



template <uint32_t addr, uint32_t bitmask> struct BB
{
    static uint32_t &r;// = (uint32_t *)(PERIPH_BB_BASE + (((uint32_t)addr - PERIPH_BASE) * 32) + (getBit(bitmask) * 4));
    static uint32_t &r_b;// = (uint32_t *)(PERIPH_BB_BASE + (((uint32_t)addr - PERIPH_BASE) * 32) + (getBit(bitmask) * 4));
};
template <uint32_t addr, uint32_t bitmask> uint32_t &BB<addr, bitmask>::r   = *(uint32_t *)(PERIPH_BB_BASE + (((uint32_t)addr - PERIPH_BASE) * 32) + (getBit(bitmask) * 4));
template <uint32_t addr, uint32_t bitmask> uint32_t &BB<addr, bitmask>::r_b = *(uint32_t *)(PERIPH_BB_BASE + (((uint32_t)addr - PERIPH_BASE) * 32) + (bitmask * 4));
#define makeBBPeriph(baseAddr,bitMap) BB<(uint32_t) baseAddr, bitMap>::r
/**
    MEM
**/
volatile uint32_t constexpr bitBandingMemBit(volatile const  void* baseAddr,const  uint8_t bit)
{
    return (uint32_t)(SRAM_BB_BASE + (((uint32_t)baseAddr - SRAM_BASE) * 32) + (bit * 4));

};
volatile uint32_t constexpr bitBandingMem(volatile const  void* baseAddr,const uint32_t bitMask)
{
    return (uint32_t)(SRAM_BB_BASE + (((uint32_t)baseAddr - SRAM_BASE) * 32) + (getBit(bitMask) * 4));
};


template <uint32_t addr, uint32_t bitmask> struct BBm
{
    static uint32_t &r;// = (uint32_t *)(SRAM_BB_BASE + (((uint32_t)addr - SRAM_BASE) * 32) + (getBit(bitmask) * 4));
    static uint32_t &r_b;// = (uint32_t *)(SRAM_BB_BASE + (((uint32_t)addr - SRAM_BASE) * 32) + (getBit(bitmask) * 4));
};
template <uint32_t addr, uint32_t bitmask> uint32_t &BBm<addr, bitmask>::r   = *(uint32_t *)(SRAM_BB_BASE + (((uint32_t)addr - SRAM_BASE) * 32) + (getBit(bitmask) * 4));
template <uint32_t addr, uint32_t bitmask> uint32_t &BBm<addr, bitmask>::r_b = *(uint32_t *)(SRAM_BB_BASE + (((uint32_t)addr - SRAM_BASE) * 32) + (bitmask * 4));
#define makeBBMem(baseAddr,bitMap) BB<(uint32_t) baseAddr, bitMap>::r
#define makeBBMemBit(baseAddr,bitMap) BB<(uint32_t) baseAddr, bitMap>::r_b


//#define BIT_BAND_SRAM(RAM,BIT) (*(uint32_t*)(SRAM_BB_BASE+32*((uint32_t)((void*)(RAM))-SRAM_BASE)+4*((uint32_t)(BIT))))


#endif // BITBANDING_H
