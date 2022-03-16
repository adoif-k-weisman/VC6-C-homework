#include<stdio.h>
#include<stdlib.h>
void save();
#define MAX 100	//定义商品数量的种类，方便用户增加、减少实际商品数量;
#define result_num 5//积分损失最小的前五种组合；
#define tot_sp 10
int result_index=0;//表示目前存放结果的数组的下标；
int results[result_num][MAX+1];//results[][]数组存放购买商品的数量，最后一个元素存放剩余积分；
int temp_result[MAX];//存放临时方案购买商品的数量;
//int tot_sp=10;//总的实际的商品种类;
int best_results = 0;
int expect_remain = 0;
struct stru_sp
{
	char name[256];
	int value;
};
stru_sp splist[MAX]={//储存商品信息,商品清单;
	{"李宁双肩包",8200},
	{"新款毛巾",683},
	{"金吉星软包抽纸",1040},
	{"2018洗车大毛巾",1250},
	{"小米(MI) 10000毫安 新移动电源2",7900},
	{"乐扣乐扣(LOCK&LOCK) 不锈钢保温杯",8690},
	{"滋润型护肤脂41.5g（大号冷霜）",710},
	{"Kans韩束 芦荟胶",1905},
	{"维达(Vinda) 手帕纸",2090},
	{"佳洁士",394}
};
void update_result(int now_sp_index,int now_creadit,int result_index);
void deal_sp(int now_creadit,int now_sp_index);
void sort();
void save();
void main()
{
	int m;
	printf("所有的商品：\n");
	for(int i=0;i<tot_sp;i++)//打印所有的商品;
	{	printf("%-40s\t%-5d\n",splist[i].name,splist[i].value);
	}
	printf("总共的商品数：%d\n",tot_sp);
	printf("====================================================\n");
	printf("请输入你的积分数:\n");
	scanf("%d",&m);
	printf("====================================================\n");

	deal_sp(m,0);
	sort();
	int plan=1;//记录输出方案的个数;
	for(i=0;i<result_num;i++)//按损失从小到大排序
	{	//int remain = m;
		printf("****===第%d选择===****\n",plan++);
		printf("兑换以下所有商品后剩余积分:%d\n",results[i][MAX]);
		printf("\n商品名称\t\t\t\t\t需积分\t换购数\n");
		printf("------------------------------------------------\n");
		for(int j=0;j<tot_sp;j++)
		{	
			printf("%-40s\t%-5d\t%-2d\n",splist[j].name,splist[j].value,results[i][j]);
			//remain -= results[i][j] * splist[j].value;
			//printf("%d=%d-%d *%d \n",remain,remain,splist[j].value*results[i][j]);
		}
		printf("================================================\n");
	}
	printf("\n");
	save();

}


void deal_sp(int now_creadit,int now_sp_index)//递归得出最佳方案;
{	
	if(best_results==result_num) return;
	if(now_sp_index==tot_sp||now_creadit==expect_remain)//已经遍历完所有商品;
	{	
		  if (now_creadit == expect_remain) best_results++; 
		if(result_index<result_num)//结果储存数组还没满;
		{	update_result(now_sp_index,now_creadit,result_index);
			result_index++;
		}
		else//有没有可以替换的数据;
		{	int max_remain_i=0;
			for(int j=0;j<result_num;j++)//找到当前的五种方案中剩余积分最多的方案;
			{	
				if(results[j][MAX]>results[max_remain_i][MAX])	
					max_remain_i=j;
			}
	
			if(results[max_remain_i][MAX]>now_creadit)//如果现在的方案更好，则替换它;
				update_result(now_sp_index,now_creadit,max_remain_i);
		}
	return;
	}
	for(int i=now_creadit/splist[now_sp_index].value;i>=0;i--)
	{
		temp_result[now_sp_index]=i;//假设购买i件当前商品;
		deal_sp(now_creadit-splist[now_sp_index].value*i,now_sp_index+1);
	}
}

void update_result(int now_sp_index,int now_creadit,int result_index)//向结果储存数组储存、更新换购方案;
{
	for(int i=0;i<now_sp_index;i++)//写入购买商品的数量;
			results[result_index][i]=temp_result[i];

	results[result_index][MAX]=now_creadit;//存放剩余的积分数;
}

void sort()//按积分损失从小到大排序;
{	int i,j,k;
	int temp=0;
	for(i=0;i<result_num-1;i++)//冒泡排序
	{
		for(j=0;j<result_num-i-1;j++)
		{	if(results[j][MAX]>results[j+1][MAX])//比较谁剩的积分多;
			{//printf("%d\t\t%d\n",results[i][j],results[i+1][j]);
				for(k=0;k<MAX+1;k++)
				{	temp=results[j][k];
					results[j][k]=results[j+1][k];
					results[j+1][k]=temp;
				//	printf("%d \t%d\t%d\t\n",temp,results[j][k],results[j][k+1]);
				}
			}
		}
	}
}

void save()
{	
	int plan=1;
	printf("需要保存换购方案到文件中吗？按1 Yes,按 0 No\n");
	int flag;
	scanf("%d",&flag);
	FILE *fp;
	if((fp=fopen("换购清单.txt","w+"))==NULL)
	{	printf("cannot open file!");
		exit(0);
	}
	char s[100] = { "\n商品名称\t\t\t\t\t需积分\t换购数\n" };
	char s2[100] = { "---------------------------------------------------------------------------------------------\n" };
	//写入数据
	while(flag==1){
	for(int i=0;i<result_num;i++)
	{	
		fprintf(fp,"********************===第%d选择===********************\n",plan++);
		fprintf(fp,"兑换以下所有商品后剩余积分:%d\n",results[i][MAX]);
		fprintf(fp, "%s", s);
		fprintf(fp, "%s", s2);
		for (int j=0;j<tot_sp;j++)
			{
				fprintf(fp, "%-40s\t\t%-5d\t%-2d\n",splist[j].name,splist[j].value,results[i][j]);
			}
	}
	printf("保存成功！！！\n");
	break;
	}
	fclose(fp);

}