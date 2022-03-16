#include<string.h>
#include<stdio.h>
#define MAX 100
int num[MAX];
char exp[MAX]={'\0'};
void get_exp(char str[]);
void get_num(char str[]);
void main()
{	char str[MAX];
	int i=0;
	double a1=0,a2=0,a3=0;
	char op1='+',op2,op3;
	printf("请输入待计算的表达式：");
	gets(str);
	get_num(str);
	get_exp(str);	
	while(op1!='=')
	{
		a2=num[i];
		op2=exp[i];
		while(op2=='/'||op2=='*')
		{	a3=num[i+1];
			op3=exp[i+1];
			if(op2=='*')
				a2*=a3;
			if(op2=='/')
				a2/=a3;
			op2=op3;
			i++;
		}
		if(op1=='+')
			a1+=a2;
		else if(op1=='-')
			a1-=a2;
		op1=op2;
		++i;
		
	}
	printf("==========answer=%.2lf\n",a1);

}
void get_answer()
{

}
void get_num(char str[])//获得字符串表达式中的数字;
{	int temp=0;
	int i,t=0;
	for(i=0;str[i]!='\0';i++)
	{
		if('0'<=str[i]&&str[i]<='9')
		{	temp=temp*10+str[i]-'0';
			if(!('0'<=str[i+1]&&str[i+1]<='9'))
			{	num[t]=temp;
				t++;
				temp=0;
			}
		}
	}
}

void get_exp(char str[])//获得字符串中的运算符号;
{	int t=0,i;
	for(i=0;str[i]!='\0';i++)
	{
		if(str[i]=='*'||str[i]=='/'||str[i]=='+'||str[i]=='-')
		{
			exp[t]=str[i];
			t++;
		}
	}
	exp[t]='=';//'='用于运算完毕的终止符;
}