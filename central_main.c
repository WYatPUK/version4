#include <reg51.h>

char Str[30];
int Strlen;

#define central //用来获取central需要处理的字符串信息
#include "GeneralAnswer0601.h"

void UsartConfiguration();

#define Num_Port 5	   //试试能不能用
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
	SCON=0X50;			//设置为工作方式1
	TMOD=0X20;			//设置计数器工作方式2
	PCON=0X80;			//波特率加倍
	TH1=0XFA;
	//TH1=0XF3;		    //计数器初始值设置，注意波特率是4800的
	//TL1=0XF3;
	TL1=0XFA;			 //调成了9600波特率
	ES=1;						//打开接收中断
	EA=1;						//打开总中断
	TR1=1;					    //打开计数器
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
	//判定是否是Re指令
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
			for (i=0; i<1000 && Receive_Port[0]() == 1; i++); //等待一段时间，应该不用太长，太长也只能自认倒霉了，因为之前已经对码成功
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
	//判定是否是Ask指令
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
			for (i=0; i<1000 && Receive_Port[mPort]() == 1; i++); //等待一段时间，应该不用太长，太长也只能自认倒霉了，因为之前已经对码成功
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
			for (i=0; i<1000 && Receive_Port[mPort]() == 1; i++); //等待一段时间，应该不用太长，太长也只能自认倒霉了，因为之前已经对码成功
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
	
	//判定是否是Find指令
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
			for (i=0; i<1000 && Receive_Port[0]() == 1; i++); //等待一段时间，应该不用太长，太长也只能自认倒霉了，因为之前已经对码成功
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
			for (i=0; i<10000 && Receive_Port[mPort]() == 1; i++); //等待一段时间，应该不用太长，太长也只能自认倒霉了，因为之前已经对码成功
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
	//判定是否是Confirm指令
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
	//判定是否是Link指令
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
			for (i=0; i<1000 && Receive_Port[mPort]() == 1; i++); //等待一段时间，应该不用太长，太长也只能自认倒霉了，因为之前已经对码成功
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
			for (i=0; i<1000 && Receive_Port[mPort]() == 1; i++); //等待一段时间，应该不用太长，太长也只能自认倒霉了，因为之前已经对码成功
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
	//判定是否是Check指令
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
			for (i=0; i<1000 && Receive_Port[mPort]() == 1; i++); //等待一段时间，应该不用太长，太长也只能自认倒霉了，因为之前已经对码成功
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
			for (i=0; i<1000 && Receive_Port[mPort]() == 1; i++); //等待一段时间，应该不用太长，太长也只能自认倒霉了，因为之前已经对码成功
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
		case '$': //刷新Str 且 结束Str输入
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
	receiveData=SBUF; //出去接收到的数据
	RI = 0;           //清除接收中断标志位
	DoUSART(receiveData);
	//SBUF=receiveData; //将接收到的数据放入到发送寄存器
	//while(!TI);		  //等待发送数据完成
	//TI=0;			  //清除发送完成标志位
}
