//��������������㷨
#include <stdio.h>
#include <malloc.h>
typedef int ElemType;
typedef struct LinkNode  
{
	ElemType data;
	LinkNode *next;		//ָ���̽��
} LinkNode;					//����������������
void swap(LinkNode *&p,LinkNode*& q)
{
    ElemType temp = p->data;
    p->data = q->data;
    q->data = temp;
}

void CreateListF(LinkNode *&L,ElemType a[],int n)
//ͷ�巨����������
{
	LinkNode *s;
	L=(LinkNode *)malloc(sizeof(LinkNode));  	//����ͷ���
	L->next=NULL;
	for (int i=0;i<n;i++)
	{	
		s=(LinkNode *)malloc(sizeof(LinkNode));//�����½��s
		s->data=a[i];
		s->next=L->next;			//�����s����ԭ��ʼ���֮ǰ,ͷ���֮��
		L->next=s;
	}
}
void CreateListR(LinkNode *&L,ElemType a[],int n)
//β�巨����������
{
	LinkNode *s,*r;
	L=(LinkNode *)malloc(sizeof(LinkNode));  	//����ͷ���
	L->next=NULL;
	r=L;					//rʼ��ָ���ն˽��,��ʼʱָ��ͷ���
	for (int i=0;i<n;i++)
	{	
		s=(LinkNode *)malloc(sizeof(LinkNode));//�����½��s
		s->data=a[i];
		r->next=s;			//�����s������r֮��
		r=s;
	}
	r->next=NULL;			//�ն˽��next����ΪNULL
}
void InitList(LinkNode *&L)
{
	L=(LinkNode *)malloc(sizeof(LinkNode));  	//����ͷ���
	L->next=NULL;
}
void DestroyList(LinkNode *&L)
{
	LinkNode *pre=L,*p=pre->next;
	while (p!=NULL)
	{	free(pre);
		pre=p;
		p=pre->next;
	}
	free(pre);	//��ʱpΪNULL,preָ��β���,�ͷ���
}
bool ListEmpty(LinkNode *L)
{
	return(L->next==NULL);
}
int ListLength(LinkNode *L)
{
	LinkNode *p=L;int i=0;
	while (p->next!=NULL)
	{	i++;
		p=p->next;
	}
	return(i);
}
void DispList(LinkNode *L)
{
	LinkNode *p=L->next;
	while (p!=NULL)
	{	printf("%d ",p->data);
		p=p->next;
	}
	printf("\n");
}
bool GetElem(LinkNode *L,int i,ElemType &e)//�ҵ���i��Ԫ��
{
	int j=0;
	LinkNode *p=L;
	if (i<=0) return false;		//i���󷵻ؼ�
	while (j<i && p!=NULL)
	{	j++;
		p=p->next;
	}
	if (p==NULL)				//�����ڵ�i�����ݽ��
		return false;
	else						//���ڵ�i�����ݽ��
	{	e=p->data;
		return true;
	}
}
int LocateElem(LinkNode *L,ElemType e)//��λֵΪe�����ݽڵ�
{
	LinkNode *p=L->next;
	int n=1;
	while (p!=NULL && p->data!=e)
	{	p=p->next;
		n++;
	}
	if (p==NULL)
		return(0);
	else
		return(n);
}
bool ListInsert(LinkNode *&L,int i,ElemType e)//�ڵ�i��λ�ò���Ԫ��e
{
	int j=0;
	LinkNode *p=L,*s;
	if (i<=0) return false;			//i���󷵻ؼ�
	while (j<i-1 && p!=NULL)		//���ҵ�i-1�����p
	{	j++;
		p=p->next;
	}
	if (p==NULL)					//δ�ҵ�λ��Ϊi-1�Ľ��
		return false;
	else							//�ҵ�λ��Ϊi-1�Ľ��*p
	{	s=(LinkNode *)malloc(sizeof(LinkNode));//�����½��*s
		s->data=e;
		s->next=p->next;			//��s�����뵽���p֮��
		p->next=s;
		return true;
	}
}
//========================================================================================
//6������������L����һ��ֵΪe��Ԫ�أ�ʹ��������
void ListInsertOrder(LinkNode*& L,ElemType e)//�ٶ��õ������������
{
    LinkNode* pre = L,*q;
    while(pre->next!=NULL && pre->next->data < e)
        pre = pre->next;
    q=(LinkNode*) malloc(sizeof(LinkNode));
    q->data = e;
    q->next=pre->next;
    pre->next = q;
}
//7��ɾ����������L������ֵΪe��Ԫ�ء�
bool ListDeleteElem(LinkNode*&L,ElemType e)
{
    LinkNode *pre=L,*q;
    while(pre->next!=NULL&& pre->next->data<e)
        pre = pre->next;
    //�ҵ�Ҫɾ���ڵ��ǰһ���ڵ�
    if(pre->next->data != e)
    {
        printf("��������û��%dԪ��\n",e);
        return true;
    }
    else{
        q=pre->next;
        while(q->data==e){
            pre->next = q->next;//ָ��Ҫɾ���ڵ����һ���ڵ�
            free(q);//ɾ���ýڵ�
            q = pre->next;//ָ����һ���ڵ�
        }
           return true;
    }
}

//8������������L��ֵΪeԪ���޸�ֵΪe1��ʹ��������
bool ListChangeElem(LinkNode*& L,ElemType e,ElemType e1)
{
    LinkNode *pre=L,*q,*rea;
    while(pre->next!=NULL&&pre->next->data!=e)
        pre=pre->next;
    q=pre->next;
    if(q->data != e){
        printf("��������û��ֵΪ%d�Ľڵ�\n",e);
        return false;
    }
    else{
        q->data = e1;
        if(e1>e){
        rea=q;
        while(rea->next!=NULL && rea->next->data <e1){
            rea = rea->next;
        }
            //���Ľڵ�next��ϵ
        pre->next = q->next;
        q->next = rea->next;
        rea->next = q;
        return true;
        }
        else if(e1==e)
            return true;
        else{//�����Ԫ��С��ԭ����Ԫ��,�޸�λ����ǰ
            pre->next =q->next;//�Ͽ�������q
            pre = L;
            while(pre->next!=NULL && pre->next->data < e1)
                pre = pre->next;
            q->next = pre->next;
            pre->next = q;
            return true;
        }
    }
}
//9������������L����������[low,high]������ȡ�������µ���������L1��
//Ĭ�ϸõ��������
void CreateNewList(ElemType low ,ElemType high ,LinkNode *&L ,LinkNode *&L1)
{
    //ע�ⲻҪ���˳�ʼ��L1,L1������ֻ��һ����ָ��
    L1 = (LinkNode*)malloc(sizeof(LinkNode));
    L1->next = NULL;

    LinkNode *p1=L,*Lp,*Hp;
    while(p1->next!=NULL && p1->next->data < low)
            p1=p1->next;//�ҵ���lowС�����һ���ڵ�
    Lp = p1->next;//low���俪ʼ�ķ�Χ
    Hp=p1->next;
    while(Hp->next!=NULL && Hp->next->data <= high)
        Hp=Hp->next;//Hp��Ϊ[low,high]����Ľ�����
    //��һ���汾,�µ����������ǿյ�,ʹ��β�巨    
    LinkNode *s,*r;
	r=L1;					//rʼ��ָ���ն˽��,��ʼʱָ��ͷ���
    while(Lp!=Hp->next){
		s=(LinkNode *)malloc(sizeof(LinkNode));//�����½��s
		s->data=Lp->data;
		r->next=s;			//�����s������r֮��
		r=s;
	    r->next=NULL;			//�ն˽��next����ΪNULL
        Lp=Lp->next;
    }
    //�ڶ����汾,���������Ϊ��,��ֱ�ӵ���ǰ���������뺯��
}
//10����������L1����������L2�ֱ�洢��������A��B�����ù鲢���ֱ�����������ϵĲ����������Ͳ��
//���Ҫ������������������������ʹ���L3,L4,L5
//�:ֻ����һ�����ϵ�Ԫ��

//�󲢼�
void Union(LinkNode* L1, LinkNode* L2, LinkNode*& L3)//�������򼯺�L1��L2�Ĳ���L3��
{
    LinkNode* p1, * p2, * p3,*s;
    L3 = (LinkNode*)malloc(sizeof(LinkNode));
    L3->next = NULL;
    p3 = L3;
    p1 = L1->next; p2 = L2->next;
    while (p1 && p2) {
        //˭С�Ȳ���˭������
        if (p1->data < p2->data) {
            s = (LinkNode*)malloc(sizeof(LinkNode));
            s->data = p1->data;
            s->next = NULL;
            //ʹ��β�巨
            p3->next = s; p3 = s; p1 = p1->next;
        }
        else if (p1->data > p2->data) {//����С��p2
            s = (LinkNode*)malloc(sizeof(LinkNode));
            s->data = p2->data;
            s->next = NULL;
            p3->next = s; p3 = s; p2 = p2->next;
        }
        else {//p1=p2,��㱣��p1,p2�е�һ������
            s = (LinkNode*)malloc(sizeof(LinkNode));
            s->data = p1->data;
            s->next = NULL;
            p3->next = s; p3 = s;
            p1 = p1->next; p2 = p2->next;
        }
    }
    //β�巨����ʣ�µ�Ԫ��
    while (p1) {
        s = (LinkNode*)malloc(sizeof(LinkNode));
        s->data = p1->data;
        s->next = NULL;
        p3->next = s; p3 = s;
        p1 = p1->next; 

   }
    while (p2) {
        s = (LinkNode*)malloc(sizeof(LinkNode));
        s->data =p2->data;
        s->next = NULL;
        p3->next = s; p3 = s;
        p2= p2->next;
    }

}
void InterSect(LinkNode* L1, LinkNode* L2, LinkNode*& L3)//�������򼯺�L1��L2�ĵĽ���L3��
{
    LinkNode* p1, * p2, * p3,*s;
    L3 = (LinkNode*)malloc(sizeof(LinkNode));
    L3->next = NULL;
    p3 = L3;
    p1 = L1->next; p2 = L2->next;
//����β�巨��������������
    while (p1 && p2) {
        if (p1->data < p2->data) {
             p1= p1->next;
        }
        else if (p1->data > p2->data) {
            p2 = p2->next;
        }
        else {//p1->data = p2->data ������ 
            s = (LinkNode*)malloc(sizeof(LinkNode));
            s->data = p1->data;
            s->next = NULL;
            p3->next = s; p3 = s;
            p1= p1->next; p2 = p2->next;
        }
    }
}
void Subs(LinkNode* L1, LinkNode* L2, LinkNode*& L3)//�������򼯺�L1��L2�ĲL3��L3 = L1-L2
{
    LinkNode* p1, * p2, * p3, * s;
    L3 = (LinkNode*)malloc(sizeof(LinkNode));
    L3->next = NULL;
    p3 = L3;
    p1 = L1->next; p2 = L2->next;

    while (p1 && p2) {//�����A-B���ϵĲ
        if (p1->data < p2->data) {
            s = (LinkNode*)malloc(sizeof(LinkNode));
            s->data = p1->data;
            s->next = NULL;
            p3->next = s; p3 = s; p1= p1->next;
        }
        else if (p1->data > p2->data) {
            p2 = p2->next;

        }
        else {//p1->data == L2->data
            p1= p1->next; p2 = p2->next;
        }
    }
    while (p1) {
        s = (LinkNode*)malloc(sizeof(LinkNode));
        s->data = p1->data;
        s->next = NULL;
        p3->next = s; p3 = s;
        p1 = p1->next;
    }
}
//ʵ�ֿ��ŵ������,�����õ������Ϊ�����
LinkNode* getPartition(LinkNode* pBegin,LinkNode* pEnd)
{
    ElemType key = pBegin->data;
    LinkNode *p=pBegin,*q=p->next;
    while(q!=pEnd){
        if(q->data < key){
            p=p->next;
            swap(p,q);//ֻ�ǽ���p,qָ���data����
        }
        q=q->next;
    }
    swap(pBegin,p);
    return p;
}
void QuickSort(LinkNode* pBegin,LinkNode* pEnd)
{
    if(pBegin!=pEnd){
        LinkNode* partition = getPartition(pBegin,pEnd);
        QuickSort(pBegin,partition);
        QuickSort(partition->next,pEnd);
    }
}

bool ListDelete(LinkNode *&L,int i,ElemType &e)//ɾ����i������
{
	int j=0;
	LinkNode *p=L,*q;
	if (i<=0) return false;		//i���󷵻ؼ�
	while (j<i-1 && p!=NULL)	//���ҵ�i-1�����
	{	j++;
		p=p->next;
	}
	if (p==NULL)				//δ�ҵ�λ��Ϊi-1�Ľ��
		return false;
	else						//�ҵ�λ��Ϊi-1�Ľ��p
	{	q=p->next;				//qָ��Ҫɾ���Ľ��
		if (q==NULL) 
			return false;		//�������ڵ�i�����,����false
		e=q->data;
		p->next=q->next;		//�ӵ�������ɾ��q���
		free(q);				//�ͷ�q���
		return true;
	}
}

int main()
{
    LinkNode* L,*L1,*L2,*L3,*L4;
    //InitList(L);//��ʼ����������L
    //����һ����������L�����һ���������������һ������������������Ե���������
    ElemType a[] = {1,2,3,4,5,6,7,8,9};
    CreateListR(L,a,9);
    ElemType b[] = {1,3,5,6,7,8,9,10,15,17,19};
    ElemType c[] = {1,2,3,4,5,6,7,9,11,15,16};
    /*
    ElemType d[] = {3,5,1,9,0,13,66,45,32,11,99};
    CreateListR(L4,d,11);
    printf("ʵ���ҵĿ���:\n");
    QuickSort(L4->next,NULL);//successful 
    DispList(L4);
    DestroyList(L4);
    */
    CreateListR(L1,b,11);
    CreateListR(L2,c,11);

	printf("������L:\n");
	DispList(L);
//����������L�ĳ��ȡ�
    printf("the length of list is %d\n",ListLength(L));

//��������L��ȡ����i��Ԫ�ء�
    ElemType e;

    GetElem(L,5,e);
    printf("the fifth elem of list is %d\n",e);

//��λ������ȷ����������LֵΪeԪ�ص�λ�á�
    printf("the loaction of 7 is %d \n",LocateElem(L,7));

//����������L����һ��ֵΪe��Ԫ�أ�ʹ��������
    printf("����Ԫ��5��ĵ�����:\n");
    ListInsertOrder(L,5);
    DispList(L);
//ɾ����������L������ֵΪe��Ԫ�ء�
bool flag = ListDeleteElem(L,5);
    if(flag) printf("ɾ������Ԫ��'5'�ɹ�!\n");
    else printf("δ�ܳɹ�ɾ��Ԫ��'5'\n");
    DispList(L);
//����������L��ֵΪeԪ���޸�ֵΪe1��ʹ��������
    ListChangeElem(L,7,0);
    printf("change the 7 to 0 :\n");
    DispList(L);
    ListChangeElem(L,2,11);
    printf("change the 2 to 11:\n");
    DispList(L);
//����������L����������[low,high]������ȡ�������µ���������L1��
    CreateNewList(1,7,L,L3);
    printf("ȡ������[1,7]��Ԫ�ص�L3:\n");
    DispList(L3);
    DestroyList(L3);

//��������LA����������LB�ֱ�洢��������A��B�����ù鲢���ֱ�����������ϵĲ����������Ͳ��
	printf("������L1:\n");
	DispList(L1);
	printf("������L2:\n");
	DispList(L2);
    //����:
    Union(L1,L2,L3);
    printf("L1 �� L2�Ĳ���:\n");
    DispList(L3);
    DestroyList(L3);
    //����:
    InterSect(L1,L2,L3);
    printf("L1 �� L2�Ľ���:\n");
    DispList(L3);
    DestroyList(L3);    
    //�:
    Subs(L1,L2,L3);
    printf("L1 �� L2�Ĳ:\n");
    DispList(L3);
    DestroyList(L3);
    return 0;
}
