#ifndef __AVL__
#define  __AVL__

typedef void ** titem;

typedef struct _node{
    titem item;
    struct _node *esq;
    struct _node *dir;
    struct _node *pai;
    int h;
}tnode;

typedef struct _avl{
    tnode *raiz;
    int (*cmp)(void*, void*);
    char *(*get_key)(void *); // ?
}tarv;

void avl_insere(tarv *parv,titem reg);
void avl_insere_node(tarv *parv,tnode ** ppnode,titem reg);
void avl_remove(tnode ** parv,titem reg);
void avl_destroi(tnode * parv);

tnode ** tree_minimum(tnode **arv);
tnode ** tree_maximum(tnode **arv);
tnode ** sucessor(tnode **arv);

void _rd(tnode ** pparv);
void _re(tnode ** pparv);
void _avl_rebalancear(tnode ** pparv);

#endif