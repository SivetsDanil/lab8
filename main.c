#include <stdio.h>
#include "list.c"

int main(void) {
    List l;
    list_init(&l);
    list_insert(&l, 0, RED);
    list_insert(&l, 1, GREEN);
    list_insert(&l, 2, BLUE);

    list_print(&l);
    list_delete(&l, 0);
    list_print(&l);
    list_delete(&l, 2);
    list_print(&l);
    list_delete(&l, 1);
    list_print(&l);
    list_delete(&l, 0);
    list_print(&l);
    list_insert(&l, 0, RED);
    list_insert(&l, 1, GREEN);
    list_insert(&l, 1, BLUE);
    list_insert(&l, 0, BLUE);
    list_insert(&l, 2, BLUE);
    list_print(&l);
    list_remove_last_k(&l, 10);
    list_print(&l);
    return 0;
}