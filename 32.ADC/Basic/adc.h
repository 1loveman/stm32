#ifndef __ADC_H__
#define __ADC_H__
#include"stm32f10x.h"
#define ADC_DR_ADDR ((uint32_t)0x4001244C)
#define ADC_IN5 GPIO_Pin_5

void ADC_GPIO_Init(void);
void ADC_DMA_Init(void);
void ADC_Configuration(void);

#endif
