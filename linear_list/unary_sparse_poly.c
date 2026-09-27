/*
一元稀疏多项式的顺序表表示

Px = 1 + 7x^10000 + 4x^30000

0       1       2       下标
1       7       4       系数
0       10000   30000   指数
*/

#include <stdio.h>
#include <stdlib.h>
#include "mydef.h"

typedef float coef_t;
typedef int expn_t;

typedef struct {
    coef_t coef; // 系数
    expn_t expn;   // 指数
} Term;
typedef struct {
    Term *data; // 存储空间地址
    int length; // 项数
} Poly;

// 构建一元稀疏多项式
Status init_poly(Poly *P, Term e[], int n){
    P->length = n;
    P->data = (Term*)malloc(sizeof(Term) * n);
    if (P->data == NULL) return ERROR;

    for (int i = 0; i < n; i++) P->data[i] = e[i];
    return OK;
}

int get_length_poly(Poly *P){
    return P->length;
}

// 多项式相加，指数递增排列，Pc无需初始化
Status add_poly(Poly *Pa, Poly *Pb, Poly *Pc){
    int ai = 0, bi = 0, ci = 0;
    Pc->data = (Term*)malloc(sizeof(Term) * (Pa->length + Pb->length));
    if (Pc->data == NULL) return ERROR;

    // Pa 和 Pb 非空
    while(ai < Pa->length && bi < Pb->length){
        if (Pa->data[ai].expn < Pb->data[bi].expn)
            Pc->data[ci++] = Pa->data[ai++];

        else if (Pa->data[ai].expn > Pb->data[bi].expn)
            Pc->data[ci++] = Pb->data[bi++];

        else{
            coef_t total_coef = Pa->data[ai].coef + Pb->data[bi].coef;
            if (total_coef != 0){
                Pc->data[ci].coef = total_coef;
                Pc->data[ci].expn = Pa->data[ai].expn;
                ci++;
            }
            ai++; bi++;
        }
    }

    // Pa 非空，Pb 为空
    while (ai < Pa->length)
        Pc->data[ci++] = Pa->data[ai++];

    // Pb 非空，Pa 为空
    while (bi < Pb->length)
        Pc->data[ci++] = Pb->data[bi++];

    // 重新分配空间
    if (ci < Pa->length + Pb->length){
        Pc->data = (Term*)realloc(Pc->data, sizeof(Term) * ci);
        if (Pc->data == NULL) return ERROR;
    }

    Pc->length = ci;
    return OK;
}

void print_poly(Poly *P){
    for (int i = 0; i < P->length; i++){
        printf("%.0fx^%d", P->data[i].coef, P->data[i].expn);
        if (i < P->length - 1) printf(" + ");
        else printf("\n");
    }
}

// 快速构造项的数组
Status create_terms(Term **T, coef_t coefs[], expn_t expns[], int n){
    *T = (Term*)malloc(sizeof(Term) * n);
    if (*T == NULL) return ERROR;
    for (int i = 0; i < n; i++){
        (*T)[i].coef = coefs[i];
        (*T)[i].expn = expns[i];
    }
    return OK;
}

int main(){
    Poly Pa, Pb, Pc;
    Term *a_terms, *b_terms;
    coef_t a_coefs[] = {2, 7, -2},
           b_coefs[] = {-7, 3, 9, 2};
    expn_t a_expns[] = {1, 4, 6},
           b_expns[] = {4, 6, 7, 9};

    // for (int i = 0; i < 3; i++){
    //     Term temp;
    //     temp.coef = a_coefs[i];
    //     temp.expn = a_expns[i];
    //     a[i] = temp;
    // }
    create_terms(&a_terms, a_coefs, a_expns, 3);
    create_terms(&b_terms, b_coefs, b_expns, 4);
    init_poly(&Pa, a_terms, 3);
    init_poly(&Pb, b_terms, 4);
    print_poly(&Pa);
    print_poly(&Pb);

    add_poly(&Pa, &Pb, &Pc);
    print_poly(&Pc);

    free(Pa.data);
    free(Pb.data);
    free(Pc.data);
    return 0;
}