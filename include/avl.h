#ifndef __AVL__
#define  __AVL__
#include "../include/linkedlist.h"

//typedef LinkedList * titem; 

typedef struct _node{
    LinkedList * item;
    struct _node *esq;
    struct _node *dir;
    struct _node *pai;
    int h;
}tnode;

typedef struct _avl{
    tnode *raiz;
    int (*cmp)(void*, void*, int active);
    void (*freefunc)(void*); // free linkedlist
    int active;
}tarv;

int max(int a,int b);
void avl_insere(tarv *parv,void * data,int active);
void avl_destroi(tarv * parv,void (*freefunc)(void*));// free on linkedlist

tnode ** tree_minimum(tnode **arv);
tnode ** tree_maximum(tnode **arv);
tnode ** sucessor(tnode **arv);

void _rd(tnode ** pparv);
void _re(tnode ** pparv);
void _avl_rebalancear(tnode ** pparv);

tnode * achar_inicio(tarv * parv, void * data); //tcity
tnode * achar_fim(tarv * parv, void * data);

#endif