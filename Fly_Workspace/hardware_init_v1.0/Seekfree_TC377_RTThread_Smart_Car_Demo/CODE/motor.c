#include "motor.h"

#define MOTOR1_DIR   P21_2              //定义1电机方向控制引脚
#define MOTOR1_PWM   ATOM0_CH1_P21_3    //定义1电机PWM引脚

#define MOTOR2_DIR   P21_4              //定义2电机方向控制引脚
#define MOTOR2_PWM   ATOM0_CH3_P21_5    //定义2电机PWM引脚

#define MOTOR3_DIR   P02_4              //定义3电机方向控制引脚
#define MOTOR3_PWM   ATOM0_CH5_P02_5    //定义3电机PWM引脚

#define MOTOR4_DIR   P02_6              //定义4电机方向控制引脚
#define MOTOR4_PWM   ATOM0_CH7_P02_7    //定义4电机PWM引脚

void motor_init(void)
{

    //卓大大的推文中，建议电磁组电机频率选用13K-17K

    //在使用本例程请务必确认所使用的驱动类型
    //本例程只支持DRV8701E驱动

    //初始化PWM引脚
    gtm_pwm_init(MOTOR1_PWM, 17000, 0);
    gtm_pwm_init(MOTOR2_PWM, 17000, 0);
    gtm_pwm_init(MOTOR3_PWM, 17000, 0);
    gtm_pwm_init(MOTOR4_PWM, 17000, 0);

    //初始化方向控制引脚
    gpio_init(MOTOR1_DIR, GPO, 0, PUSHPULL);
    gpio_init(MOTOR2_DIR, GPO, 0, PUSHPULL);
    gpio_init(MOTOR3_DIR, GPO, 0, PUSHPULL);
    gpio_init(MOTOR4_DIR, GPO, 0, PUSHPULL);
}

void motor_pid(int16 expect_speed)
{
    
}


void motor_control(int32 duty_m1, int32 duty_m2, int32 duty_m3, int32 duty_m4)
{
    //对占空比限幅
    duty_m1 = (int32)limit((float)duty_m1, GTM_ATOM0_PWM_DUTY_MAX);
    duty_m2 = (int32)limit((float)duty_m2, GTM_ATOM0_PWM_DUTY_MAX);
    duty_m3 = (int32)limit((float)duty_m3, GTM_ATOM0_PWM_DUTY_MAX);
    duty_m4 = (int32)limit((float)duty_m4, GTM_ATOM0_PWM_DUTY_MAX);

    if(duty_m1 >= 0)                                        // 左侧正转
    {
        gpio_set(MOTOR1_DIR, GPIO_LOW);                     // DIR输出高电平
        pwm_duty(MOTOR1_PWM, duty_m1);                    // 计算占空比
    }
    else													// 左侧反转
    {
        gpio_set(MOTOR1_DIR, GPIO_HIGH);                    // DIR输出高电平
        pwm_duty(MOTOR1_PWM, -duty_m1);                    // 计算占空比
    }

    if(duty_m2 >= 0)                                        // 左侧正转
    {
        gpio_set(MOTOR2_DIR, GPIO_LOW);                     // DIR输出高电平
        pwm_duty(MOTOR2_PWM, duty_m2);                       // 计算占空比
    }
    else                                                    // 左侧反转
    {
        gpio_set(MOTOR2_DIR, GPIO_HIGH);                    // DIR输出高电平
        pwm_duty(MOTOR2_PWM, -duty_m2);                   // 计算占空比
    }

    if(duty_m3 >= 0)                                        // 左侧正转
    {
        gpio_set(MOTOR3_DIR, GPIO_LOW);                     // DIR输出高电平
        pwm_duty(MOTOR3_PWM, duty_m3);                      // 计算占空比
    }
    else                                                    // 左侧反转
    {
        gpio_set(MOTOR3_DIR, GPIO_HIGH);                    // DIR输出高电平
        pwm_duty(MOTOR3_PWM, -duty_m3);                     // 计算占空比
    }

    if(duty_m4 >= 0)                                        // 左侧正转
    {
        gpio_set(MOTOR4_DIR, GPIO_LOW);                     // DIR输出高电平
        pwm_duty(MOTOR4_PWM, duty_m4);                        // 计算占空比
    }
    else                                                    // 左侧反转
    {
        gpio_set(MOTOR4_DIR, GPIO_HIGH);                    // DIR输出高电平
        pwm_duty(MOTOR4_PWM, -duty_m4);                      // 计算占空比
    }
}
