#ifndef _BSP_PWM_H_
#define _BSP_PWM_H_


#include "sc93f833x_c.h"



#define PWM_PORT   P0
#define PWM_PIN     P00
#define PWM_SET(X)  ((X)?(PWM_PIN=1):(PWM_PIN=0))












void Pwm_Init(void);
void Pwm15_Level(void);
void Pwm100_Level(void);
void Pwm_Handle(void);


#endif


