#include "motor.h"

#define MOTOR1_DIR   P21_2              //����1��������������
#define MOTOR1_PWM   ATOM0_CH1_P21_3    //����1���PWM����

#define MOTOR2_DIR   P21_4              //����2��������������
#define MOTOR2_PWM   ATOM0_CH3_P21_5    //����2���PWM����

#define MOTOR3_DIR   P02_4              //����3��������������
#define MOTOR3_PWM   ATOM0_CH5_P02_5    //����3���PWM����

#define MOTOR4_DIR   P02_6              //����4��������������
#define MOTOR4_PWM   ATOM0_CH7_P02_7    //����4���PWM����

void motor_init(void)
{

    //׿���������У�����������Ƶ��ѡ��13K-17K

    //��ʹ�ñ����������ȷ����ʹ�õ���������
    //������ֻ֧��DRV8701E����

    //��ʼ��PWM����
    gtm_pwm_init(MOTOR1_PWM, 17000, 0);
    gtm_pwm_init(MOTOR2_PWM, 17000, 0);
    gtm_pwm_init(MOTOR3_PWM, 17000, 0);
    gtm_pwm_init(MOTOR4_PWM, 17000, 0);

    //��ʼ�������������
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
    //��ռ�ձ��޷�
    duty_m1 = (int32)limit((float)duty_m1, GTM_ATOM0_PWM_DUTY_MAX);
    duty_m2 = (int32)limit((float)duty_m2, GTM_ATOM0_PWM_DUTY_MAX);
    duty_m3 = (int32)limit((float)duty_m3, GTM_ATOM0_PWM_DUTY_MAX);
    duty_m4 = (int32)limit((float)duty_m4, GTM_ATOM0_PWM_DUTY_MAX);

    if(duty_m1 >= 0)                                        // �����ת
    {
        gpio_set(MOTOR1_DIR, GPIO_LOW);                     // DIR����ߵ�ƽ
        pwm_duty(MOTOR1_PWM, duty_m1);                    // ����ռ�ձ�
    }
    else													// ��෴ת
    {
        gpio_set(MOTOR1_DIR, GPIO_HIGH);                    // DIR����ߵ�ƽ
        pwm_duty(MOTOR1_PWM, -duty_m1);                    // ����ռ�ձ�
    }

    if(duty_m2 >= 0)                                        // �����ת
    {
        gpio_set(MOTOR2_DIR, GPIO_LOW);                     // DIR����ߵ�ƽ
        pwm_duty(MOTOR2_PWM, duty_m2);                       // ����ռ�ձ�
    }
    else                                                    // ��෴ת
    {
        gpio_set(MOTOR2_DIR, GPIO_HIGH);                    // DIR����ߵ�ƽ
        pwm_duty(MOTOR2_PWM, -duty_m2);                   // ����ռ�ձ�
    }

    if(duty_m3 >= 0)                                        // �����ת
    {
        gpio_set(MOTOR3_DIR, GPIO_LOW);                     // DIR����ߵ�ƽ
        pwm_duty(MOTOR3_PWM, duty_m3);                      // ����ռ�ձ�
    }
    else                                                    // ��෴ת
    {
        gpio_set(MOTOR3_DIR, GPIO_HIGH);                    // DIR����ߵ�ƽ
        pwm_duty(MOTOR3_PWM, -duty_m3);                     // ����ռ�ձ�
    }

    if(duty_m4 >= 0)                                        // �����ת
    {
        gpio_set(MOTOR4_DIR, GPIO_LOW);                     // DIR����ߵ�ƽ
        pwm_duty(MOTOR4_PWM, duty_m4);                        // ����ռ�ձ�
    }
    else                                                    // ��෴ת
    {
        gpio_set(MOTOR4_DIR, GPIO_HIGH);                    // DIR����ߵ�ƽ
        pwm_duty(MOTOR4_PWM, -duty_m4);                      // ����ռ�ձ�
    }
}
