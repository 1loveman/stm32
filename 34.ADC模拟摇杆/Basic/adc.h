#ifndef __ADC_H__
#define __ADC_H__
#include"stm32f10x.h"
#define ADC1_DR_ADDR ((uint32_t)0x4001244c)
#define ADC1PORT GPIOA
#define ADC1_IN6 GPIO_Pin_6
#define ADC1_IN7 GPIO_Pin_7

void ADC1_GPIO_Init(void);
void ADC1_DMA_Init(void);
void ADC1_Configuration(void);

#endif
