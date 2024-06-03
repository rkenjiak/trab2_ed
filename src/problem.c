#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/problem.h"
#define EPSILON 0.000001

int cmp (void *a, void *b, int active){
    switch (active)
    {
    case 1:        
        int resultado = strcmp(((tcity *)a)->key.nome,((tcity *)b)->key.nome);
        if(resultado<0) return -1;
        if(resultado>0) return 1;
        return 0;
        break;
    case 2:
        float arg1 = ((tcity *)a)->key.latitude;
        float arg2 = ((tcity *)b)->key.latitude;
        if(arg1-arg2<EPSILON) return -1;
        if(arg1-arg2>EPSILON) return 1;
        return 0;
        break;
    case 3:
        float arg1 = ((tcity *)a)->key.longitude;
        float arg2 = ((tcity *)b)->key.longitude;
        if(arg1-arg2<EPSILON) return -1;
        if(arg1-arg2>EPSILON) return 1;
        return 0;
        break;
    case 4:
        int arg1 = ((tcity *)a)->key.codigo_uf;
        int arg2 = ((tcity *)b)->key.codigo_uf;
        if(arg1<arg2) return -1;
        if(arg1>arg2) return 1;
        return 0;
        break;
    case 5:
        int arg1 = ((tcity *)a)->key.ddd;
        int arg2 = ((tcity *)b)->key.ddd;
        if(arg1<arg2) return -1;
        if(arg1>arg2) return 1;
        return 0;
        break;
    }
}

void criarAVL(tarv *parv, char *(*get_key)(void *), int (*cmp)(void*,void*)){
    parv->raiz = NULL;
    parv->cmp = cmp;
    parv->get_key = get_key;
}

void addAVL(tarv *parv, tmunicipio *municipio, int active){
    tcity * new = (tcity *)aloca_city(municipio, active); 
    switch (active)
    {
    case 1:
        
        break;
    case 2:

        break;
    case 3:

        break;
    case 4:

        break;
    case 5:

        break;
    }

    //avl_insere(parv,new);

}

void *aloca_city(tmunicipio *municipio, int active){
    tcity * new = malloc(sizeof(tcity));
    new->active = active;
    strcpy(new->codigo_ibge, municipio->codigo_ibge);
    switch (active)
    {
    case 1: //nome
        strcpy(new->key.nome, municipio->nome);        
        break;
    case 2: //latitude
        new->key.latitude = municipio->latitude;
        break;
    case 3: //longitude
        new->key.longitude = municipio->longitude;
        break;
    case 4: //codigo_uf
        new->key.codigo_uf = municipio->codigo_uf;
        break;
    case 5: //ddd
        new->key.ddd = municipio->ddd;
        break;
    }
    return new;
}

void *aloca_municipio(char *codigo_ibge, char *nome, float latitude, float longitude, int capital,
                      int codigo_uf, int siafi_id, int ddd, char *fuso_horario) {
    tmunicipio *municipio = malloc(sizeof(tmunicipio));
    strcpy(municipio->codigo_ibge, codigo_ibge);
    strcpy(municipio->nome, nome);
    municipio->latitude = latitude;
    municipio->longitude = longitude;
    municipio->capital = capital;
    municipio->codigo_uf = codigo_uf;
    municipio->siafi_id = siafi_id;
    municipio->ddd = ddd;
    strcpy(municipio->fuso_horario, fuso_horario);
    return municipio;
}

void carregaDados(thash *h_ibge,tarv *arv, FILE *arq){ // TODO
    char linha[60];
    char *start;
    char *end;
    int colisoes;
    int max1=0, tot1=0, max2=0, tot2=0; //contadores colisoes
    int totabb=0, c1=0 , c2=0; //insercoes realizadas
    tmunicipio temp;
    tmunicipio *temp2;

    while(1){
        if(fgets (linha, 60, arq)!=NULL) {
            start = strchr(linha,'\"');
            if(start == NULL) {
                continue;
            } else{                
                start = strchr(linha,':') + 2;
                end = strrchr(start,',');
                *end = '\n';
                sscanf(start," %s", temp.codigo_ibge);

                fgets (linha, 60, arq);            
                start = strchr(linha,':') + 3;
                end = strrchr(start,'\"');
                *end = '\n';
                sscanf(start," %[^\n]", temp.nome);

                fgets (linha, 60, arq);            
                start = strchr(linha,':') + 1;
                end = strrchr(start,',');
                *end = '\n';
                sscanf(start,"%f", &temp.latitude);    

                fgets (linha, 60, arq);            
                start = strchr(linha,':') + 1;
                end = strrchr(start,',');
                *end = '\n';
                sscanf(start,"%f", &temp.longitude);

                fgets (linha, 60, arq);            
                start = strchr(linha,':') + 1;
                end = strrchr(start,',');
                *end = '\n';
                sscanf(start,"%d", &temp.capital);

                fgets (linha, 60, arq);
                start = strchr(linha,':') + 1;
                end = strrchr(start,',');
                *end = '\n';
                sscanf(start,"%d", &temp.codigo_uf);

                fgets (linha, 60, arq);            
                start = strchr(linha,':') + 1;
                end = strrchr(start,',');
                *end = '\n';
                sscanf(start,"%d", &temp.siafi_id);

                fgets (linha, 60, arq);            
                start = strchr(linha,':') + 1;
                end = strrchr(start,',');
                *end = '\n';
                sscanf(start,"%d", &temp.ddd);

                fgets (linha, 60, arq);            
                start = strchr(linha,':') + 3;
                end = strrchr(start,'\"');
                *end = '\n';
                sscanf(start," %[^\n]", temp.fuso_horario);
                
                temp2 = aloca_municipio(temp.codigo_ibge, temp.nome, temp.latitude, temp.longitude, 
                    temp.capital, temp.codigo_uf, temp.siafi_id, temp.ddd, temp.fuso_horario);

                /*hash_ibge*/
                colisoes = 0;
                if(hash_insere(h_ibge, temp2, &colisoes) == EXIT_SUCCESS) c1 += 1;
                tot1 += colisoes;
                if(colisoes>max1) max1 = colisoes;

            }
        } else{
            break;
        }
    }
    printf("Carregamento de dados concluido.\n\n");  
    printf("Houve %d insercoes ao utilizar codigo_ibge.\n", c1);
    printf("Houve no maximo %d colisoes em uma insercao.\nHouve %d totais colisoes.\n\n", max1, tot1);
    printf("Houve %d insercoes ao utilizar nome.\n", c2);
    printf("Houve no maximo %d colisoes em uma insercao.\nHouve %d totais colisoes.\n\n", max2, tot2);
}