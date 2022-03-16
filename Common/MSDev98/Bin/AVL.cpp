#include<iostream>
#include<cstdio>
using namespace std;
//�����������㷨
#include <stdio.h>
#include <malloc.h>
//typedef int ElemType;


#define MaxSize 100
typedef char ElemType;
typedef struct node
{
	ElemType data;			//����Ԫ��
	struct node* lchild;	//ָ�����ӽڵ�
	struct node* rchild;	//ָ���Һ��ӽڵ�
} BTNode;


void CreateBTree(BTNode*& b, const char* str)	//����������
{
	BTNode* St[MaxSize], * p = NULL;
	int top = -1, k, j = 0;
	char ch;
	b = NULL;				//�����Ķ�������ʼʱΪ��
	ch = str[j];
	while (ch != '\0')  	//strδɨ����ʱѭ��
	{
		switch (ch)
		{
		case '(':top++; St[top] = p; k = 1; break;		//Ϊ���ӽڵ�
		case ')':top--; break;
		case ',':k = 2; break;                      		//Ϊ���ӽڵ��ҽڵ�
		default:p = (BTNode*)malloc(sizeof(BTNode));
			p->data = ch;
			p->lchild = p->rchild = NULL;
			if (b == NULL)                    	 	//*pΪ�������ĸ��ڵ�
				b = p;
			else  								//�ѽ������������ڵ�
			{
				switch (k)
				{
				case 1:St[top]->lchild = p; break;
				case 2:St[top]->rchild = p; break;
				}
			}
		}
		j++;
		ch = str[j];
	}
}

void DestroyBTree(BTNode*& b)
{
	if (b != NULL)
	{
		DestroyBTree(b->lchild);
		DestroyBTree(b->rchild);
		free(b);
	}
}
BTNode* FindNode(BTNode* b, ElemType x)
{
	BTNode* p;
	if (b == NULL)
		return NULL;
	else if (b->data == x)
		return b;
	else
	{
		p = FindNode(b->lchild, x);
		if (p != NULL)
			return p;
		else
			return FindNode(b->rchild, x);
	}
}
BTNode* LchildNode(BTNode* p)
{
	return p->lchild;
}
BTNode* RchildNode(BTNode* p)
{
	return p->rchild;
}
int BTHeight(BTNode* b)
{
	int lchildh, rchildh;
	if (b == NULL) return(0); 				//�����ĸ߶�Ϊ0
	else
	{
		lchildh = BTHeight(b->lchild);	//���������ĸ߶�Ϊlchildh
		rchildh = BTHeight(b->rchild);	//���������ĸ߶�Ϊrchildh
		return (lchildh > rchildh) ? (lchildh + 1) : (rchildh + 1);
	}
}
void DispBTree(BTNode* b)
{
	if (b != NULL)
	{
		printf("%c", b->data);
		if (b->lchild != NULL || b->rchild != NULL)
		{
			printf("(");						//�к��ӽڵ�ʱ�����(
			DispBTree(b->lchild);				//�ݹ鴦��������
			if (b->rchild != NULL) printf(",");	//���Һ��ӽڵ�ʱ�����,
			DispBTree(b->rchild);				//�ݹ鴦��������
			printf(")");						//�к��ӽڵ�ʱ�����)
		}
	}
}

//ʹ�õݹ鷽ʽʵ�ֶ��ֲ���
int BinSearch(ElemType a[],int target,int left,int right)
{
	int mid = (left + right) >> 1;
	if (a[mid] == target)	return mid;
	else if (left >= right) return -1;
	else if (a[mid] < target) return BinSearch(a, target, mid + 1, right);
	else   return BinSearch(a, target, left, mid - 1);
}


//2����֪������t����д�㷨�ж����Ƿ��Ƕ�����������
bool IsSearchTree(BTNode* b)
{
	if (b == NULL)
		return true;
	else if ((b->lchild == NULL) && (b->rchild == NULL))
		return true;
	else if (b->rchild==NULL) {//ֻ������
		if (b->lchild->data > b->data)
			return false;
		else
			return IsSearchTree(b->lchild);
	}
	else if (b->lchild == NULL) {//ֻ������
		if (b->rchild->data < b->data)
			return false;
		else
			return IsSearchTree(b->rchild);
	}
	else {//������������ȥ�����������������Ƿ��Ƕ���������
		if ((b->lchild->data > b->data) || (b->rchild->data < b->data))
			return false;
		else
			return (IsSearchTree(b->lchild) && IsSearchTree(b->rchild));
	}	
}


//��֪������t����д�㷨�ж����Ƿ���ƽ�������������
int get_height(BTNode* b)
{
	if (b == NULL)
		return 0;
	else {
		int lh = get_height(b->lchild);
		int rh = get_height(b->rchild);
		return 1 + (lh > rh ? lh : rh);
	}
}
/*
bool isBalance_SearchTree(BTNode* b)
{
	if (b == NULL)
		return true;
	int height_lr = get_height(b->lchild) - get_height(b->rchild);
	if (height_lr > 1 || height_lr < -1)//���ж����ǲ���ƽ���������ж����ǲ��Ƕ�����������һ��һ����ж�
		return false;
	else if ((b->lchild == NULL) && (b->rchild == NULL))
		return true;
	else if (b->rchild == NULL &&b->lchild!=NULL&& b->lchild->data > b->data)//ֻ������
		return false;
	else if (b->lchild == NULL &&b->rchild!=NULL&& b->rchild->data < b->data)//ֻ������
		return false;
	else if (b->lchild->data > b->data || b->rchild->data < b->data)//������������ȥ�����������������Ƿ��Ƕ���������
		return false;
	else
		return isBalance_SearchTree(b->lchild) && isBalance_SearchTree(b->rchild);
}
*/

bool isAVL(BTNode* root, int& height)
{
	if (root == NULL)
	{
		//����
		height = 0;
		return true;
	}
	int heightLeft;
	bool resultLeft = isAVL(root->lchild, heightLeft);
	int heightRight;
	bool resultRight = isAVL(root->rchild, heightRight);

	//������������������AVL��,���Ҹ߶�������1.������
	if (resultLeft && resultRight && abs(heightLeft - heightRight) <= 1)
	{
		height = max(heightLeft, heightRight) + 1;
		return true;
	}
	else
	{
		height = max(heightLeft, heightRight) + 1;
		return false;
	}
}


int main()
{

	BTNode* a,*b,*c;
	char a1[] = { "5(4(2(,3),),7(6,8))" };
	char b1[] = { "5(2(1,4(3,)),6(,7))" };
	char c1[] = { "5(4(2(,3),),7(8,6))" };

	CreateBTree(a, a1);//����������
	CreateBTree(b, b1);//����ƽ��������
	CreateBTree(c, c1);//�Ƕ���������
	
	DispBTree(a);
	if (IsSearchTree(a)) {
		printf("�����Ƕ���������\n");
	}
	else printf("�������Ƕ���������\n");
	
	int height = 0;
	DispBTree(b);
	if (IsSearchTree(b)) {//����ƽ������������������:�Ƕ�������������ƽ����
		if (isAVL(b, height)) {
			printf("�����Ƕ���ƽ��������\n");
		}
	}
	else printf("�������Ƕ���ƽ��������\n");
	

	DispBTree(c);
	if (IsSearchTree(c)) {
		printf("�����Ƕ���������\n");
	}
	else printf("�������Ƕ���������\n");

	return 0;
}