#include"../include/linkedlist.h"

celula * busca_S(void * bucket, celula *lst){
    celula *p;
    p = lst;
    while(p != NULL && p->bucket != bucket)
        p = p->prox;
    return p;
}

void insere_inicio(void * bucket, celula **lst){
    celula *nova;
    nova = (celula *) malloc(sizeof(celula));
    nova->bucket = bucket;
    nova->prox = *lst;
    *lst = nova;
}

void insere_fim(void * bucket, celula **lst){
    celula *p;
    celula *novo = (celula *) malloc(sizeof(celula));
    novo->bucket = bucket;
    novo->prox = NULL;
    if(*lst == NULL){
        *lst = novo;
    }else{
        p = *lst;
        while(p->prox != NULL) p = p->prox;
        p->prox = novo;
    }
}

void busca_remove_S(void * bucket, celula **lst){
    celula *p, *q;
    p = NULL;
    q = *lst;
    while(q != NULL && q->bucket != bucket){
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

void apagar_LL(celula **lst){
    celula *aux;
    while(*lst != NULL){
        aux = *lst;
        *lst = (*lst)->prox;
        free(aux);
    }
}