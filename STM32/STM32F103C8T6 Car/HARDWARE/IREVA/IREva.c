//IREva.c�������.C����

#include "IREva.h"  


void IREva_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/*���������˿ڵ�ʱ��*/
	RCC_APB2PeriphClockCmd(IREva_GPIO_CLK, ENABLE);
  //RCC_APB2PeriphClockCmd(IREva_GPIO_CLKC, ENABLE); 
	//ѡ�񰴼�������
	GPIO_InitStructure.GPIO_Pin = IREva_GPIO_PIN1;
	// ���ð���������Ϊ��������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	//ʹ�ýṹ���ʼ������
	GPIO_Init(IREva_GPIO_PORT, &GPIO_InitStructure);

		//ѡ�񰴼�������
	GPIO_InitStructure.GPIO_Pin = IREva_GPIO_PIN2;
	// ���ð���������Ϊ��������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	//ʹ�ýṹ���ʼ������
	GPIO_Init(IREva_GPIO_PORT, &GPIO_InitStructure);
	
		//ѡ�񰴼�������
	GPIO_InitStructure.GPIO_Pin = IREva_GPIO_PIN3;
	// ���ð���������Ϊ��������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	//ʹ�ýṹ���ʼ������
	GPIO_Init(IREva_GPIO_PORT, &GPIO_InitStructure);
	
			//ѡ�񰴼�������
	GPIO_InitStructure.GPIO_Pin = IREva_GPIO_PIN4;
	// ���ð���������Ϊ��������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	//ʹ�ýṹ���ʼ������
	GPIO_Init(IREva_GPIO_PORTC, &GPIO_InitStructure);

}

/*
* ��������IREva_Scan
* ����  ������Ƿ��а�������
* ����  ��GPIOx��x ������ A��B��C��D���� E
*		     GPIO_Pin������ȡ�Ķ˿�λ
* ���  ��KEY_OFF(û���°���)��KEY_ON�����°�����
*/
uint8_t IREva_Scan(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	if (GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) == IREva_LO)  return 	IREva_LO;
	else
		return IREva_HI;
}


/*********************************************END OF FILE**********************/