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
		//无锁存
		//方法一
		GPIO_WriteBit(LEDPORT,LED1,(BitAction)(!GPIO_ReadInputDataBit(KEYPORT,KEY1)));

		//方法二
//		if(!GPIO_ReadInputDataBit(KEYPORT,KEY1)){
//			GPIO_SetBits(LEDPORT,LED1);
//		}
//		else{
//			GPIO_ResetBits(LEDPORT,LED1);
//		}

		//有锁存
		//方法三
//		if(!GPIO_ReadInputDataBit(KEYPORT,KEY1)){//读取key状态
//			delay_ms(20);//延时20ms再
//			if(!GPIO_ReadInputDataBit(KEYPORT,KEY1)){  //读取延时后的状态
//				GPIO_WriteBit(LEDPORT,LED1,(BitAction)(!GPIO_ReadOutputDataBit(LEDPORT,LED1)));//对led原状态取反
//				while(!GPIO_ReadInputDataBit(KEYPORT,KEY1));//等待按键松开。防止程序执行过快
//			}
//		}

		//方法四 ---二进制闪灯功能
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
