/***********************************************************************************
 KEY 驱动  huo  2016-06-01  08:45
 KEY IO：KEY1-PA4 KEY2-PC4 KEY3-PC5 KEY4-PB0 KEY5-PB1
************************************************************************************/
#include "stm32f10x.h"		//STM32F10x头文件
#include "key.h"					//KEY驱动头文件

/* KEY初始化函数 */
void key_init(void)
{
	key_gpio_init();
}
	
/* KEY GPIO初始化函数 */
void key_gpio_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_GPIOC |RCC_APB2Periph_GPIOB, ENABLE);	//使能GPIOA/C/B时钟 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;							//KEY引脚
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;					//上拉输入		
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

/* KEY功能函数 */
u8 key(KEY_e keyn)
{
	switch(keyn)
	{
		case KEY1:
			if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_4))	//输入为高电平
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

