#include "usart2.h"

void USART2_Init(u32 Baud)
{
	GPIO_InitTypeDef   GPIO_InitStructure;
	USART_InitTypeDef  USART_InitStructure;
	
RCC_APB2PeriphClockCmd(RCC_APB2ENR_IOPAEN,ENABLE);		// GPIOA桼CC
RCC_APB1PeriphClockCmd(RCC_APB1ENR_USART2EN,ENABLE);    // USART2-RCC

GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 ;  			// GPIOA-PIN_2  USART2-TX
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;         // ????????
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_Init(GPIOA,&GPIO_InitStructure);

GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;				// GPIOA-PIN_3  USART2-RX
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	// ????
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_Init(GPIOA,&GPIO_InitStructure);

USART_InitStructure.USART_BaudRate = Baud;  											// ?????	
USART_InitStructure.USART_Parity = USART_Parity_No;   									// ???
USART_InitStructure.USART_StopBits = USART_StopBits_1;									// ???
USART_InitStructure.USART_WordLength = USART_WordLength_8b; 							// ???
USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;			// ????????
USART_InitStructure.USART_Mode =USART_Mode_Rx | USART_Mode_Tx;							// ????

USART_Init(USART2,&USART_InitStructure);												// ??? USART2
USART_Cmd(USART2,ENABLE);// ?? USART2
}
/*****************  发送字符串 **********************/
void Usart2_SendString( USART_TypeDef * pUSARTx, char *str)
{
	unsigned int k=0;
  do 
  {
      Usart2_SendByte( pUSARTx, *(str + k) );
      k++;
  } while(*(str + k)!='\0');
  
  /* 等待发送完成 */
  while(USART_GetFlagStatus(pUSARTx,USART_FLAG_TC)==RESET)
  {}
}
/*****************  发送一个字符 **********************/
void Usart2_SendByte( USART_TypeDef * pUSARTx, uint8_t ch)
{
	/* 发送一个字节数据到USART */
	USART_SendData(pUSARTx,ch);
		
	/* 等待发送数据寄存器为空 */
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	
}

void USART2_SendData(u8 data)
{
	while((USART2->SR & 0X40) == 0);
	USART2->DR = data;
}

void USART2_SendString(u8 *DAT, u8 len)
{
	u8 i;
	for(i = 0; i < len; i++)
	{
		USART2_SendData(*DAT++);
	}
}