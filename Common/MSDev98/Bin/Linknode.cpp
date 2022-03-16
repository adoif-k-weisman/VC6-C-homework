//单链表基本运算算法
#include <stdio.h>
#include <malloc.h>
typedef int ElemType;
typedef struct LinkNode  
{
	ElemType data;
	LinkNode *next;		//指向后继结点
} LinkNode;					//声明单链表结点类型
void swap(LinkNode *&p,LinkNode*& q)
{
    ElemType temp = p->data;
    p->data = q->data;
    q->data = temp;
}

void CreateListF(LinkNode *&L,ElemType a[],int n)
//头插法建立单链表
{
	LinkNode *s;
	L=(LinkNode *)malloc(sizeof(LinkNode));  	//创建头结点
	L->next=NULL;
	for (int i=0;i<n;i++)
	{	
		s=(LinkNode *)malloc(sizeof(LinkNode));//创建新结点s
		s->data=a[i];
		s->next=L->next;			//将结点s插在原开始结点之前,头结点之后
		L->next=s;
	}
}
void CreateListR(LinkNode *&L,ElemType a[],int n)
//尾插法建立单链表
{
	LinkNode *s,*r;
	L=(LinkNode *)malloc(sizeof(LinkNode));  	//创建头结点
	L->next=NULL;
	r=L;					//r始终指向终端结点,开始时指向头结点
	for (int i=0;i<n;i++)
	{	
		s=(LinkNode *)malloc(sizeof(LinkNode));//创建新结点s
		s->data=a[i];
		r->next=s;			//将结点s插入结点r之后
		r=s;
	}
	r->next=NULL;			//终端结点next域置为NULL
}
void InitList(LinkNode *&L)
{
	L=(LinkNode *)malloc(sizeof(LinkNode));  	//创建头结点
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
	free(pre);	//此时p为NULL,pre指向尾结点,释放它
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
bool GetElem(LinkNode *L,int i,ElemType &e)//找到第i个元素
{
	int j=0;
	LinkNode *p=L;
	if (i<=0) return false;		//i错误返回假
	while (j<i && p!=NULL)
	{	j++;
		p=p->next;
	}
	if (p==NULL)				//不存在第i个数据结点
		return false;
	else						//存在第i个数据结点
	{	e=p->data;
		return true;
	}
}
int LocateElem(LinkNode *L,ElemType e)//定位值为e的数据节点
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
bool ListInsert(LinkNode *&L,int i,ElemType e)//在第i个位置插入元素e
{
	int j=0;
	LinkNode *p=L,*s;
	if (i<=0) return false;			//i错误返回假
	while (j<i-1 && p!=NULL)		//查找第i-1个结点p
	{	j++;
		p=p->next;
	}
	if (p==NULL)					//未找到位序为i-1的结点
		return false;
	else							//找到位序为i-1的结点*p
	{	s=(LinkNode *)malloc(sizeof(LinkNode));//创建新结点*s
		s->data=e;
		s->next=p->next;			//将s结点插入到结点p之后
		p->next=s;
		return true;
	}
}
//========================================================================================
//6）在有序单链表L插入一个值为e的元素，使其仍有序。
void ListInsertOrder(LinkNode*& L,ElemType e)//假定该单链表递增有序
{
    LinkNode* pre = L,*q;
    while(pre->next!=NULL && pre->next->data < e)
        pre = pre->next;
    q=(LinkNode*) malloc(sizeof(LinkNode));
    q->data = e;
    q->next=pre->next;
    pre->next = q;
}
//7）删除有序单链表L中所有值为e的元素。
bool ListDeleteElem(LinkNode*&L,ElemType e)
{
    LinkNode *pre=L,*q;
    while(pre->next!=NULL&& pre->next->data<e)
        pre = pre->next;
    //找到要删除节点的前一个节点
    if(pre->next->data != e)
    {
        printf("该链表中没有%d元素\n",e);
        return true;
    }
    else{
        q=pre->next;
        while(q->data==e){
            pre->next = q->next;//指向要删除节点的下一个节点
            free(q);//删除该节点
            q = pre->next;//指向下一个节点
        }
           return true;
    }
}

//8）将有序单链表L中值为e元素修改值为e1，使其仍有序。
bool ListChangeElem(LinkNode*& L,ElemType e,ElemType e1)
{
    LinkNode *pre=L,*q,*rea;
    while(pre->next!=NULL&&pre->next->data!=e)
        pre=pre->next;
    q=pre->next;
    if(q->data != e){
        printf("该链表中没有值为%d的节点\n",e);
        return false;
    }
    else{
        q->data = e1;
        if(e1>e){
        rea=q;
        while(rea->next!=NULL && rea->next->data <e1){
            rea = rea->next;
        }
            //更改节点next关系
        pre->next = q->next;
        q->next = rea->next;
        rea->next = q;
        return true;
        }
        else if(e1==e)
            return true;
        else{//插入的元素小于原来的元素,修改位置往前
            pre->next =q->next;//断开链表与q
            pre = L;
            while(pre->next!=NULL && pre->next->data < e1)
                pre = pre->next;
            q->next = pre->next;
            pre->next = q;
            return true;
        }
    }
}
//9）将有序单链表L中属于区间[low,high]的数据取出存入新的有序单链表L1。
//默认该单链表递增
void CreateNewList(ElemType low ,ElemType high ,LinkNode *&L ,LinkNode *&L1)
{
    //注意不要忘了初始化L1,L1传进来只是一个空指针
    L1 = (LinkNode*)malloc(sizeof(LinkNode));
    L1->next = NULL;

    LinkNode *p1=L,*Lp,*Hp;
    while(p1->next!=NULL && p1->next->data < low)
            p1=p1->next;//找到比low小的最后一个节点
    Lp = p1->next;//low区间开始的范围
    Hp=p1->next;
    while(Hp->next!=NULL && Hp->next->data <= high)
        Hp=Hp->next;//Hp即为[low,high]区间的结束点
    //第一个版本,新的有序单链表是空的,使用尾插法    
    LinkNode *s,*r;
	r=L1;					//r始终指向终端结点,开始时指向头结点
    while(Lp!=Hp->next){
		s=(LinkNode *)malloc(sizeof(LinkNode));//创建新结点s
		s->data=Lp->data;
		r->next=s;			//将结点s插入结点r之后
		r=s;
	    r->next=NULL;			//终端结点next域置为NULL
        Lp=Lp->next;
    }
    //第二个版本,如果单链表不为空,就直接调用前面的有序插入函数
}
//10）有序单链表L1和有序单链表L2分别存储两个集合A和B，利用归并法分别求出两个集合的并集、交集和差集。
//如果要并集，交集，差集的链表结果，就传给L3,L4,L5
//差集:只属于一个集合的元素

//求并集
void Union(LinkNode* L1, LinkNode* L2, LinkNode*& L3)//求两有序集合L1、L2的并集L3。
{
    LinkNode* p1, * p2, * p3,*s;
    L3 = (LinkNode*)malloc(sizeof(LinkNode));
    L3->next = NULL;
    p3 = L3;
    p1 = L1->next; p2 = L2->next;
    while (p1 && p2) {
        //谁小先插入谁的数据
        if (p1->data < p2->data) {
            s = (LinkNode*)malloc(sizeof(LinkNode));
            s->data = p1->data;
            s->next = NULL;
            //使用尾插法
            p3->next = s; p3 = s; p1 = p1->next;
        }
        else if (p1->data > p2->data) {//保存小的p2
            s = (LinkNode*)malloc(sizeof(LinkNode));
            s->data = p2->data;
            s->next = NULL;
            p3->next = s; p3 = s; p2 = p2->next;
        }
        else {//p1=p2,随便保存p1,p2中的一个数据
            s = (LinkNode*)malloc(sizeof(LinkNode));
            s->data = p1->data;
            s->next = NULL;
            p3->next = s; p3 = s;
            p1 = p1->next; p2 = p2->next;
        }
    }
    //尾插法插入剩下的元素
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
void InterSect(LinkNode* L1, LinkNode* L2, LinkNode*& L3)//求两有序集合L1、L2的的交集L3。
{
    LinkNode* p1, * p2, * p3,*s;
    L3 = (LinkNode*)malloc(sizeof(LinkNode));
    L3->next = NULL;
    p3 = L3;
    p1 = L1->next; p2 = L2->next;
//继续尾插法，建立有序单链表
    while (p1 && p2) {
        if (p1->data < p2->data) {
             p1= p1->next;
        }
        else if (p1->data > p2->data) {
            p2 = p2->next;
        }
        else {//p1->data = p2->data ，交集 
            s = (LinkNode*)malloc(sizeof(LinkNode));
            s->data = p1->data;
            s->next = NULL;
            p3->next = s; p3 = s;
            p1= p1->next; p2 = p2->next;
        }
    }
}
void Subs(LinkNode* L1, LinkNode* L2, LinkNode*& L3)//求两有序集合L1、L2的差集L3。L3 = L1-L2
{
    LinkNode* p1, * p2, * p3, * s;
    L3 = (LinkNode*)malloc(sizeof(LinkNode));
    L3->next = NULL;
    p3 = L3;
    p1 = L1->next; p2 = L2->next;

    while (p1 && p2) {//求的是A-B集合的差集
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
//实现快排单链表版,用于让单链表成为有序表
LinkNode* getPartition(LinkNode* pBegin,LinkNode* pEnd)
{
    ElemType key = pBegin->data;
    LinkNode *p=pBegin,*q=p->next;
    while(q!=pEnd){
        if(q->data < key){
            p=p->next;
            swap(p,q);//只是交换p,q指向的data数据
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

bool ListDelete(LinkNode *&L,int i,ElemType &e)//删除第i个数据
{
	int j=0;
	LinkNode *p=L,*q;
	if (i<=0) return false;		//i错误返回假
	while (j<i-1 && p!=NULL)	//查找第i-1个结点
	{	j++;
		p=p->next;
	}
	if (p==NULL)				//未找到位序为i-1的结点
		return false;
	else						//找到位序为i-1的结点p
	{	q=p->next;				//q指向要删除的结点
		if (q==NULL) 
			return false;		//若不存在第i个结点,返回false
		e=q->data;
		p->next=q->next;		//从单链表中删除q结点
		free(q);				//释放q结点
		return true;
	}
}

int main()
{
    LinkNode* L,*L1,*L2,*L3,*L4;
    //InitList(L);//初始化有序单链表L
    //建立一个有序单链表L。存放一组有序数，或产生一组随机数建立单链表并对单链表排序。
    ElemType a[] = {1,2,3,4,5,6,7,8,9};
    CreateListR(L,a,9);
    ElemType b[] = {1,3,5,6,7,8,9,10,15,17,19};
    ElemType c[] = {1,2,3,4,5,6,7,9,11,15,16};
    /*
    ElemType d[] = {3,5,1,9,0,13,66,45,32,11,99};
    CreateListR(L4,d,11);
    printf("实验我的快排:\n");
    QuickSort(L4->next,NULL);//successful 
    DispList(L4);
    DestroyList(L4);
    */
    CreateListR(L1,b,11);
    CreateListR(L2,c,11);

	printf("单链表L:\n");
	DispList(L);
//求有序单链表L的长度。
    printf("the length of list is %d\n",ListLength(L));

//有序单链表L中取出第i个元素。
    ElemType e;

    GetElem(L,5,e);
    printf("the fifth elem of list is %d\n",e);

//定位函数，确定有序单链表L值为e元素的位置。
    printf("the loaction of 7 is %d \n",LocateElem(L,7));

//在有序单链表L插入一个值为e的元素，使其仍有序。
    printf("插入元素5后的单链表:\n");
    ListInsertOrder(L,5);
    DispList(L);
//删除有序单链表L中所有值为e的元素。
bool flag = ListDeleteElem(L,5);
    if(flag) printf("删除所有元素'5'成功!\n");
    else printf("未能成功删除元素'5'\n");
    DispList(L);
//将有序单链表L中值为e元素修改值为e1，使其仍有序。
    ListChangeElem(L,7,0);
    printf("change the 7 to 0 :\n");
    DispList(L);
    ListChangeElem(L,2,11);
    printf("change the 2 to 11:\n");
    DispList(L);
//将有序单链表L中属于区间[low,high]的数据取出存入新的有序单链表L1。
    CreateNewList(1,7,L,L3);
    printf("取出区间[1,7]的元素到L3:\n");
    DispList(L3);
    DestroyList(L3);

//有序单链表LA和有序单链表LB分别存储两个集合A和B，利用归并法分别求出两个集合的并集、交集和差集。
	printf("单链表L1:\n");
	DispList(L1);
	printf("单链表L2:\n");
	DispList(L2);
    //并集:
    Union(L1,L2,L3);
    printf("L1 和 L2的并集:\n");
    DispList(L3);
    DestroyList(L3);
    //交集:
    InterSect(L1,L2,L3);
    printf("L1 和 L2的交集:\n");
    DispList(L3);
    DestroyList(L3);    
    //差集:
    Subs(L1,L2,L3);
    printf("L1 和 L2的差集:\n");
    DispList(L3);
    DestroyList(L3);
    return 0;
}
