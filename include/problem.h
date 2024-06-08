#ifndef __PROBLEM__
#define  __PROBLEM__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "./hash.h"
#include "./avl.h"
#include "./linkedlist.h"
#include "./set.h"

typedef struct{
    char codigo_ibge[10];
    char nome[40];
    float latitude;
    float longitude;
    int capital;
    int codigo_uf;
    int siafi_id;
    int ddd;
    char fuso_horario[40];
}tmunicipio;

typedef struct{
    union{
        char nome[40];
        float latitude;
        float longitude;
        int codigo_uf;
        int ddd;
    }key;
    char codigo_ibge[10];
    int active;
}tcity;

typedef struct{
    tarv *avl_nome;
    tarv *avl_lat;
    tarv *avl_long;
    tarv *avl_uf;
    tarv *avl_ddd;
}conjAVL;


void showQueries(tset **sNome,tset**sLat,tset**sLong,tset**sUf,tset**sDDD);
char *get_key_ibge(void *reg);
int cmp (void *a, void *b, int active);
void criarAVL(tarv *parv, int active, int (*cmp)(void*,void*,int),void (*freefunc)(void*));
void addAVL(tarv *parv, tmunicipio *municipio, int active);
void *aloca_city(tmunicipio *municipio, int active);
void *aloca_municipio(char *codigo_ibge, char *nome, float latitude, float longitude, int capital, int codigo_uf, int siafi_id, int ddd, char *fuso_horario);
void carregaDados(conjAVL *avls, thash *h_ibge,int nbuckets,tarv *avl_nome,tarv *avl_lat,tarv *avl_long,tarv *avl_uf,tarv *avl_ddd, FILE *arq,int *qtd);
void loop_insere_set(tset *set, tnode *start, tnode *end);
tset * range_query(tarv *avl,int qtd);
void constroi_conjAVL(conjAVL *avls,tarv *avl_nome,tarv *avl_lat,tarv *avl_long,tarv *avl_uf,tarv *avl_ddd);
void AddEditQuery(conjAVL *avls,tset **sNome,tset**sLat,tset**sLong,tset**sUf,tset**sDDD,int qtd);
void DesativarQuery(tset **sNome,tset**sLat,tset**sLong,tset**sUf,tset**sDDD);
void ShowInterseccao(conjAVL *avls,thash *h_ibge,tset **sNome,tset **sLat,tset **sLong,tset **sUf,tset **sDDD);



#endif