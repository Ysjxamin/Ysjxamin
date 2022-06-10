#include "tb6612.h"
/*
********************************************************************************************************
文件名：TB6612.c
功  能：配置电机驱动
备  注：电机控制pwm,用到了timer3的ch3和ch4，即 PB0-PB1连接电机驱动的使能端PWMA（左电机）和PWMB（右电机） 
				
淘  宝：https://shop60670850.taobao.com
作  者：lilianhe
日  期: 2017-2-6
*********************************************************************************************************
*/



//***************************PWM频率及占空比初始化***************************//
//=====初始化PWM 20KHZ 高频可以防止电机低频时的尖叫声
// ARR= 3599 时频率为20Khz
//PB0控制PWMA--left motor，PB1控制PWMB--right motor。STBY直接拉高
//arr：自动重装寄存器，psc分频系数
//PWM的频率 = 72MHz/ARR/PCS 例如  20K = 72M/3600/1 =  20K
void TB6612_PWM_Init(u32 arr, int psc)
{
	TIM_OCInitTypeDef TIM_OCInitSructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	GPIO_InitTypeDef    GPIO_InitStructure;
	
	//配置pwm输出端口
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0| GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		         // 复用推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	//初始化定时器
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
	TIM_TimeBaseStructure.TIM_Period = arr-1;                   //自动重新装载寄存器周期的值澹ㄥ计数值澹)
	TIM_TimeBaseStructure.TIM_Prescaler = psc-1;                  //时钟分频系数
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;     //对外部时钟进行采样的时钟分频
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //向上计数
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);              //参数初始化

	TIM_ClearFlag(TIM3, TIM_FLAG_Update);
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
	//设置通道3 pwm参数
	TIM_OCInitSructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitSructure.TIM_OutputState= TIM_OutputState_Enable;
	TIM_OCInitSructure.TIM_Pulse = 0;                            //占空比=
	TIM_OCInitSructure.TIM_OCPolarity = TIM_OCPolarity_High;     //当定时器计数值小于CCR1_Val时为高电平
	TIM_OC3Init(TIM3, &TIM_OCInitSructure);                      //参数初始化
	TIM_OC3PolarityConfig(TIM3, TIM_OCPreload_Enable);           //开始输出pwm

	//设置通道4 pwm参数
	TIM_OCInitSructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitSructure.TIM_OutputState= TIM_OutputState_Enable;
	TIM_OCInitSructure.TIM_Pulse = 0;                            //占空比= 
	TIM_OCInitSructure.TIM_OCPolarity = TIM_OCPolarity_High;     //当定时器计数值小于CCR1_Val时为高电平
	TIM_OC4Init(TIM3, &TIM_OCInitSructure);                      //参数初始化
	TIM_OC4PolarityConfig(TIM3, TIM_OCPreload_Enable);           //开始输出pwm

	TIM_ARRPreloadConfig(TIM3, ENABLE);                          //启动自动重装
	TIM_Cmd(TIM3, ENABLE);                                       //启动定时	
}

//***************************占空比调节***************************//
//占空比 = TIMx_CCRx / TIMx_ARR
//moto_r：右轮电机，moto_l：左轮电机.   数值 0-3600
void TB6612_PWM_Out(u16 moto_l, u16 moto_r)
{

	TIM_OCInitTypeDef TIM_OCInitSructure;
	TIM_OCInitSructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitSructure.TIM_OutputState= TIM_OutputState_Enable;
	//CH3 左电机
	TIM_OCInitSructure.TIM_Pulse = moto_l;               //占空比= ccr/3600
	TIM_OC3Init(TIM3, &TIM_OCInitSructure);              //参数初始化
	TIM_OC3PolarityConfig(TIM3, TIM_OCPreload_Enable);   //开始输出pwm
	
	//CH4 右电机
	TIM_OCInitSructure.TIM_Pulse = moto_r;               //占空比= ccr /3600
	TIM_OC4Init(TIM3, &TIM_OCInitSructure);              //参数初始化
	TIM_OC4PolarityConfig(TIM3, TIM_OCPreload_Enable);   //开始输出pwm
	
	TIM_ARRPreloadConfig(TIM3, ENABLE);                  //启动自动重装
	 
}	


void TB6612_GPIO_Config(void)
{		
		/*定义一个GPIO_InitTypeDef类型的结构体*/
		GPIO_InitTypeDef GPIO_InitStructure;
		RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE);                                	  /*开启GPIO的外设时钟*/																   
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;	    /*选择要控制的GPIO引脚*/	
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;                                          /*设置引脚模式为通用推挽输出*/   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                                         /*设置引脚速率为50MHz */ 
		GPIO_Init(GPIOB, &GPIO_InitStructure);                                                 /*调用库函数，初始化GPIO*/	
}

//以下单独定义每个轮子运动状态，如果不对可以修改里面的参数
//比如左轮前进，AIN1（0），AIN2（1）.如果往后转了，就改成AIN1（1），AIN2（0）

void Motor_Left(u8 state)
{
	if(state == GO)      //左电机前进
	{
	  AIN1(0);
		AIN2(1);
	}
	if(state == BACK)   //左电机后退
	{
		AIN1(1);
		AIN2(0);
	}
	if(state == STOP)  //停转
	{
	  AIN1(1);
		AIN2(1);
	}
}

void Motor_Right(u8 state)
{
	if(state == GO)      //右电机前进
	{
	  BIN1(0);
		BIN2(1);
	}
	if(state == BACK)   //右电机后退
	{
		BIN1(1);
		BIN2(0);
	}
	if(state == STOP)  //停转
	{
	  BIN1(1);
		BIN2(1);
	}
}

//以下定义了小车整体的运动方向。转弯靠左右电机差速实现。

void Car_Go(void)
{
	//小车前进
	//左电机前进      右电机前进
	Motor_Left(GO);   Motor_Right(GO);
}

void Car_Back(void)
{
	//小车后退
	//左电机后退     右电机后退
	Motor_Left(BACK);   Motor_Right(BACK);
	
}

void Car_Right(void)
{
	//小车右转圈
	//左电机前进      右电机后退
	Motor_Left(GO);   Motor_Right(BACK);
}

void Car_Left(void)
{
	//小车左转圈
	//左电机后退      右电机前进
	Motor_Left(BACK);   Motor_Right(GO);
}

void Car_Stop(void)
{
	//小车停车
	//左电机停止      右电机停止
	Motor_Left(STOP);   Motor_Right(STOP);
}




