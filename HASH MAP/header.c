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
        case 6: strcpy(r.nome, "agua"); break;
        default: strcpy(r.nome, ""); break;
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
    printf("Compartimentos na tabela: \n");
    for(int i=0; i<MAX_SIZE; i++){
        if(t->qtds[i] != 0){
            printf("Linha %d - %d compartimentos \n", i, t->qtds[i]);
            infoCompartment(t->tabela[i][0]);
        }
    }
    printf("\nAo total ja foram enviadas %d naves apos a ultima abertura.\n ", t->contador);
}

/************************************************************/

// Fun��o para concatenar 4 inteiros
int concatenateIntegers(int numbers[], int n) {
    int result = 0;

    for(int i=0; i<n; i++){
        result = result*10 + numbers[i];
    }

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

// Fun��o hash para o compartimento
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
            printf("O portal abrira pela primeira vez na %da insercao.\n", t->contador);
        }else{
            printf("O portal abrira novamente na %da insercao apos a %da abertura.\n", t->contador, t->aberturas);
        }

        t->aberturas++;
        resetar(t, linha);
    }
}
