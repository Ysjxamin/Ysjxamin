/*
 * menu.c
 *
 *  Created on: 2022年2月19日
 *      Author: czh
 */

#include "menu.h"
uint16 flag_1 =0;
uint16 flag_2 =0 ;
uint16 flag_3 =0 ;
uint16 flag_4 =0 ;
extern float X_Balance_KP;
extern float X_Balance_KI;
extern float X_Balance_KD;
extern float X_Velocity_KP;
extern float X_Velocity_KI;
uint32 write_buf;

void choose_menu(void)
{

    //读取eeprom中的数据
    X_Balance_KP = flash_read(EXAMPLE_EEPROM_SECTOR, 0, float);
    X_Balance_KI = flash_read(EXAMPLE_EEPROM_SECTOR, 1, float);
    X_Balance_KD = flash_read(EXAMPLE_EEPROM_SECTOR, 2, float);
    X_Velocity_KP = flash_read(EXAMPLE_EEPROM_SECTOR, 3, float);
    X_Velocity_KI = flash_read(EXAMPLE_EEPROM_SECTOR, 4, float);
    int height=0;
    u8 key=0,mark=1;
    lcd_clear(WHITE);
    lcd_showstr(0, 0, "X_Balance_KP");
    lcd_showstr(0, 1, "X_Balance_KI");
    lcd_showstr(0, 2, "X_Balance_KD");
    lcd_showstr(0, 3, "X_Velocity_KP");
    lcd_showstr(0, 4, "X_Velocity_KI");
    lcd_showstr(0, 5, "exit");
    lcd_showstr(120, height, "**");
    lcd_showfloat(70,0,X_Balance_KP,4,6);
    lcd_showfloat(70,1,X_Balance_KI,2,6);
    lcd_showfloat(70,2,X_Balance_KD,3,6);
    lcd_showfloat(70,3,X_Velocity_KP,2,6);
    lcd_showfloat(70,4,X_Velocity_KI,2,6);
    while(mark)
    {
        key=0;
        key=KEY_Scan(0);
        if(key)
        {
                switch(key)
                {
                    case KEY0_PRES:
                        height++;
                        if(height>4)height=0;
                        lcd_clear(WHITE);
                        lcd_showstr(0, 0, "X_Balance_KP");
                        lcd_showstr(0, 1, "X_Balance_KI");
                        lcd_showstr(0, 2, "X_Balance_KD");
                        lcd_showstr(0, 3, "X_Velocity_KP");
                        lcd_showstr(0, 4, "X_Velocity_KI");
                        lcd_showstr(0, 5, "exit");
                        lcd_showstr(120, height, "**");
                        lcd_showfloat(70,0,X_Balance_KP,4,6);
                        lcd_showfloat(70,1,X_Balance_KI,2,6);
                        lcd_showfloat(70,2,X_Balance_KD,3,6);
                        lcd_showfloat(70,3,X_Velocity_KP,2,6);
                        lcd_showfloat(70,4,X_Velocity_KI,2,6);
                        systick_delay_ms(STM0, 50);
                        break;
                    case KEY1_PRES:
                        height--;
                        if(height<0)height=4;
                        lcd_clear(WHITE);
                        lcd_showstr(0, 0, "X_Balance_KP");
                        lcd_showstr(0, 1, "X_Balance_KI");
                        lcd_showstr(0, 2, "X_Balance_KD");
                        lcd_showstr(0, 3, "X_Velocity_KP");
                        lcd_showstr(0, 4, "X_Velocity_KI");
                        lcd_showstr(0, 5, "exit");
                        lcd_showstr(120, height, "**");
                        lcd_showfloat(70,0,X_Balance_KP,4,6);
                        lcd_showfloat(70,1,X_Balance_KI,2,6);
                        lcd_showfloat(70,2,X_Balance_KD,3,6);
                        lcd_showfloat(70,3,X_Velocity_KP,2,6);
                        lcd_showfloat(70,4,X_Velocity_KI,2,6);
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
                                X_Balance_KI=set_pid(height,X_Balance_KI,1);
                                break;
                            case 2:
                                X_Balance_KD=set_pid(height,X_Balance_KD,1);
                                break;
                            case 3:
                                X_Velocity_KP=set_pid(height,X_Velocity_KP,1);
                                break;
                            case 4:
                                X_Velocity_KI=set_pid(height,X_Velocity_KI,1);
                                break;
                            case 5:
                                mark=0;
                            break;
                        }
                        //检查当前页是否有数据，如果有数据则需要擦除整个扇区，
                        if(flash_check(EXAMPLE_EEPROM_SECTOR, 0) || flash_check(EXAMPLE_EEPROM_SECTOR, 1) || flash_check(EXAMPLE_EEPROM_SECTOR, 2) || flash_check(EXAMPLE_EEPROM_SECTOR, 3)|| flash_check(EXAMPLE_EEPROM_SECTOR, 4)|| flash_check(EXAMPLE_EEPROM_SECTOR, 5))
                        {
                            eeprom_erase_sector(EXAMPLE_EEPROM_SECTOR);
                        }

                        //当写入的数据不是32位时，建议将数据放入uint32 类型的变量中，在将该变量作为参数传入到eeprom_page_program函数
                        write_buf = X_Balance_KP;
                        //将数据写入EXAMPLE_EEPROM_SECTOR扇区的第0页
                        eeprom_page_program(EXAMPLE_EEPROM_SECTOR, 0, &write_buf);
                        write_buf = X_Balance_KI;
                        eeprom_page_program(EXAMPLE_EEPROM_SECTOR, 1, &write_buf);
                        write_buf = X_Balance_KD;
                        eeprom_page_program(EXAMPLE_EEPROM_SECTOR, 2, &write_buf);
                        write_buf = X_Velocity_KP;
                        eeprom_page_program(EXAMPLE_EEPROM_SECTOR, 3, &write_buf);
                        write_buf = X_Velocity_KI;
                        eeprom_page_program(EXAMPLE_EEPROM_SECTOR, 4, &write_buf);
                        lcd_clear(WHITE);
                        lcd_showstr(0, 0, "X_Balance_KP");
                        lcd_showstr(0, 1, "X_Balance_KI");
                        lcd_showstr(0, 2, "X_Balance_KD");
                        lcd_showstr(0, 3, "X_Velocity_KP");
                        lcd_showstr(0, 4, "X_Velocity_KI");
                        lcd_showstr(0, 5, "exit");
                        lcd_showstr(120, height, "**");
                        lcd_showfloat(70,0,X_Balance_KP,4,6);
                        lcd_showfloat(70,1,X_Balance_KI,2,6);
                        lcd_showfloat(70,2,X_Balance_KD,3,6);
                        lcd_showfloat(70,3,X_Velocity_KP,2,6);
                        lcd_showfloat(70,4,X_Velocity_KI,2,6);
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
