#include"stdafx.h"
#include<stdio.h>
#include<string.h>

int main(int argc,char* argv[])
{
	char s[10];
	strcpy(s,"1234567");
	printf("%ld %x\n",*(long*)(s+2),*(long*)(s+2));
	printf("%d %x\n",*(short*)(s+2),*(short*)(s+2));
	printf("%d\n",*(char *)(s+2));
	*(int*)(s+1) = 16706;
	printf("%s\n",s);

	return 0;
}