#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../include/problem.h"





int main(){
    thash h_ibge;
    tarv avl_nome, avl_lat, avl_long, avl_uf, avl_ddd;
    int nbuckets = 15013;
    char leitura[40];
    int escolha;


    FILE *arquivo = fopen("./data/municipios.json", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");        
        return EXIT_FAILURE;
    }

    carregaDados(&h_ibge,nbuckets,&avl_nome,&avl_lat,&avl_long,&avl_uf,&avl_ddd,arquivo);
    printf("Dados carregados.\n");
    
    
    
    
    
    
    
    
    
    hash_apaga(&h_ibge);
    printf("Hash apagada.\n");
    avl_destroi(&avl_nome,avl_nome.freefunc);
    avl_destroi(&avl_lat,avl_lat.freefunc);
    avl_destroi(&avl_long,avl_long.freefunc);
    avl_destroi(&avl_uf,avl_uf.freefunc);
    avl_destroi(&avl_ddd,avl_ddd.freefunc);
    printf("AVL apagada.\n");
    fclose(arquivo);
    printf("Arquivo fechado.\n");
    return EXIT_SUCCESS;
}