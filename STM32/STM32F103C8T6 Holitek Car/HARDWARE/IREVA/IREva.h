//IREva.h红外避障.h函数
#ifndef __IREVA_H
#define	__IREVA_H


#include "stm32f10x.h"

//  引脚定义
#define    IREva_GPIO_CLK     RCC_APB2Periph_GPIOB
#define    IREva_GPIO_PORT    GPIOB			   
#define    IREva_GPIO_PIN1			GPIO_Pin_12

#define    IREva_GPIO_CLK     RCC_APB2Periph_GPIOB
#define    IREva_GPIO_PORT    GPIOB			   
#define    IREva_GPIO_PIN2			GPIO_Pin_13

#define    IREva_GPIO_CLK     RCC_APB2Periph_GPIOB
#define    IREva_GPIO_PORT    GPIOB			   
#define    IREva_GPIO_PIN3			GPIO_Pin_14
//IREva_GPIO_PORTC GPIOC
#define    IREva_GPIO_CLKC     RCC_APB2Periph_GPIOC
#define    IREva_GPIO_PORTC    GPIOC			   
#define    IREva_GPIO_PIN4			GPIO_Pin_15

 /** 按键按下标置宏
	*  按键按下为高电平，设置 KEY_ON=1， KEY_OFF=0
	*  若按键按下为低电平，把宏设置成KEY_ON=0 ，KEY_OFF=1 即可
	*/
#define IREva_HI	1
#define IREva_LO	0

void IREva_GPIO_Config(void);
uint8_t IREva_Scan(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);


#endif
