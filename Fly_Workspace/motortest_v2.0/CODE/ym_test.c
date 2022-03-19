/*


 * ym_test.c
 *
 *  Created on: 2022年2月15日
 *      Author: huawei

#include "headfile.h"
#include "ym_test.h"

************************************************************************
 *  函数名称：TestMotor(void)
 *  功能说明：测试标定输出PWM控制电机
 *  参数说明：无
 *  函数返回：无
 *  修改时间：2020年4月1日
 *  备    注：驱动2个电机
 【注意事项】注意，一定要对舵机打角进行限制
 使用龙邱母板测试流程：
 1.先使用万用表测量电池电压，务必保证电池电压在7V以上，否则无力不反应！
 2.接好母板到驱动板的信号线及电源线；
 3.接好驱动板到电机的导线；
 4.烧写程序并运行，确定电机能正常转动后，开启驱动板电源开关；
 5.按键K0/K1确定电机转动速度及方向；
 6.如果出现疯转，按下K2键返回低速模式，或者直接关闭驱动板电源！
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
    //lcd_clear(WHITE);        //清屏
    //lcd_showstr(0,0,"Motor Test！");
    //记得测试前调用初始化
    Set_balance_motor(balance_duty);
    while (1)
    {
        if (gpio_get(K1) == 0 && key_flag_1==0)      //按下KEY1键，动量轮电机占空比归零
        {
           systick_delay_ms(STM0, 10);
           if(gpio_get(K1) == 0)
          {
            key_flag_1=1;//表面已经按下了
            //按键处理

            balance_duty=0;

            while(!gpio_get(K1));
            key_flag_1=0;//表面已经按下了
           }
        }
        if (gpio_get(K2) == 0 && key_flag_2==0)      //按下KEY2键，平衡轮电机占空比加大1000
        {

            systick_delay_ms(STM0, 10);
                       if(gpio_get(K2) == 0)
                     {
                       key_flag_2=1;//表面已经按下了
                       //按键处理

                       if (balance_duty < GTM_ATOM0_PWM_DUTY_MAX)      //满占空比为10000
                           balance_duty += 1000;

                       while(!gpio_get(K2));
                       key_flag_2=0;//表面已经按下了
                      }
        }
        if (gpio_get(K3) == 0 && key_flag_3==0)      //按下KEY3键，平衡轮电机占空比减小1000
        {
            systick_delay_ms(STM0, 10);
             if(gpio_get(K3) == 0)
            {
                 key_flag_3=1;//表面已经按下了
                  //按键处理
                 if (balance_duty > -GTM_ATOM0_PWM_DUTY_MAX)
                   balance_duty -= 1000;
                 //balance_duty=0;
                  while(!gpio_get(K3));
                  key_flag_3=0;//表面已经按下了
             }
        }
        if (gpio_get(K4) == 0 && key_flag_4==0)      //按下KEY3键，平衡轮电机死机后开转
        {
            systick_delay_ms(STM0, 10);
             if(gpio_get(K4) == 0)
            {
                 key_flag_4=1;//表面已经按下了
                  //按键处理
                 Set_balance_motor(balance_duty);
                  while(!gpio_get(K4));
                  key_flag_4=0;//表面已经按下了
             }
        }
        if (gpio_get(K5) == 0 && key_flag_5==0)      //按下KEY3键，平衡轮电机占空比->1000
        {
            systick_delay_ms(STM0, 10);
             if(gpio_get(K5) == 0)
            {
                 key_flag_5=1;//表面已经按下了
                  //按键处理
                 gpio_toggle(LED2);
                 balance_duty = 1000;
                  while(!gpio_get(K5));
                  key_flag_5=0;//表面已经按下了
             }
        }
        Set_balance_motor(balance_duty);
        get_encoder_value();
        lcd_showint32(0,2,balance_duty,5);
        lcd_showint32(0,4,balance_encoder,5);
        gpio_toggle(LED0);       //电平翻转,LED闪烁;
        rt_thread_mdelay(200);
    }
}


************************************************************************
 *  函数名称：Test_Servo(void)
 *  功能说明：舵机PWM初始化，测试标定输出PWM控制SD5/S3010舵机
 *  参数说明：无
 *  函数返回：无
 *  修改时间：2020年4月1日
 *  备    注：驱动2个舵机
 【注意事项】注意，一定要对舵机打角进行限制
 使用龙邱母板测试流程：
 1.先使用万用表测量电池电压，务必保证电池电压在7V以上，否则无力不反应！
 2.然后确定舵机供电电压，SD5舵机用5V供电，S3010用6-7V供电！！！
 3.把舵机的舵盘去掉，让舵机可以自由转动；
 4.烧写程序并运行，让舵机转动到中值附近；如果没反应重复1-2步，或者调整舵机的PWM频率计占空比，能受控为准；
 5.舵机受控后用手轻转，舵机会吱吱响，对抗转动，此时可以装上舵盘；
 6.按键K0/K1确定舵机的左右转动极限，并记下来，作为后续限幅防止舵机堵转烧毁！
 ************************************************************************

void TestSteer (void)
{
    int32 MidSteering=0,MaxSteering=0,MinSteering=0;
    int32 duty = MidSteering;

    lcd_clear(WHITE);          //清屏
    lcd_showstr(0,0,"Steer Test!");
    //初始化
    Set_steer(MidSteering);      //中值
    while (1)
    {
        if (gpio_get(K1) == 0)      //按下KEY1键，舵机占空比减小
    {
        if (duty > -MaxSteering)
            duty -= 100;
    }
    if (gpio_get(K2) == 0)      //按下KEY2键，舵机占空比加大
    {
        if (duty < MaxSteering)      //满占空比为10000
            duty += 100;
    }
    if (gpio_get(K3) == 0)      //按下KEY3键，平衡轮电机占空比减小
    {

    }
    if (gpio_get(K4) == 0)      //按下KEY4键，平衡轮电机占空比加大
    {

    }
    if (gpio_get(K5) == 0)      //按下KEY5键，舵机占空比
    {
        duty = MidSteering;
    }
    Set_steer(duty);
    printf( "steer_PWM: %d;", duty);

    gpio_toggle(LED0);       //电平翻转,LED闪烁;
    }
}

************************************************************************
 *  函数名称：void TestEncoder(void)
 *  功能说明：测试程序，TFT1.8显示
 *  参数说明：无
 *  函数返回：无
 *  修改时间：2020年4月10日
 *  备    注：
 ************************************************************************

void TestEncoder(void)
{
    char txt[32];

    lcd_clear(WHITE);          //清屏
    lcd_showstr(0,0,"Encoder Test!");
    //初始化
    while (1)
    {
         //获取编码器值
        get_encoder_value();
        //ECPULSE1 = ENC_GetCounter(ENC2_InPut_P33_7); //左电机 母板上编码器1，小车前进为负值
        //ECPULSE2 = ENC_GetCounter(ENC4_InPut_P02_8); //右电机 母板上编码器2，小车前进为正值

        printf("back_Encoder Value:%d",back_encoder);
        printf("balance_Encoder Value:%d",balance_encoder);
    }
    gpio_toggle(LED0);       //电平翻转,LED闪烁;
    rt_thread_mdelay(200);
}

*/
