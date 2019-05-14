/***********************************************************************************
 IR 驱动  huo  2016-06-01  09:00
 IR IO：IR_LEFT-PD8 IR_RIGHT-PD9 IR_MIDDLE-PD10  遇黑变亮，返回低电平
************************************************************************************/
#include "stm32f10x.h"		//STM32F10x头文件
#include "ir.h"						//IR驱动头文件

/* IR初始化函数 */
void ir_init(void)
{
	ir_gpio_init();
}

/* IR GPIO初始化函数 */
void ir_gpio_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//设置成上拉输入
	GPIO_Init(GPIOD, &GPIO_InitStructure);
}

