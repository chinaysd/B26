#include "system.h"




void System_Init(void)
{
     CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);
     Led_Init();
     Timer_Init();
     enableInterrupts(); //¿ªÆôÖÐ¶Ï
}

void System_Handle(void)
{

}



