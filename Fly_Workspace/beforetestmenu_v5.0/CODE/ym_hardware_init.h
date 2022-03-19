/*
 * ym_hardware_init.h
 *
 *  Created on: 2022��3��1��
 *      Author: huawei
 */

#ifndef CODE_YM_HARDWARE_INIT_H_
#define CODE_YM_HARDWARE_INIT_H_

//ʹ������4.3��λ��Э��
/////////////////////////////////////////////////////////////////////////////////////
//���ݲ�ֺ궨�壬�ڷ��ʹ���1�ֽڵ���������ʱ������int16��float�ȣ���Ҫ�����ݲ�ֳɵ����ֽڽ��з���
#define BYTE0(dwTemp)       ( *( (char *)(&dwTemp)    ) )     /*!< uint32_t ���ݲ�� byte0  */
#define BYTE1(dwTemp)       ( *( (char *)(&dwTemp) + 1) )     /*!< uint32_t ���ݲ�� byte1  */
#define BYTE2(dwTemp)       ( *( (char *)(&dwTemp) + 2) )     /*!< uint32_t ���ݲ�� byte2  */
#define BYTE3(dwTemp)       ( *( (char *)(&dwTemp) + 3) )     /*!< uint32_t ���ݲ�� byte3  */

 extern unsigned char DataScope_OutPut_Buffer[42];      //���ڷ��ͻ�����
 void ym_SendWirelessUpMachine(float data1, float data2, float data3, float data4, float data5, float data6, float data7, float data8, float data9,float data10);

 extern unsigned char i; //��������
 extern unsigned char Send_Count; //������Ҫ���͵����ݸ���
 extern  float a;
extern uint32 read_data[24];
extern uint32 write_data[24];

void ym_hardware_init(void);

void ANO_DT_send_int16(short data1, short data2, short data3, short data4, short data5, short data6, short data7, short data8 );//������λ�����ͺ���

//extern unsigned char DataScope_OutPut_Buffer[42];      //������֡���ݻ�����


void DataScope_Get_Channel_Data(float Data,unsigned char Channel);    // дͨ�������� ������֡���ݻ�����

unsigned char DataScope_Data_Generate(unsigned char Channel_Number);  // ����֡�������ɺ���



#endif /* CODE_YM_HARDWARE_INIT_H_ */
