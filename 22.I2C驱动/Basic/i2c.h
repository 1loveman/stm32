#ifndef __I2C_H__
#define __I2C_H__
#include"stm32f10x.h"
#define I2C1PORT GPIOB
#define I2C1_SDA GPIO_Pin_7
#define I2C1_SCL GPIO_Pin_6
#define HostAddress 0XC0
#define BusSpeed 200000

void I2C_Configuration(void);
void I2C_Send_Byte(u8 SlaveAddr,u8 WriteAddr,u8 data);
void I2C_Send_Buffer(u8 SlaveAddr,u8 WriteAddr,u8* BuffPtr,u16 BuffLen);
u8 I2C_Read_Byte(u8 SlaveAddr,u8 ReadAddr);
void I2C_Read_Buffer(u8 SlaveAddr,u8 ReadAddr,u8* BuffPtr,u16 BuffLen);
#endif
