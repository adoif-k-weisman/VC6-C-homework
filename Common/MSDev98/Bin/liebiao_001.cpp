
#include <stdafx.h>
#include <stdio.h>  
#include <malloc.h>  

struct plist {//�����б�ṹ��
    int A[1000];
    int n;
};
void List_Init(plist *list);
void List_Append(plist* list, int value);
void List_Show(plist *list);
void List_Insert(plist *list, int index, int value);


void List_Init(plist *list) { //��ʼ�б�
    list->n = 0;
}

void List_Append(plist* list, int value) { //�ο�python�е�append()����
    list->A[list->n++] = value;
}

void List_Insert(plist *list, int index, int value) { //������ĳ��λ�ò���ֵ���±��0��ʼ
    for (int i = list->n - 1; i >= index; i--) {
        list->A[i + 1] = list->A[i];
    }
    list->A[index] = value;
    list->n++;
}

void List_Show(plist *list) { //��ӡ�б�
    printf("len=%d values=", list->n);
    for (int i = 0; i < list->n; ++i)
    {
        printf("%d ", list->A[i]);
    }
    printf("\n");
}

int main() {
    plist* P_List = (plist*)malloc(sizeof(plist));
    List_Init(P_List);
    List_Append(P_List, 123);
    List_Append(P_List, 456);
    List_Append(P_List, 789);
    List_Show(P_List);
    List_Insert(P_List, 1, 666);
    List_Show(P_List);
    getchar(); //visual studio 2017 ���һ��������ֻ��������
}