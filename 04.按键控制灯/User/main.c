#include"stm32f10x.h"
#include"sys.h"
#include"delay.h"
#include"led.h"
#include"key.h"

int main(){
	u8 a=0;
	RCC_Configuration();
	LED_Init();
	KEY_Init();
	while(1){
		//������
		//����һ
		GPIO_WriteBit(LEDPORT,LED1,(BitAction)(!GPIO_ReadInputDataBit(KEYPORT,KEY1)));

		//������
//		if(!GPIO_ReadInputDataBit(KEYPORT,KEY1)){
//			GPIO_SetBits(LEDPORT,LED1);
//		}
//		else{
//			GPIO_ResetBits(LEDPORT,LED1);
//		}

		//������
		//������
//		if(!GPIO_ReadInputDataBit(KEYPORT,KEY1)){//��ȡkey״̬
//			delay_ms(20);//��ʱ20ms��
//			if(!GPIO_ReadInputDataBit(KEYPORT,KEY1)){  //��ȡ��ʱ���״̬
//				GPIO_WriteBit(LEDPORT,LED1,(BitAction)(!GPIO_ReadOutputDataBit(LEDPORT,LED1)));//��ledԭ״̬ȡ��
//				while(!GPIO_ReadInputDataBit(KEYPORT,KEY1));//�ȴ������ɿ�����ֹ����ִ�й���
//			}
//		}

		//������ ---���������ƹ���
//		if(!GPIO_ReadInputDataBit(KEYPORT,KEY1)){
//			delay_ms(20);
//			if(!GPIO_ReadInputDataBit(KEYPORT,KEY1)){
//			a++;
//			if(a>3){
//				a=0;
//			}
//			GPIO_Write(GPIOB,a);
//			while(!GPIO_ReadInputDataBit(KEYPORT,KEY1));
//			}
//		}
	}
}
