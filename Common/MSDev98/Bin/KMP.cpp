#include<cstdio>
int t,i,j,n,nex[1000005];char a[1000005];
int main(){
    while(scanf("%d",&n),n){
        scanf("%s",a+1);
        printf("Test case #%d\n",++t);
        for(i=2,j=0;i<=n;i++){//������� next[] ������
            while(j&&a[i]!=a[j+1])j=nex[j];
            if(a[i]==a[j+1])j++;nex[i]=j;
        }
		for(i=1;i<=n;i++)
				printf("%d ",nex[i]);
        for(i=2;i<=n;i++)//����1��1ֻ��һ����ĸ��ֻ�����������ɳ���Ϊ1��ѭ�������Դ�2��ʼö��
            if(i%(i-nex[i])==0&&nex[i])//�ж�ʱ��Ҫע��nex[i]�Ƿ�Ϊ0
                printf("%d %d\n",i,i/(i-nex[i]));
//���i���г��ȴ���1����Сѭ��Ԫ�����i�ĳ���(��i)�Լ����ѭ������K(��i-nex[i])
        printf("\n");//�ǵ����һ������
    }
}
