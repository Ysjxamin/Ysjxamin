#include "stm32f10x.h"  
#include "delay.h"
#include "timer.h"
#include "oled.h"
#include "usart.h"
#include "syn6288.h"
#include "IREva.h"  
#include "tb6612.h"
#include "usart2.h"
#include "usart3.h"
#include "rc522.h"
#include "remote.h"
unsigned char data1[16] = {0x12,0x34,0x56,0x78,0xED,0xCB,0xA9,0x87,0x12,0x34,0x56,0x78,0x01,0xFE,0x01,0xFE};
//M1卡的某一块写为如下格式，则该块为钱包，可接收扣款和充值命令
//4字节金额（低字节在前）＋4字节金额取反＋4字节金额＋1字节块地址＋1字节块地址取反＋1字节块地址＋1字节块地址取反 
unsigned char data2[4]  = {0,0,0,0x01};
unsigned char DefaultKey[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}; 
unsigned char g_ucTempbuf[20];
int status,i;
unsigned int temp;
char ch;
unsigned char ym_flag=0;
unsigned char jr_flag=0;
extern u8 Remote;
int main(void)  
{
	Remote_Init();  
int n1,n2=0;
int number=0;
	char *str="hello world";
	u8 hsjc_flag=1;
	//char ch;
	//u16 led0pwmval=0;
	//u8 dir=1;	
	//延时函数初始化 	 
	delay_init();
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级 
	//USART2初始化
  USART2_Init(9600);
	//串口初始化为115200
	USART_Config();
	LED_Init();
	OLED_Init();	
 OLED_ShowCar();
	//TIM3_PWM_Init(899,0);	 //不分频。PWM频率=72000000/900=80Khz
	/* ??????? */
	IREva_GPIO_Config();
	//串口3初始化（SYN6288)
	USART2_Init(9600);
	TB6612_PWM_Init(3600, 1);//PWM频率初始化20KHz
	TB6612_GPIO_Config();    //电机驱动IO配置
	TB6612_PWM_Out(900, 900);	//30%PWM
  //Car_Go();
	GPIO_ResetBits(GPIOC,GPIO_Pin_13);						 //PC.13 输出高
	//RC522 NFC
	RC522_Init();//初始化
	PcdReset();
 	PcdAntennaOff(); 
	delay_ms(10);
 	PcdAntennaOn();
	delay_ms(10);
	TIM2_Config(1000-1,7200-1);	
  TIM4_Config(1000-1,7200-1); 
	while(1) 
	{	

/*		
			ch=getchar();
		
        switch(ch)
        {
          case '1':
            printf("Go Ahead!");
					Car_Go();
            GPIO_ResetBits(GPIOC,GPIO_Pin_13);
            break;
          case '2':
            printf("Go Back!");
					Car_Back();
            GPIO_SetBits(GPIOC,GPIO_Pin_13);
            break;
          case '3':
            printf("Go Left!");
					Car_Left();
           GPIO_ResetBits(GPIOC,GPIO_Pin_13);
            break;
          case '4':
            printf("Go Right!");
           Car_Right();
            break;
          case '5':
            printf("Car Stop!");
					Car_Stop();

            break;
          case '6':
            printf("Close Light!");

            break;
          case '0':
            printf("Stop!");
   
            break;
          case 'a':
              
            break;
          case 'b':
              
            break;
          case 'c':
              
            break;
          case 'd':
            
            break;
          case 'e':
           
            break;     
          default:
            
            break;					
        }
				*/
		
		status = PcdRequest(PICC_REQALL, g_ucTempbuf);//寻卡
         if (status != MI_OK)//MI_OK==0;
         {    
		     PcdReset();
		     PcdAntennaOff(); 
		     PcdAntennaOn(); 
			 continue;
         }		     
		// printf("卡的类型:");
	    for(i=0;i<2;i++)
		{
			temp=g_ucTempbuf[i];
			//printf("%X",temp);
			
		}	
		printf("  ");
    status = PcdAnticoll(g_ucTempbuf);//防冲撞
    if(status != MI_OK)
    {   
			continue;    
		}
		   
		////////以下为超级终端打印出的内容////////////////////////
	
		//printf("卡序列号：");	//超级终端显示,
		printf("I");
		for(i=0;i<4;i++)
		{
			temp=g_ucTempbuf[i];	
			printf("%X",temp);			
		}
		printf("D");
    printf("\r\n");
		//杨铭
		if(g_ucTempbuf[0]==0x51&&g_ucTempbuf[1]==0x09&&g_ucTempbuf[2]==0x2b&&g_ucTempbuf[3]==0x7b)
		{
		GPIO_ResetBits(GPIOC,GPIO_Pin_13);
			OLED_ShowJr();
			printf("识别卡片成功！");
			if(jr_flag==0)
			{     number++;  n1=number; }
			jr_flag=1;
			ch='a';
		  USART_SendData(USART2,ch);
			OLED_ShowNum(16*6,6,n1,1,16);
			//SYN_FrameInfo(2, "[v7][m1][t5]俊荣信息录入成功");
			//SYN_FrameInfo(2, "[v9][m5][t9]俊荣太逊了");
			printf("B%dH",n1);
		printf("I");
		for(i=0;i<4;i++)
		{
			temp=g_ucTempbuf[i];	
			printf("%X",temp);			
		}
		printf("D");
		}
		//杨铭
		else if(g_ucTempbuf[0]==0x5c&&g_ucTempbuf[1]==0x88&&g_ucTempbuf[2]==0x27&&g_ucTempbuf[3]==0x1c)
		{	
		OLED_ShowYangM();
			printf("识别卡片成功！");
			if(ym_flag==0)
			{   
				number++;  n2=number;
			}
			ch='b';
		  USART_SendData(USART2,ch);
			ym_flag=1;
			OLED_ShowNum(16*6,6,n2,1,16);
			
			
			//SYN_FrameInfo(2, "[v7][m1][t5]杨铭信息录入成功");
			//SYN_FrameInfo(2, "[v7][m1][t5]杨铭说俊荣太逊了");
			printf("B%dH",n2);
					printf("I");
		for(i=0;i<4;i++)
		{
			temp=g_ucTempbuf[i];	
			printf("%X",temp);			
		}
		printf("D");
		}
		else if(g_ucTempbuf[0]==0x7C&&g_ucTempbuf[1]==0xBD&&g_ucTempbuf[2]==0xA3&&g_ucTempbuf[3]==0x08)
		{	
			printf("识别卡片成功！");
			GPIO_ResetBits(GPIOC,GPIO_Pin_13);
		//	LED1=1;	
		}
		else
		{
					printf("I");
		for(i=0;i<4;i++)
		{
			temp=g_ucTempbuf[i];	
			printf("%X",temp);			
		}
		printf("D");
		}
}
}