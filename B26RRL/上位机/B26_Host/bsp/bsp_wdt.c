#include "bsp_wdt.h"


void Wdt_Init(void)
{
	WDTCON |= 0X10;
}

void Wdt_Feed(void)
{
	WDTCON |= 0X10;
}



