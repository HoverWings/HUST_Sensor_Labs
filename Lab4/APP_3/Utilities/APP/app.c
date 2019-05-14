/***********************************************************************************
 APP 用户应用程序  huo  2016-06-01  16:30
 综合演示程序
************************************************************************************/
#include "stm32f10x.h"		//STM32F10x头文件
#include "led.h"					//LED驱动头文件
#include "key.h"					//KEY驱动头文件
#include "ir.h"						//IR驱动头文件
#include "DCMotor.h"			//DCMotor驱动头文件
#include "remote.h"				//Remote驱动头文件
#include "app.h"					//用户应用程序头文件

volatile u8 MODE_Select=1;					//模式选择模式
volatile u8 MODE_Wifi=0;						//WiFi控制模式
volatile u8 MODE_Remote=0;					//遥控控制模式
volatile u8 MODE_Trackline=0;				//循迹模式
volatile u8 MODE_Avoid=0;						//避障避险模式

/* 按键扫描应用函数 */
void ScanKEY(void)
{
	if(key(KEY1)==KEY_ON)
		led(LED5,LED_ON);
	else
		led(LED5,LED_OFF);
	if(key(KEY2)==KEY_ON)
		led(LED4,LED_ON);
	else
		led(LED4,LED_OFF);
	if(key(KEY3)==KEY_ON)
		led(LED3,LED_ON);
	else
		led(LED3,LED_OFF);
	if(key(KEY4)==KEY_ON)
		led(LED2,LED_ON);
	else
		led(LED2,LED_OFF);
	if(key(KEY5)==KEY_ON)
		led(LED1,LED_ON);
	else
		led(LED1,LED_OFF);
}

/* 循迹小车程序 */
/*效果：正常情况下小车循迹，前方有障碍物（三个障碍物传感器均检测到障碍物）时逆向循迹。
*/
void Trackline(void)
{	
	
	u16 DCMotor_Val=250;
	ScanKEY();
	if(REMOTE_VT == REMOTE_ON)
	{
		if(REMOTE_D0 == REMOTE_ON && REMOTE_D1 == REMOTE_ON)
		{
			DCMotor_Val=250;
			do
				LED_ALL_OFF;
			while(REMOTE_D5 == REMOTE_ON && REMOTE_D4 == REMOTE_ON);
		}
		if(REMOTE_D0 == REMOTE_ON)
		{
			DCMotor_Val -= 50;
			if(DCMotor_Val < 50)
				DCMotor_Val = 50;
			do
				LED_ALL_OFF;
			while(REMOTE_D0 == REMOTE_ON);
		}
		if(REMOTE_D1 == REMOTE_ON)
		{
			DCMotor_Val += 50;
			if(DCMotor_Val > 500)
				DCMotor_Val = 500;
			do
				LED_ALL_OFF;
			while(REMOTE_D1 == REMOTE_ON);
		}
		if(REMOTE_D2 == REMOTE_ON)
		{
			turn_right(DCMotor_Val);
			LED_ALL_OFF;
			led(LED1,LED_ON);
			led(LED2,LED_ON);
		}
		if(REMOTE_D3 == REMOTE_ON)
		{
			turn_left(DCMotor_Val);
			LED_ALL_OFF;
			led(LED5,LED_ON);
			led(LED4,LED_ON);
		}
		if(REMOTE_D4 == REMOTE_ON)
		{
			back_off(DCMotor_Val);
			LED_ALL_OFF;
			led(LED5,LED_ON);
			led(LED3,LED_ON);
			led(LED1,LED_ON);
		}
		if(REMOTE_D5 == REMOTE_ON)
		{
			go_forward(DCMotor_Val);
			LED_ALL_OFF;
			led(LED4,LED_ON);
			led(LED3,LED_ON);
			led(LED2,LED_ON);
		}
	}
		//if(IR_LEFT==IR_ON || IR_MIDDLE==IR_ON || IR_RIGHT==IR_ON)
	else if((key(KEY1)==KEY_OFF && key(KEY2)==KEY_OFF) && (key(KEY4)==KEY_ON || key(KEY5)==KEY_ON)){
				turn_right(400);
		if(IR_LEFT==IR_ON && IR_MIDDLE==IR_ON && IR_RIGHT==IR_ON)
		{
			back_off(50);
			LED_ALL_OFF;
			led(LED5,LED_ON);
			led(LED3,LED_ON);
			led(LED1,LED_ON);
		}
		else if(IR_LEFT==IR_OFF && IR_MIDDLE==IR_ON && IR_RIGHT==IR_OFF)
		{
			back_off(50);
			LED_ALL_OFF;
			led(LED5,LED_ON);
			led(LED3,LED_ON);
			led(LED1,LED_ON);
		}
		else if(IR_LEFT==IR_ON && IR_RIGHT==IR_OFF)
		{
			turn_right(50);
			LED_ALL_OFF;
			led(LED1,LED_ON);
			led(LED2,LED_ON);
		}
		else if(IR_LEFT==IR_OFF && IR_RIGHT==IR_ON)
		{
			turn_left(50);
			LED_ALL_OFF;
			led(LED5,LED_ON);
			led(LED4,LED_ON);
		}}

			
		else if((key(KEY1)==KEY_ON || key(KEY2)==KEY_ON) && (key(KEY4)==KEY_OFF || key(KEY5)==KEY_OFF))
		{
				turn_left(400);
			if(IR_LEFT==IR_ON && IR_MIDDLE==IR_ON && IR_RIGHT==IR_ON)
		{
			back_off(50);
			LED_ALL_OFF;
			led(LED5,LED_ON);
			led(LED3,LED_ON);
			led(LED1,LED_ON);
		}
		else if(IR_LEFT==IR_OFF && IR_MIDDLE==IR_ON && IR_RIGHT==IR_OFF)
		{
			back_off(50);
			LED_ALL_OFF;
			led(LED5,LED_ON);
			led(LED3,LED_ON);
			led(LED1,LED_ON);
		}
		else if(IR_LEFT==IR_ON && IR_RIGHT==IR_OFF)
		{
			turn_right(50);
			LED_ALL_OFF;
			led(LED1,LED_ON);
			led(LED2,LED_ON);
		}
		else if(IR_LEFT==IR_OFF && IR_RIGHT==IR_ON)
		{
			turn_left(50);
			LED_ALL_OFF;
			led(LED5,LED_ON);
			led(LED4,LED_ON);
		}}


			
		else if(((key(KEY1)==KEY_ON && key(KEY2)==KEY_ON) && (key(KEY3)==KEY_ON) &&(key(KEY4)==KEY_ON && key(KEY5)==KEY_ON))||((key(KEY1)==KEY_OFF && key(KEY2)==KEY_OFF) && (key(KEY3)==KEY_OFF) &&(key(KEY4)==KEY_OFF && key(KEY5)==KEY_OFF))){
        do {turn_left(200);
            if(IR_LEFT==IR_ON && IR_MIDDLE==IR_ON && IR_RIGHT==IR_ON)
		{
			back_off(50);
			LED_ALL_OFF;
			led(LED5,LED_ON);
			led(LED3,LED_ON);
			led(LED1,LED_ON);
		}
		else if(IR_LEFT==IR_OFF && IR_MIDDLE==IR_ON && IR_RIGHT==IR_OFF)
		{
			back_off(50);
			LED_ALL_OFF;
			led(LED5,LED_ON);
			led(LED3,LED_ON);
			led(LED1,LED_ON);
		}
		else if(IR_LEFT==IR_ON && IR_RIGHT==IR_OFF)
		{
			turn_right(50);
			LED_ALL_OFF;
			led(LED1,LED_ON);
			led(LED2,LED_ON);
		}
		else if(IR_LEFT==IR_OFF && IR_RIGHT==IR_ON)
		{
			turn_left(50);
			LED_ALL_OFF;
			led(LED5,LED_ON);
			led(LED4,LED_ON);
		}

}
        while((key(KEY1)==KEY_OFF && key(KEY2)==KEY_OFF) && (key(KEY3)==KEY_ON) &&(key(KEY4)==KEY_OFF && key(KEY5)==KEY_OFF));					

}
		
		else{
        go_forward(200);
			if(IR_LEFT==IR_ON && IR_MIDDLE==IR_ON && IR_RIGHT==IR_ON)
		{
			back_off(50);
			LED_ALL_OFF;
			led(LED5,LED_ON);
			led(LED3,LED_ON);
			led(LED1,LED_ON);
		}
		else if(IR_LEFT==IR_OFF && IR_MIDDLE==IR_ON && IR_RIGHT==IR_OFF)
		{
			back_off(50);
			LED_ALL_OFF;
			led(LED5,LED_ON);
			led(LED3,LED_ON);
			led(LED1,LED_ON);
		}
		else if(IR_LEFT==IR_ON && IR_RIGHT==IR_OFF)
		{
			turn_right(50);
			LED_ALL_OFF;
			led(LED1,LED_ON);
			led(LED2,LED_ON);
		}
		else if(IR_LEFT==IR_OFF && IR_RIGHT==IR_ON)
		{
			turn_left(50);
			LED_ALL_OFF;
			led(LED5,LED_ON);
			led(LED4,LED_ON);
		}
		else 
		{
			go_forward(50);
			LED_ALL_OFF;
			led(LED4,LED_ON);
			led(LED3,LED_ON);
			led(LED2,LED_ON);
		}  


}
			
		
        
}
		
    //TIM_ClearITPendingBit(TIM2, TIM_IT_Update  );  //清除TIMx更新中断标志 

		




/* 解析WiFi串口数据 */
void WIFI_msgHandler(u8 msg[5])
{
	switch(msg[0])
	{
		case 0x50:
		{	brake();LED_ALL_ON;	}
		break;
		case 0x51:
		{	go_forward(msg[1]<<8|msg[2]);
			LED_ALL_OFF;led(LED4,LED_ON);led(LED3,LED_ON);led(LED2,LED_ON);	}
		break;
		case 0x52:
		{	back_off(msg[1]<<8|msg[2]);
			LED_ALL_OFF;led(LED5,LED_ON);led(LED3,LED_ON);led(LED1,LED_ON);	}
		break;
		case 0x54:
		{	turn_left(msg[3]<<8|msg[4]);
			LED_ALL_OFF;led(LED5,LED_ON);led(LED4,LED_ON);	}
		break;
		case 0x58:
		{	turn_right(msg[3]<<8|msg[4]);
			LED_ALL_OFF;led(LED2,LED_ON);led(LED1,LED_ON);	}
		break;
		case 0x60:
			LED_ALL_OFF;
		break;
		case 0x61:
			if(msg[1]==0x1F || msg[2]==0x1F)
			{	led(LED5,LED_ON);led(LED4,LED_ON);	}
			else
			{	led(LED5,LED_OFF);led(LED4,LED_OFF);	}
		break;
		case 0x62:
			if(msg[1]==0x1F || msg[2]==0x1F)
				led(LED3,LED_ON);
			else
				led(LED3,LED_OFF);
		break;
		case 0x64:
			if(msg[1]==0x1F || msg[2]==0x1F)
			{	led(LED2,LED_ON);led(LED1,LED_ON);	}
			else
			{	led(LED2,LED_OFF);led(LED1,LED_OFF);	}
		break;
		case 0x68:
			LED_ALL_ON;
		break;
	}
}

/* 遥控模式信息处理 */
void Remote_msgHandler(void)
{
	static u16 DCMotor_Val=250;
	
	if(REMOTE_VT == REMOTE_ON)
	{
		if(REMOTE_D0 == REMOTE_ON && REMOTE_D1 == REMOTE_ON)
		{
			DCMotor_Val=250;
			do
				LED_ALL_OFF;
			while(REMOTE_D5 == REMOTE_ON && REMOTE_D4 == REMOTE_ON);
		}
		if(REMOTE_D0 == REMOTE_ON)
		{
			DCMotor_Val -= 50;
			if(DCMotor_Val < 50)
				DCMotor_Val = 50;
			do
				LED_ALL_OFF;
			while(REMOTE_D0 == REMOTE_ON);
		}
		if(REMOTE_D1 == REMOTE_ON)
		{
			DCMotor_Val += 50;
			if(DCMotor_Val > 500)
				DCMotor_Val = 500;
			do
				LED_ALL_OFF;
			while(REMOTE_D1 == REMOTE_ON);
		}
		if(REMOTE_D2 == REMOTE_ON)
		{
			turn_right(DCMotor_Val);
			LED_ALL_OFF;
			led(LED1,LED_ON);
			led(LED2,LED_ON);
		}
		if(REMOTE_D3 == REMOTE_ON)
		{
			turn_left(DCMotor_Val);
			LED_ALL_OFF;
			led(LED5,LED_ON);
			led(LED4,LED_ON);
		}
		if(REMOTE_D4 == REMOTE_ON)
		{
			back_off(DCMotor_Val);
			LED_ALL_OFF;
			led(LED5,LED_ON);
			led(LED3,LED_ON);
			led(LED1,LED_ON);
		}
		if(REMOTE_D5 == REMOTE_ON)
		{
			go_forward(DCMotor_Val);
			LED_ALL_OFF;
			led(LED4,LED_ON);
			led(LED3,LED_ON);
			led(LED2,LED_ON);
		}
	}
	else
	{
		brake();
		LED_ALL_ON;
	}
}

/* Follow跟随模式信息处理 */
void Avoid_msgHandler(void)
{
	//当三个障碍物传感器均
	if((IR_LEFT==IR_ON && IR_MIDDLE==IR_ON && IR_RIGHT==IR_ON) || (key(KEY1)==KEY_ON && key(KEY5)==KEY_ON))
	{
		back_off(200);
		LED_ALL_OFF;
		led(LED5,LED_ON);
		led(LED3,LED_ON);
		led(LED1,LED_ON);
	}
	else if((IR_LEFT==IR_OFF && IR_MIDDLE==IR_ON && IR_RIGHT==IR_OFF) || (key(KEY1)==KEY_ON && key(KEY5)==KEY_ON))
	{
//		back_off(200);			//前方有障碍，后退
//		LED_ALL_OFF;
//		led(LED5,LED_ON);
//		led(LED3,LED_ON);
//		led(LED1,LED_ON);
		back_off(200);		//前方有障碍，左拐
		LED_ALL_OFF;
		led(LED5,LED_ON);
		led(LED4,LED_ON);
//		turn_right(200);		//前方有障碍，右拐
//		LED_ALL_OFF;
//		led(LED1,LED_ON);
//		led(LED2,LED_ON);
	}
	else if((IR_LEFT==IR_ON && IR_RIGHT==IR_OFF) || (key(KEY1)==KEY_ON && key(KEY5)==KEY_OFF))
	{
		turn_left(200);
		LED_ALL_OFF;
		led(LED1,LED_ON);
		led(LED2,LED_ON);
	}
	else if((IR_LEFT==IR_OFF && IR_RIGHT==IR_ON) || (key(KEY1)==KEY_OFF && key(KEY5)==KEY_ON))
	{
		turn_right(200);
		LED_ALL_OFF;
		led(LED5,LED_ON);
		led(LED4,LED_ON);
	}
	else 
	{
		go_forward(200);
		LED_ALL_OFF;
		led(LED4,LED_ON);
		led(LED3,LED_ON);
		led(LED2,LED_ON);
	}
}

/*follow*/

void Follow_msgHandler(void){
    if((IR_LEFT==IR_ON && IR_MIDDLE==IR_ON && IR_RIGHT==IR_ON) || (key(KEY1)==KEY_ON && key(KEY5)==KEY_ON))
		{
			back_off(100);
			LED_ALL_OFF;
			led(LED5,LED_ON);
			led(LED3,LED_ON);
			led(LED1,LED_ON);
		}
		else if((IR_LEFT==IR_OFF && IR_MIDDLE==IR_ON && IR_RIGHT==IR_OFF) || (key(KEY1)==KEY_ON && key(KEY5)==KEY_ON))
		{
			go_forward(100);
			LED_ALL_OFF;
			led(LED5,LED_ON);
			led(LED3,LED_ON);
			led(LED1,LED_ON);
		}
		else if((IR_LEFT==IR_ON && IR_RIGHT==IR_OFF) || (key(KEY1)==KEY_ON && key(KEY5)==KEY_OFF))
		{
			turn_right(100);
			LED_ALL_OFF;
			led(LED1,LED_ON);
			led(LED2,LED_ON);
		}
		else if((IR_LEFT==IR_OFF && IR_RIGHT==IR_ON) || (key(KEY1)==KEY_OFF && key(KEY5)==KEY_ON))
		{
			turn_left(100);
			LED_ALL_OFF;
			led(LED5,LED_ON);
			led(LED4,LED_ON);
		}
		else 
		{
			//go_forward(100);
			brake();
			LED_ALL_OFF;
			led(LED4,LED_ON);
			led(LED3,LED_ON);
			led(LED2,LED_ON);
		}
}




