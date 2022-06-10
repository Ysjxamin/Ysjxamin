//IREva.c红外避障.C程序

#include "IREva.h"  


void IREva_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/*开启按键端口的时钟*/
	RCC_APB2PeriphClockCmd(IREva_GPIO_CLK, ENABLE);
  //RCC_APB2PeriphClockCmd(IREva_GPIO_CLKC, ENABLE); 
	//选择按键的引脚
	GPIO_InitStructure.GPIO_Pin = IREva_GPIO_PIN1;
	// 设置按键的引脚为浮空输入
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	//使用结构体初始化按键
	GPIO_Init(IREva_GPIO_PORT, &GPIO_InitStructure);

		//选择按键的引脚
	GPIO_InitStructure.GPIO_Pin = IREva_GPIO_PIN2;
	// 设置按键的引脚为浮空输入
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	//使用结构体初始化按键
	GPIO_Init(IREva_GPIO_PORT, &GPIO_InitStructure);
	
		//选择按键的引脚
	GPIO_InitStructure.GPIO_Pin = IREva_GPIO_PIN3;
	// 设置按键的引脚为浮空输入
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	//使用结构体初始化按键
	GPIO_Init(IREva_GPIO_PORT, &GPIO_InitStructure);
	
			//选择按键的引脚
	GPIO_InitStructure.GPIO_Pin = IREva_GPIO_PIN4;
	// 设置按键的引脚为浮空输入
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	//使用结构体初始化按键
	GPIO_Init(IREva_GPIO_PORTC, &GPIO_InitStructure);

}

/*
* 函数名：IREva_Scan
* 描述  ：检测是否有按键按下
* 输入  ：GPIOx：x 可以是 A，B，C，D或者 E
*		     GPIO_Pin：待读取的端口位
* 输出  ：KEY_OFF(没按下按键)、KEY_ON（按下按键）
*/
uint8_t IREva_Scan(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	if (GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) == IREva_LO)  return 	IREva_LO;
	else
		return IREva_HI;
}


/*********************************************END OF FILE**********************/