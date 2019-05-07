#include "bsp_uart.h"
#include "string.h"

unsigned char Uart0SendFlag,Uart0ReceiveFlag;

void Uart_Init(unsigned char Freq,unsigned int BaudRate)
{
	#if 1
       P1CON &= 0xF3;
	P1PH = 0X0C;	 //TX/RXΪ���������룻

       PCON |= 0x80;    //SMOD = 1��
	SCON = 0X50;     //����ͨ�ŷ�ʽΪģʽһ���������
	T2CON = 0x00;    //ʹ�ö�ʱ��1��UARTʱ��
	TMCON = 0X03;    //��ʱ��ʱ��ΪFsys
	TMOD = 0X20;     //8λ����
	TH1 = 256 - (Freq*1000000/BaudRate/16);	     //��24Mʱ��������Ϊ9600��
	TR1 = 1;
	EUART = 1;       //����Uart0�ж�
	EA = 1;
	#else
       P1CON &= 0xF3;
	P1PH = 0X0C;	 //TX/RXΪ���������룻

       PCON |= 0x80;    //SMOD = 1��
	SCON = 0X50;     //����ͨ�ŷ�ʽΪģʽһ���������
	T2CON = 0x36;    //ʹ�ö�ʱ��1��UARTʱ��
	TMCON = 0X03;    //��ʱ��ʱ��ΪFsys
	TMOD = 0X20;     //8λ����
	TH2 = 256 - (Freq*1000000/BaudRate/16);	     //��24Mʱ��������Ϊ9600��
	TR2 = 1;
	EUART = 1;       //����Uart0�ж�
	EA = 1;
	#endif
}

static void Send_Byte(unsigned char Byte)
{
	 SBUF = Byte;
        while(!(Uart0SendFlag));
        Uart0SendFlag = 0;
}

static unsigned char Send_Data(PROTOCOL_TX *p)
{
	static unsigned char Cnts;
	for(Cnts = 0;Cnts < SENDBUFSIZE;Cnts ++)
	{
		Send_Byte(p->Buf[Cnts]);
	}
	return 1;
}

unsigned char Protocol_Send(unsigned char addr,unsigned char id,unsigned int TX_DATA)
{
	PROTOCOL_TX buf;
	memset(&buf,0,sizeof(buf));
	buf.Data_Format.ADDR = addr;
	buf.Data_Format.ID      = id;
	buf.Data_Format.DATA1 = Hight(TX_DATA);
	buf.Data_Format.DATA2 = Low(TX_DATA);
	buf.Data_Format.CHECKSUM = (unsigned char)(buf.Data_Format.ADDR + buf.Data_Format.ID +buf.Data_Format.DATA1 + buf.Data_Format.DATA2);
	buf.Data_Format.STOP1 = 0x0d;
	buf.Data_Format.STOP2 = 0x0a;
	return Send_Data(&buf);
}



/*****************************************************
*�������ƣ�void UartInt(void) interrupt 4
*�������ܣ�Uart0�жϺ���
*��ڲ�����void
*���ڲ�����void
*****************************************************/
void UartInt(void) interrupt 4
{
	if(TI)
	{
	    TI=0;	
	    Uart0SendFlag = 1;
	}
	if(RI)
	{
	     RI=0;
	     Uart0ReceiveFlag = 1;
	}
}




