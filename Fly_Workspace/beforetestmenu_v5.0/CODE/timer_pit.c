#include "encoder.h"
#include "motor.h"
#include "timer_pit.h"
#include "elec.h"
#include "ym_control.h"
extern int32 MotorDutyA;
extern int32 balance_encoder;
extern float Angle_X_Final;
extern float X_Balance_KP;
extern float X_Balance_KI;
extern float X_Balance_KD;
void timer1_pit_entry(void *parameter)
{
    static uint32 time;
    time++;
    
    //采集陀螺仪数据
    //get_icm20602_gyro_spi();

    if(0 == (time%100))
    {
        //采集编码器数据
        //encoder_get();
        gpio_toggle(LED0);
    }

    if(0 == (time%5))
    {
        Balance();
        lcd_showstr(0,0,"ban_duty:");
        lcd_showint32(10,0,MotorDutyA,5);
        lcd_showstr(0,1,"ban_encoder:");
        lcd_showint32(12,1,balance_encoder,5);
        lcd_showstr(0,2,"Pitch:");
        lcd_showfloat(7,2,Angle_X_Final,2,6);
        lcd_showstr(0,3,"PID:");
        lcd_showfloat(0,4,X_Balance_KP,4,4);
        lcd_showfloat(0,5,X_Balance_KI,2,4);
        lcd_showfloat(0,6,X_Balance_KD,3,4);
        //采集加速度数据
        //get_icm20602_accdata_spi();
        //采集电磁信号
        //elec_get();
        
        //根据电磁信号计算车身位置
        //elec_calculate();
    }
    //控制电机转动
    //motor_control(10000, 10000, 10000, 10000);
    
}


void timer_pit_init(void)
{
    rt_timer_t timer;
    
    //创建一个定时器 周期运行
    timer = rt_timer_create("timer1", timer1_pit_entry, RT_NULL, 1, RT_TIMER_FLAG_PERIODIC);
    
    //启动定时器
    if(RT_NULL != timer)
    {
        rt_timer_start(timer);
    }

    
}
