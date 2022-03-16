#include <graphics.h>		// 引用图形库头文件
#include <conio.h>
#include<stdio.h>

/*
int main()
{
	initgraph(640, 480);	// 创建绘图窗口，大小为 640x480 像素
	// 设置背景色为蓝色
	setbkcolor(WHITE);
	// 用背景色清空屏幕,这样才能让背景色发挥作用
	cleardevice();

//	setlinecolor(0xff0000); //将颜色设置为蓝色
	setlinecolor(RED);		//将颜色设置为红色
	circle(200, 200, 100);	// 画圆，圆心(200, 200)，半径 100
	setfillcolor(YELLOW);
	setfillstyle(BS_HATCHED, HS_BDIAGONAL);
	printf("%d\n",BYTE GetRValue( BLUE));//返回并输出指定颜色的红色值

	_getch();				// 按任意键继续
	closegraph();			// 关闭绘图窗口
	return 0;
}
*/

/*
int main()
{
	// 初始化绘图窗口
	initgraph(640, 480);
//	setorigin(200, 200);	//设置坐标原点
	// 创建一个矩形区域
	HRGN rgn = CreateRectRgn(100, 100, 200, 200);
	// 将该矩形区域设置为裁剪区
	setcliprgn(rgn);
	// 不再使用 rgn，清理 rgn 占用的系统资源
	DeleteObject(rgn);

	// 画圆，受裁剪区影响，只显示出四段圆弧
	circle(150, 150, 55);

	// 取消之前设置的裁剪区
	setcliprgn(NULL);

	// 画圆，不再受裁剪区影响，显示出一个完整的圆
	circle(150, 150, 60);

	// 按任意键退出
	_getch();
	closegraph();
	return 0;
}
*/

//填充图案程序
/*
#include <conio.h>
#include <graphics.h>

int main()
{
	// 创建绘图窗口
	initgraph(640, 480);

	// 定义填充单元
	IMAGE img(10, 8);

	// 绘制填充单元
	SetWorkingImage(&img);	// 设置绘图目标为 img 对象
	setbkcolor(BLACK);		// 黑色区域为背景色
	cleardevice();
	setfillcolor(WHITE);	// 白色区域为自定义图案
	solidrectangle(1, 1, 8, 5);
	SetWorkingImage(NULL);	// 恢复绘图目标为默认绘图窗口

	// 设置填充样式为自定义填充图案
	setfillstyle(BS_PATTERN, NULL, &img);

	// 设置自定义图案的填充颜色
	settextcolor(GREEN);

	// 绘制无边框填充三角形
	POINT pts[] = { {50, 50}, {50, 200}, {300, 50} };
	solidpolygon(pts, 3);

	// 按任意键退出
	_getch();
	closegraph();
}
*/

#include <graphics.h>
#include <conio.h>
#include <math.h>

#define PI 3.14159265359

int main()
{
	// 创建绘图窗口
	initgraph(640, 480);

	// 定义数组，保存五角星的五个顶点坐标
	POINT pts[5];

	// 计算五角星的五个顶点坐标
	double a = PI / 2;
	for (int i = 0; i < 5; i++)
	{
		pts[i].x = int(320 + cos(a) * 100);
		pts[i].y = int(240 - sin(a) * 100);
		a += PI * 4 / 5;
	}

	// 设置填充模式为 WINDING
	setpolyfillmode(WINDING);
	// 设置填充颜色为红色
	setfillcolor(RED);
	// 绘制五角星(无边框)
	solidpolygon(pts, 5);

	// 按任意键退出
	_getch();
	closegraph();
}