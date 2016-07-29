sbit A1 = P1^0;
sbit B2 = P3^7;
sbit A3 = P3^4;
sbit B3 = P3^6;
sbit A4 = P3^2;
sbit B4 = P3^5;
sbit A5 = P1^6;
sbit B5 = P3^3;
sbit A6 = P1^4;
sbit B6 = P1^7;
sbit A7 = P1^1;
sbit B7 = P1^5;
sbit A8 = P1^2;
sbit B8 = P1^3;
void ClearLink()
{
	A1=0;
	//A2=0;
	A3=0;
	A4=0;
	A5=0;
	A6=0;
	A7=0;
	A8=0;
	//B1=0;
	B2=0;
	B3=0;
	B4=0;
	B5=0;
	B6=0;
	B7=0;
	B8=0;
}
void ALinkTo(char x)
{
	A1 = 0;
	A3 = 0;
	A4 = 0;
	A5 = 0;
	A6 = 0;
	A7 = 0;
	A8 = 0;	
	switch (x)
	{
		case 1:
			A1 = 1;
			break;
		case 3:
			A3 = 1;
			break;
		case 4:
			A4 = 1;
			break;
		case 5:
			A5 = 1;
			break;
		case 6:
			A6 = 1;
			break;
		case 7:
			A7 = 1;
			break;
		case 8:
			A8 = 1;
			break;
	}
}
void BLinkTo(char x)
{
	B2 = 0;
	B3 = 0;
	B4 = 0;
	B5 = 0;
	B6 = 0;
	B7 = 0;
	B8 = 0;
	switch (x)
	{
		case 2:
			B2 = 1;
			break;
		case 3:
			B3 = 1;
			break;
		case 4:
			B4 = 1;
			break;
		case 5:
			B5 = 1;
			break;
		case 6:
			B6 = 1;
			break;
		case 7:
			B7 = 1;
			break;
		case 8:
			B8 = 1;
			break;
	}
}
void Link(char a,char b)
{
	if (a==1)
	{
		ALinkTo(1);
		BLinkTo(b);
	}
	else if (b==1)
	{
		ALinkTo(1);
		BLinkTo(a);
	}
	else if (a==2)
	{
		ALinkTo(b);
		BLinkTo(2);
	}
	else if (b==2)
	{
		ALinkTo(a);
		BLinkTo(2);
	}
	else 
	{
		ALinkTo(a);
		BLinkTo(b); 
	}
} 
