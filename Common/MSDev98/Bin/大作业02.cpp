#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define N 40
float average(int a[],int n);
int  max_index(int a[],int n);
int min_index(int a[],int n);
void array_sort(int a[],int n);
void shunxu_search(int a[],int n,int target);
void binary_search(int a[],int n,int target);
void exchange(int a[],int n);
void reserve(int a[],int len);
void main()//Ĭ��һά���飻
{
	int a[N],copy[N],n,i;//copy[N]�������ڴ�����˳�����,a[N]���������ֲ���;
	srand((unsigned)time(NULL));//ʹÿ�β������������ͬ;
	printf("����ʵ�ʴ���Ԫ�صĸ���:");
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		a[i]=rand()%100;
		copy[i]=a[i];
	}
	printf("������%d�������:  ",n);
	for(i=0;i<n;i++)
	{
		printf(" %d ",a[i]);
	}
	printf("\n");
	printf("�������ƽ������%.2lf\n",average(a,n));//��ʾ���и���ƽ����������;
	printf("�����������и���ƽ���������ݣ�");
	for(i=0;i<n;i++)
	{
		if(a[i]>average(a,n))
			printf(" %d ",a[i]);
	}
	printf("\n");

	exchange(a,n);

	reserve(a,n);

	array_sort(a,n);

	int target;
	printf("����������ҵ�����");
	scanf("%d",&target);
	printf("����������˳����ҵĽ��:\n");
	shunxu_search(copy,n,target);
	printf("========================================================\n");
	printf("������������ֲ��ҵĽ��:\n");
	binary_search(a,n,target);
	//��ͬһ�����Ĳ���Ч�ʱȽϣ����Խ��:���ַ���˳����ҿ죬Ч�ʸ�;
}
void exchange(int a[],int n)//�������������С����
{
	int temp,i;
	temp=a[max_index(a,n)];
	a[max_index(a,n)]=a[min_index(a,n)];
	a[min_index(a,n)]=temp;
	printf("�����:%d\n",a[max_index(a,n)]);
	printf("��С��:%d\n",a[min_index(a,n)]);
	printf("�������������С����λ�ú������:\n");
	for(i=0;i<n;i++)
	{
		printf(" %d ",a[i]);
	}
	printf("\n");

}
float average(int a[],int n)//n--���鳤��
{	float sum=0;
	float aver;
	for(int i=0;i<n;i++)
	{
		sum+=a[i];	
	}
	aver= sum/n;
	return aver;
}

int  max_index(int a[],int n)//�����������±�;
{
	int maxi=0;
	for(int i=0;i<=n;i++)
	{
		if(a[maxi]<a[i])
			maxi=i;	
	}
	return maxi;
}
int min_index(int a[],int n)//�����С�����±�;
{	int mini=0;
	for(int i=0;i<n;i++)
	{
		if(a[mini]>a[i])
			mini=i;
	}
	return mini;
}

void reserve(int a[],int len)//�������������;
{	int i,temp;
	for (i=0;i<len/2;i++)
	{
		temp=a[i];//��ʼ����
		a[i]=a[len-i-1];
		a[len-i-1]=temp;
	}
	printf("���ú�����飺 ");
	for(i=0;i<len;i++)
	{
		printf("%d ",a[i]);
	}
	printf("\n");
}
	
void array_sort(int a[],int n)//����������ʾ;
{	int i,j,flag,temp;//flag���ڼ��������ɣ��Ż��㷨��
	for(i=0;i<n-1;i++)//ð������;
	{	
		flag=0;
		for(j=0;j<n-i-1;j++)
		{
			if(a[j]>a[j+1])
			{	flag=1;
				temp=a[j+1];
				a[j+1]=a[j];
				a[j]=temp;
			}
		}
		if(!flag)	break;
	}
	printf("�������������飺");
	for(i=0;i<n;i++)
	{	
		printf(" %d ",a[i]);
	}
	printf("\n");
}

void shunxu_search(int a[],int n,int target)//����������˳����ң�
{
	int  i,t=0;
	int flag=0;//t��ʾ���Ҵ�����flag��ʾ�Ƿ��������в��ҵ�������
	for(i=0;i<n;i++)
	{	t++;
		printf("��%d�αȽϣ��Ƚϵ����ݣ�%d %d\n",t,a[i],target);
		if(a[i]==target)
		{	flag=1;
			break;
		}
	}
	if(flag==1)
		printf("�ܹ��Ƚϴ�����%d,���ҽ����%d���ڣ������±���%d\n",t,target,i);
	else
		printf("�ܹ��Ƚϴ�����%d,���ҽ����%d���ڸ�������\n",t,target);
}

void binary_search(int a[],int n,int target)//������������ֲ��ң�
{
	int index=-1,t=0;//index��ʾ�ҵ��������±�;
	//��ʾҪ�ҵ�����
	int low=0,high=n-1,mid;//low��ʾ��С������high��ʾ��������mid��ʾ�м������
	while(low<=high)
	{	mid=(high+low)/2;
		if(a[mid]==target)
		{	index=mid;
			t++;
			break;
		}
		else if(a[mid]<target)
		{	low=mid+1;
			t++;
			printf("��%d�αȽϣ�%d<%d\n",t,a[mid],target);
		}
		else
		{	high=mid-1;
			t++;
			printf("��%d�αȽϣ�%d>%d\n",t,a[mid],target);
		}
	}
	if(index==-1)
		printf("�ܹ��Ƚϴ�����%d,���ҽ����%d���ڸ�������\n",t,target);
	else
		printf("�ܹ��Ƚϴ�����%d,���ҽ����%d���ڣ������±���%d\n",t,target,index);
}