#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "beep.h"
#include "ds18b20.h"
/************************************************
 ALIENTEK��ӢSTM32������ʵ��4
 ���� ʵ��   
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com 
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾  
 ���ߣ�����ԭ�� @ALIENTEK
************************************************/
 int main(void)
 {		
	 	//u8 t=0;			    
	short temperature;  
	 short temp;
 	u16 t;  
	u16 len;	
	u16 times=0;
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(9600);	 //���ڳ�ʼ��Ϊ115200
 	LED_Init();			     //LED�˿ڳ�ʼ��
	KEY_Init();          //��ʼ���밴�����ӵ�Ӳ���ӿ�
	 BEEP_Init(); //��ʼ���������˿�
	 //printf("wdnmd");
while(DS18B20_Init())
{
	printf("DS18B20 ERROR!!!");
	delay_ms(200);
}
 
 	while(1)
	{
		temperature=DS18B20_Get_Temp();
		temp=temperature/10;
		
		if(USART_RX_STA&0x8000)
		{					   		
			if(USART_RX_BUF[0] == 0x00)
			{
			LED0=!LED0;
			}
			if(USART_RX_BUF[0] == 0x01)
			{
			LED1=!LED1;
			}
			if(USART_RX_BUF[0] == 0x02)
			{
				BEEP = ~BEEP;
			}		
			USART_RX_STA=0;
		}else
		{
			times++;
			if(times%300==0)printf("temperature=%d",temp);  
			delay_ms(10);   
		}
	}		
 }

