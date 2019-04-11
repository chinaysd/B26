#ifndef _BSP_LOCK_H_
#define _BSP_LOCK_H_

#include "sc93f833x_c.h"


#define Lock_True     1
#define Lock_False    0

#define RED_PORT    P2
#define RED_PIN       P25
#define RED_SET(X)   ((X)?(RED_PIN=1):(RED_PIN=0))


void Lock_Init(void);
void Lock_Handle(void);


#endif

