#include "bsp_lock.h"
#include "bsp_pwm.h"
#include "bsp_key.h"


unsigned char Lock_Flag;
extern unsigned char Pwm_Level;
extern unsigned char SendBackData;

void Lock_Init(void)
{
     	P2CON |= 0X20;
	P2PH   &= ~0X20;
}

void Lock_Handle(void)
{
	if(!Lock_Flag)
	{
		Lock_Flag = Lock_True;
		//RED_SET(1);
		//Pwm_Level = 0;
	}
	else
	{
		Lock_Flag = Lock_False;
		//RED_SET(0);
	}
}







