/*
 * ym_control.c
 *
 *  Created on: 2022年2月14日
 *      Author: huawei
 */
#include "ym_control.h"
#include "headfile.h"
#include "ym_kalman.h"
#define Servo_Delta 160
//#define banlance_encoder GPT12_T2
//#define back_encoder     GPT12_T4
extern float Angle_X_Final;
extern float Gyro_x;
int32 balance_encoder,back_encoder;
uint8  Start_Flag=0;                    //启动标志
int16 encoder_now;//编码器
float Pitch_Zero=1.0;
float Zero_error=0.0;              // Pitch偏差值,Pitch_error=0.00;//设置Pitch轴角度零点
 float X_Balance_KP=0,X_Balance_KI=0,X_Balance_KD=0;  // 平衡环PID  Pitch轴角度环PID参数 动量轮
 float X_Velocity_KP=0,X_Velocity_KI=0;//动量轮电机速度环PI参数
 float Balance_Kp=0,Balance_Ki=0,Balance_Kd=0,Motor_Kp=0,Motor_Ki=0;//舵机PID参数 后轮电机PID参数

int32 Velocity;
int32 PWM_X,PWM_accel;                  // PWM中间量
int32 Steer_PWM;
int32 PWM_Steer;
int32 MotorDutyA = 0;                // 飞轮电机驱动占空比数值
int32 MotorDutyB = 0;                // 后轮电机驱动占空比数值
int32  Motor_Bias, Motor_Last_Bias, Motor_Integration; // 电机所用参数
float   Integration;
float Pitch; short gyro[3];
float   Integration;
unsigned char Flag_Stop = 0, Flag_Show, Flag_Imu;          // 停车，显示，IMU完成标志位
 int32 Vat;
 int32 Vbat;

//舵机左满偏值和右满偏值需要测定
int32 MaxSteering = 960, MinSteering = 640;   //舵机保护左满偏/舵机右满偏
int32 MidSteering=800;//舵机中值
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
    PWM_X = X_balance_Control(Pitch,Pitch_Zero,gyro[0]);// 动量轮电机控制左右倾角
    PWM_accel = - Velocity_Control(-balance_encoder);          // 动量轮电机速度环正反馈
    MotorDutyA = -(PWM_X-PWM_accel);
    if(MotorDutyA>7000) MotorDutyA=7000;        // 动量轮电机限幅
    else if(MotorDutyA<-7000) MotorDutyA=-7000; // 动量轮电机限幅
    else if(MotorDutyA<-0) MotorDutyA -=800;    // 死区
    else if(MotorDutyA>0) MotorDutyA+=800;      // 死区
    if((MotorDutyA<1000)&&(MotorDutyA>-1000))
            MotorDutyA=0;
    ///////// 舵机电机控制///////
     Steer_PWM = SBB_Get_BalancePID(Pitch, gyro[0]);               // PID计算单车平衡的PWM数值
     if( Steer_PWM <-Servo_Delta)  Steer_PWM = -Servo_Delta;  // 舵机角度限制
     else if(Steer_PWM > Servo_Delta)  Steer_PWM = Servo_Delta;  // 舵机角度限制
     PWM_Steer = MidSteering + Steer_PWM;                      // 转换为舵机控制PWM
     MotorDutyB = SBB_Get_MotorPI(back_encoder, Velocity)/5;           // 电机增量式PI控制
    if((Pitch > 10) || (Pitch < -10))       // 摔倒停车判断
       Flag_Stop = 1;
   //if(Vbat<2500) Flag_Stop = 1;            // 电压低于约11V，停止输出，防止电池过放
   else Flag_Stop = 0;

    if(Flag_Stop == 1)                       // 停车
    {
        MotorDutyA = 0;                      // 电机关闭
        Integration = 0;                     // 积分参数归零
    }
    Set_balance_motor(MotorDutyA);       // 电机控制
    Set_back_motor(MotorDutyB);       // 电机控制
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
    if(Start_Flag==1) Encoder_Integral=0,Encoder=0,Velocity=0;                //停止时参数清零
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
            gpio_set(Motor_back_Dir, 0);
            //pwm_duty(Motor_back_Return, 0);                  // 同一时间 一个电机只能输出一个PWM 另一通道保持低电平
        }
        else
        {
            pwm_duty(Motor_back_Go, (-PWM));                           //反转
            gpio_set(Motor_back_Dir, 1);
            //pwm_duty(Motor_back_Return, (-PWM));                  // 同一时间 一个电机只能输出一个PWM 另一通道保持低电平
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
            gpio_set(Motor_balance_Dir, 0);
            //pwm_duty(Motor_balance_Return,0);                  // 同一时间 一个电机只能输出一个PWM 另一通道保持低电平
        }
        else
        {
            pwm_duty(Motor_balance_Go, (-PWM));                           //反转
            gpio_set(Motor_balance_Dir, 1);
            //pwm_duty(Motor_balance_Return, (-PWM));                  // 同一时间 一个电机只能输出一个PWM 另一通道保持低电平
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
/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
【函数名】int SBB_Get_BalancePID(float Angle,float Gyro)
【功  能】舵机打角控制PID
【参数值】float Angle,电单车左右倾角
【参数值】float Gyro 电单车左右角速度
【返回值】小车平衡，舵机转向PID
【作  者】chiusir
【最后更新】2021年1月22日
【软件版本】V1.0
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
int SBB_Get_BalancePID(float Angle,float Gyro)
{
    float  Bias;
    int32 SBB_BalancePID;
    Bias = Angle - Zero_error;     // 求出平衡的角度中值和此时横滚角的偏差
    Integration += Bias;           // 积分
    if(Integration<-380)      Integration=-380; //限幅
    else if(Integration>380)  Integration= 380; //限幅
    //===计算平衡控制的舵机PWM  PID控制 kp是P系数 ki式I系数 kd是D系数
    SBB_BalancePID = Balance_Kp * Bias + Balance_Ki*Integration + Balance_Kd*Gyro;
    return SBB_BalancePID;
}
/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
【函数名】int SBB_Get_MotorPI (int Encoder,int Target)
【功  能】电机控制增量式PI
【参数值】int Encoder 编码器脉采集的冲数
【参数值】int Target  期望脉冲数
【返回值】电机PWM
【作  者】chiusir
【最后更新】2021年1月22日
【软件版本】V1.0
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
int SBB_Get_MotorPI (int32 Encoder,int32 Target)
{
    static int32 Pwm;
    Motor_Bias = Encoder - Target;            // 计算偏差
    Pwm += Motor_Kp * (Motor_Bias - Motor_Last_Bias) + Motor_Ki * Motor_Bias;
    // ==增量式PI控制器
    if(Pwm > 7000) Pwm = 7000;               // 限幅
    else if(Pwm < -7000)Pwm = -7000;         // 限幅
    Motor_Last_Bias = Motor_Bias;            // 保存上一次偏差
    return Pwm;                              // 增量输出
}


