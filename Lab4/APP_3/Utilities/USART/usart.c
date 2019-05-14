/***********************************************************************************
 USART ����  huo  2016-06-01  15:00
 USART1 IO��TX1-PA9 RX1-PA10 ֧��printf
************************************************************************************/
#include "stm32f10x.h"		//STM32F10xͷ�ļ�
#include "app.h"					//�û�Ӧ�ó���ͷ�ļ�
#include "usart.h"				//USART����ͷ�ļ�	  

//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
_sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc������ʹ��USART1��USART1�����ʼ���ſ��ã� 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//ѭ������,ֱ���������   
    USART1->DR = (u8) ch;      
	return ch;
}
#endif 

/*ʹ��microLib�ķ���*/
 /* 
int fputc(int ch, FILE *f)
{
	USART_SendData(USART1, (uint8_t) ch);

	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET) {}	
   
    return ch;
}
int GetKey (void)  { 

    while (!(USART1->SR & USART_FLAG_RXNE));

    return ((int)(USART1->DR & 0x1FF));
}
*/
 
/* ����1��ʼ�� */  
void usart1_init(u32 bound)
{
	usart1_gpio_init();
	usart1_usart_init(bound);
	usart1_nvic_init();
}

/* USART1 GPIO��ʼ������ */
void usart1_gpio_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��GPIOAʱ��
	
	//USART1_TX   GPIOA.9
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.9
   
  //USART1_RX	  GPIOA.10��ʼ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.10  
}

/* USART1 USART��ʼ������ */
void usart1_usart_init(u32 bound)
{
	USART_InitTypeDef USART_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);	//ʹ��USART1ʱ��

  //USART ��ʼ������
	USART_InitStructure.USART_BaudRate = bound;//���ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

  USART_Init(USART1, &USART_InitStructure); //��ʼ������1
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
  USART_Cmd(USART1, ENABLE);                    //ʹ�ܴ���1 
}

/* USART1 NVIC��ʼ������ */
void usart1_nvic_init(void)
{
 	NVIC_InitTypeDef NVIC_InitStructure;

  //Usart1 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x03 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
}

/* ����1�жϷ������ */
void USART1_IRQHandler(void)                	//����1�жϷ������
{
	uint16_t Res;
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
	{
		Res =USART_ReceiveData(USART1);	//��ȡ���յ�������
		USART_SendData(USART1,Res);
  } 
} 

/* WiFi��ʼ�� */  
void wifi_init(void)
{
    wifi_gpio_init();
    wifi_nvic_init();
    wifi_uart_init();
}

/* WiFi GPIO��ʼ������ */
void wifi_gpio_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	/********************************************************
	* Configure USART3 use for communication with zigbee
	* [PB10]  --->  TX    [PB11]  --->  RX
	*******************************************************/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	//ʹ��GPIOBʱ��

	/* Configure USART3 Tx (PB10)as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	/* Configure USART3 Rx (PB11) as input floating */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

/* WiFi USART��ʼ������ */
void wifi_uart_init(void)
{
	/********************************************************
	* UART3 configuration
	* UART3 configured as follow:
		- BaudRate = 115200 baud
		- Word Length = 8 Bits
		- One Stop Bit
		- No parity
		- Hardware flow control disabled (RTS and CTS signals)
		- Receive and transmit enabled
	*******************************************************/

	USART_InitTypeDef USART_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);	//ʹ��USART3ʱ��

	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	/* Configure the USART3 */
	USART_Init(USART3 ,&USART_InitStructure);

	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
	/* Enable the USART3 */
	USART_Cmd(USART3, ENABLE);
}

/* WiFi NVIC��ʼ������ */
void wifi_nvic_init(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;//ͨ������Ϊ����3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3; //�ж�ռ�ȵȼ�1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2; //�ж���Ӧ���ȼ�10
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //���ж�
	NVIC_Init(&NVIC_InitStructure);
}

u8 WIFI_msg[5];		//WiFi���ܵ�������
/*******************************************************************************
* Function Name  : USART3_IRQHandler
* Description    : This function handles USART3 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void USART3_IRQHandler(void)
{
    static u8 state = FRM_STA_SOF;
//    static u8 msg[5];
    u8 ch;
    if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET) //�жϷ��������ж�
    {
        USART_ClearITPendingBit(USART3,USART_IT_RXNE);  //����жϱ�־
        ch=USART_ReceiveData(USART3);

        switch(state)
				{
					case FRM_STA_SOF:
							if(ch == FRM_VAL_SOF) state = FRM_STA_LEN;
							break;
					case FRM_STA_LEN:
							if(ch == 0x08)  state = FRM_STA_CMD;
							else state = FRM_STA_SOF;
							break;
					case FRM_STA_CMD: WIFI_msg[0] = ch; state = FRM_STA_DAT0; break;
					case FRM_STA_DAT0: WIFI_msg[1] = ch;state = FRM_STA_DAT1; break;
					case FRM_STA_DAT1: WIFI_msg[2] = ch;state = FRM_STA_DAT2; break;
					case FRM_STA_DAT2: WIFI_msg[3] = ch;state = FRM_STA_DAT3; break;
					case FRM_STA_DAT3: WIFI_msg[4] = ch;state = FRM_STA_EOF; break;
					case FRM_STA_EOF:
							if(ch == FRM_VAL_EOF)
							{
//								msgHandler(msg);
								state = FRM_STA_SOF;
							}
//							state = FRM_STA_SOF;
							break;
        }

    }
}
