#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
/*
int main()
{
    int a1,a2,a3;
    char op1,op2,op3;
 
    //为了保证结构，在最开始加上一个0+
    a1 = 0;
    op1 = '+';
    while(op1!='=')
    {
        scanf("%d %c",&a2,&op2);    //这里用一个空格来忽略空白符
        //计算乘除
        while(op2=='*' || op2=='/')
        {
            scanf("%d %c",&a3,&op3);
            if(op2=='*')
                a2 *= a3;
            else if(op2=='/')
                a2 /= a3;
            op2 = op3;    //此处注意
        }
        //将两项相加（减）
        if(op1=='+')
            a1 += a2;
        else if(op1=='-')
            a1 -= a2;
        op1 = op2;    //此处注意
    }
 
    printf("%d",a1);
 
	return 0;
}
*/
int main()
{
    char a[10]={'1','5','2','9'};

    int len=strlen(a);//获得字符串长度
    printf("%d\n",len);
  //  int p = strchr(a,'a');
    int k=atoi(a);  //字符串转int
    printf("%c\n",a[1]-'0'); //char转int
    printf("%c\n",5+'0'); //int转char
	printf("int === %d\n",k);
    return 0;
}
