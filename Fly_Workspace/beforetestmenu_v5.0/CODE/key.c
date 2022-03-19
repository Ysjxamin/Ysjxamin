/*
 * key.c
 *
 *  Created on: 2022��2��19��
 *      Author: czh
 */

#include "key.h"
void delay_ms(int count)
{
    systick_delay_ms(STM0, count);
}
void GPIO_KEY_Init(void)
{
    //����P21_2Ϊ���� PULLUP����������
//    gpio_init(P15_5, GPI, 0, PULLUP);
    gpio_init(P20_6, GPI, 0, PULLUP);
    gpio_init(P20_7, GPI, 0, PULLUP);
    gpio_init(P20_8, GPI, 0, PULLUP);
    gpio_init(P20_9, GPI, 0, PULLUP);
}

uint8 KEY_Scan(uint8 mode)
{
    static uint8 key_up=1;//�������ɿ���־
    if(mode)key_up=1;  //֧������
    if(key_up&&(KEY0==0||KEY1==0||KEY2==0||KEY3==0))
    {
        systick_delay_ms(STM0, 10);
        key_up=0;
        if(KEY0==0)return KEY0_PRES;
        else if(KEY1==0)return KEY1_PRES;
        else if(KEY2==0)return KEY2_PRES;
        else if(KEY3==0)return KEY3_PRES;
    }else if(KEY0==1&&KEY1==1&&KEY2==1)key_up=1;
    return 0;// �ް�������
}

/*******************************************************************************
 *  @brief      touch_key����
 *  @note       �ᴥ��������
 *  @date       2021-07-11
 *  @author     С��
 ******************************************************************************/
void touch_key (void)
{
    touch_key1();
    touch_key2();
    touch_key3();
    touch_key4();
}

/*******************************************************************************
 *  @brief      touch_key1����
 *  @note       �ᴥ����1����
 *  @date       2021-07-11
 *  @author     С��
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
 *  @brief      touch_key2����
 *  @note       �ᴥ����2����
 *  @date       2021-07-11
 *  @author     С��
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
 *  @brief      touch_key3����
 *  @note       �ᴥ����3����
 *  @date       2021-07-11
 *  @author     С��
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
 *  @brief      touch_key4����
 *  @note       �ᴥ����4����
 *  @date       2021-07-11
 *  @author     С��
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
