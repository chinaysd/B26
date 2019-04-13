#ifndef _BSP_MSG_H_
#define _BSP_MSG_H_

#include "stm8s.h"
#include "system.h"




typedef enum
{
	Msg_NonValue,
       Msg_PushAOpen,
       Msg_PushAClose,
       Msg_PushBOpen,
       Msg_PushBClose,
       Msg_PushRegister,
       Msg_PushResetClose,
       Msg_WarmOpen,
       Msg_WarmClose,
       Msg_Led1Open,
       Msg_Led1Close,
       Msg_MassOpen,
       Msg_MassClose
}
MSG_STATUS;





void Msg_Init(void);
void Msg_Function(unsigned char GetValue);
void Msg_Register(void (*Cb)(unsigned char));
void Msg_Poll(void);



#endif
