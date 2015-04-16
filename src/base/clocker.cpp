#include "clocker.h"



void Clocker::setHightClock()
{
    FLASH->ACR |= FLASH_ACR_PRFTBE; // Enable Prefetch Buffer.
    FLASH->ACR &= ~(FLASH_ACR_LATENCY); // Предочистка.
    /*FLASH->ACR |= FLASH_ACR_LATENCY_0; // Если SystemCoreClock <= 24 МГц, без пропусков.
    FLASH->ACR |= FLASH_ACR_LATENCY_1; // Если 24< SystemCoreClock <= 48, пропускать 1 такт.*/
    FLASH->ACR |= FLASH_ACR_LATENCY_2; // Если 48< SystemCoreClock <= 72, пропускать 2 такта.

    RCC->CR|=RCC_CR_HSEON; // Включить генератор HSE.
    while (!(RCC->CR & RCC_CR_HSERDY)) {}; // Ожидание готовности HSE.
    RCC->CFGR &=~RCC_CFGR_SW; // Очистить биты SW0, SW1.
    RCC->CFGR |= RCC_CFGR_SW_HSE; // Выбрать HSE для тактирования SW0=1.

    RCC->CFGR |= RCC_CFGR_PPRE1_2 | RCC_CFGR_PPRE1_0; // Выбрать HSE для тактирования SW0=1.


    RCC->CFGR &=~((RCC_CFGR_PLLSRC|RCC_CFGR_PLLXTPRE|RCC_CFGR_PLLMULL)); // Предочистка.
    RCC->CFGR|=RCC_CFGR_PLLSRC_HSE; // Тактировать PLL от HSE (12 MHz).
    RCC->CFGR|=RCC_CFGR_PLLMULL6; // Умножать частоту на 6 (12*6=72 MHz).
    //RCC->CFGR|=RCC_CFGR_PLLMULL9; // Умножать частоту на 6 (12*6=72 MHz).
    RCC->CR |= RCC_CR_PLLON; // Запустить PLL.
        while ((RCC->CR & RCC_CR_PLLRDY)==0) {} // Ожидание готовности PLL.
    RCC->CFGR &=~RCC_CFGR_SW; // Очистить биты SW0, SW1.
    RCC->CFGR |= RCC_CFGR_SW_PLL; // Тактирование с выхода PLL.
    while ((RCC->CFGR&RCC_CFGR_SWS)!=0x08) {} // Ожидание переключения на PLL.
}
void Clocker::setLowClock()
{
    __disable_irq();
    RCC->CFGR = (RCC->CFGR & ~RCC_CFGR_SW) | RCC_CFGR_SW_HSE; // Тактирование с HSE.
    while ((RCC->CFGR&RCC_CFGR_SWS)!=RCC_CFGR_SWS_HSE) {} // Ждём HSE
    //FLASH->ACR |= FLASH_ACR_PRFTBE; // Enable Prefetch Buffer.
    FLASH->ACR |= (FLASH->ACR & ~(FLASH_ACR_LATENCY))|  FLASH_ACR_LATENCY_0; // Если SystemCoreClock <= 24 МГц, без пропусков.
    /*FLASH->ACR |= FLASH_ACR_LATENCY_1; // Если 24< SystemCoreClock <= 48, пропускать 1 такт.
    FLASH->ACR |= FLASH_ACR_LATENCY_2; // Если 48< SystemCoreClock <= 72, пропускать 2 такта.*/
    __enable_irq();
    RCC->CR &= ~RCC_CR_PLLON;

}
