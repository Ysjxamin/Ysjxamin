/*
 * ym_all_init.c
 *
 *  Created on: 2022年2月13日
 *      Author: huawei
 */

#include "headfile.h"
#include "ym_hardware_init.h"
 unsigned char i; //计数变量
 unsigned char Send_Count; //串口需要发送的数据个数
 float a;
extern int32 MidSteering;
//uint32 read_data[24]= {0};//读数据缓存数组
//uint32 write_data[24]= {0};//写数据缓存数组
//uint32 write_buf ;//写数据缓存
unsigned char DataScope_OutPut_Buffer[42] = {0};       //串口发送缓冲区
uint8 data_to_send[16];//匿名上位机发送数据缓存
void ym_hardware_init(void)
{
    /**************TFT彩屏初始化**************/
     lcd_init();
     lcd_clear(WHITE);
     systick_delay_ms(STM0, 10);//上电延时
    /**************编码器初始化**************/
     gpt12_init(GPT12_T2, encoder_A1, encoder_B1);//后轮马达编码器
     gpt12_init(GPT12_T4, encoder_A2, encoder_B2);//动量轮编码器
    /**************LED初始化**************/
     gpio_init(LED0,GPO,0,PUSHPULL);
     gpio_init(LED1,GPO,0,PUSHPULL);
     gpio_init(LED2,GPO,0,PUSHPULL);
     /**************按键初始化**************/
      gpio_init(K1, GPI, 0, PULLUP);
      gpio_init(K2, GPI, 0, PULLUP);
      gpio_init(K3, GPI, 0, PULLUP);
      gpio_init(K4, GPI, 0, PULLUP);
      gpio_init(K0, GPI, 0, PULLUP);    //输入
     /**************蜂鸣器**************/
     gpio_init(BEEP,GPO,0,PUSHPULL);   //输出
     /**************电机初始化***************/
     gtm_pwm_init(Motor_back_Go, 17 * 1000, 0);   //后轮电机17kHz
     gpio_init(Motor_back_Dir, GPO, 0, PUSHPULL);
     gtm_pwm_init(Motor_balance_Go, 17000, 0);   //平衡轮电机17kHz
     gpio_init(Motor_balance_Dir, GPO, 0, PUSHPULL);
     //初始化方向控制引脚
     gtm_pwm_init(DUOJI_Channel, 50, MidSteering);   //50Hz MidSteering*TIMES/
     //mpu6050初始化
     mpu6050_init();
     //ym_mpu6050_init();
     seekfree_wireless_init();

}
void ym_SendWirelessUpMachine(float data1, float data2, float data3, float data4, float data5, float data6, float data7, float data8, float data9,float data10)
{
            //if(a>3.14) a=-3.14;
            DataScope_Get_Channel_Data(data1, 1 );
            DataScope_Get_Channel_Data(data2, 2 );
            DataScope_Get_Channel_Data(data3, 3 );
            DataScope_Get_Channel_Data(data4, 4 );
            DataScope_Get_Channel_Data(data5, 5 );
            DataScope_Get_Channel_Data(data6 , 6 );
            DataScope_Get_Channel_Data(data7, 7 );
            DataScope_Get_Channel_Data(data8, 8 );
            DataScope_Get_Channel_Data(data9, 9 );
            DataScope_Get_Channel_Data(data10, 10);
            Send_Count = DataScope_Data_Generate(10);
                uart_putbuff(WIRELESS_UART,DataScope_OutPut_Buffer,Send_Count);//发送最后的数据
}
/*******************************************************************************
 *  @brief      ANO_DT_send_int16函数
 *  @note       匿名上位机发送函数 v7
 *  @date       2021-07-11
 *  @author     小麦
 ******************************************************************************/
void ANO_DT_send_int16(short data1, short data2, short data3, short data4, short data5, short data6, short data7, short data8 )
{
    unsigned char  _cnt=0;
    unsigned char  sumcheck = 0, i = 0,addcheck = 0;
    data_to_send[_cnt++] = 0xAA;      //匿名协议帧头  0xAAAA
    data_to_send[_cnt++] = 0xAA;
    data_to_send[_cnt++] = 0xF1;      //使用用户协议帧0xF1
    data_to_send[_cnt++] = 16;        //8个int16_t 长度 16个字节

    data_to_send[_cnt++]=BYTE0(data1); //小端
    data_to_send[_cnt++]=BYTE1(data1);

    data_to_send[_cnt++]=BYTE0(data2);
    data_to_send[_cnt++]=BYTE1(data2);

    data_to_send[_cnt++]=BYTE0(data3);
    data_to_send[_cnt++]=BYTE1(data3);

    data_to_send[_cnt++]=BYTE0(data4);
    data_to_send[_cnt++]=BYTE1(data4);

    data_to_send[_cnt++]=BYTE0(data5);
    data_to_send[_cnt++]=BYTE1(data5);

    data_to_send[_cnt++]=BYTE0(data6);
    data_to_send[_cnt++]=BYTE1(data6);

    data_to_send[_cnt++]=BYTE0(data7);
    data_to_send[_cnt++]=BYTE1(data7);

    data_to_send[_cnt++]=BYTE0(data8);
    data_to_send[_cnt++]=BYTE1(data8);

    //校验
    for(i=0;i<_cnt;i++)
    {
        sumcheck+=data_to_send[i];
        addcheck+=sumcheck;
    }
    data_to_send[_cnt++]=sumcheck;
    data_to_send[_cnt++]=addcheck;

    //uart_putbuff(UART_0, data_to_send, _cnt);//发送最后的数据
    uart_putbuff(WIRELESS_UART,data_to_send,_cnt);//发送最后的数据
    //seekfree_wireless_send_buff(data_to_send,_cnt);//由于sizeof计算字符串的长度包含了最后一个0，因此需要减一

}
//函数说明：将单精度浮点数据转成4字节数据并存入指定地址
//附加说明：用户无需直接操作此函数
//target:目标单精度数据
//buf:待写入数组
//beg:指定从数组第几个元素开始写入
//函数无返回
void Float2Byte(float *target,unsigned char *buf,unsigned char beg)
{
    unsigned char *point;
    point = (unsigned char*)target;   //得到float的地址
    buf[beg]   = point[0];
    buf[beg+1] = point[1];
    buf[beg+2] = point[2];
    buf[beg+3] = point[3];
}


//函数说明：将待发送通道的单精度浮点数据写入发送缓冲区
//Data：通道数据
//Channel：选择通道（1-10）
//函数无返回
void DataScope_Get_Channel_Data(float Data,unsigned char Channel)
{
    if ( (Channel > 10) || (Channel == 0) )  return; //通道个数大于10或等于0，直接跳出，不执行函数
  else
  {
     switch (Channel)
        {
      case 1:  Float2Byte(&Data,DataScope_OutPut_Buffer,1); break;
      case 2:  Float2Byte(&Data,DataScope_OutPut_Buffer,5); break;
          case 3:  Float2Byte(&Data,DataScope_OutPut_Buffer,9); break;
          case 4:  Float2Byte(&Data,DataScope_OutPut_Buffer,13); break;
          case 5:  Float2Byte(&Data,DataScope_OutPut_Buffer,17); break;
          case 6:  Float2Byte(&Data,DataScope_OutPut_Buffer,21); break;
          case 7:  Float2Byte(&Data,DataScope_OutPut_Buffer,25); break;
          case 8:  Float2Byte(&Data,DataScope_OutPut_Buffer,29); break;
          case 9:  Float2Byte(&Data,DataScope_OutPut_Buffer,33); break;
          case 10: Float2Byte(&Data,DataScope_OutPut_Buffer,37); break;
        }
  }
}


//函数说明：生成 DataScopeV1.0 能正确识别的帧格式
//Channel_Number，需要发送的通道个数
//返回发送缓冲区数据个数
//返回0表示帧格式生成失败
unsigned char DataScope_Data_Generate(unsigned char Channel_Number)
{
    if ( (Channel_Number > 10) || (Channel_Number == 0) ) { return 0; }  //通道个数大于10或等于0，直接跳出，不执行函数
  else
  {
     DataScope_OutPut_Buffer[0] = '$';  //帧头

     switch(Channel_Number)
   {
         case 1:   DataScope_OutPut_Buffer[5]  =  5; return  6;
         case 2:   DataScope_OutPut_Buffer[9]  =  9; return 10;
         case 3:   DataScope_OutPut_Buffer[13] = 13; return 14;
         case 4:   DataScope_OutPut_Buffer[17] = 17; return 18;
         case 5:   DataScope_OutPut_Buffer[21] = 21; return 22;
         case 6:   DataScope_OutPut_Buffer[25] = 25; return 26;
         case 7:   DataScope_OutPut_Buffer[29] = 29; return 30;
         case 8:   DataScope_OutPut_Buffer[33] = 33; return 34;
         case 9:   DataScope_OutPut_Buffer[37] = 37; return 38;
     case 10:  DataScope_OutPut_Buffer[41] = 41; return 42;
   }
  }
    return 0;
}



