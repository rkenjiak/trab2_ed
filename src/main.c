#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../include/problem.h"
#include "../include/avl.h"
#include "../include/hash.h"
#include "../include/linkedlist.h"




int main(){


    FILE *arquivo = fopen("./data/municipios.json", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");        
        return EXIT_FAILURE;
    }   




    fclose(arquivo);
    return EXIT_SUCCESS;
}