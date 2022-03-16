#include<iostream>
#include<cstdio>
using namespace std;
//二叉排序树算法
#include <stdio.h>
#include <malloc.h>
//typedef int ElemType;


#define MaxSize 100
typedef char ElemType;
typedef struct node
{
	ElemType data;			//数据元素
	struct node* lchild;	//指向左孩子节点
	struct node* rchild;	//指向右孩子节点
} BTNode;


void CreateBTree(BTNode*& b, const char* str)	//创建二叉树
{
	BTNode* St[MaxSize], * p = NULL;
	int top = -1, k, j = 0;
	char ch;
	b = NULL;				//建立的二叉树初始时为空
	ch = str[j];
	while (ch != '\0')  	//str未扫描完时循环
	{
		switch (ch)
		{
		case '(':top++; St[top] = p; k = 1; break;		//为左孩子节点
		case ')':top--; break;
		case ',':k = 2; break;                      		//为孩子节点右节点
		default:p = (BTNode*)malloc(sizeof(BTNode));
			p->data = ch;
			p->lchild = p->rchild = NULL;
			if (b == NULL)                    	 	//*p为二叉树的根节点
				b = p;
			else  								//已建立二叉树根节点
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
	if (b == NULL) return(0); 				//空树的高度为0
	else
	{
		lchildh = BTHeight(b->lchild);	//求左子树的高度为lchildh
		rchildh = BTHeight(b->rchild);	//求右子树的高度为rchildh
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
			printf("(");						//有孩子节点时才输出(
			DispBTree(b->lchild);				//递归处理左子树
			if (b->rchild != NULL) printf(",");	//有右孩子节点时才输出,
			DispBTree(b->rchild);				//递归处理右子树
			printf(")");						//有孩子节点时才输出)
		}
	}
}

//使用递归方式实现二分查找
int BinSearch(ElemType a[],int target,int left,int right)
{
	int mid = (left + right) >> 1;
	if (a[mid] == target)	return mid;
	else if (left >= right) return -1;
	else if (a[mid] < target) return BinSearch(a, target, mid + 1, right);
	else   return BinSearch(a, target, left, mid - 1);
}


//2、已知二叉树t，编写算法判断其是否是二叉排序树。
bool IsSearchTree(BTNode* b)
{
	if (b == NULL)
		return true;
	else if ((b->lchild == NULL) && (b->rchild == NULL))
		return true;
	else if (b->rchild==NULL) {//只有左树
		if (b->lchild->data > b->data)
			return false;
		else
			return IsSearchTree(b->lchild);
	}
	else if (b->lchild == NULL) {//只有右树
		if (b->rchild->data < b->data)
			return false;
		else
			return IsSearchTree(b->rchild);
	}
	else {//左右子树，再去看左子树、右子树是否是二叉排序树
		if ((b->lchild->data > b->data) || (b->rchild->data < b->data))
			return false;
		else
			return (IsSearchTree(b->lchild) && IsSearchTree(b->rchild));
	}	
}


//已知二叉树t，编写算法判断其是否是平衡二叉排序树。
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
	if (height_lr > 1 || height_lr < -1)//先判定它是不是平衡树，再判定它是不是二叉排序树，一层一层地判断
		return false;
	else if ((b->lchild == NULL) && (b->rchild == NULL))
		return true;
	else if (b->rchild == NULL &&b->lchild!=NULL&& b->lchild->data > b->data)//只有左树
		return false;
	else if (b->lchild == NULL &&b->rchild!=NULL&& b->rchild->data < b->data)//只有右树
		return false;
	else if (b->lchild->data > b->data || b->rchild->data < b->data)//左右子树，再去看左子树、右子树是否是二叉排序树
		return false;
	else
		return isBalance_SearchTree(b->lchild) && isBalance_SearchTree(b->rchild);
}
*/

bool isAVL(BTNode* root, int& height)
{
	if (root == NULL)
	{
		//空树
		height = 0;
		return true;
	}
	int heightLeft;
	bool resultLeft = isAVL(root->lchild, heightLeft);
	int heightRight;
	bool resultRight = isAVL(root->rchild, heightRight);

	//左子树和右子树都是AVL树,并且高度相差不大于1.返回真
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

	CreateBTree(a, a1);//二叉排序树
	CreateBTree(b, b1);//二叉平衡排序树
	CreateBTree(c, c1);//非二叉排序树
	
	DispBTree(a);
	if (IsSearchTree(a)) {
		printf("该树是二叉排序树\n");
	}
	else printf("该树不是二叉排序树\n");
	
	int height = 0;
	DispBTree(b);
	if (IsSearchTree(b)) {//二叉平衡排序树，二个条件:是二叉排序树，是平衡树
		if (isAVL(b, height)) {
			printf("该树是二叉平衡排序树\n");
		}
	}
	else printf("该树不是二叉平衡排序树\n");
	

	DispBTree(c);
	if (IsSearchTree(c)) {
		printf("该树是二叉排序树\n");
	}
	else printf("该树不是二叉排序树\n");

	return 0;
}