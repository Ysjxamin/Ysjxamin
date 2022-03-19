#include "headfile.h"
#include "encoder.h"
#include "display.h"





void display_entry(void *parameter)
{
    while(1)
    {
        ips200_displayimage032(mt9v03x_image[0], MT9V03X_W, MT9V03X_H);
        ips200_showint16(0, 8, icm_gyro_x);
        ips200_showint16(0, 9, icm_acc_x);
        ips200_showint16(0, 10, encoder1);
        ips200_showint16(0, 11, encoder2);
        ips200_showint16(0, 12, encoder3);
        ips200_showint16(0, 13, encoder4);
    }
    
}






void display_init(void)
{
    rt_thread_t tid;
    
    //初始化屏幕
    ips200_init();
    
    //创建显示线程 优先级设置为6 
    tid = rt_thread_create("display", display_entry, RT_NULL, 256, 31, 30);
    
    //启动显示线程
    if(RT_NULL != tid)
    {
        rt_thread_startup(tid);
    }
}
