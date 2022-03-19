/*
 * ym_all_init.c
 *
 *  Created on: 2022��2��13��
 *      Author: huawei
 */

#include "headfile.h"
#include "ym_hardware_init.h"

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
     gpio_init(K5, GPI, 0, PULLUP);    //����
     /**************������**************/
     gpio_init(BEEP,GPO,0,PUSHPULL);   //���
     /**************�����ʼ��***************/
     gtm_pwm_init(Motor_back_Go, 17 * 1000, 0);   //���ֵ��17kHz
     gtm_pwm_init(Motor_back_Return, 17 * 1000, 0);
     gtm_pwm_init(Motor_balance_Go, 12500, 1000);   //ƽ���ֵ��17kHz
     gtm_pwm_init(Motor_balance_Return, 12500, 0);
     //mpu6050��ʼ��
     mpu6050_init();
     //ym_mpu6050_init();
}
