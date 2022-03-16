//约瑟夫环---选猴王;
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
    struct node *head,*tail,*q,*p;//p指向当前处理的节点，q总是指向
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
            for(int i=0; i<n;i++){//填入猴子序号
                //采用尾插法构建链表，tail尾指针;
                p=(struct node*)malloc(sizeof(struct node));
                p->data=i+1;
                tail->next=p;//插到尾部;
                p->next=tail->next;//最后的next域指向第一个有效节点，形成循环链表;
                tail=p;//tail移动到最后一个节点，为下一次插入做准备;
            }
            p=head->next;
            q=tail;
            i=1;
            while(p!=q){//p,q总是一前一后，一旦他们相遇，则说明只剩一个节点了;
            if(i==m)
               { q->next=q->next->next;//q在p前面;
               //q->next=p->next;等价于;
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
        //    head->next=q;最后只剩二个节点时，删除第一个节点时，有可能造成链表不完整，故加上此句;
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