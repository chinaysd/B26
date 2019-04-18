#include "bsp_uart.h"

unsigned char UartSendFlag,UartReceiveFlag;
unsigned char Rev_Data,Rev_Num,Rev_String[REV_BUF_SIZE];


void Uart_Init(void)
{
	P1CON &= 0XF3;
	P1PH |= 0X0C;	 //TX/RX为带上拉输入；
	P13 = 1;		 //TX初始高电平；
	SCON = 0X50;     //方式1，允许接收数据
	PCON |= 0X80; 
	T2CON = 0x00;    //使用定时器1作UART时钟
	TMOD = 0X20;     //定时器1  8位自动重载
	TMCON = 0X02;    //定时器1   Fsys；
	//TL1 = 217;		
	TH1 = 243;		 //UART 波特率24M情况下=38400；
	TR1 = 0;
	ET1 = 0;		 //Timer1使能
	TR1 = 1;		 //启动Timer0
	EUART = 1;	     //允许UART中断
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
*函数名称：void UartInt(void) interrupt 4
*函数功能：Uart0中断服务函数
*入口参数：void
*出口参数：void
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



