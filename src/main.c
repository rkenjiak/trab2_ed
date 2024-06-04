#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../include/problem.h"





int main(){
    thash h_ibge;
    tarv arv;
    int nbuckets = 15013;
    char leitura[40];
    int escolha;


    FILE *arquivo = fopen("./data/municipios.json", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");        
        return EXIT_FAILURE;
    }

    hash_constroi(&h_ibge, nbuckets, get_key_ibge);
    printf("Hash construido.\n");
    criarAVL(&arv,2,cmp,apagar_LL);
    printf("AVL1 construido\n");
    carregaDados(&h_ibge,&arv,arquivo);
    printf("Dados carregados.\n");
    
    
    
    
    
    
    
    
    
    //printf("Test\n");
    hash_apaga(&h_ibge);
    printf("Hash apagada.\n");
    avl_destroi(&arv,arv.freefunc);
    printf("AVL apagada.\n");
    fclose(arquivo);
    printf("Arquivo fechado.\n");
    return EXIT_SUCCESS;
}