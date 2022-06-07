#include "timer.h"
#include "led.h"
#include "usart.h"
#include "rc522.h"
#include "stdio.h"
extern unsigned char data1[16];
//M1卡的某一块写为如下格式，则该块为钱包，可接收扣款和充值命令
//4字节金额（低字节在前）＋4字节金额取反＋4字节金额＋1字节块地址＋1字节块地址取反＋1字节块地址＋1字节块地址取反 
extern unsigned char data2[4] ;
extern unsigned char DefaultKey[6] ; 


extern unsigned char g_ucTempbuf[20];
extern int status,i;
extern unsigned int temp;
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTE精英STM32开发板
//定时器 驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/4
//版本：V1.1
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
//********************************************************************************
//V1.1 20120904
//1,增加TIM3_PWM_Init函数。
//2,增加LED0_PWM_VAL宏定义，控制TIM3_CH2脉宽									  
//////////////////////////////////////////////////////////////////////////////////  
   	  
//通用定时器3中断初始化
//这里时钟选择为APB1的2倍，而APB1为36M
//arr：自动重装值。
//psc：时钟预分频数
//这里使用的是定时器3!
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
		//printf("中断");
	
			
				
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
		printf("中断");
		TIM_ClearITPendingBit(TIM4,TIM_IT_Update);//?????????
	}
	
}
