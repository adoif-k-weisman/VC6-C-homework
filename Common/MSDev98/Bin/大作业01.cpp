#include<stdio.h>
void ming7an7(int m,int n);
void jiecheng(int m,int n);
void max_divisor_min_gong_bei_shu(int m,int n);
void huiwenshu(int m,int n);
void sushu(int m,int n);
void wanshu(int m,int n);
//ֻ����m��n��������m<n;
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

void ming7an7(int m,int n)//��m��n֮�����7��7��;
{
	int flag=0,x;
	printf("%d��%d֮��ġ���7��7�����У�",m,n);
	for(int i=m;i<=n;i++)
	{	x=i;
		while(x)	//�жϺ������֡�7��
		{
			if(x%10==7)
				flag=1;
			x/=10;
		}
		if(i%7==0)//�жϰ�7�������ܱ�7��������;
			flag=1;
	if(flag==1)
		printf(" %d ",i);
	flag=0;
	}
	printf("\n");
}

void jiecheng(int m,int n)//��m��n�Ľ׳�;
{
	long sum_m=1,sum_n=1;
	for(int i=1;i<=m;i++)//m�Ľ׳�
	{
		sum_m*=i;
	}
	for(i=1;i<=n;i++)//n�Ľ׳�;
	{
		sum_n*=i;
	}
	printf("%d!=%ld\t,%d!=%ld\n",m,sum_m,n,sum_n);
}

void max_divisor_min_gong_bei_shu(int m,int n)//�����Լ������С������;
{
	int i;
	for(i=m;i>=0;i--)
	{
		if(m%i==0&&n%i==0)
		{	
			printf("%d��%d֮������Լ��:%d\n",m,n,i);
			break;
		}
	}
	for(i=n;i<=m*n;i++)
	{	
		if(i%m==0&&i%n==0)
		{	printf("%d%��%d��С������:%d\n",m,n,i);
			break;
		}
	}
}

void huiwenshu(int m,int n)//�������;
{	int temp=0,x;
	printf("%d��%d֮��Ļ������У�",m,n);
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

void sushu(int m,int n)//������;
{	printf("%d��%d֮�������������",m,n);
	for(int i=m;i<=n;i++)
	{	if(i==2)//'2'������;
			printf(" 2 ");
		for(int j=2;j<i;j++)//�ж�������Ƿ��г�1��������֮�������;
		{
			if(i%j==0)
				break;
			else if(j==i-1)
				printf(" %d ",i);
		}
	}
	printf("\n");
}

void wanshu(int m,int n)//������;
{	int sum=0;//sum�����������֮��;
printf("%d��%d֮���������:",m,n);
	for(int i=m;i<=n;i++)//i��������m��n֮���������;
	{
		for(int j=1;j<i;j++)
		{
			if(i%j==0)
				sum+=j;
		}
		if(sum==i)//�ж��Ƿ�������;
			printf(" %d ",i);
		sum=0;
	}
	printf("\n");
}
