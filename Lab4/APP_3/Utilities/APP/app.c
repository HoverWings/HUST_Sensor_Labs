/***********************************************************************************
 APP �û�Ӧ�ó���  huo  2016-06-01  16:30
 �ۺ���ʾ����
************************************************************************************/
#include "stm32f10x.h"		//STM32F10xͷ�ļ�
#include "led.h"					//LED����ͷ�ļ�
#include "key.h"					//KEY����ͷ�ļ�
#include "ir.h"						//IR����ͷ�ļ�
#include "DCMotor.h"			//DCMotor����ͷ�ļ�
#include "remote.h"				//Remote����ͷ�ļ�
#include "app.h"					//�û�Ӧ�ó���ͷ�ļ�

volatile u8 MODE_Select=1;					//ģʽѡ��ģʽ
volatile u8 MODE_Wifi=0;						//WiFi����ģʽ
volatile u8 MODE_Remote=0;					//ң�ؿ���ģʽ
volatile u8 MODE_Trackline=0;				//ѭ��ģʽ
volatile u8 MODE_Avoid=0;						//���ϱ���ģʽ

/* ����ɨ��Ӧ�ú��� */
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

/* ѭ��С������ */
/*Ч�������������С��ѭ����ǰ�����ϰ�������ϰ��ﴫ��������⵽�ϰ��ʱ����ѭ����
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
		
    //TIM_ClearITPendingBit(TIM2, TIM_IT_Update  );  //���TIMx�����жϱ�־ 

		




/* ����WiFi�������� */
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

/* ң��ģʽ��Ϣ���� */
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

/* Follow����ģʽ��Ϣ���� */
void Avoid_msgHandler(void)
{
	//�������ϰ��ﴫ������
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
//		back_off(200);			//ǰ�����ϰ�������
//		LED_ALL_OFF;
//		led(LED5,LED_ON);
//		led(LED3,LED_ON);
//		led(LED1,LED_ON);
		back_off(200);		//ǰ�����ϰ������
		LED_ALL_OFF;
		led(LED5,LED_ON);
		led(LED4,LED_ON);
//		turn_right(200);		//ǰ�����ϰ����ҹ�
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




