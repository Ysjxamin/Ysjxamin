/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：三群：824575535
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		main
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ3184284598)
 * @version    		查看doc内version文件 版本说明
 * @Software 		ADS v1.2.2
 * @Target core		TC264D
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2020-3-23
 ********************************************************************************************************************/


#include "Cpu0_Main.h"
#include "ym_all_h.h"
#include "headfile.h"
#define BUZZER_PIN          P33_10          // 定义主板上蜂鸣器对应引脚

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
//将本语句与#pragma section all restore语句之间的全局变量都放在CPU0的RAM中

// ================运行移植提示================
// ====== 当前 RTThread 仅能在 Cpu 0 运行 ======
// ====== 当前 RTThread 仅能在 Cpu 0 运行 ======
// ====== 当前 RTThread 仅能在 Cpu 0 运行 ======
// ================运行移植提示================


//工程导入到软件之后，应该选中工程然后点击refresh刷新一下之后再编译
//工程默认设置为关闭优化，可以自己右击工程选择properties->C/C++ Build->Setting
//然后在右侧的窗口中找到C/C++ Compiler->Optimization->Optimization level处设置优化等级
//一般默认新建立的工程都会默认开2级优化，因此大家也可以设置为2级优化

//对于TC系列默认是不支持中断嵌套的，希望支持中断嵌套需要在中断内使用enableInterrupts();来开启中断嵌套
//简单点说实际上进入中断后TC系列的硬件自动调用了disableInterrupts();来拒绝响应任何的中断，因此需要我们自己手动调用enableInterrupts();来开启中断的响应。
//函数声明

rt_sem_t camera_sem;

// ================运行移植提示================
// ====== 当前 RTThread 仅能在 Cpu 0 运行 ======
// ====== 当前 RTThread 仅能在 Cpu 0 运行 ======
// ====== 当前 RTThread 仅能在 Cpu 0 运行 ======
// ================运行移植提示================


int main(void)
{


    //等待所有核心初始化完毕
    IfxCpu_emitEvent(&g_cpuSyncEvent);
    IfxCpu_waitEvent(&g_cpuSyncEvent, 0xFFFF);
    //camera_sem = rt_sem_create("camera", 0, RT_IPC_FLAG_FIFO);
    ym_hardware_init();
    //mt9v03x_init();
    //陀螺仪初始化
    //mpu6050_init();
    //显示线程初始化
    //display_init();
    //编码器初始化
    //encoder_init();
    //邮箱初始化
    //buzzer_init();
    //按钮初始化
    //button_init();
    //电机初始化
    //motor_init();
    //电磁初始化
    //elec_init();
    //定时器线程初始化
    //timer_pit_init();
    //使用CCU6_0模块的通道0 产生一个 5ms的周期中断
    pit_interrupt_ms(CCU6_0, PIT_CH0, 5);
    //choose_menu();
    //pit_interrupt_ms(CCU6_0, PIT_CH1, 5);
     //gpio_set(BUZZER_PIN, 1);    //打开蜂鸣器
    while(1)
    {

               gpio_toggle(LED2);       //电平翻转,LED闪烁;
               if (gpio_get(K1) == 0 )      //按下KEY1键，动量轮电机占空比归零
                       {
                          systick_delay_ms(STM0, 100);
                          if(gpio_get(K1) == 0)
                         {
                           //按键处理
                           gpio_set(BEEP, 1);    //打开蜂鸣器
                           systick_delay_ms(STM0, 100);//上电延时
                           gpio_set(BEEP, 0);    //关闭蜂鸣器
                           //X_Balance_KP+=20;
                           MotorDutyB+=200;

                           gpio_toggle(LED0);

                         }
                          while(!gpio_get(K1));
                       }
                       if (gpio_get(K2) == 0 )      //按下KEY2键，平衡轮电机占空比加大1000 KP增大100
                       {

                           systick_delay_ms(STM0, 100);
                                      if(gpio_get(K2) == 0)
                                    {
                                      //按键处理
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
                       if (gpio_get(K3) == 0 )      //按下KEY3键，平衡轮电机占空比减小1000 KP减小100
                       {
                           systick_delay_ms(STM0, 100);
                            if(gpio_get(K3) == 0)
                           {
                                 //按键处理
                                X_Balance_KD+=5;

                                gpio_toggle(LED0);
                            }
                            while(!gpio_get(K3));
                       }
                       if (gpio_get(K4) == 0 )      //按下KEY3键，平衡轮电机死机后开转 KD增大1
                       {
                           systick_delay_ms(STM0, 100);
                            if(gpio_get(K4) == 0)
                           {
                                 //按键处理
                                X_Velocity_KI+=0.5;
                               /* back_duty+=100;
                                Set_back_motor(back_duty);*/
                                gpio_toggle(LED0);

                            }
                            while(!gpio_get(K4));
                       }
                       if (gpio_get(K0) == 0 )      //按下KEY3键，平衡轮电机占空比->1000 KD减小1
                       {
                           systick_delay_ms(STM0, 100);
                            if(gpio_get(K0) == 0)
                           {
                                 //按键处理
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

                      gpio_toggle(LED2);       //电平翻转,LED闪烁;
        //等待摄像头采集完毕
        //rt_sem_take(camera_sem, RT_WAITING_FOREVER);
        //开始处理摄像头图像

        //处理完成需要将标志位置0
        //mt9v03x_finish_flag = 0;
    }
}

#pragma section all restore


