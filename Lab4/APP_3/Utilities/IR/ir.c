/***********************************************************************************
 IR ����  huo  2016-06-01  09:00
 IR IO��IR_LEFT-PD8 IR_RIGHT-PD9 IR_MIDDLE-PD10  ���ڱ��������ص͵�ƽ
************************************************************************************/
#include "stm32f10x.h"		//STM32F10xͷ�ļ�
#include "ir.h"						//IR����ͷ�ļ�

/* IR��ʼ������ */
void ir_init(void)
{
	ir_gpio_init();
}

/* IR GPIO��ʼ������ */
void ir_gpio_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//���ó���������
	GPIO_Init(GPIOD, &GPIO_InitStructure);
}

