#include "timer.h"
#include "led.h"
#include "usart.h"
#include "rc522.h"
#include "stdio.h"
extern unsigned char data1[16];
//M1����ĳһ��дΪ���¸�ʽ����ÿ�ΪǮ�����ɽ��տۿ�ͳ�ֵ����
//4�ֽڽ����ֽ���ǰ����4�ֽڽ��ȡ����4�ֽڽ�1�ֽڿ��ַ��1�ֽڿ��ַȡ����1�ֽڿ��ַ��1�ֽڿ��ַȡ�� 
extern unsigned char data2[4] ;
extern unsigned char DefaultKey[6] ; 


extern unsigned char g_ucTempbuf[20];
extern int status,i;
extern unsigned int temp;
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTE��ӢSTM32������
//��ʱ�� ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/4
//�汾��V1.1
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//********************************************************************************
//V1.1 20120904
//1,����TIM3_PWM_Init������
//2,����LED0_PWM_VAL�궨�壬����TIM3_CH2����									  
//////////////////////////////////////////////////////////////////////////////////  
   	  
//ͨ�ö�ʱ��3�жϳ�ʼ��
//����ʱ��ѡ��ΪAPB1��2������APB1Ϊ36M
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//����ʹ�õ��Ƕ�ʱ��3!
extern char ch;

//?????????1ms,CLK_INT=72,????? = 1000
/**********************************************************
** ???: TIM2_Int_Init
** ????:  ???????
** ????: ?
** ????: ?
** ??:????=(????+1)*(???+1) /TIM5??(72MHz),??(s)
   ??????t=(7200*10000)/72000000s=1s
***********************************************************/
void TIM2_Config(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef    TIM_TimeBaseStructure;
	NVIC_InitTypeDef           NVIC_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //??TIM2??
	//???????
  TIM_ClearITPendingBit(TIM2,TIM_IT_Update);//TIM_ClearFlag(TIM2,TIM_FLAG_Update);//??????
	TIM_TimeBaseStructure.TIM_Period = arr; //???????????????????????????	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //??????TIMx???????????
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //??????:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM??????
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);  //??????????TIMx???????
	TIM_ITConfig(TIM2,TIM_IT_Update, ENABLE);     //?????TIM2??,??????
 
	//?????NVIC??
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  //TIM2??
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //?????0?
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //????3?
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ?????
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_Cmd(TIM2, ENABLE);     //?????2
}

/**********************************************************
** ???: TIM2_IRQHandler
** ????: ???2?????????
** ????: ?
** ????: ?
***********************************************************/
void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
	{
		//printf("�ж�");
	
			
				
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);//?????????
	}
}
 
/**********************************************************
** ???: TIM4_Int_Init
** ????:  ???????
** ????: ?
** ????: ?
** ??:????=(????+1)*(???+1) /TIM6??(72MHz),??(s)
   ??????t=(7200*10000)/72000000s=1s
***********************************************************/
void TIM4_Config(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef    TIM_TimeBaseStructure;
	NVIC_InitTypeDef           NVIC_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); //??TIM4??
	//???????
  TIM_ClearITPendingBit(TIM4,TIM_IT_Update);//TIM_ClearFlag(TIM2,TIM_FLAG_Update);//??????
	TIM_TimeBaseStructure.TIM_Period = arr; //???????????????????????????	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //??????TIMx???????????
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //??????:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM??????
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);  //??????????TIMx???????
	TIM_ITConfig(TIM4,TIM_IT_Update, ENABLE);     //?????TIM4??,??????
 
	//?????NVIC??
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;  //TIM4??
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //?????0?
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //????3?
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ?????
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_Cmd(TIM4, ENABLE);     //?????4
}
 /**********************************************************
** ???: TIM4_IRQHandler
** ????: ???4?????????
** ????: ?
** ????: ?
***********************************************************/
void TIM4_IRQHandler(void)
{
	
		if(TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)
	{
		printf("�ж�");
		TIM_ClearITPendingBit(TIM4,TIM_IT_Update);//?????????
	}
	
}
