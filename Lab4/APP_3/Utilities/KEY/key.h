#ifndef _KEY_H_
#define _KEY_H_	 

/*! 枚举KEY编号 */
typedef enum
{
  KEY1 = 1,
  KEY2,
  KEY3,
  KEY4,
  KEY5,
}KEY_e;

/*! 枚举KEY按下状态 */
typedef enum KEY_status
{
  KEY_OFF =   0,            //未按下(对应低电平)
  KEY_ON  =   1             //已按下(对应高电平)
}KEY_status; 

void key_init(void);
void key_gpio_init(void);
u8 key(KEY_e keyn);
		 				    
#endif
