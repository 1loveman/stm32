#ifndef __I2C_H__
#define __I2C_H__
#include"stm32f10x.h"
#define I2C1PORT GPIOB
#define I2C1_SDA GPIO_Pin_7
#define I2C1_SCL GPIO_Pin_6
#define HOSTADDR 0XC0
#define BUSSPEED 200000

void I2C1_Configuration(void);
void I2C1_Send_Byte(u8 SlaveAddr,u8 WriteAddr,u8 Data);
void I2C1_Send_Buffer(u8 SlaveAddr,u8 WriteAddr,u8* BufferPtr,u16 BufferLen);
u8 I2C1_Read_Byte(u8 SlaveAddr,u8 ReadAddr);
void I2C1_Read_Buffer(u8 SlaveAddr,u8 ReadAddr,u8* BufferPtr,u16 BufferLen);

#endif
