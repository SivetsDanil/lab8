#include <stdio.h>
#include "list.h"

const char* elem_to_str(Elem e) {
    static const char* names[] = {"RED", "GREEN", "BLUE", "YELLOW", "BLACK", "WHITE"};
    if (e < 0 || e > WHITE)
        return "?";
    return names[e];
}

static int alloc_index(List* l) {
    if (l->free_head == NIL)
        return NIL;
    int idx = l->free_head;
    l->free_head = l->nodes[idx].next;
    return idx;
}

static void free_index(List* l, int idx) {
    l->nodes[idx].next = l->free_head;
    l->free_head = idx;
}

void list_init(List* l) {
    l->head = NIL;
    l->tail = NIL;
    l->size = 0;
    for (int i = 0; i < MAX_SIZE - 1; i++)
        l->nodes[i].next = i + 1;
    l->nodes[MAX_SIZE - 1].next = NIL;
    l->free_head = 0;
}

int list_length(const List* l) {
    return l->size;
}

void iter_init(const List* l, Iterator* it) {
    it->idx = l->head;
    it->steps = 0;
}

int iter_valid(const Iterator* it) {
    return it->idx != NIL;
}

void iter_next(const List* l, Iterator* it) {
    if (iter_valid(it)) {
        it->idx = l->nodes[it->idx].next;
        it->steps++;
    }
}

void iter_prev(const List* l, Iterator* it) {
    if (it->steps <= 0)
        return;
    if (it->idx == NIL)
        it->idx = l->tail;
    else
        it->idx = l->nodes[it->idx].prev;
    it->steps--;
}

Elem iter_get(const List* l, const Iterator* it) {
    return l->nodes[it->idx].data;
}

int iter_pos(const Iterator* it) {
    return it->steps;
}

void list_print(const List* l) {
    if (l->size == 0) {
        printf("empty\n");
        return;
    }
    Iterator it;
    for (iter_init(l, &it); iter_valid(&it); iter_next(l, &it))
        printf("%s ", elem_to_str(iter_get(l, &it)));
    printf("\n");
}

int list_insert(List* l, int pos, Elem val) {
    if (pos < 0 || pos > l->size)
        return -1;
    int idx = alloc_index(l);
    if (idx == NIL)
        return -1;
    Iterator it;
    iter_init(l, &it);
    for (int i = 0; i < pos; i++)
        iter_next(l, &it);
    int q = it.idx;
    l->nodes[idx].data = val;
    l->nodes[idx].next = q;
    if (q == NIL) {
        l->nodes[idx].prev = l->tail;
    }else {
        l->nodes[idx].prev = l->nodes[q].prev;
    }
    if (q != NIL)
        l->nodes[q].prev = idx;
    else
        l->tail = idx;

    if (l->nodes[idx].prev != NIL)
        l->nodes[l->nodes[idx].prev].next = idx;
    else
        l->head = idx;
    l->size++;
    return 0;
}
int  list_delete(List* l, int pos) {
    if (pos < 0 || pos >= l->size)
        return -1;
    Iterator it;
    iter_init(l, &it);
    for (int i = 0; i < pos; i++)
        iter_next(l, &it);
    int idx = it.idx;
    int p = l->nodes[idx].prev;
    int n = l->nodes[idx].next;
    if (p != NIL)
        l->nodes[p].next = n;
    else
        l->head = n;
    if (n != NIL)
        l->nodes[n].prev = p;
    else
        l->tail = p;
    free_index(l, idx);
    l->size--;
    return 0;
}
int list_remove_last_k(List* l, int k){
    if (k > l->size) {
        return -1;
    }
    for (int i = 0; i < k; i++) {
        list_delete(l, l->size-1);
    }
    return 0;
}