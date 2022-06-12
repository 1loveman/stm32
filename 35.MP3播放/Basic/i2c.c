#include"i2c.h"

void I2C1_Configuration(void){
    GPIO_InitTypeDef GPIO_InitS;
    I2C_InitTypeDef I2C_InitS;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1,ENABLE);
    
    GPIO_InitS.GPIO_Pin=I2C1_SDA|I2C1_SCL;
    GPIO_InitS.GPIO_Mode=GPIO_Mode_AF_OD;
    GPIO_InitS.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&GPIO_InitS);

    I2C_InitS.I2C_Mode=I2C_Mode_I2C;
    I2C_InitS.I2C_DutyCycle=I2C_DutyCycle_2;
    I2C_InitS.I2C_OwnAddress1=HOSTADDR;
    I2C_InitS.I2C_Ack=I2C_Ack_Enable;
    I2C_InitS.I2C_AcknowledgedAddress=I2C_AcknowledgedAddress_7bit;
    I2C_InitS.I2C_ClockSpeed=BUSSPEED;
    I2C_Init(I2C1,&I2C_InitS);
    I2C_Cmd(I2C1,ENABLE);
}

void I2C1_SendByte(u8 saddr,u8 waddr,u8 data){
    I2C_GenerateSTART(I2C1,ENABLE);
    while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_MODE_SELECT));//事件主模式选择
    I2C_Send7bitAddress(I2C1,saddr,I2C_Direction_Transmitter);
    while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));//事件主发送模式选择
    I2C_SendData(I2C1,waddr);
    while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTED));
    I2C_SendData(I2C1,data);
    while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTED));
    I2C_GenerateSTOP(I2C1,ENABLE);
}

void I2C1_SendBuf(u8 saddr,u8 waddr,u8* bufptr,u16 buflen){
    I2C_GenerateSTART(I2C1,ENABLE);
    while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_MODE_SELECT));
    I2C_Send7bitAddress(I2C1,saddr,I2C_Direction_Transmitter);
    while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
    I2C_SendData(I2C1,waddr);
    while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTED));
    while(buflen--){
        I2C_SendData(I2C1,*(bufptr++));
        while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTED));
    }
    I2C_GenerateSTOP(I2C1,ENABLE);
}


u8 I2C1_ReceiveByte(u8 saddr,u8 raddr){
    while(I2C_GetFlagStatus(I2C1,I2C_FLAG_BUSY));
    I2C_GenerateSTART(I2C1,ENABLE);
    while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_MODE_SELECT));
    I2C_Send7bitAddress(I2C1,saddr,I2C_Direction_Transmitter);
    while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
    I2C_GenerateSTART(I2C1,ENABLE);
    while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_MODE_SELECT));
    I2C_SendData(I2C1,raddr);
    while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTED));
    I2C_GenerateSTART(I2C1,ENABLE);
    while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_MODE_SELECT));
    I2C_Send7bitAddress(I2C1,saddr,I2C_Direction_Receiver);
    while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
    I2C_AcknowledgeConfig(I2C1,DISABLE);
    I2C_GenerateSTOP(I2C1,ENABLE);
    return (I2C_ReceiveData(I2C1));
}

void I2C1_ReceiveBuf(u8 saddr,u8 raddr,u8* bufptr,u16 buflen){
    while(I2C_GetFlagStatus(I2C1,I2C_FLAG_BUSY));
    I2C_GenerateSTART(I2C1,ENABLE);
    while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_MODE_SELECT));
    I2C_Send7bitAddress(I2C1,saddr,I2C_Direction_Transmitter);
    while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
    I2C_GenerateSTART(I2C1,ENABLE);
    while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_MODE_SELECT));
    I2C_SendData(I2C1,raddr);
    I2C_GenerateSTART(I2C1,ENABLE);
    while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_MODE_SELECT));
    I2C_Send7bitAddress(I2C1,saddr,I2C_Direction_Receiver);
    while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
    while(buflen--){
        if(!buflen){
            I2C_AcknowledgeConfig(I2C1,DISABLE);
            I2C_GenerateSTOP(I2C1,ENABLE);
        }
        if(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_RECEIVED)){
            *(bufptr++)=I2C_ReceiveData(I2C1);
        }
    }
    I2C_AcknowledgeConfig(I2C1,ENABLE);
}
