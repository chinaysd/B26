#ifndef _SYSTEM_H_
#define _SYSTEM_H_

#include "sc93f833x_c.h"
#include "bsp_led.h"
#include  "bsp_timer.h"
#include "TimeOut.h"
#include "bsp_uart.h"
#include "bsp_key.h"
#include "bsp_pwm.h"
#include "bsp_motro.h"
#include "bsp_lock.h"










void System_Init(void);
void System_Handle(void);


#endif

