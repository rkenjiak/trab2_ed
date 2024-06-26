#ifndef __HASH__
#define __HASH__
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/* hash */
typedef struct {
        uintptr_t *table;
        int size;
        int max;
        uintptr_t deleted;
        char *(*get_key)(void *);
}thash;

/* funcoes para hash */
int hash_insere(thash *h, void *bucket, int *cont);
int hash_constroi(thash *h,int nbuckets, char *(*get_key)(void *));
void * hash_busca(thash *h, const char *key);
// int hash_remove(thash *h, const char *key);
void hash_apaga(thash *h);


#endif