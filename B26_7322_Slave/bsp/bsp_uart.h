#ifndef _BSP_UART_H_
#define _BSP_UART_H_

#include "sc92f732x_c.h"



#define   REV_BUF_SIZE      7


#define Get32Bit(x,y)         (((x<<8)|y)&0xffff)









void Uart_Init(void);
void Send_Byte(unsigned char Byte);
unsigned char Rev_Byte(void);

unsigned char Rev_Select(void);


#endif


