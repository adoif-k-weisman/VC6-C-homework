#include<stdio.h>
void ming7an7(int m,int n);
void jiecheng(int m,int n);
void max_divisor_min_gong_bei_shu(int m,int n);
void huiwenshu(int m,int n);
void sushu(int m,int n);
void wanshu(int m,int n);
//只考虑m和n是正数；m<n;
void main()
{
	int m,n;
	printf("please input m(n>m):");
	scanf("%d",&m);
	printf("input n :");
	scanf("%d",&n);
	ming7an7(m,n);
	jiecheng(m,n);
	max_divisor_min_gong_bei_shu(m,n);
	huiwenshu(m,n);
	sushu(m,n);
	wanshu(m,n);
}

void ming7an7(int m,int n)//求m、n之间的明7暗7数;
{
	int flag=0,x;
	printf("%d和%d之间的“明7暗7”数有：",m,n);
	for(int i=m;i<=n;i++)
	{	x=i;
		while(x)	//判断含有数字“7”
		{
			if(x%10==7)
				flag=1;
			x/=10;
		}
		if(i%7==0)//判断暗7数，即能被7整除的数;
			flag=1;
	if(flag==1)
		printf(" %d ",i);
	flag=0;
	}
	printf("\n");
}

void jiecheng(int m,int n)//求m、n的阶乘;
{
	long sum_m=1,sum_n=1;
	for(int i=1;i<=m;i++)//m的阶乘
	{
		sum_m*=i;
	}
	for(i=1;i<=n;i++)//n的阶乘;
	{
		sum_n*=i;
	}
	printf("%d!=%ld\t,%d!=%ld\n",m,sum_m,n,sum_n);
}

void max_divisor_min_gong_bei_shu(int m,int n)//求最大公约数，最小公倍数;
{
	int i;
	for(i=m;i>=0;i--)
	{
		if(m%i==0&&n%i==0)
		{	
			printf("%d和%d之间的最大公约数:%d\n",m,n,i);
			break;
		}
	}
	for(i=n;i<=m*n;i++)
	{	
		if(i%m==0&&i%n==0)
		{	printf("%d%和%d最小公倍数:%d\n",m,n,i);
			break;
		}
	}
}

void huiwenshu(int m,int n)//求回文数;
{	int temp=0,x;
	printf("%d和%d之间的回文数有：",m,n);
	for(int i=m;i<=n;i++)
	{	x=i;
		while(x)
		{temp=temp*10+x%10;
			x=x/10;
		};
		if(temp==i)
			printf(" %d ",i);
		temp=0;
	}
	printf("\n");
}

void sushu(int m,int n)//求素数;
{	printf("%d和%d之间的所有素数：",m,n);
	for(int i=m;i<=n;i++)
	{	if(i==2)//'2'是素数;
			printf(" 2 ");
		for(int j=2;j<i;j++)//判断这个数是否有除1和它本身之外的因数;
		{
			if(i%j==0)
				break;
			else if(j==i-1)
				printf(" %d ",i);
		}
	}
	printf("\n");
}

void wanshu(int m,int n)//求完数;
{	int sum=0;//sum用来存放因数之和;
printf("%d和%d之间的完数有:",m,n);
	for(int i=m;i<=n;i++)//i用来遍历m、n之间的所有数;
	{
		for(int j=1;j<i;j++)
		{
			if(i%j==0)
				sum+=j;
		}
		if(sum==i)//判断是否是完数;
			printf(" %d ",i);
		sum=0;
	}
	printf("\n");
}
