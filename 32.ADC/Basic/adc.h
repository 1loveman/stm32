#ifndef __ADC_H__
#define __ADC_H__
#include"stm32f10x.h"
#define ADC1_DR_ADDR (0X4001244C)
#define ADC_IN4 GPIO_Pin_4
#define ADC_IN5 GPIO_Pin_5

void ADC_GPIO_Init(void);
void ADC_Configuration(void);
void ADC_DMA_Init(void);

#endif
