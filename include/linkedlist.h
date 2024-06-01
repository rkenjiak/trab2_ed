#ifndef __LINKEDLIST__
#define  __LINKEDLIST__
#include<stdlib.h>

typedef struct linkedlist{
    uintptr_t * bucket;
    struct linkedlist *prox;
}celula;

celula * busca_S(void * bucket, celula *lst);
void insere_inicio(void * bucket, celula **lst);
void insere_fim(void * bucket, celula **lst);
void busca_remove_S(void * bucket, celula **lst);
void apagar_LL(celula **lst);


#endif