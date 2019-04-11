#ifndef _BSP_MOTRO_H_
#define _BSP_MOTRO_H_

#include "sc93f833x_c.h"



#define MOTRO1_PORT      P0
#define MOTRO1_PIN         P01


#define MOTRO_PORT         P0
#define MOTRO_PIN            P02




void Motro_Init(void);
void Motro_Handle(void);
void Motro_Interrupt_Handle(void);

#endif

