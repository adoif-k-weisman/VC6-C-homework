//英文文本文件,英文中有字母、数字、其它字符，无汉字，文件有多行。只用"r"功能
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
	char str[1000]={'\0'},ch;//str[1000]数组用于储存从文件中读取的内容;
	char filename[20];
	int i=0;
	printf("请输入打开文件的名字：");
	scanf("%s",filename);
	if((fp=fopen(filename,"r"))==NULL)//打开文件;
	{
		printf("Error,cannot open the file!\n");
		exit(0);
	}
	while(!feof(fp))//将文本读入str数组中;
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

void count_letter(char str[])//默认区分字母大小写；
{
	char letter[26];//储存英文26个小字母
	int i=0,count=0;//count--统计字母频数;
	for(;i<26;i++)//产生26个字母的字典存放在letter数组中;
	{	letter[i]='a'+i;
	}
	printf("字母出现频数：\n");
	for(i=0;i<26;i++)//统计小写字母；
	{
		for(int j=0;str[j]!='\0';j++)
		{
			if(str[j]==letter[i])
				count++;
		}
		if(count!=0)//输出统计的小写字母;
		{	printf("'%c': %d\n",letter[i],count);
			count=0;
		}
	}
	for(i=0;i<26;i++)//在统计完小写字母后，产生英文26个大写字母存放在letter中；
	{
		letter[i]='A'+i;
	}
	for(i=0;i<26;i++)//统计大写字母；
	{
		for(int j=0;str[j]!='\0';j++)
		{
			if(str[j]==letter[i])
				count++;
		}
		if(count!=0)//输出统计的大写字母
		{	printf(" %c : %d\n",letter[i],count);
			count=0;
		}
	}
}

// 统计其中单词的个数，并显示结果;
void count_words(char str[])
{
	int sum=0,i=0,word=0;//sum--总的单词数，word--判断条件;
	for(;str[i]!='\0';i++)
	{
		
		if(!((str[i]>='a'&&str[i]<='z')||(str[i]>='A'&&str[i]<='Z')))
			word=0;
		else if((word==0)&&(('A'<=str[i]&&str[i]<='Z')||('a'<=str[i]&&str[i]<='z')))
		{	word=1;
			sum++;
		}
	}
	printf("该文件中的单词数: %d\n",sum);
}

void long_word(char str[])//统计最长的单词；
{
	int currLen=0,maxLen=0,currStart=0,MaxStart=0;//maxlen--单词长度,currStart--单词开始的下标，maxStart--最长的单词开始的下标;
    int i=0,j=0;
    for(i=0;str[i]!='\0';i++)
    {
        if((str[i]>='a'&&str[i]<='z')||(str[i]>='A'&&str[i]<='Z'))
        {
            if(currLen==0)//当前长度等于0时，说明一个单词刚刚查找完；
                currStart=i;//新单词的开始位置；
            currLen++;
        }
        if(currLen>maxLen)//当前单词的长度大于最大值，进行赋值；
        {
            maxLen=currLen;
            MaxStart=currStart;
        }
     //遇到非字母，即一个单词已经结束。
		if(!((str[i]>='a'&&str[i]<='z')||(str[i]>='A'&&str[i]<='Z')))
		{
            currLen=0;
        }
    }
	printf("最长的单词是：");
    for(j=MaxStart;j<MaxStart+maxLen;j++)
        printf("%c",str[j]);
	printf(" ,单词的长度：%d",maxLen);
	printf("\n");
}

void count_num(char str[])//统计出现的整数；
{
	int a[100]={0};
	int temp=0,j=0;
	printf("文本中出现的整数：\n");
	for(int i=0;str[i]!='\0';i++)
	{
		if('0'<=str[i]&&str[i]<='9')
		{
			temp=temp*10+(str[i]-'0');//将数字从char型装换为int型;
			if(!('0'<=str[i+1]&&str[i+1]<='9'))//判断一个数字读取完后，将其存在a[100]数组中并输出;
			{	a[j]=temp;
				printf(" %d,",a[j]);
				j++;
				temp=0;
			}
		}
	}
	printf("\b \n");
	
}