#include"stm32f10x.h"
#include"sys.h"
#include"rtc.h"
#include"usart.h"

int main(void){
	u8 i;
	const u8 mon_tab[]={31,28,31,30,31,30,31,31,30,31,30,31};
	RCC_Configuration();
	RTC_Config();
	USART1_Init(115200);
	USART1_RX_STA=0XC000;
	while(1){
		if(USART1_RX_STA&0XC000){
			if(!(USART1_RX_STA&0X3FFF)){
				if(!RTC_Get()){
					printf(" 洋桃开发板STM32实时时钟测试程序   \r\n");
					printf(" 现在实时时间：%d-%d-%d %d:%d:%d  ",ryear,rmon,rday,rhour,rmin,rsec);//显示日期时间
					if(rweek==0)printf("星期日   \r\n");//rweek值为0时表示星期日
					if(rweek==1)printf("星期一   \r\n");
					if(rweek==2)printf("星期二   \r\n");
					if(rweek==3)printf("星期三   \r\n");
					if(rweek==4)printf("星期四   \r\n");
					if(rweek==5)printf("星期五   \r\n");
					if(rweek==6)printf("星期六   \r\n");
					printf(" 单按回车键更新时间。输入字母C初始化时钟 \r\n");
					printf(" 请输入设置时间,格式20170806120000,按回车键确定！ \r\n");
				}
				else{
					printf("获取失败！\r\n");
				}
			}
			else if((USART1_RX_STA&0X3FFF)==1){
				if((USART1_RX_BUFF[0]=='c')||(USART1_RX_BUFF[0]=='C')){
					RTC_First_Config();
					BKP_WriteBackupRegister(BKP_DR1,0XA5A5);
					printf("初始化成功！\r\n");
				}
				else{
					printf("初始化失败！\r\n");
				}
				
			}
			else if((USART1_RX_STA&0X3FFF)==14){
				i=0;
				while((i<14)&&(0x30<=USART1_RX_BUFF[i])&&(USART1_RX_BUFF[i]<=0x39))i++;
				if(i==14){
					ryear=(USART1_RX_BUFF[0]-0x30)*1000+(USART1_RX_BUFF[1]-0x30)*100+(USART1_RX_BUFF[2]-0x30)*10+(USART1_RX_BUFF[3]-0x30);
					rmon=(USART1_RX_BUFF[4]-0x30)*10+(USART1_RX_BUFF[5]-0x30);
					rday=(USART1_RX_BUFF[6]-0x30)*10+(USART1_RX_BUFF[7]-0x30);
					rhour=(USART1_RX_BUFF[8]-0x30)*10+(USART1_RX_BUFF[9]-0x30);
					rmin=(USART1_RX_BUFF[10]-0x30)*10+(USART1_RX_BUFF[11]-0x30);
					rsec=(USART1_RX_BUFF[12]-0x30)*10+(USART1_RX_BUFF[13]-0x30);
					if((1970<=ryear)&&(ryear<=2099)&&(1<=rmon)&&(rmon<=12)&&(1<=rday)&&(rday<=31)&&(rhour<=23)&&(rmin<=59)&&(rsec<=59)){
						if(Is_Leap_Year(ryear)){
							if(rmon==2){
								if(rday<=(mon_tab[rmon-1]+1)){
									if(!RTC_Set(ryear,rmon,rday,rhour,rmin,rsec)) printf("设置成功！          \r\n");
									else printf("设置失败！          \r\n");
								}
								else printf("输入数据有误！          \r\n");
							}
							else{
								if(rday<=mon_tab[rmon-1]){
									if(!RTC_Set(ryear,rmon,rday,rhour,rmin,rsec)) printf("设置成功！          \r\n");
									else printf("设置失败！          \r\n");
								}
								else printf("输入数据有误！          \r\n");
							}
						}
						else{
							if(rday<=mon_tab[rmon-1]){
								if(!RTC_Set(ryear,rmon,rday,rhour,rmin,rsec)) printf("设置成功！          \r\n");
								else printf("设置失败！          \r\n");
							}
							else printf("输入数据有误！          \r\n");
						}
					}
					else printf("输入数据有误！          \r\n");
				}
				else printf("输入数据有误！          \r\n");
			}
			else printf("指令输入有误！          \r\n");
			USART1_RX_STA=0;
		}
	}
}

