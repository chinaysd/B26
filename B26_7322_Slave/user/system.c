#include "system.h"


extern unsigned char Rev_String[REV_BUF_SIZE];
extern TIMEOUT_PARA TimeOut_Para[4];

unsigned char TableOnlyOneInputFlag,TableOnlyTwoInputFlag;
unsigned int    TableOnlyOneInputCnts;
unsigned int  RevData;


void System_Init(void)
{
	TimeOutDet_Init();
     	Led_Init();
       TableKeyInit();
       Push_Init();
       Key_Init();
	Timer_Init();
	Uart_Init();
	WDTCON |= 0X10;
	EA = 1;
}

void System_Handle(void)
{
	WDTCON |= 0X10;
	if((0==(Key_Handle(KEY1_ID)))&&(0==(Key_Handle(KEY2_ID))))
	{
		 if(Rev_Select())
		 {
			RevData = (unsigned int)(Get32Bit(Rev_String[2],Rev_String[3]));
			memset(&Rev_String,0,sizeof(Rev_String));
			switch (RevData)
			{
				case 0x0001:     
							   Push_Handle(PUSHA_ADDR,PUSH_OPEN);
							   Send_Byte(0x01);
							   break;
			        case 0x0002:
							   Push_Handle(PUSHA_ADDR,PUSH_CLOSE);
							   Send_Byte(0x02);
							   break;
				case 0x0003:
							   Push_Handle(PUSHB_ADDR,PUSH_OPEN);
							   Send_Byte(0x03);
							   break;
				case 0x0004:
							   Push_Handle(PUSHB_ADDR,PUSH_CLOSE);
							   Send_Byte(0x04);
							   break;
				case 0x0005:
							   Push_Handle(PUSHC_ADDR,PUSH_OPEN);
							   Send_Byte(0x05);
							   break;
				case 0x0006:
							   Push_Handle(PUSHC_ADDR,PUSH_CLOSE);
							   Send_Byte(0x06);
							   break;
				case 0x0007:
							   if(TableReturnValue() == TABLE_ENABLE){
									Push_Handle(PUSHD_ADDR,PUSH_OPEN);
								       Send_Byte(0x07);
							   }
							   else
							   {
							   	Push_Handle(PUSHD_ADDR,PUSH_STOP);
							   }
							   break;
				case 0x0008:
							   if(TableReturnValue() == TABLE_ENABLE){
									Push_Handle(PUSHD_ADDR,PUSH_CLOSE);
								       Send_Byte(0x08);
							   }
							   else
							   {
							   	Push_Handle(PUSHD_ADDR,PUSH_STOP);
							   }
							   break;
				case 0x0009:
							   PushResetHandle();
							   break;
			       case 0x000C:
							   LED_SET(1);
							   Send_Byte(0x10);
							   break;
				case 0x00AA:
							   LED_SET(0);
							   Send_Byte(0x20);
							   break;
				default:
							PushResetBackHandle();
							Push_Handle(PUSHA_ADDR,PUSH_STOP);
							Push_Handle(PUSHB_ADDR,PUSH_STOP);
							Push_Handle(PUSHC_ADDR,PUSH_STOP);
							if(TableReturnValue() == TABLE_ENABLE){
							Push_Handle(PUSHD_ADDR,PUSH_STOP);
							TableOnlyOneInputFlag = 0;
							TableOnlyOneInputCnts = 0;
							}
							break;
			}
		 }
	}
	else if((Key_Handle(KEY1_ID)) &&(Key_Handle(KEY2_ID)))
	{
		if(Rev_Select())
		 {
			RevData = (unsigned int)(Get32Bit(Rev_String[2],Rev_String[3]));
			memset(&Rev_String,0,sizeof(Rev_String));
			switch (RevData)
			{
				case 0x0001:     
							   Push_Handle(PUSHA_ADDR,PUSH_CLOSE);
							   Send_Byte(0x02);
							   break;
			        case 0x0002:						   
							   Push_Handle(PUSHA_ADDR,PUSH_OPEN);
							   Send_Byte(0x01);
							   break;
				case 0x0003:
							   Push_Handle(PUSHB_ADDR,PUSH_CLOSE);
							   Send_Byte(0x04);
							   break;
				case 0x0004:
							   Push_Handle(PUSHB_ADDR,PUSH_OPEN);
							   Send_Byte(0x03);
							   break;
				case 0x0005:
							   Push_Handle(PUSHC_ADDR,PUSH_OPEN);
							   Send_Byte(0x05);
							   break;
				case 0x0006:
							   Push_Handle(PUSHC_ADDR,PUSH_CLOSE);
							   Send_Byte(0x06);
							   break;
				case 0x0007:
							   if(TableReturnValue() == TABLE_ENABLE){
									Push_Handle(PUSHD_ADDR,PUSH_OPEN);
								       Send_Byte(0x07);
							   }
							   else
							   {
							   	Push_Handle(PUSHD_ADDR,PUSH_STOP);
							   }
							   break;
				case 0x0008:
							   if(TableReturnValue() == TABLE_ENABLE){
									Push_Handle(PUSHD_ADDR,PUSH_CLOSE);
								       Send_Byte(0x08);
							   }
							   else
							   {
							   	Push_Handle(PUSHD_ADDR,PUSH_STOP);
							   }
							   break;
				case 0x0009:
							   PushResetHandle();
							   break;
			       case 0x000C:
							   LED_SET(1);
							   break;
				case 0x00AA:
							   LED_SET(0);
							   break;
				default:
							PushResetBackHandle();
							Push_Handle(PUSHA_ADDR,PUSH_STOP);
							Push_Handle(PUSHB_ADDR,PUSH_STOP);
							Push_Handle(PUSHC_ADDR,PUSH_STOP);
							if(TableReturnValue() == TABLE_ENABLE){
							Push_Handle(PUSHD_ADDR,PUSH_STOP);
							TableOnlyOneInputFlag = 0;
							TableOnlyOneInputCnts = 0;
							}
							break;
			}
		 }
	}
	else if(    (1    ==   (Key_Handle(KEY1_ID)))   &&      (0    ==   (Key_Handle(KEY2_ID)))          )
	{
		if(Rev_Select())
		 {
			RevData = (unsigned int)(Get32Bit(Rev_String[2],Rev_String[3]));
			memset(&Rev_String,0,sizeof(Rev_String));
			switch (RevData)
			{
				case 0x0001:     
							   Push_Handle(PUSHA_ADDR,PUSH_CLOSE);
							   Send_Byte(0x02);
							   break;
			        case 0x0002:
							   Push_Handle(PUSHA_ADDR,PUSH_OPEN);
							   Send_Byte(0x01);
							   break;
				case 0x0003:
							   Push_Handle(PUSHB_ADDR,PUSH_OPEN);
							   Send_Byte(0x03);
							   break;
				case 0x0004:
							   Push_Handle(PUSHB_ADDR,PUSH_CLOSE);
							   Send_Byte(0x04);
							   break;
				case 0x0005:
							   Push_Handle(PUSHC_ADDR,PUSH_OPEN);
							   Send_Byte(0x05);
							   break;
				case 0x0006:
							   Push_Handle(PUSHC_ADDR,PUSH_CLOSE);
							   Send_Byte(0x06);
							   break;
				case 0x0007:
							   if(TableReturnValue() == TABLE_ENABLE){
									Push_Handle(PUSHD_ADDR,PUSH_OPEN);
								       Send_Byte(0x07);
							   }
							   else
							   {
							   	Push_Handle(PUSHD_ADDR,PUSH_STOP);
							   }
							   break;
				case 0x0008:
							   if(TableReturnValue() == TABLE_ENABLE){
									Push_Handle(PUSHD_ADDR,PUSH_CLOSE);
								       Send_Byte(0x08);
							   }
							   else
							   {
							   	Push_Handle(PUSHD_ADDR,PUSH_STOP);
							   }
							   break;
				case 0x0009:
							   PushResetHandle();
							   break;
			       case 0x000C:
							   LED_SET(1);
							   break;
				case 0x00AA:
							   LED_SET(0);
							   break;
				default:
							PushResetBackHandle();
							Push_Handle(PUSHA_ADDR,PUSH_STOP);
							Push_Handle(PUSHB_ADDR,PUSH_STOP);
							Push_Handle(PUSHC_ADDR,PUSH_STOP);
							if(TableReturnValue() == TABLE_ENABLE){
							Push_Handle(PUSHD_ADDR,PUSH_STOP);
							TableOnlyOneInputFlag = 0;
							TableOnlyOneInputCnts = 0;
							}
							break;
			}
		 }
	}
	else if(    (0    ==   (Key_Handle(KEY1_ID)))   &&      (1    ==   (Key_Handle(KEY2_ID)))          )
	{
		if(Rev_Select())
		 {
			RevData = (unsigned int)(Get32Bit(Rev_String[2],Rev_String[3]));
			memset(&Rev_String,0,sizeof(Rev_String));
			switch (RevData)
			{
				case 0x0001:     
							   Push_Handle(PUSHA_ADDR,PUSH_OPEN);
							   Send_Byte(0x01);
							   break;
			        case 0x0002:
							   Push_Handle(PUSHA_ADDR,PUSH_CLOSE);
							   Send_Byte(0x02);
							   break;
				case 0x0003:
							   Push_Handle(PUSHB_ADDR,PUSH_CLOSE);
							   Send_Byte(0x04);
							   break;
				case 0x0004:
							   Push_Handle(PUSHB_ADDR,PUSH_OPEN);
							   Send_Byte(0x03);
							   break;
				case 0x0005:
							   Push_Handle(PUSHC_ADDR,PUSH_OPEN);
							   Send_Byte(0x05);
							   break;
				case 0x0006:
							   Push_Handle(PUSHC_ADDR,PUSH_CLOSE);
							   Send_Byte(0x06);
							   break;
				case 0x0007:
							   if(TableReturnValue() == TABLE_ENABLE){
									Push_Handle(PUSHD_ADDR,PUSH_OPEN);
								       Send_Byte(0x07);
							   }
							   else
							   {
							   	      Push_Handle(PUSHD_ADDR,PUSH_STOP);
								      //Send_Byte(0x0aa);
							   }
							   break;
				case 0x0008:
							   if(TableReturnValue() == TABLE_ENABLE){
									Push_Handle(PUSHD_ADDR,PUSH_CLOSE);
								       Send_Byte(0x08);
							   }
							   else
							   {
							   	      Push_Handle(PUSHD_ADDR,PUSH_STOP);
							   }
							   break;
				case 0x0009:
							   PushResetHandle();
							   break;
			       case 0x000C:
							   LED_SET(1);
							   break;
				case 0x00AA:
							   LED_SET(0);
							   break;
				default:
							PushResetBackHandle();
							Push_Handle(PUSHA_ADDR,PUSH_STOP);
							Push_Handle(PUSHB_ADDR,PUSH_STOP);
							Push_Handle(PUSHC_ADDR,PUSH_STOP);
							if(TableReturnValue() == TABLE_ENABLE){
							Push_Handle(PUSHD_ADDR,PUSH_STOP);
							TableOnlyOneInputFlag = 0;
							TableOnlyOneInputCnts = 0;
							TableOnlyTwoInputFlag = 0;
							}
							break;
			}
		 }
	}
	 
	 #if 1
	 if(TableReturnValue() == TABLE_DISABLE)
	 {
	 	#if 1
	 	if(!TableOnlyOneInputFlag)
	 	{
			TableOnlyOneInputFlag =1;
			TimeOut_Record(&TimeOut_Para[2],4000);
			Push_Handle(PUSHD_ADDR,PUSH_STOP);
		}
		if(TimeOutDet_Check(&TimeOut_Para[2]))
		{
			Push_Handle(PUSHD_ADDR,PUSH_CLOSE);
			if(!TableOnlyTwoInputFlag)
			{
				TableOnlyTwoInputFlag = 1;
				TimeOut_Record(&TimeOut_Para[3],14000);
			}
			if(TimeOutDet_Check(&TimeOut_Para[3]))
			{
				Push_Handle(PUSHD_ADDR,PUSH_STOP);
			}
		}
		#else
		if(!TableOnlyOneInputFlag)
		{
			TableOnlyOneInputFlag  = 1;
			TableOnlyOneInputCnts = 0;
			Push_Handle(PUSHD_ADDR,PUSH_CLOSE);

		}
	       if(TableOnlyOneInputCnts > 15000)
	      {
			TableOnlyOneInputCnts = 0;
			//TableOnlyOneInputFlag = 0;
			Push_Handle(PUSHD_ADDR,PUSH_STOP);
	       }
		#endif
	 }
	 else
	 {
	 	TableOnlyOneInputFlag = 0;
		TableOnlyOneInputCnts = 0;
		TableOnlyTwoInputFlag = 0;
	 }
	 #endif
}


