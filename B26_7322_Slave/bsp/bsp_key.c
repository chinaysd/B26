#include "bsp_key.h"

//KEY_FORMAT_K Key_Format;

void Key_Init(void)
{
	P2CON &= ~0XC0;
	P2PH   |= 0XC0;
}

unsigned char Key_Handle(unsigned char ID)
{
	if(ID == KEY1_ID)
	{
		if(KEY1_PIN == KEY_DOWN)
		{
                    return 1;
		}
		else
		{
                   return 0;
		}
	}
	else if(ID == KEY2_ID)
	{
		if(KEY2_PIN == KEY_DOWN)
		{
                   return 1;
		}
		else
		{
		     return 0;
		}
	}
	else
	{
		return 0;
	}
}



