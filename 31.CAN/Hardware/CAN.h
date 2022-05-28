#ifndef __CAN_H__
#define __CAN_H__
#include"stm32f10x.h"
#define CAN_INT_ENABLE 0
#define TSJW CAN_SJW_1tq
#define TBS1 CAN_BS1_8tq
#define TBS2 CAN_BS2_7tq
#define BRP 9

u8 CAN_Configuration(void);
u8 CAN_Send_Msg(u8* msg,u8 len);
u8 CAN_Receive_Msg(u8* buf);

#endif
