#ifndef _DCMOTOR_H_
#define _DCMOTOR_H_	 

#define DCMOTOR_DEAD_VAL		400
#define DCMOTOR_MAX_VAL			900

#define LF_MOTOR_ON 				GPIO_SetBits(GPIOE, GPIO_Pin_12)
#define LF_MOTOR_OFF 				GPIO_ResetBits(GPIOE, GPIO_Pin_12)
#define LR_MOTOR_ON 				GPIO_SetBits(GPIOE, GPIO_Pin_10)
#define LR_MOTOR_OFF 				GPIO_ResetBits(GPIOE, GPIO_Pin_10)
#define RF_MOTOR_ON 				GPIO_SetBits(GPIOD, GPIO_Pin_14)
#define RF_MOTOR_OFF 				GPIO_ResetBits(GPIOD, GPIO_Pin_14)
#define RR_MOTOR_ON 				GPIO_SetBits(GPIOD, GPIO_Pin_15)
#define RR_MOTOR_OFF 				GPIO_ResetBits(GPIOD, GPIO_Pin_15)

void DCMotor_init(u16 arr,u16 psc);
void LeftMotor_io_init(void);
void RightMotor_io_init(void);
void TIM1_PWM_Init(u16 arr,u16 psc);
void TIM3_PWM_Init(u16 arr,u16 psc);

void go_forward(u16 parameter);
void back_off(u16 parameter);
void turn_left(u16 parameter);
void turn_right(u16 parameter);
void brake(void);

#endif
