/*
顺序表数组实现
*/

#include <stdio.h>

#define MAXSIZE 100
#define ERROR (-1)
#define OK 0

typedef int ElemType;
typedef struct {
    ElemType data[MAXSIZE];
    int length;
} SqList;

// 初始化线性表
void init_sq(SqList *L){
    L->length = 0;
}