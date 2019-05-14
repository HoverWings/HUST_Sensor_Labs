/***********************************************************************************
 APP �û�Ӧ�ó���  huo  2016-06-01  16:30
 �ۺ���ʾ����
************************************************************************************/
#include "stm32f10x.h"		//STM32F10xͷ�ļ�

#include "led.h"					//LED����ͷ�ļ�
#include "key.h"					//KEY����ͷ�ļ�
#include "ir.h"						//IR����ͷ�ļ�
#include "timer.h"				//TIMER����ͷ�ļ�
#include "usart.h"				//USART����ͷ�ļ�	  
#include "DCMotor.h"			//DCMotor����ͷ�ļ�
#include "remote.h"				//Remote����ͷ�ļ�
#include "app.h"					//�û�Ӧ�ó���ͷ�ļ�
/*
extern u8 WIFI_msg[5];									//WiFi���ܵ�������

extern volatile u8 MODE_Select;					//ģʽѡ��ģʽ
extern volatile u8 MODE_Wifi;						//WiFi����ģʽ
extern volatile u8 MODE_Remote;					//ң�ؿ���ģʽ
extern volatile u8 MODE_Trackline;			//ѭ��ģʽ
extern volatile u8 MODE_Avoid;					//���ϱ���ģʽ
*/
int main(void)
{
	led_init();						//LED�Ƴ�ʼ��
	key_init();						//KEY������ʼ��
	ir_init();						//IR������ϳ�ʼ��
	DCMotor_init(899,0);	//����Ƶ��PWMƵ��=72000000/900=80Khz
	remote_init();				//Remoteң������ʼ��
	/* ֻҪ�����õ��жϣ�����Ҫ�����жϷ��飻��ʹ��Ĭ�Ϸ��鷽��  */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	TIM2_Int_Init(9,7199);//10Khz�ļ���Ƶ�ʣ�������10Ϊ1ms  
	usart1_init(115200);	//USART1��ʼ����֧��printf
	wifi_init();					//WiFiģ���ʼ��
	
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

