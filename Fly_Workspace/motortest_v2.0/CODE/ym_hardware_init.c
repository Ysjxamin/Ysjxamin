/*
 * ym_all_init.c
 *
 *  Created on: 2022年2月13日
 *      Author: huawei
 */

#include "headfile.h"
#include "ym_hardware_init.h"

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
     gpio_init(K5, GPI, 0, PULLUP);    //输入
     /**************蜂鸣器**************/
     gpio_init(BEEP,GPO,0,PUSHPULL);   //输出
     /**************电机初始化***************/
     gtm_pwm_init(Motor_back_Go, 17 * 1000, 0);   //后轮电机17kHz
     gtm_pwm_init(Motor_back_Return, 17 * 1000, 0);
     gtm_pwm_init(Motor_balance_Go, 12500, 1000);   //平衡轮电机17kHz
     gtm_pwm_init(Motor_balance_Return, 12500, 0);
     //mpu6050初始化
     mpu6050_init();
     //ym_mpu6050_init();
}
