#include <graphics.h>		// ����ͼ�ο�ͷ�ļ�
#include <conio.h>
#include<stdio.h>

/*
int main()
{
	initgraph(640, 480);	// ������ͼ���ڣ���СΪ 640x480 ����
	// ���ñ���ɫΪ��ɫ
	setbkcolor(WHITE);
	// �ñ���ɫ�����Ļ,���������ñ���ɫ��������
	cleardevice();

//	setlinecolor(0xff0000); //����ɫ����Ϊ��ɫ
	setlinecolor(RED);		//����ɫ����Ϊ��ɫ
	circle(200, 200, 100);	// ��Բ��Բ��(200, 200)���뾶 100
	setfillcolor(YELLOW);
	setfillstyle(BS_HATCHED, HS_BDIAGONAL);
	printf("%d\n",BYTE GetRValue( BLUE));//���ز����ָ����ɫ�ĺ�ɫֵ

	_getch();				// �����������
	closegraph();			// �رջ�ͼ����
	return 0;
}
*/

/*
int main()
{
	// ��ʼ����ͼ����
	initgraph(640, 480);
//	setorigin(200, 200);	//��������ԭ��
	// ����һ����������
	HRGN rgn = CreateRectRgn(100, 100, 200, 200);
	// ���þ�����������Ϊ�ü���
	setcliprgn(rgn);
	// ����ʹ�� rgn������ rgn ռ�õ�ϵͳ��Դ
	DeleteObject(rgn);

	// ��Բ���ܲü���Ӱ�죬ֻ��ʾ���Ķ�Բ��
	circle(150, 150, 55);

	// ȡ��֮ǰ���õĲü���
	setcliprgn(NULL);

	// ��Բ�������ܲü���Ӱ�죬��ʾ��һ��������Բ
	circle(150, 150, 60);

	// ��������˳�
	_getch();
	closegraph();
	return 0;
}
*/

//���ͼ������
/*
#include <conio.h>
#include <graphics.h>

int main()
{
	// ������ͼ����
	initgraph(640, 480);

	// ������䵥Ԫ
	IMAGE img(10, 8);

	// ������䵥Ԫ
	SetWorkingImage(&img);	// ���û�ͼĿ��Ϊ img ����
	setbkcolor(BLACK);		// ��ɫ����Ϊ����ɫ
	cleardevice();
	setfillcolor(WHITE);	// ��ɫ����Ϊ�Զ���ͼ��
	solidrectangle(1, 1, 8, 5);
	SetWorkingImage(NULL);	// �ָ���ͼĿ��ΪĬ�ϻ�ͼ����

	// ���������ʽΪ�Զ������ͼ��
	setfillstyle(BS_PATTERN, NULL, &img);

	// �����Զ���ͼ���������ɫ
	settextcolor(GREEN);

	// �����ޱ߿����������
	POINT pts[] = { {50, 50}, {50, 200}, {300, 50} };
	solidpolygon(pts, 3);

	// ��������˳�
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
	// ������ͼ����
	initgraph(640, 480);

	// �������飬��������ǵ������������
	POINT pts[5];

	// ��������ǵ������������
	double a = PI / 2;
	for (int i = 0; i < 5; i++)
	{
		pts[i].x = int(320 + cos(a) * 100);
		pts[i].y = int(240 - sin(a) * 100);
		a += PI * 4 / 5;
	}

	// �������ģʽΪ WINDING
	setpolyfillmode(WINDING);
	// ���������ɫΪ��ɫ
	setfillcolor(RED);
	// ���������(�ޱ߿�)
	solidpolygon(pts, 5);

	// ��������˳�
	_getch();
	closegraph();
}