//IREva.h�������.h����
#ifndef __IREVA_H
#define	__IREVA_H


#include "stm32f10x.h"

//  ���Ŷ���
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

 /** �������±��ú�
	*  ��������Ϊ�ߵ�ƽ������ KEY_ON=1�� KEY_OFF=0
	*  ����������Ϊ�͵�ƽ���Ѻ����ó�KEY_ON=0 ��KEY_OFF=1 ����
	*/
#define IREva_HI	1
#define IREva_LO	0

void IREva_GPIO_Config(void);
uint8_t IREva_Scan(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);


#endif
