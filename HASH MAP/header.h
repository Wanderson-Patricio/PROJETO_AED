#ifndef HASH_H_INCLUDED
#define HASH_H_INCLUDED

#define MAX_RESOURCES 3 // A quantidade de recursos por compartimento
#define MAX_PERMUTATIONS 6 // 3 recursos por compartimento, dando 3! permutacções
#define MAX_SIZE 556 // 5 diferentes recursos (555+1)

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
    int aberturas;
}Table;

Resource createResource(int id);

void infoResource(Resource r);

Compartment createCompartment(int ids[]);

void infoCompartment(Compartment c);

int isEquals(Compartment a, Compartment b);

Table* createTable();

void deleteTable(Table* t);

void infoTable(Table* t);

/************************************************************/

// Função para concatenar 4 inteiros
int concatenateIntegers(int numbers[], int n);

void selectionSort(int arr[], int n);

// Função hash para o compartimento
int h(Compartment c);

int verificaAbertura(Table* t, int linha);

void resetar(Table* t, int linha);

int isNewPermutation(Table* t, int linha, Compartment c);

void insertCompartment(Table* t, Compartment c);


#endif // HASH_H_INCLUDED
