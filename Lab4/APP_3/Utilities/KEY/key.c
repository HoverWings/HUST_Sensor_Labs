/***********************************************************************************
 KEY ����  huo  2016-06-01  08:45
 KEY IO��KEY1-PA4 KEY2-PC4 KEY3-PC5 KEY4-PB0 KEY5-PB1
************************************************************************************/
#include "stm32f10x.h"		//STM32F10xͷ�ļ�
#include "key.h"					//KEY����ͷ�ļ�

/* KEY��ʼ������ */
void key_init(void)
{
	key_gpio_init();
}
	
/* KEY GPIO��ʼ������ */
void key_gpio_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_GPIOC |RCC_APB2Periph_GPIOB, ENABLE);	//ʹ��GPIOA/C/Bʱ�� 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;							//KEY����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;					//��������		
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

/* KEY���ܺ��� */
u8 key(KEY_e keyn)
{
	switch(keyn)
	{
		case KEY1:
			if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_4))	//����Ϊ�ߵ�ƽ
				return KEY_ON;
			else
				return KEY_OFF;
		case KEY2:
			if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_4))
				return KEY_ON;
			else
				return KEY_OFF;
		case KEY3:
			if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_5))
				return KEY_ON;
			else
				return KEY_OFF;
		case KEY4:
			if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0))
				return KEY_ON;
			else
				return KEY_OFF;
		case KEY5:
			if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1))
				return KEY_ON;
			else
				return KEY_OFF;
		default:
			return KEY_OFF;
	}
}

