#ifndef __SQLIST_H__
#define __SQLIST_H__

#include "mydef.h"

#define INITSIZE 100

typedef int ElemType;
typedef struct {
    ElemType *data; // 存储空间地址
    int length;     // 有效长度
    int size;       // 存储容量
    int increment;  // 扩容增量
} SqList;

Status init_sq(SqList *L);
Status init_sq_i(SqList *L, int size, int increment);
Status destroy_sq(SqList *L);
Status clear_sq(SqList *L);
Status expand_sq(SqList *L);

Status append_sq(SqList *L, ElemType e);
Status insert_sq(SqList *L, int pos, ElemType e);
int locate_sq(SqList *L, ElemType e);
Status get_elem_sq(SqList *L, int pos, ElemType *e);
Status delete_sq(SqList *L, int pos, ElemType *e);

void print_sq(SqList *L);
#endif