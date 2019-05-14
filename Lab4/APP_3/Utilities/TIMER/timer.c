/***********************************************************************************
 TIMER ����  huo  2016-06-01  09:45
 ����TimeBase
************************************************************************************/
#include "stm32f10x.h"		//STM32F10xͷ�ļ�
#include "led.h"					//LED����ͷ�ļ�
#include "key.h"					//KEY����ͷ�ļ�
#include "DCMotor.h"			//DCMotor����ͷ�ļ�
#include "remote.h"				//Remote����ͷ�ļ�
#include "app.h"					//�û�Ӧ�ó���ͷ�ļ�
#include "timer.h"				//TIMER����ͷ�ļ�

extern u8 WIFI_msg[5];									//WiFi���ܵ�������

extern volatile u8 MODE_Select;					//ģʽѡ��ģʽ
extern volatile u8 MODE_Wifi;						//WiFi����ģʽ
extern volatile u8 MODE_Remote;					//ң�ؿ���ģʽ
extern volatile u8 MODE_Trackline;			//ѭ��ģʽ
extern volatile u8 MODE_Avoid;					//���ϱ���ģʽ

//ͨ�ö�ʱ��2�жϳ�ʼ��
//����ʱ��ѡ��ΪAPB1��2������APB1Ϊ36M
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
void TIM2_Int_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //ʱ��ʹ��
	
	//��ʱ��TIM2��ʼ��
	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE ); //ʹ��ָ����TIM3�ж�,��������ж�

	//�ж����ȼ�NVIC����
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  //TIM2�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //��ʼ��NVIC�Ĵ���

	TIM_Cmd(TIM2, ENABLE);  //ʹ��TIMx					 
}

//��ʱ��2�жϷ������
void TIM2_IRQHandler(void)   //TIM2�ж�
{
	static u8 T;
	
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)  //���TIM2�����жϷ������
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update  );  //���TIMx�����жϱ�־ 

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

