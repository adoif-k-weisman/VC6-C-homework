
#include<stdio.h>
#include<stdlib.h>
#define N 50
#define LEN 15
int n=0;
struct Student_info
{	char StuID[LEN];//学生学号 
	char Stuname[LEN];//姓名
	char Stusex;//性别,w--女生,m--男生;
	int Stuage;//年龄
	float score[3]; //三科成绩，分别对应C语言，高数，英语；

}stu[N];


void main()
{
	//char filename[LEN + 1];
	int i = 0;
	printf("请输入要刷新学生信息的文件名：\n");
//	scanf("%s", filename);
	int j = 0;
	FILE * fp;
	if ((fp = fopen("C:\\Users\\adoif\\Desktop\\student3.txt", "r")) == NULL) 
	{
		printf("canont open file!\n");
		exit(0);
	}
	//从文件读取信息 
	while (fscanf(fp, "%s %s %c %d %.lf %,lf %.lf ",stu[i].StuID, stu[i].Stuname, &stu[i].Stusex,&stu[i].Stuage,stu[i].score[0], stu[i].score[1], stu[i].score[2]) == 7) {
		j++;
		printf("================\n");
	}
	n = j;
	printf("n=%d,j=%d",n,j);
	printf("刷新成功\n!!!");
	//return n;
	printf("read read read!!!\n");
	for(i=0;i<n;i++)
	{
		printf("%s\t\t%s\t\t%c\t\t%d\t\t%.2f\t\t%.2f\t\t%.2f\n",stu[i].StuID,stu[i].Stuname,stu[i].Stusex,stu[i].Stuage,stu[i].score[0],stu[i].score[1],stu[i].score[2]);	
	}
}
