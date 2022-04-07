#include"buzzer.h"
#include"delay.h"

uc16 musicl[78]={ //����1�����ݱ�������������ż���ǳ��ȣ�
330,750,
440,375,
494,375,
523,750,
587,375,
659,375,
587,750,
494,375,
392,375,
440,1500,
330,750,
440,375,
494,375,
523,750,
587,375,
659,375,
587,750,
494,375,
392,375,
784,1500,
659,750,
698,375,
784,375,
880,750,
784,375,
698,375,
659,750,
587,750,
659,750,
523,375,
494,375,
440,750,
440,375,
494,375,
523,750,
523,750,
494,750,
392,750,
440,3000
};

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
void BUZZER_Work_s(){
	u16 i,e;//�˴�����λӦ�òο�musicl��ֵ
	for(i=0;i<39;i++){//���ĸ���
		for(e=0;e<musicl[2*i]*musicl[2*i+1]/1000;e++){	 //��ʱ��ת��Ϊ������ʱ
			GPIO_ResetBits(BUZZERPORT,BUZZER);
			delay_us(500000/musicl[2*i]);
			GPIO_SetBits(BUZZERPORT,BUZZER);
			delay_us(500000/musicl[2*i]);
		}
	}

}

