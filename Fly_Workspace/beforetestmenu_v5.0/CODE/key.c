/*
 * key.c
 *
 *  Created on: 2022年2月19日
 *      Author: czh
 */

#include "key.h"
void delay_ms(int count)
{
    systick_delay_ms(STM0, count);
}
void GPIO_KEY_Init(void)
{
    //设置P21_2为输入 PULLUP：上拉输入
//    gpio_init(P15_5, GPI, 0, PULLUP);
    gpio_init(P20_6, GPI, 0, PULLUP);
    gpio_init(P20_7, GPI, 0, PULLUP);
    gpio_init(P20_8, GPI, 0, PULLUP);
    gpio_init(P20_9, GPI, 0, PULLUP);
}

uint8 KEY_Scan(uint8 mode)
{
    static uint8 key_up=1;//按键按松开标志
    if(mode)key_up=1;  //支持连按
    if(key_up&&(KEY0==0||KEY1==0||KEY2==0||KEY3==0))
    {
        systick_delay_ms(STM0, 10);
        key_up=0;
        if(KEY0==0)return KEY0_PRES;
        else if(KEY1==0)return KEY1_PRES;
        else if(KEY2==0)return KEY2_PRES;
        else if(KEY3==0)return KEY3_PRES;
    }else if(KEY0==1&&KEY1==1&&KEY2==1)key_up=1;
    return 0;// 无按键按下
}

/*******************************************************************************
 *  @brief      touch_key函数
 *  @note       轻触按键功能
 *  @date       2021-07-11
 *  @author     小麦
 ******************************************************************************/
void touch_key (void)
{
    touch_key1();
    touch_key2();
    touch_key3();
    touch_key4();
}

/*******************************************************************************
 *  @brief      touch_key1函数
 *  @note       轻触按键1功能
 *  @date       2021-07-11
 *  @author     小麦
 ******************************************************************************/
void touch_key1 (void)
{
    if (gpio_get(K1) == 0)
    {
        systick_delay_ms(STM0, 100);
        if (gpio_get(K1) == 0)
        {



        }
        while (!gpio_get(K1))
            ;
    }
}

/*******************************************************************************
 *  @brief      touch_key2函数
 *  @note       轻触按键2功能
 *  @date       2021-07-11
 *  @author     小麦
 ******************************************************************************/
void touch_key2 (void)
{
    if (gpio_get(K2) == 0)
    {
        systick_delay_ms(STM0, 100);
        if (gpio_get(K2) == 0)
        {



        }
        while (!gpio_get(K2))
            ;
    }
}


/*******************************************************************************
 *  @brief      touch_key3函数
 *  @note       轻触按键3功能
 *  @date       2021-07-11
 *  @author     小麦
 ******************************************************************************/
void touch_key3 (void)
{
    if (gpio_get(K3) == 0)
    {
        systick_delay_ms(STM0, 100);
        if (gpio_get(K3) == 0)
        {


        }
        while (!gpio_get(K3))
            ;
    }
}

/*******************************************************************************
 *  @brief      touch_key4函数
 *  @note       轻触按键4功能
 *  @date       2021-07-11
 *  @author     小麦
 ******************************************************************************/
void touch_key4 (void)
{
    if (gpio_get(K4) == 0)
    {
        systick_delay_ms(STM0, 100);
        if (gpio_get(K4) == 0)
        {



        }
        while (!gpio_get(K4))
            ;
    }
}
