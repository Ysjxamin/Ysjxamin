/**************************************************
//软件环境：MDK5.18a
//用0.96'OLED显示
**************************************************/
/*******************************************
程序名称：OLED显示
文 件 名：main.c
版 本 号：V1.0

作    者：
日    期：2019-3-24
修    改：无
功    能：用STM32F103 和0.96'OLED实现显示功能
硬件说明：
          -----------------------------------------------------
          OLED接线：                 
          GND ----- GND                                                
          VCC ----- 3.3V            
          CLK ----- PB13              
          MOSI ---- PB14
		  RES ----- PB15
          DC ------ PC6              
          CS ------ PB12             
          -----------------------------------------------------
软件说明：OLED使用IO口模块SPI通信
修改历史：无
修改日期：无
修改作者：无
修改功能：无         
备    注：无
********************************************/

#include "oled.h"
#include "stdlib.h"
#include "oledfont.h"  	 
#include "delay.h"
#include "codetab.h"

void OLED_ShowCar()
{
	int i;
	//OLED第一行显示“多功能医用小车：”
	for(i=0;i<8;i++)
	{
OLED_ShowCHinese(i*16,0,i+0);
	}
		//OLED第二行显示”模式：疫情隔离点“
	for(i=0;i<8;i++)
	{
OLED_ShowCHinese(i*16,2,i+8);
	}
}

void OLED_ShowCar_hesuan()
{
	int i;
	//OLED第一行显示“多功能医用小车：”
	for(i=0;i<8;i++)
	{
OLED_ShowCHinese(i*16,0,i+0);
	}
		//OLED第二行显示”模式：核酸检测点“
	for(i=0;i<8;i++)
	{
OLED_ShowCHinese(i*16,2,i+16);
	}
}

void OLED_ShowYangM()
{
	OLED_ShowCar_hesuan();
	int i;
	//OLED第一行显示“多功能医用小车：”
	for(i=0;i<8;i++)
	{
OLED_ShowCHinese_nfc(i*16,4,i+0);
	}
		//OLED第二行显示”模式：疫情隔离点“
	for(i=0;i<6;i++)
	{
OLED_ShowCHinese_nfc(i*16,6,i+9);
	}
}
void OLED_ShowJr()
{
	OLED_ShowCar_hesuan();
	int i;
	//OLED第一行显示“多功能医用小车：”
	for(i=0;i<8;i++)
	{
OLED_ShowCHinese_nfc(i*16,4,i+15);
	}
		//OLED第二行显示”模式：疫情隔离点“
	for(i=0;i<6;i++)
	{
OLED_ShowCHinese_nfc(i*16,6,i+24);
	}
}
/**
/****************************************************************/
//--------------------------------------------------------------
// Prototype      : void OLED_DrawBMP(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char BMP[]);
// Calls          : 
// Parameters     : x0,y0 -- ?????(x0:0~127, y0:0~7); x1,y1 -- ?????(???)???(x1:1~128,y1:1~8)
// Description    : ??BMP??
//--------------------------------------------------------------
void OLED_DrawBMP2(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char BMP[])
{
	unsigned int j=0;
	unsigned char x,y;

	if(y1%8==0)
		y = y1/8;
	else
		y = y1/8 + 1;
	
	for(y=y0;y<y1;y++)
	{
		OLED_Set_Pos(x0,y);
		for(x=x0;x<x1;x++)
		{
			OLED_WR_Byte(BMP[j++],OLED_DATA); 
		}
	}
}
/****************************************************************/

//OLED的显存
//存放格式如下.
//[0]0 1 2 3 ... 127	
//[1]0 1 2 3 ... 127	
//[2]0 1 2 3 ... 127	
//[3]0 1 2 3 ... 127	
//[4]0 1 2 3 ... 127	
//[5]0 1 2 3 ... 127	
//[6]0 1 2 3 ... 127	
//[7]0 1 2 3 ... 127 			   

//#if OLED_MODE==1
////向SSD1106写入一个字节。
////dat:要写入的数据/命令
////cmd:数据/命令标志 0,表示命令;1,表示数据;
//void OLED_WR_Byte(uint8_t dat,uint8_t cmd)
//{
//	DATAOUT(dat);	    
//	if(cmd)
//	  OLED_DC_Set();
//	else 
//	  OLED_DC_Clr();		   
//	OLED_CS_Clr();
//	OLED_WR_Clr();	 
//	OLED_WR_Set();
//	OLED_CS_Set();	  
//	OLED_DC_Set();	 
//} 	    	    
//#else
//向SSD1106写入一个字节。
//dat:要写入的数据/命令
//cmd:数据/命令标志 0,表示命令;1,表示数据;
void OLED_WR_Byte(uint8_t dat,uint8_t cmd)
{	
	uint8_t i;			  
	if(cmd)
	  OLED_DC_Set();
	else 
	  OLED_DC_Clr();		  
	OLED_CS_Clr();
	
	for(i=0;i<8;i++)
	{			  
		OLED_SCLK_Clr();
		if(dat&0x80)
		   OLED_SDIN_Set();
		else 
		   OLED_SDIN_Clr();
		OLED_SCLK_Set();
		dat<<=1;   
	}
	
	//SPI1_ReadWriteByte(dat);//SPI写入数据
	
	OLED_CS_Set();
	OLED_CS_Set();
	OLED_DC_Set();   	  
} 
//#endif
void OLED_Set_Pos(unsigned char x, unsigned char y) 
{ 
	OLED_WR_Byte(0xb0+y,OLED_CMD);
	OLED_WR_Byte(((x&0xf0)>>4)|0x10,OLED_CMD);
	OLED_WR_Byte((x&0x0f)|0x01,OLED_CMD); 
}  

//开启OLED显示    
void OLED_Display_On(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC命令
	OLED_WR_Byte(0X14,OLED_CMD);  //DCDC ON
	OLED_WR_Byte(0XAF,OLED_CMD);  //DISPLAY ON
}

//关闭OLED显示     
void OLED_Display_Off(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC命令
	OLED_WR_Byte(0X10,OLED_CMD);  //DCDC OFF
	OLED_WR_Byte(0XAE,OLED_CMD);  //DISPLAY OFF
}

//清屏函数,清完屏,整个屏幕是黑色的!和没点亮一样!!!	  
void OLED_Clear(void)  
{  
	uint8_t i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED_WR_Byte (0xb0+i,OLED_CMD);    //设置页地址（0~7）
		OLED_WR_Byte (0x00,OLED_CMD);      //设置显示位置—列低地址
		OLED_WR_Byte (0x10,OLED_CMD);      //设置显示位置—列高地址   
		for(n=0;n<128;n++)
			OLED_WR_Byte(0,OLED_DATA); 
	} //更新显示
}

//在指定位置显示一个字符,包括部分字符
//x:0~127
//y:0~63
//mode:0,反白显示;1,正常显示				 
//size:选择字体 16/12 
void OLED_ShowChar(uint8_t x,uint8_t y,uint8_t chr)
{      	
	unsigned char c=0,i=0;	
	c=chr-' ';//得到偏移后的值			
	if(x>Max_Column-1){x=0;y=y+2;}
	if(SIZE ==16)
	{
		OLED_Set_Pos(x,y);	
		for(i=0;i<8;i++)
			OLED_WR_Byte(F8X16[c*16+i],OLED_DATA);
		OLED_Set_Pos(x,y+1);
		for(i=0;i<8;i++)
			OLED_WR_Byte(F8X16[c*16+i+8],OLED_DATA);
	}
	else 
	{	
		OLED_Set_Pos(x,y+1);
		for(i=0;i<6;i++)
			OLED_WR_Byte(F6x8[c][i],OLED_DATA);				
	}
}
//m^n函数
uint32_t oled_pow(uint8_t m,uint8_t n)
{
	uint32_t result=1;	 
	while(n--)
		result*=m; 
	
	return result;
}				  
//显示2个数字
//x,y :起点坐标	 
//len :数字的位数
//size:字体大小
//mode:模式	0,填充模式;1,叠加模式
//num:数值(0~4294967295);	 		  
void OLED_ShowNum(uint8_t x,uint8_t y,uint32_t num,uint8_t len,uint8_t size)
{         	
	uint8_t t,temp;
	uint8_t enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/oled_pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				OLED_ShowChar(x+(size/2)*t,y,' ');
				continue;
			}else enshow=1; 
		 	 
		}
	 	OLED_ShowChar(x+(size/2)*t,y,temp+'0'); 
	}
} 


void OLED_ShowArrStr(unsigned char x, unsigned char y, unsigned char ch[],uint8_t nlens)
{
	unsigned char c = 0,i = 0,j = 0,l = 0;
	
	for(l=0;l<21;l++)
	{
		if(l<nlens)
			c = ch[j] - 32;
		else
			c = 0;
		
		if(x > 126)
		{
			x = 0;
			y++;
		}
		OLED_Set_Pos(x,y);
		for(i=0;i<6;i++)
			OLED_WR_Byte(F6x8[c][i],OLED_DATA);	  
		x += 6;
		j++;
	}
}

//--------------------------------------------------------------
// Prototype      : void OLED_ShowChar(unsigned char x, unsigned char y, unsigned char ch[], unsigned char TextSize)
// Calls          : 
// Parameters     : x,y -- 起始点坐标(x:0~127, y:0~7); ch[] -- 要显示的字符串; TextSize -- 字符大小(1:6*8 ; 2:8*16)
// Description    : 显示codetab.h中的ASCII字符，有6*8和8*16可选择
//--------------------------------------------------------------
void OLED_ShowStr(unsigned char x, unsigned char y, unsigned char ch[], unsigned char TextSize)
{
	unsigned char c = 0,i = 0,j = 0;
	switch(TextSize)
	{
		case 1:
		{
			while(ch[j] != '\0')
			{
				c = ch[j] - 32;
				if(x > 126)
				{
					x = 0;
					y++;
				}
				OLED_Set_Pos(x,y);
				for(i=0;i<6;i++)
					OLED_WR_Byte(F6x8[c][i],OLED_DATA);	  
				x += 6;
				j++;
			}
		}
		break;
		case 2:
		{
			while(ch[j] != '\0')
			{
				c = ch[j] - 32;
				if(x > 120)
				{
					x = 0;
					y++;
				}
				OLED_Set_Pos(x,y);
				for(i=0;i<8;i++)
					OLED_WR_Byte(F8X16[c*16+i],OLED_DATA);	  
				OLED_Set_Pos(x,y+1);
				for(i=0;i<8;i++)
					OLED_WR_Byte(F8X16[c*16+i+8],OLED_DATA);	  
				x += 8;
				j++;
			}
		}
		break;
	}
}

//显示一个字符号串
//X从0开始计数
//Y第一行值为0，第二行为2，依次为 0 2 4 6 ,第一行显示系统状态，比如初始化成功，当前时间等，第二行显示服务器信息，第三行显示车辆信息，第四行显示温湿度值 
void OLED_ShowString(uint8_t x,uint8_t y,uint8_t *chr)
{
	unsigned char j=0;
	while (chr[j]!='\0')
	{		
		OLED_ShowChar(x,y,chr[j]);
		x+=8;
		if(x>120)
			{x=0;y+=2;}
		j++;
	}
}
//显示菜单汉字
void OLED_ShowCHinese(uint8_t x,uint8_t y,uint8_t no)
{      			    
	uint8_t t,adder=0;
	OLED_Set_Pos(x,y);	
    for(t=0;t<16;t++)
	{
		OLED_WR_Byte(Hzk[2*no][t],OLED_DATA);
		adder+=1;
	}	
	OLED_Set_Pos(x,y+1);	
    for(t=0;t<16;t++)
	{	
		OLED_WR_Byte(Hzk[2*no+1][t],OLED_DATA);
		adder+=1;
	}					
}
//显示编号识别汉字
void OLED_ShowCHinese_nfc(uint8_t x,uint8_t y,uint8_t no)
{      			    
	uint8_t t,adder=0;
	OLED_Set_Pos(x,y);	
    for(t=0;t<16;t++)
	{
		OLED_WR_Byte(Hzk_nfc[2*no][t],OLED_DATA);
		adder+=1;
	}	
	OLED_Set_Pos(x,y+1);	
    for(t=0;t<16;t++)
	{	
		OLED_WR_Byte(Hzk_nfc[2*no+1][t],OLED_DATA);
		adder+=1;
	}					
}
/***********功能描述：显示显示BMP图片128×64起始点坐标(x,y),x的范围0～127，y为页的范围0～7*****************/
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[])
{ 	
	unsigned int j=0;
	unsigned char x,y;
  
	if(y1%8==0) y=y1/8;      
	else y=y1/8+1;
	for(y=y0;y<y1;y++)
	{
		OLED_Set_Pos(x0,y);
		for(x=x0;x<x1;x++)
		{      
			OLED_WR_Byte(BMP[j++],OLED_DATA);	    	
		}
	}
} 


//初始化SSD1306		
/*
OLED接线：                 
GND ----- GND                                                
VCC ----- 3.3V            
CLK ----- PB13              
MOSI ---- PB14
RES ----- PB15
DC ------ PC6              
CS ------ PB12 
*/
void OLED_Init(void)
{  	 
 	GPIO_InitTypeDef  GPIO_InitStructure;
 	
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 	//使能GPIOB口时钟

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;	 
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 	//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;			//速度50MHz
 	GPIO_Init(GPIOB, &GPIO_InitStructure);	  					//初始化GPIOB5-9
 	GPIO_SetBits(GPIOB,GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9);	

	OLED_RST_Set();	
	delay_ms(100);
	OLED_RST_Clr();	
	delay_ms(200);
	OLED_RST_Set(); 
					  
	OLED_WR_Byte(0xAE,OLED_CMD);	//--turn off oled panel
	OLED_WR_Byte(0x00,OLED_CMD);	//---set low column address
	OLED_WR_Byte(0x10,OLED_CMD);	//---set high column address
	OLED_WR_Byte(0x40,OLED_CMD);	//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	OLED_WR_Byte(0x81,OLED_CMD);	//--set contrast control register
	OLED_WR_Byte(0xCF,OLED_CMD); 	// Set SEG Output Current Brightness
	OLED_WR_Byte(0xA1,OLED_CMD);	//--Set SEG/Column Mapping     0xa0左右反置 0xa1正常
	OLED_WR_Byte(0xC8,OLED_CMD);	//Set COM/Row Scan Direction   0xc0上下反置 0xc8正常
	OLED_WR_Byte(0xA6,OLED_CMD);	//--set normal display
	OLED_WR_Byte(0xA8,OLED_CMD);	//--set multiplex ratio(1 to 64)
	OLED_WR_Byte(0x3f,OLED_CMD);	//--1/64 duty
	OLED_WR_Byte(0xD3,OLED_CMD);	//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	OLED_WR_Byte(0x00,OLED_CMD);	//-not offset
	OLED_WR_Byte(0xd5,OLED_CMD);	//--set display clock divide ratio/oscillator frequency
	OLED_WR_Byte(0x80,OLED_CMD);	//--set divide ratio, Set Clock as 100 Frames/Sec
	OLED_WR_Byte(0xD9,OLED_CMD);	//--set pre-charge period
	OLED_WR_Byte(0xF1,OLED_CMD);	//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	OLED_WR_Byte(0xDA,OLED_CMD);	//--set com pins hardware configuration
	OLED_WR_Byte(0x12,OLED_CMD);
	OLED_WR_Byte(0xDB,OLED_CMD);	//--set vcomh
	OLED_WR_Byte(0x40,OLED_CMD);	//Set VCOM Deselect Level
	OLED_WR_Byte(0x20,OLED_CMD);	//-Set Page Addressing Mode (0x00/0x01/0x02)
	OLED_WR_Byte(0x02,OLED_CMD);	//
	OLED_WR_Byte(0x8D,OLED_CMD);	//--set Charge Pump enable/disable
	OLED_WR_Byte(0x14,OLED_CMD);	//--set(0x10) disable
	OLED_WR_Byte(0xA4,OLED_CMD);	// Disable Entire Display On (0xa4/0xa5)
	OLED_WR_Byte(0xA6,OLED_CMD);	// Disable Inverse Display On (0xa6/a7) 
	OLED_WR_Byte(0xAF,OLED_CMD);	//--turn on oled panel
	
	OLED_WR_Byte(0xAF,OLED_CMD); 	/*display ON*/ 
	OLED_Clear();
	OLED_Set_Pos(0,0); 	
}
