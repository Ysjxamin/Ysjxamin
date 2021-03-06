/*
 * ym_kalman.c
 *
 *  Created on: 2022年2月12日
 *      Author: aming
 */
#include "ym_all_h.h"
#include "headfile.h"
extern int16 mpu_gyro_x,mpu_gyro_y,mpu_gyro_z;
extern int16 mpu_acc_x,mpu_acc_y,mpu_acc_z;
float ax,ay,az,Gyro_x,Gyro_y,Gyro_z,Angle_x_temp,Angle_y_temp;

//卡尔曼参数
float Q_angle = 0.001;
float Q_gyro  = 0.003;
float R_angle = 0.5;
float dt      = 0.01;//dt为kalman滤波器采样时间
char  C_0     = 1;
float Q_bias, Angle_err;
float PCt_0, PCt_1, E;
float K_0, K_1, t_0, t_1;
float Pdot[4] ={0,0,0,0};
float PP[2][2] = { { 1, 0 },{ 0, 1 } };
float Angle_X_Final,Angle_Y_Final;
void Kalman_Filter_X(float Accel,float Gyro) //卡尔曼函数
{
    Angle_X_Final += (Gyro - Q_bias) * dt; //先验估计

    Pdot[0]=Q_angle - PP[0][1] - PP[1][0]; // Pk-先验估计误差协方差的微分

    Pdot[1]= -PP[1][1];
    Pdot[2]= -PP[1][1];
    Pdot[3]= Q_gyro;

    PP[0][0] += Pdot[0] * dt;   // Pk-先验估计误差协方差微分的积分
    PP[0][1] += Pdot[1] * dt;   // =先验估计误差协方差
    PP[1][0] += Pdot[2] * dt;
    PP[1][1] += Pdot[3] * dt;

    Angle_err = Accel - Angle_X_Final;  //zk-先验估计

    PCt_0 = C_0 * PP[0][0];
    PCt_1 = C_0 * PP[1][0];

    E = R_angle + C_0 * PCt_0;

    K_0 = PCt_0 / E;
    K_1 = PCt_1 / E;

    t_0 = PCt_0;
    t_1 = C_0 * PP[0][1];

    PP[0][0] -= K_0 * t_0;       //后验估计误差协方差
    PP[0][1] -= K_0 * t_1;
    PP[1][0] -= K_1 * t_0;
    PP[1][1] -= K_1 * t_1;

    Angle_X_Final += K_0 * Angle_err;    //后验估计
    Q_bias        += K_1 * Angle_err;    //后验估计
    Gyro_x         = Gyro - Q_bias;  //输出值（后验估计）的微分 = 角速度
}

void Kalman_Filter_Y(float Accel,float Gyro) //卡尔曼函数
{
    Angle_Y_Final += (Gyro - Q_bias) * dt; //先验估计

    Pdot[0]=Q_angle - PP[0][1] - PP[1][0]; // Pk-先验估计误差协方差的微分

    Pdot[1]=- PP[1][1];
    Pdot[2]=- PP[1][1];
    Pdot[3]=Q_gyro;

    PP[0][0] += Pdot[0] * dt;   // Pk-先验估计误差协方差微分的积分
    PP[0][1] += Pdot[1] * dt;   // =先验估计误差协方差
    PP[1][0] += Pdot[2] * dt;
    PP[1][1] += Pdot[3] * dt;

    Angle_err = Accel - Angle_Y_Final;  //zk-先验估计

    PCt_0 = C_0 * PP[0][0];
    PCt_1 = C_0 * PP[1][0];

    E = R_angle + C_0 * PCt_0;

    K_0 = PCt_0 / E;
    K_1 = PCt_1 / E;

    t_0 = PCt_0;
    t_1 = C_0 * PP[0][1];

    PP[0][0] -= K_0 * t_0;       //后验估计误差协方差
    PP[0][1] -= K_0 * t_1;
    PP[1][0] -= K_1 * t_0;
    PP[1][1] -= K_1 * t_1;

    Angle_Y_Final   += K_0 * Angle_err;  //后验估计
    Q_bias  += K_1 * Angle_err;  //后验估计
    Gyro_y   = Gyro - Q_bias;    //输出值（后验估计）的微分 = 角速度
}
void MPU6050(void)
{
    get_accdata();
     get_gyro();   //得到传感器数据
        ax = (9.8*mpu_acc_x)/8192;
        ay = (9.8*mpu_acc_y)/8192;
        az = (9.8*mpu_acc_z)/8192;
        Gyro_x = (mpu_gyro_x)/16.4;
        Gyro_y = (mpu_gyro_y)/16.4;
        Gyro_z = (mpu_gyro_z)/16.4;

        //用加速度计算三个轴和水平面坐标系之间的夹角
        Angle_x_temp=(atan(ay/az))*180/3.14;
        Angle_y_temp=(atan(ax/az))*180/3.14;

        Kalman_Filter_X(Angle_x_temp,Gyro_x);  //卡尔曼滤波计算X倾角
        Kalman_Filter_Y(Angle_y_temp,Gyro_y);  //卡尔曼滤波计算Y倾角
}


