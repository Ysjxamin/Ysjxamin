#include "pwm.h"
#include "timer.h"
#include "stm32f10x_tim.h"
void Set_motor_L(int PWM)
{
	int pwm_ = PWM_xianfu(PWM);
	if(pwm_>0)
	{
		TIM_SetCompare2(TIM3,100);
	}
	else
	{
		
	}
	
}

void Set_motor_R(int PWM)
{
	int pwm_ = PWM_xianfu(PWM);
	if(pwm_>0)
	{
    TIM_SetCompare4(TIM3,100);
	}
	else
	{

	}

}

int PWM_xianfu(int PWM)//最大设置为9999
{
	if(PWM<-899) PWM=-899;	
	if(PWM>899)  PWM=899;	
	return PWM;
}
int myabs(int a)
{ 		   
	  int temp;
		if(a<0)  temp=-a;  
	  else temp=a;
	  return temp;
}
