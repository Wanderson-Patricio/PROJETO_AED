#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "header.h"

/************************************************************/

Resource createResource(int id){
    Resource r;
    r.id = id;
    switch(id){
        case 1: strcpy(r.nome, "minerios"); break;
        case 2: strcpy(r.nome, "combustivel"); break;
        case 3: strcpy(r.nome, "remedios"); break;
        case 4: strcpy(r.nome, "comida"); break;
        case 5: strcpy(r.nome, "armamento"); break;
    }

    return r;
}

void infoResource(Resource r){
    printf("id: %d - %s \n", r.id, r.nome);
}

Compartment createCompartment(int ids[]){
    Compartment c;
    for(int i=0; i<MAX_RESOURCES; i++){
        c.recursos[i] = createResource(ids[i]);
    }

    return c;
}

void infoCompartment(Compartment c){
    printf("******************************\n");
    for(int i=0; i<MAX_RESOURCES; i++){
        infoResource(c.recursos[i]);
    }
    printf("******************************\n");
}

int isEquals(Compartment a, Compartment b){
    for(int i=0; i<MAX_RESOURCES; i++){
        if(a.recursos[i].id != b.recursos[i].id){
            return 0;
        }
    }

    return 1;
}

Table* createTable(){
    Table* t = (Table*)malloc(sizeof(Table));

    if(t != NULL){
        for(int i = 0; i<MAX_SIZE; i++){
            t->qtds[i] = 0;
        }

        t->contador = 0;
        t->aberturas = 0;
    }

    return t;
}

void deleteTable(Table* t){
    free(t);
}

void infoTable(Table* t){
    /*
    for(int i=0; i<MAX_SIZE; i++){
        if(t->qtds[i] != 0){
            printf("----------------------------------------------\n");
            printf("Compartimentos na linha %d: \n", i);
            for(int j=0; j<t->qtds[i]; j++){
                infoCompartment(t->tabela[i][j]);
            }
            printf("----------------------------------------------\n");
        }
    }
    */
    for(int i=0; i<MAX_SIZE; i++){
        if(t->qtds[i] != 0){
            printf("Linha %d - %d compartimentos \n", i, t->qtds[i]);
        }
    }
    printf("\nAo total ja foram enviadas %d naves após a última abertura.\n ", t->contador);
}

/************************************************************/

// Função para concatenar 4 inteiros
int concatenateIntegers(int numbers[], int n) {
    // Convert integers to strings
    char str[n][12];

    for(int i=0; i<n; i++){
        sprintf(str[i], "%d", numbers[i]);
    }

    // Concatenate the strings
    char concatenatedStr[12*n]; // Adjust the size based on your requirements
    strcpy(concatenatedStr, str[0]);

    for(int i=1; i<n; i++){
        strcat(concatenatedStr, str[i]);
    }

    // Convert the concatenated string back to an integer
    int result = atoi(concatenatedStr);

    return result;
}

void selectionSort(int arr[], int n){
    int aux, menor;

    for(int i=0; i<n-1; i++){
        menor = i;
        for(int j=i+1; j<n; j++){
            if(arr[j]<arr[menor]){
                menor = j;
            }
        }

        aux = arr[i];
        arr[i] = arr[menor];
        arr[menor] = aux;
    }
}

// Função hash para o compartimento
int h(Compartment c){
    int ids[MAX_RESOURCES];
    for(int i=0; i<MAX_RESOURCES; i++){
        ids[i] = c.recursos[i].id;
    }

    selectionSort(ids, MAX_RESOURCES);

    return concatenateIntegers(ids, MAX_RESOURCES);
}

int verificaAbertura(Table* t, int linha){
    if(t->qtds[linha] == MAX_PERMUTATIONS){
        return 1;
    }

    return 0;
}

void resetar(Table* t, int linha){
    t->qtds[linha] = 0;
    t->contador = 0;
}

int isNewPermutation(Table* t, int linha, Compartment c){
    for(int coluna=0; coluna<t->qtds[linha]; coluna++){
        if(isEquals(c, t->tabela[linha][coluna]) == 1){
            return 0;
        }
    }

    return 1;
}

void insertCompartment(Table* t, Compartment c){
    int linha = h(c);
    int coluna = t->qtds[linha];

    if(coluna < MAX_PERMUTATIONS){

        if(isNewPermutation(t, linha, c) == 1){
            t->tabela[linha][coluna] = c;
            t->qtds[linha] = coluna + 1;
        }
        t->contador++;

    }

    if(verificaAbertura(t, linha) == 1){
        if(t->aberturas == 0){
            printf("O portal abrirá pela primeira vez na %dª inserção.\n", t->contador);
        }else{
            printf("O portal abrirá novamente na %dª inserção após a %dª abertura.\n", t->contador, t->aberturas);
        }
        t->aberturas++;
        resetar(t, linha);
    }
}






