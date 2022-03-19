/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ����Ⱥ��824575535
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file       		main
 * @company	   		�ɶ���ɿƼ����޹�˾
 * @author     		��ɿƼ�(QQ3184284598)
 * @version    		�鿴doc��version�ļ� �汾˵��
 * @Software 		ADS v1.2.2
 * @Target core		TC264D
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2020-3-23
 ********************************************************************************************************************/


#include "Cpu0_Main.h"
#include "ym_all_h.h"
#include "headfile.h"
#define BUZZER_PIN          P33_10          // ���������Ϸ�������Ӧ����

#pragma section all "cpu0_dsram"
//���������#pragma section all restore���֮���ȫ�ֱ���������CPU0��RAM��

// ================������ֲ��ʾ================
// ====== ��ǰ RTThread ������ Cpu 0 ���� ======
// ====== ��ǰ RTThread ������ Cpu 0 ���� ======
// ====== ��ǰ RTThread ������ Cpu 0 ���� ======
// ================������ֲ��ʾ================


//���̵��뵽���֮��Ӧ��ѡ�й���Ȼ����refreshˢ��һ��֮���ٱ���
//����Ĭ������Ϊ�ر��Ż��������Լ��һ�����ѡ��properties->C/C++ Build->Setting
//Ȼ�����Ҳ�Ĵ������ҵ�C/C++ Compiler->Optimization->Optimization level�������Ż��ȼ�
//һ��Ĭ���½����Ĺ��̶���Ĭ�Ͽ�2���Ż�����˴��Ҳ��������Ϊ2���Ż�

//����TCϵ��Ĭ���ǲ�֧���ж�Ƕ�׵ģ�ϣ��֧���ж�Ƕ����Ҫ���ж���ʹ��enableInterrupts();�������ж�Ƕ��
//�򵥵�˵ʵ���Ͻ����жϺ�TCϵ�е�Ӳ���Զ�������disableInterrupts();���ܾ���Ӧ�κε��жϣ������Ҫ�����Լ��ֶ�����enableInterrupts();�������жϵ���Ӧ��
//��������

rt_sem_t camera_sem;

// ================������ֲ��ʾ================
// ====== ��ǰ RTThread ������ Cpu 0 ���� ======
// ====== ��ǰ RTThread ������ Cpu 0 ���� ======
// ====== ��ǰ RTThread ������ Cpu 0 ���� ======
// ================������ֲ��ʾ================


int main(void)
{


    //�ȴ����к��ĳ�ʼ�����
    IfxCpu_emitEvent(&g_cpuSyncEvent);
    IfxCpu_waitEvent(&g_cpuSyncEvent, 0xFFFF);
    //camera_sem = rt_sem_create("camera", 0, RT_IPC_FLAG_FIFO);
    ym_hardware_init();
    //mt9v03x_init();
    //�����ǳ�ʼ��
    //mpu6050_init();
    //��ʾ�̳߳�ʼ��
    //display_init();
    //��������ʼ��
    //encoder_init();
    //�����ʼ��
    //buzzer_init();
    //��ť��ʼ��
    //button_init();
    //�����ʼ��
    //motor_init();
    //��ų�ʼ��
    //elec_init();
    //��ʱ���̳߳�ʼ��
    //timer_pit_init();
    //ʹ��CCU6_0ģ���ͨ��0 ����һ�� 5ms�������ж�
    pit_interrupt_ms(CCU6_0, PIT_CH0, 5);
    pit_interrupt_ms(CCU6_0, PIT_CH1, 5);
     //gpio_set(BUZZER_PIN, 1);    //�򿪷�����
    while(1)
    {
        //�ȴ�����ͷ�ɼ����
        //rt_sem_take(camera_sem, RT_WAITING_FOREVER);
        //��ʼ��������ͷͼ��

        //���������Ҫ����־λ��0
        //mt9v03x_finish_flag = 0;
    }
}

#pragma section all restore


