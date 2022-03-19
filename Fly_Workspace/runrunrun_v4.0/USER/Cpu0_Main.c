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
 extern int32 MotorDutyA;
 extern int32 MotorDutyB;
 extern int32 balance_encoder;
 extern float Angle_X_Final;
 extern float X_Balance_KP;
 extern float X_Balance_KI;
 extern float X_Balance_KD;
 extern float X_Velocity_KP;
 extern float X_Velocity_KI;
 extern unsigned char Flag_Stop;
 extern float Pitch_Zero;
 extern int32 MidSteering;
  int32 back_duty;
 int32 steer_duty;
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
    //choose_menu();
    //pit_interrupt_ms(CCU6_0, PIT_CH1, 5);
     //gpio_set(BUZZER_PIN, 1);    //�򿪷�����
    while(1)
    {

               gpio_toggle(LED2);       //��ƽ��ת,LED��˸;
               if (gpio_get(K1) == 0 )      //����KEY1���������ֵ��ռ�ձȹ���
                       {
                          systick_delay_ms(STM0, 100);
                          if(gpio_get(K1) == 0)
                         {
                           //��������
                           gpio_set(BEEP, 1);    //�򿪷�����
                           systick_delay_ms(STM0, 100);//�ϵ���ʱ
                           gpio_set(BEEP, 0);    //�رշ�����
                           //X_Balance_KP+=20;
                           MotorDutyB+=200;

                           gpio_toggle(LED0);

                         }
                          while(!gpio_get(K1));
                       }
                       if (gpio_get(K2) == 0 )      //����KEY2����ƽ���ֵ��ռ�ձȼӴ�1000 KP����100
                       {

                           systick_delay_ms(STM0, 100);
                                      if(gpio_get(K2) == 0)
                                    {
                                      //��������
                                gpio_toggle(LED0);
                                  X_Balance_KP=0;
                                  X_Balance_KI=0;
                                  X_Balance_KD=0;
                                  X_Velocity_KP=0;
                                  X_Velocity_KI=0;
                                //X_Velocity_KP-=5;

                                     }
                                while(!gpio_get(K2));
                       }
                       if (gpio_get(K3) == 0 )      //����KEY3����ƽ���ֵ��ռ�ձȼ�С1000 KP��С100
                       {
                           systick_delay_ms(STM0, 100);
                            if(gpio_get(K3) == 0)
                           {
                                 //��������
                                X_Balance_KD+=5;

                                gpio_toggle(LED0);
                            }
                            while(!gpio_get(K3));
                       }
                       if (gpio_get(K4) == 0 )      //����KEY3����ƽ���ֵ��������ת KD����1
                       {
                           systick_delay_ms(STM0, 100);
                            if(gpio_get(K4) == 0)
                           {
                                 //��������
                                X_Velocity_KI+=0.5;
                               /* back_duty+=100;
                                Set_back_motor(back_duty);*/
                                gpio_toggle(LED0);

                            }
                            while(!gpio_get(K4));
                       }
                       if (gpio_get(K0) == 0 )      //����KEY3����ƽ���ֵ��ռ�ձ�->1000 KD��С1
                       {
                           systick_delay_ms(STM0, 100);
                            if(gpio_get(K0) == 0)
                           {
                                 //��������
                                gpio_toggle(LED0);
                               X_Balance_KD-=5;

                            }
                            while(!gpio_get(K0));
                       }
              lcd_showstr(0,0,"ban_duty:");
                       lcd_showint32(80,0,MotorDutyA,5);
                       lcd_showstr(0,1,"ban_encoder:");
                       lcd_showint32(100,1,balance_encoder,5);
                       lcd_showstr(0,2,"Pitch: ");
                       lcd_showfloat(50,2,Angle_X_Final,2,6);
                       //lcd_showstr(0,3,"PID:");
                       lcd_showfloat(0,3,X_Velocity_KP,2,4);
                       lcd_showfloat(0,4,X_Velocity_KI,2,4);
                       lcd_showfloat(0,5,X_Balance_KP,4,4);
                       lcd_showfloat(0,6,X_Balance_KI,2,4);
                       lcd_showfloat(0,7,X_Balance_KD,3,4);

                      gpio_toggle(LED2);       //��ƽ��ת,LED��˸;
        //�ȴ�����ͷ�ɼ����
        //rt_sem_take(camera_sem, RT_WAITING_FOREVER);
        //��ʼ��������ͷͼ��

        //���������Ҫ����־λ��0
        //mt9v03x_finish_flag = 0;
    }
}

#pragma section all restore


