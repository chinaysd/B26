#include  "bsp_timer.h"
#include "system.h"


void Timer_Init(void)
{
	TMCON = 0X07;                 //------111 ;Timer0��Tiemr1��Tiemr2ѡ��ʱ��Fsys
	//T0����
	TMOD = 0x11;                  //0001 0001  ;Timer0��Timer1���ù�����ʽ1
	TL0 = (65536 - 1000)%256;    //���ʱ�䣺ʱ��ΪFsys����12000*��1/Fsys��;
	TH0 = (65536 - 1000)/256;
	TR0 = 0;
	ET0 = 1;                      //��ʱ��0����
	TR0 = 1;                      //�򿪶�ʱ��0
	#if 0
	//T1����
	TL1 = (65536 - 100)%256;    //���ʱ�䣺ʱ��ΪFsys����24000*��1/Fsys��;
	TH1 = (65536 - 100)/256;
	TR1 = 0;
	ET1 = 1;                      //��ʱ��1����
	TR1 = 1;                      //�򿪶�ʱ��1
	#endif
	#if 1
	//T2����
	T2MOD = 0x00;
	T2CON = 0x00;	              //����Ϊ16λ���ؼĴ���
	RCAP2H = (65536-1000)/256;   //���ʱ�䣺ʱ��ΪFsys����12000*��1/Fsys��;
	RCAP2L = (65536-1000)%256;
	TR2 = 0;
	ET2 = 1;                      //��ʱ��2����
	TR2 = 1;                      //�򿪶�ʱ��2
	#endif
}

/**************************************************
*�������ƣ�void timer0/1() interrupt 1/3
*�������ܣ���ʱ���жϲ�������
*��ڲ�����void
*���ڲ�����void
**************************************************/
void timer0() interrupt 1     //100us
{
	EA = 0;
       TL0 = (65536 - 1000)%256;
	TH0 = (65536 - 1000)/256;
	TimeOutDet_DecHandle();
	Motro_Interrupt_Handle();
	Pwm_Handle();
	EA = 1;
}

void timer1() interrupt 3     //100us
{
       TL1 = (65536 - 100)%256;
	TH1 = (65536 - 100)/256;

}

void Timer2Int(void) interrupt 5    //1s
{		
	TF2 = 0;   //�������
      //P25 = ~P25;
      
}

