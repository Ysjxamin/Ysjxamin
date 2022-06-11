#ifndef __TB6612_H
#define __TB6612_H

#include "stm32f10x.h"
#include "timer.h"

//硬件链接说明

//电机控制pwm,用到了timer3的ch3和ch4，即 PB0-PB1连接电机驱动的使能端PWMA（左电机）和PWMB（右电机） 
//电机正反控制：INA1和INA2控制 一路（左电机）
//	  				 INB1和INB2控制 一路（右电机）
//             PWMA ---- PB0
//             PWMB ---- PB1
//             INA2 ---- PB12
//             INA1 ---- PB13
//             INB1 ---- PB14
//             INB2 ---- PB15


#define GO    0//定义电机状态 前进
#define BACK  1//后退
#define STOP  2//停车

/* 带参宏，可以像内联函数一样使用 */
#define AIN2(a)	if (a)	\
					GPIO_SetBits(GPIOB,GPIO_Pin_12);\
					else		\
					GPIO_ResetBits(GPIOB,GPIO_Pin_12)

#define AIN1(a)	if (a)	\
					GPIO_SetBits(GPIOB,GPIO_Pin_13);\
					else		\
					GPIO_ResetBits(GPIOB,GPIO_Pin_13)
					
#define BIN1(a)	if (a)	\
					GPIO_SetBits(GPIOB,GPIO_Pin_14);\
					else		\
					GPIO_ResetBits(GPIOB,GPIO_Pin_14)
					
#define BIN2(a)	if (a)	\
					GPIO_SetBits(GPIOB,GPIO_Pin_15);\
					else		\
					GPIO_ResetBits(GPIOB,GPIO_Pin_15)

void TB6612_PWM_Init(u32 arr, int psc);
void TB6612_PWM_Out(u16 moto_l, u16 moto_r);
void TB6612_GPIO_Config(void);
void Motor_Left(u8 state);
void Motor_Right(u8 state);
void Car_Go(void);					
void Car_Back(void);						
void Car_Left(void);
void Car_Right(void);
void Car_Stop(void);		
#endif
