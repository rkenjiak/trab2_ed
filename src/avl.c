#include<stdio.h>
#include<stdlib.h>
#include "../include/avl.h"

int max(int a,int b){
    return a>b?a:b;
}

int altura(tnode *arv){
    int ret;
    if (arv==NULL){
        ret = -1;
    }else{
        ret = arv->h;
    }
    return ret;
}

void avl_insere(tarv *parv,titem item){
    avl_insere_node(parv,&parv->raiz,item);
}

void avl_insere_node(tarv *parv,tnode ** ppnode,titem item){ //TODO
    if (*ppnode == NULL){
        *ppnode = (tnode *) malloc(sizeof(tnode));
        (*ppnode)->item = item;
        (*ppnode)->esq = NULL;
        (*ppnode)->dir = NULL;
        (*ppnode)->h = 0;

    }else if(((*parv)->item - item)>0){ //
        avl_insere_node(parv,&(*ppnode)->esq,item);
    }else{
        avl_insere_node(parv,&(*ppnode)->dir,item);
    }
    (*ppnode)->h = max(altura((*ppnode)->esq),altura((*ppnode)->dir)) + 1;
    _avl_rebalancear(ppnode);
}

void avl_insere2(tnode ** parv,titem item){ //TODO
    tnode *y = NULL, *x = *parv;
    tnode *z = (tnode *) malloc(sizeof(tnode));
    z->item = item;
    z->esq = NULL;
    z->dir = NULL;
    z->h = 0;
    if (*parv == NULL){
        

    }else if(((*parv)->item - item)>0){
        avl_insere(&(*parv)->esq,item);
    }else{
        avl_insere(&(*parv)->dir,item);
    }
    (*parv)->h = max(altura((*parv)->esq),altura((*parv)->dir)) + 1;
    _avl_rebalancear(parv);
}



void _rd(tnode **parv){
    tnode * y = *parv; 
    tnode * x = y->esq;
    tnode * A = x->esq;
    tnode * B = x->dir;
    tnode * C = y->dir;

    y->esq = B; 
    x->dir = y;
    *parv  = x;
    x->pai = y->pai;
    B->pai = y;
    y->pai = x;    
    y->h = max(altura(B),altura(C)) + 1;
    x->h = max(altura(A),altura(y)) + 1;
}

void _re(tnode **parv){
    tnode * x = *parv; 
    tnode * y = x->dir;
    tnode * A = x->esq;
    tnode * B = y->esq;
    tnode * C = y->dir;

    x->dir = B;
    y->esq = x; 
    *parv  = y;
    y->pai = x->pai;
    B->pai = x;
    x->pai = y;    
    x->h = max(altura(A),altura(B)) + 1;
    y->h = max(altura(x),altura(C)) + 1;
}

void _avl_rebalancear(tnode **parv){
    int fb;
    int fbf;
    tnode * filho;
    fb = altura((*parv)->esq) - altura((*parv)->dir);

    if (fb  == -2){
        filho = (*parv)->dir;
        fbf = altura(filho->esq) - altura(filho->dir);
        if (fbf <= 0){ /* Caso 1  --> ->*/
            _re(parv);
        }else{   /* Caso 2  --> <-*/
            _rd(&(*parv)->dir);
            _re(parv);
        }
    }else if (fb == 2){  
        filho = (*parv)->esq;
        fbf = altura(filho->esq) - altura(filho->dir);
        if (fbf >=0){ /* Caso 3  <-- <-*/
            _rd(parv);
        }else{  /* Caso 4  <-- ->*/
            _re(&(*parv)->esq);
            _rd(parv);
        }
    }
}

tnode ** percorre_esq(tnode ** arv){
    tnode * aux = *arv;
    if (aux->esq  == NULL){
        return arv;
    }else{
        while (aux->esq->esq != NULL)
            aux = aux->esq;
        return &(aux->esq);
    }
}

tnode ** tree_minimum(tnode **arv){
    tnode *aux = *arv;
    while(aux->esq != NULL) aux = aux->esq;
    return &(aux);
}

tnode ** tree_maximum(tnode **arv){
    tnode *aux = *arv;
    while(aux->dir != NULL) aux = aux->dir;
    return &(aux);
}

tnode **sucessor(tnode **arv){
    tnode *x = *arv, *y;
    if(x->dir != NULL){
        return tree_minimum(&(x->dir));
    }
    y = x->pai;
    while(y != NULL && x == y->dir){
        x = y;
        y = y->pai;
    }
    return &y;
}

void avl_remove(tnode **parv, titem reg){
    int cmp;
    tnode *aux;
    tnode **sucessor;
    if (*parv != NULL){
        cmp  = (*parv)->item  - reg;
        if (cmp > 0){ /* ir esquerda*/
            avl_remove(&((*parv)->esq), reg);
        }else if (cmp < 0){ /*ir direita*/
            avl_remove(&((*parv)->dir), reg);
        }else{ /* ACHOU  */
            if ((*parv)->esq == NULL && (*parv)->dir == NULL){   /* no folha */
                free(*parv);
                *parv = NULL;
            }else if ((*parv)->esq == NULL || (*parv)->dir == NULL){ /* tem um filho*/
                aux = *parv;
                if ((*parv)->esq == NULL){
                    *parv = (*parv)->dir;
                }else{
                    *parv = (*parv)->esq;
                }
                free(aux);
            }else{ /* tem dois filhos */
                sucessor = percorre_esq(&(*parv)->dir);
                (*parv)->item = (*sucessor)->item;
                avl_remove(&(*parv)->dir,(*sucessor)->item);
            }
        }
        if (*parv != NULL){
            (*parv)->h = max(altura((*parv)->esq),altura((*parv)->dir)) + 1;
            _avl_rebalancear(parv);
        }
    }
}

void avl_destroi(tnode *parv){ // TODO: free on linkedlist
    if (parv!=NULL){
        avl_destroi(parv->esq);
        avl_destroi(parv->dir);
        free(parv);
    }
}

tnode *paiInsercao(tnode *raiz, titem novoItem) { /// ??????
    tnode *pai = NULL;
    tnode *atual = raiz;

    while (atual != NULL) {
        if (novoItem.chave < atual->item.chave) {
            pai = atual;
            atual = atual->esq;
        } else if (novoItem.chave > atual->item.chave) {
            pai = atual;
            atual = atual->dir;
        } else {
            // Chave duplicada: negar a inserção
            return NULL;
        }
    }

    return pai;
}