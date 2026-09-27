#include "sqlist.h"
#include <stdio.h>

int main(){
    SqList list;
    init_sq(&list);
    for (int i=0; i<=5; i++){
        append_sq(&list, i);
    }
    print_sq(&list);
    destroy_sq(&list);
    return 0;
}