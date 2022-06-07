#ifndef __ADC_H__
#define __ADC_H__
#include"stm32f10x.h"
#define ADC1_DR_ADDR ((uint32_t)0X4001244C)
#define ADC1PORT GPIOA
#define ADC1_CH4 GPIO_Pin_4
#define ADC1_CH5 GPIO_Pin_5

void ADC1_GPIO_Init(void);
void ADC1_DMA_Init(void);
void ADC1_Configuration(void);

#endif
