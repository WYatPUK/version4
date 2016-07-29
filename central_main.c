#include <reg51.h>

char Str[30];
int Strlen;

#define central //������ȡcentral��Ҫ������ַ�����Ϣ
#include "GeneralAnswer0601.h"

void UsartConfiguration();

#define Num_Port 5	   //�����ܲ�����
#define Port0_Sendp P0^0
#define Port0_Receivep P0^1
#define Port1_Sendp P0^2
#define Port1_Receivep P0^3
#define Port2_Sendp P0^4
#define Port2_Receivep P0^5
#define Port3_Sendp P0^6
#define Port3_Receivep P0^7
#define Port4_Sendp P2^7
#define Port4_Receivep P2^6
#include "Communication_Profile0601.h"
#include "Communication_Send_Central0601.h"
#include "Communication_Receive_Central0601.h"

void main()
{
	UsartConfiguration();
	Initialize_Communication();
	Strlen = 0;	
	while (1)
	{
		
	}
}

/*
void SendString1(const char* a)
{
	int i;
	for (i=0; i<30 && a[i]!=0; i++)
	{
		SBUF = a[i];
		while (!TI);
		TI = 0;
	}
} */
void UsartConfiguration()
{
	SCON=0X50;			//����Ϊ������ʽ1
	TMOD=0X20;			//���ü�����������ʽ2
	PCON=0X80;			//�����ʼӱ�
	TH1=0XFA;
	//TH1=0XF3;		    //��������ʼֵ���ã�ע�Ⲩ������4800��
	//TL1=0XF3;
	TL1=0XFA;			 //������9600������
	ES=1;						//�򿪽����ж�
	EA=1;						//�����ж�
	TR1=1;					    //�򿪼�����
	ET1=0;
}

void SendString0(const char* a)
{
	int i;
	for (i=0; i<30 && a[i]!=0; i++)
	{
		SBUF = a[i];
		while (!TI);
		TI = 0;
	}
}

void SendCharHex(char x)
{
	unsigned char low;
	unsigned char high;
	low = x&0x0f;
	high = (x>>4)&0x0f;
	if (low<10) low = '0'+low;
	else low = 'a'+low-10;
	if (high<10) high = '0'+high;
	else high = 'a'+high-10;
	SBUF=high;
	while(!TI);
	TI=0;
	SBUF=low;
	while(!TI);
	TI=0;	
}
unsigned char CharToHex(char high, char low)
{
	unsigned char x; 
	if (high >= '0' && high <= '9')
	{
		x = (high - '0')<<4;
	}
	else if (high >= 'a' && high <= 'f')
	{
		x = (high - 'a' + 10)<<4;
	}
	else return 0;
	if (low >= '0' && low <= '9')
	{
		x |= (low - '0');
	}
	else if (low >= 'a' && low <= 'f')
	{
		x |= (low - 'a' + 10);
	}
	else return 0;
	return x;	
}

char Send_GoStart_Port(char Port)
{
	SendData = 0;
	SendOrder = R_Cmd_GoStart;
	return SendM_Port(Port);
}

void Serial_SendDataOrder(unsigned char Order, unsigned int Data)
{
	SendCharHex((Data>>8)&0xff);
	SendCharHex(Data&0xff) ;
	SendCharHex(Order);
}	 
void DoString()
{
	int i;
	char mPort;
	/*
	//�ж��Ƿ���Reָ��
	if (Strlen == Serial_Cmd_Re_Len + Serial_Cmd_Re_Extra)
	{
		for (i=0; i<Serial_Cmd_Re_Len; i++)
		{
			if (Str[i] != Serial_Cmd_Re[i]) break;
		}
		if (i == Serial_Cmd_Re_Len)
		{
			if (Send_GoStart_Port(0)!=Send_Finished)
			{
				SendString0(Serial_Back_GoStartWrong);
				return;
			}
			SendOrder = CharToHex(Str[i+4],Str[i+5]);
			SendData = (CharToHex(Str[i],Str[i+1])<<8) | CharToHex(Str[i+2],Str[i+3]);
			if (SendM_Port(0)!=Send_Finished)
			{
				SendString0(Serial_Back_SendWrong);
				return;
			}
			for (i=0; i<1000 && Receive_Port[0]() == 1; i++); //�ȴ�һ��ʱ�䣬Ӧ�ò���̫����̫��Ҳֻ�����ϵ�ù�ˣ���Ϊ֮ǰ�Ѿ�����ɹ�
			if (i==1000)
			{
				SendString0(Serial_Back_NoAnswer);
				return;
			}
			if (ReceiveM_Port(0) != Receive_Finished)
			{
				SendString0(Serial_Back_TreatyWrong);
				return;
			}
			Serial_SendDataOrder(ReceiveOrder, ReceiveData);
			return;
		}
	} */
	//�ж��Ƿ���Askָ��
	if (Strlen == Serial_Cmd_Ask_Len + Serial_Cmd_Port)
	{
		for (i=0; i<Serial_Cmd_Ask_Len; i++)
		{
			if (Str[i] != Serial_Cmd_Ask[i]) break;
		}
		if (i == Serial_Cmd_Ask_Len && Str[i] == '@')
		{
			//do something
			mPort =	CharToHex('0', Str[i + 1]);
			if (mPort >= Num_Port) 
			{
				SendString0(Serial_Back_PortNotExist);
				return;
			}
			if (Send_GoStart_Port(mPort)!=Send_Finished)
			{
				SendString0(Serial_Back_GoStartWrong);
				return;
			}
			SendOrder = R_Cmd_Ask;
			SendData = 0;
			if (SendM_Port(mPort)!=Send_Finished)
			{
				SendString0(Serial_Back_SendWrong);
				return;
			}
			for (i=0; i<1000 && Receive_Port[mPort]() == 1; i++); //�ȴ�һ��ʱ�䣬Ӧ�ò���̫����̫��Ҳֻ�����ϵ�ù�ˣ���Ϊ֮ǰ�Ѿ�����ɹ�
			if (i==1000)
			{
				SendString0(Serial_Back_NoAnswer);
				return;
			}
			if (ReceiveM_Port(mPort) != Receive_Finished)
			{
				SendString0(Serial_Back_TreatyWrong);
				return;
			}
			if (ReceiveOrder != SendOrder || ReceiveData != SendData)
			{
				SendString0(Serial_Back_WrongRepeatBack);
				Serial_SendDataOrder(ReceiveOrder, ReceiveData);
				return;
			}
			for (i=0; i<1000 && Receive_Port[mPort]() == 1; i++); //�ȴ�һ��ʱ�䣬Ӧ�ò���̫����̫��Ҳֻ�����ϵ�ù�ˣ���Ϊ֮ǰ�Ѿ�����ɹ�
			if (i==1000)
			{
				SendString0(Serial_Back_NoAnswer);
				return;
			}
			if (ReceiveM_Port(mPort)!=Receive_Finished)
			{
				SendString0(Serial_Back_TreatyWrong);
				return;
			}
			SendString0(Serial_Back_Info);
			Serial_SendDataOrder(ReceiveOrder, ReceiveData);
			SBUF = '#';
			while (!TI); TI = 0;
			return;
		}
	}
	
	//�ж��Ƿ���Findָ��
	if (Strlen == Serial_Cmd_Find_Len + Serial_Cmd_Find_Extra + 2)
	{
		for (i=0; i<Serial_Cmd_Find_Len; i++)
		{
			if (Str[i] != Serial_Cmd_Find[i]) break;
		}
		if (i == Serial_Cmd_Find_Len && Str[Serial_Cmd_Find_Len + Serial_Cmd_Find_Extra] == '@')
		{
			mPort =	CharToHex('0', Str[Serial_Cmd_Find_Len + Serial_Cmd_Find_Extra + 1]);
			if (mPort >= Num_Port) 
			{
				SendString0(Serial_Back_PortNotExist);
				return;
			}
			//do something
			if (Send_GoStart_Port(mPort)!=Send_Finished)
			{
				SendString0(Serial_Back_GoStartWrong);
				return;
			}
			SendOrder = CharToHex(Str[i+4],Str[i+5]);
			SendData = (CharToHex(Str[i],Str[i+1])<<8) | CharToHex(Str[i+2],Str[i+3]);
			if (SendM_Port(mPort)!=Send_Finished)
			{
				SendString0(Serial_Back_SendWrong);
				return;
			}
			for (i=0; i<1000 && Receive_Port[0]() == 1; i++); //�ȴ�һ��ʱ�䣬Ӧ�ò���̫����̫��Ҳֻ�����ϵ�ù�ˣ���Ϊ֮ǰ�Ѿ�����ɹ�
			if (i==1000)
			{
				SendString0(Serial_Back_NoAnswer);
				return;
			}														   
			if (ReceiveM_Port(mPort)!=Receive_Finished)
			{
				SendString0(Serial_Back_TreatyWrong);
				return;
			}
			if (ReceiveOrder != SendOrder || ReceiveData != SendData)
			{
				SendString0(Serial_Back_WrongRepeatBack);
				return;
			}
			for (i=0; i<10000 && Receive_Port[mPort]() == 1; i++); //�ȴ�һ��ʱ�䣬Ӧ�ò���̫����̫��Ҳֻ�����ϵ�ù�ˣ���Ϊ֮ǰ�Ѿ�����ɹ�
			if (i==10000)
			{
				SendString0(Serial_Back_NoAnswer);
				return;
			}
			if (ReceiveM_Port(mPort)!=Receive_Finished)
			{
				SendString0(Serial_Back_TreatyWrong);
				return;
			}
			SendString0(Serial_Back_Confirm);
			Serial_SendDataOrder(ReceiveOrder, ReceiveData);
			SBUF = '#';
			while (!TI); TI = 0;	
			return;
		}
	}
	//�ж��Ƿ���Confirmָ��
	if (Strlen == Serial_Cmd_Confirm_Len + 2)
	{
		for (i=0; i<Serial_Cmd_Confirm_Len; i++)
		{
			if (Str[i] != Serial_Cmd_Confirm[i]) break;
		}
		if (i == Serial_Cmd_Confirm_Len && Str[i] == '@')
		{
			mPort =	CharToHex('0', Str[i + 1]);
			if (mPort >= Num_Port) 
			{
				SendString0(Serial_Back_PortNotExist);
				return;
			}
			SendOrder = R_Cmd_FindConfirm;
			SendData = 0;
			if (SendM_Port(mPort)!=Send_Finished)
			{
				SendString0(Serial_Back_SendWrong);
				return;
			}
			SendString0(Serial_Back_Confirmed);
			return;
		}
	} 
	//�ж��Ƿ���Linkָ��
	if (Strlen == Serial_Cmd_Link_Len + Serial_Cmd_Link_Extra + Serial_Cmd_Port)
	{
		for (i=0; i<Serial_Cmd_Link_Len; i++)
		{
			if (Str[i] != Serial_Cmd_Link[i]) break;
		}
		if (i == Serial_Cmd_Link_Len && Str[i + Serial_Cmd_Link_Extra] == '@')
		{
			//do something
			mPort =	CharToHex('0', Str[i + Serial_Cmd_Link_Extra + 1]);
			if (Send_GoStart_Port(mPort)!=Send_Finished)
			{
				SendString0(Serial_Back_GoStartWrong);
				return;
			}
			SendOrder = R_Cmd_Link;
			SendData = (CharToHex(Str[i],Str[i+1])<<8) | CharToHex(Str[i+2],Str[i+3]);
			if (SendM_Port(mPort)!=Send_Finished)
			{
				SendString0(Serial_Back_SendWrong);
				return;
			}
			for (i=0; i<1000 && Receive_Port[mPort]() == 1; i++); //�ȴ�һ��ʱ�䣬Ӧ�ò���̫����̫��Ҳֻ�����ϵ�ù�ˣ���Ϊ֮ǰ�Ѿ�����ɹ�
			if (i==1000)
			{
				SendString0(Serial_Back_NoAnswer);
				return;
			}
			if (ReceiveM_Port(mPort)!=Receive_Finished)
			{
				SendString0(Serial_Back_TreatyWrong);
				return;
			}
			if (ReceiveOrder != SendOrder || ReceiveData != SendData)
			{
				SendString0(Serial_Back_WrongRepeatBack);
				return;
			}
			for (i=0; i<1000 && Receive_Port[mPort]() == 1; i++); //�ȴ�һ��ʱ�䣬Ӧ�ò���̫����̫��Ҳֻ�����ϵ�ù�ˣ���Ϊ֮ǰ�Ѿ�����ɹ�
			if (i==1000)
			{
				SendString0(Serial_Back_NoAnswer);
				return;
			}
			if (ReceiveM_Port(mPort)!=Receive_Finished)
			{
				SendString0(Serial_Back_TreatyWrong);
				return;
			}
			if (ReceiveOrder == T_Cmd_LinkFinished)
			{
				SendString0(Serial_Back_LinkFinished);
			}
			else if (ReceiveOrder == T_Cmd_LinkWrong)
			{
				SendString0(Serial_Back_LinkWrong);
				return;
			}
			else
			{
				SendString0(Serial_Back_NowayWrong);
				return;
			}
			return;
		}
	}
	//�ж��Ƿ���Checkָ��
	if (Strlen == Serial_Cmd_Check_Len + Serial_Cmd_Check_Extra + Serial_Cmd_Port)
	{
		for (i=0; i<Serial_Cmd_Check_Len; i++)
		{
			if (Str[i] != Serial_Cmd_Check[i]) break;
		}
		if (i == Serial_Cmd_Check_Len && Str[i + Serial_Cmd_Check_Extra] == '@')
		{
			//do something
			mPort = CharToHex('0', Str[i + Serial_Cmd_Check_Extra + 1]);
			if (Send_GoStart_Port(mPort)!=Send_Finished)
			{
				SendString0(Serial_Back_GoStartWrong);
				return;
			}
			SendOrder = R_Cmd_Check;
			SendData = (CharToHex(Str[i],Str[i+1])<<8) | CharToHex(Str[i+2],Str[i+3]);
			if (SendM_Port(mPort)!=Send_Finished)
			{
				SendString0(Serial_Back_SendWrong);
				return;
			}
			for (i=0; i<1000 && Receive_Port[mPort]() == 1; i++); //�ȴ�һ��ʱ�䣬Ӧ�ò���̫����̫��Ҳֻ�����ϵ�ù�ˣ���Ϊ֮ǰ�Ѿ�����ɹ�
			if (i==1000)
			{
				SendString0(Serial_Back_NoAnswer);
				return;
			}
			if (ReceiveM_Port(mPort)!=Receive_Finished)
			{
				SendString0(Serial_Back_TreatyWrong);
				return;
			}
			if (ReceiveOrder != SendOrder || ReceiveData != SendData)
			{
				SendString0(Serial_Back_WrongRepeatBack);
				return;
			}
			for (i=0; i<1000 && Receive_Port[mPort]() == 1; i++); //�ȴ�һ��ʱ�䣬Ӧ�ò���̫����̫��Ҳֻ�����ϵ�ù�ˣ���Ϊ֮ǰ�Ѿ�����ɹ�
			if (i==1000)
			{
				SendString0(Serial_Back_NoAnswer);
				return;
			}
			if (ReceiveM_Port(mPort)!=Receive_Finished)
			{
				SendString0(Serial_Back_TreatyWrong);
				return;
			}
			if (ReceiveOrder == T_Cmd_PasswordWrong)
			{
				SendString0(Serial_Back_PasswordWrong);
				return;
			}
			else if (ReceiveOrder == T_Cmd_PasswordAccepted)
			{
				SendString0(Serial_Back_PasswordAccepted);
			}
			else 
			{
				SendString0(Serial_Back_NowayWrong);
				return;
			}
			return;
		}
	}
	SendString0(Serial_Back_UnknownCmd);
	return;
}
void DoUSART(unsigned char receiveData)
{
	switch (receiveData)
	{							 
		case '$': //ˢ��Str �� ����Str����
			if (Strlen != 0)
			{
				DoString();
				Strlen = 0;
			}
			Strlen = 0;
			break;
		default:
			Str[Strlen] = receiveData;
			Strlen ++;
			break;
	}
}
void Usart() interrupt 4
{
	unsigned char receiveData;
	receiveData=SBUF; //��ȥ���յ�������
	RI = 0;           //��������жϱ�־λ
	DoUSART(receiveData);
	//SBUF=receiveData; //�����յ������ݷ��뵽���ͼĴ���
	//while(!TI);		  //�ȴ������������
	//TI=0;			  //���������ɱ�־λ
}
