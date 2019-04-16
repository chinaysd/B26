#include "bsp_led.h"



void Led_Init(void)
{
      P1CON |= 0X80;
      P1PH   &= ~0X80;
      LED_SET(0);
}

