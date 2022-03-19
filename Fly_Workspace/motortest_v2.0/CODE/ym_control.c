/*
 * ym_control.c
 *
 *  Created on: 2022��2��14��
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
uint8  Start_Flag=0;                    //������־
int16 encoder_now;//������
float Pitch_Zero=7.0,Pitch_error=0.00;//����Pitch��Ƕ����
float X_Balance_KP=1900.001,X_Balance_KI=3.2001,X_Balance_KD=60.001;  // ƽ�⻷PID  Pitch��ǶȻ�PID���� ������
float X_Velocity_KP=90,X_Velocity_KI=100;//�����ֵ���ٶȻ�PI����
int PWM_X,PWM_accel;                  // PWM�м���
int32 MotorDutyA = 0;                // ���ֵ������ռ�ձ���ֵ
int32 MotorDutyB = 0;                // ���ֵ������ռ�ձ���ֵ
short  Motor_Bias, Motor_Last_Bias, Motor_Integration; // ������ò���
float   Integration;
float Pitch; short gyro[3];
float   Integration;
unsigned char Flag_Stop = 0, Flag_Show, Flag_Imu;          // ͣ������ʾ��IMU��ɱ�־λ
 int Vat;
 int Vbat;
//�������ƫֵ������ƫֵ��Ҫ�ⶨ
int16 MaxSteering = 960, MinSteering = 640;   //�����������ƫ/�������ƫ
int16 MidSteering=800;//�����ֵ
/**************************************************************************
 *  @brief      Balance����
 *  @note       ����ƽ����ƽ�⺯��
 *  @date       2021-07-09
 *  @author     aming
**************************************************************************/
void Balance(void)
{
    /* ��ȡ������ֵ */
    get_encoder_value();//�����ַ����ͺ��ַ���
    /* ��ȡpitch */
    MPU6050();
    Pitch=Angle_X_Final;//pitch ������
    gyro[0]=Gyro_x;
    //Pitch_Zero=???;
    /////// �����ֿ���//////////
    /*PWM_X = X_balance_Control(Pitch,Pitch_Zero,gyro[0]);// �����ֵ�������������
    PWM_accel = - Velocity_Control(-balance_encoder);          // �����ֵ���ٶȻ�������
    MotorDutyA = -(PWM_X-PWM_accel);*/
    if(MotorDutyA>8000) MotorDutyA=8000;        // �����ֵ���޷�
    else if(MotorDutyA<-8000) MotorDutyA=-8000; // �����ֵ���޷�
    else if(MotorDutyA<-0) MotorDutyA -=800;    // ����
    else if(MotorDutyA>0) MotorDutyA+=800;      // ����
    if((MotorDutyA<1000)&&(MotorDutyA>-1000))
            MotorDutyA=0;

    if((Pitch > 20) || (Pitch < -20))       // ˤ��ͣ���ж�
       Flag_Stop = 1;
   //if(Vbat<2500) Flag_Stop = 1;            // ��ѹ����Լ11V��ֹͣ�������ֹ��ع���
   else Flag_Stop = 0;

    if(Flag_Stop == 1)                       // ͣ��
    {
        MotorDutyA = 0;                      // ����ر�
        Integration = 0;                     // ���ֲ�������
    }
    Set_balance_motor(MotorDutyA);       // �������
}

/**************************************************************************
 *  @brief      filtering����
 *  @note       һ�׵�ͨ�˲�����
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
 *  @brief      encoder����
 *  @note       ������ֵ��ȡ����
 *  @date       2021-07-09
 *  @author     aming
 *  @tips       ���Ϊ10000��pwm������ PWM/10000 *100%
 ******************************************************************************/
void get_encoder_value(void)
{

        balance_encoder = gpt12_get(GPT12_T2);
        gpt12_clear(GPT12_T2);

        back_encoder=gpt12_get(GPT12_T4);
        gpt12_clear(GPT12_T4);
/*�Ա�������ȡֵ�Ĵ���
 *
 *
 *
 �Ա�������ȡֵ�Ĵ���*/
}
/**************************************************************************
X��ƽ��PID����,�ǶȻ�
**************************************************************************/
float X_balance_Control(float Angle,float Angle_Zero,float Gyro)
{
     float PWM,Bias;
     static float error;
     Bias=Angle-Pitch_Zero;                                            //��ȡƫ��
     error+=Bias;                                                      //ƫ���ۻ�
     if(error>+30) error=+30;                                          //�����޷�
     if(error<-30) error=-30;                                          //�����޷�
     PWM=X_Balance_KP*Bias + X_Balance_KI*error + Gyro*X_Balance_KD;   //��ȡ������ֵ
     return PWM;
}
/**************************************************************************
�������ٶ�PI����,�ٶ���������
**************************************************************************/
float Velocity_Control(int32 encoder)
{
    static float Encoder,Encoder_Integral;
    float Velocity,Encoder_Least;

    Encoder_Least = encoder;                                                  //�ٶ��˲�
    Encoder *= 0.7;                                                           //һ�׵�ͨ�˲���
    Encoder += Encoder_Least*0.3;                                             //һ�׵�ͨ�˲���
    Encoder_Integral += Encoder;                                              //���ֳ�λ��
    if(Encoder_Integral > +2000) Encoder_Integral = +2000;                    //�����޷�
    if(Encoder_Integral < -2000) Encoder_Integral = -2000;                    //�����޷�
    Velocity = Encoder * X_Velocity_KP + Encoder_Integral * X_Velocity_KI/100;//��ȡ������ֵ
    if(Start_Flag==0) Encoder_Integral=0,Encoder=0,Velocity=0;                //ֹͣʱ��������
      return Velocity;
}
/*******************************************************************************
 *  @brief      Set_back_motor����
 *  @note       ���������ת������
 *  @date       2021-07-09
 *  @author     aming
 *  @tips       ���Ϊ10000��pwm������ PWM/10000 *100%
 ******************************************************************************/
void Set_back_motor(int32 PWM)
{
        if(PWM>=0)
        {
            pwm_duty(Motor_back_Go, PWM);                    //��ת
            pwm_duty(Motor_back_Return, 0);                  // ͬһʱ�� һ�����ֻ�����һ��PWM ��һͨ�����ֵ͵�ƽ
        }
        else
        {
            pwm_duty(Motor_back_Go, 0);                           //��ת
            pwm_duty(Motor_back_Return, (-PWM));                  // ͬһʱ�� һ�����ֻ�����һ��PWM ��һͨ�����ֵ͵�ƽ
        }
}
/*******************************************************************************
 *  @brief      Set_balance_motor����
 *  @note       ����ƽ���ֵ��ת������
 *  @date       2021-07-09
 *  @author     aming
 *  @tips       ���Ϊ10000��pwm������ PWM/10000 *100%
 ******************************************************************************/
void Set_balance_motor(int32 PWM)
{
        if(PWM>=0)
        {
            pwm_duty(Motor_balance_Go, PWM);                    //��ת
            pwm_duty(Motor_balance_Return, 0);                  // ͬһʱ�� һ�����ֻ�����һ��PWM ��һͨ�����ֵ͵�ƽ
        }
        else
        {
            pwm_duty(Motor_balance_Go, 0);                           //��ת
            pwm_duty(Motor_balance_Return, (-PWM));                  // ͬһʱ�� һ�����ֻ�����һ��PWM ��һͨ�����ֵ͵�ƽ
        }
}
/*******************************************************************************
 *  @brief      Set_steer����
 *  @note       ����
 *  @date       2021-07-09
 *  @author     aming
 *  @tips       ���Ϊ10000��pwm������ PWM/10000 *100%
 ******************************************************************************/
void Set_steer(int32 PWM)
{
    if(PWM>MaxSteering)
    {    PWM=MaxSteering;   }
    if(PWM<MinSteering)
    {    PWM=MinSteering;   }

    pwm_duty(DUOJI_Channel, PWM);
}

