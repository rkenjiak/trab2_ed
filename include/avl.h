#ifndef __AVL__
#define  __AVL__

typedef LinkedList * titem;

typedef struct _node{
    titem item;
    struct _node *esq;
    struct _node *dir;
    struct _node *pai;
    int h;
}tnode;

typedef struct _avl{
    tnode *raiz;
    int (*cmp)(void*, void*, int active);
    char *(*get_key)(void *); // ?
    void (*freefunc)(void*); // free linkedlist
}tarv;

void avl_insere(tarv *parv,titem reg,int active);
void avl_insere_node(tarv *parv,tnode **ppnode,tnode *pai,titem reg,int active);
void avl_remove(tnode ** parv,titem reg);
void avl_destroi_node(tnode *pnode,void (*freefunc)(void*)); // free on linkedlist
void avl_destroi(tarv * parv,void (*freefunc)(void*));

tnode ** tree_minimum(tnode **arv);
tnode ** tree_maximum(tnode **arv);
tnode ** sucessor(tnode **arv);

void _rd(tnode ** pparv);
void _re(tnode ** pparv);
void _avl_rebalancear(tnode ** pparv);

#endif