#include<stdio.h>
#include<stdlib.h>
#define LEN sizeof(List)

typedef struct ListNode
{
	int num;
	int data;
	struct ListNode *pri;
	struct ListNode *next;
}List;

List *create()
{
	List *head=NULL,*p,*tail,*pri;
	int num,data;
	scanf("%d%d",&num,&data);
	while(num!=0){
		p=(List *)malloc(LEN);
		p->num=num;
		p->data=data;
		if(head==NULL)
		{
			head=tail=pri=p;
			tail->next=NULL;
			tail->pri=NULL;
		}
		else
		{
			tail->next=p;
			tail=p;
			tail->next=NULL;
			tail->pri=pri;
			pri=p;
		}
		scanf("%d%d",&num,&data);
	}
	tail->next=head;
	head->pri=tail;
	return head;
}

void print(List *head)
{
	List *p=head;
	printf("num\tdata\n");
	while(p!=head->pri){
		printf("%d\t%d\n",p->num,p->data);
		p=p->next;
	}
	printf("%d\t%d\n",p->num,p->data);
}

void swap(List *p,List *q)
{
	List temp=*p;
	temp.next=q->next;
	temp.pri=q->pri;
	q->next=p->next;
	q->pri=p->pri;
	*p=*q;
	*q=temp;
}

void QuickSort(List *Left,List *Right)
{
	List *p=Left,*q=Right;
	if(Left != Right)
	{
		p=p->next;
		while( p != q ){
			if(p->data > Left->data)
			{
				swap(p,q);
				q=q->pri;
			}
			else
				p=p->next;
		}

		if(p->data > Left->data)
			p=p->pri;

		swap(p,Left);
		QuickSort(Left,p);
		QuickSort(q,Right);
	}
}

int main()
{
	List *L;
	L=create();
	QuickSort(L,L->pri);
	print(L);
	return 0;
}
