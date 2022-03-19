/*
 * menu.c
 *
 *  Created on: 2022年2月19日
 *      Author: czh
 */

#include "ym_all_h.h"
//extern float X_Balance_KP;
//extern float X_Balance_KI;
 float _X_Balance_KI;
//extern float X_Balance_KD;
//extern float X_Velocity_KP;
//extern float X_Velocity_KI;
 float _X_Velocity_KI;
 float _X_Velocity_KP;
 float _Balance_Ki;
 float _Balance_Kd;
uint32 write_buf;

void choose_menu_xpid(void)
{

    //读取eeprom中的数据
    X_Balance_KP = flash_read(EXAMPLE_EEPROM_SECTOR, 0, uint32);
    _X_Balance_KI = flash_read(EXAMPLE_EEPROM_SECTOR, 1, uint32);
    X_Balance_KI=_X_Balance_KI/10;
    X_Balance_KD = flash_read(EXAMPLE_EEPROM_SECTOR, 2, uint32);
    _X_Velocity_KP = flash_read(EXAMPLE_EEPROM_SECTOR, 3, uint32);
    X_Velocity_KP=-_X_Velocity_KP;
    _X_Velocity_KI = flash_read(EXAMPLE_EEPROM_SECTOR, 4, uint32);
    X_Velocity_KI=-_X_Velocity_KI/10;
    int height=0;
    u8 key=0,mark=1;
    lcd_clear(WHITE);
    lcd_showstr(0, 0, "X_B_KP");
    lcd_showstr(0, 1, "X_B_KI");
    lcd_showstr(0, 2, "X_B_KD");
    lcd_showstr(0, 3, "X_V_KP");
    lcd_showstr(0, 4, "X_V_KI");
    lcd_showstr(0, 5, "exit");
    lcd_showstr(120, height, "**");
    lcd_showfloat(70,0,X_Balance_KP,4,1);
    lcd_showfloat(70,1,X_Balance_KI,2,1);
    lcd_showfloat(70,2,X_Balance_KD,3,1);
    lcd_showfloat(70,3,X_Velocity_KP,2,1);
    lcd_showfloat(70,4,X_Velocity_KI,2,1);
    while(mark)
    {
        key=0;
        key=KEY_Scan(0);
        //gpio_toggle(LED0);       //电平翻转,LED闪烁;

        if(key)
        {
                switch(key)
                {
                    case KEY0_PRES:
                        height++;
                        if(height>5)height=0;
                        lcd_clear(WHITE);
                        lcd_showstr(0, 0, "X_B_KP");
                        lcd_showstr(0, 1, "X_B_KI");
                        lcd_showstr(0, 2, "X_B_KD");
                        lcd_showstr(0, 3, "X_V_KP");
                        lcd_showstr(0, 4, "X_V_KI");
                        lcd_showstr(0, 5, "exit");
                        lcd_showstr(120, height, "**");
                        lcd_showfloat(70,0,X_Balance_KP,4,1);
                        lcd_showfloat(70,1,X_Balance_KI,2,1);
                        lcd_showfloat(70,2,X_Balance_KD,3,1);
                        lcd_showfloat(70,3,X_Velocity_KP,2,1);
                        lcd_showfloat(70,4,X_Velocity_KI,2,1);
                        systick_delay_ms(STM0, 50);
                        break;
                    case KEY1_PRES:
                        height--;
                        if(height<5)height=5;
                        lcd_clear(WHITE);
                        lcd_showstr(0, 0, "X_B_KP");
                        lcd_showstr(0, 1, "X_B_KI");
                        lcd_showstr(0, 2, "X_B_KD");
                        lcd_showstr(0, 3, "X_V_KP");
                        lcd_showstr(0, 4, "X_V_KI");
                        lcd_showstr(0, 5, "exit");
                        lcd_showstr(120, height, "**");
                        lcd_showfloat(70,0,X_Balance_KP,4,1);
                        lcd_showfloat(70,1,X_Balance_KI,2,1);
                        lcd_showfloat(70,2,X_Balance_KD,3,1);
                        lcd_showfloat(70,3,X_Velocity_KP,2,1);
                        lcd_showfloat(70,4,X_Velocity_KI,2,1);
                        systick_delay_ms(STM0, 50);
                        break;
                    case KEY2_PRES:
                        lcd_clear(WHITE);
                        switch(height)
                        {
                            case 0:
                                X_Balance_KP=set_pid(height,X_Balance_KP,1);
                                break;
                            case 1:
                                _X_Balance_KI=set_pid(height,_X_Balance_KI,1);
                                break;
                            case 2:
                                X_Balance_KD=set_pid(height,X_Balance_KD,1);
                                break;
                            case 3:
                                _X_Velocity_KP=set_pid(height,_X_Velocity_KP,1);
                                break;
                            case 4:
                                _X_Velocity_KI=set_pid(height,_X_Velocity_KI,1);
                                break;
                            case 5:
                                mark=0;
                            break;
                        }
                        //检查当前页是否有数据，如果有数据则需要擦除整个扇区，
                        if(flash_check(EXAMPLE_EEPROM_SECTOR, 0) || flash_check(EXAMPLE_EEPROM_SECTOR, 1) || flash_check(EXAMPLE_EEPROM_SECTOR, 2) || flash_check(EXAMPLE_EEPROM_SECTOR, 3)|| flash_check(EXAMPLE_EEPROM_SECTOR, 4))
                        {
                            eeprom_erase_sector(EXAMPLE_EEPROM_SECTOR);
                        }

                        //当写入的数据不是32位时，建议将数据放入uint32 类型的变量中，在将该变量作为参数传入到eeprom_page_program函数
                        write_buf = X_Balance_KP;
                        //将数据写入EXAMPLE_EEPROM_SECTOR扇区的第0页
                        eeprom_page_program(EXAMPLE_EEPROM_SECTOR, 0, &write_buf);
                        write_buf = _X_Balance_KI;
                        eeprom_page_program(EXAMPLE_EEPROM_SECTOR, 1, &write_buf);
                        write_buf = X_Balance_KD;
                        eeprom_page_program(EXAMPLE_EEPROM_SECTOR, 2, &write_buf);
                        write_buf = _X_Velocity_KP;
                        eeprom_page_program(EXAMPLE_EEPROM_SECTOR, 3, &write_buf);
                        write_buf = _X_Velocity_KI;
                        eeprom_page_program(EXAMPLE_EEPROM_SECTOR, 4, &write_buf);
                        lcd_clear(WHITE);
                        lcd_showstr(0, 0, "X_B_KP");
                        lcd_showstr(0, 1, "X_B_KI");
                        lcd_showstr(0, 2, "X_B_KD");
                        lcd_showstr(0, 3, "X_V_KP");
                        lcd_showstr(0, 4, "X_V_KI");
                        lcd_showstr(0, 5, "exit");
                        lcd_showstr(120, height, "**");
                        lcd_showfloat(70,0,X_Balance_KP,4,1);
                        lcd_showfloat(70,1,(_X_Balance_KI/10),2,1);
                        lcd_showfloat(70,2,X_Balance_KD,3,1);
                        lcd_showfloat(70,3,(-X_Velocity_KP),2,1);
                        lcd_showfloat(70,4,(-X_Velocity_KI/10),2,1);
                        systick_delay_ms(STM0, 50);
                        break;
                    default:break;
                }
        }
    }
}
void ym_ShowBalanceMessage(void)
{
    lcd_showstr(0,0,"ban_duty:");
    lcd_showint32(80,0,MotorDutyA,5);
    lcd_showstr(0,1,"ban_encoder:");
    lcd_showint32(100,1,balance_encoder,5);
    lcd_showstr(0,2,"Pitch: ");
    lcd_showfloat(50,2,Angle_X_Final,2,6);
    //lcd_showstr(0,3,"PID:");
    lcd_showfloat(0,3,X_Velocity_KP,2,4);
    lcd_showfloat(0,4,X_Velocity_KI,2,4);
    lcd_showfloat(0,5,X_Balance_KP,4,4);
    lcd_showfloat(0,6,X_Balance_KI,2,4);
    lcd_showfloat(0,7,X_Balance_KD,3,4);
}
void ym_choose_menu_all(void)
{
    int height=0;
    u8 key=0,mark=1;
    lcd_clear(WHITE);
    lcd_showstr(0, 0, "X_B_PID");
    lcd_showstr(0, 1, "X_V_PID");
    lcd_showstr(0, 2, "S_B_PID");
    lcd_showstr(0, 3, "M_V_PID");
    lcd_showstr(0, 4, "Camera");
    lcd_showstr(0, 5, "exit");
    lcd_showstr(120, height, "**");
    while(mark)
    {
        key=0;
        key=KEY_Scan(0);
        //gpio_toggle(LED0);       //电平翻转,LED闪烁;

        if(key)
        {
                switch(key)
                {
                    case KEY0_PRES:
                        height++;
                        if(height>5)height=0;
                        lcd_clear(WHITE);
                        lcd_showstr(0, 0, "X_B_PID");
                        lcd_showstr(0, 1, "X_V_PID");
                        lcd_showstr(0, 2, "S_B_PID");
                        lcd_showstr(0, 3, "M_V_PID");
                        lcd_showstr(0, 4, "Camera");
                        lcd_showstr(0, 5, "exit");
                        lcd_showstr(120, height, "**");
                        systick_delay_ms(STM0, 50);
                        break;
                    case KEY1_PRES:
                        height--;
                        if(height<5)height=5;
                        lcd_clear(WHITE);
                        lcd_showstr(0, 0, "X_B_PID");
                        lcd_showstr(0, 1, "X_V_PID");
                        lcd_showstr(0, 2, "S_B_PID");
                        lcd_showstr(0, 3, "M_V_PID");
                        lcd_showstr(0, 4, "Camera");
                        lcd_showstr(0, 5, "exit");
                        lcd_showstr(120, height, "**");
                        systick_delay_ms(STM0, 50);
                        break;
                    case KEY2_PRES:
                        lcd_clear(WHITE);
                        switch(height)
                        {
                            case 0:
                                choose_menu_xpid();
                                break;
                            case 1:
                                choose_menu_xpid();;
                                break;
                            case 2:
                                choose_menu_smpid();;
                                break;
                            case 3:
                                choose_menu_smpid();
                                break;
                            case 4:
                               //_X_Velocity_KI=set_pid(height,_X_Velocity_KI,1);
                                break;
                            case 5:
                                mark=0;
                            break;
                        }
                        //检查当前页是否有数据，如果有数据则需要擦除整个扇区，
                        if(flash_check(EXAMPLE_EEPROM_SECTOR, 0) || flash_check(EXAMPLE_EEPROM_SECTOR, 1) || flash_check(EXAMPLE_EEPROM_SECTOR, 2) || flash_check(EXAMPLE_EEPROM_SECTOR, 3)|| flash_check(EXAMPLE_EEPROM_SECTOR, 4))
                        {
                            eeprom_erase_sector(EXAMPLE_EEPROM_SECTOR);
                        }

                        //当写入的数据不是32位时，建议将数据放入uint32 类型的变量中，在将该变量作为参数传入到eeprom_page_program函数
                        write_buf = X_Balance_KP;
                        //将数据写入EXAMPLE_EEPROM_SECTOR扇区的第0页
                        eeprom_page_program(EXAMPLE_EEPROM_SECTOR, 0, &write_buf);
                        write_buf = _X_Balance_KI;
                        eeprom_page_program(EXAMPLE_EEPROM_SECTOR, 1, &write_buf);
                        write_buf = X_Balance_KD;
                        eeprom_page_program(EXAMPLE_EEPROM_SECTOR, 2, &write_buf);
                        write_buf = _X_Velocity_KP;
                        eeprom_page_program(EXAMPLE_EEPROM_SECTOR, 3, &write_buf);
                        write_buf = _X_Velocity_KI;
                        eeprom_page_program(EXAMPLE_EEPROM_SECTOR, 4, &write_buf);
                        lcd_clear(WHITE);
                        lcd_showstr(0, 0, "X_B_KP");
                        lcd_showstr(0, 1, "X_B_KI");
                        lcd_showstr(0, 2, "X_B_KD");
                        lcd_showstr(0, 3, "X_V_KP");
                        lcd_showstr(0, 4, "X_V_KI");
                        lcd_showstr(0, 5, "exit");
                        lcd_showstr(120, height, "**");
                        lcd_showfloat(70,0,X_Balance_KP,4,1);
                        lcd_showfloat(70,1,(_X_Balance_KI/10),2,1);
                        lcd_showfloat(70,2,X_Balance_KD,3,1);
                        lcd_showfloat(70,3,(-X_Velocity_KP),2,1);
                        lcd_showfloat(70,4,(-X_Velocity_KI/10),2,1);
                        systick_delay_ms(STM0, 50);
                        break;
                    default:break;
                }
        }
    }
}

float set_pid(int height,float temp_pid,float weight)
{
    u8 key=0,mark=1;
    lcd_showfloat(0,height,temp_pid,4,6);
    lcd_showstr(0, height+1, "weight");
    lcd_showuint16(80,height+1,weight);
    while(mark)
    {
        key=0;
        key=KEY_Scan(0);
        if(key)
        {
                    switch(key)
                    {
                        case KEY0_PRES:
                            lcd_clear(WHITE);
                            temp_pid+=weight;
                            lcd_showfloat(0,height,temp_pid,4,6);
                            lcd_showstr(0, height+1, "weight");
                            lcd_showuint16(80,height+1,weight);
                            systick_delay_ms(STM0, 50);
                            break;
                        case KEY1_PRES:
                            lcd_clear(WHITE);
                            temp_pid-=weight;
                            lcd_showfloat(0,height,temp_pid,4,6);
                            lcd_showstr(0, height+1, "weight");
                            lcd_showuint16(80,height+1,weight);
                            systick_delay_ms(STM0, 50);
                            break;
                        case KEY3_PRES:
                            lcd_clear(WHITE);
                            weight=weight*10;
                            if(weight>100)weight=1;
                            lcd_showfloat(0,height,temp_pid,4,6);
                            lcd_showstr(0, height+1, "weight");
                            lcd_showuint16(80,height+1,weight);
                            systick_delay_ms(STM0, 150);
                            break;
                        case KEY2_PRES:
                            mark=0;
                            break;
                        default:break;
                    }
        }
    }
    return temp_pid;
}
void choose_menu_smpid(void)
{

    //读取eeprom中的数据
    Balance_Kp = flash_read(EXAMPLE_EEPROM_SECTOR_smpid, 0, uint32);
    _Balance_Ki = flash_read(EXAMPLE_EEPROM_SECTOR_smpid, 1, uint32);
    Balance_Ki=_Balance_Ki/1000;
    _Balance_Kd = flash_read(EXAMPLE_EEPROM_SECTOR_smpid, 2, uint32);
    Balance_Kd=_Balance_Kd/100;
    //_X_Velocity_KP = flash_read(EXAMPLE_EEPROM_SECTOR, 3, uint32);
    Motor_Kp=flash_read(EXAMPLE_EEPROM_SECTOR_smpid, 3, uint32);
    //_X_Velocity_KI = flash_read(EXAMPLE_EEPROM_SECTOR, 4, uint32);
    Motor_Ki=flash_read(EXAMPLE_EEPROM_SECTOR_smpid, 4, uint32);
    int height=0;
    u8 key=0,mark=1;
    lcd_clear(WHITE);
    lcd_showstr(0, 0, "S_B_KP");
    lcd_showstr(0, 1, "S_B_KI");
    lcd_showstr(0, 2, "S_B_KD");
    lcd_showstr(0, 3, "B_V_KP");
    lcd_showstr(0, 4, "B_V_KI");
    lcd_showstr(0, 5, "exit");
    lcd_showstr(120, height, "**");
    lcd_showfloat(70,0,Balance_Kp,2,1);
    lcd_showfloat(70,1,Balance_Ki,1,3);
    lcd_showfloat(70,2,Balance_Kd,1,4);
    lcd_showfloat(70,3,Motor_Kp,2,1);
    lcd_showfloat(70,4,Motor_Ki,2,1);
    while(mark)
    {
        key=0;
        key=KEY_Scan(0);
        //gpio_toggle(LED0);       //电平翻转,LED闪烁;

        if(key)
        {
                switch(key)
                {
                    case KEY0_PRES:
                        height++;
                        if(height>5)height=0;
                        lcd_clear(WHITE);
                        lcd_showstr(0, 0, "S_B_KP");
                        lcd_showstr(0, 1, "S_B_KI");
                        lcd_showstr(0, 2, "S_B_KD");
                        lcd_showstr(0, 3, "B_V_KP");
                        lcd_showstr(0, 4, "B_V_KI");
                        lcd_showstr(0, 5, "exit");
                        lcd_showstr(120, height, "**");
                        lcd_showfloat(70,0,Balance_Kp,2,1);
                        lcd_showfloat(70,1,Balance_Ki,1,3);
                        lcd_showfloat(70,2,Balance_Kd,1,4);
                        lcd_showfloat(70,3,Motor_Kp,2,1);
                        lcd_showfloat(70,4,Motor_Ki,2,1);
                        systick_delay_ms(STM0, 50);
                        break;
                    case KEY1_PRES:
                        height--;
                        if(height<5)height=5;
                        lcd_clear(WHITE);
                        lcd_showstr(0, 0, "S_B_KP");
                        lcd_showstr(0, 1, "S_B_KI");
                        lcd_showstr(0, 2, "S_B_KD");
                        lcd_showstr(0, 3, "B_V_KP");
                        lcd_showstr(0, 4, "B_V_KI");
                        lcd_showstr(0, 5, "exit");
                        lcd_showstr(120, height, "**");
                        lcd_showfloat(70,0,Balance_Kp,2,1);
                        lcd_showfloat(70,1,Balance_Ki,1,3);
                        lcd_showfloat(70,2,Balance_Kd,1,4);
                        lcd_showfloat(70,3,Motor_Kp,2,1);
                        lcd_showfloat(70,4,Motor_Ki,2,1);
                        systick_delay_ms(STM0, 50);
                        break;
                    case KEY2_PRES:
                        lcd_clear(WHITE);
                        switch(height)
                        {
                            case 0:
                                Balance_Kp=set_pid(height,Balance_Kp,1);
                                break;
                            case 1:
                                Balance_Ki=set_pid(height,_Balance_Ki,1);
                                break;
                            case 2:
                                Balance_Kd=set_pid(height,_Balance_Kd,1);
                                break;
                            case 3:
                                Motor_Kp=set_pid(height,Motor_Kp,1);
                                break;
                            case 4:
                                Motor_Ki=set_pid(height,Motor_Ki,1);
                                break;
                            case 5:
                                mark=0;
                            break;
                        }
                        //检查当前页是否有数据，如果有数据则需要擦除整个扇区，
                        if(flash_check(EXAMPLE_EEPROM_SECTOR_smpid, 0) || flash_check(EXAMPLE_EEPROM_SECTOR_smpid, 1) || flash_check(EXAMPLE_EEPROM_SECTOR_smpid, 2) || flash_check(EXAMPLE_EEPROM_SECTOR_smpid, 3)|| flash_check(EXAMPLE_EEPROM_SECTOR_smpid, 4))
                        {
                            eeprom_erase_sector(EXAMPLE_EEPROM_SECTOR_smpid);
                        }

                        //当写入的数据不是32位时，建议将数据放入uint32 类型的变量中，在将该变量作为参数传入到eeprom_page_program函数
                        write_buf = Balance_Kp;
                        //将数据写入EXAMPLE_EEPROM_SECTOR扇区的第0页
                        eeprom_page_program(EXAMPLE_EEPROM_SECTOR_smpid, 0, &write_buf);
                        write_buf = _Balance_Ki;
                        eeprom_page_program(EXAMPLE_EEPROM_SECTOR_smpid, 1, &write_buf);
                        write_buf = _Balance_Kd;
                        eeprom_page_program(EXAMPLE_EEPROM_SECTOR_smpid, 2, &write_buf);
                        write_buf = Motor_Kp;
                        eeprom_page_program(EXAMPLE_EEPROM_SECTOR_smpid, 3, &write_buf);
                        write_buf = Motor_Kp;
                        eeprom_page_program(EXAMPLE_EEPROM_SECTOR_smpid, 4, &write_buf);
                        lcd_clear(WHITE);
                        lcd_showstr(0, 0, "S_B_KP");
                        lcd_showstr(0, 1, "S_B_KI");
                        lcd_showstr(0, 2, "S_B_KD");
                        lcd_showstr(0, 3, "B_V_KP");
                        lcd_showstr(0, 4, "B_V_KI");
                        lcd_showstr(0, 5, "exit");
                        lcd_showstr(120, height, "**");
                        lcd_showfloat(70,0,Balance_Kp,2,1);
                        lcd_showfloat(70,1,Balance_Ki/1000,1,3);
                        lcd_showfloat(70,2,Balance_Kd/100,1,4);
                        lcd_showfloat(70,3,Motor_Kp,2,1);
                        lcd_showfloat(70,4,Motor_Ki,2,1);
                        systick_delay_ms(STM0, 50);
                        break;
                    default:break;
                }
        }
    }
}
