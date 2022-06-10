#ifndef __USART3_H
#define __USART3_H
#include "stdio.h"	
#include "sys.h" 

#define USART3_REC_LEN  			200  	//�����������ֽ��� 200
#define EN_USART3_RX 			1		//ʹ�ܣ�1��/��ֹ��0������1����
	  	
extern u8  USART3_RX_BUF[USART3_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u16 USART3_RX_STA;         		//����״̬���	
//����봮���жϽ��գ��벻Ҫע�����º궨��
void USART3_SendString(u8 *DAT,u8 len);
void USART3_SendData(u8 data);

void USART3_Init(u32 Baud);
void USART3_Config(void);
void UART_SendStr(USART_TypeDef* USARTx, char *str);

void Usart3_SendByte( USART_TypeDef * pUSARTx, uint8_t ch);
void Usart3_SendString( USART_TypeDef * pUSARTx, char *str);
void UART_SendStr(USART_TypeDef* USARTx, char *str);

#endif