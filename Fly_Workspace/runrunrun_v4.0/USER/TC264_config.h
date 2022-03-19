/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ����Ⱥ��824575535
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file       		isr
 * @company	   		�ɶ���ɿƼ����޹�˾
 * @author     		��ɿƼ�(QQ3184284598)
 * @version    		�鿴doc��version�ļ� �汾˵��
 * @Software 		ADS v1.2.2
 * @Target core		TC264D
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2020-3-23
 ********************************************************************************************************************/

#ifndef _TC264_config_h
#define _TC264_config_h

#define AURIX_MCU_FREQUENCY         200*1000*1000//���õ�Ƭ��Ƶ��Ϊ200M 200M(Ĭ��Ƶ��)

//-------------------------------------------------------------------------------------------------------------------
//  PRINTF_ENABLE Ϊ 0               ��ʹ��printf���ڴ�ӡ�����������������Ϣ���򲻻��ʼ����Ӧ����
//  PRINTF_ENABLE Ϊ 1               ʹ��printf���ڴ�ӡ���������������Ϣ������ʼ����Ӧ���ڣ����ﶨ��Ϊ1֮�������Լ��ֶ���ʼ������
//-------------------------------------------------------------------------------------------------------------------
#define PRINTF_ENABLE               1


#if(1 == PRINTF_ENABLE)

//-------------------------------------------------------------------------------------------------------------------
//printf���ڴ�ӡ������ʹ�õĴ��ڡ����ڲ����ʡ��������ź궨��
//-------------------------------------------------------------------------------------------------------------------
#define DEBUG_UART                  UART_0
#define DEBUG_UART_BAUD             115200
#define DEBUG_UART_TX_PIN           UART0_TX_P14_0
#define DEBUG_UART_RX_PIN           UART0_RX_P14_1

//-------------------------------------------------------------------------------------------------------------------
//  DEBUG_INFO Ϊ 0                  �����������Ϣ
//  DEBUG_INFO Ϊ 1                  ���������Ϣ��������Ϣ�������������ļ���������  ��ҪPRINTF�궨��Ϊ1������Ч���
//-------------------------------------------------------------------------------------------------------------------
#define DEBUG_PRINTF                1

#endif

//������������
#define encoder_A1 GPT12_T2INB_P33_7
#define encoder_B1 GPT12_T2EUDB_P33_6
//�����ֱ�����
#define encoder_A2 GPT12_T4INA_P02_8
#define encoder_B2 GPT12_T4EUDA_P00_9
//����
#define K1 P33_11
#define K2 P23_1
#define K3 P33_13
#define K4 P32_4
#define K0 P33_12

#define KEY0  gpio_get(P33_12)//��ȡ����0
#define KEY1  gpio_get(P33_11)//��ȡ����1
#define KEY2  gpio_get(P23_1)//��ȡ����2
#define KEY3  gpio_get(P33_13)//��ȡ����3
//������
#define BEEP P33_10
//LED
#define LED0 P11_9
#define LED1 P11_11
#define LED2 P10_1
//���PWM
#define DUOJI_Channel ATOM1_CH1_P33_9    //GTM_ATOM1_PWM_DUTY_MAX ��Ҫ����Ϊ100000
//���PWM
#define Motor_balance_Go ATOM0_CH5_P02_5
#define Motor_balance_Dir P02_7
#define Motor_back_Dir P02_6
#define Motor_back_Go  ATOM0_CH4_P02_4





#endif
