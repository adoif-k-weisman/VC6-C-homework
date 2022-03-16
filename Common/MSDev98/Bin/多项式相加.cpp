#include <stdio.h>
#include<malloc.h>
#include<conio.h>
//单链表实现多项式
typedef struct
{
    float coef;//系数
    int expn;//指数
}ElemType;
typedef struct LNode
{
    ElemType data;
    struct LNode* next;
}LNode, LinkList;


void InitList(LinkList*& L)//创建链表
{

    L = (LinkList*)malloc(sizeof(LNode));
    L->next = NULL;

}
void InsLNode(LinkList*& L, ElemType x)//在链表中插入节点，并使节点数据按指数从高到低排序
{
    LinkList* s, * p;
    s = (LinkList*)malloc(sizeof(LNode));//生成新节点
    s->data = x;
    p = L;

    //插入节点，按指数从高到低排序
	//先找到最后一个 指数大于插入的节点指数的 节点
    while (p->next != NULL && p->next->data.expn > x.expn)
        p = p->next;
	//如果它不是尾节点，那么它的下一个节点的指数必然小于或者等于这个插入节点的指数
    if (p->next != NULL) {
        if (p->next->data.expn == x.expn){//插入的节点和已有的节点的指数相同
            p->next->data.coef += x.coef;
			free(s);
		}
        else { //p->nxet->data.expn < x.expn
            s->next = p->next;
            p->next = s;
        }
    }
	//如果它是尾结点，直接插入
    else {//p就是最后一个节点
        p->next = s;
        s->next = NULL;
    }
    //。。。。。
}
void AddPolyn(LinkList* pa, LinkList* pb, LinkList*& pc)//多项式相加
{
    LinkList * qa, * qb, * s, * rear;
    //pc已经经过初始化
    /*
    pc=(LinkList*)malloc(sizeof(LNode));
    pc->next=NULL;
    */
    //使用尾插法
    rear = pc;//我自己要返回的多项式结果

    qa = pa->next;//qa指向第一个多项式的第一个元素
    qb = pb->next;//qb指向第二个多项式的第一个元素	

    while (qa != NULL && qb != NULL)
    {
        if (qa != NULL && qb != NULL && qa->data.expn < qb->data.expn)//第一个多项式的元素当前指数小于第二个多项式的元素当前指数
        {
            //补充
            s = (LinkList*)malloc(sizeof(LNode));
            s->data.coef = qb->data.coef;
            s->data.expn = qb->data.expn;
            s->next = NULL;
            rear->next = s;
            rear = s;
            qb = qb->next;

        }

        if (qa != NULL && qb != NULL && qa->data.expn == qb->data.expn)//第一个多项式的元素当前指数等于第二个多项式的元素当前指数
        {
            //补充	
            s = (LinkList*)malloc(sizeof(LNode));
            s->data.coef = qb->data.coef + qa->data.coef;
            s->data.expn = qb->data.expn ;
            s->next = NULL;
            rear->next = s;
            rear = s;
            qb = qb->next;
            qa = qa->next;
        }


        if (qa != NULL && qb != NULL && qa->data.expn > qb->data.expn && qa != NULL && qb != NULL)
        {
            //补充	
            s = (LinkList*)malloc(sizeof(LNode));
            s->data.coef = qa->data.coef;
            s->data.expn = qa->data.expn;
            s->next = NULL;
            rear->next = s;
            rear = s;
            qa = qa->next;
        }
    }
    while (qb != NULL)//第二个多项式未遍历完
    {
        //补充	
        s = (LinkList*)malloc(sizeof(LNode));
        s->data.coef = qb->data.coef;
        s->data.expn = qb->data.expn;
        s->next = NULL;
        rear->next = s;
        rear = s;
        qb = qb->next;
    }

    while (qa != NULL)//第一个多项式未遍历完
    {
        //补充
		s = (LinkList*)malloc(sizeof(LNode));
        s->data.coef = qa->data.coef;
        s->data.expn = qa->data.expn;
        s->next = NULL;
        rear->next = s;
        rear = s;
        qa = qa->next;
    }

}


void Print(LinkList* L)//输出多项式
{
    LinkList* p;
    p = L->next;
    while (p->next != NULL)
    {
        printf("%fx^%d+", p->data.coef, p->data.expn);
        p = p->next;
    }
    //输出最后一项
    printf("%fx^%d", p->data.coef, p->data.expn);
}

int main()
{
    LinkList* La, * Lb, * Lc;

    ElemType c;

    int a, i;


    InitList(La);
    InitList(Lb);
    InitList(Lc);

    printf("输入La的项数:");
    scanf("%d", &a);
    for (i = 0; i < a; i++)
    {
        printf("输入La第%d项系数:", i + 1);
        scanf("%f", &c.coef);
        printf("输入La第%d项指数:", i + 1);
        scanf("%d", &c.expn);
        InsLNode(La, c);//调用函数，将生成新节点，并按指数有序插入到合适的位置
    }

    printf("输入Lb的项数:");
    scanf("%d", &a);
    for (i = 0; i < a; i++)
    {
        printf("输入Lb第 %d项系数:", i + 1);
        scanf("%f", &c.coef);
        printf("输入Lb第%d项指数:", i + 1);
        scanf("%d", &c.expn);
        InsLNode(Lb, c);//调用函数，将生成新节点，并按指数有序插入到合适的位置
    }

    printf("La为"); printf("\n");
    Print(La); printf("\n");
    printf("Lb为"); printf("\n");
    Print(Lb); printf("\n");

    printf("多项式和为"); printf("\n");

    AddPolyn(La, Lb, Lc);

    Print(Lc);
	printf("\n");
    return 0;
}
