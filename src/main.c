#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../include/problem.h"

int main(){
    thash h_ibge;
    tarv avl_nome, avl_lat, avl_long, avl_uf, avl_ddd;
    tset *sNome,*sLat,*sLong,*sUf,*sDDD;
    conjAVL avls;
    //conjSets cSets;

    int nbuckets = 15013;
    char leitura[40];
    int escolha = -1;
    int qtd;    
    sNome=sLat=sLong=sUf=sDDD=NULL;

    FILE *arquivo = fopen("./data/municipios.json", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");        
        return EXIT_FAILURE;
    }

    carregaDados(&avls,&h_ibge,nbuckets,&avl_nome,&avl_lat,&avl_long,&avl_uf,&avl_ddd,arquivo,&qtd);
    printf("Dados carregados.\n");
    
    while(escolha != 0){
        showMenu(&avls,sNome,sLat,sLong,sUf,sDDD);
        if(scanf(" %d",&escolha) == 1) {
            switch (escolha)
            {
            case 1:
                AddEditQuery(&avls,&sNome,&sLat,&sLong,&sUf,&sDDD,qtd);             
                break;
            case 2:
                DesativarQuery(&avls,&sNome,&sLat,&sLong,&sUf,&sDDD);
                break;
            case 3:
                ShowInterseccao(&avls,&h_ibge,&sNome,&sLat,&sLong,&sUf,&sDDD);
                break;
            }
        }else {
            printf("| Escolha inválida.\n");
            while (getchar() != '\n');
            continue;
        }
    }
        
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