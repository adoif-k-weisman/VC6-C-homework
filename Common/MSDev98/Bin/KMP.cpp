#include<cstdio>
int t,i,j,n,nex[1000005];char a[1000005];
int main(){
    while(scanf("%d",&n),n){
        scanf("%s",a+1);
        printf("Test case #%d\n",++t);
        for(i=2,j=0;i<=n;i++){//最基本的 next[] 数组求法
            while(j&&a[i]!=a[j+1])j=nex[j];
            if(a[i]==a[j+1])j++;nex[i]=j;
        }
		for(i=1;i<=n;i++)
				printf("%d ",nex[i]);
        for(i=2;i<=n;i++)//由于1～1只有一个字母，只能是它本身构成长度为1的循环，所以从2开始枚举
            if(i%(i-nex[i])==0&&nex[i])//判断时还要注意nex[i]是否为0
                printf("%d %d\n",i,i/(i-nex[i]));
//如果i含有长度大于1的最小循环元，输出i的长度(即i)以及最大循环次数K(即i-nex[i])
        printf("\n");//记得输出一个空行
    }
}
