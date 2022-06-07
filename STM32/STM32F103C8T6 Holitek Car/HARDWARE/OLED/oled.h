#ifndef __OLED_H
#define __OLED_H			  	 
#include "sys.h"
#include "stdlib.h"
#include "stm32f10x.h"


//OLEDģʽ����
//0:4�ߴ���ģʽ
//1:����8080ģʽ
#define OLED_MODE 0
#define SIZE 16
#define XLevelL		0x00
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF 
#define X_WIDTH 	128
#define Y_WIDTH 	64	    						  
//-----------------OLED�˿ڶ���----------------

//7��OLED���������Ŷ������£�
//GND
//VCC��2.2V~5.5V
//SCL��CLKʱ�ӣ��ߵ�ƽ2.2V~5.5V��--D0
//SDA��MOSI����--D1
//RST����λ
//D/C������/����
//CS��Ƭѡ�ţ��ӵ�

//PC0~7,��Ϊ������
//#define DATAOUT(x) GPIO_Write(GPIOC,x);//���  
//ʹ��4�ߴ��нӿ�ʱʹ�� 

#define OLED_SCLK_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_9)			//CLK	PB9 SCK D0
#define OLED_SCLK_Set() GPIO_SetBits(GPIOB,GPIO_Pin_9)

#define OLED_SDIN_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_8)			//DIN	PB8 MISO D1
#define OLED_SDIN_Set() GPIO_SetBits(GPIOB,GPIO_Pin_8)


#define OLED_RST_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_7)				//RES	PB7
#define OLED_RST_Set() GPIO_SetBits(GPIOB,GPIO_Pin_7)

#define OLED_DC_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_6)				//DC	PB6
#define OLED_DC_Set() GPIO_SetBits(GPIOB,GPIO_Pin_6)

#define OLED_CS_Clr()  GPIO_ResetBits(GPIOB,GPIO_Pin_5)				//CS  	PB5
#define OLED_CS_Set()  GPIO_SetBits(GPIOB,GPIO_Pin_5)
 		     
#define OLED_CMD  0	//д����
#define OLED_DATA 1	//д����

void OLED_ShowCar();
void OLED_ShowYangM();
void OLED_ShowJr();
	
//OLED�����ú���
void OLED_WR_Byte(uint8_t dat,uint8_t cmd);	    
void OLED_Display_On(void);
void OLED_Display_Off(void);	   							   		    
void OLED_Init(void);
void OLED_Clear(void);
void OLED_DrawPoint(uint8_t x,uint8_t y,uint8_t t);
void OLED_Fill(uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2,uint8_t dot);
void OLED_ShowChar(uint8_t x,uint8_t y,uint8_t chr);
void OLED_ShowNum(uint8_t x,uint8_t y,uint32_t num,uint8_t len,uint8_t size);
void OLED_ShowArrStr(unsigned char x, unsigned char y, unsigned char ch[],uint8_t nlens);
void OLED_ShowStr(unsigned char x, unsigned char y, unsigned char ch[], unsigned char TextSize);
void OLED_ShowString(uint8_t x,uint8_t y, uint8_t *p);	 
void OLED_Set_Pos(unsigned char x, unsigned char y);
void OLED_ShowCHinese(uint8_t x,uint8_t y,uint8_t no);
void OLED_ShowCHinese_nfc(uint8_t x,uint8_t y,uint8_t no);
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]);
void OLED_DrawBMP2(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char BMP[]);
#endif  
	 



