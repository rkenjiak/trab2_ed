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

void avl_insere(tarv *parv,void * data, int active){
    avl_insere_node(parv,&parv->raiz,NULL,data,active);
}

void avl_insere_node(tarv *parv,tnode ** ppnode, tnode * pai,void * data, int active){ 
    if (*ppnode == NULL){
        *ppnode = (tnode *) malloc(sizeof(tnode));
        //(*ppnode)->item = item; 
        (*ppnode)->esq = NULL;
        (*ppnode)->dir = NULL;
        (*ppnode)->h = 0;
        (*ppnode)->pai = pai;
        (*ppnode)->item = inicializa_llist();
        insere_inicio(data, (*ppnode)->item);

    }else if(parv->cmp((void*)((*ppnode)->item->head->data), data,active)>0){ 
        avl_insere_node(parv,&(*ppnode)->esq,(*ppnode),data,active);
    }else if(parv->cmp((void*)((*ppnode)->item->head->data), data,active)<0){
        avl_insere_node(parv,&(*ppnode)->dir,(*ppnode),data,active);
    }else { // caso que precisa inserir em linkedlist
        insere_inicio(data, (*ppnode)->item); // apenas insere na ll?
    }
    (*ppnode)->h = max(altura((*ppnode)->esq),altura((*ppnode)->dir)) + 1;
    _avl_rebalancear(ppnode);
}

void _rd(tnode **ppnode){
    tnode * y = *ppnode; 
    tnode * x = y->esq;
    tnode * A = x->esq;
    tnode * B = x->dir;
    tnode * C = y->dir;

    y->esq = B; 
    x->dir = y;
    *ppnode = x;
    x->pai = y->pai;
    if(B != NULL)B->pai = y;
    y->pai = x;    
    y->h = max(altura(B),altura(C)) + 1;
    x->h = max(altura(A),altura(y)) + 1;
}

void _re(tnode **ppnode){
    tnode * x = *ppnode; 
    tnode * y = x->dir;
    tnode * A = x->esq;
    tnode * B = y->esq;
    tnode * C = y->dir;

    x->dir = B;
    y->esq = x; 
    *ppnode = y;
    y->pai = x->pai;
    if(B != NULL)B->pai = x;
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
    if(aux->esq == NULL){
        return arv;
    }else{
        while(aux->esq->esq != NULL) aux = aux->esq;
        return &(aux->esq);
    }    
}

tnode ** tree_maximum(tnode **arv){
    tnode *aux = *arv;
    if(aux->dir == NULL){
        return arv;
    }else{
        while(aux->dir->dir != NULL) aux = aux->dir;
        return &(aux->dir);
    }    
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
    if(y == NULL) return NULL; // caso que eh tree_max
    return &(x->pai);
}

void avl_remove(tnode **parv, LinkedList *reg){ /* adaptar para ll */
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

void avl_destroi(tarv * arv, void (*freefunc)(void*)){
    avl_destroi_node(arv->raiz,freefunc);
}

void avl_destroi_node(tnode *pnode, void (*freefunc)(void*)){ // TODO: free on linkedlist
    if (pnode!=NULL){
        avl_destroi_node(pnode->esq,freefunc);
        avl_destroi_node(pnode->dir,freefunc);
        freefunc(pnode->item);
        free(pnode);
    }
}

tnode * achar_inicio(tarv * parv, void * data){
    return achar_node_prox(parv, &parv->raiz,data); 
}

tnode * achar_node_prox(tarv *parv, tnode **ppnode, void *data){
    if(*ppnode == NULL) 
        return NULL;
    if(parv->cmp((void*)((*ppnode)->item->head->data),data,parv->active)>=0){
        tnode * esq = achar_node_prox(parv,&(*ppnode)->esq,data);
        if(esq != NULL){
            return esq;
        }else{
            return *ppnode;
        }
    }    
    return achar_node_prox(parv,&(*ppnode)->dir,data);    
}

tnode * achar_fim(tarv * parv, void * data){
    return achar_node_ant(parv, &parv->raiz,data); 
}

tnode * achar_node_ant(tarv *parv, tnode **ppnode, void *data){
    if(*ppnode == NULL) 
        return NULL;
    if(parv->cmp((void*)((*ppnode)->item->head->data),data,parv->active)<=0){
        tnode * dir = achar_node_ant(parv,&(*ppnode)->dir,data);
        if(dir != NULL){
            return dir;
        }else{
            return *ppnode;
        }
    }    
    return achar_node_ant(parv,&(*ppnode)->esq,data);    
}

