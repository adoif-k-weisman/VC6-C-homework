//Լɪ��---ѡ����;
#include"stdio.h"
#include"malloc.h"
#include"stdlib.h"

struct node{
    int data;
    struct node *next;
};
int main()
{
    int n,m;
    int i;
    int answer[100];
    int count=0;
    struct node *head,*tail,*q,*p;//pָ��ǰ����Ľڵ㣬q����ָ��
    head=(struct node*)malloc(sizeof(struct node));
    head->data=-1;
    head->next=NULL;
    while(1){
        scanf("%d%d",&n,&m);
        if(n==0||m==0)
            free(head);
            break;
        else
        {
            tail=head;
            for(int i=0; i<n;i++){//����������
                //����β�巨��������tailβָ��;
                p=(struct node*)malloc(sizeof(struct node));
                p->data=i+1;
                tail->next=p;//�嵽β��;
                p->next=tail->next;//����next��ָ���һ����Ч�ڵ㣬�γ�ѭ������;
                tail=p;//tail�ƶ������һ���ڵ㣬Ϊ��һ�β�����׼��;
            }
            p=head->next;
            q=tail;
            i=1;
            while(p!=q){//p,q����һǰһ��һ��������������˵��ֻʣһ���ڵ���;
            if(i==m)
               { q->next=q->next->next;//q��pǰ��;
               //q->next=p->next;�ȼ���;
                free(p);
                i=1;
               }
            else
               {
                q=p;
                p=p->next;
                i++;
               }
            }
        //    head->next=q;���ֻʣ�����ڵ�ʱ��ɾ����һ���ڵ�ʱ���п�����������������ʼ��ϴ˾�;
            answer[count]=p->data;
            count++;
            free(p);
            head->next = NULL;
        }
    }
    for(i=0;i<count;i++)
        {
            printf("%d\n",answer[i]);
        }
//    free(head);
    return 0;
}