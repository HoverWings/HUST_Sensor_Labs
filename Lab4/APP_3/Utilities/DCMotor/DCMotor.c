/***********************************************************************************
 DCMotor 驱动:Timer1 Timer3  huo  2016-06-01  10:30
 左前：EN-PE12 PWM_A-T1CH3-PE13  PWM_B-T1CH4-PE14
 左后：EN-PE10 PWM_A-T1CH1-PE9   PWM_B-T1CH2-PE11
 右前：EN-PD14 PWM_A-T3CH1-PC6   PWM_B-T3CH2-PC7
 右后：EN-PD15 PWM_A-T3CH3-PC8   PWM_B-T3CH4-PC9
 A 高 B 低 正转，A 低 B 高 反转 
************************************************************************************/
#include "stm32f10x.h"		//STM32F10x头文件
#include "DCMotor.h"			//DCMotor驱动头文件

/* DCMotor初始化函数 */
void DCMotor_init(u16 arr,u16 psc)
{
	LeftMotor_io_init();
	RightMotor_io_init();
	TIM1_PWM_Init(arr,psc);
	TIM3_PWM_Init(arr,psc);
}

/* DCMotor GPIO初始化函数 */
void LeftMotor_io_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE | RCC_APB2Periph_AFIO, ENABLE);
	
	GPIO_PinRemapConfig(GPIO_FullRemap_TIM1, ENABLE);

	//设置该引脚为复用输出功能,输出TIM1 CH1 CH2 CH3 CH4的PWM脉冲波形	GPIOE.9 GPIOE.11 GPIOE.13 GPIOE.14
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 |GPIO_Pin_11 |GPIO_Pin_13 |GPIO_Pin_14; //TIM1_CH1 CH2 CH3 CH4
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOE, &GPIO_InitStructure); 			 //初始化GPIO
 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 |GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOE, &GPIO_InitStructure);

	GPIO_SetBits(GPIOE, GPIO_Pin_10 |GPIO_Pin_12);
}
void RightMotor_io_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD | RCC_APB2Periph_AFIO, ENABLE);  //使能GPIO和AFIO复用功能时钟
	
	GPIO_PinRemapConfig(GPIO_FullRemap_TIM3, ENABLE);	//完全重映射TIM3 
	
	//设置该引脚为复用输出功能,输出TIM3 CH1 CH2 CH3 CH4的PWM脉冲波形	GPIOC.6 GPIOC.7 GPIOC.8 GPIOC.9
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9; //TIM_CH1 CH2 CH3 CH4
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化GPIO
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14 |GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	GPIO_SetBits(GPIOD, GPIO_Pin_14 |GPIO_Pin_15);
}

//TIM1 PWM部分初始化 
//PWM输出初始化
//arr：自动重装值
//psc：时钟预分频数
void TIM1_PWM_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE); //使能定时器1时钟
	
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_Pulse = 0; 
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);
	TIM_OC2Init(TIM1, &TIM_OCInitStructure);
	TIM_OC3Init(TIM1, &TIM_OCInitStructure);
	TIM_OC4Init(TIM1, &TIM_OCInitStructure);

	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);
	TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);
	
	TIM_ARRPreloadConfig(TIM1, ENABLE);
	
	TIM_CtrlPWMOutputs(TIM1,ENABLE); 
	
	TIM_Cmd(TIM1, ENABLE);
}

//TIM3 PWM部分初始化 
//PWM输出初始化
//arr：自动重装值
//psc：时钟预分频数
void TIM3_PWM_Init(u16 arr,u16 psc)
{  
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	//使能定时器3时钟
	
	//初始化TIM3
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	
	//初始化TIM3 Channel1 PWM模式	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM3 OC1
	//初始化TIM3 Channel2 PWM模式	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM3 OC2
	//初始化TIM3 Channel3 PWM模式	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高
	TIM_OC3Init(TIM3, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM3 OC3
	//初始化TIM3 Channel4 PWM模式	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高
	TIM_OC4Init(TIM3, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM3 OC4
	
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIM3在CCR1上的预装载寄存器
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIM3在CCR2上的预装载寄存器
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIM3在CCR3上的预装载寄存器
	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIM3在CCR4上的预装载寄存器
	
	TIM_ARRPreloadConfig(TIM3, ENABLE);

	TIM_Cmd(TIM3, ENABLE);  //使能TIM3
}

/* DCMotor 动作函数 parameter为0-500之间 */
void go_forward(u16 parameter)		//前进函数
{
	parameter += DCMOTOR_DEAD_VAL;
	if(parameter > DCMOTOR_MAX_VAL)
		parameter = DCMOTOR_MAX_VAL;
	TIM_SetCompare3(TIM1,parameter);
	TIM_SetCompare4(TIM1,0);
	TIM_SetCompare1(TIM1,parameter);		
	TIM_SetCompare2(TIM1,0);
	TIM_SetCompare1(TIM3,parameter);		
	TIM_SetCompare2(TIM3,0);
	TIM_SetCompare3(TIM3,parameter);
	TIM_SetCompare4(TIM3,0);
}

void back_off(u16 parameter)			//后退函数
{
	parameter += DCMOTOR_DEAD_VAL;
	if(parameter > DCMOTOR_MAX_VAL)
		parameter = DCMOTOR_MAX_VAL;
	TIM_SetCompare3(TIM1,0);
	TIM_SetCompare4(TIM1,parameter);
	TIM_SetCompare1(TIM1,0);		
	TIM_SetCompare2(TIM1,parameter);
	TIM_SetCompare1(TIM3,0);		
	TIM_SetCompare2(TIM3,parameter);
	TIM_SetCompare3(TIM3,0);
	TIM_SetCompare4(TIM3,parameter);
}

void turn_left(u16 parameter)			//左拐函数
{
	parameter += DCMOTOR_DEAD_VAL;
	if(parameter > DCMOTOR_MAX_VAL)
		parameter = DCMOTOR_MAX_VAL;
	TIM_SetCompare3(TIM1,0);
	TIM_SetCompare4(TIM1,parameter);
	TIM_SetCompare1(TIM1,0);		
	TIM_SetCompare2(TIM1,parameter);
	TIM_SetCompare1(TIM3,parameter);		
	TIM_SetCompare2(TIM3,0);
	TIM_SetCompare3(TIM3,parameter);
	TIM_SetCompare4(TIM3,0);
}

void turn_right(u16 parameter)		//右拐函数
{
	parameter += DCMOTOR_DEAD_VAL;
	if(parameter > DCMOTOR_MAX_VAL)
		parameter = DCMOTOR_MAX_VAL;
	TIM_SetCompare3(TIM1,parameter);
	TIM_SetCompare4(TIM1,0);
	TIM_SetCompare1(TIM1,parameter);		
	TIM_SetCompare2(TIM1,0);
	TIM_SetCompare1(TIM3,0);		
	TIM_SetCompare2(TIM3,parameter);
	TIM_SetCompare3(TIM3,0);
	TIM_SetCompare4(TIM3,parameter);
}

void brake(void)									//刹车函数
{
	TIM_SetCompare3(TIM1,0);
	TIM_SetCompare4(TIM1,0);
	TIM_SetCompare1(TIM1,0);
	TIM_SetCompare2(TIM1,0);
	TIM_SetCompare1(TIM3,0);
	TIM_SetCompare2(TIM3,0);
	TIM_SetCompare3(TIM3,0);
	TIM_SetCompare4(TIM3,0);
}


