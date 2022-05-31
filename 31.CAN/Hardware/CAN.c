#include"CAN.h"

u8 CAN_Configuration(void){
    GPIO_InitTypeDef GPIO_InitS;
    CAN_InitTypeDef CAN_InitS;
    CAN_FilterInitTypeDef CAN_FilterInitS;
    #if CAN_INT_ENABLE
    NVIC_InitTypeDef NVIC_InitS;
    #endif
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1,ENABLE);

    GPIO_InitS.GPIO_Pin=GPIO_Pin_12;
    GPIO_InitS.GPIO_Mode=GPIO_Mode_AF_PP;
    GPIO_InitS.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitS);
    GPIO_InitS.GPIO_Pin=GPIO_Pin_11;
    GPIO_InitS.GPIO_Mode=GPIO_Mode_IPU;
    GPIO_Init(GPIOA,&GPIO_InitS);

    CAN_InitS.CAN_TTCM=DISABLE;
    CAN_InitS.CAN_ABOM=DISABLE;
    CAN_InitS.CAN_AWUM=DISABLE;
    CAN_InitS.CAN_NART=ENABLE;
    CAN_InitS.CAN_RFLM=DISABLE;
    CAN_InitS.CAN_TXFP=DISABLE;
    CAN_InitS.CAN_Mode=CAN_Mode_Normal;
    CAN_InitS.CAN_SJW=TSJW;
    CAN_InitS.CAN_BS1=TBS1;
    CAN_InitS.CAN_BS2=TBS2;
    CAN_InitS.CAN_Prescaler=BRP;
    CAN_Init(CAN1,&CAN_InitS);
    
    CAN_FilterInitS.CAN_FilterNumber=0;
    CAN_FilterInitS.CAN_FilterMode=CAN_FilterMode_IdMask;
    CAN_FilterInitS.CAN_FilterScale=CAN_FilterScale_32bit;
    CAN_FilterInitS.CAN_FilterIdHigh=0x0000;
    CAN_FilterInitS.CAN_FilterIdLow=0x0000;
    CAN_FilterInitS.CAN_FilterMaskIdHigh=0X0000;
    CAN_FilterInitS.CAN_FilterMaskIdLow=0x0000;
    CAN_FilterInitS.CAN_FilterFIFOAssignment=CAN_Filter_FIFO0;
    CAN_FilterInitS.CAN_FilterActivation=ENABLE;
    CAN_FilterInit(&CAN_FilterInitS);

    #if CAN_INT_ENABLE
    CAN_ITConfig(CAN1,CAN_IT_FMP0,ENABLE);
    NVIC_InitS.NVIC_IRQChannel=USB_LP_CAN1_RX0_IRQn;
    NVIC_InitS.NVIC_IRQChannelPreemptionPriority=1;
    NVIC_InitS.NVIC_IRQChannelSubPriority=0;
    NVIC_InitS.NVIC_IRQChannelCmd=ENABLE;
    NVIC_Init(&NVIC_InitS);
    #endif
    return 0;
}

u8 CAN_Send_Msg(u8* msg,u8 len){
    u8 mbox;
    u8 i=0;
    CanTxMsg TxMsg;
    TxMsg.StdId=0x000;
    TxMsg.ExtId=0x00000000;
    TxMsg.IDE=CAN_Id_Standard;
    TxMsg.RTR=CAN_RTR_Data;
    TxMsg.DLC=len;
    while(i<len){
        TxMsg.Data[i++]=*(msg++);
    }
    i=0;
    mbox=CAN_Transmit(CAN1,&TxMsg);
    while((CAN_TransmitStatus(CAN1,mbox)==CAN_TxStatus_Failed)&&(i<0xfff))i++;
    if(i>=0xfff)return 1;
    return 0;
}

u8 CAN_Receive_Msg(u8* buf){
    u8 i=0;
    CanRxMsg RxMsg;
    if(CAN_MessagePending(CAN1,CAN_FIFO0)==0)return 0;
    CAN_Receive(CAN1,CAN_FIFO0,&RxMsg);
    while(i<8){
        *(buf++)=RxMsg.Data[i++];
    }
    return RxMsg.DLC;
}

void USB_LP_CAN1_RX0_IRQHandler(void){
    vu8 i=0;
    vu8 Tlen=0;
    vu8 Tbuff[8];
    CanRxMsg RxMsg;
    RxMsg.StdId=0x00;
    RxMsg.ExtId=0X00;
    RxMsg.IDE=0;
    RxMsg.RTR=0;
    RxMsg.DLC=0;
    RxMsg.FMI=0;
    while(i<8){
        RxMsg.Data[i++]=0;
    }
    CAN_Receive(CAN1,CAN_FIFO0,&RxMsg);
    Tlen=RxMsg.DLC;
    i=0;
    if(RxMsg.StdId==0X00){
        while(i<Tlen){
            Tbuff[i]=RxMsg.Data[i];
            i++;
        }
    }
}
