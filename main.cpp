#include <iostream.h>
#include "math.h"

#define PI 3.14159
#define NN 2048

struct complex                                                 //data form                 
{
	float Re;
	float Im;
};

void FFT(complex x[],complex y[],int N);     
void MAG();            

char mode = 0;

int i,N;
complex x[NN],y[NN];
double z[NN];

void main()
{
	int i,N;
	cout<<"Complex Mode? (1 or 0)"<<endl;
	cin>>mode;
	cout<<"N=? (2,4,8,16...)"<<endl;
	cin>>N;
	cout<<"Data?"<<endl;
	
		for(i=0;i<N;i++)										//input
		{
			cout<<"Re("<<i<<"):";
			cin>>x[i].Re;
			if(mode == 1)
			{
				cout<<"Im("<<i<<"):";
				cin>>x[i].Im;
			}
			else
				x[i].Im = 0;
		}
		FFT(x,y,N);
		for(i=0;i<N;i++)
			cout<<"X["<<i<<"] -> "<<x[i].Re<<"+"<<x[i].Im<<"i"<<endl;
		MAG();
		for(i=0;i<N;i++)
			cout<<z[i]<<"\t";
		cout<<endl;
}

void FFT(complex x[],complex y[],int N)						//FFT
{
	int i,j,k,m=0;
	int p,q,s;
	double angle;
	complex W;
	complex c[NN];

	for(i=0,j=0;i<N-1;i++)		
	{
		if(i<j)
		{
			c[i]=x[i];
			x[i]=x[j];
			x[j]=c[i];
		}
		k=N/2;
		while(k<=j)
		{
			j=j-k;
			k=k/2;
		}
		j=j+k;
	}
	
	for(m=0;m<(log(N)/log(2));m++)    
	{
		for(k=0;k<pow(2,((log(N)/log(2))-m-1));k++) 
		{
			for(s=0;s<pow(2,m);s++) 
			{
				p=k*int(pow(2,m+1))+s;
				angle=-PI*2*s*pow(2,((log(N)/log(2))-m-1))/N;
				W.Re=float (cos(angle));
				W.Im=float (sin(angle));
				q=p+int(pow(2,m));
				y[p].Re=x[p].Re+W.Re*x[q].Re-x[q].Im*W.Im;
				y[p].Im=x[p].Im+W.Im*x[q].Re+x[q].Im*W.Re;
				y[q].Re=x[p].Re-(W.Re*x[q].Re-x[q].Im*W.Im);
				y[q].Im=x[p].Im-(W.Im*x[q].Re+x[q].Im*W.Re);
			}
		}
		for(i=0;i<N;i++)
			x[i]=y[i];
	}

}


void MAG()
{
	int n;
	for(n=0;n<=N-1;n++)
	{
		z[n]=sqrt((x[n].Re)*(x[n].Re)+(x[n].Im)*(x[n].Im));
	}
}