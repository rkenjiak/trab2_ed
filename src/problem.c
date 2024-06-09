#include "../include/problem.h"

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
        resultado = strcasecmp(((tcity *)a)->key.nome,((tcity *)b)->key.nome);
        if(resultado<0) return -1;
        if(resultado>0) return 1;
        return 0;
        break;
    case 2:
        arg1_f = ((tcity *)a)->key.latitude;
        arg2_f = ((tcity *)b)->key.latitude;
        if(arg1_f<arg2_f) return -1;
        if(arg1_f>arg2_f) return 1;
        return 0;
        break;
    case 3:
        arg1_f = ((tcity *)a)->key.longitude;
        arg2_f = ((tcity *)b)->key.longitude;
        if(arg1_f<arg2_f) return -1;
        if(arg1_f>arg2_f) return 1;
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

void carregaDados(conjAVL *avls,thash *h_ibge,int nbuckets,tarv *avl_nome,tarv *avl_lat,tarv *avl_long,tarv *avl_uf,tarv *avl_ddd, FILE *arq,int *qtd){ // TODO
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
    constroi_conjAVL(avls,avl_nome,avl_lat,avl_long,avl_uf,avl_ddd);

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
    *qtd = c1;
}



tset * range_query(tarv *avl, int qtd){
    int a, b, auxi;
    float c, d, auxf;
    char palavra_1[40];
    char palavra_2[40];
    char aux[40];
    tset * new = criaSet(qtd);
    tnode * start;
    tnode * end;
    tcity temp;
    switch (avl->active)
    {
    case 1:        
        printf("| Digite uma palavra para pesquisar através do nome: ");
        scanf(" %[^\n]",palavra_1);
        printf("| Digite outra palavra para pesquisar através do nome: ");
        scanf(" %[^\n]",palavra_2);
        if(strcasecmp(palavra_1,palavra_2)>0){
            strcpy(aux,palavra_1);
            strcpy(palavra_1,palavra_2);
            strcpy(palavra_2,aux);
        }
        temp.active = avl->active;
        strcpy(temp.key.nome,palavra_1);
        start = achar_inicio(avl,&temp);

        strcpy(temp.key.nome,palavra_2);
        end = achar_fim(avl,&temp);

        if(start == NULL || end == NULL){
            desalocaSet(&new);
            new = NULL;
        }else{
            loop_insere_set(new,start,end);
        }
        break;
    case 2:
        printf("| Digite os 2 valores (float) de latitude que deseja buscar: ");
        scanf("%f %f", &c, &d);
        if(c>d){
            auxf = c;
            c = d;
            d = auxf;
        }
        temp.active = avl->active;
        temp.key.latitude = c;
        start = achar_inicio(avl,&temp);

        temp.key.latitude = d;
        end = achar_fim(avl,&temp);

        if(start == NULL || end == NULL){
            desalocaSet(&new);
            new = NULL;
        }else{
            loop_insere_set(new,start,end);
        }
        break;
    case 3:
        printf("| Digite os 2 valores (float) de longitude que deseja buscar: ");
        scanf("%f %f", &c, &d);
        if(c>d){
            auxf = c;
            c = d;
            d = auxf;
        }
        temp.active = avl->active;
        temp.key.longitude = c;
        start = achar_inicio(avl,&temp);

        temp.key.longitude = d;
        end = achar_fim(avl,&temp);

        if(start == NULL || end == NULL){
            desalocaSet(&new);
            new = NULL;
        }else{
            loop_insere_set(new,start,end);
        }
        break;
    case 4:
        printf("| Digite os 2 valores (int) de codigo_uf que deseja buscar: ");
        scanf("%d %d", &a, &b);
        if(a>b){
            auxi = a;
            a = b;
            b = auxi;
        }
        temp.active = avl->active;
        temp.key.codigo_uf = a;
        start = achar_inicio(avl,&temp);

        temp.key.codigo_uf = b;
        end = achar_fim(avl,&temp);

        if(start == NULL || end == NULL){
            desalocaSet(&new);
            new = NULL;
        }else{
            loop_insere_set(new,start,end);
        }
        break;
    case 5:   
        printf("| Digite os 2 valores (int) de ddd que deseja buscar: ");
        scanf("%d %d", &a, &b);
        if(a>b){
            auxi = a;
            a = b;
            b = auxi;
        }
        temp.active = avl->active;
        temp.key.ddd = a;
        start = achar_inicio(avl,&temp);
        
        temp.key.ddd = b;
        end = achar_fim(avl,&temp);

        if(start == NULL || end == NULL){
            desalocaSet(&new);
            new = NULL;
        }else{
            loop_insere_set(new,start,end);
        }
        break;    
    }
    return new;
}


void loop_insere_set(tset *set, tnode *start, tnode *end){
    celula *aux;    
    while(start != end){
        aux = start->item->head;
        while(aux != NULL){
            insereSet(set,((tcity *)(aux->data))->codigo_ibge);
            aux = aux->prox;
        }
        start = *(sucessor(&start));
    }
    if(start == end){
        aux = start->item->head;
        while(aux != NULL){
            insereSet(set,((tcity *)(aux->data))->codigo_ibge);
            aux = aux->prox;
        }        
    }
}

void showQueries(tset **sNome,tset**sLat,tset**sLong,tset**sUf,tset**sDDD,tset**sFinal){
    printf("|\n|--------------QUERIES----------------\n");
    if(*sNome!=NULL){
        printf("| Há %d cidades na QUERY_NOME.\n",(*sNome)->tam);
    }else{
        printf("| DESATIVADA - QUERY NOME\n");
    }
    if(*sLat!=NULL){
        printf("| Há %d cidades na QUERY_LATITUDE.\n",(*sLat)->tam);
    }else{
        printf("| DESATIVADA - QUERY LATITUDE\n");
    }
    if(*sLong!=NULL){
        printf("| Há %d cidades na QUERY_LONGITUDE.\n",(*sLong)->tam);
    }else{
        printf("| DESATIVADA - QUERY LONGITUDE\n");
    }
    if(*sUf!=NULL){
        printf("| Há %d cidades na QUERY_CODIGO_UF.\n",(*sUf)->tam);
    }else{
        printf("| DESATIVADA - QUERY CODIGO_UF\n");
    }
    if(*sDDD!=NULL){
        printf("| Há %d cidades na QUERY_DDD.\n",(*sDDD)->tam);
    }else{
        printf("| DESATIVADA - QUERY DDD\n");
    }    
    if(*sFinal!=NULL){
        printf("| Há %d cidades nas QUERIES selecionadas.\n",(*sFinal)->tam);
    }else{
        printf("| Não há nenhuma QUERY selecionada.\n");
    }

}

void constroi_conjAVL(conjAVL *avls,tarv *avl_nome,tarv *avl_lat,tarv *avl_long,tarv *avl_uf,tarv *avl_ddd){
    avls->avl_nome = avl_nome;
    avls->avl_lat = avl_lat;
    avls->avl_long = avl_long;
    avls->avl_uf = avl_uf;
    avls->avl_ddd = avl_ddd;
}

void AddEditQuery(conjAVL *avls,tset **sNome,tset**sLat,tset**sLong,tset**sUf,tset**sDDD,int qtd,tset**sFinal){
    int opc = -1;
    while(opc != 0){        
        showQueries(sNome,sLat,sLong,sUf,sDDD,sFinal);
        printf("|--------------------------------------------------------------------------\n");
        printf("| (1) NOME  (2) LATITUDE  (3) LONGITUDE  (4) CODIGO_UF  (5) DDD  (6) DESATIVAR QUERY  (0) VOLTAR\n| Qual opção você deseja adicionar/editar: ");
        if(scanf(" %d", &opc) == 1){
            switch (opc)
            {
            case 1:
                if(*sNome != NULL) desalocaSet(sNome);
                *sNome = range_query(avls->avl_nome,qtd);  
                break;
            case 2:
                if(*sLat != NULL) desalocaSet(sLat);
                *sLat = range_query(avls->avl_lat,qtd);   
                break;
            case 3:
                if(*sLong != NULL) desalocaSet(sLong);
                *sLong = range_query(avls->avl_long,qtd);     
                break;
            case 4:
                if(*sUf != NULL) desalocaSet(sUf);
                *sUf = range_query(avls->avl_uf,qtd);   
                break;
            case 5:
                if(*sDDD != NULL) desalocaSet(sDDD);
                *sDDD = range_query(avls->avl_ddd,qtd);  
                break;
            case 6:
                DesativarQuery(sNome,sLat,sLong,sUf,sDDD,sFinal);
                break;
            }            
        }else {
            printf("| Escolha inválida.\n");
            while (getchar() != '\n');
            continue;
        }
        desalocaSet(sFinal);
        *sFinal=calculaInterseccao(sNome,sLat,sLong,sUf,sDDD);
    }
}

void DesativarQuery(tset **sNome,tset**sLat,tset**sLong,tset**sUf,tset**sDDD,tset**sFinal){
    int opc=-1;
    while(opc != 0){        
        showQueries(sNome,sLat,sLong,sUf,sDDD,sFinal);
        printf("|--------------------------------------------------------------------------\n");
        printf("| (1) NOME  (2) LATITUDE  (3) LONGITUDE  (4) CODIGO_UF  (5) DDD  (0) VOLTAR\n| Qual opção você deseja desativar: ");
        if(scanf(" %d", &opc) == 1){
            switch (opc)
            {
            case 1:
                if(*sNome != NULL) desalocaSet(sNome);
                *sNome = NULL;  
                break;
            case 2:
                if(*sLat != NULL) desalocaSet(sLat); 
                *sLat = NULL;            
                break;
            case 3:
                if(*sLong != NULL) desalocaSet(sLong);   
                *sLong = NULL;      
                break;
            case 4:
                if(*sUf != NULL) desalocaSet(sUf);              
                *sUf = NULL;
                break;
            case 5:
                if(*sDDD != NULL) desalocaSet(sDDD);   
                *sDDD = NULL;       
                break;
            }            
        }else {
            printf("| Escolha inválida.\n");
            while (getchar() != '\n');
            continue;
        }
        desalocaSet(sFinal);
        *sFinal=calculaInterseccao(sNome,sLat,sLong,sUf,sDDD);
    }
}

void imprimeInfoCidade(thash *h_ibge, const char *cod, int tam){
    tmunicipio *municipio = hash_busca(h_ibge, cod);
    printf("|  %s ", municipio->codigo_ibge);
    printf("| %-*s ", tam+1, municipio->nome);
    printf("| %8.4f ",municipio->latitude);
    printf("|  %8.4f ",municipio->longitude);
    printf("| %7d ",municipio->capital);
    printf("| %d ",municipio->codigo_uf);
    printf("| %8d ",municipio->siafi_id);
    printf("| %3d ",municipio->ddd);
    printf("| %s\n",municipio->fuso_horario);
}
void imprimeInfoCidade2(tmunicipio *municipio, int tam){
    printf("|  %s ", municipio->codigo_ibge);
    printf("| %-*s ", tam+1, municipio->nome);
    printf("| %8.4f ",municipio->latitude);
    printf("|  %8.4f ",municipio->longitude);
    printf("| %7d ",municipio->capital);
    printf("| %d ",municipio->codigo_uf);
    printf("| %8d ",municipio->siafi_id);
    printf("| %3d ",municipio->ddd);
    printf("| %s\n",municipio->fuso_horario);
}
void imprimeCabecalho(int tam){
    printf("| cod_ibge ");
    printf("| nome%*c ",tam-3,' ');
    printf("| latitude ");
    printf("| longitude ");
    printf("| capital ");
    printf("| uf ");
    printf("| siafi_id ");
    printf("| ddd ");
    printf("| fuso_horario\n");
}

int utf8_strlen(const char *s) {
    int i = 0, j = 0;
    while (s[i]) {
        if ((s[i] & 0xc0) != 0x80)
            j++;
        i++;
    }
    return j;
}

int maxTam(tset *set,thash *h_ibge){
    int max=0,a;
    tmunicipio *municipio;
    if(set==NULL) return 0;
    for(int i=0;i<set->tam;i++){
        municipio = hash_busca(h_ibge, set->lista[i]);
        a=utf8_strlen(municipio->nome);
        if(a>max) max = a;
    }
    return max;
}

tset * calculaInterseccao(tset **sNome,tset **sLat,tset **sLong,tset **sUf,tset **sDDD){
    tset *p1=NULL,*p2=NULL,*p3=NULL,*pfinal=NULL;
    p1=interseccao(*sNome,*sLat);
    p2=interseccao(p1,*sLong);
    p3=interseccao(p2,*sUf);
    pfinal=interseccao(p3,*sDDD);
    desalocaSet(&p1);
    desalocaSet(&p2);
    desalocaSet(&p3);
    return pfinal;
}

void criaVetor(tset *sFinal, tmunicipio ** vetor,thash *h_ibge){
    if(sFinal==NULL) return;
    tmunicipio *temp;
    size_t tam = sizeof(tmunicipio);
    (*vetor) = (tmunicipio*)malloc(sFinal->tam*sizeof(tmunicipio));
    for(int i=0;i<sFinal->tam;i++){
        temp=hash_busca(h_ibge,sFinal->lista[i]);
        memcpy((*vetor)+i,temp,tam);
    }
}
void destroiVertor(tset *tFinal,tmunicipio ** vetor){
    free(*vetor);
    *vetor = NULL;
}

int cmp_nome(const void*a,const void*b){
    return strcasecmp(((tmunicipio*)a)->nome,((tmunicipio*)b)->nome);
}
int cmp_lat(const void*a,const void*b){
    float arg1_f,arg2_f;   
    arg1_f = ((tmunicipio *)a)->latitude;
    arg2_f = ((tmunicipio *)b)->latitude;
    if(arg1_f<arg2_f) return -1;
    if(arg1_f>arg2_f) return 1;
    return 0;
}
int cmp_long(const void*a,const void*b){
    float arg1_f,arg2_f;   
    arg1_f = ((tmunicipio *)a)->longitude;
    arg2_f = ((tmunicipio *)b)->longitude;
    if(arg1_f<arg2_f) return -1;
    if(arg1_f>arg2_f) return 1;
    return 0;   
}
int cmp_uf(const void*a,const void*b){
    return ((tmunicipio*)a)->codigo_uf-((tmunicipio*)b)->codigo_uf;    
}
int cmp_ddd(const void*a,const void*b){
    return ((tmunicipio*)a)->ddd-((tmunicipio*)b)->ddd;
}

void ShowInterseccao(conjAVL *avls,thash *h_ibge,tset **sNome,tset **sLat,tset **sLong,tset **sUf,tset **sDDD,tset**sFinal,tmunicipio **vetor){
    int opc=-1,tam,i,sorted=0;
    desalocaSet(sFinal);
    *sFinal=calculaInterseccao(sNome,sLat,sLong,sUf,sDDD);
    tam = maxTam(*sFinal,h_ibge);
    criaVetor(*sFinal,vetor,h_ibge);

    while(opc!=0){
        imprimeCabecalho(tam);
        if(sFinal!=NULL)
        for(i=0;i<(*sFinal)->tam && !sorted;i++){
            imprimeInfoCidade(h_ibge,(*sFinal)->lista[i],tam);
        }
        for(i=0;i<(*sFinal)->tam && sorted;i++){
            imprimeInfoCidade2((*vetor)+i,tam);
        }
        printf("| SORT_BY: (1) NOME  (2) LAT  (3) LONG  (4) UF  (5) DDD  (0) SAIR\n| Digite sua escolha: ");
        if(scanf(" %d",&opc)==1){
            switch (opc)
            {
            case 1:
                sorted=1;
                qsort(*vetor,(*sFinal)->tam,sizeof(tmunicipio),cmp_nome);                 
                break;
            case 2:
                sorted=1;
                qsort(*vetor,(*sFinal)->tam,sizeof(tmunicipio),cmp_lat);                          
                break;
            case 3:
                sorted=1;
                qsort(*vetor,(*sFinal)->tam,sizeof(tmunicipio),cmp_long);
                break;
            case 4:
                sorted=1;
                qsort(*vetor,(*sFinal)->tam,sizeof(tmunicipio),cmp_uf);
                break;
            case 5:
                sorted=1;
                qsort(*vetor,(*sFinal)->tam,sizeof(tmunicipio),cmp_ddd);
                break;
            }
        }else {
            printf("| Escolha inválida.\n");
            while (getchar() != '\n');
            continue;
        }
    }   
    destroiVertor(*sFinal,vetor);
    desalocaSet(sFinal); 
}