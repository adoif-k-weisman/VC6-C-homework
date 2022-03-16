//每个同学的信息：学号、姓名、性别、三门课程成绩（可以自由扩充，出生日期、电话、学号等等）
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define N 50	//N表示总的可以储存的学生人数;
#define LEN 15
int n=3,t=1;	//n表示实际有的，现在有的学生人数；
struct Student_info
{	char StuID[LEN];//学生学号 
	char Stuname[LEN];//姓名
	char Stusex;//性别,w--女生,m--男生;
	int Stuage;//年龄
	float score[3]; //三科成绩，分别对应C语言，高数，英语；

}stu[N]={{"20011397","adoif",'m',19,99,86,90},{"20011398","shiina",'w',18,90,89,96},{"20011399","joan",'w',17,96,99,90}};

void menu();//菜单函数，显示本系统支持的功能;
void present();
void seek();
void modify();//修改学生信息;
void flunk();
void sort();
void increase();
void del();
void save();
void exit();


int main()
{
	int num;//num是菜单选项 
	while(t)//t是全局变量，用exit退出函数改变t的值来控制循环是否继续 
	{
		menu();//输出主菜单界面 
		printf("您好，请输入菜单编号：");
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
			default:printf("输入有误，请重新输入！");	
	}
	} 
	return 0;
}
void menu()//菜单---提示输入数字；
{
	printf("\n\n");
	printf("*****************************************************\n");
	printf("*-------------------中央民族大学------------------------\n");	
	printf("*                 学生信息管理系统                  *\n");
	printf("*****************************************************\n");
	printf("********************系统功能菜单*********************\n");
	printf("----------------------     --------------------------\n");
	printf("**********************************************************************\n");
	printf("**    1、显示所有同学的信息       *     2、查找指定同学的信息      **\n");
	printf("*****************************************************\n");
	printf("**    3、修改指定同学的信息  *     4、显示有不及格同学的信息       **\n");
	printf("*****************************************************\n");
	printf("**    5、按指定课程排序输出 *     6、增加一个新同学     **\n");
	printf("*****************************************************\n");
	printf("**    7、删除一个同学   *     8、以文件形式保存      **\n");
	printf("******0、退出学生信息管理系统********\n");
	printf("**********************************************************************\n");
	printf("*************************                            \n");
	printf("----------------------     --------------------------\n");
	
} 


void present()//显示所有同学的信息；
{	
	if(n==0)
	{
		printf("您好，现在没有学生信息，请先增加学生信息!\n");
	}
	else
	{
		printf("现在共有%d名学生：\n",n);
		printf("学号\t\t姓名\t\t性别\t\t年龄\t\tC语言\t\t高数\t\t英语\n");
		for(int i=0;i<n;i++)
		{
			printf("%s\t\t%s\t\t%c\t\t%d\t\t%.2f\t\t%.2f\t\t%.2f\n",stu[i].StuID,stu[i].Stuname,stu[i].Stusex,stu[i].Stuage,stu[i].score[0],stu[i].score[1],stu[i].score[2]);	
		}
	}
		
	system("pause");	
}

void seek()//查找指定同学的信息；
{
int i,num,flag;
	char s1[LEN+1];
	printf("*****************************\n");
	printf("**-------1.按学号查询------**\n");
	printf("**-------2.按姓名查询------**\n");
	printf("**-------3.退出本菜单------**\n");
	printf("*****************************\n");
	while(1)
	{
		flag=0;
		printf("请输入子菜单：");
		scanf("%d",&num);
		switch(num)
		{
			case 1:
			printf("请输入需要查找学生的学号：\n");
			scanf("%s",s1);
			for(i=0;i<n;i++)
			{
				if(strcmp(stu[i].StuID,s1)==0)
				{
					flag=1;
					printf("学号\t\t姓名\t\t性别\t\t年龄\t\tC语言\t\t高数\t\t英语\n");
					printf("%s\t\t%s\t\t%c\t\t%d\t\t%.2f\t\t%.2f\t\t%.2f\n",stu[i].StuID,stu[i].Stuname,stu[i].Stusex,stu[i].Stuage,stu[i].score[0],stu[i].score[1],stu[i].score[2]);
				}	
			}break;	
			case 2:
			printf("请输入需要查找学生的姓名：\n");
			scanf("%s",s1);
			for(i=0;i<n;i++)
			{
				if(strcmp(stu[i].Stuname,s1)==0)
				{
					flag=1;
					printf("学号\t\t姓名\t\t性别\t\t年龄\t\tC语言\t\t高数\t\t英语\n");
					printf("%s\t\t%s\t\t%c\t\t%d\t\t%.2f\t\t%.2f\t\t%.2f\n",stu[i].StuID,stu[i].Stuname,stu[i].Stusex,stu[i].Stuage,stu[i].score[0],stu[i].score[1],stu[i].score[2]);
				}	
			}break;		
			case 3: return;
			default: printf("请在1--3之间输入\n");
		}
		if(flag==0)
		printf("找不到该学生!\n请重新输入！"); 
	} 
}
void modify( )//n---表示长度，str[]结构体数组；
{
	char ID[LEN],name[LEN],sex;
	int age;
	float score;
	getchar();//处理上面敲入的回车符;
	printf("请输入需要修改的学生姓名：");
	gets(name);
	while(1)
	{	
		int flag=0;
		for(int i=0;i<n;i++)
		{
			if(strcmp(name,stu[i].Stuname)==0)
			{
				flag=1;
				int num;//用于switch函数的子菜单 
				printf("请选择需要修改的学生信息：\n");
				printf("***************************************************\n");
				printf("*----1.修改学号--------  -  -----2.修改性别-------*\n");
				printf("*----3.修改年龄--------  -  -----4.修改C语言成绩--*\n");
				printf("*----5.修改高数成绩----  -  -----6.修改英语成绩---*\n");
				printf("*-------------------7.退出本菜单------------------*\n");
				printf("***************************************************\n\n");
				printf("请输入子菜单：");
				scanf("%d",&num);
				switch(num)
				{
					case 1:	
					printf("请输入新的学号:\n");
					getchar();
					gets(ID);
					strcpy(stu[i].StuID,ID);break;
					case 2:
					getchar();//处理回车符;	
					printf("请输入新的性别:\n");
					scanf("%c",&sex);
					stu[i].Stusex=sex;break;
					case 3:
					printf("请输入新的年龄:\n");
					scanf("%d",&age);
					stu[i].Stuage=age;break;
					case 4:
					printf("请输入新的C语言成绩:\n");
					scanf("%f",&score);
					stu[i].score[0]=score;break;
					case 5:
					printf("请输入新的高数成绩:\n");
					scanf("%f",&score);
					stu[i].score[1]=score;break;
					case 6:
					printf("请输入新的英语成绩:\n");
					scanf("%f",&score);
					stu[i].score[2]=score;break;
					case 7:
					return;break; 
					default:
					printf("请在1--7之间选择！\n");
				}
				if(num>0&&num<7)
				printf("修改成功，注意保存哟！！！\n");
				break;//找到学生，结束循环;	
			}
		}	
		if(flag==0)
		{
			printf("没有找到该学生，请重新输入需要修改信息的学生姓名：\n");
			gets(name);
		}
	}
	system("pause");	
}

void flunk()//默认满分为100分，60分以下不及格；
{
	for(int i=0;i<n;i++)
	{
		if(stu[i].score[0]<60||stu[i].score[1]<60||stu[i].score[2]<60)
		{	printf("不及格同学的信息：\n");
			printf("学号\t\t姓名\t\t性别\t\t年龄\t\tC语言\t\t高数\t\t英语\n");
			printf("%s\t\t%s\t\t%c\t\t%d\t\t%.2f\t\t%.2f\t\t%.2f\n",stu[i].StuID,stu[i].Stuname,stu[i].Stusex,stu[i].Stuage,stu[i].score[0],stu[i].score[1],stu[i].score[2]);
		}
		else if(i==n-1)//没有同学的信息被输出;
			printf("没有成绩不及格的同学！！！\n");
	}
	system("pause");
}

void sort( )//按指定课程排序输出;
{	
	int num,i,j;
	struct Student_info temp;//temp作为结构体，临时储存交换学生的信息;
	printf("请输入数字选择要排序的课程成绩：\n");
	printf("'  1.C语言成绩\t  2.高数成绩 \t 3.英语成绩\n");
	scanf("%d",&num);

	for(j=0;j<n-1;j++)//冒泡排序;
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

	printf("the sorted grades(成绩由低到高输出):\n");
	printf("学号\t\t姓名\t\t性别\t\t年龄\t\tC语言\t\t高数\t\t英语\n");
	for(i=0;i<n;i++)
		printf("%s\t\t%s\t\t%c\t\t%d\t\t%.2f\t\t%.2f\t\t%.2f\n",stu[i].StuID,stu[i].Stuname,stu[i].Stusex,stu[i].Stuage,stu[i].score[0],stu[i].score[1],stu[i].score[2]);
	
	system("pause");
}
void increase()//增加一个新同学;
{

	int i=n,j,flag,m=0;//i代表增加学生信息过程中任意时刻的学生人数 ,flag作为判断增加学生信息的过程是否完成;
	printf("\n请输入待增加的学生人数：\n");
	scanf("%d",&m);
	if(m>0){
	do{
		flag=1;
		while(flag)
		{
			flag=0;
			printf("请输入第%d位学生的学号：\n",i+1);//第几位学生从1开始计数,而stu[]从零开始，需要加1 ;
			scanf("%s",stu[i].StuID);
			//判断学号是否重复
			for(j=0;j<i;j++){
				if(strcmp(stu[i].StuID,stu[j].StuID)==0){
					printf("该学号已经存在，请重新输入！\n");	
					flag=1;
					break;			
				}	 
			}
		}
		printf("请输入第%d位学生姓名:\n",i+1);
		scanf("%s",stu[i].Stuname); 
		printf("请输入第%d位学生年龄:\n",i+1);
		scanf("%d",&stu[i].Stuage); 
		getchar();//处理上面输入的换行符；
		printf("请输入第%d位学生性别:\n",i+1);	
		scanf("%c",&stu[i].Stusex);
		printf("请输入第%d位学生的C语言成绩:\n",i+1);
		scanf("%f",&stu[i].score[0]);
		printf("请输入第%d位学生的高数成绩:\n",i+1);
		scanf("%f",&stu[i].score[1]);
		printf("请输入第%d位学生的大学英语成绩:\n",i+1);
		scanf("%f",&stu[i].score[2]);
		i++;
		}while(i<n+m);//只要当前学生人数还没到达添加后的总人数，就得继续添加		
	}
	n+=m;// 添加完成，系统人数n的值也要增加 
	printf("添加完成！！！\n");
	system("pause");
}

void del()//删除一个同学
{
	int i,j,flag;
	char s1[LEN];
	printf("请输入需要删除的学生学号：\n");
	scanf("%s",s1);
	flag=0;
	for(i=0;i<n;i++)
	{
		if(strcmp(s1,stu[i].StuID)==0)
		{
			flag=1;
			for(j=i;j<n-1;j++)
			{
				stu[j]=stu[j+1];//直接把后面的学生都往前移动一位 
			}
		}
		if(flag==1) break;//说明已经找到了需要删除的学生，结束循环 
	} 
	 if(0==flag)
	 {
	 	printf("该学号不存在！！！\n");
	 }
	
	if(1==flag)
	{	
		printf("删除成功\n");
		n--;		
	}
	system("pause");
}
void save()//退出并把学生信息保存到文件 
{
	int i;
	FILE *fp;
	char filename[LEN+1];
	printf("请输入要保存的文件名(记得加.txt后缀名呐)：\n"); 	
	scanf("%s",filename);
	if((fp=fopen(filename,"w+"))==NULL)
	{
		printf("打开文件失败！\n");
		exit(0);	
	}
    char s[100] = { "学号\t\t姓名\t性别\t年龄  \tC语言 \t高数 \t英语\n" };
	char s2[100] = { "---------------------------------------------------------------------------------------------\n" };
	//写入数据
	fprintf(fp, "%s", s);
	fprintf(fp, "%s", s2);
	for (i=0;i<n;i++)
	{
		fprintf(fp, "%s\t%s\t%c\t%d\t%.lf\t%.lf\t%.lf\n", stu[i].StuID, stu[i].Stuname, stu[i].Stusex, stu[i].Stuage,stu[i].score[0], stu[i].score[1], stu[i].score[2]);
	}
	printf("保存成功！！！\n");
	fclose(fp);
	system("pause");
}


void exit()
{	int flag;
	printf("确认退出吗？按1确认，按0取消\n");
	scanf("%d",&flag);
	if(flag==1)
	{	t=0;//t=0,退出main函数里的while循环;
		printf("成功退出，感谢使用\n");
	}
	else
	{	t=1;
		printf("退出取消\n");
		system("pause");
	}
}
	