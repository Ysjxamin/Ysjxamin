/*
 * ym_control.c
 *
 *  Created on: 2022年2月14日
 *      Author: huawei
 */
#include "ym_control.h"
#include "headfile.h"
#include "ym_kalman.h"
//#define banlance_encoder GPT12_T2
//#define back_encoder     GPT12_T4
extern float Angle_X_Final;
extern float Gyro_x;
int32 balance_encoder,back_encoder;
uint8  Start_Flag=0;                    //启动标志
int16 encoder_now;//编码器
float Pitch_Zero=7.0,Pitch_error=0.00;//设置Pitch轴角度零点
float X_Balance_KP=1900.001,X_Balance_KI=3.2001,X_Balance_KD=60.001;  // 平衡环PID  Pitch轴角度环PID参数 动量轮
float X_Velocity_KP=90,X_Velocity_KI=100;//动量轮电机速度环PI参数
int PWM_X,PWM_accel;                  // PWM中间量
int32 MotorDutyA = 0;                // 飞轮电机驱动占空比数值
int32 MotorDutyB = 0;                // 后轮电机驱动占空比数值
short  Motor_Bias, Motor_Last_Bias, Motor_Integration; // 电机所用参数
float   Integration;
float Pitch; short gyro[3];
float   Integration;
unsigned char Flag_Stop = 0, Flag_Show, Flag_Imu;          // 停车，显示，IMU完成标志位
 int Vat;
 int Vbat;
//舵机左满偏值和右满偏值需要测定
int16 MaxSteering = 960, MinSteering = 640;   //舵机保护左满偏/舵机右满偏
int16 MidSteering=800;//舵机中值
/**************************************************************************
 *  @brief      Balance函数
 *  @note       动量平衡轮平衡函数
 *  @date       2021-07-09
 *  @author     aming
**************************************************************************/
void Balance(void)
{
    /* 获取编码器值 */
    get_encoder_value();//动量轮反馈和后轮反馈
    /* 读取pitch */
    MPU6050();
    Pitch=Angle_X_Final;//pitch 左负右正
    gyro[0]=Gyro_x;
    //Pitch_Zero=???;
    /////// 动量轮控制//////////
    /*PWM_X = X_balance_Control(Pitch,Pitch_Zero,gyro[0]);// 动量轮电机控制左右倾角
    PWM_accel = - Velocity_Control(-balance_encoder);          // 动量轮电机速度环正反馈
    MotorDutyA = -(PWM_X-PWM_accel);*/
    if(MotorDutyA>8000) MotorDutyA=8000;        // 动量轮电机限幅
    else if(MotorDutyA<-8000) MotorDutyA=-8000; // 动量轮电机限幅
    else if(MotorDutyA<-0) MotorDutyA -=800;    // 死区
    else if(MotorDutyA>0) MotorDutyA+=800;      // 死区
    if((MotorDutyA<1000)&&(MotorDutyA>-1000))
            MotorDutyA=0;

    if((Pitch > 20) || (Pitch < -20))       // 摔倒停车判断
       Flag_Stop = 1;
   //if(Vbat<2500) Flag_Stop = 1;            // 电压低于约11V，停止输出，防止电池过放
   else Flag_Stop = 0;

    if(Flag_Stop == 1)                       // 停车
    {
        MotorDutyA = 0;                      // 电机关闭
        Integration = 0;                     // 积分参数归零
    }
    Set_balance_motor(MotorDutyA);       // 电机控制
}

/**************************************************************************
 *  @brief      filtering函数
 *  @note       一阶低通滤波函数
 *  @date       2021-07-09
 *  @author     aming
**************************************************************************/
int32 filtering(int32 new_data)
{
    static int32 old_data;
    new_data = 0.7*old_data + 0.3* new_data;
    old_data = new_data;
    return new_data;
}
/*******************************************************************************
 *  @brief      encoder函数
 *  @note       编码器值获取函数
 *  @date       2021-07-09
 *  @author     aming
 *  @tips       最大为10000，pwm比例是 PWM/10000 *100%
 ******************************************************************************/
void get_encoder_value(void)
{

        balance_encoder = gpt12_get(GPT12_T2);
        gpt12_clear(GPT12_T2);

        back_encoder=gpt12_get(GPT12_T4);
        gpt12_clear(GPT12_T4);
/*对编码器获取值的处理
 *
 *
 *
 对编码器获取值的处理*/
}
/**************************************************************************
X轴平衡PID控制,角度环
**************************************************************************/
float X_balance_Control(float Angle,float Angle_Zero,float Gyro)
{
     float PWM,Bias;
     static float error;
     Bias=Angle-Pitch_Zero;                                            //获取偏差
     error+=Bias;                                                      //偏差累积
     if(error>+30) error=+30;                                          //积分限幅
     if(error<-30) error=-30;                                          //积分限幅
     PWM=X_Balance_KP*Bias + X_Balance_KI*error + Gyro*X_Balance_KD;   //获取最终数值
     return PWM;
}
/**************************************************************************
动量轮速度PI控制,速度正反馈环
**************************************************************************/
float Velocity_Control(int32 encoder)
{
    static float Encoder,Encoder_Integral;
    float Velocity,Encoder_Least;

    Encoder_Least = encoder;                                                  //速度滤波
    Encoder *= 0.7;                                                           //一阶低通滤波器
    Encoder += Encoder_Least*0.3;                                             //一阶低通滤波器
    Encoder_Integral += Encoder;                                              //积分出位移
    if(Encoder_Integral > +2000) Encoder_Integral = +2000;                    //积分限幅
    if(Encoder_Integral < -2000) Encoder_Integral = -2000;                    //积分限幅
    Velocity = Encoder * X_Velocity_KP + Encoder_Integral * X_Velocity_KI/100;//获取最终数值
    if(Start_Flag==0) Encoder_Integral=0,Encoder=0,Velocity=0;                //停止时参数清零
      return Velocity;
}
/*******************************************************************************
 *  @brief      Set_back_motor函数
 *  @note       后轮马达电机转动函数
 *  @date       2021-07-09
 *  @author     aming
 *  @tips       最大为10000，pwm比例是 PWM/10000 *100%
 ******************************************************************************/
void Set_back_motor(int32 PWM)
{
        if(PWM>=0)
        {
            pwm_duty(Motor_back_Go, PWM);                    //正转
            pwm_duty(Motor_back_Return, 0);                  // 同一时间 一个电机只能输出一个PWM 另一通道保持低电平
        }
        else
        {
            pwm_duty(Motor_back_Go, 0);                           //反转
            pwm_duty(Motor_back_Return, (-PWM));                  // 同一时间 一个电机只能输出一个PWM 另一通道保持低电平
        }
}
/*******************************************************************************
 *  @brief      Set_balance_motor函数
 *  @note       动量平衡轮电机转动函数
 *  @date       2021-07-09
 *  @author     aming
 *  @tips       最大为10000，pwm比例是 PWM/10000 *100%
 ******************************************************************************/
void Set_balance_motor(int32 PWM)
{
        if(PWM>=0)
        {
            pwm_duty(Motor_balance_Go, PWM);                    //正转
            pwm_duty(Motor_balance_Return, 0);                  // 同一时间 一个电机只能输出一个PWM 另一通道保持低电平
        }
        else
        {
            pwm_duty(Motor_balance_Go, 0);                           //反转
            pwm_duty(Motor_balance_Return, (-PWM));                  // 同一时间 一个电机只能输出一个PWM 另一通道保持低电平
        }
}
/*******************************************************************************
 *  @brief      Set_steer函数
 *  @note       函数
 *  @date       2021-07-09
 *  @author     aming
 *  @tips       最大为10000，pwm比例是 PWM/10000 *100%
 ******************************************************************************/
void Set_steer(int32 PWM)
{
    if(PWM>MaxSteering)
    {    PWM=MaxSteering;   }
    if(PWM<MinSteering)
    {    PWM=MinSteering;   }

    pwm_duty(DUOJI_Channel, PWM);
}

