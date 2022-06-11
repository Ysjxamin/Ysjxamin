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
//M1����ĳһ��дΪ���¸�ʽ����ÿ�ΪǮ�����ɽ��տۿ�ͳ�ֵ����
//4�ֽڽ����ֽ���ǰ����4�ֽڽ��ȡ����4�ֽڽ�1�ֽڿ��ַ��1�ֽڿ��ַȡ����1�ֽڿ��ַ��1�ֽڿ��ַȡ�� 
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
	//��ʱ������ʼ�� 	 
	delay_init();
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ� 
	//USART2��ʼ��
  USART2_Init(9600);
	//���ڳ�ʼ��Ϊ115200
	USART_Config();
	LED_Init();
	OLED_Init();	
 OLED_ShowCar();
	//TIM3_PWM_Init(899,0);	 //����Ƶ��PWMƵ��=72000000/900=80Khz
	/* ??????? */
	IREva_GPIO_Config();
	//����3��ʼ����SYN6288)
	USART2_Init(9600);
	TB6612_PWM_Init(3600, 1);//PWMƵ�ʳ�ʼ��20KHz
	TB6612_GPIO_Config();    //�������IO����
	TB6612_PWM_Out(900, 900);	//30%PWM
  //Car_Go();
	GPIO_ResetBits(GPIOC,GPIO_Pin_13);						 //PC.13 �����
	//RC522 NFC
	RC522_Init();//��ʼ��
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
		
		status = PcdRequest(PICC_REQALL, g_ucTempbuf);//Ѱ��
         if (status != MI_OK)//MI_OK==0;
         {    
		     PcdReset();
		     PcdAntennaOff(); 
		     PcdAntennaOn(); 
			 continue;
         }		     
		// printf("��������:");
	    for(i=0;i<2;i++)
		{
			temp=g_ucTempbuf[i];
			//printf("%X",temp);
			
		}	
		printf("  ");
    status = PcdAnticoll(g_ucTempbuf);//����ײ
    if(status != MI_OK)
    {   
			continue;    
		}
		   
		////////����Ϊ�����ն˴�ӡ��������////////////////////////
	
		//printf("�����кţ�");	//�����ն���ʾ,
		printf("I");
		for(i=0;i<4;i++)
		{
			temp=g_ucTempbuf[i];	
			printf("%X",temp);			
		}
		printf("D");
    printf("\r\n");
		//����
		if(g_ucTempbuf[0]==0x51&&g_ucTempbuf[1]==0x09&&g_ucTempbuf[2]==0x2b&&g_ucTempbuf[3]==0x7b)
		{
		GPIO_ResetBits(GPIOC,GPIO_Pin_13);
			OLED_ShowJr();
			printf("ʶ��Ƭ�ɹ���");
			if(jr_flag==0)
			{     number++;  n1=number; }
			jr_flag=1;
			ch='a';
		  USART_SendData(USART2,ch);
			OLED_ShowNum(16*6,6,n1,1,16);
			//SYN_FrameInfo(2, "[v7][m1][t5]������Ϣ¼��ɹ�");
			//SYN_FrameInfo(2, "[v9][m5][t9]����̫ѷ��");
			printf("B%dH",n1);
		printf("I");
		for(i=0;i<4;i++)
		{
			temp=g_ucTempbuf[i];	
			printf("%X",temp);			
		}
		printf("D");
		}
		//����
		else if(g_ucTempbuf[0]==0x5c&&g_ucTempbuf[1]==0x88&&g_ucTempbuf[2]==0x27&&g_ucTempbuf[3]==0x1c)
		{	
		OLED_ShowYangM();
			printf("ʶ��Ƭ�ɹ���");
			if(ym_flag==0)
			{   
				number++;  n2=number;
			}
			ch='b';
		  USART_SendData(USART2,ch);
			ym_flag=1;
			OLED_ShowNum(16*6,6,n2,1,16);
			
			
			//SYN_FrameInfo(2, "[v7][m1][t5]������Ϣ¼��ɹ�");
			//SYN_FrameInfo(2, "[v7][m1][t5]����˵����̫ѷ��");
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
			printf("ʶ��Ƭ�ɹ���");
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