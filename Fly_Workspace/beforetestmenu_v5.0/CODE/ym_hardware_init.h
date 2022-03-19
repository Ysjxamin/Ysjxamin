/*
 * ym_hardware_init.h
 *
 *  Created on: 2022年3月1日
 *      Author: huawei
 */

#ifndef CODE_YM_HARDWARE_INIT_H_
#define CODE_YM_HARDWARE_INIT_H_

//使用匿名4.3上位机协议
/////////////////////////////////////////////////////////////////////////////////////
//数据拆分宏定义，在发送大于1字节的数据类型时，比如int16、float等，需要把数据拆分成单独字节进行发送
#define BYTE0(dwTemp)       ( *( (char *)(&dwTemp)    ) )     /*!< uint32_t 数据拆分 byte0  */
#define BYTE1(dwTemp)       ( *( (char *)(&dwTemp) + 1) )     /*!< uint32_t 数据拆分 byte1  */
#define BYTE2(dwTemp)       ( *( (char *)(&dwTemp) + 2) )     /*!< uint32_t 数据拆分 byte2  */
#define BYTE3(dwTemp)       ( *( (char *)(&dwTemp) + 3) )     /*!< uint32_t 数据拆分 byte3  */

 extern unsigned char DataScope_OutPut_Buffer[42];      //串口发送缓冲区
 void ym_SendWirelessUpMachine(float data1, float data2, float data3, float data4, float data5, float data6, float data7, float data8, float data9,float data10);

 extern unsigned char i; //计数变量
 extern unsigned char Send_Count; //串口需要发送的数据个数
 extern  float a;
extern uint32 read_data[24];
extern uint32 write_data[24];

void ym_hardware_init(void);

void ANO_DT_send_int16(short data1, short data2, short data3, short data4, short data5, short data6, short data7, short data8 );//匿名上位机发送函数

//extern unsigned char DataScope_OutPut_Buffer[42];      //待发送帧数据缓存区


void DataScope_Get_Channel_Data(float Data,unsigned char Channel);    // 写通道数据至 待发送帧数据缓存区

unsigned char DataScope_Data_Generate(unsigned char Channel_Number);  // 发送帧数据生成函数



#endif /* CODE_YM_HARDWARE_INIT_H_ */
