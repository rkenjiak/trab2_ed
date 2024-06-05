#include "../include/set.h"

tset * criaSet(int max){
    tset * new = (tset *)malloc(sizeof(tset));
    char **lista = (char **)malloc(max * sizeof(char *));
    new->lista = lista;
    new->max = max;
    new->tam = 0;
    return new;
}

void desalocaSet(tset * set){
    for(int i = 0; i<set->tam; i++){
        free(set->lista[i]);
    }
    free(set->lista);
    free(set);
}

// nao esta verificando se cod ja esta no set
void insereSet(tset * set,const char * cod){ // strings de tam no max 9
    char *palavra = (char*)malloc(10*sizeof(char));
    strcpy(palavra,cod);
    set->lista[set->tam] = palavra;
    set->tam += 1;
}

tset * interseccao(tset *t1, tset *t2){
    int i, j;
    tset * new = criaSet(t1->max);
    for(i = 0; i<t1->tam;i++){
        for(j = 0; j<t2->tam; j++){
            if(strcmp(t1->lista[i],t2->lista[j]) == 0){
                insereSet(new, t1->lista[i]);
                break;
            }
        }
    }
    return new;
}