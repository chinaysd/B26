#include "bsp_motro.h"

unsigned char UpFlag,DownFlag;
unsigned int   UpCnts,DownCnts;

void Motro_Init(void)
{
      P0CON  |= 0X06;
      P0PH    &= ~0X06;
      P0        &= 0X00;
}

void Motro_Handle(void)
{
	static unsigned char MotroTempCnts;
	++ MotroTempCnts;
	if(MotroTempCnts & 0x01)
	{
		 P0 &= 0Xf9;
	        P0 |= 1 << 1;
		 UpFlag = 1;
		 DownFlag = 0;
		 UpCnts = 0;
		 DownCnts = 0;
	}
	else
	{
		 P0 &= 0Xf9;
	        P0 |= 1 << 2;
		 UpFlag = 0;
		 DownFlag = 1;
		 UpCnts = 0;
		 DownCnts = 0;
	}
}

void Motro_Interrupt_Handle(void)
{
      if(UpFlag){
         UpCnts ++;
         if(UpCnts > 12000){
		  UpCnts = 0;
		  DownCnts = 0;
               P0 &= 0Xf9;
		  UpFlag = 0;
		  DownFlag = 0;
		 }
	  }
     if(DownFlag){
        DownCnts ++;
        if(DownCnts > 12000){
              UpCnts = 0;
		 DownCnts = 0;
              P0 &= 0Xf9;
	       UpFlag = 0;
		 DownFlag = 0;
		}
	 }
}
