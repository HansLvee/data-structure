#include "sqlist.h"
#include <stdio.h>
#include <stdlib.h>

// 初始化线性表
Status init_sq(SqList *L){
    L->data = NULL;
    L->data = (ElemType*)malloc(sizeof(ElemType) * INITSIZE);
    if (L->data == NULL) return ERROR;
    L->length = 0;
    L->size = INITSIZE;
    L->increment = (int)(INITSIZE / 2);
    return OK;
}

Status init_sq_i(SqList *L, int size, int increment){
    L->data = NULL;
    L->data = (ElemType*)malloc(sizeof(ElemType) * size);
    if (L->data == NULL) return ERROR;
    L->length = 0;
    L->size = size;
    L->increment = increment;
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

Status get_elem_sq(SqList *L, int pos, ElemType *e){
    if (0 <= pos < L->length){
        *e = L->data[pos];
        return OK;
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