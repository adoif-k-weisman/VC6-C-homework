#include<iostream>
using namespace std;
int max_array(int &line,int &column,int a[][4]);
/*
int main()
{
	int a[3][4]={11,23,45,6,7,89,1,2,45,67,7,8};
	int line=0;
	int column=0;
	int max=max_array(line,column,a);
	cout<<"数组最大的数是:"<<max<<endl;
	cout<<"最大的数的行数是"<<line<<endl;
	cout<<"最大的数的列数是"<<column<<endl;
	return 0;
}
*/
int  max_array(int &line,int &column,int a[3][4])
{	
	int i,j;
	int max=a[0][0];
	line=0,column=0;
	for( i=0;i<2;i++)
	{	for( j=0;j<3;j++)
		{	
			if(max<a[i][j])
			{	line=i;
				column=j;
			}
		}

	}
	return a[line][column];
}
/*
int main()
{
	char goodman;
	for(goodman='A';goodman<='D';goodman++)
	{
		if((goodman!='A')+(goodman=='C')+(goodman=='D')+(goodman!='D')==3)
			cout<<"做好事的人是"<<goodman<<endl;
	}
	return 0;
}
*/

void calc_number(int num,int a[]);
int main()
{	int a[10]={0};
	int num;
	cout<<"请输入一个数字:";
	cin>>num;
	calc_number(num,a);
	for(int i=0;i<10;i++)
	{
		cout<<"数字"<<i<<"的个数：";
		cout<<a[i]<<endl;
	}
	return 0;
}

void calc_number(int num,int a[])
{	int b[10]={0,1,2,3,4,5,6,7,8,9};
	int temp=0;
	while(num>0){
		temp=num%10;
		switch(temp)
		{	cout<<"temp="<<temp<<endl;
			case 0:a[0]++;break;
			case 1:a[1]++;break;
			case 2:a[2]++;break;
			case 3:a[3]++;break;
			case 4:a[4]++;break;
			case 5:a[5]++;break;
			case 6:a[6]++;break;
			case 7:a[7]++;break;
			case 8:a[8]++;break;
			case 9:a[9]++;break;
			default:cout<<"wrong number!!!"<<endl;
		}
		num/=10;
	}
}


