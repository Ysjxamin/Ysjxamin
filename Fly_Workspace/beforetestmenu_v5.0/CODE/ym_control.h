/*
 * ym_control.h
 *
 *  Created on: 2022年2月14日
 *      Author: huawei
 */

#ifndef CODE_YM_CONTROL_H_
#define CODE_YM_CONTROL_H_

#include "common.h"

 extern int32 MotorDutyA;
 extern int32 MotorDutyB;
 extern int32 balance_encoder;
 extern float X_Balance_KP;
 extern float X_Balance_KI;
 extern float X_Balance_KD;
 extern float X_Velocity_KP;
 extern float X_Velocity_KI;
 extern float Balance_Kp;
 extern float Balance_Ki;
 extern float Balance_Kd;
 extern float Motor_Kp;
 extern float Motor_Ki;
 extern unsigned char Flag_Stop;
 extern float Pitch_Zero;
 extern int32 MidSteering;
/*
void Set_back_motor( int32 PWM);
void Set_balance_motor( int32 PWM);
void Set_steer( int32 PWM);
int16 filtering(int16 new_data);//一阶低通滤波函数
*/
void get_encoder_value(void);
float X_balance_Control(float Angle,float Angle_Zero,float Gyro);
float Velocity_Control(int32 encoder);
void Balance(void);
void Set_balance_motor(int32 PWM);
void Set_back_motor(int32 PWM);
void Set_steer(int32 PWM);
int32 filtering(int32 new_data);//一阶低通滤波函数
#endif /* CODE_YM_CONTROL_H_ */
