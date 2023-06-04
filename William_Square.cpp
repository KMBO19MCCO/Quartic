#include <iostream>
#include <cmath>
#include <conio.h>

#define eps 1e-15
using namespace std;

double c0,c1,c2,c3,c4,c5;
double p;

double FUN(double x)
{
	return c0+x*(c1+x*(c2+x*(c3+x*(c4+x*(c5+x)))));
}

void QDRTC(double b, double c)
{
	double d = b*b-4*c;
	double r;
	if (d < 0) 
	{
		// отрицательный детерминант - комплексные корни
		cout<<"Complex roots are "<< -b/2<<" +/- "<<sqrt(-d)/2<<"i"<<endl;		
	}
	else
	{
		// положительный детерминант - вешественные корни
		d = sqrt(d);
		if (b>0) r = -(b+d) / 2;
		else 	r = (d-b) / 2;
		cout << "Real roots are "<< r << " & " << c/r << endl;
	}
}

double REFINE(double vl, double vr)
{
	double xl = vl;
	double xr = vr;
	double p;
	double fp;
	while (1)
	{		
		p = xl+(xr-xl)/2;
		fp=FUN(p);
		if (abs(p-xl)<=eps || abs(fp)<=eps) return p;
		//if (p==xl || fp==0) return p;
		if (fp > 0) xr=p;
		else xl=p;
	}
		
}
int QUART(double a0, double a1, double a2, double a3)
{
	double s;
	double bd = 0;
	c0 = pow(a0,3);
	if (c0<bd) bd = c0;
	c1=-a2*a0*a0;
	if (c1 <bd) bd = c1;
	c2 = a0*(a1*a3-a0);
	if (c2 <bd) bd = c2;
	c3 = -a0*(a3*a3-2*a2)-a1*a1;
	if (c3<bd) bd = c3;
	c4 = a1*a3-a0;
	if (c4<bd) bd = c4;
	c5 = -a2;
	if (c5<bd) bd = c5;

	bd = 1- bd;
	
	if (a0 > 0)
	{
		// scase
		p = sqrt(a0);
		if (abs(FUN(p))<=eps)
		{
			// lim
			s = sqrt(a3*a3 - 4*a2 + 8*p);
			QDRTC((a3+s)/2,p);
			QDRTC((a3-s)/2,p);
			cout<<"---------1"<<endl;
			return 0;		
		}
		else
		p = REFINE(p,bd);
	}
	else p = REFINE(0,bd);
	
	// metka cd
	double den = p*p-a0;
	if (abs(den) <= eps)
	{
		// lim
		s = sqrt(a3*a3 - 4*a2 + 8*p);
		QDRTC((a3+s)/2, p);
		QDRTC((a3-s)/2, p);	
		cout<<"---------2"<<endl;		
		return 0;		
	}
	
	QDRTC((a1*p-a3*a0)/den, a0/p);
	QDRTC(p*(a3*p-a1)/den, p);
	cout<<"---------3"<<endl;
	return 0;		
}

int main()
{	
	double a0 = 4;
	double a1 = 2;
	double a2 = 3;
	double a3 = 1;

	QUART(a3,a2,a1,a0);	
	_getch();
}
