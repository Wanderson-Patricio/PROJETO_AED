#ifndef HASH_H_INCLUDED
#define HASH_H_INCLUDED

#define MAX_RESOURCES 3 // A quantidade de recursos por compartimento
#define MAX_PERMUTATIONS 6 // 3 recursos por compartimento, dando 3! permutacções
#define MAX_SIZE 667 // 6 diferentes recursos (666+1)

// Anderson
typedef struct resource{
    char nome[50];
    int id;
}Resource;

// Anderson
typedef struct compartment{
    Resource recursos[MAX_RESOURCES];
}Compartment;

// Anderson
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

// Anderson
int isEquals(Compartment a, Compartment b);

Table* createTable();

void deleteTable(Table* t);

void infoTable(Table* t);

/************************************************************/

// Função para concatenar 4 inteiros
// Anderson
int concatenateIntegers(int numbers[], int n);

// Anderson (Cria HEAP Sort e muda)
void selectionSort(int arr[], int n);

// Função hash para o compartimento
// Anderson
int h(Compartment c);

// Anderson
int verificaAbertura(Table* t, int linha);

// Anderson
void resetar(Table* t, int linha);

// Anderson
int isNewPermutation(Table* t, int linha, Compartment c);

void insertCompartment(Table* t, Compartment c);


#endif // HASH_H_INCLUDED
