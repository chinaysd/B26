#ifndef _KEY_PORT_H_
#define _KEY_PORT_H_


#include "sc93f833x_c.h"  
#include "bsp_key.h"

#define       False        0
#define       True         1

#define       KEY_LIGHT_VALUE                           0x00000008
#define       KEY_CUP_VALUE                              0X00000010
#define       KEY_HOME_VALUE                           0X00000010

#define       KEY_OPEN_VALUE                            0X00001000
#define       KEY_CLOSE_VALUE                           0X00000200

#define       KEY_HEAD_UP_VALUE                       0X00000100
#define       KEY_HEAD_DOWN_VALUE                  0X00000020

#define       KEY_LUMBAR_UP_VALUE                   0X00080000
#define       KEY_LUMBAR_DOWN_VALUE              0X00040000

#define      KEY_TABLE_UP_VALUE                      0X00008000
#define      KEY_TABLE_DOWN_VALUE                 0X00004000


#define       KEY_LOCK_VALUE                             0X00000000



unsigned long Key_Port_Read(unsigned char num);

#endif
