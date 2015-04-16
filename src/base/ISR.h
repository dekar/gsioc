#ifndef INTERRUPTS_H
#define INTERRUPTS_H
#include <stdint.h>
extern uint32_t _estack;
//#define USE_MEMORY_ISR

extern "C"
{
    namespace ISR
    {
        void DefaultHandler();
        struct ShortISRVector
        {
            uint32_t estack;
            void (*Reset )(void);
        };

        struct ISRVector
        {
            uint32_t estack;
            void (*Reset )(void);
            void (*NMI )(void);
            void (*HardFault )(void);
            void (*MemManage )(void);
            void (*BusFault )(void);
            void (*UsageFault )(void);
            void (*UNUSED[4] )(void);
            void (*SVC )(void);
            void (* DebugMon)(void);
            void (*UNUSED2 )(void);
            void (*PendSV )(void);
            void (*SysTickI )(void);
            void (*WWDG_IRQ )(void);
            void (*PVD_IRQ )(void);
            void (*TAMPER_IRQ )(void);
            void (*RTC_IRQ )(void);
            void (*FLASH_IRQ )(void);
            void (*RCC_IRQ )(void);
            void (*EXTI0_IRQ )(void);
            void (*EXTI1_IRQ )(void);
            void (*EXTI2_IRQ )(void);
            void (*EXTI3_IRQ )(void);
            void (*EXTI4_IRQ )(void);
            void (*DMA1_Channel1_IRQ )(void);
            void (*DMA1_Channel2_IRQ )(void);
            void (*DMA1_Channel3_IRQ )(void);
            void (*DMA1_Channel4_IRQ )(void);
            void (*DMA1_Channel5_IRQ )(void);
            void (*DMA1_Channel6_IRQ )(void);
            void (*DMA1_Channel7_IRQ )(void);
            void (*ADC1_2_IRQ )(void);
            void (*USB_HP_CAN1_TX_IRQ )(void);
            void (*USB_LP_CAN1_RX0_IRQ )(void);
            void (*CAN1_RX1_IRQ )(void);
            void (*CAN1_SCE_IRQ )(void);
            void (*EXTI9_5_IRQ )(void);
            void (*TIM1_BRK_TIM9_IRQ )(void);
            void (*TIM1_UP_TIM10_IRQ )(void);
            void (*TIM1_TRG_COM_TIM11_IRQ )(void);
            void (*TIM1_CC_IRQ )(void);
            void (*TIM2_IRQ )(void);
            void (*TIM3_IRQ )(void);
            void (*TIM4_IRQ )(void);
            void (*I2C1_EV_IRQ )(void);
            void (*I2C1_ER_IRQ )(void);
            void (*I2C2_EV_IRQ )(void);
            void (*I2C2_ER_IRQ )(void);
            void (*SPI1_IRQ )(void);
            void (*SPI2_IRQ )(void);
            void (*USART1_IRQ )(void);
            void (*USART2_IRQ )(void);
            void (*USART3_IRQ )(void);
            void (*EXTI15_10_IRQ )(void);
            void (*RTCAlarm_IRQ )(void);
            void (*USBWakeUp_IRQ )(void);
            void (*TIM8_BRK_TIM12_IRQ )(void);
            void (*TIM8_UP_TIM13_IRQ )(void);
            void (*TIM8_TRG_COM_TIM14_IRQ )(void);
            void (*TIM8_CC_IRQ )(void);
            void (*ADC3_IRQ )(void);
            void (*FSMC_IRQ )(void);
            void (*SDIO_IRQ )(void);
            void (*TIM5_IRQ )(void);
            void (*SPI3_IRQ )(void);
            void (*UART4_IRQ )(void);
            void (*UART5_IRQ )(void);
            void (*TIM6_IRQ )(void);
            void (*TIM7_IRQ )(void);
            void (*DMA2_Channel1_IRQ )(void);
            void (*DMA2_Channel2_IRQ )(void);
            void (*DMA2_Channel3_IRQ )(void);
            void (*DMA2_Channel4_5_IRQ )(void);
        };
         void DefaultHendler (void);//
         void Reset (void);
         void NMI (void);
         void HardFault (void) ; // __attribute__((weak, alias ("_ZN6m3core14DefaultHendlerEv")));
         void MemManage (void) ; // __attribute__((weak, alias ("_ZN6m3core14DefaultHendlerEv")));
         void BusFault (void) ; // __attribute__((weak, alias ("_ZN6m3core14DefaultHendlerEv")));
         void UsageFault (void) ; // __attribute__((weak, alias ("_ZN6m3core14DefaultHendlerEv")));
         void SVC (void) ; // __attribute__((weak, alias ("_ZN6m3core14DefaultHendlerEv")));
         void DebugMon (void) ; // __attribute__((weak, alias ("_ZN6m3core14DefaultHendlerEv")));
         void PendSV (void) ; // __attribute__((weak, alias ("_ZN6m3core14DefaultHendlerEv")));
         void SysTickI (void) ; // __attribute__((weak, alias ("_ZN6m3core14DefaultHendlerEv")));
         void WWDG_IRQ (void) ; // __attribute__((weak, alias ("_ZN6m3core14DefaultHendlerEv")));
         void PVD_IRQ (void) ; // __attribute__((weak, alias ("_ZN6m3core14DefaultHendlerEv")));
         void TAMPER_IRQ (void) ; // __attribute__((weak, alias ("_ZN6m3core14DefaultHendlerEv")));
         void RTC_IRQ (void) ; // __attribute__((weak, alias ("_ZN6m3core14DefaultHendlerEv")));
         void FLASH_IRQ (void) ; // __attribute__((weak, alias ("_ZN6m3core14DefaultHendlerEv")));
         void RCC_IRQ (void) ; // __attribute__((weak, alias ("_ZN6m3core14DefaultHendlerEv")));
         void EXTI0_IRQ (void) ; // __attribute__((weak, alias ("_ZN6m3core14DefaultHendlerEv")));
         void EXTI1_IRQ (void) ; // __attribute__((weak, alias ("_ZN6m3core14DefaultHendlerEv")));
         void EXTI2_IRQ (void) ; // __attribute__((weak, alias ("_ZN6m3core14DefaultHendlerEv")));
         void EXTI3_IRQ (void) ; // __attribute__((weak, alias ("_ZN6m3core14DefaultHendlerEv")));
         void EXTI4_IRQ (void) ; // __attribute__((weak, alias ("_ZN6m3core14DefaultHendlerEv")));
         void DMA1_Channel1_IRQ (void) ; // __attribute__((weak, alias ("_ZN6m3core14DefaultHendlerEv")));
         void DMA1_Channel2_IRQ (void) ; // __attribute__((weak, alias ("_ZN6m3core14DefaultHendlerEv")));
         void DMA1_Channel3_IRQ (void) ; // __attribute__((weak, alias ("_ZN6m3core14DefaultHendlerEv")));
         void DMA1_Channel4_IRQ (void) ; // __attribute__((weak, alias ("_ZN6m3core14DefaultHendlerEv")));
         void DMA1_Channel5_IRQ (void) ; // __attribute__((weak, alias ("_ZN6m3core14DefaultHendlerEv")));
         void DMA1_Channel6_IRQ (void) ; // __attribute__((weak, alias ("_ZN6m3core14DefaultHendlerEv")));
         void DMA1_Channel7_IRQ (void) ; // __attribute__((weak, alias ("_ZN6m3core14DefaultHendlerEv")));
         void ADC1_2_IRQ (void) ; // __attribute__((weak, alias ("_ZN6m3core14DefaultHendlerEv")));
         void USB_HP_CAN1_TX_IRQ (void) ; // __attribute__((weak, alias ("_ZN6m3core14DefaultHendlerEv")));
         void USB_LP_CAN1_RX0_IRQ (void) ; // __attribute__((weak, alias ("_ZN6m3core14DefaultHendlerEv")));
         void CAN1_RX1_IRQ (void) ; // __attribute__((weak, alias ("_ZN6m3core14DefaultHendlerEv")));
         void CAN1_SCE_IRQ (void) ; // __attribute__((weak, alias ("_ZN6m3core14DefaultHendlerEv")));
         void EXTI9_5_IRQ (void) ; // __attribute__((weak, alias ("_ZN6m3core14DefaultHendlerEv")));
         void TIM1_BRK_TIM9_IRQ (void) ; // __attribute__((weak, alias ("_ZN6m3core14DefaultHendlerEv")));
         void TIM1_UP_TIM10_IRQ (void) ; // __attribute__((weak, alias ("_ZN6m3core14DefaultHendlerEv")));
         void TIM1_TRG_COM_TIM11_IRQ (void) ; // __attribute__((weak, alias ("_ZN6m3core14DefaultHendlerEv")));
         void TIM1_CC_IRQ (void) ; // __attribute__((weak, alias ("_ZN6m3core14DefaultHendlerEv")));
         void TIM2_IRQ (void) ; // __attribute__((weak, alias ("_ZN6m3core14DefaultHendlerEv")));
         void TIM3_IRQ (void) ; // __attribute__((weak, alias ("_ZN6m3core14DefaultHendlerEv")));
         void TIM4_IRQ (void) ; // __attribute__((weak, alias ("_ZN6m3core14DefaultHendlerEv")));
         void I2C1_EV_IRQ (void) ; // __attribute__((weak, alias ("_ZN6m3core14DefaultHendlerEv")));
         void I2C1_ER_IRQ (void) ; // __attribute__((weak, alias ("_ZN6m3core14DefaultHendlerEv")));
         void I2C2_EV_IRQ (void) ; // __attribute__((weak, alias ("_ZN6m3core14DefaultHendlerEv")));
         void I2C2_ER_IRQ (void) ; // __attribute__((weak, alias ("_ZN6m3core14DefaultHendlerEv")));
         void SPI1_IRQ (void) ; // __attribute__((weak, alias ("_ZN6m3core14DefaultHendlerEv")));
         void SPI2_IRQ (void) ; // __attribute__((weak, alias ("_ZN6m3core14DefaultHendlerEv")));
         void USART1_IRQ (void) ; // __attribute__((weak, alias ("_ZN6m3core14DefaultHendlerEv")));
         void USART2_IRQ (void) ; // __attribute__((weak, alias ("_ZN6m3core14DefaultHendlerEv")));
         void USART3_IRQ (void) ; // __attribute__((weak, alias ("_ZN6m3core14DefaultHendlerEv")));
         void EXTI15_10_IRQ (void) ; // __attribute__((weak, alias ("_ZN6m3core14DefaultHendlerEv")));
         void RTCAlarm_IRQ (void) ; // __attribute__((weak, alias ("_ZN6m3core14DefaultHendlerEv")));
         void USBWakeUp_IRQ (void) ; // __attribute__((weak, alias ("_ZN6m3core14DefaultHendlerEv")));
         void TIM8_BRK_TIM12_IRQ (void) ; // __attribute__((weak, alias ("_ZN6m3core14DefaultHendlerEv")));
         void TIM8_UP_TIM13_IRQ (void) ; // __attribute__((weak, alias ("_ZN6m3core14DefaultHendlerEv")));
         void TIM8_TRG_COM_TIM14_IRQ (void) ; // __attribute__((weak, alias ("_ZN6m3core14DefaultHendlerEv")));
         void TIM8_CC_IRQ (void) ; // __attribute__((weak, alias ("_ZN6m3core14DefaultHendlerEv")));
         void ADC3_IRQ (void) ; // __attribute__((weak, alias ("_ZN6m3core14DefaultHendlerEv")));
         void FSMC_IRQ (void) ; // __attribute__((weak, alias ("_ZN6m3core14DefaultHendlerEv")));
         void SDIO_IRQ (void) ; // __attribute__((weak, alias ("_ZN6m3core14DefaultHendlerEv")));
         void TIM5_IRQ (void) ; // __attribute__((weak, alias ("_ZN6m3core14DefaultHendlerEv")));
         void SPI3_IRQ (void) ; // __attribute__((weak, alias ("_ZN6m3core14DefaultHendlerEv")));
         void UART4_IRQ (void) ; // __attribute__((weak, alias ("_ZN6m3core14DefaultHendlerEv")));
         void UART5_IRQ (void) ; // __attribute__((weak, alias ("_ZN6m3core14DefaultHendlerEv")));
         void TIM6_IRQ (void) ; // __attribute__((weak, alias ("_ZN6m3core14DefaultHendlerEv")));
         void TIM7_IRQ (void) ; // __attribute__((weak, alias ("_ZN6m3core14DefaultHendlerEv")));
         void DMA2_Channel1_IRQ (void) ; // __attribute__((weak, alias ("_ZN6m3core14DefaultHendlerEv")));
         void DMA2_Channel2_IRQ (void) ; // __attribute__((weak, alias ("_ZN6m3core14DefaultHendlerEv")));
         void DMA2_Channel3_IRQ (void) ; // __attribute__((weak, alias ("_ZN6m3core14DefaultHendlerEv")));
         void DMA2_Channel4_5_IRQ (void) ; // __attribute__((weak, alias ("_ZN6m3core14DefaultHendlerEv")));

    }

}


#endif // INTERRUPTS_H
