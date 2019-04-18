#include "bsp_key.h"
#include "TimeOut.h"
#include "key_port.h"
#include "bsp_pwm.h"
#include "bsp_lock.h"
#include "bsp_motro.h"




typedef enum {
    KEY_STATE_IDLE,
    KEY_STATE_JITTER,
    KEY_STATE_PRESS_DOWN,
    KEY_STATE_CP
} KEY_STATE;

unsigned char SendBackData;
unsigned long get_key_data;

unsigned char LedOnlyOneInputFlag;
//KEY_MSG_STATUS KeyMsgStatus;

static TIMEOUT_PARA Key_Scan_Timer,Key_Wait_Timer;
static KEY_STATE	KeyState;
static t_KEY_MSG Key_Msg;
static unsigned char PreKeyIndex = MSG_INVALID;
static unsigned char Led1_OpenFlag;

extern unsigned char Lock_Flag;
extern unsigned char Pwm_Level;

static void (*GetValueCb)(unsigned char);


/**
	@function: 按键事件，更多按键时，对应增加按键按键
	
*/
static xdata unsigned char KeyEvent[11][5]=
{
	//按键开始(按下)	    		短按								长按					长按保持						长按松开
	{MSG_KEY_NONE,					MSG_KEY_NONE,						MSG_KEY_NONE,			MSG_KEY_NONE,						MSG_KEY_NONE},			// 空，无用
	{MSG_KEY1_PRESS,				MSG_KEY1_SHORT_PRESS,				MSG_KEY1_LONGPRESS,	MSG_KEY1_LONGPRESS_HD,				MSG_KEY1_LONGPRESS_RE},		// key1
	{MSG_KEY2_PRESS,				MSG_KEY2_SHORT_PRESS,				MSG_KEY2_LONGPRESS,	MSG_KEY2_LONGPRESS_HD,				MSG_KEY2_LONGPRESS_RE},		// key2
	{MSG_KEY3_PRESS,				MSG_KEY3_SHORT_PRESS, 				MSG_KEY3_LONGPRESS, 	MSG_KEY3_LONGPRESS_HD,				MSG_KEY3_LONGPRESS_RE},	// key3	
	{MSG_KEY4_PRESS,				MSG_KEY4_SHORT_PRESS, 				MSG_KEY4_LONGPRESS, 	MSG_KEY4_LONGPRESS_HD,				MSG_KEY4_LONGPRESS_RE},	// key4	
	{MSG_KEY5_PRESS,				MSG_KEY5_SHORT_PRESS, 				MSG_KEY5_LONGPRESS, 	MSG_KEY5_LONGPRESS_HD,				MSG_KEY5_LONGPRESS_RE},	// key5
	{MSG_KEY6_PRESS,				MSG_KEY6_SHORT_PRESS, 				MSG_KEY6_LONGPRESS, 	MSG_KEY6_LONGPRESS_HD,				MSG_KEY6_LONGPRESS_RE},	// key6
	{MSG_KEY7_PRESS,				MSG_KEY7_SHORT_PRESS, 				MSG_KEY7_LONGPRESS, 	MSG_KEY7_LONGPRESS_HD,				MSG_KEY7_LONGPRESS_RE},	// key7
       {MSG_KEY8_PRESS,				MSG_KEY8_SHORT_PRESS, 				MSG_KEY8_LONGPRESS, 	MSG_KEY8_LONGPRESS_HD,				MSG_KEY8_LONGPRESS_RE},	// key8
	{MSG_KEY9_PRESS,			       MSG_KEY9_SHORT_PRESS,				MSG_KEY9_LONGPRESS,	 MSG_KEY9_LONGPRESS_HD, 			MSG_KEY9_LONGPRESS_RE},     // key9
	{MSG_KEY10_PRESS,			       MSG_KEY10_SHORT_PRESS,				MSG_KEY10_LONGPRESS,	 MSG_KEY10_LONGPRESS_HD, 			MSG_KEY10_LONGPRESS_RE}, // key7
};

/**
	@function:	获取按键索引值
	根据按键的个数，需要做相应的修改
*/
static unsigned char GetKeyIndex(void)
{
	extern unsigned long Key_Port_Read(unsigned char num);
	unsigned char value = 0,cnt = 0;
	if(Key_Port_Read(1))
		cnt ++,value = 1;
	if(Key_Port_Read(2))
		cnt ++,value = 2;
	if(Key_Port_Read(3))
		cnt ++,value = 3;
	if(Key_Port_Read(4))
		cnt ++,value = 4;
	if(Key_Port_Read(5))
		cnt ++,value = 5;
	if(Key_Port_Read(6))
		cnt ++,value = 6;
	if(Key_Port_Read(7))
		cnt ++,value = 7;
	if(Key_Port_Read(8))
		cnt ++,value = 8;
	if(Key_Port_Read(9))
		cnt ++,value = 9;
	if(Key_Port_Read(10))
		cnt ++,value = 10;
	if(cnt > 1)
		value = MSG_INVALID;
	return value;	
}


void  Key_Init(void)
{
	TouchKeyInit(); // 触控按键初始化
	KeyState=KEY_STATE_IDLE;
	TimeOut_Record(&Key_Scan_Timer,0);
}

void Key_Function(unsigned char GetValue)
{
	static unsigned char TempCnts,LockCnts,LockOnlyOneFlag;
	if(GetValue == MSG_KEY_NONE)
	{
		if((SendBackData == Led1_OpenData)||(SendBackData == Led1_CloseData))
		{
			LedOnlyOneInputFlag = 0;
		}
		else
		{
			if((SendBackData == OpenData)||(SendBackData == CloseData)||(SendBackData == HeadUpData)\
			||(SendBackData == HeadDownData)||(SendBackData == LumbarOpenData)||(LumbarCloseData)\
			||(SendBackData == HomeData))
			{
				SendBackData = NoData;
			}
		}
		LockOnlyOneFlag = 0;
	}
	else if((GetValue == MSG_KEY1_SHORT_PRESS)&&(!Lock_Flag))
	{
		#if 0
		if((SendBackData != Led1_OpenData)||(SendBackData != Led1_CloseData))
		{
			++ TempCnts;
			if(TempCnts & 0x01)
			{
				SendBackData = Led1_OpenData;
				Pwm100_Level();
			}
			else
			{
				SendBackData = Led1_CloseData;
				Pwm15_Level();
			}
		}
		#else
              if(!LedOnlyOneInputFlag)
              {
			LedOnlyOneInputFlag = 1;
			++ TempCnts;
			if(TempCnts & 0x01)
			{
				SendBackData = Led1_OpenData;
				Led1_OpenFlag = 1;
				Pwm100_Level();
			}
			else
			{
				SendBackData = Led1_CloseData;
				Led1_OpenFlag = 0;
				Pwm15_Level();
			}
	        }
		#endif
	}
	else if((GetValue == MSG_KEY2_SHORT_PRESS)&&(!Lock_Flag))
	{
		Motro_Handle();
	}
	else if((GetValue == MSG_KEY3_PRESS)&&(!Lock_Flag))
	{
		if(SendBackData != OpenData)
		{
			SendBackData = OpenData;
		}
	}
	else if((GetValue == MSG_KEY4_PRESS)&&(!Lock_Flag))
	{
		if(SendBackData != CloseData)
		{
			SendBackData = CloseData;
		}
	}
	else if((GetValue == MSG_KEY5_PRESS)&&(!Lock_Flag))
	{
		if(SendBackData != HeadUpData)
		{
			SendBackData = HeadUpData;
		}
	}
	else if((GetValue == MSG_KEY6_PRESS)&&(!Lock_Flag))
	{
		if(SendBackData != HeadDownData)
		{
			SendBackData = HeadDownData;
		}
	}
	else if((GetValue == MSG_KEY7_PRESS)&&(!Lock_Flag))
	{
		if(SendBackData != LumbarOpenData)
		{
			SendBackData = LumbarOpenData;
		}
	}
	else if((GetValue == MSG_KEY8_PRESS)&&(!Lock_Flag))
	{
              if(SendBackData != LumbarCloseData)
		{
			SendBackData = LumbarCloseData;
		}
	}
	else if((GetValue == MSG_KEY9_PRESS)&&(!Lock_Flag))
	{
		 if(SendBackData != TableOpenData)
		{
			SendBackData = TableOpenData;
		}
	}
	else if((GetValue == MSG_KEY10_PRESS)&&(!Lock_Flag))
	{
             if(SendBackData != TableCloseData)
		{
			SendBackData = TableCloseData;
		}
	}
	else if((GetValue == MSG_KEY2_LONGPRESS_HD)&&(!Lock_Flag))
	{
		if(SendBackData != HomeData)
             {
			SendBackData = HomeData;
		}
	}
	else if(GetValue == MSG_KEY1_LONGPRESS_HD)
	{
		#if 0
		if(SendBackData != LockData)
		{
			SendBackData = LockData;
			++ LockCnts;
			Lock_Handle();
			if(LockCnts & 0x01)
			{
				Pwm_Level = 0
			}
			else
			{
				
			}
		}
		#else
		if(!LockOnlyOneFlag)
		{
                    LockOnlyOneFlag = 1;
		       ++ LockCnts;
			Lock_Handle();
		}
		else
		{
			#if 0
			if(LockCnts & 0x01)
			{
				Pwm_Level = 0;
			}
			else
			{
				if(SendBackData == Led1_OpenData)
				{
					Pwm_Level = 100;
				}
				else if(SendBackData == Led1_CloseData)
				{
					Pwm_Level = 15;
				}
			}
			#else
			#endif
		}

		#endif
	}
       if(LockCnts & 0x01)
	{
		Pwm_Level = 0;
	}
	else
	{	
		if(Led1_OpenFlag)
		{
			Pwm100_Level();
		}
		else if(Led1_OpenFlag == 2)
		{
			Pwm15_Level();
		}
		else
		{
			Pwm15_Level();
		}
	}
}
/**
	@function:按键的扫描
	@return :t_KEY_MSG 类型的消息，消息集在t_KEY_MSG中定义
*/
t_KEY_MSG Key_Scan(void){
	unsigned char KeyIndex;
	if(SOCAPI_TouchKeyStatus&0x80) // 重要步骤 2: 触摸键扫描一轮标志，是否调用 TouchKeyScan() 一定要根据此标志位置起后
	{
		SOCAPI_TouchKeyStatus &= 0x7f;// 重要步骤 3:  清除标志位， 需要外部清除。
		get_key_data = TouchKeyScan();// 按键数据处理函数
		TouchKeyRestart();// 启动下一轮转换
	}
	
	if(!(TimeOutDet_Check(&Key_Scan_Timer))){
		return MSG_INVALID;
	}
	
	TimeOut_Record(&Key_Scan_Timer,KEY_SCAN_TIME);
	
	KeyIndex=GetKeyIndex();
	if(KeyIndex == MSG_INVALID)
		return MSG_INVALID;

	switch(KeyState){
		case KEY_STATE_IDLE:{
			if(!KeyIndex){
				return MSG_KEY_NONE;
			}
			PreKeyIndex = KeyIndex;
			TimeOut_Record(&Key_Wait_Timer,KEY_JITTER_TIME);
			KeyState = KEY_STATE_JITTER;
			break;
		}
		
		case KEY_STATE_JITTER:{
			if(PreKeyIndex != KeyIndex){
				KeyState = KEY_STATE_IDLE;
			}else if(TimeOutDet_Check(&Key_Wait_Timer)){
				TimeOut_Record(&Key_Wait_Timer,KEY_CP_TIME);
				KeyState = KEY_STATE_PRESS_DOWN;
				return KeyEvent[PreKeyIndex][0];
			}
			break;
		}

		case KEY_STATE_PRESS_DOWN:{
			if(PreKeyIndex != KeyIndex){
				KeyState = KEY_STATE_IDLE;
				return KeyEvent[PreKeyIndex][1];
			}else if(TimeOutDet_Check(&Key_Wait_Timer)){
				TimeOut_Record(&Key_Wait_Timer,KEY_CPH_TIME);
				KeyState = KEY_STATE_CP;
				return KeyEvent[PreKeyIndex][2];
			}
			break;
		}
		
		case KEY_STATE_CP:{
			if(PreKeyIndex != KeyIndex){
				KeyState = KEY_STATE_IDLE;
				return KeyEvent[PreKeyIndex][4];
			}else if(TimeOutDet_Check(&Key_Wait_Timer)){
				TimeOut_Record(&Key_Wait_Timer,KEY_CPH_TIME);
				return KeyEvent[PreKeyIndex][3];
			}
			break;
		}
		
		default:{
			KeyState = KEY_STATE_IDLE;
			break;
		}
	}
	return MSG_INVALID;
}


void Key_Register(void (*Cb)(unsigned char))
{
	if(Cb)
	{
		GetValueCb = Cb;
	}
}

void Key_Poll(void)
{
	Key_Msg = Key_Scan();
	if(GetValueCb)
	{
		GetValueCb(Key_Msg);
	}
}

