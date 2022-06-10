#ifndef __USART_H
#define	__USART_H

#include "stm32f10x.h"
#include <stdio.h>


void USART_Config(void);
void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch);
#endif /* __USART_H */
