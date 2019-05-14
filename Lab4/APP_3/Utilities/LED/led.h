#ifndef _LED_H_
#define _LED_H_

#define LED_ALL_OFF GPIO_ResetBits(GPIOB, GPIO_Pin_5 |GPIO_Pin_6 |GPIO_Pin_7 |GPIO_Pin_8 |GPIO_Pin_9)
#define LED_ALL_ON	GPIO_SetBits(GPIOB, GPIO_Pin_5 |GPIO_Pin_6 |GPIO_Pin_7 |GPIO_Pin_8 |GPIO_Pin_9)

/*! 枚举LED编号 */
typedef enum
{
  LED1 = 1,
  LED2,
  LED3,
  LED4,
  LED5,
}LED_e;

/*! 枚举LED亮灭状态 */
typedef enum LED_status
{
  LED_OFF =   0,            //灯灭(对应低电平)
  LED_ON  =   1             //灯亮(对应高电平)
}LED_status; 

void led_init(void);
void led_gpio_init(void);
void led(LED_e ledn,LED_status status);
		 				    
#endif
