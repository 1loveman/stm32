#include"buzzer.h"
#include"delay.h"

void BUZZER_Init(void){		 //��ʼ��
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitStructure.GPIO_Pin=BUZZER;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(BUZZERPORT,&GPIO_InitStructure);

	GPIO_SetBits(BUZZERPORT,BUZZER);//��PB5���óɸߵ�ƽ��ֹbuzzer�ջ�
}

void BUZZER_Work(void){
	u8 i;
	for(i=0;i<100;i++){	//ѭ���ɸı������ʱ��
		GPIO_WriteBit(BUZZERPORT,BUZZER,(BitAction)(0));
		delay_us(500);//500usͨ������ó�
		GPIO_WriteBit(BUZZERPORT,BUZZER,(BitAction)(1));//�����Ըߵ�ƽ����
		delay_us(500);
	}
}
void BUZZER_Work2(void){
	u8 i;
	for(i=0;i<100;i++){
		GPIO_WriteBit(BUZZERPORT,BUZZER,(BitAction)(0));
		delay_us(250);
		GPIO_WriteBit(BUZZERPORT,BUZZER,(BitAction)(1));
		delay_us(250);
	}
}
void BUZZER_Work3(void){
	u8 i;
	for(i=0;i<100;i++){
		GPIO_WriteBit(BUZZERPORT,BUZZER,(BitAction)(0));
		delay_us(125);
		GPIO_WriteBit(BUZZERPORT,BUZZER,(BitAction)(1));
		delay_us(125);
	}
}
void BUZZER_Work4(void){
	u8 i;
	for(i=0;i<200;i++){
		GPIO_WriteBit(BUZZERPORT,BUZZER,(BitAction)(0));
		delay_us(500);
		GPIO_WriteBit(BUZZERPORT,BUZZER,(BitAction)(1));
		delay_us(500);
	}
}

