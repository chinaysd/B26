#include "bsp_push.h"

static unsigned char OnlyOneInputFlag,OnlyTwoInputFlag;
TIMEOUT_PARA TimeOut_Para[3];


void Push_Init(void)
{
	P0CON |= 0X3C;
	P0PH    &= ~0X3C;
	P2CON |= 0X33;
	P2PH   &= ~0X33;
}


void Push_Handle(PUSH_ADDR addr,PUSH_STATUS Push_Status)
{
      if(addr == PUSHA_ADDR)
      {
		if(Push_Status == PUSH_STOP)
		{
			PUSHA_OPEN_SET(0);
			PUSHA_CLOSE_SET(0);
		}
		else if(Push_Status == PUSH_OPEN)
		{
			PUSHA_OPEN_SET(1);
			PUSHA_CLOSE_SET(0);
		}
		else if(Push_Status == PUSH_CLOSE)
		{
			PUSHA_CLOSE_SET(1);
			PUSHA_OPEN_SET(0);
		}
      }
	else if(addr == PUSHB_ADDR)
	{
		if(Push_Status == PUSH_STOP)
		{
			PUSHB_OPEN_SET(0);
			PUSHB_CLOSE_SET(0);
		}
		else if(Push_Status == PUSH_OPEN)
		{
			PUSHB_OPEN_SET(1);
			PUSHB_CLOSE_SET(0);
		}
		else if(Push_Status == PUSH_CLOSE)
		{
			PUSHB_CLOSE_SET(1);
			PUSHB_OPEN_SET(0);
		}
	}
	else if(addr == PUSHC_ADDR)
	{
		if(Push_Status == PUSH_STOP)
		{
			PUSHC_OPEN_SET(0);
			PUSHC_CLOSE_SET(0);
		}
		else if(Push_Status == PUSH_OPEN)
		{
			PUSHC_OPEN_SET(1);
			PUSHC_CLOSE_SET(0);
		}
		else if(Push_Status == PUSH_CLOSE)
		{
			PUSHC_CLOSE_SET(1);
			PUSHC_OPEN_SET(0);
		}
	}
	else if(addr == PUSHD_ADDR)
	{
		if(Push_Status == PUSH_STOP)
		{
			PUSHD_OPEN_SET(0);
			PUSHD_CLOSE_SET(0);
		}
		else if(Push_Status == PUSH_OPEN)
		{
			PUSHD_OPEN_SET(1);
			PUSHD_CLOSE_SET(0);
		}
		else if(Push_Status == PUSH_CLOSE)
		{
			PUSHD_CLOSE_SET(1);
			PUSHD_OPEN_SET(0);
		}
	}
}

void PushResetHandle(void)
{
	if(!OnlyOneInputFlag)
	{
		OnlyOneInputFlag = PushReset_True;
		TimeOut_Record(&TimeOut_Para[0],500);//1000ms
              PUSHA_CLOSE_SET(1);
	}
       if(TimeOutDet_Check(&TimeOut_Para[0]))
	{
		if(!OnlyTwoInputFlag)
		{
			OnlyTwoInputFlag = PushReset_True;
			TimeOut_Record(&TimeOut_Para[1],500);//1000ms
			PUSHB_CLOSE_SET(1);
		}
		if(TimeOutDet_Check(&TimeOut_Para[1]))
		{
			PUSHC_CLOSE_SET(1);
		}
	}
}

void PushResetBackHandle(void)
{
	 PUSHA_CLOSE_SET(0);
	 PUSHB_CLOSE_SET(0);
	 PUSHC_CLOSE_SET(0);
	 OnlyOneInputFlag = PushReset_False;
	 OnlyTwoInputFlag = PushReset_False;
}

