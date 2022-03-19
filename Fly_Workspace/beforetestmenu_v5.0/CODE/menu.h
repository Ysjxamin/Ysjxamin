/*
 * menu.h
 *
 *  Created on: 2022Äê2ÔÂ19ÈÕ
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
#define EXAMPLE_EEPROM_SECTOR_smpid        (1)
void choose_menu_xpid(void);
void choose_menu_smpid(void);
float set_pid(int height,float temp_pid,float weight);
void ym_ShowBalanceMessage(void);
void ym_choose_menu_all(void);
#endif /* USER_MENU_H_ */
