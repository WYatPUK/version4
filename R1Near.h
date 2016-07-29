//需要设置large data 使数据存到xdata里 
unsigned char p0;//内部变量
unsigned char p2;//内部变量
double ratio0;//外部
double ratio;//临时变量
const unsigned int Resistance[82] = {3968, 4224, 4544, 4928, 5248, 5824, 6208, 6400, 9600, 10368, 11264, 11712, 12416, 15872, 17088, 17600, 18688, 19200, 19712, 20480, 21120, 23360, 24192, 26304, 27328, 28672, 30080, 39680, 42240, 45440, 49280, 52480, 58240, 62080, 64000, 9601, 10369, 11265, 11713, 12417, 15873, 17089, 17601, 18689, 19201, 19713, 20481, 21121, 23361, 24193, 26305, 27329, 28673, 30081, 39681, 42241, 45441, 49281, 52481, 58241, 62081, 64001, 9602, 10370, 11266, 11714, 12418, 15874, 17602, 18690, 19202, 19714, 20482, 21122, 23362, 24194, 26306, 27330, 30082, 64002, 64003, 64004};
const unsigned char ResistanceP0[82] = {15, 7, 11, 3, 5, 9, 17, 1, 62, 14, 54, 22, 6, 10, 124, 60, 28, 18, 34, 12, 2, 116, 52, 6, 36, 68, 4, 120, 56, 88, 24, 40, 72, 8, 8, 112, 112, 48, 48, 48, 80, 96, 96, 96, 16, 16, 96, 16, 32, 32, 32, 32, 32, 32, 64, 64, 64, 64, 64, 64, 64, 64, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
const unsigned char ResistanceP2[82] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 6, 0, 6, 2, 0, 0, 14, 6, 2, 2, 4, 0, 0, 14, 6, 2, 4, 8, 0, 14, 6, 10, 2, 4, 8, 16, 0, 62, 14, 54, 22, 6, 10, 60, 28, 18, 34, 12, 2, 116, 52, 20, 36, 4, 8, 64, 128};

void GetRatio(unsigned int Num, unsigned int Num0, unsigned int Dec, unsigned int Dec0)
{
	int i;
	ratio = ((double)Num/Num0);
	for (i=0; i<(Dec - Dec0); ++i)
		ratio *= 10;
	return ;
}
int IfNearChange (const unsigned int x0)
{
	unsigned int Num0 = (x0>>6);
	unsigned int Dec0 = x0 & 0x3f;
	unsigned int Num = (x>>6);
	unsigned int Dec = x & 0x3f;
	if (Dec > Dec0)
		GetRatio(Num, Num0, Dec, Dec0); 
	else if (Dec == Dec0)
	{
		if (Num>Num0)
			GetRatio(Num, Num0, 0, 0);
		else 
			GetRatio(Num0, Num, 0, 0); 
	} 
	else 
		GetRatio(Num0, Num, Dec0, Dec);	
	if (ratio < ratio0)
	{
		ratio0 = ratio;
		R = x0;
		return 1;
	}
	return 0;
}
void OnlyFindNearSet()
{
	int i;
	for (i=0; i<82; ++i)
	{
		if ( IfNearChange ( Resistance[i] ) )
		{
			p0 = ResistanceP0[i];
			p2 = ResistanceP2[i];
		}
	}
}
void DoNearSet ()
{
	P2 = p2;
	P0 = p0;
}