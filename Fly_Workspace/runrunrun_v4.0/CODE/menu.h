/*
 * menu.h
 *
 *  Created on: 2022��2��19��
 *      Author: czh
 */

#ifndef USER_MENU_H_
#define USER_MENU_H_

#include "Cpu0_Main.h"
#include "headfile.h"
#include "SEEKFREE_MT9V03X.h"
#include "key.h"
#define u8 uint8
#define EXAMPLE_EEPROM_SECTOR        (0)
void choose_menu(void);
float set_pid(int height,float temp_pid,float weight);
#endif /* USER_MENU_H_ */
