#ifndef __TB6612_H
#define __TB6612_H

#include "stm32f10x.h"
#include "timer.h"

//Ӳ������˵��

//�������pwm,�õ���timer3��ch3��ch4���� PB0-PB1���ӵ��������ʹ�ܶ�PWMA����������PWMB���ҵ���� 
//����������ƣ�INA1��INA2���� һ·��������
//	  				 INB1��INB2���� һ·���ҵ����
//             PWMA ---- PB0
//             PWMB ---- PB1
//             INA2 ---- PB12
//             INA1 ---- PB13
//             INB1 ---- PB14
//             INB2 ---- PB15


#define GO    0//������״̬ ǰ��
#define BACK  1//����
#define STOP  2//ͣ��

/* ���κ꣬��������������һ��ʹ�� */
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
