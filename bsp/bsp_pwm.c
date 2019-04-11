#include "bsp_pwm.h"

unsigned char Pwm_Level;
unsigned int PwmAutoCount100us;

void Pwm_Init(void)
{
	P0CON |= 0X01;
	P0PH   &= ~0X01;
}

void Pwm15_Level(void)
{
	Pwm_Level = 15;
}

void Pwm100_Level(void)
{
	Pwm_Level = 100;
}

void Pwm_Handle(void)
{
	PwmAutoCount100us ++;
	if(PwmAutoCount100us > 100)
	{
		PwmAutoCount100us = 0;
	}
	if(PwmAutoCount100us > Pwm_Level)
	{
		PWM_SET(0);
	}
	else
	{
		PWM_SET(1);
	}
}


