#ifndef __LINKEDLIST__
#define  __LINKEDLIST__
#include <stdlib.h>
#include <stdint.h>

typedef struct _celula{
    uintptr_t data; // tcity
    struct _celula *prox;
}celula;

typedef struct _LinkedList{
    celula * head;
} LinkedList;

LinkedList * inicializa_llist();
void insere_inicio(void * data, LinkedList *lst);
void insere_fim(void * data, LinkedList *lst);
void apagar_LL(void *lst);


#endif