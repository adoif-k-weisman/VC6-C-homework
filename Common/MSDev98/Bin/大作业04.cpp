//ÿ��ͬѧ����Ϣ��ѧ�š��������Ա����ſγ̳ɼ��������������䣬�������ڡ��绰��ѧ�ŵȵȣ�
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define N 50	//N��ʾ�ܵĿ��Դ����ѧ������;
#define LEN 15
int n=3,t=1;	//n��ʾʵ���еģ������е�ѧ��������
struct Student_info
{	char StuID[LEN];//ѧ��ѧ�� 
	char Stuname[LEN];//����
	char Stusex;//�Ա�,w--Ů��,m--����;
	int Stuage;//����
	float score[3]; //���Ƴɼ����ֱ��ӦC���ԣ�������Ӣ�

}stu[N]={{"20011397","adoif",'m',19,99,86,90},{"20011398","shiina",'w',18,90,89,96},{"20011399","joan",'w',17,96,99,90}};

void menu();//�˵���������ʾ��ϵͳ֧�ֵĹ���;
void present();
void seek();
void modify();//�޸�ѧ����Ϣ;
void flunk();
void sort();
void increase();
void del();
void save();
void exit();


int main()
{
	int num;//num�ǲ˵�ѡ�� 
	while(t)//t��ȫ�ֱ�������exit�˳������ı�t��ֵ������ѭ���Ƿ���� 
	{
		menu();//������˵����� 
		printf("���ã�������˵���ţ�");
		scanf("%d",&num); 
		switch(num)
		{
			case 1: present(); break;
			case 2: seek(); break;
			case 3: modify(); break;
			case 4: flunk(); break;
			case 5: sort(); break;
			case 6: increase(); break;
			case 7: del(); break;
			case 8: save(); break; 
			case 0: exit(); break;
			default:printf("�����������������룡");	
	}
	} 
	return 0;
}
void menu()//�˵�---��ʾ�������֣�
{
	printf("\n\n");
	printf("*****************************************************\n");
	printf("*-------------------���������ѧ------------------------\n");	
	printf("*                 ѧ����Ϣ����ϵͳ                  *\n");
	printf("*****************************************************\n");
	printf("********************ϵͳ���ܲ˵�*********************\n");
	printf("----------------------     --------------------------\n");
	printf("**********************************************************************\n");
	printf("**    1����ʾ����ͬѧ����Ϣ       *     2������ָ��ͬѧ����Ϣ      **\n");
	printf("*****************************************************\n");
	printf("**    3���޸�ָ��ͬѧ����Ϣ  *     4����ʾ�в�����ͬѧ����Ϣ       **\n");
	printf("*****************************************************\n");
	printf("**    5����ָ���γ�������� *     6������һ����ͬѧ     **\n");
	printf("*****************************************************\n");
	printf("**    7��ɾ��һ��ͬѧ   *     8�����ļ���ʽ����      **\n");
	printf("******0���˳�ѧ����Ϣ����ϵͳ********\n");
	printf("**********************************************************************\n");
	printf("*************************                            \n");
	printf("----------------------     --------------------------\n");
	
} 


void present()//��ʾ����ͬѧ����Ϣ��
{	
	if(n==0)
	{
		printf("���ã�����û��ѧ����Ϣ����������ѧ����Ϣ!\n");
	}
	else
	{
		printf("���ڹ���%d��ѧ����\n",n);
		printf("ѧ��\t\t����\t\t�Ա�\t\t����\t\tC����\t\t����\t\tӢ��\n");
		for(int i=0;i<n;i++)
		{
			printf("%s\t\t%s\t\t%c\t\t%d\t\t%.2f\t\t%.2f\t\t%.2f\n",stu[i].StuID,stu[i].Stuname,stu[i].Stusex,stu[i].Stuage,stu[i].score[0],stu[i].score[1],stu[i].score[2]);	
		}
	}
		
	system("pause");	
}

void seek()//����ָ��ͬѧ����Ϣ��
{
int i,num,flag;
	char s1[LEN+1];
	printf("*****************************\n");
	printf("**-------1.��ѧ�Ų�ѯ------**\n");
	printf("**-------2.��������ѯ------**\n");
	printf("**-------3.�˳����˵�------**\n");
	printf("*****************************\n");
	while(1)
	{
		flag=0;
		printf("�������Ӳ˵���");
		scanf("%d",&num);
		switch(num)
		{
			case 1:
			printf("��������Ҫ����ѧ����ѧ�ţ�\n");
			scanf("%s",s1);
			for(i=0;i<n;i++)
			{
				if(strcmp(stu[i].StuID,s1)==0)
				{
					flag=1;
					printf("ѧ��\t\t����\t\t�Ա�\t\t����\t\tC����\t\t����\t\tӢ��\n");
					printf("%s\t\t%s\t\t%c\t\t%d\t\t%.2f\t\t%.2f\t\t%.2f\n",stu[i].StuID,stu[i].Stuname,stu[i].Stusex,stu[i].Stuage,stu[i].score[0],stu[i].score[1],stu[i].score[2]);
				}	
			}break;	
			case 2:
			printf("��������Ҫ����ѧ����������\n");
			scanf("%s",s1);
			for(i=0;i<n;i++)
			{
				if(strcmp(stu[i].Stuname,s1)==0)
				{
					flag=1;
					printf("ѧ��\t\t����\t\t�Ա�\t\t����\t\tC����\t\t����\t\tӢ��\n");
					printf("%s\t\t%s\t\t%c\t\t%d\t\t%.2f\t\t%.2f\t\t%.2f\n",stu[i].StuID,stu[i].Stuname,stu[i].Stusex,stu[i].Stuage,stu[i].score[0],stu[i].score[1],stu[i].score[2]);
				}	
			}break;		
			case 3: return;
			default: printf("����1--3֮������\n");
		}
		if(flag==0)
		printf("�Ҳ�����ѧ��!\n���������룡"); 
	} 
}
void modify( )//n---��ʾ���ȣ�str[]�ṹ�����飻
{
	char ID[LEN],name[LEN],sex;
	int age;
	float score;
	getchar();//������������Ļس���;
	printf("��������Ҫ�޸ĵ�ѧ��������");
	gets(name);
	while(1)
	{	
		int flag=0;
		for(int i=0;i<n;i++)
		{
			if(strcmp(name,stu[i].Stuname)==0)
			{
				flag=1;
				int num;//����switch�������Ӳ˵� 
				printf("��ѡ����Ҫ�޸ĵ�ѧ����Ϣ��\n");
				printf("***************************************************\n");
				printf("*----1.�޸�ѧ��--------  -  -----2.�޸��Ա�-------*\n");
				printf("*----3.�޸�����--------  -  -----4.�޸�C���Գɼ�--*\n");
				printf("*----5.�޸ĸ����ɼ�----  -  -----6.�޸�Ӣ��ɼ�---*\n");
				printf("*-------------------7.�˳����˵�------------------*\n");
				printf("***************************************************\n\n");
				printf("�������Ӳ˵���");
				scanf("%d",&num);
				switch(num)
				{
					case 1:	
					printf("�������µ�ѧ��:\n");
					getchar();
					gets(ID);
					strcpy(stu[i].StuID,ID);break;
					case 2:
					getchar();//����س���;	
					printf("�������µ��Ա�:\n");
					scanf("%c",&sex);
					stu[i].Stusex=sex;break;
					case 3:
					printf("�������µ�����:\n");
					scanf("%d",&age);
					stu[i].Stuage=age;break;
					case 4:
					printf("�������µ�C���Գɼ�:\n");
					scanf("%f",&score);
					stu[i].score[0]=score;break;
					case 5:
					printf("�������µĸ����ɼ�:\n");
					scanf("%f",&score);
					stu[i].score[1]=score;break;
					case 6:
					printf("�������µ�Ӣ��ɼ�:\n");
					scanf("%f",&score);
					stu[i].score[2]=score;break;
					case 7:
					return;break; 
					default:
					printf("����1--7֮��ѡ��\n");
				}
				if(num>0&&num<7)
				printf("�޸ĳɹ���ע�Ᵽ��Ӵ������\n");
				break;//�ҵ�ѧ��������ѭ��;	
			}
		}	
		if(flag==0)
		{
			printf("û���ҵ���ѧ����������������Ҫ�޸���Ϣ��ѧ��������\n");
			gets(name);
		}
	}
	system("pause");	
}

void flunk()//Ĭ������Ϊ100�֣�60�����²�����
{
	for(int i=0;i<n;i++)
	{
		if(stu[i].score[0]<60||stu[i].score[1]<60||stu[i].score[2]<60)
		{	printf("������ͬѧ����Ϣ��\n");
			printf("ѧ��\t\t����\t\t�Ա�\t\t����\t\tC����\t\t����\t\tӢ��\n");
			printf("%s\t\t%s\t\t%c\t\t%d\t\t%.2f\t\t%.2f\t\t%.2f\n",stu[i].StuID,stu[i].Stuname,stu[i].Stusex,stu[i].Stuage,stu[i].score[0],stu[i].score[1],stu[i].score[2]);
		}
		else if(i==n-1)//û��ͬѧ����Ϣ�����;
			printf("û�гɼ��������ͬѧ������\n");
	}
	system("pause");
}

void sort( )//��ָ���γ��������;
{	
	int num,i,j;
	struct Student_info temp;//temp��Ϊ�ṹ�壬��ʱ���潻��ѧ������Ϣ;
	printf("����������ѡ��Ҫ����Ŀγ̳ɼ���\n");
	printf("'  1.C���Գɼ�\t  2.�����ɼ� \t 3.Ӣ��ɼ�\n");
	scanf("%d",&num);

	for(j=0;j<n-1;j++)//ð������;
	{
		for(i=0;i<n-j-1;i++)
		{
			if(stu[i].score[num-1]>stu[i+1].score[num-1])
			{	temp=stu[i];
				stu[i]=stu[i+1];
				stu[i+1]=temp;
			}
		}
	}

	printf("the sorted grades(�ɼ��ɵ͵������):\n");
	printf("ѧ��\t\t����\t\t�Ա�\t\t����\t\tC����\t\t����\t\tӢ��\n");
	for(i=0;i<n;i++)
		printf("%s\t\t%s\t\t%c\t\t%d\t\t%.2f\t\t%.2f\t\t%.2f\n",stu[i].StuID,stu[i].Stuname,stu[i].Stusex,stu[i].Stuage,stu[i].score[0],stu[i].score[1],stu[i].score[2]);
	
	system("pause");
}
void increase()//����һ����ͬѧ;
{

	int i=n,j,flag,m=0;//i��������ѧ����Ϣ����������ʱ�̵�ѧ������ ,flag��Ϊ�ж�����ѧ����Ϣ�Ĺ����Ƿ����;
	printf("\n����������ӵ�ѧ��������\n");
	scanf("%d",&m);
	if(m>0){
	do{
		flag=1;
		while(flag)
		{
			flag=0;
			printf("�������%dλѧ����ѧ�ţ�\n",i+1);//�ڼ�λѧ����1��ʼ����,��stu[]���㿪ʼ����Ҫ��1 ;
			scanf("%s",stu[i].StuID);
			//�ж�ѧ���Ƿ��ظ�
			for(j=0;j<i;j++){
				if(strcmp(stu[i].StuID,stu[j].StuID)==0){
					printf("��ѧ���Ѿ����ڣ����������룡\n");	
					flag=1;
					break;			
				}	 
			}
		}
		printf("�������%dλѧ������:\n",i+1);
		scanf("%s",stu[i].Stuname); 
		printf("�������%dλѧ������:\n",i+1);
		scanf("%d",&stu[i].Stuage); 
		getchar();//������������Ļ��з���
		printf("�������%dλѧ���Ա�:\n",i+1);	
		scanf("%c",&stu[i].Stusex);
		printf("�������%dλѧ����C���Գɼ�:\n",i+1);
		scanf("%f",&stu[i].score[0]);
		printf("�������%dλѧ���ĸ����ɼ�:\n",i+1);
		scanf("%f",&stu[i].score[1]);
		printf("�������%dλѧ���Ĵ�ѧӢ��ɼ�:\n",i+1);
		scanf("%f",&stu[i].score[2]);
		i++;
		}while(i<n+m);//ֻҪ��ǰѧ��������û������Ӻ�����������͵ü������		
	}
	n+=m;// �����ɣ�ϵͳ����n��ֵҲҪ���� 
	printf("�����ɣ�����\n");
	system("pause");
}

void del()//ɾ��һ��ͬѧ
{
	int i,j,flag;
	char s1[LEN];
	printf("��������Ҫɾ����ѧ��ѧ�ţ�\n");
	scanf("%s",s1);
	flag=0;
	for(i=0;i<n;i++)
	{
		if(strcmp(s1,stu[i].StuID)==0)
		{
			flag=1;
			for(j=i;j<n-1;j++)
			{
				stu[j]=stu[j+1];//ֱ�ӰѺ����ѧ������ǰ�ƶ�һλ 
			}
		}
		if(flag==1) break;//˵���Ѿ��ҵ�����Ҫɾ����ѧ��������ѭ�� 
	} 
	 if(0==flag)
	 {
	 	printf("��ѧ�Ų����ڣ�����\n");
	 }
	
	if(1==flag)
	{	
		printf("ɾ���ɹ�\n");
		n--;		
	}
	system("pause");
}
void save()//�˳�����ѧ����Ϣ���浽�ļ� 
{
	int i;
	FILE *fp;
	char filename[LEN+1];
	printf("������Ҫ������ļ���(�ǵü�.txt��׺����)��\n"); 	
	scanf("%s",filename);
	if((fp=fopen(filename,"w+"))==NULL)
	{
		printf("���ļ�ʧ�ܣ�\n");
		exit(0);	
	}
    char s[100] = { "ѧ��\t\t����\t�Ա�\t����  \tC���� \t���� \tӢ��\n" };
	char s2[100] = { "---------------------------------------------------------------------------------------------\n" };
	//д������
	fprintf(fp, "%s", s);
	fprintf(fp, "%s", s2);
	for (i=0;i<n;i++)
	{
		fprintf(fp, "%s\t%s\t%c\t%d\t%.lf\t%.lf\t%.lf\n", stu[i].StuID, stu[i].Stuname, stu[i].Stusex, stu[i].Stuage,stu[i].score[0], stu[i].score[1], stu[i].score[2]);
	}
	printf("����ɹ�������\n");
	fclose(fp);
	system("pause");
}


void exit()
{	int flag;
	printf("ȷ���˳��𣿰�1ȷ�ϣ���0ȡ��\n");
	scanf("%d",&flag);
	if(flag==1)
	{	t=0;//t=0,�˳�main�������whileѭ��;
		printf("�ɹ��˳�����лʹ��\n");
	}
	else
	{	t=1;
		printf("�˳�ȡ��\n");
		system("pause");
	}
}
	