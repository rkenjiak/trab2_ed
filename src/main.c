#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../include/problem.h"

int main(){
    thash h_ibge;
    tarv avl_nome, avl_lat, avl_long, avl_uf, avl_ddd;
    tset *sNome,*sLat,*sLong,*sUf,*sDDD,*sFinal;
    conjAVL avls;
    tmunicipio *vetor;

    int nbuckets = 15013;
    char leitura[40];
    int escolha = -1;
    int qtd;    
    sNome=sLat=sLong=sUf=sDDD=sFinal=NULL;

    FILE *arquivo = fopen("./data/municipios.json", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");        
        return EXIT_FAILURE;
    }

    carregaDados(&avls,&h_ibge,nbuckets,&avl_nome,&avl_lat,&avl_long,&avl_uf,&avl_ddd,arquivo,&qtd);
    printf("Dados carregados.\n");
    
    while(escolha != 0){
        showQueries(&sNome,&sLat,&sLong,&sUf,&sDDD,&sFinal);
        printf("|-------------------MENU-------------------|\n");
        printf("| 0 - SAIR\n| 1 - ADICIONAR/EDITAR QUERY\n| 2 - IMPRIMIR QUERY\n");
        printf("|------------------------------------------|\n");
        printf("| Digite sua escolha: ");
        if(scanf(" %d",&escolha) == 1) {
            switch (escolha)
            {
            case 1:
                AddEditQuery(&avls,&sNome,&sLat,&sLong,&sUf,&sDDD,qtd,&sFinal);             
                break;
            case 2:
                ShowInterseccao(&avls,&h_ibge,&sNome,&sLat,&sLong,&sUf,&sDDD,&sFinal,&vetor);
                break;
            }
        }else {
            printf("| Escolha invalida.\n");
            while (getchar() != '\n');
            continue;
        }
        
    }

    desalocaSet(&sNome);
    desalocaSet(&sLat);
    desalocaSet(&sLong);
    desalocaSet(&sUf);
    desalocaSet(&sDDD);
    desalocaSet(&sFinal);
        
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