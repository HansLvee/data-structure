/*
线性表的单向链表实现
*/

#include <stdio.h>
#include <stdlib.h>
#include "mydef.h"

typedef struct {
    ElemType data;
    struct Node *next;
} Node;

Node* init_sq(){
    Node *head = (Node*)malloc(sizeof(Node));
    head->data = 0;
    head->next = NULL;
    return head;
}



