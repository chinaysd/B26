#include "bsp_uart.h"

unsigned char UartSendFlag,UartReceiveFlag;
unsigned char Rev_Data,Rev_Num,Rev_String[REV_BUF_SIZE];


void Uart_Init(void)
{
	P1CON &= 0XF3;
	P1PH |= 0X0C;	 //TX/RXΪ���������룻
	P13 = 1;		 //TX��ʼ�ߵ�ƽ��
	SCON = 0X50;     //��ʽ1�������������
	PCON |= 0X80; 
	T2CON = 0x00;    //ʹ�ö�ʱ��1��UARTʱ��
	TMOD = 0X20;     //��ʱ��1  8λ�Զ�����
	TMCON = 0X02;    //��ʱ��1   Fsys��
	//TL1 = 217;		
	TH1 = 243;		 //UART ������24M�����=38400��
	TR1 = 0;
	ET1 = 0;		 //Timer1ʹ��
	TR1 = 1;		 //����Timer0
	EUART = 1;	     //����UART�ж�
}

void Send_Byte(unsigned char Byte)
{
	SBUF = Byte;
	while(!UartSendFlag);
	UartSendFlag = 0;
}

unsigned char Rev_Select(void)
{
	if(Rev_Num & 0x80)
	{
		Rev_Num = 0x00;
		return 1;
	}
	else
	{
		return 0;
	}
}

unsigned char Rev_Byte(void)
{
	static unsigned char Byte;
	Byte = SBUF;
	//while(!UartReceiveFlag);
	//UartReceiveFlag = 0;
	return Byte;
}

static void Rev_Handle(void)
{
	Rev_Data = Rev_Byte();
	if((Rev_Num & 0x08) == 0)
	{
		if(Rev_Num & 0x40)
		{
			if(Rev_Data == 0x0a)
			{
				Rev_Num = 0x80;
			}
			else
			{
				Rev_Num = 0x00;
			}
		}
		else
		{
			if(Rev_Data == 0x0d)
			{
				Rev_Num = 0x40;
			}
			else
			{
				Rev_String[Rev_Num] = Rev_Data;
				Rev_Num ++;
				#if 0
				if(Rev_String[4] != (unsigned char)(Rev_String[0]+Rev_String[1]+Rev_String[2]+Rev_String[3]))
				{
					Rev_Num = 0x00;
				}
				#endif
				if(Rev_String[0] != 0xfa)
				{
					Rev_Num = 0x00;
				}
				if(Rev_Num > REV_BUF_SIZE)
				{
					Rev_Num = 0x00;
				}
			}
		}
	}
}

/*****************************************************
*�������ƣ�void UartInt(void) interrupt 4
*�������ܣ�Uart0�жϷ�����
*��ڲ�����void
*���ڲ�����void
*****************************************************/
void UartInt(void) interrupt 4
{
	if(TI)
	{
		TI = 0;	
		UartSendFlag = 1;		
	}
	if(RI)
	{
		RI = 0;	
		UartReceiveFlag = 1;
		Rev_Handle();
	}	
}



