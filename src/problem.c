#include "../include/problem.h"
#define EPSILON 0.000001

char *get_key_ibge(void *reg) {
    return ((tmunicipio *)reg)->codigo_ibge;
}

char *get_key_set(void *reg) {
    return ((tcity *)reg)->codigo_ibge;
}

int cmp (void *a, void *b, int active){
    int arg1_i,arg2_i,resultado;
    float arg1_f,arg2_f;
    switch (active)
    {
    case 1:  // strcasecmp? strings.h      
        int resultado = strcmp(((tcity *)a)->key.nome,((tcity *)b)->key.nome);
        if(resultado<0) return -1;
        if(resultado>0) return 1;
        return 0;
        break;
    case 2:
        arg1_f = ((tcity *)a)->key.latitude;
        arg2_f = ((tcity *)b)->key.latitude;
        if(arg1_f-arg2_f<EPSILON) return -1;
        if(arg1_f-arg2_f>EPSILON) return 1;
        return 0;
        break;
    case 3:
        arg1_f = ((tcity *)a)->key.longitude;
        arg2_f = ((tcity *)b)->key.longitude;
        if(arg1_f-arg2_f<EPSILON) return -1;
        if(arg1_f-arg2_f>EPSILON) return 1;
        return 0;
        break;
    case 4:
        arg1_i = ((tcity *)a)->key.codigo_uf;
        arg2_i = ((tcity *)b)->key.codigo_uf;
        if(arg1_i<arg2_i) return -1;
        if(arg1_i>arg2_i) return 1;
        return 0;
        break;
    case 5:
        arg1_i = ((tcity *)a)->key.ddd;
        arg2_i = ((tcity *)b)->key.ddd;
        if(arg1_i<arg2_i) return -1;
        if(arg1_i>arg2_i) return 1;
        return 0;
        break;
    }
}

void criarAVL(tarv *parv,int active, int (*cmp)(void*,void*,int), void (*freefunc)(void*)){
    parv->raiz = NULL;
    parv->cmp = cmp;
    parv->active = active;
    parv->freefunc = freefunc;
}

void addAVL(tarv *parv, tmunicipio *municipio, int active){
    tcity * new = (tcity *)aloca_city(municipio, active);
    avl_insere(parv,new,active);
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

void carregaDados(thash *h_ibge,int nbuckets,tarv *avl_nome,tarv *avl_lat,tarv *avl_long,tarv *avl_uf,tarv *avl_ddd, FILE *arq){ // TODO
    char linha[60];
    char *start;
    char *end;
    int colisoes;
    int max1=0, tot1=0, max2=0, tot2=0; //contadores colisoes
    int totabb=0, c1=0 , c2=0; //insercoes realizadas
    tmunicipio temp;
    tmunicipio *temp2;

    hash_constroi(h_ibge, nbuckets, get_key_ibge);
    criarAVL(avl_nome,1,cmp,apagar_LL);
    criarAVL(avl_lat,2,cmp,apagar_LL);
    criarAVL(avl_long,3,cmp,apagar_LL);
    criarAVL(avl_uf,4,cmp,apagar_LL);
    criarAVL(avl_ddd,5,cmp,apagar_LL);

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
                addAVL(avl_nome,temp2,avl_nome->active);
                addAVL(avl_lat,temp2,avl_lat->active);
                addAVL(avl_long,temp2,avl_long->active);
                addAVL(avl_uf,temp2,avl_uf->active);
                addAVL(avl_ddd,temp2,avl_ddd->active);
            }
        } else{
            break;
        }
    }
    printf("Carregamento de dados concluido.\n\n");  
    printf("Houve %d insercoes ao utilizar codigo_ibge.\n", c1);
    printf("Houve no maximo %d colisoes em uma insercao.\nHouve %d totais colisoes.\n\n", max1, tot1);
}

void showMenu(){
    printf("|-------------MENU-------------|\n");
    printf("|------------------------------|\n");
    printf("| Digite sua escolha: ");
}

void range_query(char ** vetor, int *tam, int escolha){

}

void print_range_query(tarv * avl){ /// ddd 5 
    int active = 5;
    int a, b;
    printf("Qual range deseja imprimir: ");
    scanf("%d %d", &a, &b);


}