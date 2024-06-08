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
    if(t1==NULL && t2==NULL)return NULL;
    else if(t1==NULL) return t2;
    else if(t2==NULL) return t1;
    else{
        int i, j, mintam;
        mintam = (t1->tam<t2->tam) ? t1->tam : t2->tam;
        tset * new = criaSet(mintam);
        for(i = 0; i<t1->tam;i++){
            for(j = 0; j<t2->tam; j++){
                if(strcmp(t1->lista[i],t2->lista[j]) == 0){
                    insereSet(new, t1->lista[i]);                    
                }
            }
        }
        return new;
    }    
}