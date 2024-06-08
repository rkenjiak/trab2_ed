#ifndef __SET__
#define  __SET__
#include "./hash.h"
#include <string.h>

typedef struct{
    char **lista;
    int tam;
    int max;
} tset;

tset * criaSet(int max);
void insereSet(tset * set,const char * cod);
void desalocaSet(tset ** set);
tset * interseccao(tset *t1, tset *t2);

#endif