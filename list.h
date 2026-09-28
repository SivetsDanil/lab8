#ifndef LIST_H
#define LIST_H

#define MAX_SIZE 64

#define NIL (-1)

typedef enum {
    RED, GREEN, BLUE, YELLOW, BLACK, WHITE
} Elem;

typedef struct {
    Elem data;
    int prev;
    int next;
} Node;

typedef struct {
    Node nodes[MAX_SIZE];
    int head;
    int tail;
    int size;
    int free_head;
} List;


typedef struct {
    int idx;
    int steps;
} Iterator;

const char* elem_to_str(Elem e);

void list_init(List* l);
int  list_length(const List* l);
void list_print(const List* l);
int  list_insert(List* l, int pos, Elem val);
int  list_delete(List* l, int pos);


int  list_remove_last_k(List* l, int k);

void iter_init(const List* l, Iterator* it);
int  iter_valid(const Iterator* it);
void iter_next(const List* l, Iterator* it);
void iter_prev(const List* l, Iterator* it);
Elem iter_get(const List* l, const Iterator* it);
int  iter_pos(const Iterator* it);

#endif