/*
线性表的动态数组实现

此处线性表结构体的初始化使用栈分配，数据堆分配
*/

#include <stdio.h>
#include <stdlib.h>
#include "mydef.h"

#define INITSIZE 100

typedef struct {
    ElemType *data; // 存储空间地址
    int length;     // 有效长度
    int size;       // 存储容量
    int increment;  // 扩容增量
} SqList;

// 初始化线性表
Status init_sq(SqList *L){
    L->data = NULL;
    L->data = (ElemType*)malloc(sizeof(ElemType) * INITSIZE);
    if (L->data == NULL) return ERROR;
    L->length = 0;
    L->size = INITSIZE;
    return OK;
}

Status destroy_sq(SqList *L){
    free(L->data);
    L->data = NULL;
    L->length = 0;
    L->size = 0;
}

Status clear_sq(SqList *L){
    L->length = 0;
}

Status expand_sq(SqList *L){
    ElemType *new_buf;
    new_buf = (ElemType*)realloc(L->data, sizeof(ElemType) * (L->size + L->increment));
    if (new_buf == NULL) return ERROR;
    L->data = new_buf;
    L->size += L->increment;
    return OK;
}

Status append_sq(SqList *L, ElemType e){
    if (L->length >= INITSIZE){
        printf("sqlist is full\n");
        return ERROR;
    }
    L->data[L->length++] = e;
    return OK;
}

Status insert_sq(SqList *L, int pos, ElemType e){
    if (0 <= pos <= L->length){
        for (int i=L->length-1; i>=pos; i--){
            L->data[i+1] = L->data[i];
        }
        L->data[pos] = e;
        L->length++;
        return OK;
    }
    return ERROR;
}

// 查找元素下标
int locate_sq(SqList *L, ElemType e){
    for (int i = 0; i < L->length; i++){
        if (L->data[i] == e) return i;
    }
    return ERROR;
}

// 删除元素并返回
Status delete_sq(SqList *L, int pos, ElemType *e){
    if (pos >= L->length || pos <= 0){
        return ERROR;
    }
    if (e != NULL) *e = L->data[pos];

    for (int i = pos; i < L->length-1; i++){
        L->data[i] = L->data[i+1];
    }
    L->length--;
    return OK;
}

void print_sq(SqList *L){
    for (int i=0; i < L->length; i++){
        printf("%d ", L->data[i]);
    }
    printf("\n");
}

int main(){
    SqList list;
    init_sq(&list);
    printf("数组长度%d\n", list.length);
    printf("结构体字节%zu，数组总字节%zu\n",
        sizeof(SqList), sizeof(list.data));
    append_sq(&list, 11);
    append_sq(&list, 22);
    append_sq(&list, 33);

    insert_sq(&list, 1, 91);
    insert_sq(&list, 0, 90);
    insert_sq(&list, 5, 95);
    print_sq(&list);

    delete_sq(&list, 1, NULL);
    print_sq(&list);
    printf("length:%d\n", list.length);

    destroy_sq(&list);
    return 0;
}