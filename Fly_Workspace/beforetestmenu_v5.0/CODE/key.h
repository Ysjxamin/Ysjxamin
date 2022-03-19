/*
 * key.h
 *
 *  Created on: 2022��2��19��
 *      Author: czh
 */

#ifndef USER_KEY_H_
#define USER_KEY_H_
#include "Cpu0_Main.h"
#include "headfile.h"
#include "SEEKFREE_MT9V03X.h"
#define u8 uint8
#define u16 uint16
#define u32 uint32


#define KEY0_PRES   1   //KEY0����
#define KEY1_PRES   2   //KEY1����
#define KEY2_PRES   3   //KEY2����
#define KEY3_PRES   4   //KEY2����

void GPIO_KEY_Init(void);
uint8 KEY_Scan(uint8 mode);
void delay_ms(int count);


void touch_key (void);
void touch_key1 (void);
void touch_key2 (void);
void touch_key3 (void);
void touch_key4 (void);

#endif /* USER_KEY_H_ */
