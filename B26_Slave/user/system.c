#include "system.h"




void System_Init(void)
{
     CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);
     Led_Init();
     Timer_Init();
     enableInterrupts(); //�����ж�
}

void System_Handle(void)
{

}



