#include "bsp_table.h"


void TableKeyInit(void)
{
        P0CON &= ~0X01;
	  P0PH    |= 0X01;
}

void TableDelayRuningOpen(void)
{
	
}

unsigned char TableReturnValue(void)
{
	if(TABLE_DOWN == TableKeyPin)
	{
	      return TABLE_ENABLE;	
	}
	else
	{
		return TABLE_DISABLE;
	}
}

