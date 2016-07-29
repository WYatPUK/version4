#define Send_Finished 0x00
#define Send_Port_Not_Exist 0x01
#define Send_Port_Low 0x02 
#define Send_Recognize1_Wrong 0x03 
#define Send_Recognize2_Wrong 0x04
char SendM_Port(char Port)
{
	unsigned char S[24], j, i, x;
	//一开始需要满足的条件 
	if(Port>=Num_Port) return Send_Port_Not_Exist;
	//接受脚如果是低电平，则返回
	if(Receive_Port[Port]() == 0) return Send_Port_Low; 
	//开始集中处理数据
	j = 0; 
	for (i=15; i<=15; --i)
	{
		S[j] = ((SendData>>i)&1) * 10 + 10;
		j++;
	}
	for (i=7; i<=7; --i)
	{
		S[j] = ((SendOrder>>i)&1) * 10 + 10;
		j++;
	}
	//处理数据完毕
	//开始对码 先输出0，对方须在10+步内回复0 + 75位的低电平，告知对方这是Wy设备 + 后输出1，对方须在10+步内回复1 + 后接75位的高电平 对吗完毕 
	for (i=0; i<10 && Receive_Port[Port]() == 1; ++i)
	{
		Send_Port[Port](0);
	} 
	if (i == 10) 
	{
		Send_Port[Port](1);//一定要有，不然对方就会一直认为有信息在传递
		return Send_Recognize1_Wrong; //调试的时候去掉
	} 
	for (i=0; i<37; ++i)
	{
		Send_Port[Port](0);
	} 
	for (i=0; i<10 && Receive_Port[Port]() == 0; ++i)
	{
		Send_Port[Port](1);
	}
	if (i == 10) return Send_Recognize1_Wrong; 
	for (i=0; i<37; ++i)
	{
		Send_Port[Port](1);
	}
	//结束对码 
	//开始发送 
	for (i=0; i<24; ++i)
	{
		x = S[i];
		for (;x;x--)
		{
			Send_Port[Port](0);
		}
		for (x=0;x<10; x++)
		{
			Send_Port[Port](1);
		}
	}
	//结束发送
	//再次对码，跟上次一样 
	for (i=0; i<10 && Receive_Port[Port]() == 1; ++i)
	{
		Send_Port[Port](0);
	} 
	if (i == 10)
	{
		Send_Port[Port](1);
		return Send_Recognize2_Wrong; //调试的时候去掉
	} 
	for (i=0; i<37; ++i)
	{
		Send_Port[Port](0);
	} 
	for (i=0; i<10 && Receive_Port[Port]() == 0; ++i)
	{
		Send_Port[Port](1);
	}
	if (i == 10) return Send_Recognize2_Wrong; 
	Send_Port[Port](1);
	//结束对码
	//发送完毕
	return Send_Finished;
} 
