#include"stm32f10x.h"
#include"sys.h"
#include"led.h"

int main(){
	RCC_Configuration();
	LED_Init();
	while(1){
		//����һ
//		GPIO_WriteBit(LEDPORT,LED1,(BitAction)(1));
		//����(BitAction)(1)Ϊö�ٿ�ֱ�Ӹ�ΪBit_SET����Bit_RESET

//		//������
//		GPIO_WriteBit(LEDPORT,LED1,(BitAction)(0));
//		GPIO_WriteBit(LEDPORT,LED2,(BitAction)(!GPIO_ReadOutputDataBit(LEDPORT,LED1)));
//		//�����Ƿ���һͨ����LED1ȡ��������Ϩ��LED2

//		//������
//		GPIO_SetBits(LEDPORT,LED1);
//		GPIO_ResetBits(LEDPORT,LED2);
//		//���ض�������λ���߸�λ
//
//		//������
		GPIO_Write(LEDPORT,0x03);
//		//ֱ����˿�д��
//		//����ÿһλ������λ�ֱ�����Ӧ������״̬
//		//����0x0001��ʾ��pin_0��1  0x0002��ʾ��pin_1��1  0x0003��ʾ��pin_0��pin_1ͬʱ��1
	}
}
