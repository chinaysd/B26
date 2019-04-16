#ifndef _BSP_KEY_H_
#define _BSP_KEY_H_


#include "sc92f732x_c.h"


#define    KEY1_PORT     P2
#define    KEY1_PIN        P26

#define     KEY2_PORT     P2
#define     KEY2_PIN        P27

#define    KEY1_ID     0X01
#define    KEY2_ID     0X02

#define    KEY_DOWN    0X00
#define    KEY_UP         0X01















void Key_Init(void);
unsigned char Key_Handle(unsigned char ID);


#endif
