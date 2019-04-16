#ifndef _SYSTEM_H_
#define _SYSTEM_H_

#include "sc92f732x_c.h"





#include "bsp_led.h"
#include "bsp_timer.h"
#include "TimeOut.h"
#include "bsp_uart.h"
#include "string.h"
#include "bsp_push.h"
#include "bsp_table.h"
#include "bsp_key.h"




#define OnLine_Time    1000







void System_Init(void);
void System_Handle(void);





#endif

