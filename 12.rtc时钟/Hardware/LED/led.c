#include"led.h"

void LED_Init(void){
	GPIO_InitTypeDef GPIO_InitStructure;					   //实例化结构体
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);	   //设置时钟总线
	GPIO_InitStructure.GPIO_Pin=LED1|LED2;					   //设置管脚
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;			   //设置工作模式
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;			   //设置端口速度，只有作为输出的时候才设置 分别有 2、10、50
	GPIO_Init(LEDPORT,&GPIO_InitStructure);					   //根据结构体参数初始化端口；
}
////IO口工作模式
//GPIO_Mode_AIN				   // 模拟输入
//GPIO_Mode_IN_FLOATING		   // 浮空输入
//GPIO_Mode_IPU				   // 上拉输入
//GPIO_Mode_IPD				   // 下拉输入
//GPIO_Mode_Out_PP			   // 推挽输出
//GPIO_Mode_OUT_OD			   // 开漏输出
//GPIO_Mode_AF_PP				   // 复用推挽输出
//GPIO_Mode_AF_OD				   // 复用开漏输出
