#include "system.h"

extern unsigned char SendBackData;
TIMEOUT_PARA TimeOut_Para[2];

void System_Init(void)
{
	TimeOutDet_Init();
	Pwm_Init();
	Pwm15_Level();
	Motro_Init();
       Led_Init();
	Lock_Init();
       Timer_Init();
	Key_Init();
	Key_Register(Key_Function);
	Wdt_Init();
	Uart_Init(2,9600);
}

void System_Handle(void)
{
	Wdt_Feed();
	Key_Poll();
	if(TimeOutDet_Check(&TimeOut_Para[0]))
	{
		TimeOut_Record(&TimeOut_Para[0],700);//45ms
		Protocol_Send(0xfa,0xfb,SendBackData);
	}
}




