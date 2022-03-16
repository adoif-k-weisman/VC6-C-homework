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
void main()//默认一维数组；
{
	int a[N],copy[N],n,i;//copy[N]数组用于处理做顺序查找,a[N]数组做二分查找;
	srand((unsigned)time(NULL));//使每次产生的随机数不同;
	printf("输入实际处理元素的个数:");
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		a[i]=rand()%100;
		copy[i]=a[i];
	}
	printf("产生的%d个随机数:  ",n);
	for(i=0;i<n;i++)
	{
		printf(" %d ",a[i]);
	}
	printf("\n");
	printf("该数组的平均数：%.2lf\n",average(a,n));//显示所有高于平均数的数据;
	printf("该数组中所有高于平均数的数据：");
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
	printf("请输入想查找的数：");
	scanf("%d",&target);
	printf("对无序数组顺序查找的结果:\n");
	shunxu_search(copy,n,target);
	printf("========================================================\n");
	printf("对有序数组二分查找的结果:\n");
	binary_search(a,n,target);
	//对同一个数的查找效率比较，测试结果:二分法比顺序查找快，效率高;
}
void exchange(int a[],int n)//交换最大数与最小数：
{
	int temp,i;
	temp=a[max_index(a,n)];
	a[max_index(a,n)]=a[min_index(a,n)];
	a[min_index(a,n)]=temp;
	printf("最大数:%d\n",a[max_index(a,n)]);
	printf("最小数:%d\n",a[min_index(a,n)]);
	printf("交换最大数和最小数的位置后的数组:\n");
	for(i=0;i<n;i++)
	{
		printf(" %d ",a[i]);
	}
	printf("\n");

}
float average(int a[],int n)//n--数组长度
{	float sum=0;
	float aver;
	for(int i=0;i<n;i++)
	{
		sum+=a[i];	
	}
	aver= sum/n;
	return aver;
}

int  max_index(int a[],int n)//求出最大数的下标;
{
	int maxi=0;
	for(int i=0;i<=n;i++)
	{
		if(a[maxi]<a[i])
			maxi=i;	
	}
	return maxi;
}
int min_index(int a[],int n)//求出最小数的下标;
{	int mini=0;
	for(int i=0;i<n;i++)
	{
		if(a[mini]>a[i])
			mini=i;
	}
	return mini;
}

void reserve(int a[],int len)//对数组进行逆置;
{	int i,temp;
	for (i=0;i<len/2;i++)
	{
		temp=a[i];//开始交换
		a[i]=a[len-i-1];
		a[len-i-1]=temp;
	}
	printf("逆置后的数组： ");
	for(i=0;i<len;i++)
	{
		printf("%d ",a[i]);
	}
	printf("\n");
}
	
void array_sort(int a[],int n)//递增排序并显示;
{	int i,j,flag,temp;//flag用于检测排序完成，优化算法；
	for(i=0;i<n-1;i++)//冒泡排序;
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
	printf("排序后递增的数组：");
	for(i=0;i<n;i++)
	{	
		printf(" %d ",a[i]);
	}
	printf("\n");
}

void shunxu_search(int a[],int n,int target)//对无序数组顺序查找；
{
	int  i,t=0;
	int flag=0;//t表示查找次数，flag表示是否在数组中查找到该数；
	for(i=0;i<n;i++)
	{	t++;
		printf("第%d次比较，比较的数据，%d %d\n",t,a[i],target);
		if(a[i]==target)
		{	flag=1;
			break;
		}
	}
	if(flag==1)
		printf("总共比较次数：%d,查找结果：%d存在，它的下标是%d\n",t,target,i);
	else
		printf("总共比较次数：%d,查找结果：%d不在该数列中\n",t,target);
}

void binary_search(int a[],int n,int target)//对有序数组二分查找；
{
	int index=-1,t=0;//index表示找到的数的下标;
	//表示要找的数；
	int low=0,high=n-1,mid;//low表示最小的数，high表示最大的数，mid表示中间的数；
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
			printf("第%d次比较：%d<%d\n",t,a[mid],target);
		}
		else
		{	high=mid-1;
			t++;
			printf("第%d次比较：%d>%d\n",t,a[mid],target);
		}
	}
	if(index==-1)
		printf("总共比较次数：%d,查找结果：%d不在该数列中\n",t,target);
	else
		printf("总共比较次数：%d,查找结果：%d存在，它的下标是%d\n",t,target,index);
}