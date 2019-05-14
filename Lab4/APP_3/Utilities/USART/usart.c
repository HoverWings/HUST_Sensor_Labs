/***********************************************************************************
 USART 驱动  huo  2016-06-01  15:00
 USART1 IO：TX1-PA9 RX1-PA10 支持printf
************************************************************************************/
#include "stm32f10x.h"		//STM32F10x头文件
#include "app.h"					//用户应用程序头文件
#include "usart.h"				//USART驱动头文件	  

//加入以下代码,支持printf函数,而不需要选择use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
_sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数，使用USART1，USART1必须初始化才可用！ 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//循环发送,直到发送完毕   
    USART1->DR = (u8) ch;      
	return ch;
}
#endif 

/*使用microLib的方法*/
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
 
/* 串口1初始化 */  
void usart1_init(u32 bound)
{
	usart1_gpio_init();
	usart1_usart_init(bound);
	usart1_nvic_init();
}

/* USART1 GPIO初始化函数 */
void usart1_gpio_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//使能GPIOA时钟
	
	//USART1_TX   GPIOA.9
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.9
   
  //USART1_RX	  GPIOA.10初始化
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.10  
}

/* USART1 USART初始化函数 */
void usart1_usart_init(u32 bound)
{
	USART_InitTypeDef USART_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);	//使能USART1时钟

  //USART 初始化设置
	USART_InitStructure.USART_BaudRate = bound;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

  USART_Init(USART1, &USART_InitStructure); //初始化串口1
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启串口接受中断
  USART_Cmd(USART1, ENABLE);                    //使能串口1 
}

/* USART1 NVIC初始化函数 */
void usart1_nvic_init(void)
{
 	NVIC_InitTypeDef NVIC_InitStructure;

  //Usart1 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x03 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
}

/* 串口1中断服务程序 */
void USART1_IRQHandler(void)                	//串口1中断服务程序
{
	uint16_t Res;
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
	{
		Res =USART_ReceiveData(USART1);	//读取接收到的数据
		USART_SendData(USART1,Res);
  } 
} 

/* WiFi初始化 */  
void wifi_init(void)
{
    wifi_gpio_init();
    wifi_nvic_init();
    wifi_uart_init();
}

/* WiFi GPIO初始化函数 */
void wifi_gpio_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	/********************************************************
	* Configure USART3 use for communication with zigbee
	* [PB10]  --->  TX    [PB11]  --->  RX
	*******************************************************/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	//使能GPIOB时钟

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

/* WiFi USART初始化函数 */
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

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);	//使能USART3时钟

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

/* WiFi NVIC初始化函数 */
void wifi_nvic_init(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;//通道设置为串口3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3; //中断占先等级1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2; //中断响应优先级10
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //打开中断
	NVIC_Init(&NVIC_InitStructure);
}

u8 WIFI_msg[5];		//WiFi接受到的数据
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
    if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET) //判断发生接收中断
    {
        USART_ClearITPendingBit(USART3,USART_IT_RXNE);  //清除中断标志
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
