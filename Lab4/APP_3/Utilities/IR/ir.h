#ifndef _IR_H_
#define _IR_H_	 

#define IR_ON			0
#define IR_OFF		1

#define IR_LEFT				GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_8)
#define IR_RIGHT 			GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_9)
#define IR_MIDDLE			GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_10)

void ir_init(void);
void ir_gpio_init(void);
		 				    
#endif
