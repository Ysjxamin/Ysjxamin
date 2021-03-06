/*********************************************************************************************************//**
 * @file    USART/Interrupt/ht32_board_config.h
 * @version $Rev:: 5575         $
 * @date    $Date:: 2021-08-18 #$
 * @brief   The header file of board configuration.
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
/* Define to prevent recursive inclusion -------------------------------------------------------------------*/
#ifndef __HT32_BOARD_CONFIG_H
#define __HT32_BOARD_CONFIG_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Settings ------------------------------------------------------------------------------------------------*/
#if defined(USE_HT32F52230_SK)
  #define _HTCFG_UART_TX_GPIOX                    A
  #define _HTCFG_UART_TX_GPION                    4
  #define _HTCFG_UART_RX_GPIOX                    A
  #define _HTCFG_UART_RX_GPION                    5
  #define HTCFG_UART_IPN                          UART0
#endif

#if defined(USE_HT32F52241_SK)
  #define _HTCFG_UART_TX_GPIOX                    A
  #define _HTCFG_UART_TX_GPION                    4
  #define _HTCFG_UART_RX_GPIOX                    A
  #define _HTCFG_UART_RX_GPION                    5
  #define HTCFG_UART_IPN                          UART1
#endif

#if defined(USE_HT32F52253_SK)
  #define _HTCFG_UART_TX_GPIOX                    A
  #define _HTCFG_UART_TX_GPION                    4
  #define _HTCFG_UART_RX_GPIOX                    A
  #define _HTCFG_UART_RX_GPION                    5
  #define HTCFG_UART_IPN                          USART1
#endif

#if defined(USE_HT32F52341_SK)
  #define _HTCFG_UART_TX_GPIOX                    A
  #define _HTCFG_UART_TX_GPION                    4
  #define _HTCFG_UART_RX_GPIOX                    A
  #define _HTCFG_UART_RX_GPION                    5
  #define HTCFG_UART_IPN                          UART1
#endif

#if defined(USE_HT32F52352_SK)
  #define _HTCFG_UART_TX_GPIOX                    A
  #define _HTCFG_UART_TX_GPION                    4
  #define _HTCFG_UART_RX_GPIOX                    A
  #define _HTCFG_UART_RX_GPION                    5
  #define HTCFG_UART_IPN                          USART1
#endif

#if defined(USE_HT32F0008_SK)
  #define _HTCFG_UART_TX_GPIOX                    A
  #define _HTCFG_UART_TX_GPION                    4
  #define _HTCFG_UART_RX_GPIOX                    A
  #define _HTCFG_UART_RX_GPION                    5
  #define HTCFG_UART_IPN                          UART0
#endif

#if defined(USE_HT32F50230_SK)
  #define _HTCFG_UART_TX_GPIOX                    A
  #define _HTCFG_UART_TX_GPION                    4
  #define _HTCFG_UART_RX_GPIOX                    A
  #define _HTCFG_UART_RX_GPION                    5
  #define HTCFG_UART_IPN                          UART1
#endif

#if defined(USE_HT32F50241_SK)
  #define _HTCFG_UART_TX_GPIOX                    A
  #define _HTCFG_UART_TX_GPION                    4
  #define _HTCFG_UART_RX_GPIOX                    A
  #define _HTCFG_UART_RX_GPION                    5
  #define HTCFG_UART_IPN                          UART1
#endif

#if defined(USE_HT32F52354_SK)
  #define _HTCFG_UART_TX_GPIOX                    A
  #define _HTCFG_UART_TX_GPION                    4
  #define _HTCFG_UART_RX_GPIOX                    A
  #define _HTCFG_UART_RX_GPION                    5
  #define HTCFG_UART_IPN                          UART1
#endif

#if defined(USE_HT32F0006_DVB)
  #define _HTCFG_UART_TX_GPIOX                    A
  #define _HTCFG_UART_TX_GPION                    2
  #define _HTCFG_UART_RX_GPIOX                    A
  #define _HTCFG_UART_RX_GPION                    3
  #define HTCFG_UART_IPN                          USART0
#endif

#if defined(USE_HT32F57341_SK)
  #define _HTCFG_UART_TX_GPIOX                    A
  #define _HTCFG_UART_TX_GPION                    4
  #define _HTCFG_UART_RX_GPIOX                    A
  #define _HTCFG_UART_RX_GPION                    5
  #define HTCFG_UART_IPN                          USART0
#endif

#if defined(USE_HT32F57352_SK)
  #define _HTCFG_UART_TX_GPIOX                    A
  #define _HTCFG_UART_TX_GPION                    4
  #define _HTCFG_UART_RX_GPIOX                    A
  #define _HTCFG_UART_RX_GPION                    5
  #define HTCFG_UART_IPN                          USART0
#endif

#if defined(USE_HT32F52367_SK)
  #define _HTCFG_UART_TX_GPIOX                    A
  #define _HTCFG_UART_TX_GPION                    4
  #define _HTCFG_UART_RX_GPIOX                    A
  #define _HTCFG_UART_RX_GPION                    5
  #define HTCFG_UART_IPN                          USART1
#endif

#if defined(USE_HT32F50343_SK)
  #define _HTCFG_UART_TX_GPIOX                    A
  #define _HTCFG_UART_TX_GPION                    4
  #define _HTCFG_UART_RX_GPIOX                    A
  #define _HTCFG_UART_RX_GPION                    5
  #define HTCFG_UART_IPN                          UART1
#endif

#if defined(USE_HT32F65240_DVB)
  #define _HTCFG_UART_TX_GPIOX                    A
  #define _HTCFG_UART_TX_GPION                    3
  #define _HTCFG_UART_RX_GPIOX                    A
  #define _HTCFG_UART_RX_GPION                    1
  #define HTCFG_UART_IPN                          USART0
#endif

#if defined(USE_HT32F65240_SK)
  #define _HTCFG_UART_TX_GPIOX                    A
  #define _HTCFG_UART_TX_GPION                    4
  #define _HTCFG_UART_RX_GPIOX                    A
  #define _HTCFG_UART_RX_GPION                    5
  #define HTCFG_UART_IPN                          UART0
#endif

#if defined(USE_HT32F65232_SK)  //PRELIMINARY_NOT_TEST
  #define _HTCFG_UART_TX_GPIOX                    A
  #define _HTCFG_UART_TX_GPION                    4
  #define _HTCFG_UART_RX_GPIOX                    A
  #define _HTCFG_UART_RX_GPION                    5
  #define HTCFG_UART_IPN                          UART0
#endif

#if defined(USE_HT32F61355_SK) || defined(USE_HT32F61356_SK) || defined(USE_HT32F61357_SK)
  #define _HTCFG_UART_TX_GPIOX                    C
  #define _HTCFG_UART_TX_GPION                    4
  #define _HTCFG_UART_RX_GPIOX                    C
  #define _HTCFG_UART_RX_GPION                    5
  #define HTCFG_UART_IPN                          UART0
#endif

#if defined(USE_HT32F54241_SK)
  #define _HTCFG_UART_TX_GPIOX                    A
  #define _HTCFG_UART_TX_GPION                    4
  #define _HTCFG_UART_RX_GPIOX                    A
  #define _HTCFG_UART_RX_GPION                    5
  #define HTCFG_UART_IPN                          UART1
#endif

#if defined(USE_HT32F54253_SK)
  #define _HTCFG_UART_TX_GPIOX                    A
  #define _HTCFG_UART_TX_GPION                    4
  #define _HTCFG_UART_RX_GPIOX                    A
  #define _HTCFG_UART_RX_GPION                    5
  #define HTCFG_UART_IPN                          USART1
#endif
#if defined(USE_HT32F52352_SK)
  #define HTCFG_OUTPUT_LED0_ID                                  (GPIO_PC)
  #define HTCFG_OUTPUT_LED1_ID                                  (GPIO_PC)
  #define HTCFG_OUTPUT_LED2_ID                                  (GPIO_PC)
  #define HTCFG_INPUT_WAKE_ID                                   (GPIO_PB)
  #define HTCFG_INPUT_KEY1_ID                                   (GPIO_PD)
  #define HTCFG_INPUT_KEY2_ID                                   (GPIO_PD)

  #define HTCFG_OUTPUT_LED0_CLK(CK)                             (CK.Bit.PC)
  #define HTCFG_OUTPUT_LED1_CLK(CK)                             (CK.Bit.PC)
  #define HTCFG_OUTPUT_LED2_CLK(CK)                             (CK.Bit.PC)
  #define HTCFG_INPUT_WAKE_CLK(CK)                              (CK.Bit.PB)
  #define HTCFG_INPUT_KEY1_CLK(CK)                              (CK.Bit.PD)
  #define HTCFG_INPUT_KEY2_CLK(CK)                              (CK.Bit.PD)

  #define HTCFG_LED0                                            (HT_GPIOC)
  #define HTCFG_LED1                                            (HT_GPIOC)
  #define HTCFG_LED2                                            (HT_GPIOC)
  #define HTCFG_WAKE                                            (HT_GPIOB)
  #define HTCFG_KEY1                                            (HT_GPIOD)
  #define HTCFG_KEY2                                            (HT_GPIOD)
//RC522 AFI0	
  //????	
  #define HTCFG_OUTPUT_RC522_SDA_AFIO_PIN                       (AFIO_PIN_0)
  #define HTCFG_OUTPUT_RC522_SCK_AFIO_PIN                       (AFIO_PIN_1)
  #define HTCFG_OUTPUT_RC522_MOSI_AFIO_PIN                      (AFIO_PIN_2)
  #define HTCFG_OUTPUT_RC522_RST_AFIO_PIN                       (AFIO_PIN_3)
	//????
  #define HTCFG_INPUT_RC522_MISO_AFIO_PIN                       (AFIO_PIN_4)	
	
	//RC522 GPIO	
  //????	
  #define HTCFG_OUTPUT_RC522_SDA_GPIO_PIN                       (AFIO_PIN_0)
  #define HTCFG_OUTPUT_RC522_SCK_GPIO_PIN                       (AFIO_PIN_1)
  #define HTCFG_OUTPUT_RC522_MOSI_GPIO_PIN                      (AFIO_PIN_2)
  #define HTCFG_OUTPUT_RC522_RST_GPIO_PIN                       (AFIO_PIN_3)
	//????
  #define HTCFG_INPUT_RC522_MISO_GPIO_PIN                       (AFIO_PIN_4)

  #define HTCFG_OUTPUT_LED0_AFIO_PIN                            (AFIO_PIN_14)
  #define HTCFG_OUTPUT_LED1_AFIO_PIN                            (AFIO_PIN_15)
  #define HTCFG_OUTPUT_LED2_AFIO_PIN                            (AFIO_PIN_1)
  #define HTCFG_INPUT_WAKE_AFIO_PIN                             (AFIO_PIN_12)
  #define HTCFG_INPUT_KEY1_AFIO_PIN                             (AFIO_PIN_1)
  #define HTCFG_INPUT_KEY2_AFIO_PIN                             (AFIO_PIN_2)

  #define HTCFG_OUTPUT_LED0_GPIO_PIN                            (GPIO_PIN_14)
  #define HTCFG_OUTPUT_LED1_GPIO_PIN                            (GPIO_PIN_15)
  #define HTCFG_OUTPUT_LED2_GPIO_PIN                            (GPIO_PIN_1)
  #define HTCFG_INPUT_WAKE_GPIO_PIN                             (GPIO_PIN_12)
  #define HTCFG_INPUT_KEY1_GPIO_PIN                             (GPIO_PIN_1)
  #define HTCFG_INPUT_KEY2_GPIO_PIN                             (GPIO_PIN_2)
#endif
#define HTCFG_UART_TX_GPIO_ID                     STRCAT2(GPIO_P,         _HTCFG_UART_TX_GPIOX)
#define HTCFG_UART_RX_GPIO_ID                     STRCAT2(GPIO_P,         _HTCFG_UART_RX_GPIOX)
#define HTCFG_UART_TX_AFIO_PIN                    STRCAT2(AFIO_PIN_,      _HTCFG_UART_TX_GPION)
#define HTCFG_UART_RX_AFIO_PIN                    STRCAT2(AFIO_PIN_,      _HTCFG_UART_RX_GPION)
#define HTCFG_UART_PORT                           STRCAT2(HT_,             HTCFG_UART_IPN)
#define HTCFG_UART_IRQn                           STRCAT2(HTCFG_UART_IPN, _IRQn)
#define HTCFG_UART_IRQHandler                     STRCAT2(HTCFG_UART_IPN, _IRQHandler)

#define HTCFG_UART_RX_GPIO_CLK                    STRCAT2(P,              _HTCFG_UART_RX_GPIOX)
#define HTCFG_UART_RX_GPIO_PORT                   STRCAT2(HT_GPIO,        _HTCFG_UART_RX_GPIOX)
#define HTCFG_UART_RX_GPIO_PIN                    STRCAT2(GPIO_PIN_,      _HTCFG_UART_RX_GPION)

//#define GPIO_SetOutBits(HT_GPIOC,GPIO_PIN_14);
//	GPIO_ClearOutBits(HT_GPIOC,GPIO_PIN_14);

#define MF522_NSS_1 GPIO_SetOutBits(HT_GPIOB,GPIO_PIN_0)	//PB0	 SDA
#define MF522_SCK_1 GPIO_SetOutBits(HT_GPIOB,GPIO_PIN_1)	//PB1
#define MF522_SI_1  GPIO_SetOutBits(HT_GPIOB,GPIO_PIN_2)	//PB2
#define MF522_SO  GPIO_ReadInBit(HT_GPIOB,GPIO_PIN_4)	  //PB4   IN
#define MF522_RST_1 GPIO_SetOutBits(HT_GPIOB,GPIO_PIN_3)	//PB3

#define MF522_NSS_0 GPIO_ClearOutBits(HT_GPIOB,GPIO_PIN_0)	//PB0	 SDA
#define MF522_SCK_0 GPIO_ClearOutBits(HT_GPIOB,GPIO_PIN_1)	//PB1
#define MF522_SI_0  GPIO_ClearOutBits(HT_GPIOB,GPIO_PIN_2)	//PB2
#define MF522_SO  GPIO_ReadInBit(HT_GPIOB,GPIO_PIN_4)	  //PB4   IN
#define MF522_RST_0 GPIO_ClearOutBits(HT_GPIOB,GPIO_PIN_3)	//PB3

#define MF522_NSS GPIO_WriteOutBits(HT_GPIOC,GPIO_PIN_14, 1)
//HT_GPIOB->SRR = GPIO_PIN_0;
/////////////////////////////////////////////////////////////////////
//MF522??????
/////////////////////////////////////////////////////////////////////
#define PCD_IDLE              0x00               //????????????
#define PCD_AUTHENT           0x0E               //????????
#define PCD_RECEIVE           0x08               //????????
#define PCD_TRANSMIT          0x04               //????????
#define PCD_TRANSCEIVE        0x0C               //??????????????
#define PCD_RESETPHASE        0x0F               //????
#define PCD_CALCCRC           0x03               //CRC????

/////////////////////////////////////////////////////////////////////
//Mifare_One??????????
/////////////////////////////////////////////////////////////////////
#define PICC_REQIDL           0x26               //????????????????????????
#define PICC_REQALL           0x52               //????????????????
#define PICC_ANTICOLL1        0x93               //??????
#define PICC_ANTICOLL2        0x95               //??????
#define PICC_AUTHENT1A        0x60               //????A????
#define PICC_AUTHENT1B        0x61               //????B????
#define PICC_READ             0x30               //????
#define PICC_WRITE            0xA0               //????
#define PICC_DECREMENT        0xC0               //????
#define PICC_INCREMENT        0xC1               //????
#define PICC_RESTORE          0xC2               //????????????????
#define PICC_TRANSFER         0xB0               //????????????????
#define PICC_HALT             0x50               //????

/////////////////////////////////////////////////////////////////////
//MF522 FIFO????????
/////////////////////////////////////////////////////////////////////
#define DEF_FIFO_LENGTH       64                 //FIFO size=64byte

/////////////////////////////////////////////////////////////////////
//MF522??????????
/////////////////////////////////////////////////////////////////////
// PAGE 0
#define     RFU00                 0x00    
#define     CommandReg            0x01    
#define     ComIEnReg             0x02    
#define     DivlEnReg             0x03    
#define     ComIrqReg             0x04    
#define     DivIrqReg             0x05
#define     ErrorReg              0x06    
#define     Status1Reg            0x07    
#define     Status2Reg            0x08    
#define     FIFODataReg           0x09
#define     FIFOLevelReg          0x0A
#define     WaterLevelReg         0x0B
#define     ControlReg            0x0C
#define     BitFramingReg         0x0D
#define     CollReg               0x0E
#define     RFU0F                 0x0F
// PAGE 1     
#define     RFU10                 0x10
#define     ModeReg               0x11
#define     TxModeReg             0x12
#define     RxModeReg             0x13
#define     TxControlReg          0x14
#define     TxAutoReg             0x15
#define     TxSelReg              0x16
#define     RxSelReg              0x17
#define     RxThresholdReg        0x18
#define     DemodReg              0x19
#define     RFU1A                 0x1A
#define     RFU1B                 0x1B
#define     MifareReg             0x1C
#define     RFU1D                 0x1D
#define     RFU1E                 0x1E
#define     SerialSpeedReg        0x1F
// PAGE 2    
#define     RFU20                 0x20  
#define     CRCResultRegM         0x21
#define     CRCResultRegL         0x22
#define     RFU23                 0x23
#define     ModWidthReg           0x24
#define     RFU25                 0x25
#define     RFCfgReg              0x26
#define     GsNReg                0x27
#define     CWGsCfgReg            0x28
#define     ModGsCfgReg           0x29
#define     TModeReg              0x2A
#define     TPrescalerReg         0x2B
#define     TReloadRegH           0x2C
#define     TReloadRegL           0x2D
#define     TCounterValueRegH     0x2E
#define     TCounterValueRegL     0x2F
// PAGE 3      
#define     RFU30                 0x30
#define     TestSel1Reg           0x31
#define     TestSel2Reg           0x32
#define     TestPinEnReg          0x33
#define     TestPinValueReg       0x34
#define     TestBusReg            0x35
#define     AutoTestReg           0x36
#define     VersionReg            0x37
#define     AnalogTestReg         0x38
#define     TestDAC1Reg           0x39  
#define     TestDAC2Reg           0x3A   
#define     TestADCReg            0x3B   
#define     RFU3C                 0x3C   
#define     RFU3D                 0x3D   
#define     RFU3E                 0x3E   
#define     RFU3F		  0x3F

/////////////////////////////////////////////////////////////////////
//??MF522????????????????????
/////////////////////////////////////////////////////////////////////
#define MI_OK                          0
#define MI_NOTAGERR                    (-1)
#define MI_ERR                         (-2)


#ifdef __cplusplus
}
#endif

#endif
