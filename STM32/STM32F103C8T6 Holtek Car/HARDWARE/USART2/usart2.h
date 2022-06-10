#ifndef __USART2_H
#define __USART2_H
#include "stdio.h"	
#include "sys.h" 
#include "stm32f10x.h"



void USART2_Init(u32 Baud);
void Usart2_SendString( USART_TypeDef * pUSARTx, char *str);
void Usart2_SendByte( USART_TypeDef * pUSARTx, uint8_t ch);

void USART2_SendData(u8 data);
void USART2_SendString(u8 *DAT, u8 len);
#endif