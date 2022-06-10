/*********************************************************************************************************//**
 * @file    USART/Interrupt/ht32f5xxxx_01_it.c
 * @version $Rev:: 4679         $
 * @date    $Date:: 2020-03-12 #$
 * @brief   This file provides all interrupt service routine.
 *************************************************************************************************************
 * @attention
 *
 * Firmware Disclaimer Information
 *
 * 1. The customer hereby acknowledges and agrees that the program technical documentation, including the
 *    code, which is supplied by Holtek Semiconductor Inc., (hereinafter referred to as "HOLTEK") is the
 *    proprietary and confidential intellectual property of HOLTEK, and is protected by copyright law and
 *    other intellectual property laws.
 *
 * 2. The customer hereby acknowledges and agrees that the program technical documentation, including the
 *    code, is confidential information belonging to HOLTEK, and must not be disclosed to any third parties
 *    other than HOLTEK and the customer.
 *
 * 3. The program technical documentation, including the code, is provided "as is" and for customer reference
 *    only. After delivery by HOLTEK, the customer shall use the program technical documentation, including
 *    the code, at their own risk. HOLTEK disclaims any expressed, implied or statutory warranties, including
 *    the warranties of merchantability, satisfactory quality and fitness for a particular purpose.
 *
 * <h2><center>Copyright (C) Holtek Semiconductor Inc. All rights reserved</center></h2>
 ************************************************************************************************************/

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32.h"
#include "ht32_board.h"
#include "ht32_board_config.h"

/** @addtogroup HT32_Series_Peripheral_Examples HT32 Peripheral Examples
  * @{
  */

/** @addtogroup USART_Examples USART
  * @{
  */

/** @addtogroup Interrupt
  * @{
  */


/* Global functions ----------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
 * @brief   This function handles NMI exception.
 * @retval  None
 ************************************************************************************************************/
void NMI_Handler(void)
{
}

/*********************************************************************************************************//**
 * @brief   This function handles Hard Fault exception.
 * @retval  None
 ************************************************************************************************************/
void HardFault_Handler(void)
{
  #if 1

  static vu32 gIsContinue = 0;
  /*--------------------------------------------------------------------------------------------------------*/
  /* For development FW, MCU run into the while loop when the hardfault occurred.                           */
  /* 1. Stack Checking                                                                                      */
  /*    When a hard fault exception occurs, MCU push following register into the stack (main or process     */
  /*    stack). Confirm R13(SP) value in the Register Window and typing it to the Memory Windows, you can   */
  /*    check following register, especially the PC value (indicate the last instruction before hard fault).*/
  /*    SP + 0x00    0x04    0x08    0x0C    0x10    0x14    0x18    0x1C                                   */
  /*           R0      R1      R2      R3     R12      LR      PC    xPSR                                   */
  while (gIsContinue == 0)
  {
  }
  /* 2. Step Out to Find the Clue                                                                           */
  /*    Change the variable "gIsContinue" to any other value than zero in a Local or Watch Window, then     */
  /*    step out the HardFault_Handler to reach the first instruction after the instruction which caused    */
  /*    the hard fault.                                                                                     */
  /*--------------------------------------------------------------------------------------------------------*/

  #else

  /*--------------------------------------------------------------------------------------------------------*/
  /* For production FW, you shall consider to reboot the system when hardfault occurred.                    */
  /*--------------------------------------------------------------------------------------------------------*/
  NVIC_SystemReset();

  #endif
}

/*********************************************************************************************************//**
 * @brief   This function handles SVCall exception.
 * @retval  None
 ************************************************************************************************************/
void SVC_Handler(void)
{
}

/*********************************************************************************************************//**
 * @brief   This function handles PendSVC exception.
 * @retval  None
 ************************************************************************************************************/
void PendSV_Handler(void)
{
}

/*********************************************************************************************************//**
 * @brief   This function handles SysTick Handler.
 * @retval  None
 ************************************************************************************************************/
void SysTick_Handler(void)
{
}

#define DEBUG_IO          (0)
/*********************************************************************************************************//**
 * @brief   This function handles UxARTn interrupt.
 * @retval  None
 ************************************************************************************************************/
void HTCFG_UART_IRQHandler(void)
{
  extern uc8  *gURTx_Ptr;
  extern vu32  gURTx_Length;
  extern u8   *gURRx_Ptr;
  extern vu32  gURRx_Length;
  extern vu32 gIsTxFinished;

#if (DEBUG_IO == 1)
  #define DBG_IO1_LO()    HT32F_DVB_LEDOn(HT_LED1)
  #define DBG_IO1_HI()    HT32F_DVB_LEDOff(HT_LED1)
  #define DBG_IO2_LO()    HT32F_DVB_LEDOn(HT_LED2)
  #define DBG_IO2_HI()    HT32F_DVB_LEDOff(HT_LED2)
#else
  #define DBG_IO1_LO(...)
  #define DBG_IO1_HI(...)
  #define DBG_IO2_LO(...)
  #define DBG_IO2_HI(...)
#endif

  /* Rx: Move data from UART to buffer                                                                      */
  if (USART_GetFlagStatus(HTCFG_UART_PORT, USART_FLAG_RXDR))
  {
    DBG_IO1_LO();
    gURRx_Ptr[gURRx_Length++] = USART_ReceiveData(HTCFG_UART_PORT);
    DBG_IO1_HI();

    #if 0
    if (gURRx_Length == 128)
    {
      while (1) {}; // Rx Buffer full
    }
    #endif
  }

  /* Tx, move data from buffer to UART                                                                      */
  if (USART_GetIntStatus(HTCFG_UART_PORT, USART_INT_TXDE) &&
      USART_GetFlagStatus(HTCFG_UART_PORT, USART_FLAG_TXDE))
  {
    DBG_IO2_LO();
    if (gURTx_Length > 0)
    {
      USART_SendData(HTCFG_UART_PORT, *gURTx_Ptr++);
      gURTx_Length--;
      if (gURTx_Length == 0)
      {
        USART_IntConfig(HTCFG_UART_PORT, USART_INT_TXDE, DISABLE);
      }
    }
    DBG_IO2_HI();
  }

  if (USART_GetIntStatus(HTCFG_UART_PORT, USART_INT_TXC) &&
      USART_GetFlagStatus(HTCFG_UART_PORT, USART_FLAG_TXC))
  {
    USART_IntConfig(HTCFG_UART_PORT, USART_INT_TXC, DISABLE);
    gIsTxFinished = TRUE;
  }
}


/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
