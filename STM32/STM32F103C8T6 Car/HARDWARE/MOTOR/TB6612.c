#include "tb6612.h"
/*
********************************************************************************************************
�ļ�����TB6612.c
��  �ܣ����õ������
��  ע���������pwm,�õ���timer3��ch3��ch4���� PB0-PB1���ӵ��������ʹ�ܶ�PWMA����������PWMB���ҵ���� 
				
��  ����https://shop60670850.taobao.com
��  �ߣ�lilianhe
��  ��: 2017-2-6
*********************************************************************************************************
*/



//***************************PWMƵ�ʼ�ռ�ձȳ�ʼ��***************************//
//=====��ʼ��PWM 20KHZ ��Ƶ���Է�ֹ�����Ƶʱ�ļ����
// ARR= 3599 ʱƵ��Ϊ20Khz
//PB0����PWMA--left motor��PB1����PWMB--right motor��STBYֱ������
//arr���Զ���װ�Ĵ�����psc��Ƶϵ��
//PWM��Ƶ�� = 72MHz/ARR/PCS ����  20K = 72M/3600/1 =  20K
void TB6612_PWM_Init(u32 arr, int psc)
{
	TIM_OCInitTypeDef TIM_OCInitSructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	GPIO_InitTypeDef    GPIO_InitStructure;
	
	//����pwm����˿�
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0| GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		         // �����������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	//��ʼ����ʱ��
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
	TIM_TimeBaseStructure.TIM_Period = arr-1;                   //�Զ�����װ�ؼĴ������ڵ�ֵ壨����ֵ�)
	TIM_TimeBaseStructure.TIM_Prescaler = psc-1;                  //ʱ�ӷ�Ƶϵ��
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;     //���ⲿʱ�ӽ��в�����ʱ�ӷ�Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //���ϼ���
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);              //������ʼ��

	TIM_ClearFlag(TIM3, TIM_FLAG_Update);
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
	//����ͨ��3 pwm����
	TIM_OCInitSructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitSructure.TIM_OutputState= TIM_OutputState_Enable;
	TIM_OCInitSructure.TIM_Pulse = 0;                            //ռ�ձ�=
	TIM_OCInitSructure.TIM_OCPolarity = TIM_OCPolarity_High;     //����ʱ������ֵС��CCR1_ValʱΪ�ߵ�ƽ
	TIM_OC3Init(TIM3, &TIM_OCInitSructure);                      //������ʼ��
	TIM_OC3PolarityConfig(TIM3, TIM_OCPreload_Enable);           //��ʼ���pwm

	//����ͨ��4 pwm����
	TIM_OCInitSructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitSructure.TIM_OutputState= TIM_OutputState_Enable;
	TIM_OCInitSructure.TIM_Pulse = 0;                            //ռ�ձ�= 
	TIM_OCInitSructure.TIM_OCPolarity = TIM_OCPolarity_High;     //����ʱ������ֵС��CCR1_ValʱΪ�ߵ�ƽ
	TIM_OC4Init(TIM3, &TIM_OCInitSructure);                      //������ʼ��
	TIM_OC4PolarityConfig(TIM3, TIM_OCPreload_Enable);           //��ʼ���pwm

	TIM_ARRPreloadConfig(TIM3, ENABLE);                          //�����Զ���װ
	TIM_Cmd(TIM3, ENABLE);                                       //������ʱ	
}

//***************************ռ�ձȵ���***************************//
//ռ�ձ� = TIMx_CCRx / TIMx_ARR
//moto_r�����ֵ����moto_l�����ֵ��.   ��ֵ 0-3600
void TB6612_PWM_Out(u16 moto_l, u16 moto_r)
{

	TIM_OCInitTypeDef TIM_OCInitSructure;
	TIM_OCInitSructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitSructure.TIM_OutputState= TIM_OutputState_Enable;
	//CH3 ����
	TIM_OCInitSructure.TIM_Pulse = moto_l;               //ռ�ձ�= ccr/3600
	TIM_OC3Init(TIM3, &TIM_OCInitSructure);              //������ʼ��
	TIM_OC3PolarityConfig(TIM3, TIM_OCPreload_Enable);   //��ʼ���pwm
	
	//CH4 �ҵ��
	TIM_OCInitSructure.TIM_Pulse = moto_r;               //ռ�ձ�= ccr /3600
	TIM_OC4Init(TIM3, &TIM_OCInitSructure);              //������ʼ��
	TIM_OC4PolarityConfig(TIM3, TIM_OCPreload_Enable);   //��ʼ���pwm
	
	TIM_ARRPreloadConfig(TIM3, ENABLE);                  //�����Զ���װ
	 
}	


void TB6612_GPIO_Config(void)
{		
		/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
		GPIO_InitTypeDef GPIO_InitStructure;
		RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE);                                	  /*����GPIO������ʱ��*/																   
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;	    /*ѡ��Ҫ���Ƶ�GPIO����*/	
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;                                          /*��������ģʽΪͨ���������*/   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                                         /*������������Ϊ50MHz */ 
		GPIO_Init(GPIOB, &GPIO_InitStructure);                                                 /*���ÿ⺯������ʼ��GPIO*/	
}

//���µ�������ÿ�������˶�״̬��������Կ����޸�����Ĳ���
//��������ǰ����AIN1��0����AIN2��1��.�������ת�ˣ��͸ĳ�AIN1��1����AIN2��0��

void Motor_Left(u8 state)
{
	if(state == GO)      //����ǰ��
	{
	  AIN1(0);
		AIN2(1);
	}
	if(state == BACK)   //��������
	{
		AIN1(1);
		AIN2(0);
	}
	if(state == STOP)  //ͣת
	{
	  AIN1(1);
		AIN2(1);
	}
}

void Motor_Right(u8 state)
{
	if(state == GO)      //�ҵ��ǰ��
	{
	  BIN1(0);
		BIN2(1);
	}
	if(state == BACK)   //�ҵ������
	{
		BIN1(1);
		BIN2(0);
	}
	if(state == STOP)  //ͣת
	{
	  BIN1(1);
		BIN2(1);
	}
}

//���¶�����С��������˶�����ת�俿���ҵ������ʵ�֡�

void Car_Go(void)
{
	//С��ǰ��
	//����ǰ��      �ҵ��ǰ��
	Motor_Left(GO);   Motor_Right(GO);
}

void Car_Back(void)
{
	//С������
	//��������     �ҵ������
	Motor_Left(BACK);   Motor_Right(BACK);
	
}

void Car_Right(void)
{
	//С����תȦ
	//����ǰ��      �ҵ������
	Motor_Left(GO);   Motor_Right(BACK);
}

void Car_Left(void)
{
	//С����תȦ
	//��������      �ҵ��ǰ��
	Motor_Left(BACK);   Motor_Right(GO);
}

void Car_Stop(void)
{
	//С��ͣ��
	//����ֹͣ      �ҵ��ֹͣ
	Motor_Left(STOP);   Motor_Right(STOP);
}




