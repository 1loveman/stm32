#include"stm32f10x.h"
#include"sys.h"
#include"led.h"

int main(){
	RCC_Configuration();
	LED_Init();
	while(1){
		//方法一
//		GPIO_WriteBit(LEDPORT,LED1,(BitAction)(1));
		//其中(BitAction)(1)为枚举可直接改为Bit_SET或者Bit_RESET

//		//方法二
//		GPIO_WriteBit(LEDPORT,LED1,(BitAction)(0));
//		GPIO_WriteBit(LEDPORT,LED2,(BitAction)(!GPIO_ReadOutputDataBit(LEDPORT,LED1)));
//		//本质是方法一通过对LED1取反点亮或熄灭LED2

//		//方法三
//		GPIO_SetBits(LEDPORT,LED1);
//		GPIO_ResetBits(LEDPORT,LED2);
//		//将特定引脚置位或者复位
//
//		//方法四
		GPIO_Write(LEDPORT,0x03);
//		//直接向端口写入
//		//其中每一位二进制位分别代表对应的引脚状态
//		//比如0x0001表示将pin_0置1  0x0002表示将pin_1置1  0x0003表示将pin_0和pin_1同时置1
	}
}
