/***********************************************************************************
 TIMER 驱动  huo  2016-06-01  09:45
 用于TimeBase
************************************************************************************/
#include "stm32f10x.h"		//STM32F10x头文件
#include "led.h"					//LED驱动头文件
#include "key.h"					//KEY驱动头文件
#include "DCMotor.h"			//DCMotor驱动头文件
#include "remote.h"				//Remote驱动头文件
#include "app.h"					//用户应用程序头文件
#include "timer.h"				//TIMER驱动头文件

extern u8 WIFI_msg[5];									//WiFi接受到的数据

extern volatile u8 MODE_Select;					//模式选择模式
extern volatile u8 MODE_Wifi;						//WiFi控制模式
extern volatile u8 MODE_Remote;					//遥控控制模式
extern volatile u8 MODE_Trackline;			//循迹模式
extern volatile u8 MODE_Avoid;					//避障避险模式

//通用定时器2中断初始化
//这里时钟选择为APB1的2倍，而APB1为36M
//arr：自动重装值。
//psc：时钟预分频数
void TIM2_Int_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //时钟使能
	
	//定时器TIM2初始化
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE ); //使能指定的TIM3中断,允许更新中断

	//中断优先级NVIC设置
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  //TIM2中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //初始化NVIC寄存器

	TIM_Cmd(TIM2, ENABLE);  //使能TIMx					 
}

//定时器2中断服务程序
void TIM2_IRQHandler(void)   //TIM2中断
{
	static u8 T;
	
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)  //检查TIM2更新中断发生与否
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update  );  //清除TIMx更新中断标志 

		if(T==0)
		{
			if(REMOTE_VT == REMOTE_ON)
			{
				if(MODE_Select)
				{
					if(REMOTE_D0 == REMOTE_ON)
					{
						MODE_Select = 0;
						MODE_Wifi = 0;
						MODE_Remote = 0;
						MODE_Trackline = 0;
						MODE_Avoid = 1;
						do
							LED_ALL_OFF;
						while(REMOTE_D0 == REMOTE_ON);
					}
					else if(REMOTE_D1 == REMOTE_ON)
					{
						MODE_Select = 0;
						MODE_Wifi = 0;
						MODE_Remote = 0;
						MODE_Trackline = 1;
						MODE_Avoid = 0;
						do
							LED_ALL_OFF;
						while(REMOTE_D1 == REMOTE_ON);
					}
					else if(REMOTE_D2 == REMOTE_ON)
					{
						MODE_Select = 0;
						MODE_Wifi = 0;
						MODE_Remote = 1;
						MODE_Trackline = 0;
						MODE_Avoid = 0;
						do
							LED_ALL_OFF;
						while(REMOTE_D2 == REMOTE_ON);
					}
					else if(REMOTE_D3 == REMOTE_ON)
					{
						MODE_Select = 0;
						MODE_Wifi = 1;
						MODE_Remote = 0;
						MODE_Trackline = 0;
						MODE_Avoid = 0;
						do
							LED_ALL_OFF;
						while(REMOTE_D3 == REMOTE_ON);
					}
				}
				else if(REMOTE_D5 == REMOTE_ON && REMOTE_D4 == REMOTE_ON)
				{
					MODE_Select = 1;
					MODE_Trackline = 0;
					MODE_Wifi = 0;
					MODE_Remote = 0;
					MODE_Avoid = 0;
						do
							LED_ALL_OFF;
						while(REMOTE_D5 == REMOTE_ON && REMOTE_D4 == REMOTE_ON);
				}
			}
			T++;
		}
		else if(T==1)
		{
			if(MODE_Select)
			{
				brake();
				ScanKEY();
			}
			else if(MODE_Wifi)
				Follow_msgHandler();
				//WIFI_msgHandler(WIFI_msg);
			else if(MODE_Remote)
				Remote_msgHandler();
			else if(MODE_Trackline)
				Trackline();
			else if(MODE_Avoid)
				Avoid_msgHandler();
			T=0;
		}
	}
}

