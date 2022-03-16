#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int local;
    struct node * next;
}LNode,*LinkList;

void CreateLinkList_L(LinkList L,int n);
void Josephus(LinkList L,int n,int m,int k);

void main()
{
    //创建循环单链表 结点个数是 n
    //报数 报到m的出去  也就是 删除该结点
    LinkList L = (LinkList)malloc(sizeof(LNode));
    L->local = 1;
    CreateLinkList_L(L,10);
    Josephus(L,10,4,3);
}

void CreateLinkList_L(LinkList L,int n)
{
    int i;
    LinkList s,r;
    r = L;

    for(i = 2;i <= n;i++)
    {
        s = (LinkList)malloc(sizeof(LNode));
        s->local = i;
        r->next = s;
        r = r->next;
    }
    r->next = L;
}

void Josephus(LinkList L,int n,int m,int k) //m = 3 , k = 2
{
    int i = 1,j = 1;

    LinkList p,q,s;
    p = L;
    //确定第一个喊话的同学
    while(i < k)
    {
        q = p;
        p = p->next;
        i++;
    }
    while(p->next != p)
    {

        //一个循环用来喊话，一直喊m次
        while(j < m)
        {
            q = p;
            p = p->next;
            j++;
        }
        s = p;
        p = p->next;
        q->next = p;
        printf("%d号淘汰！\n",s->local);
        free(s);
        j = 1;
    }

    printf("%d胜出！",p->local);
}


