#include <reg51.h>


#include "GeneralAnswer0601.h"
#define This_UUID 0x1113

#define Password 0x3463

unsigned int R;//10位绝对值，6位数量级
unsigned int order;//8位命令
unsigned int x;
int nearistp;
#include "Find_Struct.h"
#include "link.h"

#define Num_Port 1
#define Port0_Sendp P2^0
#define Port0_Receivep  P0^7
#include "Communication_Profile0601.h"
#include "Communication_Receive_Central0601.h"
#include "Communication_Send_Central0601.h"

void DelaySelfCheck()
{
	int i, j;
	for (i=0; i<200; i++)
	{
		for (j=0 ; j<200; j++);
	}
}
void main()
{
	char mstate;
	P0 = 0;
	P1 = 0;
	P2 = 0;
	P3 = 0;
	Initialize_Communication();
	while (1)
	{
		 while (Receive_Port[0]() == 1);
		 mstate = ReceiveM_Port(0);
		 if (mstate != Receive_Finished)
		 {
		 	 continue;
		 }
		 if (ReceiveOrder == R_Cmd_GoStart) 
		 {
		 	 continue; //回到主进程
		 }
		 SendData = ReceiveData;
		 SendOrder = ReceiveOrder;
		 SendM_Port(0);
		 	 									   	    									  
		 if (ReceiveOrder == R_Cmd_Ask)//回复设备型号
		 {
		     SendData = This_UUID;//编号
			 SendOrder = Unit_Resistance;//说明是电阻型的
			 SendM_Port(0);
		 }
		 else if (ReceiveOrder == R_Cmd_Check)//启动自检程序
		 {
		 	 int i, p;
			 if(ReceiveData == Password)
			 {
			 	 SendOrder = T_Cmd_PasswordAccepted;
				 SendData = 0;
				 SendM_Port(0);
			 }
			 else
			 {
			 	 SendOrder = T_Cmd_PasswordWrong;
				 SendData = 0;
				 SendM_Port(0);
				 continue;
			 }
			 P0 = 1<<7;
			 P1 = 0;
			 P2 = 1;
			 P3 = 3;
			 p=1;
			 for (i=0; i<7; i++)
			 {
			 	P0 |= p;
				DelaySelfCheck();
				p<<=1;
				P0 = 1<<7;
				DelaySelfCheck();
			 }
			 p=1;
			 for (i=0; i<8; i++)
			 {
			 	P1 |= p;
				DelaySelfCheck();
				p<<=1;
				P1 = 0;
				DelaySelfCheck();
			 }
			 p=0x04;
			 for (i=0; i<6; i++)
			 {
			 	P3 |= p;
				DelaySelfCheck();
				p<<=1;
				P3 = 3;
				DelaySelfCheck();
			 }
			 p=2;
			 for (i=0; i<7; i++)
			 {
			 	P2 |= p;
				DelaySelfCheck();
				p<<=1;
				P2 = 1;
				DelaySelfCheck();
			 }
		 }
		 else if (ReceiveOrder == R_Cmd_Link) //连接8引脚电路
		 {
		 	 char a, b;
             ClearLink();
			 a = ReceiveData & 0x0f;	//解释连接方式
			 b = (ReceiveData>>4) & 0x0f;
			 if ((a==1 && b==1) || (a==2 && b==2))
			 {
			 	  SendOrder = T_Cmd_LinkWrong;
				  SendData = 0;
				  SendM_Port(0);
				  continue;
			 }
			 Link(a,b);
			 SendOrder = T_Cmd_LinkFinished;
		 	 SendData = 0;
			 SendM_Port(0);
		 }
		 else if (ReceiveOrder == Unit_Resistance)	//是电阻的单位
		 {
			 x = ReceiveData;
			 nearistp = Find_Nearist(x);
			 SendData = SListR[nearistp];
			 SendOrder = Unit_Resistance;
			 SendM_Port(0);
			 while (Receive_Port[0]() == 1);  //等待无限长时间，为保证安全，在进行新操作前，中控机需要发送GoStart指令
			 if (ReceiveM_Port(0) != Receive_Finished) continue;
			 if (ReceiveOrder == R_Cmd_GoStart) continue; //回到主进程 
			 if (ReceiveOrder == R_Cmd_FindConfirm)	//确认
			 Excute(nearistp);
		 }
		 else //未知命令
		 {
		 	 SendOrder = T_Cmd_UnkownCmd;
			 SendData = 0;
			 SendM_Port(0);
		 }
	}	
}