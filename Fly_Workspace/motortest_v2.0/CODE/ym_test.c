/*


 * ym_test.c
 *
 *  Created on: 2022��2��15��
 *      Author: huawei

#include "headfile.h"
#include "ym_test.h"

************************************************************************
 *  �������ƣ�TestMotor(void)
 *  ����˵�������Ա궨���PWM���Ƶ��
 *  ����˵������
 *  �������أ���
 *  �޸�ʱ�䣺2020��4��1��
 *  ��    ע������2�����
 ��ע�����ע�⣬һ��Ҫ�Զ����ǽ�������
 ʹ������ĸ��������̣�
 1.��ʹ�����ñ������ص�ѹ����ر�֤��ص�ѹ��7V���ϣ�������������Ӧ��
 2.�Ӻ�ĸ�嵽��������ź��߼���Դ�ߣ�
 3.�Ӻ������嵽����ĵ��ߣ�
 4.��д�������У�ȷ�����������ת���󣬿����������Դ���أ�
 5.����K0/K1ȷ�����ת���ٶȼ�����
 6.������ַ�ת������K2�����ص���ģʽ������ֱ�ӹر��������Դ��
 *************************************************************************

extern int32 balance_encoder,back_encoder;
//int32 balance_duty;
// uint8  key_flag_1 =0;
 uint8  key_flag_2 =0;
 uint8  key_flag_3 =0;
 uint8  key_flag_4 =0;
 uint8  key_flag_5 =0;
void TestMotor (void)
{
    //lcd_clear(WHITE);        //����
    //lcd_showstr(0,0,"Motor Test��");
    //�ǵò���ǰ���ó�ʼ��
    Set_balance_motor(balance_duty);
    while (1)
    {
        if (gpio_get(K1) == 0 && key_flag_1==0)      //����KEY1���������ֵ��ռ�ձȹ���
        {
           systick_delay_ms(STM0, 10);
           if(gpio_get(K1) == 0)
          {
            key_flag_1=1;//�����Ѿ�������
            //��������

            balance_duty=0;

            while(!gpio_get(K1));
            key_flag_1=0;//�����Ѿ�������
           }
        }
        if (gpio_get(K2) == 0 && key_flag_2==0)      //����KEY2����ƽ���ֵ��ռ�ձȼӴ�1000
        {

            systick_delay_ms(STM0, 10);
                       if(gpio_get(K2) == 0)
                     {
                       key_flag_2=1;//�����Ѿ�������
                       //��������

                       if (balance_duty < GTM_ATOM0_PWM_DUTY_MAX)      //��ռ�ձ�Ϊ10000
                           balance_duty += 1000;

                       while(!gpio_get(K2));
                       key_flag_2=0;//�����Ѿ�������
                      }
        }
        if (gpio_get(K3) == 0 && key_flag_3==0)      //����KEY3����ƽ���ֵ��ռ�ձȼ�С1000
        {
            systick_delay_ms(STM0, 10);
             if(gpio_get(K3) == 0)
            {
                 key_flag_3=1;//�����Ѿ�������
                  //��������
                 if (balance_duty > -GTM_ATOM0_PWM_DUTY_MAX)
                   balance_duty -= 1000;
                 //balance_duty=0;
                  while(!gpio_get(K3));
                  key_flag_3=0;//�����Ѿ�������
             }
        }
        if (gpio_get(K4) == 0 && key_flag_4==0)      //����KEY3����ƽ���ֵ��������ת
        {
            systick_delay_ms(STM0, 10);
             if(gpio_get(K4) == 0)
            {
                 key_flag_4=1;//�����Ѿ�������
                  //��������
                 Set_balance_motor(balance_duty);
                  while(!gpio_get(K4));
                  key_flag_4=0;//�����Ѿ�������
             }
        }
        if (gpio_get(K5) == 0 && key_flag_5==0)      //����KEY3����ƽ���ֵ��ռ�ձ�->1000
        {
            systick_delay_ms(STM0, 10);
             if(gpio_get(K5) == 0)
            {
                 key_flag_5=1;//�����Ѿ�������
                  //��������
                 gpio_toggle(LED2);
                 balance_duty = 1000;
                  while(!gpio_get(K5));
                  key_flag_5=0;//�����Ѿ�������
             }
        }
        Set_balance_motor(balance_duty);
        get_encoder_value();
        lcd_showint32(0,2,balance_duty,5);
        lcd_showint32(0,4,balance_encoder,5);
        gpio_toggle(LED0);       //��ƽ��ת,LED��˸;
        rt_thread_mdelay(200);
    }
}


************************************************************************
 *  �������ƣ�Test_Servo(void)
 *  ����˵�������PWM��ʼ�������Ա궨���PWM����SD5/S3010���
 *  ����˵������
 *  �������أ���
 *  �޸�ʱ�䣺2020��4��1��
 *  ��    ע������2�����
 ��ע�����ע�⣬һ��Ҫ�Զ����ǽ�������
 ʹ������ĸ��������̣�
 1.��ʹ�����ñ������ص�ѹ����ر�֤��ص�ѹ��7V���ϣ�������������Ӧ��
 2.Ȼ��ȷ����������ѹ��SD5�����5V���磬S3010��6-7V���磡����
 3.�Ѷ���Ķ���ȥ�����ö����������ת����
 4.��д�������У��ö��ת������ֵ���������û��Ӧ�ظ�1-2�������ߵ��������PWMƵ�ʼ�ռ�ձȣ����ܿ�Ϊ׼��
 5.����ܿغ�������ת�������֨֨�죬�Կ�ת������ʱ����װ�϶��̣�
 6.����K0/K1ȷ�����������ת�����ޣ�������������Ϊ�����޷���ֹ�����ת�ջ٣�
 ************************************************************************

void TestSteer (void)
{
    int32 MidSteering=0,MaxSteering=0,MinSteering=0;
    int32 duty = MidSteering;

    lcd_clear(WHITE);          //����
    lcd_showstr(0,0,"Steer Test!");
    //��ʼ��
    Set_steer(MidSteering);      //��ֵ
    while (1)
    {
        if (gpio_get(K1) == 0)      //����KEY1�������ռ�ձȼ�С
    {
        if (duty > -MaxSteering)
            duty -= 100;
    }
    if (gpio_get(K2) == 0)      //����KEY2�������ռ�ձȼӴ�
    {
        if (duty < MaxSteering)      //��ռ�ձ�Ϊ10000
            duty += 100;
    }
    if (gpio_get(K3) == 0)      //����KEY3����ƽ���ֵ��ռ�ձȼ�С
    {

    }
    if (gpio_get(K4) == 0)      //����KEY4����ƽ���ֵ��ռ�ձȼӴ�
    {

    }
    if (gpio_get(K5) == 0)      //����KEY5�������ռ�ձ�
    {
        duty = MidSteering;
    }
    Set_steer(duty);
    printf( "steer_PWM: %d;", duty);

    gpio_toggle(LED0);       //��ƽ��ת,LED��˸;
    }
}

************************************************************************
 *  �������ƣ�void TestEncoder(void)
 *  ����˵�������Գ���TFT1.8��ʾ
 *  ����˵������
 *  �������أ���
 *  �޸�ʱ�䣺2020��4��10��
 *  ��    ע��
 ************************************************************************

void TestEncoder(void)
{
    char txt[32];

    lcd_clear(WHITE);          //����
    lcd_showstr(0,0,"Encoder Test!");
    //��ʼ��
    while (1)
    {
         //��ȡ������ֵ
        get_encoder_value();
        //ECPULSE1 = ENC_GetCounter(ENC2_InPut_P33_7); //���� ĸ���ϱ�����1��С��ǰ��Ϊ��ֵ
        //ECPULSE2 = ENC_GetCounter(ENC4_InPut_P02_8); //�ҵ�� ĸ���ϱ�����2��С��ǰ��Ϊ��ֵ

        printf("back_Encoder Value:%d",back_encoder);
        printf("balance_Encoder Value:%d",balance_encoder);
    }
    gpio_toggle(LED0);       //��ƽ��ת,LED��˸;
    rt_thread_mdelay(200);
}

*/
