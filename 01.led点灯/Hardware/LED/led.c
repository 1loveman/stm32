#include"led.h"

void LED_Init(void){
	GPIO_InitTypeDef GPIO_InitStructure;					   //ʵ�����ṹ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);	   //����ʱ������
	GPIO_InitStructure.GPIO_Pin=LED1|LED2;					   //���ùܽ�
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;			   //���ù���ģʽ
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;			   //���ö˿��ٶȣ�ֻ����Ϊ�����ʱ������� �ֱ��� 2��10��50
	GPIO_Init(LEDPORT,&GPIO_InitStructure);					   //���ݽṹ�������ʼ���˿ڣ�
}
////IO�ڹ���ģʽ
//GPIO_Mode_AIN				   // ģ������
//GPIO_Mode_IN_FLOATING		   // ��������
//GPIO_Mode_IPU				   // ��������
//GPIO_Mode_IPD				   // ��������
//GPIO_Mode_Out_PP			   // �������
//GPIO_Mode_OUT_OD			   // ��©���
//GPIO_Mode_AF_PP				   // �����������
//GPIO_Mode_AF_OD				   // ���ÿ�©���
