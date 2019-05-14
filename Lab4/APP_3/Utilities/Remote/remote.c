/***********************************************************************************
 Remote 驱动  huo  2016-06-01  13:30
 Remote IO：Wireless_VT-PD6
            Wireless_D0-PD5 Wireless_D1-PD4 Wireless_D2-PD3
            Wireless_D3-PD2 Wireless_D4-PD1 Wireless_D5-PD0
************************************************************************************/
#include "stm32f10x.h"		//STM32F10x头文件
#include "remote.h"				//Remote驱动头文件

/* REMOTE初始化函数 */
void remote_init(void)
{
	remote_gpio_init();
}

/* REMOTE GPIO初始化函数 */
void remote_gpio_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_5|GPIO_Pin_4|GPIO_Pin_3|GPIO_Pin_2|GPIO_Pin_1|GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//设置成浮空输入
	GPIO_Init(GPIOD, &GPIO_InitStructure);
}

