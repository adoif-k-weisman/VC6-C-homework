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
    //����ѭ�������� �������� n
    //���� ����m�ĳ�ȥ  Ҳ���� ɾ���ý��
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
    //ȷ����һ��������ͬѧ
    while(i < k)
    {
        q = p;
        p = p->next;
        i++;
    }
    while(p->next != p)
    {

        //һ��ѭ������������һֱ��m��
        while(j < m)
        {
            q = p;
            p = p->next;
            j++;
        }
        s = p;
        p = p->next;
        q->next = p;
        printf("%d����̭��\n",s->local);
        free(s);
        j = 1;
    }

    printf("%dʤ����",p->local);
}


