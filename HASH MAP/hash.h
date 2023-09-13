#ifndef HASH_H_INCLUDED
#define HASH_H_INCLUDED

#define MAX_RESOURCES 4
#define MAX_PERMUTATIONS 24 //4 recursos por compartimento, dando 4! permutacções
#define MAX_SIZE 555 //Cinco diferentes recursos

typedef struct resource{
    char nome[50];
    int id;
}Resource;

typedef struct compartment{
    Resource recursos[MAX_RESOURCES];
}Compartment;

typedef struct table{
    Compartment tabela[MAX_SIZE][MAX_PERMUTATIONS];
    int qtds[MAX_SIZE];
    int contador;
}Table;

Resource createResource(int id);

void infoResource(Resource r);

Compartment createCompartment(int ids[]);

void infoCompartment(Compartment c);

Table* createTable();

void deleteTable(Table* t);

/************************************************************/

// Função para concatenar 4 inteiros
int concatenateIntegers(int numbers[], int n);

void selectionSort(int arr[], int n);

// Função hash para o compartimento
int h(Compartment c);

void insertCompartment(Table* t, Compartment c);

#endif // HASH_H_INCLUDED
