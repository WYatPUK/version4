//预定义B_Sendp 和 B_Receivep
//#define central / peri

/*************
20160526修订
不需要再定义主机或从机，直接在函数名中体现，方便分别修改
可以同时定义多个输入输出口，最多支持15个控件，留出串口的两个引脚 

#define Num_Port <所需要的外围元件个数>
#define Port0_Sendp <例如P0^0>
#define Port0_Receivep <例如P0^1>
......

*************/
/************
20160531修订
接受不再分为两种，而是需要在调用函数的时候就要求接收端是低电平，否则返回Receive_Port_High
先包含此profile，然后根据需要包含Send.h和Receive.h 来使用 

************/
unsigned int SendData;
unsigned int ReceiveData;
unsigned char SendOrder;
unsigned char ReceiveOrder;


#if Num_Port>0
	sbit Sbit_Port0_Sendp = Port0_Sendp;
	sbit Sbit_Port0_Receivep = Port0_Receivep;
	void Send_Port0 (char x)
	{
		Sbit_Port0_Sendp = x;
	}
	char Receive_Port0 ()
	{
		return Sbit_Port0_Receivep;
	}
#endif
#if Num_Port>1
	sbit Sbit_Port1_Sendp = Port1_Sendp;
	sbit Sbit_Port1_Receivep = Port1_Receivep;
	void Send_Port1 (char x)
	{
		Sbit_Port1_Sendp = x;
	}
	char Receive_Port1 ()
	{
		return Sbit_Port1_Receivep;
	}
#endif
#if Num_Port>2
	sbit Sbit_Port2_Sendp = Port2_Sendp;
	sbit Sbit_Port2_Receivep = Port2_Receivep;
	void Send_Port2 (char x)
	{
		Sbit_Port2_Sendp = x;
	}
	char Receive_Port2 ()
	{
		return Sbit_Port2_Receivep;
	}
#endif
#if Num_Port>3
	sbit Sbit_Port3_Sendp = Port3_Sendp;
	sbit Sbit_Port3_Receivep = Port3_Receivep;
	void Send_Port3 (char x)
	{
		Sbit_Port3_Sendp = x;
	}
	char Receive_Port3 ()
	{
		return Sbit_Port3_Receivep;
	}
#endif
#if Num_Port>4
	sbit Sbit_Port4_Sendp = Port4_Sendp;
	sbit Sbit_Port4_Receivep = Port4_Receivep;
	void Send_Port4 (char x)
	{
		Sbit_Port4_Sendp = x;
	}
	char Receive_Port4 ()
	{
		return Sbit_Port4_Receivep;
	}
#endif
#if Num_Port>5
	sbit Sbit_Port5_Sendp = Port5_Sendp;
	sbit Sbit_Port5_Receivep = Port5_Receivep;
	void Send_Port5 (char x)
	{
		Sbit_Port5_Sendp = x;
	}
	char Receive_Port5 ()
	{
		return Sbit_Port5_Receivep;
	}
#endif
#if Num_Port>6
	sbit Sbit_Port6_Sendp = Port6_Sendp;
	sbit Sbit_Port6_Receivep = Port6_Receivep;
	void Send_Port6 (char x)
	{
		Sbit_Port6_Sendp = x;
	}
	char Receive_Port6 ()
	{
		return Sbit_Port6_Receivep;
	}
#endif
#if Num_Port>7
	sbit Sbit_Port7_Sendp = Port7_Sendp;
	sbit Sbit_Port7_Receivep = Port7_Receivep;
	void Send_Port7 (char x)
	{
		Sbit_Port7_Sendp = x;
	}
	char Receive_Port7 ()
	{
		return Sbit_Port7_Receivep;
	}
#endif
#if Num_Port>8
	sbit Sbit_Port8_Sendp = Port8_Sendp;
	sbit Sbit_Port8_Receivep = Port8_Receivep;
	void Send_Port8 (char x)
	{
		Sbit_Port8_Sendp = x;
	}
	char Receive_Port8 ()
	{
		return Sbit_Port8_Receivep;
	}
#endif
#if Num_Port>9
	sbit Sbit_Port9_Sendp = Port9_Sendp;
	sbit Sbit_Port9_Receivep = Port9_Receivep;
	void Send_Port9 (char x)
	{
		Sbit_Port9_Sendp = x;
	}
	char Receive_Port9 ()
	{
		return Sbit_Port9_Receivep;
	}
#endif
#if Num_Port>10
	sbit Sbit_Port10_Sendp = Port10_Sendp;
	sbit Sbit_Port10_Receivep = Port10_Receivep;
	void Send_Port10 (char x)
	{
		Sbit_Port10_Sendp = x;
	}
	char Receive_Port10 ()
	{
		return Sbit_Port10_Receivep;
	}
#endif
#if Num_Port>11
	sbit Sbit_Port11_Sendp = Port11_Sendp;
	sbit Sbit_Port11_Receivep = Port11_Receivep;
	void Send_Port11 (char x)
	{
		Sbit_Port11_Sendp = x;
	}
	char Receive_Port11 ()
	{
		return Sbit_Port11_Receivep;
	}
#endif
#if Num_Port>12
	sbit Sbit_Port12_Sendp = Port12_Sendp;
	sbit Sbit_Port12_Receivep = Port12_Receivep;
	void Send_Port12 (char x)
	{
		Sbit_Port12_Sendp = x;
	}
	char Receive_Port12 ()
	{
		return Sbit_Port12_Receivep;
	}
#endif
#if Num_Port>13
	sbit Sbit_Port13_Sendp = Port13_Sendp;
	sbit Sbit_Port13_Receivep = Port13_Receivep;
	void Send_Port13 (char x)
	{
		Sbit_Port13_Sendp = x;
	}
	char Receive_Port13 ()
	{
		return Sbit_Port13_Receivep;
	}
#endif
#if Num_Port>14
	sbit Sbit_Port14_Sendp = Port14_Sendp;
	sbit Sbit_Port14_Receivep = Port14_Receivep;
	void Send_Port14 (char x)
	{
		Sbit_Port14_Sendp = x;
	}
	char Receive_Port14 ()
	{
		return Sbit_Port14_Receivep;
	}
#endif

void Initialize_Communication()
{
	SendOrder = 0;
	SendData = 0;
	ReceiveOrder = 0;
	ReceiveData = 0;
	#if Num_Port>0
		Sbit_Port0_Sendp = 1;
		Sbit_Port0_Receivep = 1;
	#endif
	#if Num_Port>1
		Sbit_Port1_Sendp = 1;
		Sbit_Port1_Receivep = 1;
	#endif
	#if Num_Port>2
		Sbit_Port2_Sendp = 1;
		Sbit_Port2_Receivep = 1;
	#endif
	#if Num_Port>3
		Sbit_Port3_Sendp = 1;
		Sbit_Port3_Receivep = 1;
	#endif
	#if Num_Port>4
		Sbit_Port4_Sendp = 1;
		Sbit_Port4_Receivep = 1;
	#endif
	#if Num_Port>5
		Sbit_Port5_Sendp = 1;
		Sbit_Port5_Receivep = 1;
	#endif
	#if Num_Port>6
		Sbit_Port6_Sendp = 1;
		Sbit_Port6_Receivep = 1;
	#endif
	#if Num_Port>7
		Sbit_Port7_Sendp = 1;
		Sbit_Port7_Receivep = 1;
	#endif
	#if Num_Port>8
		Sbit_Port8_Sendp = 1;
		Sbit_Port8_Receivep = 1;
	#endif
	#if Num_Port>9
		Sbit_Port9_Sendp = 1;
		Sbit_Port9_Receivep = 1;
	#endif
	#if Num_Port>10
		Sbit_Port10_Sendp = 1;
		Sbit_Port10_Receivep = 1;
	#endif
	#if Num_Port>11
		Sbit_Port11_Sendp = 1;
		Sbit_Port11_Receivep = 1;
	#endif
	#if Num_Port>12
		Sbit_Port12_Sendp = 1;
		Sbit_Port12_Receivep = 1;
	#endif
	#if Num_Port>13
		Sbit_Port13_Sendp = 1;
		Sbit_Port13_Receivep = 1;
	#endif
	#if Num_Port>14
		Sbit_Port14_Sendp = 1;
		Sbit_Port14_Receivep = 1;
	#endif
}
typedef void (*Send_Port_Type[]) (char);
Send_Port_Type Send_Port =
{
	#if Num_Port>0
		Send_Port0
	#endif
	#if Num_Port>1 
		, Send_Port1 
	#endif
	#if Num_Port>2 
		, Send_Port2 
	#endif
	#if Num_Port>3 
		, Send_Port3 
	#endif
	#if Num_Port>4 
		, Send_Port4 
	#endif
	#if Num_Port>5 
		, Send_Port5 
	#endif
	#if Num_Port>6 
		, Send_Port6 
	#endif
	#if Num_Port>7 
		, Send_Port7
	#endif
	#if Num_Port>8
		, Send_Port8
	#endif
	#if Num_Port>9
		, Send_Port9
	#endif
	#if Num_Port>10
		, Send_Port10
	#endif
	#if Num_Port>11
		, Send_Port11
	#endif
	#if Num_Port>12
		, Send_Port12
	#endif
	#if Num_Port>13
		, Send_Port13
	#endif
	#if Num_Port>14
		, Send_Port14
	#endif
};
typedef char(*Receive_Port_Type[]) ();
Receive_Port_Type Receive_Port = //最多接入15个控件，留出串口的位置 
{
	#if Num_Port>0
		Receive_Port0
	#endif
	#if Num_Port>1 
		, Receive_Port1 
	#endif
	#if Num_Port>2 
		, Receive_Port2 
	#endif
	#if Num_Port>3 
		, Receive_Port3 
	#endif
	#if Num_Port>4 
		, Receive_Port4 
	#endif
	#if Num_Port>5 
		, Receive_Port5 
	#endif
	#if Num_Port>6 
		, Receive_Port6 
	#endif
	#if Num_Port>7 
		, Receive_Port7 
	#endif
	#if Num_Port>8 
		, Receive_Port8 
	#endif
	#if Num_Port>9 
		, Receive_Port9 
	#endif
	#if Num_Port>10 
		, Receive_Port10 
	#endif
	#if Num_Port>11 
		, Receive_Port12 
	#endif
	#if Num_Port>12 
		, Receive_Port12 
	#endif
	#if Num_Port>13 
		, Receive_Port13 
	#endif
	#if Num_Port>14 
		, Receive_Port14 
	#endif
};
