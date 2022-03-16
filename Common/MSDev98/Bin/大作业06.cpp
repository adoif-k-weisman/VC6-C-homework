#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX 256//������Ʒ���������࣬�����û����ӡ�����ʵ����Ʒ����;
#define result_num 5//������ʧ��С��ǰ������ϣ�
int best_results=0;//Ŀǰ���е������ϣ�
int result_index=0;//��ʾĿǰ��Ž����������±ꣻ
int results[result_num][MAX+1];//result��Ź�����Ʒ�����������һ��Ԫ�ش��ʣ����֣�
int temp_result[MAX];//�����ʱ����������Ʒ������;
int tot_sp=10;//�ܵ�ʵ�ʵ���Ʒ����;
int expect_remain = 0;//���ʣ���������0�����������ڽ�ʡ�ݹ�ʱ�䣻
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
void main()
{
	int m; 
	printf("���е���Ʒ��\n");
	for(int i=0;i<tot_sp;i++)//��ӡ���е���Ʒ;
	{	
		printf("%-40s\t%-5d\n",splist[i].name,splist[i].value);
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
	{	
		printf("****===��%dѡ��===****\n",plan++);
		printf("�һ�����������Ʒ��ʣ�����:%d\n",results[i][MAX]);
		printf("\n��Ʒ����\t\t\t\t\t�����\t������\n");
		printf("------------------------------------------------\n");
		for(int j=0;j<tot_sp;j++)
		{
			printf("%-40s\t%-5d\t%-2d\n",splist[j].name,splist[j].value,results[i][j]);
		}
		printf("================================================\n");
	}
	printf("\n");
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
{	int i,temp,j,k;
	for(i=0;i<result_num-1;i++)
	{
		for(j=0;j<result_num-i-1;j++)
		{	if(results[j][MAX]>results[j+1][MAX])//�Ƚ�˭ʣ�Ļ��ֶ�;
			{
				for(k=0;k<MAX+1;k++)
				{	temp=results[j][k];
					results[j][k]=results[j+1][k];
					results[j+1][k]=temp;
				}
			}
		}
	}
}