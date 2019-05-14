/***********************************************************************************
 LED ����  huo  2016-06-01  08:30
 LED IO��LED1-PB5 LED2-PB6 LED3-PB7 LED4-PB8 LED5-PB9������ �ߵ�ƽ����
************************************************************************************/
#include "stm32f10x.h"		//STM32F10xͷ�ļ�
#include "led.h"					//LED����ͷ�ļ�

/* LED��ʼ������ */
void led_init(void)
{
	led_gpio_init();
}

/* LED GPIO��ʼ������ */
void led_gpio_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);		//ʹ��GPIOBʱ�� 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 |GPIO_Pin_6 |GPIO_Pin_7 |GPIO_Pin_8 |GPIO_Pin_9;	//LED����
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;					//�������
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_ResetBits(GPIOB, GPIO_Pin_5 |GPIO_Pin_6 |GPIO_Pin_7 |GPIO_Pin_8 |GPIO_Pin_9);				//����͵�ƽ
}

/* LED���ܺ��� */
void led(LED_e ledn,LED_status status)
{
	switch(ledn)
	{
		case LED1:
			if(status == LED_OFF)
				GPIO_ResetBits(GPIOB,GPIO_Pin_5);		//����͵�ƽ
			else
				GPIO_SetBits(GPIOB,GPIO_Pin_5);			//����ߵ�ƽ
			break;
		case LED2:
			if(status == LED_OFF)
				GPIO_ResetBits(GPIOB,GPIO_Pin_6);
			else
				GPIO_SetBits(GPIOB,GPIO_Pin_6);
			break;
		case LED3:
			if(status == LED_OFF)
				GPIO_ResetBits(GPIOB,GPIO_Pin_7);
			else
				GPIO_SetBits(GPIOB,GPIO_Pin_7);
			break;
		case LED4:
			if(status == LED_OFF)
				GPIO_ResetBits(GPIOB,GPIO_Pin_8);
			else
				GPIO_SetBits(GPIOB,GPIO_Pin_8);
			break;
		case LED5:
			if(status == LED_OFF)
				GPIO_ResetBits(GPIOB,GPIO_Pin_9);
			else
				GPIO_SetBits(GPIOB,GPIO_Pin_9);
			break;
		default:
			LED_ALL_OFF;
	}
}
