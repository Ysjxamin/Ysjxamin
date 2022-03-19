/*
 * ym_control.h
 *
 *  Created on: 2022��2��14��
 *      Author: huawei
 */

#ifndef CODE_YM_CONTROL_H_
#define CODE_YM_CONTROL_H_

#include "common.h"


/*
void Set_back_motor( int32 PWM);
void Set_balance_motor( int32 PWM);
void Set_steer( int32 PWM);
int16 filtering(int16 new_data);//һ�׵�ͨ�˲�����
*/
void get_encoder_value(void);
float X_balance_Control(float Angle,float Angle_Zero,float Gyro);
float Velocity_Control(int32 encoder);
void Balance(void);
void Set_balance_motor(int32 PWM);
void Set_back_motor(int32 PWM);
void Set_steer(int32 PWM);
int32 filtering(int32 new_data);//һ�׵�ͨ�˲�����
#endif /* CODE_YM_CONTROL_H_ */
