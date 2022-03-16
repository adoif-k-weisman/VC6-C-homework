#include<iostream>
#include<cmath>
using namespace std;
void sort(int a[],int n);
void output_array(int a[],int n);
int* random(int n,int max);
int* merge(int x[],int y[],int m,int n);

int main()
{
	
	int *x,*y,*z;
	int n=20,m=10;
	x=random(m,100);
	y=random(n,100);
	sort(x,m);
	sort(y,n);
	cout<<"x数组";
	output_array(x,m);
	cout<<"y数组";
	output_array(y,n);
	z=merge(x,y,m,n);
	cout<<"z数组";
	output_array(z,m+n);
	delete []x;
	delete []y;
	delete []z;
	return 0;

}
//从小到大排序;
void sort(int a[],int n)
{	
	int temp;
	for(int i=0;i<n-1;i++)
	{	
		for(int j=0;j<n-i-1;j++)
		{
			if(a[j]>a[j+1])
			{
				temp=a[j];
				a[j]=a[j+1];
				a[j+1]=temp;
			}
		}
	}
}

void output_array(int a[],int n)
{	
	cout<<"从小到大排序后的数组: ";
	for(int i=0;i<n;i++)
	{
		cout<<a[i]<<",";
	}
	cout<<endl;
}
int* random(int n,int max)
{	int *a=new int[n];
//	srand((unsigned)time(NULL));
	for(int i=0;i<n;i++)
	{
		a[i]=rand()%max;
	}
	
	return a;
}

int* merge(int x[],int y[],int m,int n)
{
	int i=0,j=0,k=0;
	int *z=new int[m+n];
	while(i!=m&&j!=n)
	{
		if(x[i]<y[j])
		{
			z[k]=x[i];
			k++;
			i++;
		}
		else if(x[i]>y[j])
		{
			z[k]=y[j];
			k++;
			j++;
		}
		else//x[i]=y[j];
		{
			z[k]=x[i];
			i++;
			k++;
			z[k]=y[j];
			j++;
			k++;
		}
	}
	if(i==m)//x数组先排序完成;
	{
		for(;j<n;j++,k++)
			z[k]=y[j];
			
	}
	if(j==n)//y数组先排完;
	{
		for(;i<m;i++,k++)
			z[k]=x[i];
	}
	return z;
}
