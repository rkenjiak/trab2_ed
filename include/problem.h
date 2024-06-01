#ifndef __PROBLEM__
#define  __PROBLEM__
#include "./hash.h"

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

char *get_key_ibge(void *reg) {
    return ((tmunicipio *)reg)->codigo_ibge;
}

//TODO: adaptar
void carregaDados(thash *h_ibge,tarv *arv, thash *h_nome, FILE *arq);

#endif