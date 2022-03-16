#include <stdio.h>
#include<malloc.h>
#include<conio.h>
//������ʵ�ֶ���ʽ
typedef struct
{
    float coef;//ϵ��
    int expn;//ָ��
}ElemType;
typedef struct LNode
{
    ElemType data;
    struct LNode* next;
}LNode, LinkList;


void InitList(LinkList*& L)//��������
{

    L = (LinkList*)malloc(sizeof(LNode));
    L->next = NULL;

}
void InsLNode(LinkList*& L, ElemType x)//�������в���ڵ㣬��ʹ�ڵ����ݰ�ָ���Ӹߵ�������
{
    LinkList* s, * p;
    s = (LinkList*)malloc(sizeof(LNode));//�����½ڵ�
    s->data = x;
    p = L;

    //����ڵ㣬��ָ���Ӹߵ�������
	//���ҵ����һ�� ָ�����ڲ���Ľڵ�ָ���� �ڵ�
    while (p->next != NULL && p->next->data.expn > x.expn)
        p = p->next;
	//���������β�ڵ㣬��ô������һ���ڵ��ָ����ȻС�ڻ��ߵ����������ڵ��ָ��
    if (p->next != NULL) {
        if (p->next->data.expn == x.expn){//����Ľڵ�����еĽڵ��ָ����ͬ
            p->next->data.coef += x.coef;
			free(s);
		}
        else { //p->nxet->data.expn < x.expn
            s->next = p->next;
            p->next = s;
        }
    }
	//�������β��㣬ֱ�Ӳ���
    else {//p�������һ���ڵ�
        p->next = s;
        s->next = NULL;
    }
    //����������
}
void AddPolyn(LinkList* pa, LinkList* pb, LinkList*& pc)//����ʽ���
{
    LinkList * qa, * qb, * s, * rear;
    //pc�Ѿ�������ʼ��
    /*
    pc=(LinkList*)malloc(sizeof(LNode));
    pc->next=NULL;
    */
    //ʹ��β�巨
    rear = pc;//���Լ�Ҫ���صĶ���ʽ���

    qa = pa->next;//qaָ���һ������ʽ�ĵ�һ��Ԫ��
    qb = pb->next;//qbָ��ڶ�������ʽ�ĵ�һ��Ԫ��	

    while (qa != NULL && qb != NULL)
    {
        if (qa != NULL && qb != NULL && qa->data.expn < qb->data.expn)//��һ������ʽ��Ԫ�ص�ǰָ��С�ڵڶ�������ʽ��Ԫ�ص�ǰָ��
        {
            //����
            s = (LinkList*)malloc(sizeof(LNode));
            s->data.coef = qb->data.coef;
            s->data.expn = qb->data.expn;
            s->next = NULL;
            rear->next = s;
            rear = s;
            qb = qb->next;

        }

        if (qa != NULL && qb != NULL && qa->data.expn == qb->data.expn)//��һ������ʽ��Ԫ�ص�ǰָ�����ڵڶ�������ʽ��Ԫ�ص�ǰָ��
        {
            //����	
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
            //����	
            s = (LinkList*)malloc(sizeof(LNode));
            s->data.coef = qa->data.coef;
            s->data.expn = qa->data.expn;
            s->next = NULL;
            rear->next = s;
            rear = s;
            qa = qa->next;
        }
    }
    while (qb != NULL)//�ڶ�������ʽδ������
    {
        //����	
        s = (LinkList*)malloc(sizeof(LNode));
        s->data.coef = qb->data.coef;
        s->data.expn = qb->data.expn;
        s->next = NULL;
        rear->next = s;
        rear = s;
        qb = qb->next;
    }

    while (qa != NULL)//��һ������ʽδ������
    {
        //����
		s = (LinkList*)malloc(sizeof(LNode));
        s->data.coef = qa->data.coef;
        s->data.expn = qa->data.expn;
        s->next = NULL;
        rear->next = s;
        rear = s;
        qa = qa->next;
    }

}


void Print(LinkList* L)//�������ʽ
{
    LinkList* p;
    p = L->next;
    while (p->next != NULL)
    {
        printf("%fx^%d+", p->data.coef, p->data.expn);
        p = p->next;
    }
    //������һ��
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

    printf("����La������:");
    scanf("%d", &a);
    for (i = 0; i < a; i++)
    {
        printf("����La��%d��ϵ��:", i + 1);
        scanf("%f", &c.coef);
        printf("����La��%d��ָ��:", i + 1);
        scanf("%d", &c.expn);
        InsLNode(La, c);//���ú������������½ڵ㣬����ָ��������뵽���ʵ�λ��
    }

    printf("����Lb������:");
    scanf("%d", &a);
    for (i = 0; i < a; i++)
    {
        printf("����Lb�� %d��ϵ��:", i + 1);
        scanf("%f", &c.coef);
        printf("����Lb��%d��ָ��:", i + 1);
        scanf("%d", &c.expn);
        InsLNode(Lb, c);//���ú������������½ڵ㣬����ָ��������뵽���ʵ�λ��
    }

    printf("LaΪ"); printf("\n");
    Print(La); printf("\n");
    printf("LbΪ"); printf("\n");
    Print(Lb); printf("\n");

    printf("����ʽ��Ϊ"); printf("\n");

    AddPolyn(La, Lb, Lc);

    Print(Lc);
	printf("\n");
    return 0;
}
