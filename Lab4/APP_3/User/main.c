/***********************************************************************************
 APP 用户应用程序  huo  2016-06-01  16:30
 综合演示程序
************************************************************************************/
#include "stm32f10x.h"		//STM32F10x头文件

#include "led.h"					//LED驱动头文件
#include "key.h"					//KEY驱动头文件
#include "ir.h"						//IR驱动头文件
#include "timer.h"				//TIMER驱动头文件
#include "usart.h"				//USART驱动头文件	  
#include "DCMotor.h"			//DCMotor驱动头文件
#include "remote.h"				//Remote驱动头文件
#include "app.h"					//用户应用程序头文件
/*
extern u8 WIFI_msg[5];									//WiFi接受到的数据

extern volatile u8 MODE_Select;					//模式选择模式
extern volatile u8 MODE_Wifi;						//WiFi控制模式
extern volatile u8 MODE_Remote;					//遥控控制模式
extern volatile u8 MODE_Trackline;			//循迹模式
extern volatile u8 MODE_Avoid;					//避障避险模式
*/
int main(void)
{
	led_init();						//LED灯初始化
	key_init();						//KEY按键初始化
	ir_init();						//IR红外避障初始化
	DCMotor_init(899,0);	//不分频。PWM频率=72000000/900=80Khz
	remote_init();				//Remote遥控器初始化
	/* 只要工程用到中断，就需要设置中断分组；不使用默认分组方案  */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	TIM2_Int_Init(9,7199);//10Khz的计数频率，计数到10为1ms  
	usart1_init(115200);	//USART1初始化，支持printf
	wifi_init();					//WiFi模块初始化
	
	while (1)
	{

		/*if(MODE_Select)
		{
			brake();
			ScanKEY();
		}
		else if(MODE_Wifi)
			WIFI_msgHandler(WIFI_msg);
		else if(MODE_Remote)
			Remote_msgHandler();
 		else if(MODE_Trackline)
			Trackline();
		else if(MODE_Avoid)
			Avoid_msgHandler();*/

	} 
}

