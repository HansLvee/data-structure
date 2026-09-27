/*
有序顺序表的归并
*/

#include <stdio.h>
#include "sqlist.h"

void merge_sqlist(SqList *La, SqList *Lb, SqList *Lc);

int main(){
    SqList La, Lb, Lc;
    init_sq(&La);
    init_sq(&Lb);
    for (int i=0; i<5; i++) append_sq(&La, i);
    for (int i=5; i<10; i++) append_sq(&Lb, i);
    print_sq(&La);
    print_sq(&Lb);
    merge_sqlist(&La, &Lb, &Lc);
    print_sq(&Lc);
    destroy_sq(&La);
    destroy_sq(&Lb);
    destroy_sq(&Lc);
    return 0;
}

void merge_sqlist(SqList *La, SqList *Lb, SqList *Lc){
    int ai = 0, bi = 0;
    ElemType a, b;

    int size = La->length + Lb->length;
    init_sq_i(Lc, size, size);

    // 两顺序表均非空时
    while (ai < La->length && bi < Lb->length){
        get_elem_sq(La, ai, &a);
        get_elem_sq(Lb, bi, &b);
        if (a <= b){
            append_sq(Lc, a);
            ai++;
        }
        else{
            append_sq(Lc, b);
            bi++;
        }
    }

    // La 非空，Lb 为空
    while (ai < La->length){
        get_elem_sq(La, ai++, &a);
        append_sq(Lc, a);
    }

    // Lb 非空，La 为空
    while (bi < Lb->length){
        get_elem_sq(Lb, bi++, &b);
        append_sq(Lc, b);
    }
}