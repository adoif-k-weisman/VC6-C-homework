#include<stdio.h>
#include<stdlib.h>
void save();
#define MAX 100	//������Ʒ���������࣬�����û����ӡ�����ʵ����Ʒ����;
#define result_num 5//������ʧ��С��ǰ������ϣ�
#define tot_sp 10
int result_index=0;//��ʾĿǰ��Ž����������±ꣻ
int results[result_num][MAX+1];//results[][]�����Ź�����Ʒ�����������һ��Ԫ�ش��ʣ����֣�
int temp_result[MAX];//�����ʱ����������Ʒ������;
//int tot_sp=10;//�ܵ�ʵ�ʵ���Ʒ����;
int best_results = 0;
int expect_remain = 0;
struct stru_sp
{
	char name[256];
	int value;
};
stru_sp splist[MAX]={//������Ʒ��Ϣ,��Ʒ�嵥;
	{"����˫���",8200},
	{"�¿�ë��",683},
	{"���������ֽ",1040},
	{"2018ϴ����ë��",1250},
	{"С��(MI) 10000���� ���ƶ���Դ2",7900},
	{"�ֿ��ֿ�(LOCK&LOCK) ����ֱ��±�",8690},
	{"�����ͻ���֬41.5g�������˪��",710},
	{"Kans���� «����",1905},
	{"ά��(Vinda) ����ֽ",2090},
	{"�ѽ�ʿ",394}
};
void update_result(int now_sp_index,int now_creadit,int result_index);
void deal_sp(int now_creadit,int now_sp_index);
void sort();
void save();
void main()
{
	int m;
	printf("���е���Ʒ��\n");
	for(int i=0;i<tot_sp;i++)//��ӡ���е���Ʒ;
	{	printf("%-40s\t%-5d\n",splist[i].name,splist[i].value);
	}
	printf("�ܹ�����Ʒ����%d\n",tot_sp);
	printf("====================================================\n");
	printf("��������Ļ�����:\n");
	scanf("%d",&m);
	printf("====================================================\n");

	deal_sp(m,0);
	sort();
	int plan=1;//��¼��������ĸ���;
	for(i=0;i<result_num;i++)//����ʧ��С��������
	{	//int remain = m;
		printf("****===��%dѡ��===****\n",plan++);
		printf("�һ�����������Ʒ��ʣ�����:%d\n",results[i][MAX]);
		printf("\n��Ʒ����\t\t\t\t\t�����\t������\n");
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


void deal_sp(int now_creadit,int now_sp_index)//�ݹ�ó���ѷ���;
{	
	if(best_results==result_num) return;
	if(now_sp_index==tot_sp||now_creadit==expect_remain)//�Ѿ�������������Ʒ;
	{	
		  if (now_creadit == expect_remain) best_results++; 
		if(result_index<result_num)//����������黹û��;
		{	update_result(now_sp_index,now_creadit,result_index);
			result_index++;
		}
		else//��û�п����滻������;
		{	int max_remain_i=0;
			for(int j=0;j<result_num;j++)//�ҵ���ǰ�����ַ�����ʣ��������ķ���;
			{	
				if(results[j][MAX]>results[max_remain_i][MAX])	
					max_remain_i=j;
			}
	
			if(results[max_remain_i][MAX]>now_creadit)//������ڵķ������ã����滻��;
				update_result(now_sp_index,now_creadit,max_remain_i);
		}
	return;
	}
	for(int i=now_creadit/splist[now_sp_index].value;i>=0;i--)
	{
		temp_result[now_sp_index]=i;//���蹺��i����ǰ��Ʒ;
		deal_sp(now_creadit-splist[now_sp_index].value*i,now_sp_index+1);
	}
}

void update_result(int now_sp_index,int now_creadit,int result_index)//�����������鴢�桢���»�������;
{
	for(int i=0;i<now_sp_index;i++)//д�빺����Ʒ������;
			results[result_index][i]=temp_result[i];

	results[result_index][MAX]=now_creadit;//���ʣ��Ļ�����;
}

void sort()//��������ʧ��С��������;
{	int i,j,k;
	int temp=0;
	for(i=0;i<result_num-1;i++)//ð������
	{
		for(j=0;j<result_num-i-1;j++)
		{	if(results[j][MAX]>results[j+1][MAX])//�Ƚ�˭ʣ�Ļ��ֶ�;
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
	printf("��Ҫ���滻���������ļ����𣿰�1 Yes,�� 0 No\n");
	int flag;
	scanf("%d",&flag);
	FILE *fp;
	if((fp=fopen("�����嵥.txt","w+"))==NULL)
	{	printf("cannot open file!");
		exit(0);
	}
	char s[100] = { "\n��Ʒ����\t\t\t\t\t�����\t������\n" };
	char s2[100] = { "---------------------------------------------------------------------------------------------\n" };
	//д������
	while(flag==1){
	for(int i=0;i<result_num;i++)
	{	
		fprintf(fp,"********************===��%dѡ��===********************\n",plan++);
		fprintf(fp,"�һ�����������Ʒ��ʣ�����:%d\n",results[i][MAX]);
		fprintf(fp, "%s", s);
		fprintf(fp, "%s", s2);
		for (int j=0;j<tot_sp;j++)
			{
				fprintf(fp, "%-40s\t\t%-5d\t%-2d\n",splist[j].name,splist[j].value,results[i][j]);
			}
	}
	printf("����ɹ�������\n");
	break;
	}
	fclose(fp);

}