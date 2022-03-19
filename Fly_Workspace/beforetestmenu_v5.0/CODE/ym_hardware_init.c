/*
 * ym_all_init.c
 *
 *  Created on: 2022��2��13��
 *      Author: huawei
 */

#include "headfile.h"
#include "ym_hardware_init.h"
 unsigned char i; //��������
 unsigned char Send_Count; //������Ҫ���͵����ݸ���
 float a;
extern int32 MidSteering;
//uint32 read_data[24]= {0};//�����ݻ�������
//uint32 write_data[24]= {0};//д���ݻ�������
//uint32 write_buf ;//д���ݻ���
unsigned char DataScope_OutPut_Buffer[42] = {0};       //���ڷ��ͻ�����
uint8 data_to_send[16];//������λ���������ݻ���
void ym_hardware_init(void)
{
    /**************TFT������ʼ��**************/
     lcd_init();
     lcd_clear(WHITE);
     systick_delay_ms(STM0, 10);//�ϵ���ʱ
    /**************��������ʼ��**************/
     gpt12_init(GPT12_T2, encoder_A1, encoder_B1);//������������
     gpt12_init(GPT12_T4, encoder_A2, encoder_B2);//�����ֱ�����
    /**************LED��ʼ��**************/
     gpio_init(LED0,GPO,0,PUSHPULL);
     gpio_init(LED1,GPO,0,PUSHPULL);
     gpio_init(LED2,GPO,0,PUSHPULL);
     /**************������ʼ��**************/
      gpio_init(K1, GPI, 0, PULLUP);
      gpio_init(K2, GPI, 0, PULLUP);
      gpio_init(K3, GPI, 0, PULLUP);
      gpio_init(K4, GPI, 0, PULLUP);
      gpio_init(K0, GPI, 0, PULLUP);    //����
     /**************������**************/
     gpio_init(BEEP,GPO,0,PUSHPULL);   //���
     /**************�����ʼ��***************/
     gtm_pwm_init(Motor_back_Go, 17 * 1000, 0);   //���ֵ��17kHz
     gpio_init(Motor_back_Dir, GPO, 0, PUSHPULL);
     gtm_pwm_init(Motor_balance_Go, 17000, 0);   //ƽ���ֵ��17kHz
     gpio_init(Motor_balance_Dir, GPO, 0, PUSHPULL);
     //��ʼ�������������
     gtm_pwm_init(DUOJI_Channel, 50, MidSteering);   //50Hz MidSteering*TIMES/
     //mpu6050��ʼ��
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
                uart_putbuff(WIRELESS_UART,DataScope_OutPut_Buffer,Send_Count);//������������
}
/*******************************************************************************
 *  @brief      ANO_DT_send_int16����
 *  @note       ������λ�����ͺ��� v7
 *  @date       2021-07-11
 *  @author     С��
 ******************************************************************************/
void ANO_DT_send_int16(short data1, short data2, short data3, short data4, short data5, short data6, short data7, short data8 )
{
    unsigned char  _cnt=0;
    unsigned char  sumcheck = 0, i = 0,addcheck = 0;
    data_to_send[_cnt++] = 0xAA;      //����Э��֡ͷ  0xAAAA
    data_to_send[_cnt++] = 0xAA;
    data_to_send[_cnt++] = 0xF1;      //ʹ���û�Э��֡0xF1
    data_to_send[_cnt++] = 16;        //8��int16_t ���� 16���ֽ�

    data_to_send[_cnt++]=BYTE0(data1); //С��
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

    //У��
    for(i=0;i<_cnt;i++)
    {
        sumcheck+=data_to_send[i];
        addcheck+=sumcheck;
    }
    data_to_send[_cnt++]=sumcheck;
    data_to_send[_cnt++]=addcheck;

    //uart_putbuff(UART_0, data_to_send, _cnt);//������������
    uart_putbuff(WIRELESS_UART,data_to_send,_cnt);//������������
    //seekfree_wireless_send_buff(data_to_send,_cnt);//����sizeof�����ַ����ĳ��Ȱ��������һ��0�������Ҫ��һ

}
//����˵�����������ȸ�������ת��4�ֽ����ݲ�����ָ����ַ
//����˵�����û�����ֱ�Ӳ����˺���
//target:Ŀ�굥��������
//buf:��д������
//beg:ָ��������ڼ���Ԫ�ؿ�ʼд��
//�����޷���
void Float2Byte(float *target,unsigned char *buf,unsigned char beg)
{
    unsigned char *point;
    point = (unsigned char*)target;   //�õ�float�ĵ�ַ
    buf[beg]   = point[0];
    buf[beg+1] = point[1];
    buf[beg+2] = point[2];
    buf[beg+3] = point[3];
}


//����˵������������ͨ���ĵ����ȸ�������д�뷢�ͻ�����
//Data��ͨ������
//Channel��ѡ��ͨ����1-10��
//�����޷���
void DataScope_Get_Channel_Data(float Data,unsigned char Channel)
{
    if ( (Channel > 10) || (Channel == 0) )  return; //ͨ����������10�����0��ֱ����������ִ�к���
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


//����˵�������� DataScopeV1.0 ����ȷʶ���֡��ʽ
//Channel_Number����Ҫ���͵�ͨ������
//���ط��ͻ��������ݸ���
//����0��ʾ֡��ʽ����ʧ��
unsigned char DataScope_Data_Generate(unsigned char Channel_Number)
{
    if ( (Channel_Number > 10) || (Channel_Number == 0) ) { return 0; }  //ͨ����������10�����0��ֱ����������ִ�к���
  else
  {
     DataScope_OutPut_Buffer[0] = '$';  //֡ͷ

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



