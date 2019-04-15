#ifndef _BSP_KEY_H_
#define _BSP_KEY_H_


#include "sc93f833x_c.h"
#include "SensorMethod.h"

/**
	@function: °´¼üÉ¨ÃèµÄÊ±¼ä¶¨Òå
	@brief: Ê±»ù125us
*/
#define 	KEY_SCAN_TIME			100				//	20ms		
#define 	KEY_JITTER_TIME			100				// 	20ms
#define 	KEY_CP_TIME				10000				//	ms
#define 	KEY_CPH_TIME			100				//  200ms	³¤°´±£³Ö´¥·¢Ê±¼


#define       NoData                    0x00
#define       OpenData                 0x01
#define       CloseData                 0x02
#define       HeadUpData              0x03
#define       HeadDownData          0x04
#define       LumbarOpenData       0x05
#define       LumbarCloseData       0x06
#define       TableOpenData         0x07       
#define       TableCloseData         0x08
#define       HomeData                0x09


#define       WarmOpenData       0x0A
#define       WarmCloseData       0x0B

#define       Led1_OpenData       0x0C
#define       Led1_CloseData       0x0D

#define       Mass_OpenData       0x0E
#define       Mass_CloseData       0x0F

#define       LockData                 0x99



#if 0
typedef enum
{
	KEY_NON_STATUS,
	KEY_LIGHT_STATUS,
       KEY_CUP_STATUS,
       KEY_HOME_STATUS,
       KEY_OPEN_STATUS,
       KEY_CLOSE_STATUS,
       KEY_HEAD_UP_STATUS,
       KEY_HEAD_DOWN_STATUS,
       KEY_LOCK_STATUS
}
KEY_MSG_STATUS;
#endif

/**
	@function:msg
	@brief:  Ö§³Ö¶Ì°´£¬³¤°´£¬³¤°´±£³Ö£¬³¤°´·ÅÊÖ
*/ 
typedef enum
{
	MSG_KEY_NONE=0,
	MSG_KEY1_PRESS ,
	MSG_KEY1_SHORT_PRESS ,
	MSG_KEY1_LONGPRESS,
	MSG_KEY1_LONGPRESS_HD,
	MSG_KEY1_LONGPRESS_RE,
	MSG_KEY2_PRESS,
	MSG_KEY2_SHORT_PRESS,
	MSG_KEY2_LONGPRESS,
	MSG_KEY2_LONGPRESS_HD,
	MSG_KEY2_LONGPRESS_RE,
	MSG_KEY3_PRESS,
	MSG_KEY3_SHORT_PRESS,
	MSG_KEY3_LONGPRESS,
	MSG_KEY3_LONGPRESS_HD,
	MSG_KEY3_LONGPRESS_RE,
	MSG_KEY4_PRESS,
	MSG_KEY4_SHORT_PRESS,
	MSG_KEY4_LONGPRESS,
	MSG_KEY4_LONGPRESS_HD,
	MSG_KEY4_LONGPRESS_RE,
	MSG_KEY5_PRESS,
	MSG_KEY5_SHORT_PRESS,
	MSG_KEY5_LONGPRESS,
	MSG_KEY5_LONGPRESS_HD,
	MSG_KEY5_LONGPRESS_RE,
	MSG_KEY6_PRESS,
	MSG_KEY6_SHORT_PRESS,
	MSG_KEY6_LONGPRESS,
	MSG_KEY6_LONGPRESS_HD,
	MSG_KEY6_LONGPRESS_RE,
	MSG_KEY7_PRESS,
	MSG_KEY7_SHORT_PRESS,
	MSG_KEY7_LONGPRESS,
	MSG_KEY7_LONGPRESS_HD,
	MSG_KEY7_LONGPRESS_RE,
	MSG_KEY8_PRESS,				
	MSG_KEY8_SHORT_PRESS, 				
	MSG_KEY8_LONGPRESS, 	
	MSG_KEY8_LONGPRESS_HD,	
	MSG_KEY8_LONGPRESS_RE,
	MSG_KEY9_PRESS,				
	MSG_KEY9_SHORT_PRESS, 				
	MSG_KEY9_LONGPRESS, 	
	MSG_KEY9_LONGPRESS_HD,	
	MSG_KEY9_LONGPRESS_RE,
	MSG_KEY10_PRESS,				
	MSG_KEY10_SHORT_PRESS, 				
	MSG_KEY10_LONGPRESS, 	
	MSG_KEY10_LONGPRESS_HD,	
	MSG_KEY10_LONGPRESS_RE,
	MSG_INVALID = 0XFF
}t_KEY_MSG;











void Key_Init(void);
void Key_Function(unsigned char GetValue);
void Key_Register(void (*Cb)(unsigned char));
void Key_Poll(void);

#endif


