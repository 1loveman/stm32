#ifndef __BUZZER_H__
#define __BUZZER_H__
#include"sys.h"
#define BUZZERPORT GPIOB
#define BUZZER GPIO_Pin_5

void BUZZER_Init(void);	//初始化的声明
void BUZZER_Work(void);	//工作的声明
void BUZZER_Work2(void);
void BUZZER_Work3(void);
void BUZZER_Work4(void);
#endif
