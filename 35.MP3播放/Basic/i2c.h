#ifndef __I2C_H__
#define __I2C_H__
#include"stm32f10x.h"
#define I2C1PORT GPIOB
#define I2C1_SDA GPIO_Pin_7
#define I2C1_SCL GPIO_Pin_6
#define HOSTADDR 0XC0
#define BUSSPEED 20000

void I2C1_Configuration(void);
void I2C1_SendByte(u8 saddr,u8 waddr,u8 data);
void I2C1_SendBuf(u8 saddr,u8 waddr,u8* bufptr,u16 buflen);
u8 I2C1_ReceiveByte(u8 saddr,u8 raddr);
void I2C1_ReceiveBuf(u8 saddr,u8 raddr,u8* bufptr,u16 buflen);

#endif
