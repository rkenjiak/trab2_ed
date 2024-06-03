#include"../include/linkedlist.h"

celula * cria_cel(void * data){
    celula * new = (celula *) malloc(sizeof(celula));
    new->data = (uintptr_t)data;
    new->prox = NULL;
    return new;
}

LinkedList * inicializa_llist(){
    LinkedList * new = (LinkedList *)malloc(sizeof(LinkedList));
    new->head = NULL;
    return new;
}

/*
celula * busca_S(void * bucket, celula *lst){
    celula *p;
    p = lst;
    while(p != NULL && p->data != bucket)
        p = p->prox;
    return p;
}
*/

void insere_inicio(void * bucket, LinkedList *lst){
    celula *nova = cria_cel(bucket);
    nova->prox = lst->head;
    lst->head = nova;
}

void insere_fim(void * bucket, LinkedList *lst){
    celula *p;
    celula *novo = cria_cel(bucket);
    if(lst->head == NULL){
        lst->head = novo;
    }else{
        p = lst->head;
        while(p->prox != NULL) p = p->prox;
        p->prox = novo;
    }
}

/*
void busca_remove_S(void * bucket, celula **lst){
    celula *p, *q;
    p = NULL;
    q = *lst;
    while(q != NULL && q->data != bucket){
        p = q;
        q = q->prox;
    }
    if(q != NULL){
        if(p != NULL){
            p->prox = q->prox;
            free(q);
        }else{
            *lst = q->prox;
            free(q);
        }
    }
}
*/

void apagar_LL(LinkedList *lst){
    celula *aux1, *aux2 = (lst)->head;
    while(aux2 != NULL){
        aux1 = aux2;
        aux2 = aux2->prox;
        free(aux1);
    }
    free(lst);
}