#ifndef _USART_H_
#define _USART_H_

#include "stdio.h"	

#define FRM_VAL_SOF (0xFE)
#define FRM_VAL_EOF (0x0A)

#define FRM_STA_SOF   0x00
#define FRM_STA_LEN   0x01
#define FRM_STA_CMD   0x02
#define FRM_STA_DAT0  0x03
#define FRM_STA_DAT1  0x04
#define FRM_STA_DAT2  0x05
#define FRM_STA_DAT3  0x06
#define FRM_STA_EOF   0x07

void usart1_init(u32 bound);
void usart1_gpio_init(void);
void usart1_usart_init(u32 bound);
void usart1_nvic_init(void);
void wifi_init(void);
void wifi_gpio_init(void);
void wifi_uart_init(void);
void wifi_nvic_init(void);

#endif


