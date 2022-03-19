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
    pit_interrupt_ms(CCU6_0, PIT_CH1, 5);
     //gpio_set(BUZZER_PIN, 1);    //打开蜂鸣器
    while(1)
    {
        //等待摄像头采集完毕
        //rt_sem_take(camera_sem, RT_WAITING_FOREVER);
        //开始处理摄像头图像

        //处理完成需要将标志位置0
        //mt9v03x_finish_flag = 0;
    }
}

#pragma section all restore


