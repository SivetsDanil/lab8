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

/* Список: массив узлов + служебные поля */
typedef struct {
    Node nodes[MAX_SIZE];
    int head;      /* индекс первого элемента, NIL — список пуст */
    int tail;      /* индекс последнего элемента, NIL — список пуст */
    int size;      /* число элементов (длина за O(1)) */
    int free_head; /* голова цепочки свободных ячеек, NIL — массив полон */
} List;

/* Итератор: навигация без знания внутренностей списка.
   Указателей внутри нет — только индексы */
typedef struct {
    int idx;   /* индекс узла, на который смотрит итератор */
    int steps; /* сколько элементов пройдено = позиция итератора */
} Iterator;

/* Печать элемента словами (для человека, а не цифрой enum) */
const char* elem_to_str(Elem e);

/* Жизненный цикл и стандартные действия */
void list_init(List* l);
int  list_length(const List* l);
void list_print(const List* l);
int  list_insert(List* l, int pos, Elem val);  /* 0 — успех, -1 — ошибка */
int  list_delete(List* l, int pos);            /* 0 — успех, -1 — ошибка */

/* Нестандартное действие №9: исключить последние k элементов.
   Возвращает число реально удалённых (0 — список не менялся) */
int  list_remove_last_k(List* l, int k);

/* Итератор: единственный законный способ ходить по списку */
void iter_init(const List* l, Iterator* it);
int  iter_valid(const Iterator* it);
void iter_next(const List* l, Iterator* it);
void iter_prev(const List* l, Iterator* it);
Elem iter_get(const List* l, const Iterator* it);
int  iter_pos(const Iterator* it);

#endif