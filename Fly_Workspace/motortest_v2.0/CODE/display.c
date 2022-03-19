#include "headfile.h"
#include "encoder.h"
#include "display.h"
#include "ym_control.h"
#include "ym_kalman.h"



extern int32 MotorDutyA;
extern int32 balance_encoder;
extern float Angle_X_Final;
extern float X_Balance_KP;
extern float X_Balance_KI;
extern float X_Balance_KD;
void display_entry(void *parameter)
{
    while(1)
    {
        //��ʾPID������Ϣ
        //lcd_clear(WHITE);//����
        /*lcd_showstr(0,0,"ban_duty:");
        lcd_showint32(10,0,MotorDutyA,5);
        lcd_showstr(0,1,"ban_encoder:");
        lcd_showint32(12,1,balance_encoder,5);
        lcd_showstr(0,2,"Pitch:");
        lcd_showfloat(7,2,Angle_X_Final,2,6);
        lcd_showstr(0,3,"PID:");
        lcd_showfloat(0,4,X_Balance_KP,4,4);
        lcd_showfloat(0,5,X_Balance_KI,2,4);
        lcd_showfloat(0,6,X_Balance_KD,3,4);*/
        //float X_Balance_KP=1900.001,X_Balance_KI=3.2001,X_Balance_KD=60.001;  // ƽ�⻷PID  Pitch��ǶȻ�PID���� ������

       //��ʾ����ͷͼ��
/*        ips200_displayimage032(mt9v03x_image[0], MT9V03X_W, MT9V03X_H);
        ips200_showint16(0, 8, icm_gyro_x);
        ips200_showint16(0, 9, icm_acc_x);
        ips200_showint16(0, 10, encoder1);
        ips200_showint16(0, 11, encoder2);
        ips200_showint16(0, 12, encoder3);
        ips200_showint16(0, 13, encoder4);*/
    }
    
}






void display_init(void)
{
    rt_thread_t tid;
    
    //��ʼ����Ļ
    lcd_init();
    //lcd_clear(WHITE);
    
    //������ʾ�߳� ���ȼ�����Ϊ6 
    tid = rt_thread_create("display", display_entry, RT_NULL, 256, 31, 30);
    
    //������ʾ�߳�
    if(RT_NULL != tid)
    {
        rt_thread_startup(tid);
    }
}
