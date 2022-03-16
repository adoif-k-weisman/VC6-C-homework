
#include <stdafx.h>
#include <stdio.h>  
#include <malloc.h>  

struct plist {//定义列表结构体
    int A[1000];
    int n;
};
void List_Init(plist *list);
void List_Append(plist* list, int value);
void List_Show(plist *list);
void List_Insert(plist *list, int index, int value);


void List_Init(plist *list) { //初始列表
    list->n = 0;
}

void List_Append(plist* list, int value) { //参考python中的append()函数
    list->A[list->n++] = value;
}

void List_Insert(plist *list, int index, int value) { //插入在某个位置插入值，下标从0开始
    for (int i = list->n - 1; i >= index; i--) {
        list->A[i + 1] = list->A[i];
    }
    list->A[index] = value;
    list->n++;
}

void List_Show(plist *list) { //打印列表
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
    getchar(); //visual studio 2017 输出一闪而过，只能这样。
}