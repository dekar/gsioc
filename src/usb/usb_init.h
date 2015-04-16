#ifndef USB_ACM_H
#define USB_ACM_H

#include "stm32f10x.h"


//extern u32 count_out;
//extern u8 buffer_out[VIRTUAL_COM_PORT_DATA_SIZE];
#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}

#endif

#define RCC_APB2Periph_GPIO_DISCONNECT RCC_APB2Periph_GPIOA

#define USB_DISCONNECT_PIN (1<<15)


#define USB_DISCONNECT GPIOA

#endif
