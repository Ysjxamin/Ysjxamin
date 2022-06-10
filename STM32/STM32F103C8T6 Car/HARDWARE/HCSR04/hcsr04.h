#ifndef __HCSR04_H
#define __HCSR04_H
#include "stm32f10x.h"
//???¨´?¡§?????????¡§??
#define HCSR04_PORT     GPIOA
#define HCSR04_CLK      RCC_APB2Periph_GPIOA
#define HCSR04_TRIG     GPIO_Pin_0
#define HCSR04_ECHO     GPIO_Pin_1

#define TRIG_Send  PAout(0)
#define ECHO_Reci  PAin(1)

void hcsr04_NVIC();
void Hcsr04Init();
static void OpenTimerForHc();
static void CloseTimerForHc();
void TIM4_IRQHandler(void);
u32 GetEchoTimer(void);
float Hcsr04GetLength(void);


#endif