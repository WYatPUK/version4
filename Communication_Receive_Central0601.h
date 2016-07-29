#define Receive_Finished 0x00
#define Receive_Port_Not_Exist 0x01
#define Receive_Port_High 0x02
#define Receive_Recognize1_Wrong 0x03
#define Receive_Recognize_Wrong 0x04
#define Receive_Recognize2_Wrong 0x05
#define Receive_Process_TimeOut 0x06
//这是两次的实验数据
//01 28 29 11 12 12 24 11 11 24 11 11 11 24 24 11 24 12 12 11 23 11 24 11 11 11 11 29 00 
//01 28 29 10 11 12 24 11 11 24 12 12 11 23 24 11 24 12 12 12 12 12 12 11 11 24 24 29 00 
//为了执行严格的标准，实验下限-2，上限+2为最终的区间，在此区间外的一律认为是不合法设备
//26~31
//9~14
//21~26

//失败

//再次实验	  //啊啊啊啊啊啊啊啊那些都是16进制数，不是10进制，我是脑残啊啊啊啊啊啊啊啊
//01 28 29 10 11 12 24 11 11 24 11 12 11 24 23 11 23 11 12 11 24 11 23 11 12 11 11 29 00 00 00 
//01 29 28 12 11 11 24 11 12 24 11 11 12 24 24 12 24 12 11 12 11 11 12 11 11 24 23 29 00 00 00 
//01 29 28 12 11 11 24 12 11 24 11 11 12 24 24 12 24 12 11 12 11 11 12 11 11 24 23 29 00 00 00 
//40，41   38~43
//16，17，18    14~20
//35，36    33~38

//成功
char ReceiveM_Port(char Port)
{
	unsigned char j, i;
	ReceiveOrder = 0;
	ReceiveData = 0;
	//一开始需要满足的条件 
	if(Port>=Num_Port) return Receive_Port_Not_Exist;
	//接受脚如果是高电平，则返回
	if(Receive_Port[Port]() == 1) return Receive_Port_High;
	//开始对码，需要以上的步骤要少于10+个周期
	//先立即输出0 然后开始计数，如果是实验，先保存下来，最后统一用串口输出，如果是实际使用，需要当场判断（判断小于10+个周期）。
	//接着输出1，然后开始计数，同上
	Send_Port[Port](0);
	for (i=0; i<200 && Receive_Port[Port]() == 0; i++)
	{
		Send_Port[Port](0);//其实这是为了拖延时间的，不然一个char计数太多不好 
	}
	if (i<18 || i>23) 
	{
		Send_Port[Port](1);//这一句一定要有，不然下次发送不了 
		return Receive_Recognize1_Wrong;
	}
	Send_Port[Port](1);
	for (i=0; i<200 && Receive_Port[Port]() == 1; i++)
	{
		Send_Port[Port](1);
	}
	if (i<18 || i>23) return Receive_Recognize1_Wrong;
	//对码结束 
	for (i=0; i<16; i++)
	{
		for (j=0; j<70 && Receive_Port[Port]() == 0; ++j);
		if (j == 70) return Receive_Process_TimeOut;
		if (j<12 && j>5) //认为是0
		{
			ReceiveData<<=1;
			ReceiveData |= 0;
		}
		else if (j<23 && j>14) //认为是1
		{
			ReceiveData<<=1;
			ReceiveData |= 1;
		}
		else //错误
		{
			return Receive_Recognize_Wrong;
		}
		for (j=0; j<70 && Receive_Port[Port]() == 1; ++j);
		if (j == 70) return Receive_Process_TimeOut;
	}
	for (i=0; i<7; i++)
	{
		for (j=0; j<70 && Receive_Port[Port]() == 0; ++j);
		if (j == 70) return Receive_Process_TimeOut;
		if (j<12 && j>5) //认为是0
		{
			ReceiveOrder<<=1;
			ReceiveOrder |= 0;
		}
		else if (j<23 && j>14) //认为是1
		{
			ReceiveOrder<<=1;
			ReceiveOrder |= 1;
		}
		else //错误
		{
			return Receive_Recognize_Wrong;
		}
		for (j=0; j<70 && Receive_Port[Port]() == 1; ++j);
		if (j == 70) return Receive_Process_TimeOut;
	}
    for (j=0; j<70 && Receive_Port[Port]() == 0; ++j);
	if (j == 70) return Receive_Process_TimeOut;
	if (j<12 && j>5) //认为是0
	{
		ReceiveOrder<<=1;
		ReceiveOrder |= 0;	
	}
	else if (j<23 && j>14) //认为是1
	{
		ReceiveOrder<<=1;
		ReceiveOrder |= 1;
	}
	else //错误
	{
		return Receive_Recognize_Wrong;
	}
	//接收完毕
	//再次对码
	for (j=0; j<70 && Receive_Port[Port]() == 1; ++j);
	if (j == 70) return Receive_Process_TimeOut;
	Send_Port[Port](0);
	for (i=0; i<200 && Receive_Port[Port]() == 0; i++)
	{
		Send_Port[Port](0);//其实这是为了拖延时间的，不然一个char计数太多不好 
	} 
	if (i<18 || i>23) 
	{
		Send_Port[Port](1);//这一句一定要有，不然下次发送不了 
		return Receive_Recognize2_Wrong;
	}
	Send_Port[Port](1);
	//对码完毕
	//成功
	return Receive_Finished;
}
