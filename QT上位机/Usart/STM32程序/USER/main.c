#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "beep.h"
#include "ds18b20.h"
/************************************************
 ALIENTEK精英STM32开发板实验4
 串口 实验   
 技术支持：www.openedv.com
 淘宝店铺：http://eboard.taobao.com 
 关注微信公众平台微信号："正点原子"，免费获取STM32资料。
 广州市星翼电子科技有限公司  
 作者：正点原子 @ALIENTEK
************************************************/
 int main(void)
 {		
	 	//u8 t=0;			    
	short temperature;  
	 short temp;
 	u16 t;  
	u16 len;	
	u16 times=0;
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(9600);	 //串口初始化为115200
 	LED_Init();			     //LED端口初始化
	KEY_Init();          //初始化与按键连接的硬件接口
	 BEEP_Init(); //初始化蜂鸣器端口
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

