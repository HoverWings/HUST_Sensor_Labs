#ifndef _REMOTE_H_
#define _REMOTE_H_	 

#define REMOTE_ON			1
#define REMOTE_OFF		0

#define REMOTE_VT 		GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_6)
#define REMOTE_D0 		GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_5)
#define REMOTE_D1 		GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_4)
#define REMOTE_D2 		GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_3)
#define REMOTE_D3 		GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_2)
#define REMOTE_D4 		GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_1)
#define REMOTE_D5 		GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_0)

void remote_init(void);
void remote_gpio_init(void);
		 				    
#endif
