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
//M1¿¨µÄÄ³Ò»¿éÐ´ÎªÈçÏÂ¸ñÊ½£¬Ôò¸Ã¿éÎªÇ®°ü£¬¿É½ÓÊÕ¿Û¿îºÍ³äÖµÃüÁî
//4×Ö½Ú½ð¶î£¨µÍ×Ö½ÚÔÚÇ°£©£«4×Ö½Ú½ð¶îÈ¡·´£«4×Ö½Ú½ð¶î£«1×Ö½Ú¿éµØÖ·£«1×Ö½Ú¿éµØÖ·È¡·´£«1×Ö½Ú¿éµØÖ·£«1×Ö½Ú¿éµØÖ·È¡·´ 
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
	//ÑÓÊ±º¯Êý³õÊ¼»¯ 	 
	delay_init();
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 	 //ÉèÖÃNVICÖÐ¶Ï·Ö×é2:2Î»ÇÀÕ¼ÓÅÏÈ¼¶£¬2Î»ÏìÓ¦ÓÅÏÈ¼¶ 
	//USART2³õÊ¼»¯
  USART2_Init(9600);
	//´®¿Ú³õÊ¼»¯Îª115200
	USART_Config();
	LED_Init();
	OLED_Init();	
 OLED_ShowCar();
	//TIM3_PWM_Init(899,0);	 //²»·ÖÆµ¡£PWMÆµÂÊ=72000000/900=80Khz
	/* ??????? */
	IREva_GPIO_Config();
	//´®¿Ú3³õÊ¼»¯£¨SYN6288)
	USART2_Init(9600);
	TB6612_PWM_Init(3600, 1);//PWMÆµÂÊ³õÊ¼»¯20KHz
	TB6612_GPIO_Config();    //µç»úÇý¶¯IOÅäÖÃ
	TB6612_PWM_Out(900, 900);	//30%PWM
  //Car_Go();
	GPIO_ResetBits(GPIOC,GPIO_Pin_13);						 //PC.13 Êä³ö¸ß
	//RC522 NFC
	RC522_Init();//³õÊ¼»¯
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
		/*
		//ÅÐ¶Ï¿ÚÕÖÊÇ·ñÓÃÍê
			if( IREva_Scan(IREva_GPIO_PORTC,IREva_GPIO_PIN4) == IREva_LO  )
		{
        GPIO_SetBits(GPIOC,GPIO_Pin_13);						 //PC.13 Êä³ö¸
			  SYN_FrameInfo(2, "[v7][m1][t5]¿ÚÕÖ²»×ã£¬Çë¼°Ê±²¹³ä");
		} 
		else
		{
       GPIO_ResetBits(GPIOC,GPIO_Pin_13);						 //PC.13 Êä³ö¸ß
		}		
		status = PcdRequest(PICC_REQALL, g_ucTempbuf);//Ñ°¿¨
         if (status != MI_OK)//MI_OK==0;
         {    
		     PcdReset();
		     PcdAntennaOff(); 
		     PcdAntennaOn(); 
			 continue;
         }		     
		// printf("¿¨µÄÀàÐÍ:");
	    for(i=0;i<2;i++)
		{
			temp=g_ucTempbuf[i];
			//printf("%X",temp);
			
		}	
		printf("  ");
    status = PcdAnticoll(g_ucTempbuf);//·À³å×²
    if(status != MI_OK)
    {   
			continue;    
		}
		   
		////////ÒÔÏÂÎª³¬¼¶ÖÕ¶Ë´òÓ¡³öµÄÄÚÈÝ////////////////////////
	
		//printf("¿¨ÐòÁÐºÅ£º");	//³¬¼¶ÖÕ¶ËÏÔÊ¾,
		printf("I");
		for(i=0;i<4;i++)
		{
			temp=g_ucTempbuf[i];	
			printf("%X",temp);			
		}
		printf("D");
    printf("\r\n");
		//¿¡ÈÙ
		if(g_ucTempbuf[0]==0xe3&&g_ucTempbuf[1]==0xc8&&g_ucTempbuf[2]==0xab&&g_ucTempbuf[3]==0x04)
		{
		GPIO_ResetBits(GPIOC,GPIO_Pin_13);
			OLED_ShowJr();
			printf("Ê¶±ð¿¨Æ¬³É¹¦£¡");
			if(jr_flag==0)
			{     number++;  n1=number; }
			jr_flag=1;
			OLED_ShowNum(16*6,6,n1,1,16);
			SYN_FrameInfo(2, "[v7][m1][t5]¿¡ÈÙÐÅÏ¢Â¼Èë³É¹¦");
			//SYN_FrameInfo(2, "[v9][m5][t9]¿¡ÈÙÌ«Ñ·ÁË");
			printf("B%dH",n1);
		printf("I");
		for(i=0;i<4;i++)
		{
			temp=g_ucTempbuf[i];	
			printf("%X",temp);			
		}
		printf("D");
		}
		//ÑîÃú
		else if(g_ucTempbuf[0]==0x5c&&g_ucTempbuf[1]==0x88&&g_ucTempbuf[2]==0x27&&g_ucTempbuf[3]==0x1c)
		{	
		OLED_ShowYangM();
			printf("Ê¶±ð¿¨Æ¬³É¹¦£¡");
			if(ym_flag==0)
			{   
				number++;  n2=number;
			}
			ym_flag=1;
			OLED_ShowNum(16*6,6,n2,1,16);
			
			
			SYN_FrameInfo(2, "[v7][m1][t5]ÑîÃúÐÅÏ¢Â¼Èë³É¹¦");
			//SYN_FrameInfo(2, "[v7][m1][t5]ÑîÃúËµ¿¡ÈÙÌ«Ñ·ÁË");
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
			printf("Ê¶±ð¿¨Æ¬³É¹¦£¡");
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
 

	
   //TIM_SetCompare2(TIM3,195);
		//TIM_SetCompare2(TIM3,0);//Ê±¼äµ½¹Ø±Õ		  
		//ch=getchar();
        
						//Ñ¡Ôñ±³¾°ÒôÀÖ2¡£(0£ºÎÞ±³¾°ÒôÀÖ  1-15£º±³¾°ÒôÀÖ¿ÉÑ¡)
		//m[0~16]:0±³¾°ÒôÀÖÎª¾²Òô£¬16±³¾°ÒôÀÖÒôÁ¿×î´ó
		//v[0~16]:0ÀÊ¶ÁÒôÁ¿Îª¾²Òô£¬16ÀÊ¶ÁÒôÁ¿×î´ó
		//t[0~5]:0ÀÊ¶ÁÓïËÙ×îÂý£¬5ÀÊ¶ÁÓïËÙ×î¿ì
		//ÆäËû²»³£ÓÃ¹¦ÄÜÇë²Î¿¼Êý¾ÝÊÖ²á
		
		//ÔÝÍ£ºÏ³É£¬´ËÊ±Ã»ÓÐÓÃµ½£¬ÓÃÓÚÕ¹Ê¾º¯ÊýÓÃ·¨
		//YS_SYN_Set(SYN_SuspendCom);
		*/
}
}