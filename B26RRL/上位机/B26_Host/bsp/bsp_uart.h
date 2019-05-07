#ifndef _BSP_UART_H_
#define _BSP_UART_H_


#include "sc93f833x_c.h"

#define SENDBUFSIZE    7
#define Hight(x)            (((x)>>8)&0xff)
#define Low(x)              ((x)&0xff)

typedef struct
{
	unsigned char ADDR;
	unsigned char ID;
	unsigned char DATA1;
	unsigned char DATA2;
	unsigned char CHECKSUM;
	unsigned char STOP1;
	unsigned char STOP2;
}
DATA_FORMAT_TX;

typedef union
{
	unsigned char Buf[SENDBUFSIZE];
	DATA_FORMAT_TX Data_Format;
}
PROTOCOL_TX;










void Uart_Init(unsigned char Freq,unsigned int BaudRate);
void Send_Byte(unsigned char Byte);
unsigned char Protocol_Send(unsigned char addr,unsigned char id,unsigned int TX_DATA);




#endif


