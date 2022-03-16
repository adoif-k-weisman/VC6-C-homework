#include<stdio.h>
#include<stdlib.h>
/*
void main()
{
	char str[5]={1,2,3,' ',5};
	int i=0,temp=0;
	for(;str[i]!='\0';i++)
	{
		while(str[i]!=' ')
		{	if(0<=str[i]<=9)
			{	//str[i]=str[i]+'0';
				temp=temp*10+str[i];}
		}
	}
	printf("temp=%d\n",temp);
}
*/
void main()
{
	FILE *fp;
	char str[100],ch;
	int i=0,a[100],temp=0;
	if((fp=fopen("1.txt","r"))==NULL)
	{
		printf("cannot open the file\n");
		exit(0);
	}
	while(!feof(fp)){
		ch=fgetc(fp);
		str[i]=ch;
		i++;
	
	}
	printf("%d\n",str[0]);
	fclose(fp);
	for(;str[i]!='\0';i++)
	{
		while(str[i]!=' ')
		{	if('0'<=str[i]<='9')
			{	//str[i]=str[i]+'0';
				temp=temp*10+str[i]-'0';}
		}
	}
	printf("---%d\n",str[0]-'0');
	printf("temp=%d\n",temp);
}