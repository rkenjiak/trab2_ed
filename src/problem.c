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
        int resultado = strcasecmp(((tcity *)a)->key.nome,((tcity *)b)->key.nome);
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
    constroi_conjAVL(avls,avl_nome,avl_lat,avl_long,avl_uf,avl_ddd,0,0,0,0,0);

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
            desalocaSet(new);
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
            desalocaSet(new);
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
            desalocaSet(new);
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
            desalocaSet(new);
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
            desalocaSet(new);
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

void showMenu(conjAVL *avls,tset *sNome,tset*sLat,tset*sLong,tset*sUf,tset*sDDD){
    printf("\n|--------------QUERIES----------------\n");
    if(avls->e1){
        printf("| Há %d cidades na QUERY_NOME.\n",sNome->tam);
    }else{
        printf("| DESATIVADA - QUERY NOME\n");
    }
    if(avls->e2){
        printf("| Há %d cidades na QUERY_LATITUDE.\n",sLat->tam);
    }else{
        printf("| DESATIVADA - QUERY LATITUDE\n");
    }
    if(avls->e3){
        printf("| Há %d cidades na QUERY_LONGITUDE.\n",sLong->tam);
    }else{
        printf("| DESATIVADA - QUERY LONGITUDE\n");
    }
    if(avls->e4){
        printf("| Há %d cidades na QUERY_CODIGO_UF.\n",sUf->tam);
    }else{
        printf("| DESATIVADA - QUERY CODIGO_UF\n");
    }
    if(avls->e5){
        printf("| Há %d cidades na QUERY_DDD.\n",sDDD->tam);
    }else{
        printf("| DESATIVADA - QUERY DDD\n");
    }
    printf("|-------------MENU-------------|\n");
    printf("| 0 - SAIR\n| 1 - ADICIONAR/EDITAR QUERY\n| 2 - DESATIVAR QUERY\n| 3 - IMPRIMIR QUERY\n");
    printf("|------------------------------|\n");
    printf("| Digite sua escolha: ");
}

void constroi_conjAVL(conjAVL *avls,tarv *avl_nome,tarv *avl_lat,tarv *avl_long,tarv *avl_uf,tarv *avl_ddd,int e1,int e2,int e3,int e4,int e5){
    avls->avl_nome = avl_nome;
    avls->avl_lat = avl_lat;
    avls->avl_long = avl_long;
    avls->avl_uf = avl_uf;
    avls->avl_ddd = avl_ddd;
    avls->e1 = e1;
    avls->e2 = e2;
    avls->e3 = e3;
    avls->e4 = e4;
    avls->e5 = e5;
}

void AddEditQuery(conjAVL *avls,tset **sNome,tset**sLat,tset**sLong,tset**sUf,tset**sDDD,int qtd){
    int opc = -1;
    while(opc != 0){
        printf("| (1) NOME  (2) LATITUDE  (3) LONGITUDE  (4) CODIGO_UF  (5) DDD  (0) VOLTAR\nQual opção você deseja adicionar/editar: ");
        if(scanf(" %d", &opc) == 1){
            switch (opc)
            {
            case 1:
                if(*sNome != NULL) desalocaSet(*sNome);
                *sNome = range_query(avls->avl_nome,qtd);  
                avls->e1 = 1;              
                break;
            case 2:
                if(*sLat != NULL) desalocaSet(*sLat);
                *sLat = range_query(avls->avl_lat,qtd);                
                avls->e2 = 1;            
                printf("tam = %d\n",(*sLat)->tam);
                break;
            case 3:
                if(*sLong != NULL) desalocaSet(*sLong);
                *sLong = range_query(avls->avl_long,qtd);     
                avls->e3 = 1;            
                break;
            case 4:
                if(*sUf != NULL) desalocaSet(*sUf);
                *sUf = range_query(avls->avl_uf,qtd);   
                avls->e4 = 1;              
                break;
            case 5:
                if(*sDDD != NULL) desalocaSet(*sDDD);
                *sDDD = range_query(avls->avl_ddd,qtd);         
                avls->e5 = 1;        
                break;
            }
        }else {
            printf("| Escolha inválida.\n");
            while (getchar() != '\n');
            continue;
        }
    }
}

void DesativarQuery(conjAVL *avls,tset **sNome,tset**sLat,tset**sLong,tset**sUf,tset**sDDD){
    int opc=-1;
    while(opc != 0){
        printf("| (1) NOME  (2) LATITUDE  (3) LONGITUDE  (4) CODIGO_UF  (5) DDD  (0) VOLTAR\n| Qual opção você deseja desativar: ");
        if(scanf(" %d", &opc) == 1){
            switch (opc)
            {
            case 1:
                if(sNome != NULL) desalocaSet(*sNome);
                sNome = NULL;            
                avls->e1 = 0; 
                break;
            case 2:
                if(sLat != NULL) desalocaSet(*sLat); 
                sLat = NULL;   
                avls->e2 = 0;           
                break;
            case 3:
                if(sLong != NULL) desalocaSet(*sLong);   
                sLong = NULL;           
                avls->e3 = 0;
                break;
            case 4:
                if(sUf != NULL) desalocaSet(*sUf);              
                sUf = NULL;
                avls->e4 = 0;
                break;
            case 5:
                if(sDDD != NULL) desalocaSet(*sDDD);   
                sDDD = NULL;            
                avls->e5 = 0;
                break;
            }
        }else {
            printf("| Escolha inválida.\n");
            while (getchar() != '\n');
            continue;
        }
    }
}

void imprimeInfoCidade(thash *h_ibge, const char *cod, int tam){
    tmunicipio *municipio = hash_busca(h_ibge, cod);
    printf("| %s ", municipio->codigo_ibge);
    printf("|%-*s ", tam, municipio->nome);
    printf("| %2.4f ",municipio->latitude);
    printf("| %2.4f ",municipio->longitude);
    printf("| %d ",municipio->capital);
    printf("| %d ",municipio->codigo_uf);
    printf("| %d ",municipio->siafi_id);
    printf("| %d ",municipio->ddd);
    printf("| %s\n",municipio->fuso_horario);
}
void imprimeCabecalho(int tam){
    printf("| cod_ibge ");
    printf("|%*cnome ",tam,' ');
    printf("| latitude ");
    printf("| longitude ");
    printf("| capital ");
    printf("| uf ");
    printf("| siafi_id ");
    printf("| ddd ");
    printf("| fuso_horario\n");
}

int maxTam(tset *set){
    int max=0,a;
    if(set==NULL) return 0;
    for(int i=0;i<set->tam;i++){
        a=strlen(set->lista[i]);
        if(a>max) max = a;
    }
    return max;
}

void ShowInterseccao(conjAVL *avls,thash *h_ibge,tset **sNome,tset **sLat,tset **sLong,tset **sUf,tset **sDDD){
    int opc=-1,tam,i;
    tset *p1=NULL,*p2=NULL,*p3=NULL,*pfinal=NULL;
    p1=interseccao(*sNome,*sLat);
    p2=interseccao(p1,*sLong);
    p3=interseccao(p2,*sUf);
    pfinal=interseccao(p3,*sDDD);
    tam = maxTam(pfinal);
    while(opc!=0){
        imprimeCabecalho(tam);
        if(pfinal!=NULL)
        for(i=0;i<pfinal->tam;i++){
            imprimeInfoCidade(h_ibge,pfinal->lista[i],tam);
        }
        printf("| SORT_BY: (1) NOME  (2) LAT  (3) LONG  (4) UF  (5) DDD  (0) SAIR\n| Digite sua escolha: ");
        if(scanf(" %d",&opc)==1){
            switch (opc)
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
        }else {
            printf("| Escolha inválida.\n");
            while (getchar() != '\n');
            continue;

        }
    }   
    if(p1!=NULL)desalocaSet(p1);
    if(p2!=NULL)desalocaSet(p2);
    if(p3!=NULL)desalocaSet(p3);
    if(pfinal!=NULL)desalocaSet(pfinal); 
}