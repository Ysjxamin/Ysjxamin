#include "buzzer.h"
#include "button.h"
#define BUZZER_PIN          P33_10          // 定义主板上蜂鸣器对应引脚
#define KEY_1   P33_11  // 定义主板上按键对应引脚
#define KEY_2   P23_1  // 定义主板上按键对应引脚
#define KEY_3   P33_13  // 定义主板上按键对应引脚
#define KEY_4   P32_4  // 定义主板上按键对应引脚
#define KEY_5   P33_12  // 定义主板上按键对应引脚
extern int32 MotorDutyA;
//开关状态变量
uint8 key1_status = 1;
uint8 key2_status = 1;
uint8 key3_status = 1;
uint8 key4_status = 1;
uint8 key5_status = 1;
//上一次开关状态变量
uint8 key1_last_status;
uint8 key2_last_status;
uint8 key3_last_status;
uint8 key4_last_status;
uint8 key5_last_status;
//开关信号量
rt_sem_t key1_sem;
rt_sem_t key2_sem;
rt_sem_t key3_sem;
rt_sem_t key4_sem;
rt_sem_t key5_sem;
void button_test(void)
{
    //保存按键状态
       key1_last_status = key1_status;
       key2_last_status = key2_status;
       key3_last_status = key3_status;
       key4_last_status = key4_status;
       key5_last_status = key5_status;
       //读取当前按键状态
       key1_status = gpio_get(KEY_1);
       key2_status = gpio_get(KEY_2);
       key3_status = gpio_get(KEY_3);
       key4_status = gpio_get(KEY_4);
       key5_status = gpio_get(KEY_5);
       //检测到按键按下之后并放开 释放一次信号量
       if(key1_status && !key1_last_status)
       {
           gpio_set(BUZZER_PIN, 1);    //打开蜂鸣器
           systick_delay_ms(STM0, 10);//上电延时
           gpio_set(BUZZER_PIN, 0);    //关闭蜂鸣器
       }
       if(key2_status && !key2_last_status)
       {
           gpio_toggle(LED0);
           MotorDutyA+=1500;
       }
       if(key3_status && !key3_last_status)
       {
           gpio_toggle(LED0);
           MotorDutyA-=1500;
       }
       if(key4_status && !key4_last_status)
       {
           gpio_toggle(LED0);
           MotorDutyA=2000;
       }
       if(key5_status && !key5_last_status)
       {
           gpio_toggle(LED0);
           MotorDutyA=0;
       }

}
void button_entry(void *parameter)
{

    //保存按键状态
    key1_last_status = key1_status;
    key2_last_status = key2_status;
    key3_last_status = key3_status;
    key4_last_status = key4_status;
    key5_last_status = key5_status;
    //读取当前按键状态
    key1_status = gpio_get(KEY_1);
    key2_status = gpio_get(KEY_2);
    key3_status = gpio_get(KEY_3);
    key4_status = gpio_get(KEY_4);
    key5_status = gpio_get(KEY_5);
    //检测到按键按下之后并放开 释放一次信号量
    if(key1_status && !key1_last_status)    
    {
        rt_sem_release(key1_sem);
        rt_mb_send(buzzer_mailbox, 100);
        gpio_toggle(LED0);
        gpio_set(BUZZER_PIN, 1);    //打开蜂鸣器
        systick_delay_ms(STM0, 10);//上电延时

                //rt_thread_mdelay(100);  //延时
                gpio_set(BUZZER_PIN, 0);    //关闭蜂鸣器
    }
    if(key2_status && !key2_last_status)    
    {
        rt_sem_release(key2_sem);
        rt_mb_send(buzzer_mailbox, 300);
        gpio_toggle(LED0);
        MotorDutyA+=1500;
    }
    if(key3_status && !key3_last_status)    
    {
        rt_sem_release(key3_sem);
        rt_mb_send(buzzer_mailbox, 600);
        gpio_toggle(LED0);
        MotorDutyA-=1500;
    }
    if(key4_status && !key4_last_status)    
    {
        rt_sem_release(key4_sem);
        rt_mb_send(buzzer_mailbox, 1000);
        gpio_toggle(LED0);
        MotorDutyA=2000;
    }
    if(key5_status && !key5_last_status)
    {
        rt_sem_release(key5_sem);
        rt_mb_send(buzzer_mailbox, 2000);
        gpio_toggle(LED0);
        MotorDutyA=0;
    }
    
}

void button_init(void)
{
    rt_timer_t timer1;
    
    gpio_init(KEY_1, GPI, GPIO_HIGH, PULLUP);          // 初始化为GPIO浮空输入 默认上拉高电平
	gpio_init(KEY_2, GPI, GPIO_HIGH, PULLUP);
	gpio_init(KEY_3, GPI, GPIO_HIGH, PULLUP);
	gpio_init(KEY_4, GPI, GPIO_HIGH, PULLUP);
	gpio_init(KEY_5, GPI, GPIO_HIGH, PULLUP);

    /**************LED初始化**************/
     gpio_init(LED0,GPO,0,PUSHPULL);
     gpio_init(LED1,GPO,0,PUSHPULL);
     gpio_init(LED2,GPO,0,PUSHPULL);
    
    key1_sem = rt_sem_create("key1", 0, RT_IPC_FLAG_FIFO);  //创建按键的信号量，当按键按下就释放信号量，在需要使用按键的地方获取信号量即可
    key2_sem = rt_sem_create("key2", 0, RT_IPC_FLAG_FIFO);  
    key3_sem = rt_sem_create("key3", 0, RT_IPC_FLAG_FIFO);  
    key4_sem = rt_sem_create("key4", 0, RT_IPC_FLAG_FIFO);  
    key5_sem = rt_sem_create("key5", 0, RT_IPC_FLAG_FIFO);
    
    timer1 = rt_timer_create("button", button_entry, RT_NULL, 20, RT_TIMER_FLAG_PERIODIC);

    if(RT_NULL != timer1) 
    {
        rt_timer_start(timer1);
    }
}
