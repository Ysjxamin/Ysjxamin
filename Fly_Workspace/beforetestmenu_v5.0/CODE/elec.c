#include "elec.h"

#define ADC_CH1			ADC0_CH0_A0
#define ADC_CH2			ADC0_CH1_A1
#define ADC_CH3			ADC0_CH2_A2
#define ADC_CH4			ADC0_CH3_A3
#define ADC_CH5			ADC0_CH4_A4
#define ADC_CH6			ADC0_CH5_A5
#define ADC_CH7			ADC0_CH6_A6
#define ADC_CH8			ADC0_CH7_A7

uint16 elec_data[8];

void elec_init(void)
{
    adc_init(ADC_0, ADC_CH1);    // 初始化 ADC 已经对应通道引脚 10位精度
	adc_init(ADC_0, ADC_CH2);    // 初始化 ADC 已经对应通道引脚 10位精度
	adc_init(ADC_0, ADC_CH3);    // 初始化 ADC 已经对应通道引脚 10位精度
	adc_init(ADC_0, ADC_CH4);    // 初始化 ADC 已经对应通道引脚 10位精度
	adc_init(ADC_0, ADC_CH5);    // 初始化 ADC 已经对应通道引脚 10位精度
	adc_init(ADC_0, ADC_CH6);    // 初始化 ADC 已经对应通道引脚 10位精度
	adc_init(ADC_0, ADC_CH7);    // 初始化 ADC 已经对应通道引脚 10位精度
	adc_init(ADC_0, ADC_CH8);    // 初始化 ADC 已经对应通道引脚 10位精度
}
void elec_get(void)
{
    elec_data[0] = adc_convert(ADC_0, ADC_CH1, ADC_8BIT);
    elec_data[1] = adc_convert(ADC_0, ADC_CH2, ADC_8BIT);
    elec_data[2] = adc_convert(ADC_0, ADC_CH3, ADC_8BIT);
    elec_data[3] = adc_convert(ADC_0, ADC_CH4, ADC_8BIT);
    elec_data[4] = adc_convert(ADC_0, ADC_CH5, ADC_8BIT);
    elec_data[5] = adc_convert(ADC_0, ADC_CH6, ADC_8BIT);
    elec_data[6] = adc_convert(ADC_0, ADC_CH7, ADC_8BIT);
    elec_data[7] = adc_convert(ADC_0, ADC_CH8, ADC_8BIT);
    
}

void elec_calculate(void)
{
    
}
