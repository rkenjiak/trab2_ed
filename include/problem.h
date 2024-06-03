#ifndef __PROBLEM__
#define  __PROBLEM__
#include "./hash.h"
#include "./avl.h"
#include "./linkedlist.h"

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
    //char *(*key)(void *); ??
    int active;
}tcity;

char *get_key_ibge(void *reg) {
    return ((tmunicipio *)reg)->codigo_ibge;
}

void criarAVL(tarv *parv, char *(*get_key)(void *), int (*cmp)(void*,void*));
void *aloca_city(tmunicipio *municipio, int active);
void *aloca_municipio(char *codigo_ibge, char *nome, float latitude, float longitude, int capital, int codigo_uf, int siafi_id, int ddd, char *fuso_horario);
void carregaDados(thash *h_ibge,tarv *arv, FILE *arq);

#endif