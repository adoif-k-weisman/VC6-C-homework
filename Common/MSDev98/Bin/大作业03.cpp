//Ӣ���ı��ļ�,Ӣ��������ĸ�����֡������ַ����޺��֣��ļ��ж��С�ֻ��"r"����
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void count_letter(char str[]);
void count_words(char str[]);
void long_word(char str[]);
void count_num(char str[]);
void main()
{
	FILE *fp;
	char str[1000]={'\0'},ch;//str[1000]�������ڴ�����ļ��ж�ȡ������;
	char filename[20];
	int i=0;
	printf("��������ļ������֣�");
	scanf("%s",filename);
	if((fp=fopen(filename,"r"))==NULL)//���ļ�;
	{
		printf("Error,cannot open the file!\n");
		exit(0);
	}
	while(!feof(fp))//���ı�����str������;
	{
		ch=fgetc(fp);
		str[i]=ch;
		i++;
		putchar(ch);
	}
	fclose(fp);
	printf("\n--------------  \n");
	count_letter(str);
	count_words(str);
	long_word(str);
	count_num(str);
}

void count_letter(char str[])//Ĭ��������ĸ��Сд��
{
	char letter[26];//����Ӣ��26��С��ĸ
	int i=0,count=0;//count--ͳ����ĸƵ��;
	for(;i<26;i++)//����26����ĸ���ֵ�����letter������;
	{	letter[i]='a'+i;
	}
	printf("��ĸ����Ƶ����\n");
	for(i=0;i<26;i++)//ͳ��Сд��ĸ��
	{
		for(int j=0;str[j]!='\0';j++)
		{
			if(str[j]==letter[i])
				count++;
		}
		if(count!=0)//���ͳ�Ƶ�Сд��ĸ;
		{	printf("'%c': %d\n",letter[i],count);
			count=0;
		}
	}
	for(i=0;i<26;i++)//��ͳ����Сд��ĸ�󣬲���Ӣ��26����д��ĸ�����letter�У�
	{
		letter[i]='A'+i;
	}
	for(i=0;i<26;i++)//ͳ�ƴ�д��ĸ��
	{
		for(int j=0;str[j]!='\0';j++)
		{
			if(str[j]==letter[i])
				count++;
		}
		if(count!=0)//���ͳ�ƵĴ�д��ĸ
		{	printf(" %c : %d\n",letter[i],count);
			count=0;
		}
	}
}

// ͳ�����е��ʵĸ���������ʾ���;
void count_words(char str[])
{
	int sum=0,i=0,word=0;//sum--�ܵĵ�������word--�ж�����;
	for(;str[i]!='\0';i++)
	{
		
		if(!((str[i]>='a'&&str[i]<='z')||(str[i]>='A'&&str[i]<='Z')))
			word=0;
		else if((word==0)&&(('A'<=str[i]&&str[i]<='Z')||('a'<=str[i]&&str[i]<='z')))
		{	word=1;
			sum++;
		}
	}
	printf("���ļ��еĵ�����: %d\n",sum);
}

void long_word(char str[])//ͳ����ĵ��ʣ�
{
	int currLen=0,maxLen=0,currStart=0,MaxStart=0;//maxlen--���ʳ���,currStart--���ʿ�ʼ���±꣬maxStart--��ĵ��ʿ�ʼ���±�;
    int i=0,j=0;
    for(i=0;str[i]!='\0';i++)
    {
        if((str[i]>='a'&&str[i]<='z')||(str[i]>='A'&&str[i]<='Z'))
        {
            if(currLen==0)//��ǰ���ȵ���0ʱ��˵��һ�����ʸող����ꣻ
                currStart=i;//�µ��ʵĿ�ʼλ�ã�
            currLen++;
        }
        if(currLen>maxLen)//��ǰ���ʵĳ��ȴ������ֵ�����и�ֵ��
        {
            maxLen=currLen;
            MaxStart=currStart;
        }
     //��������ĸ����һ�������Ѿ�������
		if(!((str[i]>='a'&&str[i]<='z')||(str[i]>='A'&&str[i]<='Z')))
		{
            currLen=0;
        }
    }
	printf("��ĵ����ǣ�");
    for(j=MaxStart;j<MaxStart+maxLen;j++)
        printf("%c",str[j]);
	printf(" ,���ʵĳ��ȣ�%d",maxLen);
	printf("\n");
}

void count_num(char str[])//ͳ�Ƴ��ֵ�������
{
	int a[100]={0};
	int temp=0,j=0;
	printf("�ı��г��ֵ�������\n");
	for(int i=0;str[i]!='\0';i++)
	{
		if('0'<=str[i]&&str[i]<='9')
		{
			temp=temp*10+(str[i]-'0');//�����ִ�char��װ��Ϊint��;
			if(!('0'<=str[i+1]&&str[i+1]<='9'))//�ж�һ�����ֶ�ȡ��󣬽������a[100]�����в����;
			{	a[j]=temp;
				printf(" %d,",a[j]);
				j++;
				temp=0;
			}
		}
	}
	printf("\b \n");
	
}